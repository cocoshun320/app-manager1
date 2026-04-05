#ifndef URLMANAGEMENTPAGE_H
#define URLMANAGEMENTPAGE_H

#include "../core/BasePage.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <vector>

class URLManagementPage : public BasePage
{
    Q_OBJECT

public:
    explicit URLManagementPage(QWidget *parent = nullptr);
    ~URLManagementPage();

    void onPageEnter() override;
    void onPageLeave() override;
    void initialize() override;

private slots:
    void onItemDoubleClicked(const QModelIndex& index);

private:
    void setupUI();
    void loadURLCategories();

    QTreeView *m_urlTree;
    QStandardItemModel *m_model;
};

#endif // URLMANAGEMENTPAGE_H
