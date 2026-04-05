#include "AppManager.h"
#include "RegistryAccessor.h"
#include "PrivilegeManager.h"
#include "LogManager.h"
#include <windows.h>
#include <algorithm>

std::vector<ApplicationInfo> AppManager::enumerateApplications()
{
    std::vector<ApplicationInfo> applications;

    // 从HKEY_LOCAL_MACHINE读取
    std::vector<std::string> keys = RegistryAccessor::enumerateSubKeys(
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
    );

    for (const auto& key : keys) {
        ApplicationInfo app;
        std::string keyPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + key;

        app.name = RegistryAccessor::readStringValue(keyPath, "DisplayName");
        app.version = RegistryAccessor::readStringValue(keyPath, "DisplayVersion");
        app.publisher = RegistryAccessor::readStringValue(keyPath, "Publisher");
        app.uninstallCommand = RegistryAccessor::readStringValue(keyPath, "UninstallString");
        app.installLocation = RegistryAccessor::readStringValue(keyPath, "InstallLocation");
        app.iconPath = RegistryAccessor::readStringValue(keyPath, "DisplayIcon");
        app.isSystemApp = true;

        if (!app.name.empty()) {
            applications.push_back(app);
        }
    }

    // 从HKEY_CURRENT_USER读取
    keys = RegistryAccessor::enumerateSubKeys(
        "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
    );

    for (const auto& key : keys) {
        ApplicationInfo app;
        std::string keyPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + key;

        app.name = RegistryAccessor::readStringValue(keyPath, "DisplayName");
        app.version = RegistryAccessor::readStringValue(keyPath, "DisplayVersion");
        app.publisher = RegistryAccessor::readStringValue(keyPath, "Publisher");
        app.uninstallCommand = RegistryAccessor::readStringValue(keyPath, "UninstallString");
        app.installLocation = RegistryAccessor::readStringValue(keyPath, "InstallLocation");
        app.iconPath = RegistryAccessor::readStringValue(keyPath, "DisplayIcon");
        app.isSystemApp = false;

        if (!app.name.empty()) {
            applications.push_back(app);
        }
    }

    // 按名称排序
    std::sort(applications.begin(), applications.end(),
        [](const ApplicationInfo& a, const ApplicationInfo& b) {
            return a.name < b.name;
        }
    );

    return applications;
}

bool AppManager::uninstallApplication(const ApplicationInfo& app, ProgressCallback callback)
{
    if (app.uninstallCommand.empty()) {
        LogManager::instance().error("应用程序 " + app.name + " 没有卸载命令");
        return false;
    }

    if (callback) {
        callback("正在卸载: " + app.name, 0);
    }

    // 检查管理员权限
    if (!PrivilegeManager::hasAdminPrivileges()) {
        if (!PrivilegeManager::requestAdminPrivileges()) {
            LogManager::instance().error("无法获取管理员权限");
            return false;
        }
    }

    // 执行卸载命令
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::string command = app.uninstallCommand;
    if (command.find("/I") == std::string::npos) {
        command += " /SILENT";
    }

    if (CreateProcessA(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // 等待进程结束
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        if (callback) {
            callback("卸载完成: " + app.name, 100);
        }

        return exitCode == 0;
    }

    if (callback) {
        callback("卸载失败: " + app.name, 0);
    }

    return false;
}

bool AppManager::uninstallApplications(const std::vector<ApplicationInfo>& apps, ProgressCallback callback)
{
    int total = apps.size();
    int completed = 0;

    for (const auto& app : apps) {
        if (uninstallApplication(app, callback)) {
            completed++;
        }
    }

    if (callback) {
        callback("批量卸载完成", 100);
    }

    return completed == total;
}

bool AppManager::cleanupRegistry(const std::string& appName)
{
    // 清理HKEY_LOCAL_MACHINE中的注册表项
    std::vector<std::string> keys = RegistryAccessor::enumerateSubKeys(
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
    );

    for (const auto& key : keys) {
        std::string keyPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + key;
        std::string name = RegistryAccessor::readStringValue(keyPath, "DisplayName");

        if (name == appName) {
            RegistryAccessor::deleteKey(keyPath);
            LogManager::instance().info("已清理注册表项: " + keyPath);
        }
    }

    // 清理HKEY_CURRENT_USER中的注册表项
    keys = RegistryAccessor::enumerateSubKeys(
        "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
    );

    for (const auto& key : keys) {
        std::string keyPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + key;
        std::string name = RegistryAccessor::readStringValue(keyPath, "DisplayName");

        if (name == appName) {
            RegistryAccessor::deleteKey(keyPath);
            LogManager::instance().info("已清理注册表项: " + keyPath);
        }
    }

    return true;
}

bool AppManager::requestAdminPrivileges()
{
    return PrivilegeManager::requestAdminPrivileges();
}
