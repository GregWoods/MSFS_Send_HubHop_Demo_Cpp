// MSFS_G1000_WAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <map>
#include <conio.h>
#include "WASMIF.h"

int main()
{
     std::cout << "Press 'z' to presss the G1000 PFD Soft Button 2\nPress 'q' to quit.";
     /*
     ?? where is WASMClient.ini?? Supposed to be in the same directory as the executable
     if it doesn't exist, these variables are set in default.cpp:

     m_logLevel = DEFAULT_LOG_LEVEL;
     m_lvarUpdateFrequency = DEFAULT_LVAR_UPDATE_FREQ;
     m_simConnectConnection = SIMCONNECT_OPEN_CONFIGINDEX_LOCAL;

     from SimConnect SDK:
     static const DWORD SIMCONNECT_OPEN_CONFIGINDEX_LOCAL   = -1;   // ignore SimConnect.cfg settings, and force local connection

     */
     WASMIF* wasmPtr = WASMIF::GetInstance();

     wasmPtr->setSimConfigConnection(SIMCONNECT_OPEN_CONFIGINDEX_LOCAL);
     //wasmPtr->setLvarUpdateFrequency(lvarUpdateFrequency)
     wasmPtr->start();

     //There is probably a callback way to do this, but for now we will just wait
     Sleep(1000);     //or the executeCalculatorCode will silently fail

     //wrap this in a loop to capture keyboard input
     const char* calcCode = "(>H:AS1000_PFD_SOFTKEYS_2)";
     char ccode[1024] = { 0 }; // Pad to 1024 bytes, zero-initialized
     strncpy_s(ccode, sizeof(ccode), calcCode, _TRUNCATE); // Safe copy, truncates if necessary

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
         Sleep(10);
     }

     wasmPtr->end();
}
