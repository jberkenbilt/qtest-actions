[[deprecated("warning")]]
inline int f()
{
    return 12;
}
static auto x = f();

int main()
{
    return 0;
}
