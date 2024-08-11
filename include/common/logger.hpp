#pragma once

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger
{
  public:
    Logger(LogLevel level = LogLevel::INFO) : logLevel(level), logToConsole(true), logToFile(false)
    {
        moduleName = "";
    }

    void setLogLevel(LogLevel level)
    {
        logLevel = level;
    }

    void setModuleName(std::string name)
    {
        moduleName = name + ": ";
    }

    void setLogToConsole(bool enable)
    {
        logToConsole = enable;
    }

    void setLogToFile(const std::string &filename, bool enable)
    {
        logToFile = enable;
        if (enable)
        {
            logFile.open(filename, std::ios::out | std::ios::app);
        }
        else if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void log(LogLevel level, const std::string &message)
    {
        if (level >= logLevel)
        {
            std::string logMessage = formatLogMessage(level, message);
            std::lock_guard<std::mutex> lock(logMutex);
            if (logToConsole)
            {
                std::cout << logMessage << std::endl;
            }
            if (logToFile && logFile.is_open())
            {
                logFile << logMessage << std::endl;
                logFile.flush(); // TODO: may want to buffer this and flush periodically for better
                                 // performance
            }
        }
    }

    void debug(const std::string &message)
    {
        log(LogLevel::DEBUG, message);
    }

    void info(const std::string &message)
    {
        log(LogLevel::INFO, message);
    }

    void warn(const std::string &message)
    {
        log(LogLevel::WARN, message);
    }

    void error(const std::string &message)
    {
        log(LogLevel::ERROR, message);
    }

  private:
    LogLevel logLevel;
    std::string moduleName;
    bool logToConsole;
    bool logToFile;
    std::ofstream logFile;
    std::mutex logMutex;

    std::string formatLogMessage(LogLevel level, const std::string &message)
    {
        std::ostringstream oss;
        oss << "[" << getCurrentTime() << "] [" << logLevelToString(level) << "] " << moduleName
            << message;
        return oss.str();
    }

    std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return oss.str();
    }

    std::string logLevelToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }
};
