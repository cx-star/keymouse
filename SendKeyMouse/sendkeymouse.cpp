#include <windows.h>
#include <windef.h>
#include <Winuser.h>
#include "sendkeymouse.h"
#include <MyGlobalShortCut/MyGlobalShortCut.h>
#include <QDebug>

/*
模拟鼠标动作API函数mouse_event，它可以实现模拟鼠标按下和放开等动作。

VOID mouse_event(
DWORD dwFlags, // 鼠标动作标识。
DWORD dx, // 鼠标水平方向位置。
DWORD dy, // 鼠标垂直方向位置。
DWORD dwData, // 鼠标轮子转动的数量。
DWORD dwExtraInfo // 一个关联鼠标动作辅加信息。
);

其中，dwFlags表示了各种各样的鼠标动作和点击活动，它的常用取值如下：

MOUSEEVENTF_MOVE 表示模拟鼠标移动事件。

MOUSEEVENTF_LEFTDOWN 表示模拟按下鼠标左键。

MOUSEEVENTF_LEFTUP 表示模拟放开鼠标左键。

MOUSEEVENTF_RIGHTDOWN 表示模拟按下鼠标右键。

MOUSEEVENTF_RIGHTUP 表示模拟放开鼠标右键。

MOUSEEVENTF_MIDDLEDOWN 表示模拟按下鼠标中键。

MOUSEEVENTF_MIDDLEUP 表示模拟放开鼠标中键。

*/
/*
设置和获取当前鼠标位置的API函数。获取当前鼠标位置使用GetCursorPos()
函数，设置当前鼠标位置使用

SetCursorPos()函数。

BOOL GetCursorPos(
LPPOINT lpPoint // 返回鼠标的当前位置。
);
BOOL SetCursorPos(
int X, // 鼠标的水平方向位置。
int Y //鼠标的垂直方向位置。
);
*/
/*
CPoint oldPoint,newPoint;
GetCursorPos(&oldPoint); //保存当前鼠标位置。
newPoint.x = oldPoint.x+40;
newPoint.y = oldPoint.y+10;
SetCursorPos(newPoint.x,newPoint.y); //设置目的地位置。
mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//模拟按下鼠标右键。
mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//模拟放开鼠标右键。
*/
/*

*/
/*

*/
SendKeyMouse::SendKeyMouse(QObject *parent) :
    QObject(parent)
{
}

QPoint SendKeyMouse::getMousePoint(void)
{
	POINT point;
	LPPOINT pointP = &point;
	GetCursorPos(pointP);
	return QPoint(point.x,point.y);
}

void SendKeyMouse::mouse_left(int x, int y)
{
    SetCursorPos(x,y);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//模拟按下鼠标。
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//模拟放开鼠标。
}

void SendKeyMouse::mouse_right(int x, int y)
{
    SetCursorPos(x,y);
    mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//模拟按下鼠标。
    mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//模拟放开鼠标。
}


/*
VOID keybd_event(
BYTE bVk, // 虚拟键值。
BYTE bScan, // 硬件扫描码。
DWORD dwFlags, // 动作标识。
DWORD dwExtraInfo // 与键盘动作关联的辅加信息。
);

其中，bVk表示虚拟键值，其实它是一个BYTE类型值的宏，其取值范围为1-254。有
关虚拟键值表请在MSDN上使用

关键字“Virtual-Key Codes”查找相关资料。bScan表示当键盘上某键被按下和放开
时，键盘系统硬件产生的扫描码

，我们可以MapVirtualKey()函数在虚拟键值与扫描码之间进行转换。dwFlags表示各种
各样的键盘动作，它有两种取

值：KEYEVENTF_EXTENDEDKEY和KEYEVENTF_KEYUP。

下面我们使用一段代码实现在游戏中按下Shift+R快捷键对攻击对象进行攻击。

keybd_event(VK_CONTROL,MapVirtualKey(VK_CONTROL,0),0,0); //按下CTRL键。
keybd_event(0x52,      MapVirtualKey(0x52,0),      0,0);//键下R键。
keybd_event(0x52,      MapVirtualKey(0x52,0),      KEYEVENTF_KEYUP,0);//放开R键。
keybd_event(VK_CONTROL,MapVirtualKey(VK_CONTROL,0),KEYEVENTF_KEYUP,0);//放开CTRL键。
 **/


void SendKeyMouse::sendKey(Qt::Key key)
{
    quint32 i = MyGlobalShortCut::nativeKeycode(key);
    keybd_event(i,MapVirtualKey(i,0),0,0);
    keybd_event(i,MapVirtualKey(i,0),KEYEVENTF_KEYUP,0);
}

void SendKeyMouse::sendKey(Qt::Key key1, Qt::Key key2)
{
    quint32 i = MyGlobalShortCut::nativeKeycode(key1);
    quint32 j = MyGlobalShortCut::nativeKeycode(key2);
    keybd_event(i,MapVirtualKey(i,0),0,0);
    keybd_event(j,MapVirtualKey(j,0),0,0);
    keybd_event(j,MapVirtualKey(j,0),KEYEVENTF_KEYUP,0);
    keybd_event(i,MapVirtualKey(i,0),KEYEVENTF_KEYUP,0);
}
/*

    keybd_event (VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
    keybd_event ('V', MapVirtualKey('V', 0), 0, 0   );
    keybd_event ('V', MapVirtualKey('V', 0), KEYEVENTF_KEYUP, 0  )  ;
    keybd_event (VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0  ) ;
*/
