#ifndef DRAGBUTTON_H
#define DRAGBUTTON_H

#include <QPushButton>

class DragButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DragButton(QWidget *parent = nullptr);
    explicit DragButton(const QString &text, QWidget *parent = nullptr);
    explicit DragButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;


private:
    QPoint m_dragStartPosition;

};

#endif // DRAGBUTTON_H
