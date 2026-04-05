#include "MainWindow.h"
#include "BasePage.h"
#include "../pages/AppManagementPage.h"
#include "../pages/LanguagePage.h"
#include "../pages/URLManagementPage.h"
#include "../pages/SecurityPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_stackedWidget(nullptr)
    , m_navigationWidget(nullptr)
    , m_opacity(0.85)
{
    setWindowTitle("应用程序管理工具");
    setMinimumSize(1000, 700);
    resize(1200, 800);

    setupUI();
    setupNavigation();
    loadStyleSheet();
    applyTransparency();
    initialize();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initialize()
{
    // 初始化所有页面
    for (auto& page : m_pages) {
        if (page) {
            page->initialize();
        }
    }
}

void MainWindow::switchToPage(int pageIndex)
{
    if (pageIndex < 0 || pageIndex >= static_cast<int>(m_pages.size())) {
        return;
    }

    // 通知当前页面离开
    int currentIndex = m_stackedWidget->currentIndex();
    if (currentIndex >= 0 && currentIndex < static_cast<int>(m_pages.size())) {
        m_pages[currentIndex]->onPageLeave();
    }

    // 切换到新页面
    m_stackedWidget->setCurrentIndex(pageIndex);
    m_navigationWidget->setCurrentIndex(pageIndex);

    // 通知新页面进入
    m_pages[pageIndex]->onPageEnter();
}

void MainWindow::setTransparency(double opacity)
{
    if (opacity < 0.0) opacity = 0.0;
    if (opacity > 1.0) opacity = 1.0;
    m_opacity = opacity;

    applyTransparency();
}

void MainWindow::setupUI()
{
    // 创建中心部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 创建标题栏
    QLabel *titleLabel = new QLabel("应用程序管理工具", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; padding: 10px; }");
    mainLayout->addWidget(titleLabel);

    // 创建页面堆栈
    m_stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(m_stackedWidget, 1);
}

void MainWindow::setupNavigation()
{
    // 创建导航控件
    m_navigationWidget = new QTabWidget(this);
    m_navigationWidget->setTabPosition(QTabWidget::North);
    m_navigationWidget->setStyleSheet("QTabWidget::pane { border: none; }");

    // 创建所有页面
    m_pages.push_back(std::make_unique<AppManagementPage>(this));
    m_pages.push_back(std::make_unique<LanguagePage>(this));
    m_pages.push_back(std::make_unique<URLManagementPage>(this));
    m_pages.push_back(std::make_unique<SecurityPage>(this));

    // 添加页面到堆栈
    for (auto& page : m_pages) {
        m_stackedWidget->addWidget(page.get());
    }

    // 添加导航标签
    m_navigationWidget->addTab(new QWidget(), "应用管理");
    m_navigationWidget->addTab(new QWidget(), "语言设置");
    m_navigationWidget->addTab(new QWidget(), "网址管理");
    m_navigationWidget->addTab(new QWidget(), "安全页面");

    // 连接信号槽
    connect(m_navigationWidget, &QTabWidget::currentChanged,
            this, &MainWindow::onNavigationButtonClicked);

    // 将导航控件添加到主窗口底部
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(m_navigationWidget);
    bottomLayout->setContentsMargins(10, 5, 10, 10);

    QWidget *centralWidget = qobject_cast<QWidget*>(this->centralWidget());
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(centralWidget->layout());
    mainLayout->addLayout(bottomLayout);
}

void MainWindow::loadStyleSheet()
{
    QFile file(":/styles/main.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}

void MainWindow::applyTransparency()
{
    setWindowOpacity(m_opacity);
    setAttribute(Qt::WA_TranslucentBackground);
}

void MainWindow::onNavigationButtonClicked()
{
    int index = m_navigationWidget->currentIndex();
    switchToPage(index);
}
