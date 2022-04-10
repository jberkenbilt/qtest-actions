#include <iostream>
#include "a.hh"

void f()
{
    std::cout << BRANCH1 << " " << BRANCH2 << std::endl;
    throw Z();
}

void Y::f()
{
    std::cout << BRANCH1 << " " << BRANCH2 << std::endl;
}

Z::Z():
    std::runtime_error("Z")
{
}
