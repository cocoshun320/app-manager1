# GitHub Actions 自动编译指南

## 📋 步骤说明

### 1. 创建GitHub仓库

1. 访问 https://github.com/new
2. 创建新仓库，例如：`app-manager`
3. 设置为 **Public**（公开）或 **Private**（私有）
4. **不要**勾选 "Initialize this repository with a README"
5. 点击 "Create repository"

### 2. 上传代码到GitHub

#### 方法A：使用Git命令行（推荐）

1. **安装Git**（如果还未安装）
   - 下载：https://git-scm.com/download/win
   - 安装时保持默认设置

2. **打开命令提示符**，执行以下命令：

```bash
# 进入项目目录
cd c:\Users\lzs18\IDEProjects\app

# 初始化Git仓库
git init

# 添加所有文件
git add .

# 提交更改
git commit -m "Initial commit"

# 添加远程仓库（替换YOUR_USERNAME为你的GitHub用户名）
git remote add origin https://github.com/YOUR_USERNAME/app-manager.git

# 推送到GitHub（首次推送需要登录）
git push -u origin master
```

当系统提示输入用户名和密码时：
- **用户名**：你的GitHub用户名
- **密码**：使用 **Personal Access Token**（不是GitHub密码）

#### 方法B：使用GitHub网页上传

1. 访问你刚创建的仓库
2. 点击 "uploading an existing file"
3. 将项目中的所有文件拖拽到上传区域
4. 在底部输入提交信息："Initial commit"
5. 点击 "Commit changes"

### 3. 获取Personal Access Token（方法A需要）

如果使用Git命令行，需要创建Personal Access Token：

1. 访问：https://github.com/settings/tokens
2. 点击 "Generate new token (classic)"
3. 勾选权限：
   - ✅ `repo`（完整仓库访问权限）
   - ✅ `workflow`（GitHub Actions权限）
4. 点击 "Generate token"
5. **复制**生成的token（只显示一次！）
6. 在Git推送时，使用这个token作为密码

### 4. 触发自动编译

#### 自动触发
- 每次推送代码到GitHub时，自动触发编译
- 每次创建Pull Request时，自动触发编译

#### 手动触发
1. 访问仓库的 "Actions" 标签页
2. 选择 "Build and Release" 工作流
3. 点击 "Run workflow"
4. 选择分支，点击 "Run workflow"

### 5. 下载编译结果

1. 访问仓库的 "Actions" 标签页
2. 点击最新的编译任务
3. 滚动到页面底部
4. 在 "Artifacts" 部分，点击 "AppManager-Windows-x64"
5. 下载ZIP文件

### 6. 使用编译好的程序

1. 解压下载的ZIP文件
2. 双击 `AppManager.exe` 运行
3. 默认登录凭据：
   - 用户名：`admin`
   - 密码：`admin123`

## 🚀 快速开始（5分钟）

### 如果你已经有Git

```bash
# 1. 进入项目目录
cd c:\Users\lzs18\IDEProjects\app

# 2. 初始化Git仓库
git init
git add .
git commit -m "Initial commit"

# 3. 替换YOUR_USERNAME为你的GitHub用户名
git remote add origin https://github.com/YOUR_USERNAME/app-manager.git

# 4. 推送到GitHub（需要Personal Access Token）
git push -u origin master
```

### 如果没有Git

1. 访问你的GitHub仓库
2. 点击 "uploading an existing file"
3. 拖拽项目文件夹中的所有文件
4. 提交更改

## 📊 编译过程说明

GitHub Actions会自动执行以下步骤：

1. **环境准备**：使用Windows 2022镜像
2. **安装依赖**：
   - Qt 6.6.0 (MSVC 2022 64-bit)
   - OpenSSL
3. **配置项目**：运行CMake
4. **编译项目**：使用Visual Studio 2022
5. **打包依赖**：使用windeployqt
6. **创建压缩包**：打包成ZIP文件
7. **上传结果**：作为Artifact提供下载

编译时间大约需要 **5-10分钟**。

## 🔧 故障排除

### 问题1：推送失败，提示认证错误

**解决方案**：
1. 创建Personal Access Token：https://github.com/settings/tokens
2. 使用token作为密码（不是GitHub密码）
3. 或使用SSH方式：
   ```bash
   git remote set-url origin git@github.com:YOUR_USERNAME/app-manager.git
   git push -u origin master
   ```

### 问题2：编译失败

**解决方案**：
1. 访问仓库的 "Actions" 标签页
2. 点击失败的编译任务
3. 查看详细的错误日志
4. 根据错误信息修改代码
5. 重新推送触发编译

### 问题3：下载的ZIP文件无法运行

**解决方案**：
1. 确保完整下载ZIP文件
2. 解压到本地文件夹
3. 双击 `AppManager.exe` 运行
4. 如果提示缺少DLL，说明打包不完整，重新编译

## 📝 代码更新后如何重新编译

只需推送新的代码，GitHub会自动触发编译：

```bash
# 修改代码后
git add .
git commit -m "Update code"
git push
```

## 🎉 完成！

现在你已经配置好了GitHub Actions自动编译。

- ✅ 代码已上传到GitHub
- ✅ 自动编译已配置
- ✅ 可以随时下载编译好的程序

每次推送代码，GitHub都会自动编译并提供下载链接！

---

**需要帮助？** 查看：
- GitHub Actions文档：https://docs.github.com/en/actions
- 项目README：README.md
