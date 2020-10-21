#include <iostream>

template <class T>
void realmain(int argc, T* argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::cout << argv[i] << std::endl;
    }
}

#ifdef WINDOWS_WMAIN

extern "C"
int wmain(int argc, wchar_t* argv[])
{
    realmain(argc, argv);
    return 0;
}

#else

int main(int argc, char* argv[])
{
    realmain(argc, argv);
    return 0;
}

#endif
