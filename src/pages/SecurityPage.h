#ifndef SECURITYPAGE_H
#define SECURITYPAGE_H

#include "../core/BasePage.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class LoginDialog;

class SecurityPage : public BasePage
{
    Q_OBJECT

public:
    explicit SecurityPage(QWidget *parent = nullptr);
    ~SecurityPage();

    void onPageEnter() override;
    void onPageLeave() override;
    void initialize() override;

private slots:
    void onLogoutClicked();

private:
    void setupUI();
    void checkLoginStatus();

    QLabel *m_welcomeLabel;
    QPushButton *m_logoutButton;
    bool m_authenticated;
};

#endif // SECURITYPAGE_H
