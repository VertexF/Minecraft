#ifndef NON_COPYABLE_HDR
#define NON_COPYABLE_HDR

namespace acid 
{
    struct NonCopyable
    {
        NonCopyable() = default;
        NonCopyable& operator=(const NonCopyable& str) = delete;
        NonCopyable(const NonCopyable& str) = delete;
    };
}

#endif // !NON_COPYABLE_HDR
