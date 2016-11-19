#include "statesettingdialog.h"
#include "ui_statesettingdialog.h"

StateSettingDialog::StateSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StateSettingDialog)
{
    ui->setupUi(this);
}

StateSettingDialog::~StateSettingDialog()
{
    delete ui;
}
