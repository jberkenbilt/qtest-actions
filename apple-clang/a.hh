#if defined _WIN32 || defined __CYGWIN__
# define QPDF_DLL__VISIBLE __declspec(dllexport)
# define QPDF_DLL__HIDDEN
# define BRANCH1 "1"
#elif defined __GNUC__
# define QPDF_DLL__VISIBLE __attribute__((visibility("default")))
# define QPDF_DLL__HIDDEN __attribute__((visibility("hidden")))
# define BRANCH1 "2"
#else
# define QPDF_DLL__VISIBLE
# define QPDF_DLL__HIDDEN
# define BRANCH1 "3"
#endif

#define QPDF_DLL QPDF_DLL__VISIBLE
#if defined _WIN32 || defined __CYGWIN__
# define QPDF_DLL_PRIVATE
# define QPDF_DLL_CLASS
# define BRANCH2 "4"
#else
# define QPDF_DLL_PRIVATE QPDF_DLL__HIDDEN
# define QPDF_DLL_CLASS QPDF_DLL__VISIBLE
# define BRANCH2 "5"
#endif

QPDF_DLL
void f();

class QPDF_DLL_CLASS X
{
  public:
    QPDF_DLL
    virtual ~X() = default;

    QPDF_DLL
    virtual void f() = 0;
};

class QPDF_DLL_CLASS Y: public X
{
  public:
    QPDF_DLL
    virtual ~Y() = default;

    QPDF_DLL
    void f();
};
