#include <app.hpp>
#include <distributor.hpp>
#include <iostream>
#include <terminal.hpp>

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
        for (size_t index; index < theWarehouses; ++index) {
            std::cout << std::left << std::setw (20)
        }
        std::cout << "+ Zum hinzufügen eines neuen Warenhauses. - Zum Entfernen." << std::endl;
        std::cout << "Mit der Backspacetaste geht's zurück. Mit Enter wird eine Eingabe bestätigt." << std::endl;
    }
}

App::App () :
    mWarehouses ()
{
}

void App::Run ()
{
    PrintMenu ();
}

void App::Distribute ()
{
    Distributer distributer (mWarehouses);
    if (distributer.CalculateRoute ()) {
        distributer.DistributeInventory ();
    } else {
        terminal::SetCursorPosition (6, 1);
        std::cout << "Für eine Verteilung der Pakete muss die Anzahl glatt durch die Warenhäuser teilbar sein." << std::endl;
    }
}

void App::EditWarehouses ()
{
    terminal::ClearConsole ();
    terminal::SetCursorPosition (1, 1);
    while (true) {

    }
}

void App::PrintMenu ()
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
                }
                else if (characterPressed == 'B' && currentMenuIndex < 3) {//Arrow Down
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
            } else if (currentMenuIndex == 3)
                std::exit (0);
        }
    }
}