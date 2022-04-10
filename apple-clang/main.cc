#include "a.hh"
#include <iostream>

int main()
{
    try {
        f();
    } catch(Z& e) {
        std::cout << "caught exception: " << e.what() << std::endl;
    }
    Y x;
    X* xp = &x;
    xp->f();
    std::cout << (dynamic_cast<Y*>(xp) != nullptr) << std::endl;
    return 0;
}
