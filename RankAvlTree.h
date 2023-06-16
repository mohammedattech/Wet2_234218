#ifndef RANK_AVL_TREE_H
#define RANK_AVL_TREE_H

#include "exceptions.h"
#include"pair.h"
#include <iostream>

using std::cout;
using std::ostream;

//Generic Avl tree. created by Bashar Abu-Leil.
static int max(int a, int b);

/*static int max(int a, int b) {
    return a > b ? a : b;
}*/



template<class T, class K,class E>
class RankAvlTree 
{
public:
    RankAvlTree() : m_root(nullptr), m_size(0) {}

    RankAvlTree(const RankAvlTree &) = delete;

    RankAvlTree &operator=(const RankAvlTree &) = delete;

    ~RankAvlTree();

    void insert(K key, T data);

    void remove(K key);

    bool search(K key) const;

    struct node {
        node *m_right;
        node *m_left;
        node *m_parent;
        int m_height;
        int m_bf;
        K m_key;
        T m_data;
        E m_extra;
        node(T data, K key) : m_right(nullptr), m_left(nullptr), m_parent(nullptr), m_height(0), m_bf(0), m_key(key),
                              m_data(data),m_extra(E(0)) {}
    };

    int getSize() const;

    void InOrder(node *vertics, int *arr, int length, int *index) const;

    void InOrder(int *arr, int length, int *index) const;

    void printInOrder(node *vertics) const;

    void printInOrder() const;

    static node *BuildCompleteTree(int hegiht, K defKey, T defData);

    void setRoot(node *root);

    T &getData(K key);

    node *getRoot();

    template<class pred>
    void inorderExecution(pred &function);

    template<class pred>
    void reset(pred &function);
    T *getMinumumData();
    node* getMinumumNode() const;

    void addExtra(K index1 , K index2,E amount );

    E getExtra(K key)const;
private:
    node *m_root;
    int m_size;

    node *searchNode(K key);

    node *findNextInOrder(node *vertics);

    node * findPreviousInOrder(K index);

    node * findPreviousInOrder(node *vertics);

    void removeLeaf(node *vertics);

    void removeHasOneSon(node *vertics);

    void swapNodes(node *v1, node *v2);

    void updateBfAndBalance(node *vertics, bool insert);

    void merge(const RankAvlTree &);

    void updateBf(node *vertics);

    void updateHeight(node *vertics);

    void destroyTree(node *vertics);

    void RotateLL(node *vertics);

    void RotateRR(node *vertics);

    void RotateLR(node *vertics);

    void RotateRL(node *vertics);

    void ExtraBalanceRR(node* vertics);

    void ExtraBalanceLL(node* vertics);

    template<class pred>
    void inorderExecution(node *vertics, pred &function);

    template<class pred>
    void reset(node *vertics, pred &function);
    void addExtra(K index1, E amount);
};


template<class T, class K,class E>
bool RankAvlTree<T, K,E>::search(K key) const {
    if (!m_root)
        return false;
    node *temp = m_root;
    while (temp) {
        if (temp->m_key == key)
            return true;
        else if (temp->m_key < key)
            temp = temp->m_right;
        else
            temp = temp->m_left;
    }
    return false;
}


template<class T, class K,class E>
void RankAvlTree<T, K,E>::insert(K key, T data) {
    node *newNode = new node(data, key);
    if (!m_size) {
        m_root = newNode;
        m_size++;
        return;
    }
    node *temp = searchNode(key);
    if (temp->m_key == key) 
    {
        delete newNode;
        throw ElementExists();
    } else if (temp->m_key < key) {
        temp->m_right = newNode;
    } else {
        temp->m_left = newNode;
    }
    newNode->m_parent = temp;
    m_size++;
    E extrasum=getExtra(key);
    newNode->m_extra=-extrasum;
    updateBfAndBalance(newNode, true);
}

template<class T, class K,class E>
RankAvlTree<T, K, E>::~RankAvlTree() {
    destroyTree(m_root);
}

template<class T, class K, class E>
void RankAvlTree<T, K, E>::destroyTree(node *vertics) {
    if (!vertics)
        return;
    destroyTree(vertics->m_left);
    destroyTree(vertics->m_right);
    delete vertics;
}

template<class T, class K,class E>
void RankAvlTree<T, K,E>::updateBfAndBalance(node *vertics, bool insert) {
    node *temp = vertics;
    while (temp) {
        updateHeight(temp);
        updateBf(temp);
        if (temp->m_bf > 1) {
            if (temp->m_left->m_bf >= 0) {
                RotateLL(temp);
            } else {
                if (temp->m_left->m_bf == -1) {
                    RotateLR(temp);
                }
            }
            if (insert) {
                break;
            }
        }
        if (temp->m_bf < -1) {
            if (temp->m_right->m_bf <= 0) {
                RotateRR(temp);
            } else {
                if (temp->m_right->m_bf == 1) {
                    RotateRL(temp);
                }
            }
            if (insert) {
                break;
            }
        }
        temp = temp->m_parent;
    }
}

template<class T, class K,class E>
void RankAvlTree<T, K ,E>::updateBf(node *vertics) {
    int left = vertics->m_left ? vertics->m_left->m_height : -1;
    int right = vertics->m_right ? vertics->m_right->m_height : -1;
    vertics->m_bf = left - right;
}


template<class T, class K,class E>
void RankAvlTree<T, K, E>::updateHeight(node *vertics) {
    int left = vertics->m_left ? vertics->m_left->m_height : -1;
    int right = vertics->m_right ? vertics->m_right->m_height : -1;
    vertics->m_height = 1 + max(left, right);
}


template<class T, class K,class E>
void RankAvlTree<T, K,E>::printInOrder(node *vertics) const {
    if (!vertics)
        return;
    printInOrder(vertics->m_left);
    cout << "(" << vertics->m_key << "," << vertics->m_data << "),";
    cout << "bf:" << vertics->m_bf << ",height:" << vertics->m_height << std::endl;
    printInOrder(vertics->m_right);
}


template<class T, class K,class E>
void RankAvlTree<T, K ,E>::printInOrder() const {
    printInOrder(m_root);
}


template<class T, class K,class E>
void RankAvlTree<T, K, E>::InOrder(node *vertics, int *arr, int length, int *index) const {
    if (!vertics)
        return;
    InOrder(vertics->m_left, arr, length, index);
    arr[*index] = vertics->m_key;
    *index = *index + 1;
    InOrder(vertics->m_right, arr, length, index);
}


template<class T, class K,class E>
void RankAvlTree<T, K,E>::InOrder(int *arr, int length, int *index) const {
    InOrder(m_root, arr, length, index);
}

template<class T, class K,class E>
typename RankAvlTree<T, K,E>::node *RankAvlTree<T, K,E>::searchNode(K key) {
    node *temp1 = m_root;
    node *temp2 = m_root;
    while (temp2) {
        temp1 = temp2;
        if (temp2->m_key == key)
            return temp2;
        else if (temp2->m_key < key) {
            temp2 = temp2->m_right;
        } else {
            temp2 = temp2->m_left;
        }
    }
    return temp1;
}


template<class T, class K,class E>
void RankAvlTree<T, K,E>::remove(K key) {
    if (!m_size)
        throw ElementDoesntExist();
    node *temp = searchNode(key);
    if (temp->m_key != key)
        throw ElementDoesntExist();
    if (!temp->m_height) {
        removeLeaf(temp);
    } else if ((temp->m_left && !temp->m_right) || (!temp->m_left && temp->m_right)) {
        removeHasOneSon(temp);
    } else {
        node *nextIn = findNextInOrder(temp);
        swapNodes(nextIn, temp);
        if (!nextIn->m_height) {
            removeLeaf(nextIn);
        } else {
            removeHasOneSon(nextIn);
        }
    }
}


template<class T, class K,class E>
typename RankAvlTree<T, K,E>::node *RankAvlTree<T, K,E>::findNextInOrder(node *vertics) {
    node *temp = vertics;
    if (temp->m_right) {
        temp = temp->m_right;
        while (temp->m_left) {
            temp = temp->m_left;
        }
    } else if (temp->m_parent) {
        if (temp->m_parent->m_left == temp)
            temp = temp->m_parent;
    }
    return temp;
}

template<class T, class K,class E>
void RankAvlTree<T, K, E>::removeLeaf(node *vertics) {
    if (vertics == m_root) {
        m_root = nullptr;
    } else {
        node *temp = vertics->m_parent;
        if (temp->m_left == vertics) {
            temp->m_left = nullptr;
        } else {
            temp->m_right = nullptr;
        }
        updateBfAndBalance(temp, false);
    }
    delete vertics;
    m_size--;
}


template<class T, class K,class E>
void RankAvlTree<T, K,E>::swapNodes(node *v1, node *v2) {
    T tempData = v2->m_data;
    K tempKey = v2->m_key;
    v2->m_data = v1->m_data;
    v2->m_key = v1->m_key;
    v1->m_data = tempData;
    v1->m_key = tempKey;
}

template<class T, class K,class E>
void RankAvlTree<T, K,E>::removeHasOneSon(node *vertics) {
    node *temp = vertics->m_left ? vertics->m_left : vertics->m_right;
    if (vertics->m_parent) {
        node *parent = vertics->m_parent;
        if (parent->m_left == vertics) {
            parent->m_left = temp;
        } else {
            parent->m_right = temp;
        }
        temp->m_parent = parent;
    } else {
        m_root = temp;
        m_root->m_parent = nullptr;
    }
    delete vertics;
    m_size--;
    updateBfAndBalance(temp, false);
}

template<class T, class K,class E>
typename RankAvlTree<T, K,E>::node *RankAvlTree<T, K,E>::BuildCompleteTree(int height, K defKey, T defData) {
    if (!height) {
        node *leaf = new node(defData, defKey);
        return leaf;
    }
    node *head = new node(defData, defKey);
    node *leftSon = BuildCompleteTree(height - 1, defKey, defData);
    node *rightSon = BuildCompleteTree(height - 1, defKey, defData);
    head->m_left = leftSon;
    head->m_right = rightSon;
    leftSon->m_parent = rightSon->m_parent = head;
    return head;
}

template<class T, class K,class E>
void RankAvlTree<T, K,E>::setRoot(node *root) {
    destroyTree(m_root);
    m_root = root;
    m_root->m_parent = nullptr;
}

template<class T, class K,class E>
void RankAvlTree<T, K,E>::RotateLL(node *vertics) 
{
    ExtraBalanceLL(vertics);
    node *parent = vertics->m_parent;
    node *leftSon = vertics->m_left;
    vertics->m_left = leftSon->m_right;
    if (vertics->m_left) {
        vertics->m_left->m_parent = vertics;
    }
    leftSon->m_right = vertics;
    vertics->m_parent = leftSon;
    leftSon->m_parent = parent;
    if (parent) {
        if (parent->m_right == vertics) {
            parent->m_right = leftSon;
        }
        if (parent->m_left == vertics) {
            parent->m_left = leftSon;
        }
    } else {
        m_root = leftSon;
    }
    updateHeight(vertics);
    updateBf(vertics);
    updateHeight(leftSon);
    updateBf(leftSon);
    if (parent) {
        updateHeight(parent);
        updateBf(parent);
    }
}

template<class T, class K,class E>
void RankAvlTree<T, K,E>::RotateRR(node *vertics) 
{
    ExtraBalanceRR(vertics);
    node *parent = vertics->m_parent;
    node *rightSon = vertics->m_right;
    vertics->m_right = rightSon->m_left;
    if (vertics->m_right) {
        vertics->m_right->m_parent = vertics;
    }
    rightSon->m_left = vertics;
    vertics->m_parent = rightSon;
    rightSon->m_parent = parent;
    if (parent) {
        if (parent->m_right == vertics) {
            parent->m_right = rightSon;
        }
        if (parent->m_left == vertics) {
            parent->m_left = rightSon;
        }
    } else {
        m_root = rightSon;
    }
    updateHeight(vertics);
    updateBf(vertics);
    updateHeight(rightSon);
    updateBf(rightSon);
    if (parent) {
        updateHeight(parent);
        updateBf(parent);
    }
}

template<class T, class K,class E>
void RankAvlTree<T, K,E>::RotateLR(node *vertics) {
    RotateRR(vertics->m_left);
    RotateLL(vertics);
}

template<class T, class K,class E>
void RankAvlTree<T, K,E>::RotateRL(node *vertics) {
    RotateLL(vertics->m_right);
    RotateRR(vertics);
}

template<class T, class K,class E>
template<class pred>
void RankAvlTree<T, K,E>::inorderExecution(pred &function) {
    inorderExecution(m_root, function);
}

template<class T, class K,class E>
template<class pred>
void RankAvlTree<T, K,E>::inorderExecution(node *vertics, pred &function) {
    if (vertics) {
        inorderExecution(vertics->m_left, function);
        function(vertics->m_data);
        inorderExecution(vertics->m_right, function);
    }
}

template<class T, class K,class E>
int RankAvlTree<T, K,E>::getSize() const {
    return m_size;
}

template<class T, class K,class E>
T &RankAvlTree<T, K,E>::getData(K key) {
    node *temp = searchNode(key);
    if (!(temp) || temp->m_key != key || !m_size)
        throw ElementDoesntExist();
    return temp->m_data;
}

template<class T, class K,class E>
typename RankAvlTree<T, K,E>::node *RankAvlTree<T, K,E>::getRoot() {
    return m_root;
}

template<class T, class K,class E>
T *RankAvlTree<T, K,E>::getMinumumData() {
    if (!m_root) {
        return nullptr;
    }
    node *minimumNode = m_root;
    while (minimumNode->m_left) {
        minimumNode = minimumNode->m_left;
    }
    return &minimumNode->m_data;
}

template<class T, class K,class E>
typename RankAvlTree<T, K,E>::node* RankAvlTree<T, K,E>::getMinumumNode() const
{
    if (!m_root) {
        return nullptr;
    }
    node *minimumNode = m_root;
    while (minimumNode->m_left) {
        minimumNode = minimumNode->m_left;
    }
    return minimumNode;
}
template<class T,class K,class E>
typename RankAvlTree<T,K,E>::node* RankAvlTree<T,K,E>::findPreviousInOrder(node *vertics){
    node *temp = vertics;
    if(temp->m_left){
        temp=temp->m_left;
        while(temp->m_right){
            temp=temp->m_right;
        }
        return temp;
    }
    else if (temp->m_parent&&temp->m_parent->m_right==temp){
        return temp->m_parent;
    }
    return temp;
}

template<class T,class K ,class E>
typename RankAvlTree<T,K,E>::node* RankAvlTree<T,K,E>::findPreviousInOrder(K index){
    node* temp=searchNode(index);
    return temp ? findPreviousInOrder(temp) : temp;
}


template<class T,class K,class E>
void RankAvlTree<T,K,E>::addExtra(K index1,K index2,E amount)
{
    addExtra(index1,-amount);
    addExtra(index2,amount);
    /*
    if(m_size==0){
        return;
    }
    node* previous1=findPreviousInOrder(index1);
    node* previous2=findPreviousInOrder(index2);
    node* minimumNode=getMinumumNode();
    if(previous2->m_key<=index2){
        addExtra(previous2->m_key,amount);
    }
    if(previous1&&previous1!=minimumNode){
        addExtra(previous1->m_key,-amount);
    }
    */

}

template<class T,class K,class E>
void RankAvlTree<T,K,E>::addExtra(K index,E amount){
    node*temp=m_root;
    bool right=false;
    while (temp)
    {
        if(temp->m_key<index){
            if(!right){
                right=true;
                temp->m_extra+=amount;
            }
            if (temp->m_key==index)
            {
                break;   
            }
            temp=temp->m_right;
        }
        else{
            if(right){
                right=false;
                temp->m_extra-=amount;
            }
            if (temp->m_key==index)
            {
                break;   
            }
            temp=temp->m_left;
        }
    }
}

template<class T,class K,class E>
E RankAvlTree<T,K,E>::getExtra(K key)const{
    if(!search(key)){
        throw ElementDoesntExist();
    }
    node* temp=m_root;
    E extra=E(0);
    while(temp){
        extra+=temp->m_extra;
        if(temp->m_key<key){
            temp=temp->m_right;
        }
        else if(temp->m_key>key)
        {
            temp=temp->m_left;
        }
        else
        {
            break;
        }
    }
    return extra;
}
template<class T,class K,class E>
void RankAvlTree<T,K,E>::ExtraBalanceLL(node* vertics)
{
    E verticsExtra= vertics->m_extra;
    E verticsLeftSonExtra= vertics->m_left->m_extra;
    if(vertics->m_left->m_right)
    {
        vertics->m_left->m_right->m_extra+=verticsLeftSonExtra;
    }
    vertics->m_extra=-verticsLeftSonExtra;
    vertics->m_left->m_extra+=verticsExtra;
}
template<class T,class K,class E>
void RankAvlTree<T,K,E>::ExtraBalanceRR(node* vertics)
{
    E verticsExtra= vertics->m_extra;
    E verticsRightSonExtra= vertics->m_right->m_extra;
    if(vertics->m_right->m_left)
    {
        vertics->m_right->m_left->m_extra+=verticsRightSonExtra;
    }
    vertics->m_extra=-verticsRightSonExtra;
    vertics->m_right->m_extra+=verticsExtra;
}

template<class T,class K,class E>
template<class pred>
void RankAvlTree<T,K,E>::reset(pred &function){
    reset(m_root,function);
}

template<class T,class K,class E>
template<class pred>
void RankAvlTree<T,K,E>::reset(node *vertics, pred &function){
    if(!vertics){
        return;
    }
    inorderExecution(vertics->m_left, function);
    vertics->m_extra=E(0);
    function(vertics->m_data);
    inorderExecution(vertics->m_right, function);
}
#endif