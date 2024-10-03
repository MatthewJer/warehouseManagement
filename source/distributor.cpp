#include <distributor.hpp>
#include <cmath>
#include <iostream>
#include <ranges>

Distributer::Distributer (std::vector <Warehouse> & theWarehouses) :
    mWarehouses           (theWarehouses),
    mCurrentPackageCount  (0),
    mWarehouseRouteOrder  (),
    mTargetInventoryCount (0)
{
}

bool Distributer::CalculateRoute ()
{
    unsigned long sum = 0;
    for (auto & warehouse : mWarehouses) {
        sum += warehouse.GetInventoryCount ();
    }
    if (sum % mWarehouses.size () != 0) {
        return false;
    }
    mTargetInventoryCount = sum / mWarehouses.size ();
    for (auto [index, warehouse] : mWarehouses | std::ranges::views::enumerate) {
        if (warehouse.GetInventoryCount () > mTargetInventoryCount) {
            mWarehouseRouteOrder.insert (mWarehouseRouteOrder.begin (), index);
        } else {
            mWarehouseRouteOrder.push_back (index);
        }
    }
    return true;
}

void Distributer::DistributeInventory ()
{
    for (size_t index : mWarehouseRouteOrder) {
        auto & warehouse = mWarehouses.at (index);
        int packagesFromTo = warehouse.GetInventoryCount () - mTargetInventoryCount;
        mCurrentPackageCount += packagesFromTo;
        if (mCurrentPackageCount < 0)
            throw std::runtime_error ("mCurrentPackageCount should not be < 0");
        if (packagesFromTo > 0) {
            std::cout << "Nehme " << packagesFromTo << " aus dem Warenhaus " << index + 1 << "."
            << " Habe " << mCurrentPackageCount << " Pakete." << std::endl;
        } else {
            std::cout << "Lege " << std::abs (packagesFromTo) << " in Warenhaus " << index + 1 << " ab."
            << " Habe " << mCurrentPackageCount << " Pakete." << std::endl;
        }
        
        
        warehouse.SetInventoryCount (mTargetInventoryCount);
    }
    std::cout << "Drücken Sie eine beliebige Taste, um zum Menü zurückzukehren." << std::endl;
    std::cin.get ();
}
