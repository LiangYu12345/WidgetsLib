#ifndef MULTILELISTVIEW_H
#define MULTILELISTVIEW_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>

class WIDGETSLIB_EXPORT MultileListView : public QWidget
{
    Q_OBJECT
public:
    explicit MultileListView(QWidget * parent = nullptr);
signals:
    void ItemClicked();
protected:
    void mousePressEvent(QMouseEvent *e) override;
private:

};

#endif // MULTILELISTVIEW_H
