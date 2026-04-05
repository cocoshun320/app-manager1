; NSIS 安装包脚本
; 用于创建应用程序的安装程序

!define PRODUCT_NAME "应用程序管理工具"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "MyCompany"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\AppManager.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"

; 包含现代UI
!include "MUI2.nsh"

; 安装程序属性
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "AppManager_Setup.exe"
InstallDir "$PROGRAMFILES64\AppManager"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

; 设置压缩
SetCompressor lzma

; 现代UI设置
!define MUI_ABORTWARNING
!define MUI_ICON "resources\icons\app.ico"
!define MUI_UNICON "resources\icons\app.ico"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "resources\icons\header.bmp"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!insertmacro MUI_PAGE_LICENSE "LICENSE.txt"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装进度页面
!insertmacro MUI_PAGE_INSTFILES
; 完成页面
!insertmacro MUI_PAGE_FINISH

; 卸载程序页面
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; 语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "English"

; 安装部分
Section "主程序" SecMain
  SectionIn RO

  SetOutPath "$INSTDIR"

  ; 复制主程序文件
  File "build\bin\Release\AppManager.exe"
  File "build\bin\Release\*.dll"

  ; 复制Qt插件
  CreateDirectory "$INSTDIR\platforms"
  File /r "build\bin\Release\platforms\*.*"

  CreateDirectory "$INSTDIR\imageformats"
  File /r "build\bin\Release\imageformats\*.*"

  CreateDirectory "$INSTDIR\styles"
  File /r "build\bin\Release\styles\*.*"

  ; 创建快捷方式
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\AppManager.exe"
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\AppManager.exe"

  ; 写入注册表
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\AppManager.exe"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "DisplayName" "${PRODUCT_NAME}"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\AppManager.exe"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegDWORD HKLM "${PRODUCT_UNINST_KEY}" "NoModify" 1
  WriteRegDWORD HKLM "${PRODUCT_UNINST_KEY}" "NoRepair" 1

  ; 创建卸载程序
  WriteUninstaller "$INSTDIR\uninst.exe"
SectionEnd

; 卸载部分
Section Uninstall
  ; 删除文件
  Delete "$INSTDIR\AppManager.exe"
  Delete "$INSTDIR\*.dll"
  Delete "$INSTDIR\uninst.exe"

  ; 删除目录
  RMDir /r "$INSTDIR\platforms"
  RMDir /r "$INSTDIR\imageformats"
  RMDir /r "$INSTDIR\styles"
  RMDir "$INSTDIR"

  ; 删除快捷方式
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk"
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
  RMDir "$SMPROGRAMS\${PRODUCT_NAME}"

  ; 删除注册表
  DeleteRegKey HKLM "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
SectionEnd
