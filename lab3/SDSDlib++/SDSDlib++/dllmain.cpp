// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <windows.h>
#include<fstream>
#define LOG_PATH "C:/labs/СП/lab3/log.txt"
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
    case DLL_THREAD_ATTACH:
        LogEvent("Подключен новый поток.");
    case DLL_THREAD_DETACH:
        LogEvent("Поток завершил работу.");
    case DLL_PROCESS_DETACH:
        LogEvent("DLL отключена от процесса.");
        break;
    }
    return TRUE;
}

