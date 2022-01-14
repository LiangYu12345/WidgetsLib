#ifndef DRAGBUTTON_H
#define DRAGBUTTON_H

#include "widgetslib_global.h"
#include <QPushButton>
#include <QMimeData>

/*!
 * \brief 可拖拽按钮
 * \details 用于传递拖拽信息
 */
class WIDGETSLIB_EXPORT DragButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DragButton(QWidget *parent = nullptr);
    explicit DragButton(const QString &text, QWidget *parent = nullptr);
    explicit DragButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    ~DragButton(){}

    /// 设置拖拽图标
    void setDragIcon(const QPixmap &icon);
    /// 设置元数据
    void setMimeData(const QMimeData &mime);
    /// 获取元数据
    QMimeData &mimeData();
    /// 设置拖拽行为
    void setDropAction(Qt::DropActions supportedActions = Qt::CopyAction);

signals:
    void dragged(Qt::DropAction action);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    void copyMimeData(const QMimeData &src, QMimeData &dst);

private:
    QPoint     m_dragStartPosition;
    QPixmap    m_icon;
    QMimeData  m_mime;
    Qt::DropActions m_actions;
};

#endif // DRAGBUTTON_H
