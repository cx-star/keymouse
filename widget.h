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
	void sendText(QString s);
protected:
	void run();
signals:
    void setClip(QString s);
private:
    QString encodeArrowNum(const QString s);
    int findNotNum(const QString s, int start);
    int findNum(const QString s, int start);
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QClipboard *m_clipboard;
private slots:
    void setClip(QString s);
    void shortcut_t_slot(QString);

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

protected:
    void closeEvent(QCloseEvent *event);
private:
	Ui::Widget *ui;

	ProcessThread* m_thread;
    SendKeyMouse *sendKeyMouse;

	QStringListModel *modelCmd;

	void insertCmdModelData(QString s);

	QStringList cmdLines;
	QStringList getCmdByShortCut(QString shortcutName);
	void createCMDLines(bool isIni,QString shortcutName);

	int totalSteps,currentStep;

    QString IniPath;
    void readIniToView(QString fileName);
    void writeViewToIni(QString fileName);

	void doCmd(bool isIni, QString shortcutName=QString());
    bool oneStepIsEnd;
    QString currentStepName;

    FloatWidget *mouseFloat;

	QTimer *m_StepTimer;

};

#endif // WIDGET_H
