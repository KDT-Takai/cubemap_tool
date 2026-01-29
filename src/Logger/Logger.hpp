#pragma once
#include <iostream>
#include <string>
#include <mutex>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    // シングルトン風で簡単に呼べる
    static void log(LogLevel level, const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);

        switch (level) {
        case LogLevel::Info:
            std::cout << "[Info] ";
            break;
        case LogLevel::Warning:
            std::cout << "[Warning] ";
            break;
        case LogLevel::Error:
            std::cerr << "[Error] ";
            break;
        }
        std::cout << msg << std::endl;
    }

    static void info(const std::string& msg) { log(LogLevel::Info, msg); }
    static void warn(const std::string& msg) { log(LogLevel::Warning, msg); }
    static void error(const std::string& msg) { log(LogLevel::Error, msg); }

private:
    static inline std::mutex mutex_;
};
