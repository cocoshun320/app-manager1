#include "PrivilegeManager.h"
#include <windows.h>
#include <shellapi.h>
#include "LogManager.h"

bool PrivilegeManager::hasAdminPrivileges()
{
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY authority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&authority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
            isAdmin = FALSE;
        }
        FreeSid(adminGroup);
    }

    return isAdmin != FALSE;
}

bool PrivilegeManager::requestAdminPrivileges()
{
    // 获取当前程序路径
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    return runAsAdmin(exePath, "");
}

bool PrivilegeManager::runAsAdmin(const std::string& executablePath, const std::string& arguments)
{
    SHELLEXECUTEINFOA sei;
    ZeroMemory(&sei, sizeof(sei));
    sei.cbSize = sizeof(sei);
    sei.hwnd = NULL;
    sei.lpVerb = "runas";
    sei.lpFile = executablePath.c_str();
    sei.lpParameters = arguments.empty() ? NULL : arguments.c_str();
    sei.nShow = SW_NORMAL;

    if (!ShellExecuteExA(&sei)) {
        DWORD error = GetLastError();
        if (error == ERROR_CANCELLED) {
            LogManager::instance().info("用户取消了权限提升请求");
        } else {
            LogManager::instance().error("权限提升失败，错误代码: " + std::to_string(error));
        }
        return false;
    }

    return true;
}
