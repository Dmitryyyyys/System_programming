#include "pch.h"
#include <fstream>
#define LOG_PATH "SDSDlib.log"

void LogEvent(const char* message) {
    std::ofstream logFile(LOG_PATH, std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        LogEvent("DLL подключена к процессу.");
        break;
    case DLL_THREAD_ATTACH:
        LogEvent("Подключен новый поток.");
        break;
    case DLL_THREAD_DETACH:
        LogEvent("Поток завершил работу.");
    case DLL_PROCESS_DETACH:
        LogEvent("Поток завершил работу.");
        break;
    }
    return TRUE;
}

