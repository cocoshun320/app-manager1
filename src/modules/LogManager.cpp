#include "LogManager.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>

LogManager& LogManager::instance()
{
    static LogManager instance;
    return instance;
}

LogManager::LogManager()
    : m_logFilePath("app_manager.log")
{
    // 打开日志文件
    m_logFile.open(m_logFilePath, std::ios::out | std::ios::app);
    if (!m_logFile.is_open()) {
        std::cerr << "Failed to open log file: " << m_logFilePath << std::endl;
    }
}

LogManager::~LogManager()
{
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void LogManager::log(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::string formattedMessage = formatMessage(level, message);

    // 输出到控制台
    std::cout << formattedMessage << std::endl;

    // 输出到文件
    if (m_logFile.is_open()) {
        m_logFile << formattedMessage << std::endl;
        m_logFile.flush();
    }
}

void LogManager::debug(const std::string& message)
{
    log(LogLevel::Debug, message);
}

void LogManager::info(const std::string& message)
{
    log(LogLevel::Info, message);
}

void LogManager::warning(const std::string& message)
{
    log(LogLevel::Warning, message);
}

void LogManager::error(const std::string& message)
{
    log(LogLevel::Error, message);
}

void LogManager::critical(const std::string& message)
{
    log(LogLevel::Critical, message);
}

void LogManager::setLogFilePath(const std::string& path)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_logFile.is_open()) {
        m_logFile.close();
    }

    m_logFilePath = path;
    m_logFile.open(m_logFilePath, std::ios::out | std::ios::app);

    if (!m_logFile.is_open()) {
        std::cerr << "Failed to open log file: " << m_logFilePath << std::endl;
    }
}

std::string LogManager::getLogFilePath() const
{
    return m_logFilePath;
}

void LogManager::clearLogFile()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_logFile.is_open()) {
        m_logFile.close();
    }

    m_logFile.open(m_logFilePath, std::ios::out | std::ios::trunc);

    if (!m_logFile.is_open()) {
        std::cerr << "Failed to clear log file: " << m_logFilePath << std::endl;
    }
}

std::string LogManager::formatMessage(LogLevel level, const std::string& message)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    ss << " [" << getLevelString(level) << "] ";
    ss << message;

    return ss.str();
}

std::string LogManager::getLevelString(LogLevel level)
{
    switch (level) {
        case LogLevel::Debug:    return "DEBUG";
        case LogLevel::Info:     return "INFO";
        case LogLevel::Warning:  return "WARNING";
        case LogLevel::Error:    return "ERROR";
        case LogLevel::Critical: return "CRITICAL";
        default:                 return "UNKNOWN";
    }
}
