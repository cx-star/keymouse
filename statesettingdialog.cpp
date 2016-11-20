#include <QSettings>
#include <QFontDialog>
#include <QColorDialog>
#include <QDebug>
#include "statesettingdialog.h"
#include "ui_statesettingdialog.h"

void StateSettingDialog::updateDisplay()
{
    ui->pushButtonFont->setText(QString("%1%2").arg(font.family()).arg(font.pointSize()));
    ui->pushButtonColor->setStyleSheet(QString("background-color: rgb(%1,%2,%3);")
                                       .arg(color.red()).arg(color.green()).arg(color.blue()));
}

StateSettingDialog::StateSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StateSettingDialog)
{
    ui->setupUi(this);

    setting = new QSettings(QCoreApplication::applicationDirPath()+"setting.ini",QSettings::IniFormat);
    setting->beginGroup("StateSettingDialog");

    font = setting->value("font").value<QFont>();
    color = setting->value("color").value<QColor>();
    opacity = setting->value("opacity").toDouble();
    translucentBackground = setting->value("translucentBackground").toBool();

    updateDisplay();
    ui->doubleSpinBoxOpacity->setValue(opacity);
    ui->checkBoxTranslucent->setChecked(translucentBackground);
}


StateSettingDialog::~StateSettingDialog()
{
    delete ui;
}

void StateSettingDialog::on_buttonBox_accepted()
{
    setting->setValue("font",font);
    setting->setValue("color",color);
    setting->setValue("opacity",ui->doubleSpinBoxOpacity->value());
    setting->setValue("translucentBackground",ui->checkBoxTranslucent->isChecked());
    setting->endGroup();
}

void StateSettingDialog::on_pushButtonColor_clicked()
{
    QColor c = QColorDialog::getColor(color,this,"获取颜色");
    if(c.isValid()){
        color = c;
        updateDisplay();
    }
}

void StateSettingDialog::on_pushButtonFont_clicked()
{
    bool b;
    QFont f = QFontDialog::getFont(&b,font,this);
    if(b){
        font = f;
        updateDisplay();
    }
}
