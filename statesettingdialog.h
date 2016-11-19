#ifndef STATESETTINGDIALOG_H
#define STATESETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class StateSettingDialog;
}

class StateSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StateSettingDialog(QWidget *parent = 0);
    ~StateSettingDialog();

private:
    Ui::StateSettingDialog *ui;
};

#endif // STATESETTINGDIALOG_H
