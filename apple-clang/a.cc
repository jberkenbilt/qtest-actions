#include <iostream>

#if defined _WIN32 || defined __CYGWIN__
# define QPDF_DLL__VISIBLE "v1"
# define QPDF_DLL__HIDDEN "v2"
#elif defined __GNUC__
# define QPDF_DLL__VISIBLE "v3"
# define QPDF_DLL__HIDDEN "v4"
#else
# define QPDF_DLL__VISIBLE "v5"
# define QPDF_DLL__HIDDEN "v6"
#endif

void f()
{
    std::cout << QPDF_DLL__VISIBLE << " " << QPDF_DLL__HIDDEN << std::endl;
}
