#include <QDebug>
#include <QPoint>
#include "windows.h"
#include "hookfunction.h"

HHOOK mouseHook=NULL;
//鼠标钩子过程
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    static PMSLLHOOKSTRUCT mouseHookStruct;
    if(nCode == HC_ACTION){
        mouseHookStruct=(PMSLLHOOKSTRUCT)lParam;
        if (wParam==WM_LBUTTONDOWN){
            HookFunction::getInstance()->emitMouseSignal(QPoint(mouseHookStruct->pt.x,mouseHookStruct->pt.y),MouseAction_LBUTTONDOWN);
            //qDebug()<<"WM_LBUTTONDOWN:"<<mouseHookStruct->pt.x<<","<<mouseHookStruct->pt.y;
            //qDebug()<<"WM_LBUTTONDOWN";
        }else if(wParam==WM_RBUTTONDOWN){
            HookFunction::getInstance()->emitMouseSignal(QPoint(mouseHookStruct->pt.x,mouseHookStruct->pt.y),MouseAction_RBUTTONDOWN);
        }
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
//卸载钩子
void unHook()
{
    UnhookWindowsHookEx(mouseHook);
}
//安装钩子,调用该函数即安装钩子
void setHook()
{
    //底层鼠标钩子
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
}

HookFunction::HookFunction()
{
    setHook();
}

void HookFunction::emitMouseSignal(const QPoint &point, MouseActionType type)
{
    emit mouseAction(point,type);
}

HookFunction* HookFunction::instance = NULL;
HookFunction *HookFunction::getInstance()
{
    if(instance==NULL){
        instance = new HookFunction;
    }
    return instance;
}

HookFunction::~HookFunction()
{
    unHook();
}

