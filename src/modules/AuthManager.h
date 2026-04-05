#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>

/**
 * @brief 认证管理器
 *
 * 提供用户凭证验证功能
 */
class AuthManager
{
public:
    /**
     * @brief 获取单例实例
     */
    static AuthManager& instance();

    /**
     * @brief 验证用户名和密码
     */
    bool authenticate(const std::string& username, const std::string& password);

    /**
     * @brief 检查是否已登录
     */
    bool isLoggedIn() const;

    /**
     * @brief 登出
     */
    void logout();

    /**
     * @brief 设置密码
     */
    void setPassword(const std::string& password);

private:
    AuthManager();
    ~AuthManager();

    /**
     * @brief 哈希密码
     */
    std::string hashPassword(const std::string& password);

    std::string m_username;
    std::string m_passwordHash;
    bool m_loggedIn;
};

#endif // AUTHMANAGER_H
