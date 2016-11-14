#include <MyGlobalShortCut/MyWinEventFilter.h>
#include <MyGlobalShortCut/MyGlobalShortCut.h>

MyWinEventFilter::~MyWinEventFilter()
{

}

MyWinEventFilter::MyWinEventFilter(MyGlobalShortCut *shortcut)
    : m_shortcut(shortcut)
{

}

//This method is called for every native event.
//typedef struct tagMSG {
//  HWND hwnd;
//  UINT message;
//  WPARAM wParam;
//  LPARAM lParam;
//  DWORD time;
//  POINT pt;
//} MSG,*PMSG,*NPMSG,*LPMSG;
bool MyWinEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
   if(eventType == "windows_generic_MSG")
    {
        MSG *msg = static_cast<MSG *>(message);
        if(msg->message == WM_HOTKEY)
        {
//            if(msg->wParam == VK_F10)
//            {
//               m_shortcut->activateShortcut();
//               return true;
//            }
            const quint32 keycode = HIWORD(msg->lParam);
            const quint32 modifiers = LOWORD(msg->lParam);
            bool res = m_shortcut->shortcuts.value(qMakePair(keycode, modifiers));
            if(res)
            {
                m_shortcut ->activateShortcut();
                return true;
            }
        }

    }
    return false;
}
