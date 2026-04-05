#ifndef URLMANAGER_H
#define URLMANAGER_H

#include <string>
#include <vector>

/**
 * @brief 网址信息结构体
 */
struct URLInfo {
    std::string name;
    std::string url;
};

/**
 * @brief 网址分类结构体
 */
struct URLCategory {
    std::string name;
    std::vector<URLInfo> urls;
};

/**
 * @brief 网址管理器
 *
 * 管理网址分类数据，提供网址打开功能
 */
class URLManager
{
public:
    /**
     * @brief 获取所有网址分类
     */
    static std::vector<URLCategory> getURLCategories();

    /**
     * @brief 在默认浏览器中打开网址
     */
    static bool openURL(const std::string& url);

private:
    /**
     * @brief 初始化网址分类数据
     */
    static void initializeURLCategories();
};

#endif // URLMANAGER_H
