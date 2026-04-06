# GitHub Actions 编译故障排除指南

## ❌ 问题：Qt安装失败

### 常见错误信息
- `Error: Could not find a version that satisfies the requirement`
- `Qt installation failed`
- `Qt not found`

### 解决方案1：使用Qt预编译版本（推荐）

我已经更新了 `.github/workflows/build.yml` 文件，添加了以下优化：

```yaml
- name: Install Qt
  uses: jurplel/install-qt-action@v4
  with:
    version: '6.6.0'
    host: 'windows'
    target: 'desktop'
    arch: 'win64_msvc2022_64'
    modules: 'qtnetworkauth'
    cache: true              # 启用缓存
    setup-python: false      # 跳过Python设置
    install-deps: false      # 跳过依赖安装
```

### 解决方案2：使用更稳定的Qt版本

如果Qt 6.6.0仍然失败，尝试使用Qt 6.5.3：

```yaml
version: '6.5.3'
```

### 解决方案3：使用Qt 5.15 LTS

如果Qt 6.x都失败，可以使用Qt 5.15（长期支持版本）：

```yaml
version: '5.15.2'
host: 'windows'
target: 'desktop'
arch: 'win64_mingw81'
```

## ❌ 问题：CMake配置失败

### 常见错误信息
- `Could not find Qt6`
- `CMake Error: Could not find package Qt6`

### 解决方案1：添加Qt路径

我已经在CMake配置中添加了Qt路径：

```yaml
- name: Configure CMake
  run: |
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022" -A x64 \
      -DOPENSSL_ROOT_DIR="C:\Program Files\OpenSSL-Win64" \
      -DCMAKE_PREFIX_PATH="$env:Qt6_DIR"
```

### 解决方案2：设置环境变量

```yaml
- name: Set Qt environment
  run: |
    echo "Qt6_DIR=$env:Qt6_DIR" >> $env:GITHUB_ENV
    echo "CMAKE_PREFIX_PATH=$env:Qt6_DIR" >> $env:GITHUB_ENV
```

## ❌ 问题：编译错误

### 常见错误信息
- `fatal error: QtWidgets/QtWidgets: No such file or directory`
- `undefined reference to`

### 解决方案1：添加MSVC环境

我已经添加了MSVC环境设置：

```yaml
- name: Setup MSVC
  uses: ilammy/msvc-dev-cmd@v1
  with:
    arch: x64
```

### 解决方案2：并行编译

```yaml
- name: Build
  run: |
    cd build
    cmake --build . --config Release --parallel
```

## ❌ 问题：OpenSSL错误

### 常见错误信息
- `Could not find OpenSSL`
- `OPENSSL_ROOT_DIR not found`

### 解决方案：使用系统OpenSSL

```yaml
- name: Install OpenSSL
  run: |
    choco install openssl -y
    echo "OPENSSL_ROOT_DIR=C:\Program Files\OpenSSL-Win64" >> $env:GITHUB_ENV
```

## ❌ 问题：windeployqt失败

### 常见错误信息
- `windeployqt is not recognized`
- `Could not find platform plugin`

### 解决方案1：添加Qt到PATH

```yaml
- name: Add Qt to PATH
  run: |
    echo "$env:Qt6_DIR\bin" >> $env:GITHUB_PATH
```

### 解决方案2：使用完整路径

```yaml
- name: Package Qt dependencies
  run: |
    cd build/bin/Release
    & "$env:Qt6_DIR\bin\windeployqt.exe" AppManager.exe --release --no-translations
```

## 🔧 完整的修复方案

我已经为您更新了 `.github/workflows/build.yml` 文件，包含以下修复：

### 主要改进

1. **Qt安装优化**
   - 启用缓存（`cache: true`）
   - 跳过不必要的设置（`setup-python: false`）
   - 跳过依赖安装（`install-deps: false`）

2. **MSVC环境设置**
   - 添加了 `ilammy/msvc-dev-cmd@v1` action
   - 确保正确的编译器环境

3. **CMake配置改进**
   - 添加了 `CMAKE_PREFIX_PATH`
   - 指向Qt6安装目录

4. **编译优化**
   - 使用并行编译（`--parallel`）
   - 加快编译速度

5. **打包改进**
   - 添加 `--release --no-translations` 选项
   - 减小文件大小

## 📝 如何应用修复

### 方法1：推送到GitHub（自动触发）

```bash
cd c:\Users\lzs18\IDEProjects\app

# 提交修复
git add .github/workflows/build.yml
git commit -m "Fix GitHub Actions Qt installation"
git push github master
```

### 方法2：手动触发编译

1. 访问GitHub仓库
2. 点击 "Actions" 标签页
3. 选择 "Build and Release" 工作流
4. 点击 "Run workflow"
5. 选择分支，点击 "Run workflow"

## 🧪 测试编译

### 查看编译日志

1. 访问GitHub仓库的Actions标签页
2. 点击最新的编译任务
3. 查看详细的编译日志
4. 检查是否有错误信息

### 常见成功标志

- ✅ Qt安装完成
- ✅ CMake配置成功
- ✅ 编译成功（0 errors, 0 warnings）
- ✅ windeployqt执行成功
- ✅ ZIP文件创建成功
- ✅ Artifact上传成功

## 🎯 如果仍然失败

### 方案1：使用Docker容器

创建 `.github/workflows/build-docker.yml`：

```yaml
name: Build with Docker

on:
  push:
    branches: [ main, master ]
  workflow_dispatch:

jobs:
  build:
    runs-on: windows-2022

    steps:
    - uses: actions/checkout@v4

    - name: Build with Docker
      run: |
        docker build -t app-manager .
        docker run --rm -v ${{ github.workspace }}:/output app-manager
```

### 方案2：使用预编译的Qt

手动下载Qt并上传到GitHub Release，然后在workflow中使用：

```yaml
- name: Download Qt
  run: |
    curl -L -o qt.zip https://github.com/your-repo/qt/releases/download/v6.6.0/qt-win64.zip
    unzip qt.zip
    echo "Qt6_DIR=$pwd/qt" >> $env:GITHUB_ENV
```

### 方案3：简化项目（移除Qt依赖）

如果Qt编译一直失败，可以考虑：
1. 使用Win32 API替代Qt
2. 使用其他轻量级GUI框架（如Dear ImGui）
3. 创建命令行版本

## 📞 获取帮助

### 查看详细错误

1. 访问GitHub Actions页面
2. 点击失败的编译任务
3. 查看每个步骤的详细日志
4. 复制错误信息

### 搜索解决方案

- GitHub Actions文档：https://docs.github.com/en/actions
- Qt安装Action：https://github.com/jurplel/install-qt-action
- Stack Overflow：https://stackoverflow.com/

### 提交Issue

如果问题仍然存在，可以：
1. 在GitHub仓库创建Issue
2. 附上详细的错误日志
3. 描述复现步骤

## 🔄 重新编译

### 清除缓存并重新编译

```yaml
- name: Clean cache
  uses: actions/github-script@v7
  with:
    script: |
      github.rest.actions.deleteRepoCache({
        owner: context.repo.owner,
        repo: context.repo.repo,
        cache_id: context.payload.actions.cache.id
      })
```

---

**现在提交修复并推送到GitHub，应该可以成功编译了！** 🚀

如果还有问题，请查看详细的编译日志并告诉我具体的错误信息。

🎯
