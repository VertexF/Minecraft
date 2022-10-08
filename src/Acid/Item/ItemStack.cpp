#include "ItemStack.h"

#include <algorithm>

namespace acid
{
    ItemStack::ItemStack(const Material& material, int amount) : 
        _material(&material), _numInStack(amount)
    {
    }

    int ItemStack::add(int amount)
    {
        _numInStack += amount;
        if (_numInStack > _material->maxStackSize) 
        {
            int leftOver = _numInStack - _material->maxStackSize;
            _numInStack = _material->maxStackSize;
            return leftOver;
        }
        else 
        {
            return 0;
        }
    }

    void ItemStack::remove() 
    {
        _numInStack--;
        if (_numInStack == 0) 
        {
            _material = &Material::NOTHING_BLOCK;
        }
    }

    int ItemStack::getNumInStack() const 
    {
        return _numInStack;
    }

    const Material& ItemStack::getMaterial() const 
    {
        return *_material;
    }
}