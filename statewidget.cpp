#include "statewidget.h"

StateWidget::StateWidget(QWidget *parent) :
    QTextBrowser(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(windowFlags()
                   |Qt::FramelessWindowHint //去边框
                   |Qt::WindowStaysOnTopHint
                    );
    setWindowState(Qt::WindowNoState //不激活
                   );

    this->setWindowOpacity(0.5);
}

StateWidget::~StateWidget()
{

}
