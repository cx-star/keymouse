#ifndef STATESETTINGDIALOG_H
#define STATESETTINGDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class StateSettingDialog;
}

class StateSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StateSettingDialog(QWidget *parent = 0);
    ~StateSettingDialog();

private slots:
    void on_buttonBox_accepted();

    void on_pushButtonColor_clicked();

    void on_pushButtonFont_clicked();

private:
    Ui::StateSettingDialog *ui;
    QSettings *setting;
    QFont font;
    QColor color;
    double opacity;
    bool translucentBackground;
    void updateDisplay();
};

#endif // STATESETTINGDIALOG_H
