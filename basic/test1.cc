#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <ctime>

#ifdef _WIN32
# include <windows.h>
#endif

static void make_timestamp()
{
#ifdef _WIN32
    SYSTEMTIME ltime;
    GetLocalTime(&ltime);

    std::cout << ltime.wYear << "/"
              << ltime.wMonth << "/"
              << ltime.wDay << "/"
              << ltime.wHour << "/"
              << ltime.wMinute << "/"
              << ltime.wSecond << "/";
    TIME_ZONE_INFORMATION tzinfo;
    GetTimeZoneInformation(&tzinfo);

    int tz_delta = static_cast<int>(tzinfo.Bias);
#else
    struct tm ltime;
    time_t now = time(0);
    tzset();
    localtime_r(&now, &ltime);
    std::cout << ltime.tm_year + 1900 << "/"
              << ltime.tm_mon + 1 << "/"
              << ltime.tm_mday << "/"
              << ltime.tm_hour << "/"
              << ltime.tm_min << "/"
              << ltime.tm_sec << "/";

    // timezone is seconds before UTC; covert to minutes before UTC
    int tz_delta = static_cast<int>(timezone / 60);
#endif
    std::string tz_offset;
    int tz_h = 0;
    int tz_m = 0;
    int t = tz_delta;
    if (t == 0)
    {
        tz_offset = "Z";
    }
    else
    {
        if (t < 0)
        {
            t = -t;
            tz_offset += "+";
        }
        else
        {
            tz_offset += "-";
        }
        tz_m = t % 60;
        tz_h = t / 60;
    }
    std::cout << tz_offset
              << tz_h << "'" << tz_m << "'"
              << " (tz_delta = " << tz_delta << ")"
              << std::endl;
}


template <class T>
void realmain(int argc, T* argv[])
{
    std::regex pdf_date("^D:([0-9]{4})([0-9]{2})([0-9]{2})"
                        "([0-9]{2})([0-9]{2})([0-9]{2})"
                        "(?:(Z)|([\\+\\-])([0-9]{2})'([0-9]{2})')$");
    std::vector<std::string> tests = {
        "D:20210207161528-05'00'",
        "D:20210207211528Z",
        "zD:20210207211528Zx",
    };

    for (auto const& str: tests)
    {
        std::smatch m;
        if (std::regex_match(str, m, pdf_date))
        {
            std::cout << str << ": match" << std::endl;
            for (auto const& i: m)
            {
                std::cout << "-> " << i << std::endl;
            }
        }
        else
        {
            std::cout << str << ": no match" << std::endl;
        }
    }

    std::cout << "---- timestamp ----" << std::endl;
    make_timestamp();
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
