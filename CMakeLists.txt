cmake_minimum_required(VERSION 3.20)
project(AppManager VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 查找Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 查找OpenSSL
find_package(OpenSSL REQUIRED)

# 启用自动MOC、UIC、RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 源文件
set(SOURCES
    src/main.cpp
    src/core/MainWindow.cpp
    src/core/BasePage.cpp
    src/modules/AppManager.cpp
    src/modules/LogManager.cpp
    src/modules/RegistryAccessor.cpp
    src/modules/PrivilegeManager.cpp
    src/modules/LanguageManager.cpp
    src/modules/URLManager.cpp
    src/modules/AuthManager.cpp
    src/pages/AppManagementPage.cpp
    src/pages/LanguagePage.cpp
    src/pages/URLManagementPage.cpp
    src/pages/SecurityPage.cpp
    src/pages/LoginDialog.cpp
)

# 头文件
set(HEADERS
    src/core/MainWindow.h
    src/core/BasePage.h
    src/modules/AppManager.h
    src/modules/LogManager.h
    src/modules/RegistryAccessor.h
    src/modules/PrivilegeManager.h
    src/modules/LanguageManager.h
    src/modules/URLManager.h
    src/modules/AuthManager.h
    src/pages/AppManagementPage.h
    src/pages/LanguagePage.h
    src/pages/URLManagementPage.h
    src/pages/SecurityPage.h
    src/pages/LoginDialog.h
)

# 资源文件
set(RESOURCES
    resources/resources.qrc
)

# 创建可执行文件
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# 链接Qt库
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    OpenSSL::SSL
    OpenSSL::Crypto
)

# 设置应用程序属性
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
    )
endif()

# 安装规则
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
