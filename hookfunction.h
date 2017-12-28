#ifndef HOOKFUNCTION_H
#define HOOKFUNCTION_H

#include <QObject>
enum MouseActionType{
    MouseAction_LBUTTONDOWN,
    MouseAction_RBUTTONDOWN,
};

class HookFunction : public QObject
{
    Q_OBJECT
public:
    ~HookFunction();
    static HookFunction* getInstance();
    void emitMouseSignal(const QPoint& point,MouseActionType type);//由instance调用，发射mouseAction信号

private:
     HookFunction();
     static HookFunction* instance;
signals:
     void mouseAction(const QPoint& point,MouseActionType);
};

#endif // HOOKFUNCTION_H
