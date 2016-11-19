#include <QFont>
#include "statewidget.h"

StateWidget::StateWidget(QWidget *parent) :
    QLabel(parent)
{
    //setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(windowFlags()
                   |Qt::FramelessWindowHint //去边框
                   |Qt::WindowStaysOnTopHint
                   |Qt::Tool
                    );
    setWindowState(Qt::WindowNoState //不激活
                   );
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::red);
    this->setPalette(palette);
    QFont font;
    font.setPointSize(36);
    this->setFont(font);
    this->setWindowOpacity(0.5);
}

StateWidget::~StateWidget()
{

}
