#include <locale>
#include <sstream>
#include <iostream>

int main()
{
    try
    {
        std::locale::global(std::locale("en_US.UTF-8"));
    }
    catch (std::runtime_error&)
    {
        try
        {
            std::locale::global(std::locale(""));
        }
        catch (std::runtime_error& e)
        {
            // Ignore this error on Windows without MSVC. We get
            // enough test coverage on other platforms, and mingw
            // seems to have limited locale support (as of
            // 2020-10).
#if ! defined(_WIN32) || defined(_MSC_VER)
            throw e;
#endif
        }
    }
    std::ostringstream buf;
    buf << 123456;
    std::cout << buf.str() << std::endl;
    return 0;
}
