# 🚀 上传代码到GitHub并编译 - 详细步骤

## ✅ 当前状态

- ✅ 代码已提交到本地Git仓库
- ✅ 已配置Gitee远程仓库
- ✅ GitHub Actions配置已就绪

## 📝 完整步骤

### 第1步：创建GitHub仓库（2分钟）

1. **访问GitHub**
   - 打开浏览器，访问：https://github.com/new

2. **创建新仓库**
   - **Repository name**：输入 `app-manager`
   - **Description**：输入 `C++ Desktop Application Manager`
   - **Public/Private**：选择 **Public**（公开）
   - **不要勾选**：
     - ❌ Add a README file
     - ❌ Add .gitignore
     - ❌ Choose a license
   - 点击 **Create repository**

3. **记住仓库地址**
   - 会显示类似这样的地址：
   - `https://github.com/YOUR_USERNAME/app-manager.git`
   - `YOUR_USERNAME` 是你的GitHub用户名

### 第2步：获取Personal Access Token（3分钟）

⚠️ **重要**：GitHub现在需要使用Personal Access Token进行认证，不能使用密码！

1. **访问设置页面**
   - 访问：https://github.com/settings/tokens

2. **创建新Token**
   - 点击 **Generate new token**
   - 选择 **Generate new token (classic)**

3. **配置Token**
   - **Note**：输入 `AppManager`
   - **Expiration**：选择 **No expiration**（永不过期）或 **90 days**
   - **Select scopes**：勾选以下权限：
     - ✅ `repo`（完整仓库访问权限）
     - ✅ `workflow`（GitHub Actions权限）
     - ✅ `write:packages`（写入包权限）

4. **生成并复制Token**
   - 点击 **Generate token**
   - **立即复制**生成的token（只显示一次！）
   - 保存到安全的地方

### 第3步：添加GitHub远程仓库（1分钟）

**打开命令提示符**，执行以下命令：

```bash
# 进入项目目录
cd c:\Users\lzs18\IDEProjects\app

# 添加GitHub远程仓库（请替换YOUR_USERNAME为你的GitHub用户名）
git remote add github https://github.com/YOUR_USERNAME/app-manager.git

# 验证远程仓库
git remote -v
```

你应该看到：
```
origin  https://gitee.com/zxcvgyujm/app-manager.git (fetch)
origin  https://gitee.com/zxcvgyujm/app-manager.git (push)
github  https://github.com/YOUR_USERNAME/app-manager.git (fetch)
github  https://github.com/YOUR_USERNAME/app-manager.git (push)
```

### 第4步：推送到GitHub（1分钟）

```bash
# 推送代码到GitHub
git push github master
```

**系统会提示输入用户名和密码：**
- **Username**：输入你的GitHub用户名
- **Password**：粘贴刚才复制的Personal Access Token

### 第5步：触发自动编译

推送成功后，GitHub会自动触发编译！

**查看编译进度：**

1. **访问GitHub仓库**
   - https://github.com/YOUR_USERNAME/app-manager

2. **点击Actions标签页**
   - 在仓库顶部导航栏找到 "Actions"
   - 点击进入

3. **查看编译任务**
   - 你会看到正在运行的编译任务
   - 状态显示：🔄 运行中
   - 编译大约需要5-10分钟

4. **查看详细日志**
   - 点击正在运行的任务
   - 可以实时查看编译日志
   - 包括环境准备、依赖安装、编译过程等

### 第6步：下载编译好的程序

**等待编译完成：**
- 状态变为：✅ 成功（绿色）
- 通常需要5-10分钟

**下载编译结果：**

1. **点击成功的编译任务**

2. **滚动到页面底部**

3. **找到Artifacts部分**
   - 看到文件名：`AppManager-Windows-x64`
   - 点击下载按钮

4. **解压并运行**
   - 解压下载的ZIP文件
   - 双击 `AppManager.exe`
   - 默认登录：
     - 用户名：`admin`
     - 密码：`admin123`

## 🔧 常见问题

### Q1: 推送失败，提示认证错误

**解决方案：**

**方法1：使用Personal Access Token**
```bash
# 移除旧的远程仓库
git remote remove github

# 重新添加（会提示输入用户名和token）
git remote add github https://github.com/YOUR_USERNAME/app-manager.git
git push github master
```

**方法2：使用SSH（推荐）**
```bash
# 生成SSH密钥
ssh-keygen -t rsa -C "your_email@example.com"

# 查看公钥
cat ~/.ssh/id_rsa.pub

# 复制公钥，添加到GitHub：https://github.com/settings/keys

# 使用SSH推送
git remote set-url github git@github.com:YOUR_USERNAME/app-manager.git
git push github master
```

### Q2: 提示仓库不存在

**解决方案：**
1. 确保已在GitHub上创建了仓库
2. 确保仓库名称正确（`app-manager`）
3. 确保替换了YOUR_USERNAME为你的实际用户名

### Q3: 编译失败

**解决方案：**
1. 查看详细的错误日志
2. 检查代码是否有语法错误
3. 修改代码后重新推送：
   ```bash
   git add .
   git commit -m "Fix compilation errors"
   git push github master
   ```

### Q4: Actions没有自动触发

**解决方案：**
1. 确保仓库中包含 `.github/workflows/build.yml` 文件
2. 确保文件路径正确
3. 检查Actions是否已启用：
   - 访问仓库设置
   - 点击 "Actions" -> "General"
   - 确保 "Allow all actions and reusable workflows" 已选中

### Q5: 找不到下载的Artifacts

**解决方案：**
1. 确保编译已完成（显示绿色✅）
2. 刷新页面
3. 点击编译任务
4. 滚动到页面底部
5. 在 "Artifacts" 部分点击下载

## 📊 编译过程说明

GitHub Actions会自动执行以下步骤：

1. **环境准备** ✅
   - 使用Windows 2022服务器
   - 配置编译环境

2. **安装依赖** ✅
   - 安装Qt 6.6.0 (MSVC 2022 64-bit)
   - 安装OpenSSL

3. **配置项目** ✅
   - 运行CMake配置
   - 生成编译配置文件

4. **编译项目** ✅
   - 使用Visual Studio 2022编译
   - Release模式优化

5. **打包依赖** ✅
   - 使用windeployqt打包Qt库
   - 包含所有必要的DLL文件

6. **创建压缩包** ✅
   - 打包成ZIP文件
   - 方便下载和分发

7. **上传Artifacts** ✅
   - 上传编译结果
   - 提供下载链接

## 📝 后续更新

### 更新代码后重新编译

```bash
cd c:\Users\lzs18\IDEProjects\app

# 修改代码...

# 提交更改
git add .
git commit -m "Update code"

# 推送到GitHub（会自动触发编译）
git push github master
```

### 同时推送到Gitee和GitHub

```bash
# 推送到Gitee
git push origin master

# 推送到GitHub
git push github master
```

## 🎯 快速参考

### GitHub仓库地址格式

```
HTTPS: https://github.com/YOUR_USERNAME/app-manager.git
SSH:   git@github.com:YOUR_USERNAME/app-manager.git
```

### 常用Git命令

```bash
# 查看远程仓库
git remote -v

# 查看状态
git status

# 查看提交历史
git log

# 查看当前分支
git branch

# 强制推送（慎用）
git push -f github master
```

## 🆘 需要帮助？

- **GitHub文档**：https://docs.github.com/
- **GitHub Actions文档**：https://docs.github.com/en/actions
- **项目README**：`README.md`
- **快速开始指南**：`QUICKSTART.md`

---

**准备好了吗？开始第1步，创建GitHub仓库吧！** 🚀

几分钟后就能下载编译好的程序了！
