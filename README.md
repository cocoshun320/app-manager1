# C++ 应用程序管理工具

一个功能强大的桌面应用程序，用于管理Windows系统中的应用程序、语言设置、网址收藏和安全访问。

## 功能特性

### 1. 应用程序管理（第一页）
- 自动扫描系统中所有已安装的应用程序（包括系统自带）
- 显示应用程序名称、版本、发布者等信息
- 支持多选和全选功能
- 一键卸载选中的应用程序
- 可选择是否清理相关注册表项

### 2. 语言设置（第二页）
- 检测语言包安装状态
- 一键安装英语（美国）语言包
- 安装成功后自动切换系统语言

### 3. 网址管理（第三页）
- 12个常用网址分类：
  - 搜索引擎：百度、Google
  - 短视频/综合平台：抖音、快手、Bilibili、Acfun
  - 海外社交/媒体：Instagram、Twitter、YouTube
  - AI工具/助手：豆包、ChatGPT、DeepSeek、Gemini、Kimi
  - 邮箱/办公协作：Gmail、QQ邮箱、飞书
  - 二手/电商相关：闲鱼
  - 开发/云服务：GitHub、阿里云、腾讯云、华为云
  - 翻译工具：有道翻译、谷歌翻译
  - 视频平台：腾讯视频、爱奇艺、优酷
  - 音乐平台：QQ音乐、网易云音乐、汽水音乐
  - 网盘存储：百度网盘、阿里网盘、夸克网盘、蓝奏云网盘
- 支持分类展开/折叠
- 双击网址在默认浏览器中打开

### 4. 安全页面（第四页）
- 需要输入用户名和密码才能访问
- 密码使用SHA-256加密存储
- 默认用户名：admin
- 默认密码：admin123

## 界面特性

- **半透明窗口**：美观的半透明效果，可以看到桌面背景
- **现代化UI**：使用Qt Style Sheets实现的现代化界面
- **流畅切换**：页面切换快速响应（<500ms）
- **美化样式**：统一的控件样式和配色方案

## 技术栈

- **编程语言**：C++17
- **GUI框架**：Qt 6.x
- **构建工具**：CMake 3.20+
- **加密库**：OpenSSL
- **平台**：Windows 10/11

## 编译要求

### 必需工具

1. **CMake** (3.20+)
   - 下载地址：https://cmake.org/download/

2. **Qt 6.x**
   - 下载地址：https://www.qt.io/download
   - 需要安装Qt Core和Qt Widgets模块

3. **Visual Studio 2022** (或兼容的C++编译器)
   - 下载地址：https://visualstudio.microsoft.com/

4. **OpenSSL**
   - 下载地址：https://slproweb.com/products/Win32OpenSSL.html

### 编译步骤

#### 方法1：使用批处理脚本（推荐）

1. 双击运行 `build.bat`
2. 脚本会自动完成以下步骤：
   - 创建build目录
   - 运行CMake配置
   - 编译项目（Release模式）
   - 打包Qt依赖库

#### 方法2：手动编译

```bash
# 1. 创建build目录
mkdir build
cd build

# 2. 运行CMake配置
cmake .. -G "Visual Studio 17 2022" -A x64

# 3. 编译项目
cmake --build . --config Release

# 4. 打包依赖库
cd bin\Release
windeployqt AppManager.exe
```

## 使用说明

### 启动程序

编译完成后，在 `build\bin\Release` 目录下找到 `AppManager.exe`，双击运行。

### 默认凭据

- 用户名：`admin`
- 密码：`admin123`

### 功能使用

1. **应用管理**
   - 点击"刷新"按钮扫描应用程序
   - 勾选要卸载的应用程序
   - 可选择"清理注册表"
   - 点击"卸载选中应用"执行卸载

2. **语言设置**
   - 选择要安装的语言包
   - 点击"安装语言包"
   - 重启计算机以应用更改

3. **网址管理**
   - 双击分类展开/折叠
   - 双击网址在浏览器中打开

4. **安全页面**
   - 输入用户名和密码
   - 点击"登录"进入
   - 点击"退出登录"退出

## 项目结构

```
app/
├── src/
│   ├── core/              # 核心类
│   │   ├── MainWindow.h/cpp
│   │   └── BasePage.h/cpp
│   ├── modules/           # 功能模块
│   │   ├── AppManager.h/cpp
│   │   ├── LogManager.h/cpp
│   │   ├── RegistryAccessor.h/cpp
│   │   ├── PrivilegeManager.h/cpp
│   │   ├── LanguageManager.h/cpp
│   │   ├── URLManager.h/cpp
│   │   └── AuthManager.h/cpp
│   ├── pages/             # 页面类
│   │   ├── AppManagementPage.h/cpp
│   │   ├── LanguagePage.h/cpp
│   │   ├── URLManagementPage.h/cpp
│   │   ├── SecurityPage.h/cpp
│   │   └── LoginDialog.h/cpp
│   └── main.cpp
├── resources/
│   ├── styles/            # 样式文件
│   │   └── main.qss
│   ├── icons/             # 图标资源
│   └── config/            # 配置文件
├── tests/                 # 测试文件
├── CMakeLists.txt         # CMake配置文件
├── build.bat              # 编译脚本
└── README.md              # 本文件
```

## 注意事项

1. **管理员权限**：卸载应用程序需要管理员权限
2. **语言包**：安装语言包需要网络连接
3. **注册表清理**：清理注册表前请谨慎操作
4. **密码安全**：建议修改默认密码

## 性能指标

- 应用启动时间：< 3秒
- 页面切换时间：< 500ms
- 应用扫描时间：< 5秒

## 系统要求

- 操作系统：Windows 10/11 (64位)
- 内存：至少 2GB RAM
- 磁盘空间：至少 100MB 可用空间

## 许可证

本项目仅供学习和个人使用。

## 问题反馈

如遇到问题，请检查：
1. 是否正确安装了所有依赖工具
2. Qt环境变量是否正确配置
3. 是否以管理员权限运行（卸载功能）
4. 日志文件 `app_manager.log` 中的错误信息

## 更新日志

### v1.0 (2025-04-05)
- 初始版本发布
- 实现所有核心功能
- 支持半透明窗口
- 完整的错误处理和日志记录
