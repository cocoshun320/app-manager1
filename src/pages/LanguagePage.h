#ifndef LANGUAGEPAGE_H
#define LANGUAGEPAGE_H

#include "../core/BasePage.h"
#include <QListWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <vector>

class LanguagePage : public BasePage
{
    Q_OBJECT

public:
    explicit LanguagePage(QWidget *parent = nullptr);
    ~LanguagePage();

    void onPageEnter() override;
    void onPageLeave() override;
    void initialize() override;

private slots:
    void onInstallClicked();

private:
    void setupUI();
    void loadLanguages();

    QListWidget *m_languageList;
    QPushButton *m_installButton;
    QProgressBar *m_progressBar;
    QLabel *m_statusLabel;
};

#endif // LANGUAGEPAGE_H
