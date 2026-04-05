#include "RegistryAccessor.h"
#include <windows.h>
#include "LogManager.h"

std::string RegistryAccessor::readStringValue(const std::string& keyPath, const std::string& valueName)
{
    HKEY hKey;
    DWORD type, size;
    std::string value;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, valueName.c_str(), NULL, &type, NULL, &size) == ERROR_SUCCESS) {
            if (type == REG_SZ) {
                value.resize(size);
                RegQueryValueExA(hKey, valueName.c_str(), NULL, &type, (LPBYTE)value.data(), &size);
                value.resize(size - 1); // 去除null终止符
            }
        }
        RegCloseKey(hKey);
    }

    return value;
}

bool RegistryAccessor::readBoolValue(const std::string& keyPath, const std::string& valueName)
{
    return readIntValue(keyPath, valueName) != 0;
}

int RegistryAccessor::readIntValue(const std::string& keyPath, const std::string& valueName)
{
    HKEY hKey;
    DWORD type, size;
    int value = 0;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        size = sizeof(DWORD);
        if (RegQueryValueExA(hKey, valueName.c_str(), NULL, &type, (LPBYTE)&value, &size) == ERROR_SUCCESS) {
            if (type == REG_DWORD) {
                // 值已正确读取
            }
        }
        RegCloseKey(hKey);
    }

    return value;
}

bool RegistryAccessor::writeStringValue(const std::string& keyPath, const std::string& valueName, const std::string& value)
{
    HKEY hKey;
    bool success = false;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        if (RegSetValueExA(hKey, valueName.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(), value.size() + 1) == ERROR_SUCCESS) {
            success = true;
        }
        RegCloseKey(hKey);
    }

    return success;
}

bool RegistryAccessor::deleteKey(const std::string& keyPath)
{
    return RegDeleteKeyA(HKEY_LOCAL_MACHINE, keyPath.c_str()) == ERROR_SUCCESS;
}

bool RegistryAccessor::deleteValue(const std::string& keyPath, const std::string& valueName)
{
    HKEY hKey;
    bool success = false;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        if (RegDeleteValueA(hKey, valueName.c_str()) == ERROR_SUCCESS) {
            success = true;
        }
        RegCloseKey(hKey);
    }

    return success;
}

std::vector<std::string> RegistryAccessor::enumerateSubKeys(const std::string& keyPath)
{
    std::vector<std::string> subKeys;
    HKEY hKey;
    DWORD index = 0;
    char name[256];
    DWORD nameSize;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        while (true) {
            nameSize = sizeof(name);
            if (RegEnumKeyExA(hKey, index, name, &nameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
                subKeys.push_back(name);
                index++;
            } else {
                break;
            }
        }
        RegCloseKey(hKey);
    }

    return subKeys;
}

std::vector<std::string> RegistryAccessor::enumerateValues(const std::string& keyPath)
{
    std::vector<std::string> values;
    HKEY hKey;
    DWORD index = 0;
    char name[256];
    DWORD nameSize;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        while (true) {
            nameSize = sizeof(name);
            if (RegEnumValueA(hKey, index, name, &nameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
                values.push_back(name);
                index++;
            } else {
                break;
            }
        }
        RegCloseKey(hKey);
    }

    return values;
}
