#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include <QTextBrowser>
namespace Ui {
class StateWidget;
}

class StateWidget : public QTextBrowser
{
    Q_OBJECT

public:
    explicit StateWidget(QWidget *parent = 0);
    ~StateWidget();

private:
    Ui::StateWidget *ui;
};

#endif // STATEWIDGET_H
