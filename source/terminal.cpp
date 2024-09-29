#include <terminal.hpp>
#include <iostream>
#include <cstdio>
#include <unistd.h>

void terminal::ClearConsole ()
{
    std::cout << "\033[2J\033[1;1H";
}

void terminal::SetCursorPosition (int theRow, int theCol)
{
    std::cout << "\033[" << theRow << ";" << theCol << "H";
}

void terminal::GetCursorPosition (int & theRow, int & theCol)
{
    std::cout << "\033[6n";
    std::cout.flush();
    char buf [32];
    int bytesRead = read (STDIN_FILENO, buf, sizeof (buf) - 1);
    if (bytesRead > 0) {
        buf[bytesRead] = '\0';
        if (buf[0] == '\033' && buf[1] == '[') {
            sscanf(buf + 2, "%d;%d", &theRow, &theCol);
        }
    }
}