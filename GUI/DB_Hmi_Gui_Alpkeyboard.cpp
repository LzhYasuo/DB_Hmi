#include "DB_Hmi_Gui_AlpKeyboard.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>

#define GET_STR(x) #x

DB_Hmi_Gui_AlpKeyboard::DB_Hmi_Gui_AlpKeyboard(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::Tool|Qt::WindowStaysOnTopHint|Qt::WindowDoesNotAcceptFocus);
    setFocusPolicy(Qt::NoFocus);
    setWindowTitle("Soft-Keyboard");

    QHBoxLayout* Layout = new QHBoxLayout();
    Layout->setSpacing(0);
    Layout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = InitWidget();

    Layout->addWidget(mWidget);
    this->setLayout(Layout);

    isCap = GetCapsButtonStatus();
    CheckCapsButtonClicked();
    emit CapLight(isCap);
}

void DB_Hmi_Gui_AlpKeyboard::SendWarrning()
{
    emit UpdateWarrning(isCap);
}

QWidget* DB_Hmi_Gui_AlpKeyboard::InitWidget()
{
    const QString WidgetStyle = "background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);";
    QWidget* mWidget = new QWidget();
    mWidget->setFixedSize(800,300);
    mWidget->setObjectName("mWidget");
    mWidget->setStyleSheet(QString("#mWidget{%1}").arg(WidgetStyle));
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    //Style
    const QString ButtonStyle = GET_STR
            (
                QPushButton{
                    background-color: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);
                    border:none;
                    color:rgb(255,255,255);
                    border:1px solid #242424;
                    border-radius:5px;
                    text-align:center;
                    font:14pt "黑体";
                }
                QPushButton:pressed{
                    background-color: qlineargradient(spread:pad, x1:1, y1:0.057, x2:1, y2:1, stop:0 rgba(225, 225, 230, 255), stop:1 rgba(200, 200, 200, 255));
                    border:none;
                    color:rgb(0,0,0);
                    border: 1px solid #444444;
                }
                QPushButton:checked{
                    background-color: qlineargradient(spread:pad, x1:1, y1:0.057, x2:1, y2:1, stop:0 rgba(225, 225, 230, 255), stop:1 rgba(200, 200, 200, 255));
                    border:none;
                    color:rgb(0,0,0);
                    border: 1px solid #444444;
                }

                );

    //1-9
    QHBoxLayout* mTopLayout = new QHBoxLayout();
    mTopLayout->setSpacing(1);
    mTopLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_ESC = Get_Button("ESC","",ButtonStyle,VK_ESCAPE,NO_CHANGE);
    QPushButton* btn_TPoint = Get_Button("`","~",ButtonStyle,VK_OEM_3,NUM_CHANGE);
    QPushButton* btn_Num1 = Get_Button("1","!",ButtonStyle,0x31,NUM_CHANGE);
    QPushButton* btn_Num2 = Get_Button("2","@",ButtonStyle,0x32,NUM_CHANGE);
    QPushButton* btn_Num3 = Get_Button("3","#",ButtonStyle,0x33,NUM_CHANGE);
    QPushButton* btn_Num4 = Get_Button("4","￥",ButtonStyle,0x34,NUM_CHANGE);
    QPushButton* btn_Num5 = Get_Button("5","%",ButtonStyle,0x35,NUM_CHANGE);
    QPushButton* btn_Num6 = Get_Button("6","^",ButtonStyle,0x36,NUM_CHANGE);
    QPushButton* btn_Num7 = Get_Button("7","&",ButtonStyle,0x37,NUM_CHANGE);
    QPushButton* btn_Num8 = Get_Button("8","*",ButtonStyle,0x38,NUM_CHANGE);
    QPushButton* btn_Num9 = Get_Button("9","(",ButtonStyle,0x39,NUM_CHANGE);
    QPushButton* btn_Num0 = Get_Button("0",")",ButtonStyle,0x30,NUM_CHANGE);
    QPushButton* btn_Line = Get_Button("-","_",ButtonStyle,VK_OEM_MINUS,NUM_CHANGE);
    QPushButton* btn_Equal = Get_Button("=","+",ButtonStyle,VK_OEM_PLUS,NUM_CHANGE);
    QPushButton* btn_Back = Get_Button("Back ","",ButtonStyle,VK_BACK,NO_CHANGE);

    //特殊宽
    btn_ESC->setFixedWidth(70);
    btn_Back->setFixedWidth(100);

    //ADD
    mTopLayout->addWidget(btn_ESC);
    mTopLayout->addWidget(btn_TPoint);
    mTopLayout->addWidget(btn_Num1);
    mTopLayout->addWidget(btn_Num2);
    mTopLayout->addWidget(btn_Num3);
    mTopLayout->addWidget(btn_Num4);
    mTopLayout->addWidget(btn_Num5);
    mTopLayout->addWidget(btn_Num6);
    mTopLayout->addWidget(btn_Num7);
    mTopLayout->addWidget(btn_Num8);
    mTopLayout->addWidget(btn_Num9);
    mTopLayout->addWidget(btn_Num0);
    mTopLayout->addWidget(btn_Line);
    mTopLayout->addWidget(btn_Equal);
    mTopLayout->addWidget(btn_Back);

    //Q-P
    QHBoxLayout* mKeyTopLayout = new QHBoxLayout();
    mKeyTopLayout->setSpacing(1);
    mKeyTopLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_Tab = Get_Button("Tab","",ButtonStyle,VK_TAB,NO_CHANGE);
    QPushButton* btn_KeyQ = Get_Button("q","Q",ButtonStyle,0x51,LETTER_CHANGE);
    QPushButton* btn_KeyW = Get_Button("w","W",ButtonStyle,0x57,LETTER_CHANGE);
    QPushButton* btn_KeyE = Get_Button("e","E",ButtonStyle,0x45,LETTER_CHANGE);
    QPushButton* btn_KeyR = Get_Button("r","R",ButtonStyle,0x52,LETTER_CHANGE);
    QPushButton* btn_KeyT = Get_Button("t","T",ButtonStyle,0x54,LETTER_CHANGE);
    QPushButton* btn_KeyY = Get_Button("y","Y",ButtonStyle,0x59,LETTER_CHANGE);
    QPushButton* btn_KeyU = Get_Button("u","U",ButtonStyle,0x55,LETTER_CHANGE);
    QPushButton* btn_KeyI = Get_Button("i","I",ButtonStyle,0x49,LETTER_CHANGE);
    QPushButton* btn_KeyO = Get_Button("o","O",ButtonStyle,0x4f,LETTER_CHANGE);
    QPushButton* btn_KeyP = Get_Button("p","P",ButtonStyle,0x50,LETTER_CHANGE);
    QPushButton* btn_KeyLeftPar = Get_Button("[","{",ButtonStyle,VK_OEM_4,NUM_CHANGE);
    QPushButton* btn_KeyRightPar = Get_Button("]","}",ButtonStyle,VK_OEM_6,NUM_CHANGE);
    QPushButton* btn_KeyInclined = Get_Button("\\","|",ButtonStyle,VK_OEM_5,NUM_CHANGE);
    QPushButton* btn_Del = Get_Button("Del","",ButtonStyle,VK_DELETE,NO_CHANGE);

    //特殊处理的长宽
    btn_Tab->setFixedWidth(100);
    btn_Del->setFixedWidth(60);

    mKeyTopLayout->addWidget(btn_Tab);
    mKeyTopLayout->addWidget(btn_KeyQ);
    mKeyTopLayout->addWidget(btn_KeyW);
    mKeyTopLayout->addWidget(btn_KeyE);
    mKeyTopLayout->addWidget(btn_KeyR);
    mKeyTopLayout->addWidget(btn_KeyT);
    mKeyTopLayout->addWidget(btn_KeyY);
    mKeyTopLayout->addWidget(btn_KeyU);
    mKeyTopLayout->addWidget(btn_KeyI);
    mKeyTopLayout->addWidget(btn_KeyO);
    mKeyTopLayout->addWidget(btn_KeyP);
    mKeyTopLayout->addWidget(btn_KeyLeftPar);
    mKeyTopLayout->addWidget(btn_KeyRightPar);
    mKeyTopLayout->addWidget(btn_KeyInclined);
    mKeyTopLayout->addWidget(btn_Del);

    //A-L
    QHBoxLayout* mKeyMidLayout = new QHBoxLayout();
    mKeyMidLayout->setSpacing(1);
    mKeyMidLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_Caps = Get_Button("Caps","",ButtonStyle,VK_CAPITAL,NO_CHANGE);
    QPushButton* btn_KeyA = Get_Button("a","A",ButtonStyle,0x41,LETTER_CHANGE);
    QPushButton* btn_KeyS = Get_Button("s","S",ButtonStyle,0x53,LETTER_CHANGE);
    QPushButton* btn_KeyD = Get_Button("d","D",ButtonStyle,0x44,LETTER_CHANGE);
    QPushButton* btn_KeyF = Get_Button("f","F",ButtonStyle,0x46,LETTER_CHANGE);
    QPushButton* btn_KeyG = Get_Button("g","G",ButtonStyle,0x47,LETTER_CHANGE);
    QPushButton* btn_KeyH = Get_Button("h","H",ButtonStyle,0x48,LETTER_CHANGE);
    QPushButton* btn_KeyJ = Get_Button("j","J",ButtonStyle,0x4a,LETTER_CHANGE);
    QPushButton* btn_KeyK = Get_Button("k","K",ButtonStyle,0x4b,LETTER_CHANGE);
    QPushButton* btn_KeyL = Get_Button("l","L",ButtonStyle,0x4c,LETTER_CHANGE);
    QPushButton* btn_KeyColon = Get_Button(";",":",ButtonStyle,VK_OEM_1,NUM_CHANGE);
    QPushButton* btn_KeyQuotes= Get_Button("'","\"",ButtonStyle,VK_OEM_7,NUM_CHANGE);
    QPushButton* btn_KeyEnter = Get_Button("Enter","",ButtonStyle,VK_RETURN,NO_CHANGE);

    //特殊宽
    btn_Caps->setFixedWidth(120);
    btn_KeyEnter->setFixedWidth(120);

    mKeyMidLayout->addWidget(btn_Caps);
    mKeyMidLayout->addWidget(btn_KeyA);
    mKeyMidLayout->addWidget(btn_KeyS);
    mKeyMidLayout->addWidget(btn_KeyD);
    mKeyMidLayout->addWidget(btn_KeyF);
    mKeyMidLayout->addWidget(btn_KeyG);
    mKeyMidLayout->addWidget(btn_KeyH);
    mKeyMidLayout->addWidget(btn_KeyJ);
    mKeyMidLayout->addWidget(btn_KeyK);
    mKeyMidLayout->addWidget(btn_KeyL);
    mKeyMidLayout->addWidget(btn_KeyColon);
    mKeyMidLayout->addWidget(btn_KeyQuotes);
    mKeyMidLayout->addWidget(btn_KeyEnter);

    //Z-M
    QHBoxLayout* mKeyBottomLayout = new QHBoxLayout();
    mKeyBottomLayout->setSpacing(1);
    mKeyBottomLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_LeftShift = Get_Button("Shift","",ButtonStyle,0,NO_CHANGE);
    QPushButton* btn_KeyZ = Get_Button("z","Z",ButtonStyle,0x5a,LETTER_CHANGE);
    QPushButton* btn_KeyX = Get_Button("x","X",ButtonStyle,0x58,LETTER_CHANGE);
    QPushButton* btn_KeyC = Get_Button("c","C",ButtonStyle,0x43,LETTER_CHANGE);
    QPushButton* btn_KeyV = Get_Button("v","V",ButtonStyle,0x56,LETTER_CHANGE);
    QPushButton* btn_KeyB = Get_Button("b","B",ButtonStyle,0x42,LETTER_CHANGE);
    QPushButton* btn_KeyN = Get_Button("n","N",ButtonStyle,0x4e,LETTER_CHANGE);
    QPushButton* btn_KeyM = Get_Button("m","M",ButtonStyle,0x4d,LETTER_CHANGE);
    QPushButton* btn_KeyComma = Get_Button(",","<",ButtonStyle,VK_OEM_COMMA,NUM_CHANGE);
    QPushButton* btn_BPoint = Get_Button(".",">",ButtonStyle,VK_OEM_PERIOD,NUM_CHANGE);
    QPushButton* btn_Inclined = Get_Button("/","?",ButtonStyle,VK_OEM_2,NUM_CHANGE);
    QPushButton* btn_KeyUp = Get_Button("↑","",ButtonStyle,VK_UP,NO_CHANGE);
    QPushButton* btn_RightShift = Get_Button("Shift","",ButtonStyle,0,NO_CHANGE);

    //
    btn_LeftShift->setFixedWidth(150);
    btn_RightShift->setFixedWidth(150);
    btn_KeyUp->setFixedWidth(75);


    mKeyBottomLayout->addWidget(btn_LeftShift);
    mKeyBottomLayout->addWidget(btn_KeyZ);
    mKeyBottomLayout->addWidget(btn_KeyX);
    mKeyBottomLayout->addWidget(btn_KeyC);
    mKeyBottomLayout->addWidget(btn_KeyV);
    mKeyBottomLayout->addWidget(btn_KeyB);
    mKeyBottomLayout->addWidget(btn_KeyN);
    mKeyBottomLayout->addWidget(btn_KeyM);
    mKeyBottomLayout->addWidget(btn_KeyComma);
    mKeyBottomLayout->addWidget(btn_BPoint);
    mKeyBottomLayout->addWidget(btn_Inclined);
    mKeyBottomLayout->addWidget(btn_KeyUp);
    mKeyBottomLayout->addWidget(btn_RightShift);

    //Ctrl-shift
    QHBoxLayout* mBottomLayout = new QHBoxLayout();
    mBottomLayout = new QHBoxLayout();
    mBottomLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_Num = Get_Button("123","",ButtonStyle,0,NO_CHANGE);
    QPushButton* btn_Ctrl = Get_Button("Ctrl","",ButtonStyle,0,NO_CHANGE);
    QPushButton* btn_ALT = Get_Button("Alt","",ButtonStyle,0,NO_CHANGE);
    QPushButton* btn_Space = Get_Button("Space","",ButtonStyle,VK_SPACE,NO_CHANGE);
    QPushButton* btn_KeyLeft = Get_Button("←","",ButtonStyle,VK_LEFT,NO_CHANGE);
    QPushButton* btn_KeyDown = Get_Button("↓","",ButtonStyle,VK_DOWN,NO_CHANGE);
    QPushButton* btn_KeyRight = Get_Button("→","",ButtonStyle,VK_RIGHT,NO_CHANGE);
    QPushButton* btn_KeyClose = Get_Button("Close","",ButtonStyle,0,NO_CHANGE);

    connect(btn_KeyClose,SIGNAL(clicked(bool)),this,SLOT(CloseButtonSlot()));
    connect(btn_LeftShift,SIGNAL(clicked(bool)),this,SLOT(LShiftButtonClickSlot()));
    connect(btn_RightShift,SIGNAL(clicked(bool)),this,SLOT(LShiftButtonClickSlot()));
    connect(btn_Ctrl,SIGNAL(clicked(bool)),this,SLOT(CtrlButtonClickSlot()));
    connect(btn_ALT,SIGNAL(clicked(bool)),this,SLOT(AltButtonClickSlot()));
    connect(btn_Caps,SIGNAL(clicked(bool)),this,SLOT(CapsButtonClickSlot()));
    connect(btn_Num,SIGNAL(clicked(bool)),this,SLOT(NumKeyBoardShow()));

    //
    btn_Num->setFixedWidth(70);
    btn_Ctrl->setFixedWidth(50);
    btn_Space->setFixedWidth(340);
    btn_KeyLeft->setFixedWidth(75);
    btn_KeyDown->setFixedWidth(75);
    btn_KeyRight->setFixedWidth(75);
    btn_KeyClose->setFixedWidth(75);

    mBottomLayout->addWidget(btn_Num);
    mBottomLayout->addWidget(btn_Ctrl);
    mBottomLayout->addWidget(btn_ALT);
    mBottomLayout->addWidget(btn_Space);
    mBottomLayout->addWidget(btn_KeyLeft);
    mBottomLayout->addWidget(btn_KeyDown);
    mBottomLayout->addWidget(btn_KeyRight);
    mBottomLayout->addWidget(btn_KeyClose);

    //Add
    mLayout->addLayout(mTopLayout);
    mLayout->addLayout(mKeyTopLayout);
    mLayout->addLayout(mKeyMidLayout);
    mLayout->addLayout(mKeyBottomLayout);
    mLayout->addLayout(mBottomLayout);
    mWidget->setLayout(mLayout);

    btn_ALT->setCheckable(true);
    btn_LeftShift->setCheckable(true);
    btn_RightShift->setCheckable(true);
    btn_Caps->setCheckable(true);
    btn_Ctrl->setCheckable(true);

    this->connect(this,&DB_Hmi_Gui_AlpKeyboard::CapLight,this,[=](bool isLight){
        btn_Caps->setChecked(isLight);
        emit UpdateWarrning(isLight);
    });
    this->connect(this,&DB_Hmi_Gui_AlpKeyboard::ShiftLight,this,[=](bool isLight){
        btn_LeftShift->setChecked(isLight);
        btn_RightShift->setChecked(isLight);
    });
    this->connect(this,&DB_Hmi_Gui_AlpKeyboard::AltLight,this,[=](bool isLight){
        btn_ALT->setChecked(isLight);
    });
    this->connect(this,&DB_Hmi_Gui_AlpKeyboard::CrtlLight,this,[=](bool isLight){
       btn_Ctrl->setChecked(isLight);
    });

    return mWidget;
}

QPushButton* DB_Hmi_Gui_AlpKeyboard::Get_Button(QString text,QString Change_Text,QString style,int key,ChangeType type)/* = NO_CHANGE)*/
{
    QPushButton* btn = new QPushButton();
    btn->setText(text);
    btn->setStyleSheet(style);
    btn->setFixedHeight(60);

    if(key != 0)
        this->connect(btn,&QPushButton::clicked,this,[=](){this->ButtonsClickSlot(key);});

//    if(type == LETTER_CHANGE)
//        this->connect(btn,&QPushButton::clicked,this,[=](){qDebug() << btn->text();});
//    else if(type == NUM_CHANGE)
//        this->connect(btn,&QPushButton::clicked,this,[=](){qDebug() << btn->text();});

    this->connect(this,&DB_Hmi_Gui_AlpKeyboard::Key_Cap,this,[=](){
        if(type == LETTER_CHANGE)
        {
            if(isCap)
            {
                btn->setText(Change_Text);
            }
            else
            {
                btn->setText(text);
            }
        }
    });

    this->connect(this,&DB_Hmi_Gui_AlpKeyboard::Key_SHIFT,this,[=](){
        if(type == NUM_CHANGE)
        {
            if(isShift)
                btn->setText(Change_Text);
            else
                btn->setText(text);
        }
    });

    return btn;
}

DB_Hmi_Gui_AlpKeyboard::~DB_Hmi_Gui_AlpKeyboard()
{

}

bool DB_Hmi_Gui_AlpKeyboard::GetCapsButtonStatus()
{
    bool CapsStatus = false;
    if(LOBYTE(GetKeyState(VK_CAPITAL) > 1))
    {
        if(LOBYTE(GetKeyState(VK_CAPITAL)) == 128)
        {
            CapsStatus = false;
        }
        else if(LOBYTE(GetKeyState(VK_CAPITAL)) == 129)
        {
            CapsStatus = true;
        }
    }
    else
    {
        CapsStatus = LOBYTE(GetKeyState(VK_CAPITAL));
    }
    return CapsStatus;
}

void DB_Hmi_Gui_AlpKeyboard::CheckCapsButtonClicked()
{
    if(isCap==true && isShift == false )
    {
        emit Key_Cap();
    }
    else if(isCap==true && isShift == true)
    {
        emit Key_Cap();
        emit Key_SHIFT();
    }
    else if(isCap==false && (isShift==true || isShift==true))
    {
        emit Key_SHIFT();
    }
    else
    {
        emit Key_Cap();
        emit Key_SHIFT();
    }
}

void DB_Hmi_Gui_AlpKeyboard::CheckShiftButtonClicked()
{
    if(isShift && !isCap)
    {
        emit Key_SHIFT();
    }
    else if(isShift && isCap)
    {
        emit Key_Cap();
        emit Key_SHIFT();
    }
    else if(!isShift && isCap)
    {
        emit Key_Cap();
    }
    else
    {
        emit Key_Cap();
        emit Key_SHIFT();
    }
}

void DB_Hmi_Gui_AlpKeyboard::ShowAndUpdataPos()
{
    show();
    QWidget *widget = qApp->focusWidget();
    if (!widget)
        return;
    QRect widgetRect = widget->rect();
    QPoint panelPos = QPoint(widgetRect.left()-this->rect().width()/3+10, widgetRect.bottom() + 5+70);
    panelPos = widget->mapToGlobal(panelPos);
    move(panelPos);

    isCap = GetCapsButtonStatus();
    CheckCapsButtonClicked();
}

void DB_Hmi_Gui_AlpKeyboard::closeEvent(QCloseEvent *)
{
    emit AlpClose();
}
#if 0
void DB_Hmi_Gui_AlpKeyboard::keyPressEvent(QKeyEvent *e)
{
//    if(e->key() == Qt::Key_CapsLock)
//    {
//        isCap=GetCapsButtonStatus();
//        CheckCapsButtonClicked();
//    }

    QWidget::keyPressEvent(e);
}

void DB_Hmi_Gui_AlpKeyboard::keyReleaseEvent(QKeyEvent *e)
{
//    if(e->key() == Qt::Key_CapsLock)
//    {
//        isCap=GetCapsButtonStatus();
//        CheckCapsButtonClicked();
//    }

    QWidget::keyReleaseEvent(e);
}
#endif

void DB_Hmi_Gui_AlpKeyboard::ButtonsClickSlot(int key)
{
    if(isShift==true && key != VK_CAPITAL )
    {
        keybd_event(VK_RSHIFT, 0, 0, 0);//按键按下
        keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);//按键按下
        keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0);//按键松开
        keybd_event(VK_RSHIFT, 0, KEYEVENTF_KEYUP, 0);//按键松开
        LShiftButtonClickSlot();
    }
    else if(isCtrl && key != VK_CAPITAL )
    {
        keybd_event(VK_CONTROL, 0, 0, 0);//按键按下
        keybd_event(key, 0, 0, 0);//按键按下
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);//按键松开
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);//按键松开
        CtrlButtonClickSlot();
    }
    else if(isAlt && key != VK_CAPITAL )
    {
        keybd_event(VK_MENU, 0, 0, 0);//按键按下
        keybd_event(key, 0, 0, 0);//按键按下
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);//按键松开
        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);//按键松开
        AltButtonClickSlot();
    }
    else
    {
        keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);//按键按下
        keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0);//按键松开
    }
}

void DB_Hmi_Gui_AlpKeyboard::LShiftButtonClickSlot()
{
    if(!isShift)
    {
        isShift=true;
    }
    else
    {
        isShift=false;
    }
    emit ShiftLight(isShift);
    CheckShiftButtonClicked();
}

void DB_Hmi_Gui_AlpKeyboard::CtrlButtonClickSlot()
{
    if(!isCtrl)
    {
        isCtrl=true;
    }
    else
    {
        isCtrl=false;
    }
    emit CrtlLight(isCtrl);
}

void DB_Hmi_Gui_AlpKeyboard::AltButtonClickSlot()
{
    if(!isAlt)
    {
        isAlt=true;
    }
    else
    {
        isAlt=false;
    }
    emit AltLight(isAlt);
}

void DB_Hmi_Gui_AlpKeyboard::CapsButtonClickSlot()
{
    isCap=GetCapsButtonStatus();
    if(!isCap)
    {
        isCap=true;
    }
    else
    {
        isCap=false;
    }
    emit CapLight(isCap);
    CheckCapsButtonClicked();
}

void DB_Hmi_Gui_AlpKeyboard::NumKeyBoardShow()
{
    close();
    emit AlpToNum();
    // NumKeyboard *NumKey=new NumKeyboard(this);
    // NumKey->show();
}

void DB_Hmi_Gui_AlpKeyboard::CloseButtonSlot()
{
    close();
    emit AlpClose();
}


