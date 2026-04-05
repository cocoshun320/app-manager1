#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <string>
#include <vector>

/**
 * @brief 语言信息结构体
 */
struct LanguageInfo {
    std::string code;
    std::string name;
    bool installed;
};

/**
 * @brief 语言管理器
 *
 * 提供语言包管理功能
 */
class LanguageManager
{
public:
    /**
     * @brief 获取可用语言列表
     */
    static std::vector<LanguageInfo> getAvailableLanguages();

    /**
     * @brief 检查语言包是否已安装
     */
    static bool isLanguageInstalled(const std::string& languageCode);

    /**
     * @brief 安装语言包
     */
    static bool installLanguagePackage(const std::string& languageCode);

    /**
     * @brief 切换系统语言
     */
    static bool switchSystemLanguage(const std::string& languageCode);
};

#endif // LANGUAGEMANAGER_H
