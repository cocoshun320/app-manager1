#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <string>
#include <vector>
#include <functional>

/**
 * @brief 应用程序信息结构体
 */
struct ApplicationInfo {
    std::string name;
    std::string version;
    std::string publisher;
    std::string uninstallCommand;
    std::string installLocation;
    std::string iconPath;
    bool isSystemApp;
};

/**
 * @brief 应用程序管理器
 *
 * 提供应用程序枚举、卸载和注册表清理功能
 */
class AppManager
{
public:
    using ProgressCallback = std::function<void(const std::string&, int)>;

    /**
     * @brief 枚举所有已安装的应用程序
     */
    static std::vector<ApplicationInfo> enumerateApplications();

    /**
     * @brief 卸载单个应用程序
     */
    static bool uninstallApplication(const ApplicationInfo& app, ProgressCallback callback = nullptr);

    /**
     * @brief 批量卸载应用程序
     */
    static bool uninstallApplications(const std::vector<ApplicationInfo>& apps, ProgressCallback callback = nullptr);

    /**
     * @brief 清理注册表
     */
    static bool cleanupRegistry(const std::string& appName);

    /**
     * @brief 请求管理员权限
     */
    static bool requestAdminPrivileges();
};

#endif // APPMANAGER_H
