////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <assert.h>
#include <stdexcept>
#include <cmath>


#include "int_stack.h"
#include "stack_machine.h"


using namespace std;

void testStack()
{
    xi::IntStack s;

    s.push(42);
    //int a = s.pop();
//    assert(s.top() == 42);            // EXPECT_EQ()
//    assert(s.pop() == 42);            // EXPECT_EQ()
    bool f = s.top() == 42;
    std::cout<<f;
    f = s.pop() == 42;
    std::cout<<f;
    // an exception should be thrown
    bool exc = false;
    try {
        s.pop();
    }
    catch(std::logic_error& /*e*/)
    {
        std::cout << "An expected exception on pop() operation is succesfully catched\n";
        exc = true;
    }
//    assert(exc);
    std::cout<<exc;

    // test for overflow
    for(int i = 0; i < xi::IntStack::STACK_SIZE; ++i)
        s.push(i);

    // next element cannot be added and, thus, en exception should be thrown
    exc = false;
    try {
        s.push(43);
    }
    catch(std::logic_error& /*e*/)
    {
        std::cout << "An expected exception on push() operation is succesfully catched\n";
        exc = true;
    }
//    assert(exc);
    std::cout<<exc;
    //int b = 0;
}

void testStackMachine()
{
    xi::StackMachine sm;
    xi::PlusOp plusop;
    sm.registerOperation('+', &plusop);
    xi::Ternary ternary;
    sm.registerOperation('?', &ternary);
    xi::Pow pow1;
    sm.registerOperation('^', &pow1);
    xi::Or orOp;
    sm.registerOperation('|', &orOp);

//    int res = sm.calculate("15 10 +");
//    int res = sm.calculate("7 8 10 + +");
//    int res = sm.calculate("2 3 1 1 2 5 ? + + +");
//    int res = sm.calculate("2 3 |");
//    int res = sm.calculate("3 2 ^ 5 + 10 2 4 ? +");
    int res = sm.calculate("17 3 ^ 24 | 0 2 7 ? + 3 + 6 1 ^ 5 7 4 ? + +");

    int r1 = sm.getStack().top();
    bool f = res == 4944;
    std::cout<<f;
    f = r1 == 4944;
    std::cout<<f;
//    assert(res == 25);
//    assert(r1 == 25);

}

int main()
{
    cout << "Hello, World!" << endl;

//    testStack();
    testStackMachine();
    return 0;
}