#ifndef AREAINFORMATIONDISPLAY_H
#define AREAINFORMATIONDISPLAY_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class WIDGETSLIB_EXPORT AreaInformationDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit AreaInformationDisplay(QWidget *parent = nullptr);

    void addItem(int Index, const QString &name, const QString &value);
    void appendItem(const QString &name, const QString &value);
    void removeItem(int Index);
    void changeItem(int Index, const QString &name, const QString &value);
    void changeItemVal(int Index, const QString &value);
signals:

private:
    QGridLayout * m_gLayout;

    QLabel * m_numberLabelKey;
    QLabel * m_numberLabelVal;
    QLabel * m_nameLabelKey;
    QLabel * m_nameLabelVal;
};

#endif // AREAINFORMATIONDISPLAY_H
