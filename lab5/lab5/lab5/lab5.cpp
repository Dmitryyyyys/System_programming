#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>
#include <csignal>
#include <map>

namespace fs = std::filesystem;

bool reloadConfig = false;
std::string serviceName = "FileBackupService";

struct Config {
    std::string sourceDir;
    std::string destDir;
    std::string logDir;
    int intervalSec;
};

Config config;
std::ofstream logFile;

std::string currentDateTime() {
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    return std::string(buf);
}

void writeLog(const std::string& message) {
    logFile << currentDateTime() << " - " << message << std::endl;
}

bool loadConfig(const std::string& path, Config& cfg) {
    std::ifstream infile(path);
    if (!infile.is_open()) return false;

    std::map<std::string, std::string> params;
    std::string line;
    while (std::getline(infile, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            params[key] = value;
        }
    }
    cfg.sourceDir = params["sourceDir"];
    cfg.destDir = params["destDir"];
    cfg.logDir = params["logDir"];
    cfg.intervalSec = std::stoi(params["intervalSec"]);

    return true;
}

void signalHandler(int signal) {
    if (signal == SIGINT) {
        reloadConfig = true;
    }
}


void setupLogFile(const std::string& logDir) {
    if (!fs::exists(logDir)) {
        if (fs::create_directories(logDir)) {
            std::cout << "Успех! " << serviceName << " создал каталог " << logDir << std::endl;
        }
        else {
            std::cerr << "Попытка выполнения операции сервисом провалена! Не удалось создать каталог логов!" << std::endl;
            exit(1);
        }
    }
    else {
        std::cout << "Успех! " << serviceName << " обнаружил каталог " << logDir << std::endl;
    }
    std::string logPath = logDir + "/" + currentDateTime() + "-service.log";
    logFile.open(logPath, std::ios::out);
    if (!logFile.is_open()) {
        std::cerr << "Попытка выполнения операции сервисом провалена! Не удалось открыть файл лога!" << std::endl;
        exit(1);
    }
}

void copyFiles(const std::string& source, const std::string& dest) {
    for (const auto& entry : fs::directory_iterator(source)) {
        fs::copy(entry, dest / entry.path().filename(), fs::copy_options::overwrite_existing);
    }
    writeLog("Успех! Сервис " + serviceName + " успешно создал резервную копию файлов!");
}

int main() {
    signal(SIGINT, signalHandler);

    if (!loadConfig("config.txt", config)) {
        std::cerr << "Попытка выполнения операции сервисом провалена! Не удалось загрузить конфигурацию!" << std::endl;
        return 1;
    }

    setupLogFile(config.logDir);

    writeLog("Успех! Сервис " + serviceName + " запущен с параметрами " + config.sourceDir + ", " + config.destDir + ", " + config.logDir);

    if (!fs::exists(config.sourceDir)) {
        writeLog("Попытка выполнения операции сервисом провалена! Исходный каталог не существует!");
        return 1;
    }

    if (!fs::exists(config.destDir)) {
        if (fs::create_directories(config.destDir)) {
            writeLog("Успех! " + serviceName + " создал каталог " + config.destDir);
        }
        else {
            writeLog("Попытка выполнения операции сервисом провалена! Не удалось создать каталог назначения!");
            return 1;
        }
    }
    else {
        writeLog("Успех! " + serviceName + " обнаружил каталог " + config.destDir);
    }

    std::string state = "Ожидание";
    while (true) {
        if (reloadConfig) {
            Config newConfig;
            if (loadConfig("config.txt", newConfig)) {
                writeLog("Успех! Сервис " + serviceName + " сменил состояние с " + state + " на Обновление конфигурации");
                config = newConfig;
                writeLog("Успех! Сервис " + serviceName + " сменил состояние с Обновление конфигурации на " + state);
            }
            reloadConfig = false;
        }

        copyFiles(config.sourceDir, config.destDir);
        std::this_thread::sleep_for(std::chrono::seconds(config.intervalSec));
    }

    return 0;
}
