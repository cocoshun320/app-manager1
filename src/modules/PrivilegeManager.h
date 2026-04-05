#ifndef PRIVILEGEMANAGER_H
#define PRIVILEGEMANAGER_H

#include <string>

/**
 * @brief 权限管理器
 *
 * 检查当前进程权限，支持请求管理员权限
 */
class PrivilegeManager
{
public:
    /**
     * @brief 检查是否具有管理员权限
     */
    static bool hasAdminPrivileges();

    /**
     * @brief 请求管理员权限
     */
    static bool requestAdminPrivileges();

    /**
     * @brief 以管理员权限运行程序
     */
    static bool runAsAdmin(const std::string& executablePath, const std::string& arguments);
};

#endif // PRIVILEGEMANAGER_H
