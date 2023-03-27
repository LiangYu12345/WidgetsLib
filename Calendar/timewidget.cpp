#include "timewidget.h"
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QOpenGLWidget>
#include <QtMath>

TimeWidget::TimeWidget(QWidget *parent)
    : QWidget{parent}
{
    Init();
    InitConnect();
}

TimeWidget::~TimeWidget()
{
    m_timer->stop();

    disconnect(m_timer, &QTimer::timeout, this, &TimeWidget::update);
    disconnect(this, &TimeWidget::sigTimeChanged, this, &TimeWidget::updateDis);

    delete m_timer;
}

void TimeWidget::setSecondValue(const int &second)
{
    if(m_secondValue == second)
        return;
    m_secondValue = second;
}

void TimeWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    int radius = qMin(width(), height());

    QPainter painter(this);

    painter.save();

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(radius / 300, radius / 300);

    painter.setPen(m_minuteColor);
    for (int j = 0; j < 60; ++j) {  //循环60次，绘制表盘
        if ((j % 5) != 0)           //判断是否能被5整除
            painter.drawLine(0, -92, 0, -96);  //不是正点刻度，绘制长4个像素的直线
        painter.rotate(6.0);   //循环60次，每次旋转6度
    }
    painter.setPen(m_hourColor);    //下面画表示小时的刻度，此时要用到画笔（因为要划线）
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(0, -88, 0, -96);     //写上刻度数字
        if (i == 0)  painter.drawText(-10,-88,20,20,Qt::AlignHCenter | Qt::AlignTop,QString::number(12));
        else  painter.drawText(-10,-88,20,20,Qt::AlignHCenter | Qt::AlignTop,QString::number(i));
        painter.rotate(30.0);
    }

    painter.setPen(Qt::black);
    QTime time(0,0,0);
    QString timeStr= time.addSecs(m_secondValue).toString();
    painter.drawText(-40, 30, 80, 30, Qt::AlignHCenter | Qt::AlignTop, timeStr);

    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0,0), 2, 2);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    painter.drawEllipse(QPoint(0,0), 97, 97);

    painter.restore();
}

void TimeWidget::Init()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->start();

    m_hours.append({0, 48});
    m_hours.append({8, 48});
    m_hours.append({4, 0});

    m_minutes.append({0, 78});
    m_minutes.append({8, 78});
    m_minutes.append({4, 0});

    m_seconds.append({0, 98});
    m_seconds.append({8, 98});
    m_seconds.append({4, 0});


    m_hourColor = QColor(127, 0, 127);
    m_minuteColor = QColor(0, 127, 127, 191);
    m_secondColor = QColor(127, 127, 0, 127);

    // 添加graphics场景作为时针的旋转
    m_scene = new QGraphicsScene;
    m_scene->setSceneRect(0, 0, 300, 300);
    m_hourHand = new TimeHand();
    m_minuteHand = new TimeHand();
    m_secondHand = new TimeHand();

    m_hourHand->setHandColor(m_hourColor);
    m_minuteHand->setHandColor(m_minuteColor);
    m_secondHand->setHandColor(m_secondColor);

    m_hourHand->setHandPoints(m_hours);
    m_minuteHand->setHandPoints(m_minutes);
    m_secondHand->setHandPoints(m_seconds);

    m_Label = new QLabel("AM", this);
    m_Label->setGeometry(300 - m_Label->width() / 2, 60 - m_Label->height(), 30 , 20);
    m_Label->setFont(QFont("微软雅黑", 12, QFont::Thin, Qt::blue));

    m_scene->addItem(m_hourHand);
    m_scene->addItem(m_minuteHand);
    m_scene->addItem(m_secondHand);

    auto view = new QGraphicsView(this);
    view->setScene(m_scene);

    //view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));  /// 初步考虑时，没使用OpenGL绘制 背景问题将会覆盖表盘。
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setRenderHint(QPainter::Antialiasing);
    view->setGeometry(0, 0, 300, 300);
    view->setStyleSheet("background: transparent; border:0px");
    //
    m_hourHand->show();
    m_minuteHand->show();
    m_secondHand->show();

    this->setGeometry(0, 0, 300, 300);

    /// 使其三个指针同步在同一的旋转中心点
    m_hourHand->setPos(150 - m_hourHand->boundingRect().width() / 2, 150 - m_hourHand->boundingRect().height() * 4 / 5);
    m_minuteHand->setPos(150 - m_minuteHand->boundingRect().width() / 2, 150 - m_minuteHand->boundingRect().height() * 4 / 5);
    m_secondHand->setPos(150 - m_secondHand->boundingRect().width() / 2, 150 - m_secondHand->boundingRect().height() * 4 / 5);

    detectionTime(m_secondValue / 3600 % 24);
}

void TimeWidget::InitConnect()
{
    connect(m_timer, &QTimer::timeout, this, &TimeWidget::update);
    connect(this, &TimeWidget::sigTimeChanged, this, &TimeWidget::updateDis);

    connect(m_hourHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onHourHandChanged);
    connect(m_minuteHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onMinuteHandChanged);
    connect(m_secondHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onSecondHandChanged);
}

void TimeWidget::update()
{
    m_secondValue ++;
    setS(m_secondValue);
}

void TimeWidget::detectionTime(const int &hour)
{
    if(hour >= 12){
        m_Label->setText("PM");
    }
    else{
        m_Label->setText("AM");
    }
}

void TimeWidget::setS(int second)
{
   m_secondValue = second;
   emit sigTimeChanged(m_secondValue);
}

void TimeWidget::setDragModel(bool isDrag)
{
    if(m_isDrop == isDrag)
        return;
    m_isDrop = isDrag;

    if(isDrag){
        connect(m_hourHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onHourHandChanged);
        connect(m_minuteHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onMinuteHandChanged);
        connect(m_secondHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onSecondHandChanged);
    }
    else{
        disconnect(m_hourHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onHourHandChanged);
        disconnect(m_minuteHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onMinuteHandChanged);
        disconnect(m_secondHand, &TimeHand::mouseMoveAngle, this, &TimeWidget::onSecondHandChanged);
    }
}

void TimeWidget::updateDis(double second)
{
    m_secondHand->setRotation(second * 6);
    m_minuteHand->setRotation((second / 60.0) * 6);
    m_hourHand->setRotation((second / 3600.0) * 30);

    auto hour = m_secondValue / 3600 % 24;
    detectionTime(hour);
}

void TimeWidget::onSecondHandChanged(int angle)
{
    m_timer->stop();
    auto rotateH = m_hourHand->rotation();
    auto rotateM = m_minuteHand->rotation() - qFloor(m_minuteHand->rotation()/360) * 360;
    auto rotateS = m_secondHand->rotation() - qFloor(m_secondHand->rotation()/360) * 360;

    auto value = qFloor(rotateH / 30.0) * 3600
            + qFloor(rotateM / 6) * 60
            + (rotateS+angle)/6;

    setS(value);
    m_timer->start();
}

void TimeWidget::onMinuteHandChanged(int angle)
{
    m_timer->stop();
    auto rotateH = m_hourHand->rotation();
    auto rotateM = m_minuteHand->rotation() - qFloor(m_minuteHand->rotation()/360) * 360;

    auto value = qFloor(rotateH / 30.0) * 3600
            +(rotateM+angle) / 6 * 60;
    setS(value);
    m_timer->start();
}

void TimeWidget::onHourHandChanged(int angle)
{
    m_timer->stop();
    auto rotateH = m_hourHand->rotation();
    auto value = (rotateH+angle) / 30.0 * 3600;
    setS(value);
    m_timer->start();
}
