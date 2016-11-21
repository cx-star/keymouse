#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QLabel>
namespace Ui {
class StateWidget;
}

class StateWidget : public QLabel
{
    Q_OBJECT

public:
    explicit StateWidget(QWidget *parent = 0);
    ~StateWidget();
    void updateDisplay();

private:
    Ui::StateWidget *ui;
};

#endif // STATEWIDGET_H
