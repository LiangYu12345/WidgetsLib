#ifndef POLYGONTABLEWIDGET_H
#define POLYGONTABLEWIDGET_H

#include "tablewidget.h"

class WIDGETSLIB_EXPORT PolygonTableWidget : public TableWidget
{
public:
    PolygonTableWidget(QWidget * parent = nullptr);
    PolygonTableWidget(int row,int column,QWidget * parent = nullptr);
private:
    void Init();
};

#endif // POLYGONTABLEWIDGET_H
