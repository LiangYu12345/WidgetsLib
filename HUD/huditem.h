#ifndef HUDITEM_H
#define HUDITEM_H

#include "widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class Crosshair : public QGraphicsItem
{
public:
    Crosshair();
    /// LMC is indicated on the corsshair by perpendicular lines
    void setLMC(bool ready);
    /// 设置右横条下的文字
    void setText(const QString &text);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float   m_len = 150;
    bool    m_lmc = true;
    QString m_text = "-";
};

/*!
 * \brief The YawIndicator class
 */
class YawIndicator : public QGraphicsItem
{
public:
    YawIndicator();
    /// 设置跨度
    void setRange(float range);
    /// 设置中心数值
    void setValue(float value);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 15;
    float m_value = 180;
    const float m_pixPerDegree = 40;
    const float m_lineHeight = 20;
    const float m_textHeight = 22;
};


/*!
 * \brief The SpeedIndicator class
 */
class SpeedIndicator : public QGraphicsItem
{
public:
    SpeedIndicator();
    /// 设置跨度
    void setRange(float range);
    /// 设置中心数值
    void setValue(float value);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 200;
    float m_value = 0;
    const float m_pixPerDegree = 2;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};

/*!
 * \brief The SpeedIndicator class
 */
class AltitudeIndicator : public QGraphicsItem
{
public:
    AltitudeIndicator();
    /// 设置跨度
    void setRange(float range);
    /// 设置中心数值
    void setValue(float value);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 400;
    float m_value = 0;
    const float m_pixPerDegree = 1;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};

/*!
 * \brief The RollIndicator class
 */
class RollIndicator : public QGraphicsItem
{
public:
    RollIndicator();
    /// 设置跨度
    void setRange(float range);
    /// 设置中心数值
    void setValue(float value);
    /// 设置圆环半径
    void setRadius(float radius);
    const float &radius() const;

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 80;
    float m_value = 0;
    float m_radius = 400;
    const float m_lineLen = 20;
    const float m_textWidth = 22;
};

/*!
 * \brief The LabelIndicator class
 */
class LabelIndicator : public QGraphicsItem
{
public:
    LabelIndicator();
    /// 设置大小
    void setSize(const QSizeF &size);
    /// 设置文字
    void setText(const QString &text);
    /// 设置箭头指示符号显示对齐位置 (目前只做了朝下)
    void setArrowAlignment(Qt::Alignment align);
    /// 设置箭头指示符号显示与否
    void setArrowVisible(bool on);
    /// 设置边框
    void setBorder(const QPen &pen);
    /// 设置背景
    void setBrush(const QBrush &brush);
    /// 设置文字字体
    void setFont(const QFont &font);
    /// 设置文字颜色
    void setPen(const QPen &pen);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSizeF        m_size={50, 20}; /// 仅表示矩形框大小
    QString       m_text;
    Qt::Alignment m_arrowAlign = Qt::AlignBottom;
    bool          m_arrowVisible = false;
    //
    QPen   m_borderPen = QPen(Qt::white, 2);
    QPen   m_textPen = QPen(Qt::green);
    QBrush m_brush = QBrush(Qt::black);
    QFont  m_font  = QFont("Microsoft Yahei", 12);
};

/*!
 * \brief The FOVIndicator class
 */
class FOVIndicator : public QGraphicsItem
{
public:
    FOVIndicator();
    /*!
     * \brief 设置视场角总挡位
     * \param level
     * 1: NFOV for SWIR
     * 3: WFOV/MFOV/NFOV for MWIR
     * 4: WFOV/MFOV/NFOV/SNFOV for TV
     */
    void setLevel(int level);
    /// 设置视场角
    void setFov(float degree);
    /// 设置大小
    void setSize(const QSizeF &size);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSizeF m_size = {80, 60};
    //
    int   m_level = 4;
    int   m_fovLevel = 1;
    float m_fov = 60;
};

/*!
 * \brief The ProgressIndicator class
 * \details 进度条，可用作增益条、视场条
 * \note 该元素的大小会影响到布局方向，默认为100*16的水平布局
 */
class ProgressIndicator : public QGraphicsItem
{
public:
    ProgressIndicator();
    /// 设置范围
    void setRange(float min, float max);
    /// 设置值
    void setValue(float value);
    /// 设置大小
    void setSize(const QSizeF &size);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSizeF m_size = {100, 16};
    //
    float m_min = 0;
    float m_max = 90;
    float m_value = 30;
};

/*!
 * \brief EO Azimuth
 */
class AZIndicator : public QGraphicsItem
{
public:
    AZIndicator();
    /// 设置角度
    void setValue(float degree);
    /// 设置半径
    void setRadius(float radius);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_radius = 45;
    float m_value = 0;
};

/*!
 * \brief The ELIndicator class
 */
class ELIndicator : public QGraphicsItem
{
public:
    ELIndicator();
    /// 设置值域范围
    void setRange(float min, float max);
    /// 设置角度
    void setValue(float degree);
    /// 设置尺寸
    void setSize(const QSizeF &size);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSizeF m_size = {30, 90};
    const float m_hLineRatio = 0.5f;
    const float m_hSpaceRatio = 0.1f;
    const float m_hRectRatio = 0.4f;
    //
    float  m_min = -90;
    float  m_max = 90;
    float  m_value = 0;
};

/*!
 * \brief The NorthIndicator class
 */
class NorthIndicator : public QGraphicsItem
{
public:
    NorthIndicator();
    /// 设置角度
    void setValue(float degree);
    /// 设置偏离半径
    void setRadius(float radius);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    void doTransform();

private:
    float m_value = 0;
    float m_radius = 120;
};

/*!
 * \brief The TrackIndicator class
 */
class TrackIndicator : public QGraphicsItem
{
public:
    TrackIndicator();
    /// 设置尺寸
    void setSize(const QSizeF &size);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSizeF m_size = {12, 24};
};

/*!
 * \brief The TrimIndicator class
 */
class SwitchIndicator : public QGraphicsObject
{
public:
    SwitchIndicator();
    /// 设置尺寸
    void setSize(const QSizeF &size);
    /// 触发显示方框(闪烁多次)
    void triggerRect();
    /// 触发显示重定位方框(闪烁一次)
    void triggerRetrack();

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSizeF m_size = {70, 70};
    //
    bool m_showRect = false;
    bool m_showRetrack = false;
};

/*!
 * \brief The PreTrackIndicator class
 * \note 显示一个X表示上一次的跟踪位置
 */
class PreTrackIndicator : public QGraphicsItem
{
public:
    PreTrackIndicator();
    /// 设置尺寸
    void setSize(const QSizeF &size);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSizeF m_size = {30, 30};
};

class LaserIndicator : public QGraphicsObject
{
public:
    LaserIndicator();
    /// 设置尺寸
    void setLen(float len);
    /// 触发闪烁显示 参数为0时永久闪烁
    void trigger(int timeoutSecond = 0);
    /// 手动停止显示
    void stop();

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    float m_len = 10;
    //
    QTimer m_timer;
};

#endif // HUDITEM_H
