#ifndef ITEM_STACK_HDR
#define ITEM_STACK_HDR

#include "Material.h"

namespace acid 
{
    class ItemStack 
    {
    public:
        ItemStack(const Material& material, int amount);

        int add(int amount);
        void remove();

        int getNumInStack() const;
        const Material& getMaterial() const;
    private:
        const Material* _material;
        int _numInStack;
    };
}

#endif // !ITEM_STACK_HDR
