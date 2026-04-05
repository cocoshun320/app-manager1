#include "BasePage.h"

BasePage::BasePage(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
{
    m_layout->setContentsMargins(10, 10, 10, 10);
    m_layout->setSpacing(10);
}

BasePage::~BasePage()
{
}
