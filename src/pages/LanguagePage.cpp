#include "LanguagePage.h"
#include "../modules/LanguageManager.h"
#include "../modules/LogManager.h"
#include <QMessageBox>
#include <QApplication>

LanguagePage::LanguagePage(QWidget *parent)
    : BasePage(parent)
    , m_languageList(nullptr)
    , m_installButton(nullptr)
    , m_progressBar(nullptr)
    , m_statusLabel(nullptr)
{
}

LanguagePage::~LanguagePage()
{
}

void LanguagePage::onPageEnter()
{
    loadLanguages();
}

void LanguagePage::onPageLeave()
{
}

void LanguagePage::initialize()
{
    setupUI();
    loadLanguages();
}

void LanguagePage::setupUI()
{
    // 创建语言列表
    m_languageList = new QListWidget(this);

    // 创建安装按钮
    m_installButton = new QPushButton("安装语言包", this);

    // 创建进度条和状态标签
    m_progressBar = new QProgressBar(this);
    m_progressBar->setVisible(false);

    m_statusLabel = new QLabel("就绪", this);

    // 添加到布局
    m_layout->addWidget(m_languageList);
    m_layout->addWidget(m_installButton);
    m_layout->addWidget(m_progressBar);
    m_layout->addWidget(m_statusLabel);

    // 连接信号槽
    connect(m_installButton, &QPushButton::clicked, this, &LanguagePage::onInstallClicked);
}

void LanguagePage::loadLanguages()
{
    m_languageList->clear();
    m_statusLabel->setText("正在加载语言列表...");
    QApplication::processEvents();

    std::vector<LanguageInfo> languages = LanguageManager::getAvailableLanguages();

    for (const auto& lang : languages) {
        QString itemText = QString::fromStdString(lang.name);
        if (lang.installed) {
            itemText += " (已安装)";
        }
        m_languageList->addItem(itemText);
    }

    m_statusLabel->setText(QString("共 %1 个语言包").arg(languages.size()));
}

void LanguagePage::onInstallClicked()
{
    QListWidgetItem *currentItem = m_languageList->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "提示", "请先选择要安装的语言包");
        return;
    }

    std::vector<LanguageInfo> languages = LanguageManager::getAvailableLanguages();
    if (languages.empty()) {
        QMessageBox::warning(this, "提示", "没有可用的语言包");
        return;
    }

    const LanguageInfo& lang = languages[0];  // 目前只有英语（美国）

    if (lang.installed) {
        QMessageBox::information(this, "提示", "该语言包已安装");
        return;
    }

    QString message = QString("确定要安装 %1 语言包吗？").arg(QString::fromStdString(lang.name));
    if (QMessageBox::question(this, "确认安装", message) != QMessageBox::Yes) {
        return;
    }

    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 100);
    m_statusLabel->setText("正在安装语言包...");

    m_progressBar->setValue(30);
    QApplication::processEvents();

    if (LanguageManager::installLanguagePackage(lang.code)) {
        m_progressBar->setValue(70);
        QApplication::processEvents();

        if (LanguageManager::switchSystemLanguage(lang.code)) {
            m_progressBar->setValue(100);
            m_statusLabel->setText("语言包安装成功");

            QMessageBox::information(this, "成功", "语言包安装成功！\n请重启计算机以应用更改。");

            loadLanguages();
        } else {
            m_statusLabel->setText("语言切换失败");
            QMessageBox::warning(this, "警告", "语言包安装成功，但语言切换失败");
        }
    } else {
        m_statusLabel->setText("语言包安装失败");
        QMessageBox::warning(this, "警告", "语言包安装失败");
    }

    m_progressBar->setVisible(false);
}
