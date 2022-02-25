#ifndef ROLLPITCH_H
#define ROLLPITCH_H

#include "widgetslib_global.h"
#include <QWidget>

/*!
 * \brief 俯仰滚转仪表
 */
class WIDGETSLIB_EXPORT RollPitch : public QWidget
{
    Q_OBJECT
public:
    explicit RollPitch(QWidget *parent = nullptr);
    void setUavID(int id);
    int ID();
    void setRoll(float roll);
    void setPitch(float pitch);
    void doubleClick();
    void setChecked(bool checked);
    void setCheckable(bool able);
    void setRollPrecision(int prec);
    void setPitchPrecision(int prec);
    void setPrecision(int prec);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void checked();

public slots:
private:
    int m_id;
    float m_roll;
    float m_pitch;
    bool m_isCheckable;
    bool m_isChecked;

private:
    int m_rollPrecision;
    int m_pitchPrecision;
};

#endif // ROLLPITCH_H
