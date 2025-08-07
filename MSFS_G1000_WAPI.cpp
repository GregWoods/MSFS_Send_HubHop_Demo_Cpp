#include <iostream>
#include <conio.h>
#include "WASMIF.h"
#include <thread>
#include <chrono>


class WASMIFGuard {
    WASMIF* wasmPtr_;
public:
    explicit WASMIFGuard(WASMIF* ptr) : wasmPtr_(ptr) {}
    ~WASMIFGuard() {
        if (wasmPtr_) wasmPtr_->end();
    }
};


int main()
{
    std::cout << "Press 'z' to press the G1000 PFD Soft Button 2\nPress 'q' to quit.";

    WASMIF* wasmPtr = WASMIF::GetInstance();
    WASMIFGuard guard(wasmPtr); // Ensures end() is called

    wasmPtr->setSimConfigConnection(SIMCONNECT_OPEN_CONFIGINDEX_LOCAL);
    wasmPtr->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    const char* calcCode = "(>H:AS1000_PFD_SOFTKEYS_2)";
    char ccode[MAX_CALC_CODE_SIZE] = { 0 };
    strncpy_s(ccode, sizeof(ccode), calcCode, _TRUNCATE);

    while (true)
    {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 'z') {
                wasmPtr->executeCalclatorCode(ccode);
            }
            else if (ch == 'q') {
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
