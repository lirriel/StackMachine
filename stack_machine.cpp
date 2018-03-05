////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include "math.h"
#include "stack_machine.h"

// TODO: add necessary headers here
// #include <...


namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need some free function, add their definitions here

//    class Thernar: public IOperation{
//    public:
//        // IOperation interface overriding
//        // We explicitly use virtual keyword to point out the virtual nature of the methods
//
//        /** If a given operator symb is not '+", an exception is thrown*/
//        virtual int operation(char op, int a, int b, int c) override;
//        virtual Arity getArity() const override;
//    };

    IOperation::Arity Ternary::getArity() const { return arTre;}

    int Ternary::operation(char op, int a, int b, int c) {
        if (op != '?')
            throw std::logic_error("Operations other than Thernar (?) are not supported!");

        if (a != 0)
            return b;
        return c;
    }

//    class Pow: public IOperation{
//    public:
//        // IOperation interface overriding
//        // We explicitly use virtual keyword to point out the virtual nature of the methods
//
//        /** If a given operator symb is not '^", an exception is thrown*/
//        virtual int operation(char op, int a, int b, int c) override;
//        virtual Arity getArity() const override;
//    };

    IOperation::Arity Pow::getArity() const { return arDue;}

    int Pow::operation(char op, int a, int b, int c) {
        if (op != '^')
            throw std::logic_error("Operations other than Power (^) are not supported!");

        return round(pow(a, b));
    }

//    class Or: public IOperation{
//    public:
//        // IOperation interface overriding
//        // We explicitly use virtual keyword to point out the virtual nature of the methods
//
//        /** If a given operator symb is not '|", an exception is thrown*/
//        virtual int operation(char op, int a, int b, int c) override;
//        virtual Arity getArity() const override;
//    };

    IOperation::Arity Or::getArity() const { return arDue;}

    int Or::operation(char op, int a, int b, int c) {
        if (op != '|')
            throw std::logic_error("Operations other than Or (|) are not supported!");

        return a | b;
    }

//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int c)
{
    if(op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class StackMachine
//==============================================================================

// TODO: implement methods of the StackMachine class here

    IOperation* StackMachine::getOperation(char symb) {
        for (SymbolToOperMapConstIter it = _opers.begin(); it != _opers.end(); ++it)
        {
            if ((*it).first == symb){
                return (*it).second;
            }
        }
        return nullptr;
    }

    bool isNumber(std::string line){
        char* p;
        strtol(line.c_str(), &p, 10);
        return (*p == 0);
    }

    void StackMachine::registerOperation(char symb, IOperation *oper) {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if(it != _opers.end())
            throw std::logic_error("The operation is already exist!");
        _opers[symb] = oper;
    }

    int StackMachine::calculate(const std::string &expr, bool clearStack) {
        if (clearStack){
            _s.clear();
        }
        std::string _expr = expr + " ";
        std::string temp = "";
        for (int i = 0; i < _expr.size(); ++i) {
            if (_expr[i] != ' '){
                temp += _expr[i];
            }
            else{
                if (isNumber(temp)){
                    _s.push(atoi(temp.c_str()));
                }
                else
                {
                    char ch = temp[0];
                    IOperation* operation = getOperation(ch);
                    if (operation == nullptr)
                        continue;
                    if (operation->getArity() == operation->arUno){
                        _s.push(operation->operation(ch, _s.pop()));
                    }
                    else if (operation->getArity() == operation->arDue){
                        _s.push(operation->operation(ch, _s.pop(), _s.pop()));
                    }
                    else{
                        _s.push(operation->operation(ch, _s.pop(), _s.pop(), _s.pop()));
                    }
                }
                temp = "";
            }
        }
        return _s.top();
    }
} // namespace xi
