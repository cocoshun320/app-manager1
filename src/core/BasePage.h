#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>
#include <QVBoxLayout>

/**
 * @brief 页面基类
 *
 * 所有功能页面的基类，定义页面生命周期接口
 */
class BasePage : public QWidget
{
    Q_OBJECT

public:
    explicit BasePage(QWidget *parent = nullptr);
    virtual ~BasePage();

    /**
     * @brief 页面进入时调用
     */
    virtual void onPageEnter() = 0;

    /**
     * @brief 页面离开时调用
     */
    virtual void onPageLeave() = 0;

    /**
     * @brief 初始化页面
     */
    virtual void initialize() = 0;

protected:
    QVBoxLayout *m_layout; ///< 主布局
};

#endif // BASEPAGE_H
