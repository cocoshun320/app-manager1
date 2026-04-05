#ifndef APPMANAGEMENTPAGE_H
#define APPMANAGEMENTPAGE_H

#include "../core/BasePage.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <vector>

class AppManagementPage : public BasePage
{
    Q_OBJECT

public:
    explicit AppManagementPage(QWidget *parent = nullptr);
    ~AppManagementPage();

    void onPageEnter() override;
    void onPageLeave() override;
    void initialize() override;

private slots:
    void onRefreshClicked();
    void onUninstallClicked();
    void onSelectAllClicked();
    void onDeselectAllClicked();

private:
    void setupUI();
    void loadApplications();

    QTableWidget *m_appTable;
    QCheckBox *m_cleanupRegistryCheckbox;
    QProgressBar *m_progressBar;
    QLabel *m_statusLabel;
    QPushButton *m_refreshButton;
    QPushButton *m_uninstallButton;
    QPushButton *m_selectAllButton;
    QPushButton *m_deselectAllButton;
};

#endif // APPMANAGEMENTPAGE_H
