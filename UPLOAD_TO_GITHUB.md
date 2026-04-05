# 🚀 上传代码到GitHub - 只需3步

## ✅ 已完成的工作

我已经为您准备好了：
- ✅ GitHub Actions自动编译配置
- ✅ Git仓库已初始化
- ✅ 代码已提交到本地仓库
- ✅ .gitignore文件已创建

## 📝 接下来的步骤（只需3步）

### 第1步：创建GitHub仓库（1分钟）

1. 访问：https://github.com/new
2. 输入仓库名称，例如：`app-manager`
3. 选择 **Public**（公开）或 **Private**（私有）
4. **不要**勾选任何选项（README、.gitignore等）
5. 点击 "Create repository"

### 第2步：获取Personal Access Token（2分钟）

1. 访问：https://github.com/settings/tokens
2. 点击 "Generate new token" → "Generate new token (classic)"
3. 勾选权限：
   - ✅ `repo`（完整仓库访问权限）
   - ✅ `workflow`（GitHub Actions权限）
4. 设置过期时间：选择 "No expiration"（永不过期）
5. 点击 "Generate token"
6. **复制**生成的token（只显示一次，请妥善保存）

### 第3步：推送代码到GitHub（1分钟）

**打开命令提示符**，执行以下命令：

```bash
# 进入项目目录
cd c:\Users\lzs18\IDEProjects\app

# 添加远程仓库（请替换YOUR_USERNAME为你的GitHub用户名）
git remote add origin https://github.com/YOUR_USERNAME/app-manager.git

# 推送代码到GitHub
git push -u origin master
```

**系统会提示输入用户名和密码：**
- **用户名**：你的GitHub用户名
- **密码**：粘贴刚才复制的Personal Access Token（不是你的GitHub密码）

## 🎉 完成！

推送成功后，GitHub会自动触发编译！

### 查看编译进度

1. 访问你的GitHub仓库
2. 点击 "Actions" 标签页
3. 你会看到正在运行的编译任务
4. 编译大约需要5-10分钟

### 下载编译好的程序

1. 等待编译完成（显示绿色✅）
2. 点击最新的编译任务
3. 滚动到页面底部
4. 在 "Artifacts" 部分，点击 "AppManager-Windows-x64"
5. 下载ZIP文件

### 使用程序

1. 解压下载的ZIP文件
2. 双击 `AppManager.exe` 运行
3. 默认登录凭据：
   - 用户名：`admin`
   - 密码：`admin123`

## 📊 编译过程

GitHub Actions会自动执行以下步骤：

1. ✅ 使用Windows 2022环境
2. ✅ 安装Qt 6.6.0
3. ✅ 安装OpenSSL
4. ✅ 配置CMake项目
5. ✅ 使用Visual Studio 2022编译
6. ✅ 打包Qt依赖库
7. ✅ 创建ZIP压缩包
8. ✅ 上传供下载

## 🔧 如果推送失败

### 问题：认证错误

**解决方案：**
1. 确保使用Personal Access Token作为密码
2. 或使用SSH方式：
   ```bash
   # 先删除HTTPS远程仓库
   git remote remove origin

   # 添加SSH远程仓库（替换YOUR_USERNAME）
   git remote add origin git@github.com:YOUR_USERNAME/app-manager.git

   # 推送代码
   git push -u origin master
   ```

### 问题：提示仓库不存在

**解决方案：**
1. 确保已在GitHub上创建了仓库
2. 确保仓库名称正确
3. 确保替换了YOUR_USERNAME为你的实际用户名

## 📝 代码更新后如何重新编译

只需提交并推送新代码：

```bash
cd c:\Users\lzs18\IDEProjects\app

# 添加修改的文件
git add .

# 提交更改
git commit -m "Update code"

# 推送到GitHub（会自动触发编译）
git push
```

## 🎯 快速参考

### 常用Git命令

```bash
# 查看状态
git status

# 查看提交历史
git log

# 查看远程仓库
git remote -v

# 强制推送（慎用）
git push -f origin master
```

### GitHub仓库地址格式

```
HTTPS: https://github.com/YOUR_USERNAME/REPO_NAME.git
SSH:   git@github.com:YOUR_USERNAME/REPO_NAME.git
```

## 🆘 需要帮助？

1. **查看详细指南**：`GITHUB_SETUP.md`
2. **查看项目说明**：`README.md`
3. **查看快速开始**：`QUICKSTART.md`

---

**准备好了吗？开始第1步吧！** 🚀

创建GitHub仓库，然后执行第3步的推送命令，几分钟后就能下载编译好的程序了！
