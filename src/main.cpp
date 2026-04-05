#include <QApplication>
#include "core/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("AppManager");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("MyCompany");

    // 创建主窗口
    MainWindow window;
    window.show();

    return app.exec();
}
