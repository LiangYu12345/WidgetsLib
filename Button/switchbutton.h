#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include <QPushButton>
class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    SwitchButton();

signals:
    void checked(bool check);
};

#endif // SWITCHBUTTON_H
