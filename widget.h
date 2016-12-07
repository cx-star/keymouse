#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QShortcut>
#include <SendKeyMouse/sendkeymouse.h>
#include <QStringListModel>
#include <QThread>
#include <QTableWidget>
#include <QClipboard>
#include "floatwidget.h"
#include "statewidget.h"
#include "hookfunction.h"

namespace Ui {
class Widget;
}

class ProcessThread : public QThread
{
    Q_OBJECT
public:
    ProcessThread();

	QStringList m_lines;
	QTableWidget *m_table;
    SendKeyMouse *m_sendKeyMouse;

	void processCMD(QString s);
	void processCMD(QStringList list);
	void mouseClick(int x, int y);
    void sendText(const QString& s);
protected:
	void run();
signals:
    void setClip(const QString& s);
    void currentProcessCmd(const QString& s);
private:
    QString encodeArrowNum(const QString& s);
    int findNotNum(const QString& s, int start);
    int findNum(const QString& s, int start);
    void resizeQString(QString &s, int size);
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void setClip(QString s);
    void shortcut_t_slot(QString key);

    void currentProcessCmd(const QString& s);

    void button_mouseClick(MouseActionType type);
    void button_mouseClick();
    void button_sendCmdText();
    void button_sendArrow();
    void button_sendDelay();
	void button_delCmdText();
	void button_AddDiyText();
	void button_delDiyText();
	void button_addDiyToCmd();
	void button_saveIni();
	void button_saveDiy();
	void comboBox_diy_changed();

    void iniChanged(QString s);

    void checkBox_oneStep();

    void checkBox_StaysOnTop();
    void spinBox_Opacity();
    void checkBox_FloatWidget();

    void currentItemChanged(const QModelIndex & current, const QModelIndex &);

	void checkBox_timer();
	void stepTimer_timerout();
	void setCheckBoxTimer();

    void on_checkBoxAutoMouse_clicked(bool checked);
    void AutoMouse_clicked(QPoint point, MouseActionType type);

    void ClipboardChanged(QClipboard::Mode mode);

    void on_pushButtonMouseLR_clicked();
    void on_pushButtonCLeanCmdText_clicked();

    void on_pushButtonCleanDiyText_clicked();

    void on_lineEditCmdText_returnPressed();

    void on_lineEditArrow_returnPressed();

    void on_lineEditDiyText_returnPressed();

    void on_pushButtonShowHelp_clicked();

    void on_checkBoxStateWidget_clicked(bool checked);

    void on_pushButtonStateSetting_clicked();

protected:
    void closeEvent(QCloseEvent *event);
private:
	Ui::Widget *ui;

    QClipboard *m_clipboard;
    SendKeyMouse *sendKeyMouse;

	QStringListModel *modelCmd;
    void insertCmdModelData(const QString &s);

    QStringList cmdLines;
	void createCMDLines(bool isIni,QString shortcutName);

    QString IniPath;
    void readIniToView(const QString& m_fileName);
    void writeViewToIni(const QString& fileName);

    void doCmd(bool isIni, const QString& shortcutName=QString());
    bool oneStepIsEnd;
    QString currentStepName;
    int totalSteps,currentStep;
    QString thisClipboardText;
    ProcessThread* m_thread;

    FloatWidget *mouseFloat;
    StateWidget *stateWidget;

	QTimer *m_StepTimer;

};

#endif // WIDGET_H
