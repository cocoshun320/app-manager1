@echo off
echo ===== 创建安装包 =====
echo.

REM 检查makensis是否安装
where makensis >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [错误] 未找到makensis（NSIS编译器）
    echo 请先安装NSIS: https://nsis.sourceforge.io/
    pause
    exit /b 1
)

REM 检查程序是否已编译
if not exist "build\bin\Release\AppManager.exe" (
    echo [错误] 未找到编译后的程序
    echo 请先运行 build.bat 编译项目
    pause
    exit /b 1
)

echo [1/2] 编译NSIS脚本...
makensis install.nsi
if %ERRORLEVEL% NEQ 0 (
    echo [错误] NSIS脚本编译失败
    pause
    exit /b 1
)

echo [2/2] 安装包创建完成
echo 安装包位置: %CD%\AppManager_Setup.exe
echo.

pause
