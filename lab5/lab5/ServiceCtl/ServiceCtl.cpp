#include <windows.h>
#include <iostream>
#include <string>

void PrintUsage() {
    std::cout << "Usage: ServiceCtl <ServiceName> <Operation> [Additional Parameters]\n";
    std::cout << "Operations:\n";
    std::cout << "  install <PathToExe> - Install the service\n";
    std::cout << "  start               - Start the service\n";
    std::cout << "  stop                - Stop the service\n";
    std::cout << "  pause               - Pause the service\n";
    std::cout << "  continue            - Resume the service\n";
    std::cout << "  info                - Display service status\n";
    std::cout << "  test                - Send custom test control code\n";
    std::cout << "  delete              - Delete the service\n";
}

bool OpenServiceHandle(const std::string& serviceName, DWORD access, SC_HANDLE& hSCManager, SC_HANDLE& hService) {
    hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (!hSCManager) return false;

    hService = OpenServiceA(hSCManager, serviceName.c_str(), access);
    return (hService != nullptr);
}

bool ControlServiceCustom(const std::string& serviceName, DWORD controlCode, const std::string& actionName) {
    SC_HANDLE hSCManager, hService;
    if (!OpenServiceHandle(serviceName, SERVICE_USER_DEFINED_CONTROL | SERVICE_PAUSE_CONTINUE | SERVICE_QUERY_STATUS | SERVICE_STOP, hSCManager, hService)) {
        std::cerr << "Failed to open service for control: " << serviceName << "\n";
        return false;
    }

    SERVICE_STATUS status;
    if (ControlService(hService, controlCode, &status)) {
        std::cout << "Service '" << serviceName << "' " << actionName << " successfully.\n";
    }
    else {
        std::cerr << "Failed to " << actionName << " service. Error: " << GetLastError() << "\n";
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return true;
}

bool DisplayServiceInfo(const std::string& serviceName) {
    SC_HANDLE hSCManager, hService;
    if (!OpenServiceHandle(serviceName, SERVICE_QUERY_STATUS, hSCManager, hService)) {
        std::cerr << "Failed to query service: " << serviceName << "\n";
        return false;
    }

    SERVICE_STATUS_PROCESS status;
    DWORD bytesNeeded;
    if (QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&status, sizeof(status), &bytesNeeded)) {
        std::cout << "Service '" << serviceName << "' status:\n";
        std::cout << "  Current State: ";
        switch (status.dwCurrentState) {
        case SERVICE_STOPPED:        std::cout << "Stopped"; break;
        case SERVICE_START_PENDING:  std::cout << "Start Pending"; break;
        case SERVICE_STOP_PENDING:   std::cout << "Stop Pending"; break;
        case SERVICE_RUNNING:        std::cout << "Running"; break;
        case SERVICE_CONTINUE_PENDING: std::cout << "Continue Pending"; break;
        case SERVICE_PAUSE_PENDING:  std::cout << "Pause Pending"; break;
        case SERVICE_PAUSED:         std::cout << "Paused"; break;
        default:                     std::cout << "Unknown"; break;
        }
        std::cout << "\n";
    }
    else {
        std::cerr << "Failed to get service status. Error: " << GetLastError() << "\n";
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return true;
}

bool StartServiceByName(const std::string& serviceName) {
    SC_HANDLE hSCManager, hService;
    if (!OpenServiceHandle(serviceName, SERVICE_START, hSCManager, hService)) {
        std::cerr << "Failed to open service: " << serviceName << "\n";
        return false;
    }

    BOOL result = StartServiceA(hService, 0, nullptr);
    if (!result) std::cerr << "Failed to start service. Error: " << GetLastError() << "\n";
    else std::cout << "Service started.\n";

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return result;
}

bool StopServiceByName(const std::string& serviceName) {
    return ControlServiceCustom(serviceName, SERVICE_CONTROL_STOP, "stopped");
}

bool PauseServiceByName(const std::string& serviceName) {
    return ControlServiceCustom(serviceName, SERVICE_CONTROL_PAUSE, "paused");
}

bool ContinueServiceByName(const std::string& serviceName) {
    return ControlServiceCustom(serviceName, SERVICE_CONTROL_CONTINUE, "resumed");
}

bool SendTestSignal(const std::string& serviceName) {
    return ControlServiceCustom(serviceName, 128, "sent test signal to");
}

bool DeleteServiceByName(const std::string& serviceName) {
    SC_HANDLE hSCManager, hService;
    if (!OpenServiceHandle(serviceName, DELETE, hSCManager, hService)) {
        std::cerr << "Failed to open service for deletion: " << serviceName << "\n";
        return false;
    }

    BOOL result = DeleteService(hService);
    if (!result) std::cerr << "Failed to delete service. Error: " << GetLastError() << "\n";
    else std::cout << "Service deleted.\n";

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return result;
}

bool InstallService(const std::string& serviceName, const std::string& exePath) {
    SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE);
    if (!hSCManager) return false;

    SC_HANDLE hService = CreateServiceA(
        hSCManager,
        serviceName.c_str(),
        serviceName.c_str(),
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_DEMAND_START,
        SERVICE_ERROR_NORMAL,
        exePath.c_str(),
        nullptr, nullptr, nullptr, nullptr, nullptr
    );

    if (!hService) {
        std::cerr << "Failed to install service. Error: " << GetLastError() << "\n";
        CloseServiceHandle(hSCManager);
        return false;
    }

    std::cout << "Service installed successfully.\n";
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        PrintUsage();
        return 1;
    }

    std::string serviceName = argv[1];
    std::string command = argv[2];

    if (command == "install") {
        if (argc < 4) {
            std::cerr << "Missing path for service.\n";
            return 1;
        }
        return InstallService(serviceName, argv[3]) ? 0 : 1;
    }
    else if (command == "start") {
        return StartServiceByName(serviceName) ? 0 : 1;
    }
    else if (command == "stop") {
        return StopServiceByName(serviceName) ? 0 : 1;
    }
    else if (command == "pause") {
        return PauseServiceByName(serviceName) ? 0 : 1;
    }
    else if (command == "continue") {
        return ContinueServiceByName(serviceName) ? 0 : 1;
    }
    else if (command == "info") {
        return DisplayServiceInfo(serviceName) ? 0 : 1;
    }
    else if (command == "test") {
        return SendTestSignal(serviceName) ? 0 : 1;
    }
    else if (command == "delete") {
        return DeleteServiceByName(serviceName) ? 0 : 1;
    }
    else {
        std::cerr << "Unknown command: " << command << "\n";
        PrintUsage();
        return 1;
    }
}
