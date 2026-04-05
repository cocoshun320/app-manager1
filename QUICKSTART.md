# 快速开始指南

## 前提条件

在开始之前，请确保已安装以下工具：

1. **CMake** (3.20+)
   - 下载：https://cmake.org/download/
   - 安装后确保已添加到系统PATH

2. **Qt 6.x**
   - 下载：https://www.qt.io/download
   - 需要安装：Qt Core、Qt Widgets
   - 设置环境变量：`QTDIR` 和 `PATH`

3. **Visual Studio 2022** (或兼容的C++编译器)
   - 下载：https://visualstudio.microsoft.com/
   - 需要安装：使用C++的桌面开发

4. **OpenSSL**
   - 下载：https://slproweb.com/products/Win32OpenSSL.html
   - 选择：Win64 OpenSSL v3.x.x

## 快速编译步骤

### 方法1：一键编译（推荐）

1. 双击运行 `build.bat`
2. 等待编译完成
3. 可执行文件位于：`build\bin\Release\AppManager.exe`

### 方法2：手动编译

```bash
# 1. 打开命令提示符（以管理员身份）
# 2. 进入项目目录
cd c:\Users\lzs18\IDEProjects\app

# 3. 创建build目录
mkdir build
cd build

# 4. 配置项目
cmake .. -G "Visual Studio 17 2022" -A x64

# 5. 编译
cmake --build . --config Release

# 6. 打包依赖库
cd bin\Release
windeployqt AppManager.exe
```

## 创建安装包

1. 确保已安装NSIS：https://nsis.sourceforge.io/
2. 双击运行 `package.bat`
3. 安装包将生成在项目根目录：`AppManager_Setup.exe`

## 运行程序

### 直接运行
```bash
cd build\bin\Release
AppManager.exe
```

### 安装后运行
1. 运行 `AppManager_Setup.exe` 安装
2. 从开始菜单或桌面快捷方式启动

## 默认登录凭据

- **用户名**：`admin`
- **密码**：`admin123`

## 功能快速导航

### 第1页：应用管理
- 刷新：扫描所有应用程序
- 全选/取消全选：快速选择
- 卸载选中应用：批量卸载
- 清理注册表：可选清理注册表项

### 第2页：语言设置
- 查看语言包状态
- 安装英语（美国）语言包
- 重启计算机应用更改

### 第3页：网址管理
- 双击分类展开/折叠
- 双击网址在浏览器中打开
- 12个分类，包含常用网址

### 第4页：安全页面
- 输入用户名和密码登录
- 登录后可访问安全功能
- 退出登录返回

## 常见问题

### Q1: 编译时提示找不到Qt
**A**: 检查Qt环境变量是否正确设置：
```bash
echo %QTDIR%
echo %PATH%
```

### Q2: 编译时提示找不到OpenSSL
**A**: 确保OpenSSL已安装并设置环境变量：
```bash
set OPENSSL_ROOT_DIR=C:\Program Files\OpenSSL-Win64
```

### Q3: 运行时提示缺少DLL
**A**: 运行windeployqt打包Qt依赖库：
```bash
cd build\bin\Release
windeployqt AppManager.exe
```

### Q4: 卸载应用时提示权限不足
**A**: 以管理员身份运行程序

### Q5: 语言包安装失败
**A**: 检查：
- 网络连接是否正常
- PowerShell是否可用
- 是否以管理员身份运行

## 项目文件说明

| 文件 | 说明 |
|------|------|
| `build.bat` | 一键编译脚本 |
| `package.bat` | 创建安装包脚本 |
| `CMakeLists.txt` | CMake配置文件 |
| `README.md` | 完整使用说明 |
| `PROJECT_SUMMARY.md` | 项目总结文档 |
| `install.nsi` | NSIS安装包脚本 |
| `LICENSE.txt` | 许可证文件 |

## 获取帮助

遇到问题？请查看：
1. `README.md` - 完整使用说明
2. `PROJECT_SUMMARY.md` - 项目总结
3. `app_manager.log` - 运行日志

## 下一步

- 修改默认密码
- 自定义网址分类
- 添加更多语言包
- 探索其他功能

---

**祝使用愉快！** 🎉
