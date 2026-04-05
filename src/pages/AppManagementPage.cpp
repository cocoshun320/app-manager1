#include "AppManagementPage.h"
#include "../modules/AppManager.h"
#include "../modules/LogManager.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QApplication>

AppManagementPage::AppManagementPage(QWidget *parent)
    : BasePage(parent)
    , m_appTable(nullptr)
    , m_cleanupRegistryCheckbox(nullptr)
    , m_progressBar(nullptr)
    , m_statusLabel(nullptr)
    , m_refreshButton(nullptr)
    , m_uninstallButton(nullptr)
    , m_selectAllButton(nullptr)
    , m_deselectAllButton(nullptr)
{
}

AppManagementPage::~AppManagementPage()
{
}

void AppManagementPage::onPageEnter()
{
    loadApplications();
}

void AppManagementPage::onPageLeave()
{
}

void AppManagementPage::initialize()
{
    setupUI();
    loadApplications();
}

void AppManagementPage::setupUI()
{
    // 创建刷新和选择按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_refreshButton = new QPushButton("刷新", this);
    m_selectAllButton = new QPushButton("全选", this);
    m_deselectAllButton = new QPushButton("取消全选", this);

    buttonLayout->addWidget(m_refreshButton);
    buttonLayout->addWidget(m_selectAllButton);
    buttonLayout->addWidget(m_deselectAllButton);
    buttonLayout->addStretch();

    // 创建应用程序表格
    m_appTable = new QTableWidget(this);
    m_appTable->setColumnCount(4);
    m_appTable->setHorizontalHeaderLabels({"选择", "名称", "版本", "发布者"});
    m_appTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_appTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_appTable->horizontalHeader()->setStretchLastSection(true);
    m_appTable->verticalHeader()->setVisible(false);

    // 创建注册表清理复选框
    m_cleanupRegistryCheckbox = new QCheckBox("清理注册表", this);

    // 创建卸载按钮
    m_uninstallButton = new QPushButton("卸载选中应用", this);

    // 创建进度条和状态标签
    m_progressBar = new QProgressBar(this);
    m_progressBar->setVisible(false);

    m_statusLabel = new QLabel("就绪", this);

    // 添加到布局
    m_layout->addLayout(buttonLayout);
    m_layout->addWidget(m_appTable);
    m_layout->addWidget(m_cleanupRegistryCheckbox);
    m_layout->addWidget(m_uninstallButton);
    m_layout->addWidget(m_progressBar);
    m_layout->addWidget(m_statusLabel);

    // 连接信号槽
    connect(m_refreshButton, &QPushButton::clicked, this, &AppManagementPage::onRefreshClicked);
    connect(m_uninstallButton, &QPushButton::clicked, this, &AppManagementPage::onUninstallClicked);
    connect(m_selectAllButton, &QPushButton::clicked, this, &AppManagementPage::onSelectAllClicked);
    connect(m_deselectAllButton, &QPushButton::clicked, this, &AppManagementPage::onDeselectAllClicked);
}

void AppManagementPage::loadApplications()
{
    m_appTable->setRowCount(0);
    m_statusLabel->setText("正在扫描应用程序...");
    QApplication::processEvents();

    std::vector<ApplicationInfo> apps = AppManager::enumerateApplications();

    m_appTable->setRowCount(apps.size());

    for (size_t i = 0; i < apps.size(); ++i) {
        const ApplicationInfo& app = apps[i];

        // 复选框
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(Qt::Unchecked);
        m_appTable->setItem(i, 0, checkItem);

        // 名称
        m_appTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(app.name)));

        // 版本
        m_appTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(app.version)));

        // 发布者
        m_appTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(app.publisher)));
    }

    m_statusLabel->setText(QString("共找到 %1 个应用程序").arg(apps.size()));
}

void AppManagementPage::onRefreshClicked()
{
    loadApplications();
}

void AppManagementPage::onUninstallClicked()
{
    std::vector<ApplicationInfo> selectedApps;

    for (int i = 0; i < m_appTable->rowCount(); ++i) {
        QTableWidgetItem *checkItem = m_appTable->item(i, 0);
        if (checkItem && checkItem->checkState() == Qt::Checked) {
            ApplicationInfo app;
            app.name = m_appTable->item(i, 1)->text().toStdString();
            app.version = m_appTable->item(i, 2)->text().toStdString();
            app.publisher = m_appTable->item(i, 3)->text().toStdString();
            selectedApps.push_back(app);
        }
    }

    if (selectedApps.empty()) {
        QMessageBox::warning(this, "提示", "请先选择要卸载的应用程序");
        return;
    }

    QString message = QString("确定要卸载选中的 %1 个应用程序吗？").arg(selectedApps.size());
    if (QMessageBox::question(this, "确认卸载", message) != QMessageBox::Yes) {
        return;
    }

    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, selectedApps.size());
    m_statusLabel->setText("正在卸载...");

    bool cleanupRegistry = m_cleanupRegistryCheckbox->isChecked();

    for (size_t i = 0; i < selectedApps.size(); ++i) {
        const ApplicationInfo& app = selectedApps[i];
        m_statusLabel->setText(QString("正在卸载: %1").arg(QString::fromStdString(app.name)));

        if (AppManager::uninstallApplication(app)) {
            if (cleanupRegistry) {
                AppManager::cleanupRegistry(app.name);
            }
        }

        m_progressBar->setValue(i + 1);
        QApplication::processEvents();
    }

    m_statusLabel->setText("卸载完成");
    m_progressBar->setVisible(false);

    loadApplications();
}

void AppManagementPage::onSelectAllClicked()
{
    for (int i = 0; i < m_appTable->rowCount(); ++i) {
        QTableWidgetItem *checkItem = m_appTable->item(i, 0);
        if (checkItem) {
            checkItem->setCheckState(Qt::Checked);
        }
    }
}

void AppManagementPage::onDeselectAllClicked()
{
    for (int i = 0; i < m_appTable->rowCount(); ++i) {
        QTableWidgetItem *checkItem = m_appTable->item(i, 0);
        if (checkItem) {
            checkItem->setCheckState(Qt::Unchecked);
        }
    }
}
