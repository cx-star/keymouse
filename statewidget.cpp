#include <QFont>
#include <QFontDialog>
#include <QSettings>
#include <QCoreApplication>
#include "statewidget.h"

void StateWidget::updateDiaplay()
{
    QSettings setting(QCoreApplication::applicationDirPath()+"setting.ini",QSettings::IniFormat);

    setting.beginGroup("StateSettingDialog");
    QPalette palette;
    palette.setColor(QPalette::WindowText,setting.value("color").value<QColor>());
    this->setPalette(palette);

    this->setFont(setting.value("font").value<QFont>());

    this->setWindowOpacity(setting.value("opacity").toDouble());

    //    Indicates that the widget should have a translucent background,
    //    i.e., any non-opaque regions of the widgets will be translucent
    //    because the widget will have an alpha channel.
    //    Setting this flag causes WA_NoSystemBackground to be set.
    //    On Windows the widget also needs the Qt::FramelessWindowHint window flag to be set.
    //    This flag is set or cleared by the widget's author.
    if(setting.value("translucentBackground").toBool()){
        setAttribute(Qt::WA_TranslucentBackground,true);
    }
    else
    {
        setAttribute(Qt::WA_TranslucentBackground,false);
    }
    setting.endGroup();
}

StateWidget::StateWidget(QWidget *parent) :
    QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(windowFlags()
                   |Qt::FramelessWindowHint //去边框
                   |Qt::WindowStaysOnTopHint
                   |Qt::Tool                //无状态栏
                    );
    setWindowState(Qt::WindowNoState); //不激活

    updateDiaplay();
}



StateWidget::~StateWidget()
{

}
