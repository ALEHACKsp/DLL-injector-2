#include "Misc.h"


int main() {
    DWORD test = find_process("notepad.exe");
    if (!test)
    {
        cout << "notepad not found";
        cin.get();
    }
    else {
        inject();
    }
}

