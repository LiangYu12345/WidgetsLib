#include "dragbutton.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QDebug>

DragButton::DragButton(QWidget *parent) : QPushButton(parent)
{
    m_actions = Qt::CopyAction;
}

DragButton::DragButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    m_actions = Qt::CopyAction;
}

DragButton::DragButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton(icon, text, parent)
{
    m_actions = Qt::CopyAction;
}

void DragButton::setDragIcon(const QPixmap &icon)
{
    m_icon = icon;
}

void DragButton::setMimeData(const QMimeData &mime)
{
    copyMimeData(mime, m_mime);
}

QMimeData &DragButton::mimeData()
{
    return m_mime;
}

void DragButton::setDropAction(Qt::DropActions supportedActions)
{
    m_actions = supportedActions;
}

void DragButton::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
        m_dragStartPosition = event->pos();
}

void DragButton::mouseMoveEvent(QMouseEvent *event)
{
    QPushButton::mouseMoveEvent(event);
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;
    //
    // TODO: QDrag must be constructed on the heap
    // and QMimeData as well
    auto drag = new QDrag(this);
    drag->setPixmap(m_icon);
    drag->setHotSpot({m_icon.width()/2, m_icon.height()/2});
    auto mime = new QMimeData;
    copyMimeData(m_mime, *mime);
    drag->setMimeData(mime);

    //
    auto dropAction = drag->exec(m_actions);
    emit dragged(dropAction);
}

void DragButton::copyMimeData(const QMimeData &src, QMimeData &dst)
{
    dst.clear();
    const auto formats = src.formats();
    for(const QString &format : formats) {
        // Retrieving data
        QByteArray data = src.data(format);
        dst.setData(format, data);
    }
}
