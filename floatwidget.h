#ifndef FLOATWIDGET_H
#define FLOATWIDGET_H

#include <QWidget>

class FloatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FloatWidget(QString disText,QWidget *parent = 0);

    QString disText() const;
    void setDisText(const QString &disText);

private:
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QString m_disText;
signals:

public slots:

protected:
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
};

#endif // FLOATWIDGET_H
