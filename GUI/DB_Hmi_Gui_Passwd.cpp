#include "DB_Hmi_Gui_Passwd.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QCryptographicHash>
#include <QTextStream>
#include "DB_Hmi_Gui_Alpkeyboard.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

DB_Hmi_Gui_Passwd::DB_Hmi_Gui_Passwd()
{
    Key = new DB_Hmi_Gui_AlpKeyboard(this);
    this->setFixedSize(205,130);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->Init();
}

DB_Hmi_Gui_Passwd::~DB_Hmi_Gui_Passwd()
{

}

void DB_Hmi_Gui_Passwd::Init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(20);
    this->setGraphicsEffect(shadow_effect);

    QWidget* mWidget = InitWidget();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget* DB_Hmi_Gui_Passwd::InitWidget()
{
    const QString Widget_Style = "background-color:rgb(255,255,255);border:1px solid gray;";
    QWidget* mWidget = new QWidget();
    mWidget->setObjectName("mWidget");
    mWidget->setStyleSheet(QString("#mWidget{%1}").arg(Widget_Style));
    mWidget->setFixedSize(200,125);


    QVBoxLayout* mVBox = new QVBoxLayout();
    mVBox->setSpacing(0);
    mVBox->setContentsMargins(0,0,0,0);

    //Top 头部
    QWidget* mTop = new QWidget();
    mTop->setObjectName("mTop");
    mTop->setFixedHeight(25);
    mTop->setStyleSheet("QWidget#mTop{background-color:rgb(120,120,120);}");

    QHBoxLayout* mTopLayout = new QHBoxLayout();
    mTopLayout->setSpacing(0);
    mTopLayout->setContentsMargins(5,0,0,0);

    const QString lbl_Top_Text_Style = "color:rgb(255,255,255);"
                                       "font : 12pt ""黑体"" ";
    QLabel* lbl_Top_Text = new QLabel();
    lbl_Top_Text->setText("Password");
    lbl_Top_Text->setFixedHeight(20);
    lbl_Top_Text->setStyleSheet(lbl_Top_Text_Style);

    mTopLayout->addWidget(lbl_Top_Text);
    mTop->setLayout(mTopLayout);

    //中间部分
    QVBoxLayout* mMidLayout = new QVBoxLayout();
    mMidLayout->setSpacing(0);
    mMidLayout->setContentsMargins(0,0,0,0);

    lineEdit = new QLineEdit(this);
    lineEdit->setFixedHeight(40);
    lineEdit->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    lineEdit->setPlaceholderText(tr("密码"));//设置密码提示
    lineEdit->setEchoMode(QLineEdit::Password);//设置密码隐藏
    lineEdit->setStyleSheet("QLineEdit{border-width:1px;font-size:12px;color:black;border:1px solid gray;}"
        "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    lineEdit->setMaxLength(16);//设置最大长度16位

    QWidget* KeyButtonLabelWidget = new QWidget();
    KeyButtonLabelWidget->setObjectName("KeyButtonLabelWidget");

    QHBoxLayout* KeyLayout = new QHBoxLayout();
    KeyLayout->setSpacing(20);
    KeyLayout->setContentsMargins(5,0,0,0);

    const QString btn_Key_Style = "";
    QPushButton* btn_Key = new QPushButton();
    btn_Key->setIcon(QIcon(":/Icon/Img/Icon/keyboard.png"));
    btn_Key->setIconSize(QSize(32,25));
    btn_Key->setStyleSheet(btn_Key_Style);
    btn_Key->setFixedSize(32,23);

    const QString lbl_Warrning_Style = "";
    QLabel* lbl_Warrning = new QLabel();
    lbl_Warrning->setStyleSheet(lbl_Warrning_Style);
    lbl_Warrning->setText("提示");

    KeyLayout->addWidget(btn_Key);
    KeyLayout->addWidget(lbl_Warrning);
    KeyButtonLabelWidget->setLayout(KeyLayout);

    mMidLayout->addWidget(lineEdit);
    mMidLayout->addWidget(KeyButtonLabelWidget);

    //尾部按钮部分
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    const QString btn_Sure_Center_Style = "";
    QPushButton* btn_Sure = new QPushButton();
    btn_Sure->setFixedHeight(35);
    btn_Sure->setText("确定");
    btn_Sure->setStyleSheet(btn_Sure_Center_Style);

    QPushButton* btn_Center = new QPushButton();
    btn_Center->setText("取消");
    btn_Center->setStyleSheet(btn_Sure_Center_Style);
    btn_Center->setFixedHeight(35);
    mLayout->addWidget(btn_Sure);
    mLayout->addWidget(btn_Center);

    mVBox->addWidget(mTop);
    mVBox->addStretch();
    mVBox->addLayout(mMidLayout);
    mVBox->addStretch();
    mVBox->addLayout(mLayout);
//    mVBox->addWidget(btn_Wranning);

    mWidget->setLayout(mVBox);

    this->connect(btn_Sure,&QPushButton::clicked,this,&DB_Hmi_Gui_Passwd::Clicked_Sure_Slot);
    this->connect(btn_Center,&QPushButton::clicked,this,[=]()
    {
        this->close();
        lineEdit->clear();
        lineEdit->setPlaceholderText(tr("密码"));//设置密码提示
    });
    this->connect(btn_Key,&QPushButton::clicked,this,[=](){Key->show();});
    this->connect(Key,&DB_Hmi_Gui_AlpKeyboard::UpdateWarrning,this,[=](bool isCap)
    {
        if(isCap)
            lbl_Warrning->setText("当前键盘输入为大写");
        else
            lbl_Warrning->setText("当前键盘输入为小写");
    });

    this->connect(lineEdit,&QLineEdit::returnPressed,this,[=](){btn_Sure->click();});

    Key->SendWarrning();

    return mWidget;
}

void DB_Hmi_Gui_Passwd::Clicked_Sure_Slot()
{
    if(lineEdit->text().isEmpty())
    {
        lineEdit->clear();
        lineEdit->setPlaceholderText("密码为空!");
        return;
    }
    QString strPwd5 = lineEdit->text();
    QByteArray bytePwd = strPwd5.toLatin1();
    QByteArray bytePwdMd5 = QCryptographicHash::hash(bytePwd,QCryptographicHash::Md5);
    QString strPwdMd5 = bytePwdMd5.toHex();

    QString FilePath = "C:\\PACnc\\DBHMI\\cfg\\password.txt";
    QFile cfile(FilePath);
    if(!cfile.open(QFile::ReadOnly | QFile::Text))
    {
        lineEdit->clear();
        lineEdit->setPlaceholderText(tr("密码文件丢失"));
        return;
    }
    QTextStream in(&cfile);
    QString myText = in.readAll();
    cfile.close();

    if(myText=="")
    {
        lineEdit->clear();
        lineEdit->setPlaceholderText(tr("密码丢失"));
        return;
    }
    myText.remove(QRegExp("\\s"));

    if(strPwdMd5 == myText)
    {
        PassWordRight();
    }
    else
    {
        lineEdit->clear();
        lineEdit->setPlaceholderText(tr("输入密码不正确！"));
        return;
    }

    done(1);
}

void DB_Hmi_Gui_Passwd::mousePressEvent(QMouseEvent* event)
{
    //调用window底下的移动
    #ifdef Q_OS_WIN
        if (ReleaseCapture())
               SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
           event->ignore();
    #endif
}
