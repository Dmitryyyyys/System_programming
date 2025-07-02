#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <shlobj.h>
#include <direct.h>
#include <signal.h>

#define SERVICE_NAME  _T("DemoService")
#define DEFAULT_INTERVAL 60  

SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
SERVICE_STATUS g_ServiceStatus = { 0 };
HANDLE g_ServiceStopEvent = NULL;

TCHAR configFilePath[MAX_PATH] = _T("C:\\labs\\СП\\lab5\\lab5\\DemoService\\config.ini");
TCHAR sourceDir[MAX_PATH], backupDir[MAX_PATH], logDir[MAX_PATH];
DWORD copyInterval = DEFAULT_INTERVAL;
HANDLE hLogFile = NULL;

void CheckPath() {
    if (!configFilePath || _tcslen(configFilePath) == 0) {
        _tprintf(_T("Ошибка: не задан путь к конфигурационному файлу!\n"));
    }
}

void FormatTime(TCHAR* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    _stprintf_s(buffer, size, _T("%04d-%02d-%02d %02d-%02d-%02d"),
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec); 
}

void LogMessage(const TCHAR* message) {
    if (!hLogFile || hLogFile == INVALID_HANDLE_VALUE) return;

    TCHAR timeBuffer[64];
    FormatTime(timeBuffer, sizeof(timeBuffer) / sizeof(TCHAR));

    TCHAR fullMessage[1024];
    _stprintf_s(fullMessage, sizeof(fullMessage) / sizeof(TCHAR), _T("[%s] %s"), timeBuffer, message);

    DWORD written;
    WriteFile(hLogFile, fullMessage, (DWORD)_tcslen(fullMessage) * sizeof(TCHAR), &written, NULL);
    WriteFile(hLogFile, _T("\r\n"), 4, &written, NULL);
}

void LoadConfig() {
    GetPrivateProfileString(_T("Paths"), _T("SourceDir"), _T(""), sourceDir, MAX_PATH, configFilePath);
    GetPrivateProfileString(_T("Paths"), _T("BackupDir"), _T("C:\\Users\\37529\\AppData\\Roaming\\DemoService\\Logs"), backupDir, MAX_PATH, configFilePath);
    GetPrivateProfileString(_T("Paths"), _T("LogDir"), _T("C:\\Users\\37529\\AppData\\Roaming\\DemoService\\Reserved"), logDir, MAX_PATH, configFilePath);
    copyInterval = GetPrivateProfileInt(_T("Settings"), _T("Interval"), DEFAULT_INTERVAL, configFilePath);
}

void SetupLogFile() {
    _tmkdir(logDir);  

    TCHAR logFilePath[MAX_PATH], timeStr[64];
    FormatTime(timeStr, sizeof(timeStr) / sizeof(TCHAR));

    _stprintf_s(logFilePath, MAX_PATH, _T("%s\\%s-service.log"), logDir, timeStr);
    hLogFile = CreateFile(logFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hLogFile == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        _tprintf(_T("Ошибка открытия лог-файла (%s): %lu\n"), logFilePath, err);
    }
}

DWORD WINAPI ServiceWorkerThread(LPVOID lpParam) {
    TCHAR sourceFile[MAX_PATH];
    _stprintf_s(sourceFile, MAX_PATH, _T("%s\\test.txt"), sourceDir);
    while (WaitForSingleObject(g_ServiceStopEvent, copyInterval * 1000) == WAIT_TIMEOUT) {
        if (GetFileAttributes(sourceFile) == INVALID_FILE_ATTRIBUTES) {
            LogMessage(_T("Файл test.txt не найден в исходной директории."));
            continue;
        }
        TCHAR timeStr[64], backupFile[MAX_PATH];
        FormatTime(timeStr, sizeof(timeStr) / sizeof(TCHAR));
        _stprintf_s(backupFile, MAX_PATH, _T("%s\\test_backup_%s.txt"), backupDir, timeStr);
        if (CopyFile(sourceFile, backupFile, FALSE)) {
            LogMessage(_T("Файл успешно скопирован в резервную директорию."));

        }
        else
        {
            DWORD err = GetLastError();
            TCHAR errorMsg[256];
            _stprintf_s(errorMsg, 256, _T("Ошибка копирования  файла: %lu"), err);
            LogMessage(errorMsg);

        }
}
    LogMessage(_T("Сервис заверщает работу фонового потока."));
    return ERROR_SUCCESS;
}

void WINAPI ServiceCtrlHandler(DWORD CtrlCode) {
    switch (CtrlCode) {
    case SERVICE_CONTROL_STOP:
        if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING) break;
        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
        LogMessage(_T("Получена команда STOP. Завершение работы сервиса..."));
        SetEvent(g_ServiceStopEvent);
        break;

    case SERVICE_CONTROL_PAUSE:
        g_ServiceStatus.dwCurrentState = SERVICE_PAUSED;
        SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
        LogMessage(_T("Сервис приостановлен."));
        break;

    case SERVICE_CONTROL_CONTINUE:
        g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
        SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
        LogMessage(_T("Сервис продолжил выполнение."));
        break;

    case 128:  
        LogMessage(_T("Принята пользовательская команда 128 (тест)."));
        break;

    default:
        break;
    }
}

void WINAPI ServiceMain(DWORD argc, LPTSTR* argv) {
    g_StatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, ServiceCtrlHandler);
    if (!g_StatusHandle) return;

    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;
    g_ServiceStatus.dwWaitHint = 0;

    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);

    g_ServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!g_ServiceStopEvent) {
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
        return;
    }

    LoadConfig();
    SetupLogFile();
    LogMessage(_T("Сервис запущен. Загрузка конфигурации завершена."));

    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);

    LogMessage(_T("Сервис находится в состоянии RUNNING."));
    ServiceWorkerThread(NULL);

    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
    LogMessage(_T("Сервис остановлен."));
}

int _tmain(int argc, TCHAR* argv[]) {
    CheckPath();
    SERVICE_TABLE_ENTRY ServiceTable[] = {
        {(LPWSTR)SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain},
        {NULL, NULL}
    };
    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}
