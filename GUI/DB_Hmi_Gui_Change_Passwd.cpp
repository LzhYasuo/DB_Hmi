#include "DB_Hmi_Gui_Change_Passwd.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "DB_Hmi_Gui_Alpkeyboard.h"
#include <QCryptographicHash>

DB_Hmi_Gui_Change_Passwd::DB_Hmi_Gui_Change_Passwd(QWidget* parent)
    :QDialog (parent)
{
    this->setFixedSize(210,215);
    Key = new DB_Hmi_Gui_AlpKeyboard(this);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->Init();
}

DB_Hmi_Gui_Change_Passwd::~DB_Hmi_Gui_Change_Passwd()
{

}

void DB_Hmi_Gui_Change_Passwd::mousePressEvent(QMouseEvent* event)
{
    //调用window底下的移动
    #ifdef Q_OS_WIN
        if (ReleaseCapture())
               SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
           event->ignore();
    #endif
}

void DB_Hmi_Gui_Change_Passwd::Init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(5,5,5,5);

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

QWidget* DB_Hmi_Gui_Change_Passwd::InitWidget()
{
    const QString Widget_Style = "background-color:rgb(255,255,255);border:1px solid gray;";
    QWidget* mWidget = new QWidget();
    mWidget->setObjectName("mWidget");
    mWidget->setStyleSheet(QString("#mWidget{%1}").arg(Widget_Style));
    mWidget->setFixedSize(200,205);


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
    lbl_Top_Text->setText("Change Password");
    lbl_Top_Text->setFixedHeight(20);
    lbl_Top_Text->setStyleSheet(lbl_Top_Text_Style);

    mTopLayout->addWidget(lbl_Top_Text);
    mTop->setLayout(mTopLayout);

    //中间部分
    QVBoxLayout* mMidLayout = new QVBoxLayout();
    mMidLayout->setSpacing(0);
    mMidLayout->setContentsMargins(0,0,0,0);

    OldPawd = new QLineEdit(this);
    OldPawd->setFixedHeight(40);
    OldPawd->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    OldPawd->setPlaceholderText(tr("旧密码"));//设置密码提示
    OldPawd->setEchoMode(QLineEdit::Password);//设置密码隐藏
    OldPawd->setStyleSheet("QLineEdit{border-width:1px;font-size:12px;color:black;border:1px solid gray;}"
        "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    OldPawd->setMaxLength(16);//设置最大长度16位

    newPawd = new QLineEdit(this);
    newPawd->setFixedHeight(40);
    newPawd->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    newPawd->setPlaceholderText(tr("第一次输入密码"));//设置密码提示
    newPawd->setEchoMode(QLineEdit::Password);//设置密码隐藏
    newPawd->setStyleSheet("QLineEdit{border-width:1px;font-size:12px;color:black;border:1px solid gray;}"
        "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    newPawd->setMaxLength(16);//设置最大长度16位

    SurenewPaswd = new QLineEdit(this);
    SurenewPaswd->setFixedHeight(40);
    SurenewPaswd->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    SurenewPaswd->setPlaceholderText(tr("第二次输入密码"));//设置密码提示
    SurenewPaswd->setEchoMode(QLineEdit::Password);//设置密码隐藏
    SurenewPaswd->setStyleSheet("QLineEdit{border-width:1px;font-size:12px;color:black;border:1px solid gray;}"
        "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    SurenewPaswd->setMaxLength(16);//设置最大长度16位

    QWidget* KeyButtonLabelWidget = new QWidget();
    KeyButtonLabelWidget->setObjectName("KeyButtonLabelWidget");

    QHBoxLayout* KeyLayout = new QHBoxLayout();
    KeyLayout->setSpacing(20);
    KeyLayout->setContentsMargins(0,0,0,0);

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

    mMidLayout->addWidget(OldPawd);
    mMidLayout->addWidget(newPawd);
    mMidLayout->addWidget(SurenewPaswd);
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

    this->connect(btn_Sure,&QPushButton::clicked,this,&DB_Hmi_Gui_Change_Passwd::Clicked_Sure_Slot);
    this->connect(btn_Center,&QPushButton::clicked,this,[=](){
        this->done(0);
//        this->close();
//        OldPawd->clear();
//        newPawd->clear();
//        SurenewPaswd->clear();
//        OldPawd->setPlaceholderText(tr("旧密码"));
//        newPawd->setPlaceholderText(tr("第一次输入密码"));//设置密码提示
//        SurenewPaswd->setPlaceholderText(tr("第二次输入密码"));//设置密码提示
    });
    this->connect(btn_Key,&QPushButton::clicked,this,[=](){Key->show();});
    this->connect(Key,&DB_Hmi_Gui_AlpKeyboard::UpdateWarrning,this,[=](bool isCap){
        if(isCap)
            lbl_Warrning->setText("当前键盘输入为大写");
        else
            lbl_Warrning->setText("当前键盘输入为小写");
    });

    Key->SendWarrning();

    return mWidget;
}

void DB_Hmi_Gui_Change_Passwd::Clicked_Sure_Slot()
{
    if(OldPawd->text().isEmpty())
    {
        OldPawd->clear();
        newPawd->clear();
        SurenewPaswd->clear();
        OldPawd->setPlaceholderText(tr("旧密码为空"));
        SurenewPaswd->setPlaceholderText(tr("新密码"));
        newPawd->setPlaceholderText(tr("第二次输入新密码"));
        return;
    }
    else if(newPawd->text().isEmpty())
    {
        OldPawd->clear();
        newPawd->clear();
        SurenewPaswd->clear();
        OldPawd->setPlaceholderText(tr("旧密码"));
        SurenewPaswd->setPlaceholderText(tr("密码为空哦"));
        newPawd->setPlaceholderText(tr("密码为空哦"));
        return;
    }
    else if(SurenewPaswd->text().isEmpty())
    {
        OldPawd->clear();
        newPawd->clear();
        SurenewPaswd->clear();
        OldPawd->setPlaceholderText(tr("旧密码"));
        newPawd->setPlaceholderText(tr("密码为空哦"));
        SurenewPaswd->setPlaceholderText(tr("密码为空哦"));
        return;
    }
    else if(SurenewPaswd->text().isEmpty() && newPawd->text().isEmpty() && OldPawd->text().isEmpty())
    {
        OldPawd->clear();
        newPawd->clear();
        SurenewPaswd->clear();
        OldPawd->setPlaceholderText(tr("我真佛了"));
        newPawd->setPlaceholderText(tr("看来你的脑子"));
        SurenewPaswd->setPlaceholderText(tr("是真的不好使"));
        return;
    }
    else if(newPawd->text() != SurenewPaswd->text())
    {
        OldPawd->clear();
        newPawd->clear();
        SurenewPaswd->clear();
        OldPawd->setPlaceholderText(tr("旧密码"));
        newPawd->setPlaceholderText(tr("两次密码输出不一致"));
        SurenewPaswd->setPlaceholderText(tr("两次密码输出不一致?"));
        return;
    }
    PawdisTure = OldPawdIsTrue();
    if(PawdisTure != 0)
    {
        OldPawd->clear();
        newPawd->clear();
        SurenewPaswd->clear();
        OldPawd->setPlaceholderText(tr("密码错误"));
        newPawd->setPlaceholderText(tr("新密码"));//设置密码提示
        SurenewPaswd->setPlaceholderText(tr("第二次输入密码"));//设置密码提示
        return;
    }

    QString strPwd5 = newPawd->text();
    QByteArray bytePwd = strPwd5.toLatin1();
    QByteArray bytePwdMd5 = QCryptographicHash::hash(bytePwd, QCryptographicHash::Md5);
    QString strPwdMd5 = bytePwdMd5.toHex();
    QString FilePath = "C:\\PACnc\\DBHMI\\cfg\\password.txt";
    QFile cfile(FilePath);

    cfile.open(QIODevice::Truncate | QIODevice::WriteOnly);
    cfile.close();

    if(!cfile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Could not open the file for reading";
//        emit ChangeState(false);
        return;
    }
    QTextStream out(&cfile);
    out<<strPwdMd5<<endl;
    out.flush();

    cfile.close();

    emit ChangeState(true);

    done(1);
}

int DB_Hmi_Gui_Change_Passwd::OldPawdIsTrue()
{
    QString strPwd5 = OldPawd->text();
    QByteArray bytePwd = strPwd5.toLatin1();
    QByteArray bytePwdMd5 = QCryptographicHash::hash(bytePwd,QCryptographicHash::Md5);
    QString strPwdMd5 = bytePwdMd5.toHex();

    QString FilePath = "C:\\PACnc\\DBHMI\\cfg\\password.txt";
    QFile cfile(FilePath);
    if(!cfile.open(QFile::ReadOnly | QFile::Text))
    {
        OldPawd->clear();
        OldPawd->setPlaceholderText(tr("密码文件丢失"));
        return 1;
    }
    QTextStream in(&cfile);
    QString myText = in.readAll();
    cfile.close();

    if(myText=="")
    {
        OldPawd->clear();
        OldPawd->setPlaceholderText(tr("密码丢失"));
        return 2;
    }
    myText.remove(QRegExp("\\s"));

    if(strPwdMd5 == myText)
    {
        return 0;
    }
    else
    {
        OldPawd->clear();
        OldPawd->setPlaceholderText(tr("输入密码不正确！"));
        return 3;
    }
}
