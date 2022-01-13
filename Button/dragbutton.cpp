#include "dragbutton.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

DragButton::DragButton(QWidget *parent) : QPushButton{parent}
{

}

DragButton::DragButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{

}

DragButton::DragButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton(icon, text, parent)
{

}

void DragButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_dragStartPosition = event->pos();
}

void DragButton::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton) ||
            (event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}
