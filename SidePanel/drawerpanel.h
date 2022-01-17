#ifndef DRAWERPANEL_H
#define DRAWERPANEL_H
#include "widgetslib_global.h"

#include <QWidget>
#include <QToolButton>
#include <QPropertyAnimation>

/*!
 * \brief 带按钮的抽屉式侧边栏
 * \note 拖拽按钮为QToolButton
 */
class WIDGETSLIB_EXPORT DrawerPanel : public QWidget
{
    Q_OBJECT
public:
    explicit DrawerPanel(QWidget *parent = nullptr);

    /// 设置对齐位置和对齐方向
    void setAlignment(const QPoint &pos, Qt::Alignment align);
    /// 设置拉手文字
    void setText(const QString &text);
    /// 设置拉手图标
    void setIcon(const QIcon &icon);
    /// 设置内容控件
    void setContent(QWidget *widget);
    /// 展开
    void open();
    /// 合上
    void close();
    /// 切换开合状态
    void toggle();

public:
    virtual QSize sizeHint() const override;

signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QPoint computePos(bool open, Qt::Alignment align);
    void updateLayout();


private:
    // Internal
    bool          m_isOpened;
    QPoint        m_basePos;    ///< 抽屉屋位置
    Qt::Alignment m_align;
    QToolButton  *m_button;
    QPropertyAnimation *m_anim;

    // External
    QWidget *m_content;
};

#endif // DRAWERPANEL_H
