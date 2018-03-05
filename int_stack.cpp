////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include "int_stack.h"

// TODO: add necessary headers here
// #include <...

namespace xi {



// TODO: add method definitions here
    IntStack::IntStack(size_t sz) {
        _stack = new int[sz];
        _ssize = sz;
        _head = 1;
    }

    void IntStack::push(int el) {
        if (isFull())
            throw std::logic_error("The stack is full!");
        _stack[_head - 1] = el;
        _head++;
    }

    int IntStack::pop() {
        if (isEmpty())
            throw std::logic_error("Stack is empty!");
        _head--;
        return _stack[_head - 1];
    }

    void IntStack::clear() {
        for (int i = _head - 2; i >= 0; --i) {
            _stack[i] = 0;
        }
        _head = 1;
    }

    bool IntStack::isEmpty() const {
        return _head - 1 == 0;
    }

    int IntStack::top() {
        if (isEmpty()){
            throw std::logic_error("The stack is empty!");
        }
        return _stack[_head - 2];
    }

    bool IntStack::isFull() const {
        return _head - 1 >= _ssize;
    }

    IntStack::~IntStack() {
        _ssize = 0;
        _head = 0;
        delete[] _stack;
    }

} // namespace xi