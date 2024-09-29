#ifndef TERMINAL_HPP
#define TERMINAL_HPP

namespace terminal {

    void ClearConsole      ();
    void GetCursorPosition (int & theRow, int & theCol);
    void SetCursorPosition (int theRow, int theCol);
};

#endif
