#ifndef AVL_EXEPTIONS_H
#define AVL_EXEPTIONS_H

#include <exception>

class Exception:public std::exception{};

class ElementExists : public Exception {};

class ElementDoesntExist : public Exception {};

class badAlloc : public Exception {};

class invalidInput : public Exception {};

class nullArg : public Exception {};

#endif