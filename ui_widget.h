/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpinBox *mouseX;
    QSpinBox *mouseY;
    QPushButton *pushButtonMoveMouseTo;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QCheckBox *checkBoxAutoMouse;
    QCheckBox *checkBoxClipboard;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBoxFloatWidget;
    QCheckBox *checkBoxStaysOnTop;
    QLabel *label_9;
    QSpinBox *spinBoxOpacity;
    QPushButton *pushButtonQuit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QSpinBox *spinBoxTimerDelay;
    QPushButton *pushButtonAddDelay;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditCmdText;
    QPushButton *pushButtonAddCmdText;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QLineEdit *lineEditArrow;
    QPushButton *pushButtonAddArrow;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelState;
    QCheckBox *checkBoxOneStep;
    QCheckBox *checkBoxTimer;
    QSpinBox *spinBoxTimer;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QComboBox *comboBoxF8;
    QLabel *label_4;
    QComboBox *comboBoxF9;
    QLabel *label_5;
    QComboBox *comboBoxF10;
    QLabel *label_6;
    QComboBox *comboBoxF11;
    QLabel *label_7;
    QComboBox *comboBoxF12;
    QPushButton *pushButtonMouseLR;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonDelCmdText;
    QListView *listViewCmd;
    QLabel *label_14;
    QLabel *label_8;
    QComboBox *comboBoxIni;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *checkBoxClipValue;
    QSpinBox *spinBoxClipValueStart;
    QLabel *label_15;
    QSpinBox *spinBoxClipValueEnd;
    QTableWidget *tableWidgetDiy;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEditDiyText;
    QPushButton *pushButtonAddDiyText;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButtonAddDiyToCmd;
    QPushButton *pushButtonDelDiyText;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButtonSaveDiy;
    QComboBox *comboBoxDiy;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(931, 488);
        horizontalLayout_12 = new QHBoxLayout(Widget);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mouseX = new QSpinBox(Widget);
        mouseX->setObjectName(QStringLiteral("mouseX"));
        mouseX->setMaximum(9999);
        mouseX->setValue(800);

        horizontalLayout->addWidget(mouseX);

        mouseY = new QSpinBox(Widget);
        mouseY->setObjectName(QStringLiteral("mouseY"));
        mouseY->setMaximum(9999);
        mouseY->setValue(300);

        horizontalLayout->addWidget(mouseY);

        pushButtonMoveMouseTo = new QPushButton(Widget);
        pushButtonMoveMouseTo->setObjectName(QStringLiteral("pushButtonMoveMouseTo"));
        pushButtonMoveMouseTo->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(pushButtonMoveMouseTo);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_13 = new QLabel(Widget);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_8->addWidget(label_13);

        checkBoxAutoMouse = new QCheckBox(Widget);
        checkBoxAutoMouse->setObjectName(QStringLiteral("checkBoxAutoMouse"));

        horizontalLayout_8->addWidget(checkBoxAutoMouse);

        checkBoxClipboard = new QCheckBox(Widget);
        checkBoxClipboard->setObjectName(QStringLiteral("checkBoxClipboard"));
        checkBoxClipboard->setChecked(true);

        horizontalLayout_8->addWidget(checkBoxClipboard);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBoxFloatWidget = new QCheckBox(Widget);
        checkBoxFloatWidget->setObjectName(QStringLiteral("checkBoxFloatWidget"));

        horizontalLayout_4->addWidget(checkBoxFloatWidget);

        checkBoxStaysOnTop = new QCheckBox(Widget);
        checkBoxStaysOnTop->setObjectName(QStringLiteral("checkBoxStaysOnTop"));

        horizontalLayout_4->addWidget(checkBoxStaysOnTop);

        label_9 = new QLabel(Widget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_4->addWidget(label_9);

        spinBoxOpacity = new QSpinBox(Widget);
        spinBoxOpacity->setObjectName(QStringLiteral("spinBoxOpacity"));
        spinBoxOpacity->setMinimum(0);
        spinBoxOpacity->setMaximum(100);
        spinBoxOpacity->setValue(100);

        horizontalLayout_4->addWidget(spinBoxOpacity);

        pushButtonQuit = new QPushButton(Widget);
        pushButtonQuit->setObjectName(QStringLiteral("pushButtonQuit"));
        pushButtonQuit->setMaximumSize(QSize(36, 16777215));

        horizontalLayout_4->addWidget(pushButtonQuit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_11 = new QLabel(Widget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_7->addWidget(label_11);

        spinBoxTimerDelay = new QSpinBox(Widget);
        spinBoxTimerDelay->setObjectName(QStringLiteral("spinBoxTimerDelay"));
        spinBoxTimerDelay->setMaximum(10000);
        spinBoxTimerDelay->setValue(500);

        horizontalLayout_7->addWidget(spinBoxTimerDelay);

        pushButtonAddDelay = new QPushButton(Widget);
        pushButtonAddDelay->setObjectName(QStringLiteral("pushButtonAddDelay"));

        horizontalLayout_7->addWidget(pushButtonAddDelay);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEditCmdText = new QLineEdit(Widget);
        lineEditCmdText->setObjectName(QStringLiteral("lineEditCmdText"));

        horizontalLayout_2->addWidget(lineEditCmdText);

        pushButtonAddCmdText = new QPushButton(Widget);
        pushButtonAddCmdText->setObjectName(QStringLiteral("pushButtonAddCmdText"));

        horizontalLayout_2->addWidget(pushButtonAddCmdText);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_10 = new QLabel(Widget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_5->addWidget(label_10);

        lineEditArrow = new QLineEdit(Widget);
        lineEditArrow->setObjectName(QStringLiteral("lineEditArrow"));

        horizontalLayout_5->addWidget(lineEditArrow);

        pushButtonAddArrow = new QPushButton(Widget);
        pushButtonAddArrow->setObjectName(QStringLiteral("pushButtonAddArrow"));

        horizontalLayout_5->addWidget(pushButtonAddArrow);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelState = new QLabel(Widget);
        labelState->setObjectName(QStringLiteral("labelState"));
        labelState->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(labelState);

        checkBoxOneStep = new QCheckBox(Widget);
        checkBoxOneStep->setObjectName(QStringLiteral("checkBoxOneStep"));
        checkBoxOneStep->setMaximumSize(QSize(44, 16777215));

        horizontalLayout_6->addWidget(checkBoxOneStep);

        checkBoxTimer = new QCheckBox(Widget);
        checkBoxTimer->setObjectName(QStringLiteral("checkBoxTimer"));
        checkBoxTimer->setMaximumSize(QSize(44, 16777215));

        horizontalLayout_6->addWidget(checkBoxTimer);

        spinBoxTimer = new QSpinBox(Widget);
        spinBoxTimer->setObjectName(QStringLiteral("spinBoxTimer"));
        spinBoxTimer->setMaximum(10000);
        spinBoxTimer->setValue(500);

        horizontalLayout_6->addWidget(spinBoxTimer);


        verticalLayout->addLayout(horizontalLayout_6);

        plainTextEdit = new QPlainTextEdit(Widget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(12);
        plainTextEdit->setFont(font);
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);


        horizontalLayout_12->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        comboBoxF8 = new QComboBox(Widget);
        comboBoxF8->setObjectName(QStringLiteral("comboBoxF8"));
        comboBoxF8->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxF8);

        label_4 = new QLabel(Widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        comboBoxF9 = new QComboBox(Widget);
        comboBoxF9->setObjectName(QStringLiteral("comboBoxF9"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBoxF9);

        label_5 = new QLabel(Widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        comboBoxF10 = new QComboBox(Widget);
        comboBoxF10->setObjectName(QStringLiteral("comboBoxF10"));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBoxF10);

        label_6 = new QLabel(Widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        comboBoxF11 = new QComboBox(Widget);
        comboBoxF11->setObjectName(QStringLiteral("comboBoxF11"));

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBoxF11);

        label_7 = new QLabel(Widget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_7);

        comboBoxF12 = new QComboBox(Widget);
        comboBoxF12->setObjectName(QStringLiteral("comboBoxF12"));

        formLayout->setWidget(4, QFormLayout::FieldRole, comboBoxF12);


        verticalLayout_2->addLayout(formLayout);

        pushButtonMouseLR = new QPushButton(Widget);
        pushButtonMouseLR->setObjectName(QStringLiteral("pushButtonMouseLR"));
        pushButtonMouseLR->setEnabled(false);

        verticalLayout_2->addWidget(pushButtonMouseLR);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_12->addLayout(verticalLayout_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButtonSave = new QPushButton(Widget);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        gridLayout_2->addWidget(pushButtonSave, 4, 0, 1, 1);

        pushButtonDelCmdText = new QPushButton(Widget);
        pushButtonDelCmdText->setObjectName(QStringLiteral("pushButtonDelCmdText"));

        gridLayout_2->addWidget(pushButtonDelCmdText, 4, 1, 1, 1);

        listViewCmd = new QListView(Widget);
        listViewCmd->setObjectName(QStringLiteral("listViewCmd"));
        listViewCmd->setMinimumSize(QSize(200, 0));
        listViewCmd->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        gridLayout_2->addWidget(listViewCmd, 3, 0, 1, 2);

        label_14 = new QLabel(Widget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_14, 1, 0, 1, 2);

        label_8 = new QLabel(Widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(20, 16777215));

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        comboBoxIni = new QComboBox(Widget);
        comboBoxIni->setObjectName(QStringLiteral("comboBoxIni"));

        gridLayout_2->addWidget(comboBoxIni, 2, 1, 1, 1);


        horizontalLayout_12->addLayout(gridLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_12 = new QLabel(Widget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        checkBoxClipValue = new QCheckBox(Widget);
        checkBoxClipValue->setObjectName(QStringLiteral("checkBoxClipValue"));

        horizontalLayout_11->addWidget(checkBoxClipValue);

        spinBoxClipValueStart = new QSpinBox(Widget);
        spinBoxClipValueStart->setObjectName(QStringLiteral("spinBoxClipValueStart"));
        spinBoxClipValueStart->setValue(1);

        horizontalLayout_11->addWidget(spinBoxClipValueStart);

        label_15 = new QLabel(Widget);
        label_15->setObjectName(QStringLiteral("label_15"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(label_15);

        spinBoxClipValueEnd = new QSpinBox(Widget);
        spinBoxClipValueEnd->setObjectName(QStringLiteral("spinBoxClipValueEnd"));
        spinBoxClipValueEnd->setValue(3);

        horizontalLayout_11->addWidget(spinBoxClipValueEnd);


        verticalLayout_3->addLayout(horizontalLayout_11);

        tableWidgetDiy = new QTableWidget(Widget);
        if (tableWidgetDiy->columnCount() < 1)
            tableWidgetDiy->setColumnCount(1);
        tableWidgetDiy->setObjectName(QStringLiteral("tableWidgetDiy"));
        tableWidgetDiy->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidgetDiy->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetDiy->setColumnCount(1);

        verticalLayout_3->addWidget(tableWidgetDiy);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEditDiyText = new QLineEdit(Widget);
        lineEditDiyText->setObjectName(QStringLiteral("lineEditDiyText"));

        horizontalLayout_3->addWidget(lineEditDiyText);

        pushButtonAddDiyText = new QPushButton(Widget);
        pushButtonAddDiyText->setObjectName(QStringLiteral("pushButtonAddDiyText"));

        horizontalLayout_3->addWidget(pushButtonAddDiyText);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButtonAddDiyToCmd = new QPushButton(Widget);
        pushButtonAddDiyToCmd->setObjectName(QStringLiteral("pushButtonAddDiyToCmd"));

        horizontalLayout_9->addWidget(pushButtonAddDiyToCmd);

        pushButtonDelDiyText = new QPushButton(Widget);
        pushButtonDelDiyText->setObjectName(QStringLiteral("pushButtonDelDiyText"));

        horizontalLayout_9->addWidget(pushButtonDelDiyText);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButtonSaveDiy = new QPushButton(Widget);
        pushButtonSaveDiy->setObjectName(QStringLiteral("pushButtonSaveDiy"));

        horizontalLayout_10->addWidget(pushButtonSaveDiy);

        comboBoxDiy = new QComboBox(Widget);
        comboBoxDiy->setObjectName(QStringLiteral("comboBoxDiy"));

        horizontalLayout_10->addWidget(comboBoxDiy);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_10);


        horizontalLayout_12->addLayout(verticalLayout_3);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        pushButtonMoveMouseTo->setText(QApplication::translate("Widget", "\346\267\273\345\212\240\351\274\240\346\240\207\344\275\215\347\275\256", 0));
        label_13->setText(QApplication::translate("Widget", "F6\346\267\273\345\212\240\351\274\240\346\240\207\345\275\223\344\275\215\347\275\256", 0));
        checkBoxAutoMouse->setText(QApplication::translate("Widget", "\350\207\252\345\212\250\346\215\225\350\216\267\351\274\240\346\240\207\345\267\246\351\224\256", 0));
        checkBoxClipboard->setText(QApplication::translate("Widget", "\347\233\221\345\220\254\345\211\252\345\210\207\346\235\277", 0));
        checkBoxFloatWidget->setText(QApplication::translate("Widget", "\351\274\240\346\240\207\344\275\215\347\275\256\351\242\204\350\247\210", 0));
        checkBoxStaysOnTop->setText(QApplication::translate("Widget", "\345\211\215\347\253\257\346\230\276\347\244\272", 0));
        label_9->setText(QApplication::translate("Widget", "\351\200\217\346\230\216\345\272\246", 0));
        pushButtonQuit->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", 0));
        label_11->setText(QApplication::translate("Widget", "\345\273\266\350\277\237", 0));
        pushButtonAddDelay->setText(QApplication::translate("Widget", "\346\267\273\345\212\240", 0));
        label->setText(QApplication::translate("Widget", "\346\226\207\346\234\254", 0));
        pushButtonAddCmdText->setText(QApplication::translate("Widget", "\346\267\273\345\212\240", 0));
        label_10->setText(QApplication::translate("Widget", "\347\256\255\345\244\264", 0));
        pushButtonAddArrow->setText(QApplication::translate("Widget", "\346\267\273\345\212\240", 0));
        labelState->setText(QApplication::translate("Widget", "state", 0));
        checkBoxOneStep->setText(QApplication::translate("Widget", "\345\215\225\346\255\245", 0));
        checkBoxTimer->setText(QApplication::translate("Widget", "\345\256\232\346\227\266", 0));
        plainTextEdit->setPlainText(QApplication::translate("Widget", "\350\257\264\346\230\216\357\274\232\n"
"M#\345\235\220\346\240\207#\345\235\220\346\240\207#\346\263\250\351\207\212\357\274\210\351\274\240\346\240\207\345\215\225\345\207\273\357\274\211\n"
"R#\345\235\220\346\240\207#\345\235\220\346\240\207#\346\263\250\351\207\212\357\274\210\351\274\240\346\240\207\345\217\263\351\224\256\357\274\211\n"
"C#\345\233\272\345\256\232\346\226\207\346\234\254#\346\263\250\351\207\212\n"
"D#\350\207\252\345\256\232\344\271\211\350\241\214\345\217\267#\346\263\250\351\207\212\n"
"E#X#Y#Z#\346\263\250\351\207\212\n"
"\343\200\200\357\274\210\350\207\252\345\256\232\344\271\211\346\226\207\346\234\254X\350\241\214\347\255\211\344\272\216Y\345\210\231\346\211\247\350\241\214Z\357\274\211\n"
"A#\346\226\271\345\220\221\345\255\227\346\257\215#\346\263\250\351\207\212\n"
"\343\200\200\357\274\210L\345\267\246R\345\217\263U\344\270\212D\344\270\213;T=tab;B=shift_tab\343\200\202\345\220\216\351\235\242\345\212\240n\344\270\272\350\207\252\345\256\232\344\271\211\350\241\214)\n"
"T#\345"
                        "\273\266\346\227\266\346\227\266\351\227\264#\346\263\250\351\207\212\n"
"P#\350\207\252\345\256\232\344\271\211\350\241\214\345\217\267#n#\357\274\210\350\207\252\345\256\232\344\271\211\345\242\236\345\212\240n)\n"
"Q#\350\207\252\345\256\232\344\271\211\350\241\214\345\217\267#n#\357\274\210\350\207\252\345\256\232\344\271\211\345\207\217\345\260\221n)", 0));
        label_3->setText(QApplication::translate("Widget", "F8", 0));
        label_4->setText(QApplication::translate("Widget", "F9", 0));
        label_5->setText(QApplication::translate("Widget", "F10", 0));
        label_6->setText(QApplication::translate("Widget", "F11", 0));
        label_7->setText(QApplication::translate("Widget", "F12", 0));
        pushButtonMouseLR->setText(QApplication::translate("Widget", "\351\274\240\346\240\207\345\267\246\345\217\263\351\224\256\345\210\207\346\215\242", 0));
        pushButtonSave->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\345\275\223\345\211\215\345\221\275\344\273\244\345\210\227\350\241\250", 0));
        pushButtonDelCmdText->setText(QApplication::translate("Widget", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214", 0));
        label_14->setText(QApplication::translate("Widget", "\345\221\275\344\273\244\345\210\227\350\241\250", 0));
        label_8->setText(QApplication::translate("Widget", "F7", 0));
        label_12->setText(QApplication::translate("Widget", "\350\207\252\345\256\232\344\271\211\346\226\207\346\234\254", 0));
        checkBoxClipValue->setText(QApplication::translate("Widget", "\345\211\252\345\210\207\346\235\277\345\200\274(\344\273\245tab\345\210\206\345\211\262)", 0));
        label_15->setText(QApplication::translate("Widget", "\350\207\263", 0));
        label_2->setText(QApplication::translate("Widget", "\350\241\214\345\220\215\347\247\260", 0));
        pushButtonAddDiyText->setText(QApplication::translate("Widget", "\346\267\273\345\212\240\350\241\214", 0));
        pushButtonAddDiyToCmd->setText(QApplication::translate("Widget", "\346\267\273\345\212\240\345\275\223\345\211\215\350\241\214\345\210\260\345\221\275\344\273\244\345\210\227\350\241\250", 0));
        pushButtonDelDiyText->setText(QApplication::translate("Widget", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214", 0));
        pushButtonSaveDiy->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\345\210\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
