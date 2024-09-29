#include <warehouse.hpp>

Warehouse::Warehouse () :
    mInventoryCount (0)
{
}

unsigned short Warehouse::GetInventoryCount () const
{
    return mInventoryCount;
}

void Warehouse::SetInventoryCount (unsigned short theInventoryCount)
{
    mInventoryCount = theInventoryCount;
}


