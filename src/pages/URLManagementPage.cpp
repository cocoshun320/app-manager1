#include "URLManagementPage.h"
#include "../modules/URLManager.h"
#include "../modules/LogManager.h"

URLManagementPage::URLManagementPage(QWidget *parent)
    : BasePage(parent)
    , m_urlTree(nullptr)
    , m_model(nullptr)
{
}

URLManagementPage::~URLManagementPage()
{
}

void URLManagementPage::onPageEnter()
{
}

void URLManagementPage::onPageLeave()
{
}

void URLManagementPage::initialize()
{
    setupUI();
    loadURLCategories();
}

void URLManagementPage::setupUI()
{
    // 创建树形视图
    m_urlTree = new QTreeView(this);
    m_urlTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_urlTree->setHeaderHidden(true);
    m_urlTree->setExpandsOnDoubleClick(false);

    // 创建模型
    m_model = new QStandardItemModel(this);
    m_urlTree->setModel(m_model);

    // 添加到布局
    m_layout->addWidget(m_urlTree);

    // 连接信号槽
    connect(m_urlTree, &QTreeView::doubleClicked, this, &URLManagementPage::onItemDoubleClicked);
}

void URLManagementPage::loadURLCategories()
{
    m_model->clear();

    std::vector<URLCategory> categories = URLManager::getURLCategories();

    for (const auto& category : categories) {
        // 创建分类项
        QStandardItem *categoryItem = new QStandardItem(QString::fromStdString(category.name));
        categoryItem->setEditable(false);

        // 添加网址项
        for (const auto& url : category.urls) {
            QStandardItem *urlItem = new QStandardItem(QString::fromStdString(url.name));
            urlItem->setEditable(false);
            urlItem->setData(QString::fromStdString(url.url), Qt::UserRole);
            categoryItem->appendRow(urlItem);
        }

        m_model->appendRow(categoryItem);

        // 展开分类
        m_urlTree->expand(categoryItem->index());
    }
}

void URLManagementPage::onItemDoubleClicked(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }

    QStandardItem *item = m_model->itemFromIndex(index);
    if (!item) {
        return;
    }

    // 获取URL数据
    QVariant urlData = item->data(Qt::UserRole);
    if (urlData.isValid()) {
        QString url = urlData.toString();
        if (URLManager::openURL(url.toStdString())) {
            LogManager::instance().info("已打开网址: " + url.toStdString());
        } else {
            LogManager::instance().error("无法打开网址: " + url.toStdString());
        }
    }
}
