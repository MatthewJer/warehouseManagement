#ifndef APP_HPP
#define APP_HPP

#include <warehouse.hpp>
#include <vector>

class App {
public:
    App ();

    void Run            ();
private:
    bool Distribute     ();
    void EditWarehouses ();
    void HandleMenu     ();
    
    std::vector <Warehouse> mWarehouses;
};

#endif
