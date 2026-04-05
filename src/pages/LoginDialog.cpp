#include "LoginDialog.h"
#include "../modules/AuthManager.h"
#include "../modules/LogManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , m_usernameEdit(nullptr)
    , m_passwordEdit(nullptr)
    , m_loginButton(nullptr)
    , m_cancelButton(nullptr)
    , m_statusLabel(nullptr)
{
    setWindowTitle("安全页面 - 登录");
    setModal(true);
    setFixedSize(350, 250);

    setupUI();
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建表单布局
    QFormLayout *formLayout = new QFormLayout();

    // 用户名输入框
    m_usernameEdit = new QLineEdit(this);
    m_usernameEdit->setPlaceholderText("请输入用户名");
    formLayout->addRow("用户名:", m_usernameEdit);

    // 密码输入框
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText("请输入密码");
    formLayout->addRow("密码:", m_passwordEdit);

    mainLayout->addLayout(formLayout);

    // 状态标签
    m_statusLabel = new QLabel("", this);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_statusLabel->setStyleSheet("QLabel { color: red; }");
    mainLayout->addWidget(m_statusLabel);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    m_loginButton = new QPushButton("登录", this);
    m_cancelButton = new QPushButton("取消", this);

    buttonLayout->addWidget(m_loginButton);
    buttonLayout->addWidget(m_cancelButton);

    mainLayout->addLayout(buttonLayout);

    // 连接信号槽
    connect(m_loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &LoginDialog::onCancelClicked);

    // 设置默认按钮
    m_loginButton->setDefault(true);

    // 设置Tab顺序
    setTabOrder(m_usernameEdit, m_passwordEdit);
    setTabOrder(m_passwordEdit, m_loginButton);
    setTabOrder(m_loginButton, m_cancelButton);
}

void LoginDialog::onLoginClicked()
{
    QString username = m_usernameEdit->text();
    QString password = m_passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        m_statusLabel->setText("请输入用户名和密码");
        return;
    }

    if (AuthManager::instance().authenticate(username.toStdString(), password.toStdString())) {
        accept();
    } else {
        m_statusLabel->setText("用户名或密码错误");
        m_passwordEdit->clear();
        m_passwordEdit->setFocus();
    }
}

void LoginDialog::onCancelClicked()
{
    reject();
}
