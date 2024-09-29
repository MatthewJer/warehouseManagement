#include <termios.h>
#include <app.hpp>
#include <unistd.h>

namespace {
    void setRawMode(bool enable)
    {
        static struct termios oldt, newt;
        if (enable) {
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        }
        else {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        }
    }
}

int main()
{
    setRawMode(true);
    App app;
    app.Run();
    setRawMode(false);
    return 0;
}
