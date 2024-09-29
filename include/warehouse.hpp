#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

class Warehouse {
public:
    Warehouse ();

    unsigned short GetInventoryCount () const;
    void           SetInventoryCount (unsigned short theInventoryCount);
private:
    unsigned short mInventoryCount;
};

#endif
