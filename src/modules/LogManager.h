#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <memory>

/**
 * @brief 日志级别枚举
 */
enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

/**
 * @brief 日志管理器
 *
 * 提供统一的日志记录接口，支持不同级别的日志输出和文件存储
 */
class LogManager
{
public:
    /**
     * @brief 获取单例实例
     */
    static LogManager& instance();

    /**
     * @brief 记录日志
     * @param level 日志级别
     * @param message 日志消息
     */
    void log(LogLevel level, const std::string& message);

    /**
     * @brief Debug级别日志
     */
    void debug(const std::string& message);

    /**
     * @brief Info级别日志
     */
    void info(const std::string& message);

    /**
     * @brief Warning级别日志
     */
    void warning(const std::string& message);

    /**
     * @brief Error级别日志
     */
    void error(const std::string& message);

    /**
     * @brief Critical级别日志
     */
    void critical(const std::string& message);

    /**
     * @brief 设置日志文件路径
     */
    void setLogFilePath(const std::string& path);

    /**
     * @brief 获取日志文件路径
     */
    std::string getLogFilePath() const;

    /**
     * @brief 清空日志文件
     */
    void clearLogFile();

private:
    LogManager();
    ~LogManager();
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    std::string formatMessage(LogLevel level, const std::string& message);
    std::string getLevelString(LogLevel level);

    std::ofstream m_logFile;
    std::string m_logFilePath;
    std::mutex m_mutex;
};

#endif // LOGMANAGER_H
