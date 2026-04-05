#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <memory>

class BasePage;

/**
 * @brief 主窗口类
 *
 * 管理应用程序的主窗口，包括页面切换、半透明效果等
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief 初始化窗口
     */
    void initialize();

    /**
     * @brief 切换到指定页面
     * @param pageIndex 页面索引
     */
    void switchToPage(int pageIndex);

    /**
     * @brief 设置窗口透明度
     * @param opacity 透明度值 (0.0 - 1.0)
     */
    void setTransparency(double opacity);

private slots:
    /**
     * @brief 导航按钮点击槽函数
     */
    void onNavigationButtonClicked();

private:
    void setupUI();
    void setupNavigation();
    void loadStyleSheet();
    void applyTransparency();

    QStackedWidget *m_stackedWidget; ///< 页面堆栈
    QTabWidget *m_navigationWidget; ///< 导航控件
    std::vector<std::unique_ptr<BasePage>> m_pages; ///< 页面列表
    double m_opacity; ///< 透明度值
};

#endif // MAINWINDOW_H
