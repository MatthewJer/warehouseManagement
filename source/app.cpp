#include <app.hpp>
#include <distributor.hpp>
#include <iostream>
#include <terminal.hpp>
#include <iomanip>

namespace {
    void PrintMenuOptions ()
    {
        std::cout << " Warenhäuser verwalten." << std::endl;
        std::cout << " Waren verteilen." << std::endl;
        std::cout << " Beenden." << std::endl;
        std::cout << "Verwenden Sie die Pfeiltesten hoch und runter zum Navigieren. Enter zum bestätigen." << std::endl;
    }

    void PrintWarehouseOptions (std::vector <Warehouse> const & theWarehouses)
    {
        for (size_t index = 0; index < theWarehouses.size (); ++index) {
            std::cout << std::left << std::setw (20) << "Warenhaus " + std::to_string (index + 1)
                      << std::setw (20) << "Aktuell: " + std::to_string (theWarehouses.at (index).GetInventoryCount ())
                      << std::setw (20) << "Eingabe: " << std::endl; 
        }
        std::cout << "+ Zum hinzufügen eines neuen Warenhauses. - Zum Entfernen." << std::endl;
        std::cout << "Verwenden Sie die Pfeiltesten hoch und runter zum Navigieren." << std::endl;
        std::cout << "Mit der 'q' geht's zurück. Mit Enter wird eine Eingabe bestätigt." << std::endl;
    }

    bool IsNumber (char character)
    {
        return character >= '0' && character <= '9';
    }

    unsigned short StringToUnsignedShort (std::string const & theString)
    {
        unsigned long value = std::stoul (theString);
        if (value > std::numeric_limits <unsigned short>::max ()) {
            throw std::out_of_range ("Value exceeds unsigned short range");
        }
        return static_cast <unsigned short> (value);
    }
}

App::App () :
    mWarehouses ()
{
}

void App::Run ()
{
    HandleMenu ();
}

bool App::Distribute ()
{
    Distributer distributer (mWarehouses);
    bool canDistribute = distributer.CalculateRoute ();
    if (canDistribute) {
        terminal::ClearConsole ();
        distributer.DistributeInventory ();
    }
    return canDistribute;
}

void App::EditWarehouses ()
{
    terminal::ClearConsole ();
    terminal::SetCursorPosition (1, 1);
    PrintWarehouseOptions (mWarehouses);
    size_t currentWarehouse = mWarehouses.size () > 0 ? 1 : 0;
    constexpr int colPos = 50;
    if (currentWarehouse > 0)
        terminal::SetCursorPosition (currentWarehouse, colPos);
    std::string currentNumber;
    while (true) {
        char characterPressed = std::cin.get ();
        if (characterPressed == '\e') {
            characterPressed = std::cin.get ();
            if (characterPressed == '[') {
                characterPressed = std::cin.get ();
                if (characterPressed == 'A' && currentWarehouse > 1) { //Arrow up
                    terminal::SetCursorPosition (currentWarehouse, colPos);
                    std::cout << "                    ";
                    terminal::SetCursorPosition (currentWarehouse, colPos);
                    --currentWarehouse;
                    terminal::SetCursorPosition (currentWarehouse, colPos);
                    currentNumber = "";
                } else if (characterPressed == 'B' && currentWarehouse < mWarehouses.size ()) {
                    terminal::SetCursorPosition (currentWarehouse, colPos);
                    std::cout << "                    ";
                    terminal::SetCursorPosition (currentWarehouse, colPos);
                    ++currentWarehouse;
                    terminal::SetCursorPosition (currentWarehouse, colPos);
                    currentNumber = "";
                }
            }
        } else if (characterPressed == '+') {
            mWarehouses.emplace_back ();
            terminal::ClearConsole ();
            terminal::SetCursorPosition (1, 1);
            PrintWarehouseOptions (mWarehouses);
            currentWarehouse = mWarehouses.size () > 0 ? 1 : 0;
            terminal::SetCursorPosition (currentWarehouse, colPos);
        } else if (characterPressed == '-' && mWarehouses.size () > 0) {
            mWarehouses.erase (mWarehouses.begin () + currentWarehouse - 1);
            terminal::ClearConsole ();
            terminal::SetCursorPosition (1, 1);
            PrintWarehouseOptions (mWarehouses);
            currentWarehouse = mWarehouses.size () > 0 ? 1 : 0;
            terminal::SetCursorPosition (currentWarehouse, colPos);
        } else if (characterPressed == 'q') {
            return;
        } else if (IsNumber (characterPressed) && mWarehouses.size () > 0) {
            currentNumber += characterPressed;
            std::cout << characterPressed;
        } else if (characterPressed == '\x7f') { //Backspace
            int row = 0;
            int column = 0;
            terminal::GetCursorPosition (row, column);
            if (column <= colPos)
                continue;
            --column;
            terminal::SetCursorPosition (row, column);
            std::cout << " ";
            terminal::SetCursorPosition (row, column);
        } else if (characterPressed == '\n' && currentNumber.size () > 0) {
            mWarehouses.at (currentWarehouse - 1).SetInventoryCount (StringToUnsignedShort (currentNumber));
            terminal::SetCursorPosition (currentWarehouse, 30);
            std::cout << currentNumber << "        ";
            currentNumber = "";
            terminal::SetCursorPosition (currentWarehouse, colPos);
            std::cout << "                    ";
            terminal::SetCursorPosition (currentWarehouse, colPos);
        }
    }
}

void App::HandleMenu ()
{
    terminal::ClearConsole ();
    PrintMenuOptions ();
    size_t currentMenuIndex = 1;
    while (true) {
        terminal::SetCursorPosition (currentMenuIndex, 1);
        std::cout << ">";
        terminal::SetCursorPosition (currentMenuIndex, 1);
        char characterPressed = std::cin.get ();
        if (characterPressed == '\e') {
            characterPressed = std::cin.get ();
            if (characterPressed == '[') {
                characterPressed = std::cin.get ();
                if (characterPressed == 'A' && currentMenuIndex > 1) { //Arrow up
                    terminal::SetCursorPosition (currentMenuIndex, 1);
                    std::cout << " ";
                    --currentMenuIndex;
                } else if (characterPressed == 'B' && currentMenuIndex < 3) {//Arrow Down
                    terminal::SetCursorPosition (currentMenuIndex, 1);
                    std::cout << " ";
                    ++currentMenuIndex;
                }
            }
        } else if (characterPressed == '\n') {
            if (currentMenuIndex == 1) {
                EditWarehouses ();
                terminal::ClearConsole ();
                PrintMenuOptions ();
            } else if (currentMenuIndex == 2) {
                bool couldDistribute = Distribute ();
                terminal::ClearConsole ();
                PrintMenuOptions ();
                if (! couldDistribute) {
                    std::cout << "Pakete konnten nicht verteilt werden,"
                              << " da die Anzahl nicht glatt durch die Warenhäuser Teilbar ist" << std::endl;
                }
            } else if (currentMenuIndex == 3)
                std::exit (0);
        }
    }
}