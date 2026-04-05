# 🚀 上传代码到Gitee - 只需3步

## ✅ 已完成的工作

我已经为您准备好了：
- ✅ Gitee Actions自动编译配置
- ✅ Git仓库已初始化
- ✅ 代码已提交到本地仓库
- ✅ .gitignore文件已创建

## 📝 接下来的步骤（只需3步）

### 第1步：创建Gitee仓库（1分钟）

1. 访问：https://gitee.com/projects/new
2. 输入仓库名称，例如：`app-manager`
3. 选择 **公开** 或 **私有**
4. **不要**勾选任何选项（README、.gitignore等）
5. 点击 "创建"

### 第2步：设置Gitee账号密码（2分钟）

如果您还没有Gitee账号：
1. 访问：https://gitee.com/signup
2. 注册账号（免费）
3. 登录

设置SSH密钥（推荐）：

**方式1：使用HTTPS（简单）**
- 直接使用Gitee的用户名和密码推送

**方式2：使用SSH（推荐）**
```bash
# 生成SSH密钥
ssh-keygen -t rsa -C "your_email@example.com"

# 查看公钥
cat ~/.ssh/id_rsa.pub
```

1. 复制公钥内容
2. 访问：https://gitee.com/profile/sshkeys
3. 点击 "添加公钥"
4. 粘贴公钥内容
5. 点击 "确定"

### 第3步：推送代码到Gitee（1分钟）

**打开命令提示符**，执行以下命令：

```bash
# 进入项目目录
cd c:\Users\lzs18\IDEProjects\app

# 删除之前的GitHub远程仓库（如果有的话）
git remote remove origin

# 添加Gitee远程仓库（请替换YOUR_USERNAME为你的Gitee用户名）
git remote add origin https://gitee.com/YOUR_USERNAME/app-manager.git

# 推送代码到Gitee
git push -u origin master
```

**系统会提示输入用户名和密码：**
- **用户名**：你的Gitee用户名
- **密码**：你的Gitee密码

**如果使用SSH方式：**
```bash
git remote remove origin
git remote add origin git@gitee.com:YOUR_USERNAME/app-manager.git
git push -u origin master
```

## 🎉 完成！

推送成功后，Gitee会自动触发编译！

### 查看编译进度

1. 访问你的Gitee仓库
2. 点击 "流水线" 标签页
3. 你会看到正在运行的编译任务
4. 编译大约需要5-10分钟

### 下载编译好的程序

1. 等待编译完成（显示绿色✅）
2. 点击最新的编译任务
3. 在 "制品" 部分，下载编译结果

### 使用程序

1. 解压下载的ZIP文件
2. 双击 `AppManager.exe` 运行
3. 默认登录凭据：
   - 用户名：`admin`
   - 密码：`admin123`

## 📊 Gitee vs GitHub

| 特性 | Gitee | GitHub |
|------|-------|--------|
| 速度 | 国内访问快 ⚡ | 国外访问快 🌍 |
| 中文支持 | 完全支持 ✅ | 部分支持 |
| 免费私有仓库 | ✅ 支持 | ✅ 支持 |
| Actions | Gitee Go | GitHub Actions |
| 编译环境 | 国内服务器 | 全球服务器 |

## 🔧 如果推送失败

### 问题：认证错误

**解决方案1：使用HTTPS**
```bash
git remote set-url origin https://gitee.com/YOUR_USERNAME/app-manager.git
git push -u origin master
```

**解决方案2：使用SSH**
```bash
# 检查SSH连接
ssh -T git@gitee.com

# 如果失败，重新添加SSH密钥
```

### 问题：提示仓库不存在

**解决方案：**
1. 确保已在Gitee上创建了仓库
2. 确保仓库名称正确
3. 确保替换了YOUR_USERNAME为你的实际用户名

### 问题：Gitee Go流水线未触发

**解决方案：**
1. 确保仓库中包含 `.gitee/workflows/build.yml` 文件
2. 确保文件路径正确
3. 检查Gitee Go是否已启用（需要申请）

## 📝 代码更新后如何重新编译

只需提交并推送新代码：

```bash
cd c:\Users\lzs18\IDEProjects\app

# 添加修改的文件
git add .

# 提交更改
git commit -m "Update code"

# 推送到Gitee（会自动触发编译）
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

### Gitee仓库地址格式

```
HTTPS: https://gitee.com/YOUR_USERNAME/REPO_NAME.git
SSH:   git@gitee.com:YOUR_USERNAME/REPO_NAME.git
```

## 🆘 需要帮助？

1. **查看详细指南**：`GITHUB_SETUP.md`（配置类似）
2. **查看项目说明**：`README.md`
3. **查看快速开始**：`QUICKSTART.md`
4. **Gitee官方文档**：https://help.gitee.com/

## 💡 提示

- Gitee在国内访问速度更快
- Gitee完全支持中文
- Gitee Go（流水线）需要申请，但通常很快通过
- 如果Gitee Go未开通，可以使用GitHub Actions（代码已配置）

---

**准备好了吗？开始第1步吧！** 🚀

创建Gitee仓库，然后执行第3步的推送命令，几分钟后就能下载编译好的程序了！
