#ifndef DISTRIBUTER_HPP
#define DISTRIBUTER_HPP

#include <vector>
#include <warehouse.hpp>

class Distributer {
public:
    Distributer (std::vector <Warehouse> & theWarehouses);

    bool CalculateRoute      ();
    void DistributeInventory ();
private:
    std::vector <Warehouse> & mWarehouses;
    int                       mCurrentPackageCount;
    std::vector <int>         mWarehouseRouteOrder;
    unsigned short            mTargetInventoryCount;
};

#endif
