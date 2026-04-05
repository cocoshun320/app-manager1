#include "SecurityPage.h"
#include "LoginDialog.h"
#include "../modules/AuthManager.h"
#include "../modules/LogManager.h"

SecurityPage::SecurityPage(QWidget *parent)
    : BasePage(parent)
    , m_welcomeLabel(nullptr)
    , m_logoutButton(nullptr)
    , m_authenticated(false)
{
}

SecurityPage::~SecurityPage()
{
}

void SecurityPage::onPageEnter()
{
    checkLoginStatus();
}

void SecurityPage::onPageLeave()
{
}

void SecurityPage::initialize()
{
    setupUI();
}

void SecurityPage::setupUI()
{
    // 创建欢迎标签
    m_welcomeLabel = new QLabel("安全页面", this);
    m_welcomeLabel->setAlignment(Qt::AlignCenter);
    m_welcomeLabel->setStyleSheet("QLabel { font-size: 24px; font-weight: bold; padding: 20px; }");

    // 创建登出按钮
    m_logoutButton = new QPushButton("退出登录", this);
    m_logoutButton->setVisible(false);

    // 添加到布局
    m_layout->addStretch();
    m_layout->addWidget(m_welcomeLabel);
    m_layout->addWidget(m_logoutButton);
    m_layout->addStretch();

    // 连接信号槽
    connect(m_logoutButton, &QPushButton::clicked, this, &SecurityPage::onLogoutClicked);
}

void SecurityPage::checkLoginStatus()
{
    if (AuthManager::instance().isLoggedIn()) {
        m_authenticated = true;
        m_welcomeLabel->setText("欢迎访问安全页面！\n您已成功通过身份验证。");
        m_logoutButton->setVisible(true);
    } else {
        m_authenticated = false;
        m_welcomeLabel->setText("请登录以访问安全页面");
        m_logoutButton->setVisible(false);

        // 显示登录对话框
        LoginDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            m_authenticated = true;
            m_welcomeLabel->setText("欢迎访问安全页面！\n您已成功通过身份验证。");
            m_logoutButton->setVisible(true);
        } else {
            // 登录失败，返回上一页
            // 这里需要通知主窗口切换页面，暂时先不实现
            m_welcomeLabel->setText("登录失败，无法访问安全页面");
        }
    }
}

void SecurityPage::onLogoutClicked()
{
    AuthManager::instance().logout();
    m_authenticated = false;
    m_welcomeLabel->setText("请登录以访问安全页面");
    m_logoutButton->setVisible(false);
    checkLoginStatus();
}
