#ifndef APP_HPP
#define APP_HPP

#include <warehouse.hpp>
#include <vector>

class App {
public:
    App ();

    void Run ();
private:
    void Distribute      ();
    void EditWarehouses  ();
    void PrintMenu       ();
    
    std::vector <Warehouse> mWarehouses;
};

#endif
