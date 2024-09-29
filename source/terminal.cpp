#include <terminal.hpp>
#include <iostream>

void terminal::ClearConsole ()
{
    std::cout << "\033[2J\033[1;1H";
}

void terminal::SetCursorPosition (int theRow, int theCol)
{
    std::cout << "\033[" << theRow << ";" << theCol << "H";
}
