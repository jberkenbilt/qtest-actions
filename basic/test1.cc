[[deprecated("read the argument to emit_warning")]]
inline int emit_warning(char const*)
{
    return 0;
}
static auto w1 = emit_warning("message1");
static auto w2 = emit_warning("message2");

int main()
{
    return 0;
}
