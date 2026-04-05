#ifndef REGISTRYACCESSOR_H
#define REGISTRYACCESSOR_H

#include <string>
#include <vector>

/**
 * @brief 注册表访问器
 *
 * 封装Windows注册表API，提供友好的C++接口
 */
class RegistryAccessor
{
public:
    /**
     * @brief 读取字符串值
     */
    static std::string readStringValue(const std::string& keyPath, const std::string& valueName);

    /**
     * @brief 读取布尔值
     */
    static bool readBoolValue(const std::string& keyPath, const std::string& valueName);

    /**
     * @brief 读取整数值
     */
    static int readIntValue(const std::string& keyPath, const std::string& valueName);

    /**
     * @brief 写入字符串值
     */
    static bool writeStringValue(const std::string& keyPath, const std::string& valueName, const std::string& value);

    /**
     * @brief 删除注册表键
     */
    static bool deleteKey(const std::string& keyPath);

    /**
     * @brief 删除注册表值
     */
    static bool deleteValue(const std::string& keyPath, const std::string& valueName);

    /**
     * @brief 枚举子键
     */
    static std::vector<std::string> enumerateSubKeys(const std::string& keyPath);

    /**
     * @brief 枚举值
     */
    static std::vector<std::string> enumerateValues(const std::string& keyPath);
};

#endif // REGISTRYACCESSOR_H
