#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    enum Level { INFO, WARNING, ERROR };

    static void log(Level level, const std::string& msg) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::string levelStr;
        switch (level) {
            case INFO: levelStr = "[INFO] "; break;
            case WARNING: levelStr = "[WARN] "; break;
            case ERROR: levelStr = "[ERROR] "; break;
        }

        std::cout << timestamp(time) << " " << levelStr << msg << std::endl;
    }

private:
    static std::string timestamp(std::time_t t) {
        std::stringstream ss;
        ss << "[" << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << "]";
        return ss.str();
    }
};
