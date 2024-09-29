#include <distributor.hpp>

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
    for (size_t index = 0; index < mWarehouses.size (); ++index) {
        if (mWarehouses.at (index).GetInventoryCount () > mTargetInventoryCount) {
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
        mCurrentPackageCount += warehouse.GetInventoryCount () - mTargetInventoryCount;
        if (mCurrentPackageCount < 0)
            throw std::runtime_error ("mCurrentPackageCount should not be < 0");
        warehouse.SetInventoryCount (mTargetInventoryCount);
    }
}
