#include "calendarwidght.h"
#include <QHBoxLayout>
#include <QLocale>
#include <QTextCharFormat>
#include <QMouseEvent>

class CalendarStyle : public QProxyStyle
{
public:
    CalendarStyle(QWidget *parent){
        setParent(parent);
    };
private:
    void drawPrimitive(PrimitiveElement e, const QStyleOption *o,
                       QPainter *p, const QWidget *w) const
    {
        if(e == PE_FrameFocusRect){
            return ;
        }
        QProxyStyle::drawPrimitive(e, o, p, w);
    }
};

CalendarWidght::CalendarWidght(QWidget *parent)
    : QCalendarWidget(parent)
{
    Init();
    InitConnect();
}

void CalendarWidght::setCalendarValue(QDate &date)
{
    if(m_date == date)
        return;
    m_date = date;

    setDataLabelText(date.year(), date.month());
    m_month = date.month();
}

void CalendarWidght::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if(date == selectedDate()){
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(QColor(0, 145, 255));
        painter->drawRoundRect(rect.x() + 1, rect.y() + 2, rect.width() - 2, rect.height() - 4, 2, 2);
        painter->setPen(QColor(255, 255, 255));
        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->restore();
    }
    else if(date == m_date){
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 161, 255));
        painter->drawRoundRect(rect.x() + 1, rect.y() + 2, rect.width() - 2, rect.height() - 4, 2, 2);
        painter->setPen(QColor(255, 255, 255));
        painter->setBrush(QColor(0, 161, 255));
        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->restore();
    }
    else if(date < minimumDate() || date > maximumDate()){
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setPen(QColor(220, 220, 220));
        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->restore();
    }
    else{
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        QFont font = painter->font();
        painter->setFont(font);
        painter->setPen(QColor(0, 0, 0));
        if(date.month() != m_month){
            painter->setPen(QColor(145, 145, 145));
        }
        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->restore();
    }
}

void CalendarWidght::Init()
{
    setLocale(QLocale::Chinese);
    setNavigationBarVisible(false);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    setStyle(new CalendarStyle(this));

    QTextCharFormat format;
    format.setForeground(QColor(0, 0, 0));
    format.setBackground(QColor(255, 255, 255));
    setHeaderTextFormat(format);
    setWeekdayTextFormat(Qt::Saturday, format);
    setWeekdayTextFormat(Qt::Sunday, format);
    setWeekdayTextFormat(Qt::Monday, format);
    setWeekdayTextFormat(Qt::Tuesday, format);
    setWeekdayTextFormat(Qt::Wednesday, format);
    setWeekdayTextFormat(Qt::Thursday, format);
    setWeekdayTextFormat(Qt::Friday, format);

    QWidget *top = new QWidget(this);
    auto hlayout = new QHBoxLayout;

    m_leftYearBtn = new QPushButton(u8"<<");
    m_leftMonthBtn = new QPushButton(u8"<");
    m_dataLabel = new QLabel;
    m_rightYearBtn = new QPushButton(u8">>");
    m_rightMonthBtn = new QPushButton(u8">");

    hlayout->addWidget(m_leftYearBtn);
    hlayout->addWidget(m_leftMonthBtn);
    hlayout->addStretch();
    hlayout->addWidget(m_dataLabel);
    hlayout->addStretch();
    hlayout->addWidget(m_rightMonthBtn);
    hlayout->addWidget(m_rightYearBtn);

    hlayout->setContentsMargins(12, 0, 12, 0);
    hlayout->setSpacing(6);
    top->setLayout(hlayout);

    QWidget *bottom = new QWidget(this);
    auto bhlayout = new QHBoxLayout;
    m_sureBtn = new QPushButton(u8"确认");
    m_cancelBtn = new QPushButton(u8"取消");

    bhlayout->addWidget(m_sureBtn);
    bhlayout->addStretch();
    bhlayout->addWidget(m_cancelBtn);
    bhlayout->setContentsMargins(12, 0, 12, 0);
    bhlayout->setSpacing(6);
    bottom->setLayout(bhlayout);

    this->setStyleSheet("QWidget{background: transparent; color: #000000; boder: 1px solid #dadde3; font-size:20px;"
                       "font-family:Microsoft YaHei; background-color: rgb(255, 255, 255);}");

    auto vBodyLayout = qobject_cast<QVBoxLayout *>(layout());
    vBodyLayout->insertWidget(0, top);
    vBodyLayout->addWidget(bottom);
}

void CalendarWidght::InitConnect()
{
    connect(m_leftYearBtn, &QPushButton::clicked, this, &QCalendarWidget::showPreviousYear);
    connect(m_leftMonthBtn, &QPushButton::clicked, this, &QCalendarWidget::showPreviousMonth);
    connect(m_rightYearBtn, &QPushButton::clicked, this, &QCalendarWidget::showNextYear);
    connect(m_rightMonthBtn, &QPushButton::clicked, this, &QCalendarWidget::showNextMonth);

    connect(this, &QCalendarWidget::currentPageChanged, [this](int year, int month){
        setDataLabelText(year, month);
        m_month = month;
    });

    connect(this, &QCalendarWidget::clicked, [this](QDate date){
        m_date = date;

        setDataLabelText(date.year(), date.month());
        m_month = date.month();
        emit calendarCellClicked(date);
    });

    connect(m_sureBtn, &QPushButton::clicked, [=](){
        emit calendarSureBtnClicked(m_date);
    });
    connect(m_cancelBtn, &QPushButton::clicked, [=](){
        emit calendarCancelBtnClicked();
    });
}

void CalendarWidght::setDataLabelText(const int year, const int month)
{
    m_dataLabel->setText(QString(u8"%1年%2月").arg(year).arg(month));
}
