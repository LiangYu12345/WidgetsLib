#ifndef WAYPOINTTABLEWIDGET_H
#define WAYPOINTTABLEWIDGET_H

#include "tablewidget.h"

class WIDGETSLIB_EXPORT WaypointTableWidget : public TableWidget
{
public:
    WaypointTableWidget(QWidget * parent = nullptr);
    WaypointTableWidget(int row,int column,QWidget * parent = nullptr);

    virtual QSize sizeHint() const override;
private:
    void Init();
};

#endif // WAYPOINTTABLEWIDGET_H
