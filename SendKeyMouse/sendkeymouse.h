#ifndef SENDKEYMOUSE_H
#define SENDKEYMOUSE_H

#include <QObject>
#include <QPoint>

class SendKeyMouse : public QObject
{
    Q_OBJECT
public:
    explicit SendKeyMouse(QObject *parent = 0);

    QPoint getMousePoint(void);
    void mouse_left(int x, int y);
    void mouse_right(int x, int y);
    void sendKey(Qt::Key key);
    void sendKey(Qt::Key key1, Qt::Key key2);


    void sendKeyDown(Qt::Key key1);
    void sendKeyUp(Qt::Key key1);

signals:

public slots:

};

#endif // SENDKEYMOUSE_H
