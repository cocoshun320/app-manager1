#include "AuthManager.h"
#include "LogManager.h"
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <cstring>

AuthManager& AuthManager::instance()
{
    static AuthManager instance;
    return instance;
}

AuthManager::AuthManager()
    : m_username("admin")
    , m_passwordHash("")  // 初始密码为空
    , m_loggedIn(false)
{
    // 设置默认密码
    setPassword("admin123");
}

AuthManager::~AuthManager()
{
}

bool AuthManager::authenticate(const std::string& username, const std::string& password)
{
    std::string passwordHash = hashPassword(password);

    if (username == m_username && passwordHash == m_passwordHash) {
        m_loggedIn = true;
        LogManager::instance().info("用户登录成功: " + username);
        return true;
    }

    LogManager::instance().warning("用户登录失败: " + username);
    return false;
}

bool AuthManager::isLoggedIn() const
{
    return m_loggedIn;
}

void AuthManager::logout()
{
    m_loggedIn = false;
    LogManager::instance().info("用户已登出");
}

void AuthManager::setPassword(const std::string& password)
{
    m_passwordHash = hashPassword(password);
    LogManager::instance().info("密码已更新");
}

std::string AuthManager::hashPassword(const std::string& password)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}
