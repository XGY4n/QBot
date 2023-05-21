#include"Pyreflex.h"

bool Botinit()
{
    if (!_Py_Reflex->testPythoninitialize()) {
        std::cout << "[WARNING]PYTHON TEST MABY NOT ALL PASS " << std::endl;
        return false;
    }
    std::cout << "[SUCCESS]PYTHON TEST ALL PASS " << std::endl;
    return true;
}