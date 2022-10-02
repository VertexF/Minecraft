#ifndef NON_MOVABLE_HDR
#define NON_MOVABLE_HDR

namespace acid 
{
    class NonMovable 
    {
    public:
        NonMovable(NonMovable&&) = delete;
        NonMovable& operator=(NonMovable&&) = delete;
    private:
        NonMovable() = default;
    };
}

#endif // !NON_MOVABLE_HDR
