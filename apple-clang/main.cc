#include "a.hh"
#include <iostream>

int main()
{
    f();
    Y x;
    X* xp = &x;
    xp->f();
    std::cout << (dynamic_cast<Y*>(xp) != nullptr) << std::endl;
    return 0;
}
