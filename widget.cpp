#include "widget.h"
#include "ui_widget.h"
#include <QClipboard>
#include <QShortcut>
#include <QDebug>
#include <MyGlobalShortCut/MyGlobalShortCut.h>
#include <SendKeyMouse/sendkeymouse.h>
#include <floatwidget.h>
#include <QStringListModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QClipboard>
#include <QTimer>
#include <QSemaphore>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileSystemModel>
#include <QTimer>
#include <QScrollBar>
#include <QMimeData>
#include <QStringList>
#include <QDesktopWidget>
#include "statesettingdialog.h"

#define VALUEFROMCLIP "valueFromClip"
#define SEPATATOR "#"
//鼠标左键
#define MOUSE_LEFT "M"
#define MOUSE_RIGHT "R"
#define CMD_TEXT "C"
#define DIY_TEXT "D"
#define DIY_NUMBER_ONEBYONE "d"
#define EQUAL_TEXT "E"
#define ArrowTab "A"
#define COPY "F"
#define PASTE "V"
//延时
#define Delay_text "T"
//上下左右UDLR,B=ShiftTab，Z=AltTab
#define ShiftDown s
#define ShiftUp S
//改变自定义文本PQ
#define DIY_INCREASE "P"
#define DIY_DECREASE "Q"

#define ShortCut_Mouse "F6"
#define ShortCut_Go "F7"
#define ShortCut_F6 "F6"
#define ShortCut_F7 "F7"
#define ShortCut_F8 "F8"
#define ShortCut_F9 "F9"
#define ShortCut_F10 "F10"
#define ShortCut_F11 "F11"
#define ShortCut_StopTimer "F11"

QSemaphore sem_OneStep;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
	ui->setupUi(this);
    this->setWindowTitle("星辰自动鼠标键盘");

    //this->setAttribute( Qt::WA_DeleteOnClose);

    m_clipboard = QApplication::clipboard();
    connect(m_clipboard,SIGNAL(changed(QClipboard::Mode)),this,SLOT(ClipboardChanged(QClipboard::Mode)));
//
	m_thread = 0;

//设置当前窗口最前端,透明度
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);
    checkBox_StaysOnTop();
    //this->setWindowFlags (Qt::FramelessWindowHint);
    //透明度
    this->setWindowOpacity((qreal)ui->spinBoxOpacity->value()/100);
    //悬浮窗
    mouseFloat = new FloatWidget("?");
    //状态窗口
    stateWidget = new StateWidget();

    connect(ui->checkBoxStaysOnTop,SIGNAL(clicked()),this,SLOT(checkBox_StaysOnTop()));
    connect(ui->checkBoxFloatWidget,SIGNAL(clicked()),this,SLOT(checkBox_FloatWidget()));
    connect(ui->spinBoxOpacity,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Opacity()));

	//自动批处理listview
	modelCmd = new QStringListModel();
	ui->listViewCmd->setModel (modelCmd);
	//ui->listViewCmd->setEditTriggers (QAbstractItemView::NoEditTriggers);//可编辑注释
    ui->listViewCmd->setSelectionMode (QAbstractItemView::ContiguousSelection);//支持shift
    //改变鼠标预览窗口
    connect(ui->listViewCmd->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(currentItemChanged(QModelIndex,QModelIndex)));

	//需手动输入的窗口tableView
	//ui->tableWidgetDiy->setVerticalHeader (new QHeaderView(Qt::Vertical));

	//按键处理
    //将 鼠标位置 插入 modelCmd
	connect(ui->pushButtonMoveMouseTo,SIGNAL(clicked()),this,SLOT(button_mouseClick()));
    //删除当前选择行
    connect(ui->pushButtonDelCmdText,SIGNAL(clicked()),this,SLOT(button_delCmdText()));
    //将lineEditCmdText（文本内容）内容插入 modelCmd
    connect(ui->pushButtonAddCmdText,SIGNAL(clicked()),this,SLOT(button_sendCmdText()));
    //箭头：左右上下tab
    connect(ui->pushButtonAddArrow,SIGNAL(clicked()),this,SLOT(button_sendArrow()));
    //延时
    connect(ui->pushButtonAddDelay,SIGNAL(clicked()),this,SLOT(button_sendDelay()));
    //增加一行自定义文本
    connect(ui->pushButtonAddDiyText,SIGNAL(clicked()),this,SLOT(button_AddDiyText()));
    //删除 自定义文本 当前行
	connect(ui->pushButtonDelDiyText,SIGNAL(clicked()),this,SLOT(button_delDiyText()));
    //将当前自定义文本加入到命令列中
    connect(ui->pushButtonAddDiyToCmd,SIGNAL(clicked()),this,SLOT(button_addDiyToCmd()));

    connect(ui->pushButtonQuit,SIGNAL(clicked()),this,SLOT(close()));
	connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(button_saveIni()));

	//执行具体操作进程
	totalSteps = 0;
	currentStep = 0;
	m_thread = new ProcessThread();
	connect(m_thread,SIGNAL(setClip(QString)),this,SLOT(setClip(QString)));
    connect(m_thread,SIGNAL(currentProcessCmd(QString)),this,SLOT(currentProcessCmd(QString)));
    connect(m_thread,SIGNAL(OneCmdEnd()),this,SLOT(checkBox_timer()));//进程结束后开启定时器
    m_thread->m_table = ui->tableWidgetDiy;
    sendKeyMouse = new SendKeyMouse();
    m_thread->m_sendKeyMouse = sendKeyMouse;

	//全局快捷键类MyGlobalShortCut测试
	QStringList shortCutList;
    shortCutList<<ShortCut_F6<<ShortCut_F7<<ShortCut_F8<<ShortCut_F9<<ShortCut_F10<<ShortCut_F11;
	foreach(QString s,shortCutList)
	{
		MyGlobalShortCut *shortcut = new MyGlobalShortCut(s,this);
        if(shortcut->registerHotKeyState)
            QObject::connect(shortcut,SIGNAL(activated(QString)),this,SLOT(shortcut_t_slot(QString)));
        else{
            QMessageBox::warning(this,"错误","注册快捷键错误:"+s);
        }
	}

	//不同配置
	QList<QComboBox*> comboBoxList;
	comboBoxList<<ui->comboBoxF8;
	comboBoxList<<ui->comboBoxF9;
	comboBoxList<<ui->comboBoxF10;
    comboBoxList<<ui->comboBoxF11;
	comboBoxList<<ui->comboBoxIni;

	QString applicationDirPath = QCoreApplication::applicationDirPath();
	IniPath = applicationDirPath+"/ini/";

    foreach(QComboBox* box,comboBoxList)//所有combobox设置model
	{
		QFileSystemModel *iniModel = new QFileSystemModel;
		iniModel->setRootPath(IniPath);
		iniModel->setNameFilterDisables (false);
		iniModel->setNameFilters(QStringList()<<"*.ini");
		box->setModel(iniModel);
		box->view()->setRootIndex(iniModel->index(IniPath));
	}
    connect(ui->comboBoxIni,SIGNAL(currentIndexChanged(QString)),this,SLOT(iniChanged(QString)));
    oneStepIsEnd = true;//单步是否结束标志位

    connect(ui->checkBoxOneStep,SIGNAL(clicked()),this,SLOT(checkBox_oneStep()));//单步checkbox

	//diy窗口保存及combobox
	connect(ui->pushButtonSaveDiy,SIGNAL(clicked()),this,SLOT(button_saveDiy()));
	connect(ui->comboBoxDiy,SIGNAL(activated(QString)),this,SLOT(comboBox_diy_changed()));
	QFileSystemModel *diyModel = new QFileSystemModel;
	diyModel->setRootPath(IniPath);
	diyModel->setNameFilterDisables (false);
	diyModel->setNameFilters(QStringList()<<"*.diy");
	ui->comboBoxDiy->setModel(diyModel);
	ui->comboBoxDiy->view()->setRootIndex(diyModel->index(IniPath));

    //初始化 定时器，调用shortcut_t_slot，其中doCMD函数release
	m_StepTimer = new QTimer(this);
	connect(m_StepTimer,SIGNAL(timeout()),this,SLOT(stepTimer_timerout()));
	connect(ui->checkBoxTimer,SIGNAL(clicked()),this,SLOT(checkBox_timer()));
	MyGlobalShortCut *shortcut = new MyGlobalShortCut("Ctrl+t",this);
	connect(shortcut,SIGNAL(activated()),this,SLOT(setCheckBoxTimer()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::setClip(QString s)//设置剪切板，槽函数，在进程里面剪切板出错
{
    m_clipboard->setText (s);
    thisClipboardText = s;
}
//定时器调用 和 响应快捷键
void Widget::shortcut_t_slot(QString key)//所有快捷键处理函数
{
    /*ctrl+t 代替
    if(key == ShortCut_StopTimer){
        ui->checkBoxTimer->setChecked(false);
        m_StepTimer->stop ();
        currentStepName.clear();
        return;
    }*/
    if(!oneStepIsEnd && currentStepName!=key)//单步未完成，按了别的按键
    {
        emit(currentProcessCmd(QString("单步未完成\r\n正在执行%1\r\n当前按键%2").arg(currentStepName).arg(key)));
        return;
    }
    if(key==ShortCut_Mouse) //捕获鼠标位置 F6
    {
        QPoint point = sendKeyMouse->getMousePoint();
        ui->mouseX->setValue(point.x());
        ui->mouseY->setValue(point.y());
        button_mouseClick(MouseAction_LBUTTONDOWN);//将 鼠标位置 插入 modelCmd
        return;
    }
    //新的开始
    currentStepName = key;//当前单步快捷键
    if(key==ShortCut_Go)//执行modelCmd即ini  F7
    {
        doCmd(true);//createCMDLines(bool,key) release(1/all)
    }
    else if(!key.isEmpty())//ShortCut_F8<<ShortCut_F9<<ShortCut_F10)
	{
        doCmd(false,key);//执行非Ini，快捷键为 key
    }
}

void Widget::currentProcessCmd(const QString &s)
{
    stateWidget->setText(s);
    stateWidget->adjustSize();
    QRect rect = QApplication::desktop()->availableGeometry();
    stateWidget->move(rect.width()-stateWidget->width(),rect.height()-stateWidget->height());
}

void Widget::insertCmdModelData(const QString& s)//将s插入modelCmd
{
    int row;
    QModelIndexList list = ui->listViewCmd->selectionModel ()->selectedRows ();
    //当前视图，没有被选中列，则插入到最后一行；有则插入到选择列前
    row = (list.size()==0) ? (modelCmd->rowCount()) :(list.at(0).row());
    modelCmd->insertRow(row);//before the given row
	QModelIndex index = modelCmd->index(row);
	modelCmd->setData(index, s);
    //滚动到最后
    if(list.size()==0){
        QScrollBar* bar = ui->listViewCmd->verticalScrollBar();
        bar->setValue(bar->maximum());
    }
}

void Widget::button_mouseClick(MouseActionType type)//将 鼠标位置 插入 modelCmd
{
	int x = ui->mouseX->value ();
	int y = ui->mouseY->value ();

    QString s = QString("%1%2%3%4%5%6%7")
            .arg(type==MouseAction_LBUTTONDOWN?MOUSE_LEFT:MOUSE_RIGHT).arg (SEPATATOR)
            .arg(x).arg (SEPATATOR)
            .arg (y).arg (SEPATATOR)
            .arg(modelCmd->rowCount());

    insertCmdModelData(s);
}

void Widget::button_mouseClick()
{
    button_mouseClick(MouseAction_LBUTTONDOWN);
}

void Widget::button_sendCmdText()//将lineEditCmdText内容插入 modelCmd
{
	QString s = ui->lineEditCmdText->text ();
	if(s.isEmpty ())
		return;
	s.prepend (SEPATATOR);
	s.prepend (CMD_TEXT);
	s.append (SEPATATOR);

    insertCmdModelData(s);
}

void Widget::button_sendArrow()
{
    QString s = ui->lineEditArrow->text ();
    if(s.isEmpty ())
        return;
    s.prepend (SEPATATOR);
    s.prepend (ArrowTab);
    s.append (SEPATATOR);

    insertCmdModelData(s);
}

void Widget::button_sendDelay()
{
    int delay = ui->spinBoxTimerDelay->value();
    if(delay==0)
        return;
    QString s = QString("%1").arg(delay);
    s.prepend (SEPATATOR);
    s.prepend (Delay_text);
    s.append (SEPATATOR);

    insertCmdModelData(s);
}

void Widget::button_delCmdText()//删除 modelCmd 内容
{
	QModelIndexList list = ui->listViewCmd->selectionModel ()->selectedRows ();
//	foreach(QModelIndex m,list)
//	{
//        qDebug()<<m.row();
    //This is a convenience function that calls removeRows().
    //不知道为什么删除不成功。。。改为removeRows
//		modelCmd->removeRow (m.row ());
//	}
    if(list.size()==0)
        return;
    modelCmd->removeRows(list.at(0).row(),list.size());
}

void Widget::button_AddDiyText()
{
	QString s = ui->lineEditDiyText->text ();
	if(s.isEmpty ())
		return;
	int row = ui->tableWidgetDiy->rowCount ();
	ui->tableWidgetDiy->insertRow (row);
	ui->tableWidgetDiy->setVerticalHeaderItem (row,new QTableWidgetItem(s));
}

void Widget::button_delDiyText()
{
	int row = ui->tableWidgetDiy->currentRow ();
	ui->tableWidgetDiy->removeRow (row);
}

void Widget::button_addDiyToCmd()
{
	int row = ui->tableWidgetDiy->currentRow ();
	if(row==-1)
		return;

	QString s = QString("%1%2%3%4").arg(DIY_TEXT).arg(SEPATATOR).arg(row).arg(SEPATATOR);

    insertCmdModelData(s);
}

void Widget::doCmd(bool isIni, const QString &shortcutName)//isIni shortcutName 参数给greateCMDLines（初始化cmdLines）用
{
    if(ui->checkBoxOneStep->isChecked())//单步执行
    {
        if(oneStepIsEnd)//之前执行的是最后一步
			currentStep = 0;//重新执行
		if(currentStep==0)//单步开始
		{
            if(m_thread->isRunning())
                return;
            createCMDLines(isIni,shortcutName);//cmdLines赋值，根据isIni判断从 快捷键 还是 model
            totalSteps = cmdLines.size();
            if(totalSteps==0)
            {
                QMessageBox::warning(this,"单步执行为空","快捷键列表"+shortcutName+"为空");
                return;
            }
			m_thread->start ();
		}
        currentStep++;
		sem_OneStep.release(1);
        ui->labelState->setText (QString("%4%1%2/%3").arg ("单步:").arg (currentStep).arg (totalSteps).arg(shortcutName));
        oneStepIsEnd = currentStep==totalSteps;//单步执行完毕
    }
    else//非单步执行，一次性执行完
    {
		if(m_thread->isRunning())//批处理操作未结束,按键速度过快
        {
            QMessageBox::warning(this,"按键速度过快","按键速度过快"+shortcutName);
            return;
        }
        createCMDLines(isIni,shortcutName);//cmdLines赋值
        ui->labelState->setText(QString("%1%2").arg(shortcutName).arg("ing"));
        sem_OneStep.release(cmdLines.size());//可以执行所有命令
		m_thread->start ();
    }

}
int ProcessThread::findNum(const QString &s, int start){
    int n = s.size();
    int p = start;
    while(p<n){
        if(s.at(p).isNumber())
            break;
        p++;
    }
    return p==n?-1:p;
}
int ProcessThread::findNotNum(const QString &s, int start){
    int n = s.size();
    int p = start;
    while(p<n){
        if(!s.at(p).isNumber())
            break;
        p++;
    }
    return p==n?-1:p;
}

QString ProcessThread::encodeArrowNum(const QString &s)
{//将方向命令中数字转换成对应方向命令
    QString r;
    int n = s.size();
    if(n<=1){
        qDebug()<<"only one:"<<s;
        return s;
    }
    int i=0;
    while(i<n){//去掉字符串前面数字
        if(s.at(i).isNumber()){
            i++;
            continue;
        }
        else
            break;
    }
    int start=0,end=0;
    while(i<n){
        start = findNum(s,i);
        if(start!=-1){//找到start
            r.append(s.mid(i,start-i-1));//U4:i=0,start=1  增加start前部分
            end = findNotNum(s,start+1);//U12F:i=0,start=1,end=3

            int line = s.mid(start,end==-1?n:end-start).toInt();//取得数字部分
            QTableWidgetItem *item = m_table->item (line,0);//数字对应行
            int l = item==0?0:item->text ().toInt();//行对应数字

            while(l--){
                r.append(s.at(start-1));
            }
            if(end==-1)
                break;
            else
                i=end;
        }
        else//没有找到start，结束
        {
            r.append(s.mid(i,n-i));
            break;
        }
    }
    qDebug()<<"encodeArrowNum"<<r;
    return r;
}

void Widget::button_saveIni()
{
    QString fileName = QFileDialog::getSaveFileName (this,"保存配置",IniPath,"*.ini");
    if(!fileName.endsWith(".ini"))
        fileName.append(".ini");
	writeViewToIni(fileName);
}

void Widget::button_saveDiy()
{//若文件已存在，则会清空原文件
	QString fileName = QFileDialog::getSaveFileName (this,"保存配置",IniPath,"*.diy");
	 if(!fileName.endsWith(".diy"))
		 fileName.append(".diy");
	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);

	int i;
	for(i=0;i<ui->tableWidgetDiy->verticalHeader ()->count ();i++)
		out<<ui->tableWidgetDiy->verticalHeaderItem (i)->text ()<<"\n";
    if(ui->checkBoxClipValue->isChecked()){
        //若“剪切板值”被选中，则增加配置“valueFromClip#1#2
        out<<VALUEFROMCLIP<<SEPATATOR<<ui->spinBoxClipValueStart->value()<<SEPATATOR<<ui->spinBoxClipValueEnd->value();
    }
}

void Widget::comboBox_diy_changed()
{
    //获取当前DIY配置文件
	QString fileName = IniPath+ui->comboBoxDiy->currentText ();
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

    //清空当前视图
	QAbstractItemModel *modelDiy = ui->tableWidgetDiy->model ();
	modelDiy->removeRows (0,modelDiy->rowCount ());
    ui->checkBoxClipValue->setChecked(false);
    ui->spinBoxClipValueEnd->setValue(0);
    ui->spinBoxClipValueStart->setValue(0);

    //读入后，插入视图
	QTextStream in(&file);
	while(!in.atEnd())
	{
		QString s = in.readLine();
		if(s.isEmpty ())
			continue;
        if(s.startsWith(VALUEFROMCLIP)){
            QStringList list = s.split(SEPATATOR);
            if(list.size()>2){
                int start = list.at(1).toInt();
                int end = list.at(2).toInt();
                ui->checkBoxClipValue->setChecked(true);
                ui->spinBoxClipValueEnd->setValue(end);
                ui->spinBoxClipValueStart->setValue(start);
            }
        }else{
            int row = ui->tableWidgetDiy->rowCount ();
            ui->tableWidgetDiy->insertRow (row);
            ui->tableWidgetDiy->setVerticalHeaderItem (row,new QTableWidgetItem(s));
        }
	}
}

void Widget::iniChanged(QString s)
{
    readIniToView(s);
}

void Widget::checkBox_oneStep()
{
    if(!ui->checkBoxOneStep->isChecked() && m_thread->isRunning())//取消选中单步选框，且进程在运行
    {
        m_thread->terminate();
        qDebug()<<"m_thread->wait"<<m_thread->wait();//确定进程被结束
        QMessageBox::warning(this,"结束单步",QString("结束单步%1").arg(m_thread->isRunning()?"失败":"成功"));
        ui->checkBoxOneStep->setChecked(m_thread->isRunning());
        oneStepIsEnd = !m_thread->isRunning();
    }
}

void Widget::checkBox_StaysOnTop()
{
    if(ui->checkBoxStaysOnTop->isChecked())
    {
        //this->hide();
        //qDebug()<<QString("%1").arg(this->windowFlags(),8,16);
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
        //qDebug()<<QString("%1").arg(this->windowFlags(),8,16);
        this->show();
    }
    else
    {
        //this->hide();
        Qt::WindowFlags flags = this->windowFlags();
        //qDebug()<<QString("%1").arg(this->windowFlags(),8,16);
        flags &= ~Qt::WindowStaysOnTopHint;
        this->setWindowFlags(flags);//需重新show
        //qDebug()<<QString("%1").arg(this->windowFlags(),8,16);
        this->show();
    }
}

void Widget::spinBox_Opacity()
{
    this->setWindowOpacity((qreal)ui->spinBoxOpacity->value()/100);
}

void Widget::checkBox_FloatWidget()
{
    if(ui->checkBoxFloatWidget->isChecked()){
        this->mouseFloat->setDisText("?");
        this->mouseFloat->show();
    }
    else{
        this->mouseFloat->hide();
    }
}
//CMD窗口 当前选择项改变，让floatWidget移动
void Widget::currentItemChanged(const QModelIndex &current, const QModelIndex &)
{
    QStringList list = current.data().toString().split(SEPATATOR);

    ui->pushButtonMouseLR->setEnabled(false);
    this->mouseFloat->setDisText("?");
    if(list.size ()<3)
        return;
    if(list.at (0)==MOUSE_LEFT||list.at (0)==MOUSE_RIGHT)
    {
        this->mouseFloat->setDisText(list.at (0)==MOUSE_LEFT?"L":"R");
        this->mouseFloat->move(list.at (1).toInt ()-this->mouseFloat->height()/2,
                                list.at (2).toInt ()-this->mouseFloat->width()/2);
        ui->pushButtonMouseLR->setEnabled(true);
    }
}
//定时器选框 开启或关闭 定时器
void Widget::checkBox_timer()
{
    if(ui->checkBoxTimer->isChecked ())//定时选框 选中
	{
        m_StepTimer->start (ui->spinBoxTimer->value ());
	}
	else
	{
		m_StepTimer->stop ();
	}
}
//定时器超时处理函数：在单步状态下，调用shortcut_t_slot
void Widget::stepTimer_timerout()
{
    //没有勾选”单步“则什么都不做
	if(!ui->checkBoxOneStep->isChecked ())
		return;
    m_StepTimer->stop();//停止定时器，进程结束后开启
	//进程执行一圈后，会退出，不能在此作为判断依据
//	if(!m_thread->isRunning ())
//		return;
    shortcut_t_slot(currentStepName);//快捷键处理函数
}

void Widget::setCheckBoxTimer()
{
	qDebug()<<"setCheckBoxTimer";
	//ui->checkBoxTimer->setChecked (!ui->checkBoxTimer->isChecked ());
	ui->checkBoxTimer->click ();
}

//将table或其他ini 中的 命令 转换成 QStringList
//根据isIni判断 命令行是 从文件 还是 当前活动列表
void Widget::createCMDLines(bool isIni, QString shortcutName)
{
	cmdLines.clear ();
	if(isIni)
	{
        cmdLines = modelCmd->stringList();
	}
	else
	{
        QComboBox *comboBox;
        if(shortcutName==ShortCut_F8)
            comboBox = ui->comboBoxF8;
        else if(shortcutName==ShortCut_F9)
            comboBox = ui->comboBoxF9;
        else if(shortcutName==ShortCut_F10)
            comboBox = ui->comboBoxF10;
        else if(shortcutName==ShortCut_F11)
            comboBox = ui->comboBoxF11;
        else
            return;

        QString fileName = IniPath+comboBox->currentText ();

        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this,"快捷键没有配置文件","快捷键"+shortcutName+"没有配置文件");
            return;
        }

        QTextStream in(&file);
        while(!in.atEnd())
        {
            cmdLines<<in.readLine();
        }
	}
	m_thread->m_lines = cmdLines;
}

void Widget::readIniToView(const QString &m_fileName)
{
    QString fileName = IniPath+m_fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    modelCmd->removeRows(0,modelCmd->rowCount());

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        insertCmdModelData(line);
    }
}

void Widget::writeViewToIni(const QString &fileName)
{
    QFile file(fileName);
     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
    QTextStream out(&file);
    foreach(QString s,modelCmd->stringList())
        out<<s<<"\r\n";
}

ProcessThread::ProcessThread()
{
}
//鼠标移动并点击
void ProcessThread::mouseClick(int x, int y)
{
    m_sendKeyMouse->mouse_left(x,y);
    //this->msleep(1000);//防止识别为双击
    this->msleep(100);
}
//设置剪切板 并 粘贴
void ProcessThread::sendText(const QString &s)
{
    //QApplication::clipboard()->setText(s);//线程内不工作
    emit setClip(s);
    this->msleep(20);//防止复制漏掉
	m_sendKeyMouse->sendKey (Qt::Key_Control,Qt::Key_V);
}
void ProcessThread::resizeQString(QString& s,int size)
{
    if(s.size()>size){
        s.resize(size-1);
        s.append("...");
    }
}

void ProcessThread::processCMD(QStringList list)
{
	if(list.size ()<3)
		return;
    if(list.at (0)==MOUSE_LEFT)//鼠标左键单击
	{
        int x = list.at(1).toInt();
        int y = list.at(2).toInt();
        mouseClick(x,y);
        emit(currentProcessCmd(QString("鼠标左键%1:%2").arg(x).arg(y)));
	}
    else if(list.at(0)==MOUSE_RIGHT)//鼠标右键单击
    {
        m_sendKeyMouse->mouse_right(list.at (1).toInt (),list.at (2).toInt ());
        emit(currentProcessCmd(QString("鼠标右键键%1:%2").arg(list.at (1).toInt ()).arg(list.at (2).toInt ())));
        this->msleep(100);
    }
	else if(list.at (0)==CMD_TEXT)
	{
        QString s = list.at(1);
        sendText(s);
        resizeQString(s,5);
        emit(currentProcessCmd(QString("发送固定文本:%1").arg(s)));
    }
	else if(list.at (0)==DIY_TEXT)
	{
		int row = list.at (1).toInt ();
		QTableWidgetItem *item = m_table->item (row,0);
        QString ss = item==0?QString():item->text ();
        //emit setClip(ss);
        sendText(ss);
        resizeQString(ss,5);
        emit(currentProcessCmd(QString("发送自定义%1行文本:%2").arg(row).arg(ss)));
	}
    else if(list.at(0)==DIY_NUMBER_ONEBYONE)// d#行号#开始#结束# d#行号#分隔符#index
    {
        if(list.size()<4)
            return;
        int row = list.at(1).toInt();
        QTableWidgetItem *item = m_table->item (row,0);
        QString ss = item==0?QString():item->text ();
        bool isNumber;
        int start = list.at(2).toInt(&isNumber);//Returns 0 if the conversion fails.
        int end = list.at(3).toInt();
        QString rr;
        if(isNumber)//数字 // d#行号#开始#结束#
        {
            rr = ss.mid(start,end-start+1);
        }else{
            QStringList ll = ss.split(list.at(2));
            if(ll.size()>end)
                rr = ll.at(end);
            else
                rr.append("1");
        }
        int i;
        for(i=0;i<rr.size();i++){
            if(!rr.at(i).isDigit())
                return;
        }
        for(i=0;i<rr.size();i++){
            keybd_event(rr.at(i).unicode(),0,0,0);
            keybd_event(rr.at(i).unicode(),0,KEYEVENTF_KEYUP,0);
        }
        emit(currentProcessCmd(QString("逐字发送%1").arg(rr)));
    }
	else if(list.at (0)==EQUAL_TEXT)// E#1#123#
	{
		int row = list.at (1).toInt ();
		QTableWidgetItem *item = m_table->item (row,0);
        QString s1 = item==0?QString():item->text ();
		if(s1 == list.at (2))
		{
			list.removeFirst ();list.removeFirst ();list.removeFirst ();
            emit(currentProcessCmd(QString("新命令%1").arg(list.join("#"))));
            processCMD(list);
        }else
            emit(currentProcessCmd(QString("匹配失败%1,%2").arg(s1).arg(list.at (2))));
	}
    else if(list.at(0)==ArrowTab)
    {
        QString s = list.at(1);
        s = encodeArrowNum(s);
        const QChar *data = s.constData();
        while(!data->isNull())
        {
            QChar c = *data/*->toUpper()*/;
            if(c==QChar('L')){
                //m_sendKeyMouse->sendKey (Qt::Key_Left);
                keybd_event( VK_LEFT, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( VK_LEFT, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );

                emit(currentProcessCmd(QString("方向键：左")));
            }
            else if(c==QChar('R')){
                //m_sendKeyMouse->sendKey (Qt::Key_Right);
                keybd_event( VK_RIGHT, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( VK_RIGHT, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );
                emit(currentProcessCmd(QString("方向键：右")));
            }
            else if(c==QChar('U')){
                //m_sendKeyMouse->sendKey (Qt::Key_Up);
                keybd_event( VK_UP, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( VK_UP, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );
                emit(currentProcessCmd(QString("方向键：上")));
            }
            else if(c==QChar('D')){
                //m_sendKeyMouse->sendKey (Qt::Key_Down);
                keybd_event( VK_DOWN, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( VK_DOWN, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );
                emit(currentProcessCmd(QString("方向键：下")));
            }
            else if(c==QChar('T')){
                m_sendKeyMouse->sendKey (Qt::Key_Tab);
                emit(currentProcessCmd(QString("Tab")));
            }

            else if(c==QChar('K')){
                m_sendKeyMouse->sendKey (Qt::Key_Space);
                emit(currentProcessCmd(QString("Space")));
            }
            else if(c==QChar('H')){
                m_sendKeyMouse->sendKey (Qt::Key_Enter);
                emit(currentProcessCmd(QString("ENTER")));
            }
            else if(c==QChar('B'))//shift_tab
            {
                m_sendKeyMouse->sendKey (Qt::Key_Shift,Qt::Key_Tab);
                emit(currentProcessCmd(QString("shift+tab")));
            }
            else if(c==QChar('Z'))//alt tab
            {
                qDebug()<<"alt tab";
                //m_sendKeyMouse->sendKey(Qt::Key_Alt,Qt::Key_Tab);
                keybd_event( VK_MENU, 0,KEYEVENTF_EXTENDEDKEY,0 );this->msleep(20);
                keybd_event( VK_TAB, 0,KEYEVENTF_EXTENDEDKEY,0 );this->msleep(20);
                keybd_event( VK_TAB, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );this->msleep(20);
                keybd_event( VK_MENU, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );this->msleep(20);
                emit(currentProcessCmd(QString("alt+tab")));
            }
            else if(c==QChar('z'))//ctrl tab
            {
                qDebug()<<"alt tab";
                //m_sendKeyMouse->sendKey(Qt::Key_Alt,Qt::Key_Tab);
                keybd_event( VK_CONTROL, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( VK_TAB, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( VK_TAB, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );
                keybd_event( VK_CONTROL, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );
                emit(currentProcessCmd(QString("alt+tab")));
            }
            else if(c==QChar('F'))//ctrl+c
            {
                keybd_event( VK_CONTROL, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( 'C', 0,0,0 );
                keybd_event( 'C', 0,0|KEYEVENTF_KEYUP,0 );
                keybd_event( VK_CONTROL, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );
                emit(currentProcessCmd(QString("ctrl+c")));
            }
            else if(c==QChar('V'))//ctrl+v
            {
                keybd_event( VK_CONTROL, 0,KEYEVENTF_EXTENDEDKEY,0 );
                keybd_event( 'V', 0,0,0 );
                keybd_event( 'V', 0,0|KEYEVENTF_KEYUP,0 );
                keybd_event( VK_CONTROL, 0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0 );
                emit(currentProcessCmd(QString("ctrl+v")));
            }/*
            else if(c==QChar('X'))//shift up
            {
                keybd_event( VK_SHIFT, 0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0 );
            }
            else if(c==QChar('x'))//shift down
            {
                keybd_event( VK_SHIFT, 0x45,KEYEVENTF_EXTENDEDKEY | 0,0 );
            }*/
            else if(c==QChar('S'))//shift up
            {
                //m_sendKeyMouse->sendKeyUp(Qt::Key_Shift);
                keybd_event( VK_SHIFT, 0,KEYEVENTF_KEYUP,0 );
                emit(currentProcessCmd(QString("按下shift")));

            }
            else if(c==QChar('s'))//shift down
            {
                //m_sendKeyMouse->sendKeyDown(Qt::Key_Shift);
                keybd_event( VK_SHIFT, 0,0,0 );
                emit(currentProcessCmd(QString("松开shift")));
            }
            ++data;
        }
    }
    else if(list.at(0)==Delay_text)
    {
        int delay = list.at(1).toInt();
        if(delay>0&&delay<10000)
            this->msleep(delay);
    }
    else if(list.at(0)==DIY_INCREASE||list.at(0)==DIY_DECREASE)
    {
        int row = list.at (1).toInt ();
        int step = list.at(2).toInt();
        QTableWidgetItem *item = m_table->item (row,0);//数字对应行
        if(item!=0){
            int num = item->text ().toInt();//行对应数字
            if(list.at(0)==DIY_INCREASE)
                num+=step;
            else
                num-=step;
            if(num<0)
                num = 0;
            item->setText(QString("%1").arg(num));
        }
    }
}

void ProcessThread::processCMD(QString s)
{
	QStringList list = s.split (SEPATATOR);
	processCMD(list);
}

void ProcessThread::run()//进程只执行一圈
{
	foreach(QString s,m_lines){
        sem_OneStep.acquire(1);
		processCMD(s);
		this->msleep (100);
        emit this->OneCmdEnd();
    }
}

void Widget::on_checkBoxAutoMouse_clicked(bool checked)
{
    HookFunction* instance = HookFunction::getInstance();
    if(checked){
        connect(instance,SIGNAL(mouseAction(QPoint,MouseActionType)),this,SLOT(AutoMouse_clicked(QPoint,MouseActionType)));
    }else{
        instance->disconnect();
    }
}

void Widget::AutoMouse_clicked(QPoint point, MouseActionType type)
{
    //Q_UNUSED(type);
    ui->mouseX->setValue(point.x());
    ui->mouseY->setValue(point.y());
    button_mouseClick(type);
}
//剪切板 内容改变，自动更新自定义文本内容
void Widget::ClipboardChanged(QClipboard::Mode mode)
{
    //qDebug()<<"ClipboardChanged "<<mode;
    if(mode == QClipboard::Clipboard&&ui->checkBoxClipboard->isChecked()&&ui->checkBoxClipValue->isChecked()){
        QString text = m_clipboard->text();
        if(text==thisClipboardText)//程序自己更新的剪切板，则不做处理
            return;
        QStringList clipValueList = m_clipboard->text().split('\t');//默认是keepEmptyParts
        //qDebug()<<clipValueList.size();
        int start = ui->spinBoxClipValueStart->value()-1;
        int end = ui->spinBoxClipValueEnd->value()-1;
        if(start<0||end<start)
            return;
        int i,j;
        for(i=start,j=0;i<=end;i++,j++){
            if(ui->tableWidgetDiy->rowCount()>i && j<clipValueList.size())
                ui->tableWidgetDiy->setItem(i,0,new QTableWidgetItem(clipValueList.value(j)));
        }
    }
}
//切换 命令列表中 鼠标左右键
void Widget::on_pushButtonMouseLR_clicked()
{
    QModelIndex current_modeindex=ui->listViewCmd->selectionModel()->currentIndex();
    QString s = current_modeindex.data().toString();

    if(s.startsWith(MOUSE_LEFT)){
        s.remove(0,1);
        s.prepend(MOUSE_RIGHT);
    }else if(s.startsWith(MOUSE_RIGHT)){
        s.remove(0,1);
        s.prepend(MOUSE_LEFT);
    }
    ui->listViewCmd->model()->setData(current_modeindex,s);
}

void Widget::closeEvent(QCloseEvent *event)
{
    mouseFloat->close();
    stateWidget->close();
    event->accept();
}
//清空命令列表
void Widget::on_pushButtonCLeanCmdText_clicked()
{
    modelCmd->removeRows(0,modelCmd->rowCount());
}
//清空自定义文本列表
void Widget::on_pushButtonCleanDiyText_clicked()
{
    ui->tableWidgetDiy->model()->removeRows(0,ui->tableWidgetDiy->model()->rowCount());
}

void Widget::on_lineEditCmdText_returnPressed()
{
    this->button_sendCmdText();
}

void Widget::on_lineEditArrow_returnPressed()
{
    this->button_sendArrow();
}

void Widget::on_lineEditDiyText_returnPressed()
{
    this->button_AddDiyText();
}
//显示或隐藏 帮助界面
void Widget::on_pushButtonShowHelp_clicked()
{
    int width = this->width();
    int helpWidth = ui->plainTextEdit->width()+6;
    ui->plainTextEdit->setHidden(!ui->plainTextEdit->isHidden());
    int width2= ui->plainTextEdit->isHidden()?width-helpWidth:width+helpWidth;
    this->setMinimumWidth(ui->plainTextEdit->isHidden()?width-helpWidth:width+helpWidth);
    this->resize(width2,this->height());
}
//根据选框 显示或隐藏 状态窗口
void Widget::on_checkBoxStateWidget_clicked(bool checked)
{
    checked?stateWidget->show():stateWidget->hide();
}
//状态窗口设置窗口
void Widget::on_pushButtonStateSetting_clicked()
{
    StateSettingDialog d;
    d.exec();
    stateWidget->updateDisplay();
}
