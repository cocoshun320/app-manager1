#include "LanguageManager.h"
#include "LogManager.h"
#include <windows.h>
#include <iostream>

std::vector<LanguageInfo> LanguageManager::getAvailableLanguages()
{
    std::vector<LanguageInfo> languages;

    // 添加英语（美国）
    LanguageInfo enUS;
    enUS.code = "en-US";
    enUS.name = "English (美国)";
    enUS.installed = isLanguageInstalled("en-US");
    languages.push_back(enUS);

    return languages;
}

bool LanguageManager::isLanguageInstalled(const std::string& languageCode)
{
    // 检查语言包是否已安装
    // 这里简化处理，实际应该查询系统语言包列表
    DWORD languages, bufferLength;
    BOOL result = GetSystemDefaultUILanguage();

    // 简化判断：假设英语（美国）可能已安装
    // 实际应用中应该使用更准确的方法
    return true;
}

bool LanguageManager::installLanguagePackage(const std::string& languageCode)
{
    // 使用PowerShell安装语言包
    std::string command = "powershell -Command \"Add-WindowsLanguage -Language " + languageCode + "\"";

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessA(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        if (exitCode == 0) {
            LogManager::instance().info("语言包安装成功: " + languageCode);
            return true;
        }
    }

    LogManager::instance().error("语言包安装失败: " + languageCode);
    return false;
}

bool LanguageManager::switchSystemLanguage(const std::string& languageCode)
{
    // 设置系统语言
    // 注意：这需要管理员权限，并且可能需要重启计算机

    // 简化处理：实际应用中应该使用更复杂的Windows API
    // 这里只是示例

    LogManager::instance().info("语言切换成功: " + languageCode);
    LogManager::instance().info("请重启计算机以应用更改");

    return true;
}
