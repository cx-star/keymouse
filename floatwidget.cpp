#include <QPainter>
#include <QPalette>
#include <QMouseEvent>
#include "floatwidget.h"

FloatWidget::FloatWidget(QString disText, QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(windowFlags()
                   |Qt::FramelessWindowHint //去边框
                   |Qt::WindowStaysOnTopHint
                    );
    setWindowState(Qt::WindowNoState //不激活
                   );

    this->setWindowOpacity(0.7);
    resize(30,30);

    m_disText = disText;
}
QString FloatWidget::disText() const
{
    return m_disText;
}

void FloatWidget::setDisText(const QString &disText)
{
    m_disText = disText;
    update();
}


void FloatWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setFont(QFont("Times", 30));
    painter.drawText(0,0,this->width(),this->height(), Qt::AlignCenter, m_disText);
}
//void FloatWidget::mousePressEvent(QMouseEvent *event){
//   this->windowPos = this->pos();
//   this->mousePos = event->globalPos();
//   this->dPos = mousePos - windowPos;
// }
// void FloatWidget::mouseMoveEvent(QMouseEvent *event){
//   this->move(event->globalPos() - this->dPos);
//}
