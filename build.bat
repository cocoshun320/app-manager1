@echo off
echo ===== C++ 应用程序管理工具 - 编译脚本 =====
echo.

REM 检查CMake是否安装
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [错误] 未找到CMake，请先安装CMake
    echo 下载地址: https://cmake.org/download/
    pause
    exit /b 1
)

REM 检查Qt是否安装
if not exist "C:\Qt" (
    echo [警告] 未在C:\Qt找到Qt安装
    echo 请确保已安装Qt 6.x并配置了环境变量
    pause
)

echo [1/4] 创建build目录...
if not exist build mkdir build

echo [2/4] 运行CMake配置...
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
if %ERRORLEVEL% NEQ 0 (
    echo [错误] CMake配置失败
    pause
    exit /b 1
)

echo [3/4] 编译项目 (Release模式)...
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo [错误] 编译失败
    pause
    exit /b 1
)

echo [4/4] 打包依赖库...
cd bin\Release
windeployqt AppManager.exe
if %ERRORLEVEL% NEQ 0 (
    echo [警告] windeployqt执行失败，可能需要手动打包Qt依赖
)

echo.
echo ===== 编译完成 =====
echo 可执行文件位置: %CD%\AppManager.exe
echo.

pause
