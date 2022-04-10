#include <iostream>
#include "a.hh"

void f()
{
    std::cout << BRANCH1 << " " << BRANCH2 << std::endl;
}

void Y::f()
{
    std::cout << BRANCH1 << " " << BRANCH2 << std::endl;
}
