#include "DB_Hmi_Gui_Numkeyboard.h"
#include <QHBoxLayout>
#include <QPushButton>

#define GET_STR(x) #x

DB_Hmi_Gui_Numkeyboard::DB_Hmi_Gui_Numkeyboard(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::WindowDoesNotAcceptFocus);
    AlpKeyShow=false;

    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* Widget = InitWidget();

    mLayout->addWidget(Widget);
    this->setLayout(mLayout);


}

DB_Hmi_Gui_Numkeyboard::~DB_Hmi_Gui_Numkeyboard()
{

}

QWidget* DB_Hmi_Gui_Numkeyboard::InitWidget()
{
    //Button style
    const QString BtnKeyStyle = GET_STR
    (
        QPushButton{
        background-color: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);
        border:none;
        color:rgb(255,255,255);
        border:1px solid #242424;
        padding:5px;
        min-height:15px;
        border-radius:5px;
        }
        QPushButton:pressed{
        background-color: qlineargradient(spread:pad, x1:1, y1:0.057, x2:1, y2:1, stop:0 rgba(225, 225, 230, 255), stop:1 rgba(200, 200, 200, 255));
        border:none;
        color:rgb(0,0,0);
        border: 1px solid #444444;
        }
    );

    const QString WidgetStyle = "background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);";
    QWidget* mWidget = new QWidget();
    mWidget->setFixedSize(243,243);
    mWidget->setObjectName("mWidget");
    mWidget->setStyleSheet(QString("#mWidget{%1})").arg(WidgetStyle));

    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(1);
    mLayout->setContentsMargins(0,0,0,0);

    //1-3
    QHBoxLayout* mTopNumLayout = new QHBoxLayout();
    mTopNumLayout->setContentsMargins(0,0,0,0);
    mTopNumLayout->setSpacing(1);
    QPushButton* btn_Num1 = Get_Button("1",BtnKeyStyle,VK_NUMPAD1);
    QPushButton* btn_Num2 = Get_Button("2",BtnKeyStyle,VK_NUMPAD1);
    QPushButton* btn_Num3 = Get_Button("3",BtnKeyStyle,VK_NUMPAD1);
    QPushButton* btn_Delete = Get_Button("<-",BtnKeyStyle,VK_BACK);
    mTopNumLayout->addWidget(btn_Num1);
    mTopNumLayout->addWidget(btn_Num2);
    mTopNumLayout->addWidget(btn_Num3);
    mTopNumLayout->addWidget(btn_Delete);

    //4-6
    QHBoxLayout* mMidNumLayout = new QHBoxLayout();
    mMidNumLayout->setContentsMargins(0,0,0,0);
    mMidNumLayout->setSpacing(1);
    QPushButton* btn_Num4 = Get_Button("4",BtnKeyStyle,VK_NUMPAD4);
    QPushButton* btn_Num5 = Get_Button("5",BtnKeyStyle,VK_NUMPAD5);
    QPushButton* btn_Num6 = Get_Button("6",BtnKeyStyle,VK_NUMPAD6);
    mMidNumLayout->addWidget(btn_Num4);
    mMidNumLayout->addWidget(btn_Num5);
    mMidNumLayout->addWidget(btn_Num6);
    mMidNumLayout->addStretch();

    //7-9
    QHBoxLayout* mBottomNumLayout = new QHBoxLayout();
    mBottomNumLayout->setSpacing(1);
    mBottomNumLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_Num7 = Get_Button("7",BtnKeyStyle,VK_NUMPAD7);
    QPushButton* btn_Num8 = Get_Button("8",BtnKeyStyle,VK_NUMPAD8);
    QPushButton* btn_Num9 = Get_Button("9",BtnKeyStyle,VK_NUMPAD9);
    QPushButton* btn_NumSub = Get_Button("-",BtnKeyStyle,VK_SUBTRACT);
    mBottomNumLayout->addWidget(btn_Num7);
    mBottomNumLayout->addWidget(btn_Num8);
    mBottomNumLayout->addWidget(btn_Num9);
    mBottomNumLayout->addWidget(btn_NumSub);

    //0-Enter
    QHBoxLayout* mBottomSymbolLayout = new QHBoxLayout();
    mBottomSymbolLayout->setSpacing(1);
    mBottomSymbolLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_Num0 = Get_Button("0",BtnKeyStyle,VK_NUMPAD0);
    btn_Num0->setFixedSize(120,60);
    QPushButton* btn_Point = Get_Button(".",BtnKeyStyle,VK_DECIMAL);
    QPushButton* btn_Enter = Get_Button("->",BtnKeyStyle,999);
    mBottomSymbolLayout->addWidget(btn_Num0);
    mBottomSymbolLayout->addWidget(btn_Point);
    mBottomSymbolLayout->addWidget(btn_Enter);

    //Add
    mLayout->addLayout(mTopNumLayout);
    mLayout->addLayout(mMidNumLayout);
    mLayout->addLayout(mBottomNumLayout);
    mLayout->addLayout(mBottomSymbolLayout);
    mWidget->setLayout(mLayout);

    return mWidget;
}

QPushButton* DB_Hmi_Gui_Numkeyboard::Get_Button(QString text,QString style,int key)
{
    QPushButton* btn = new QPushButton();
    btn->setText(text);
    btn->setIcon(QIcon(""));
    btn->setStyleSheet(style);
    btn->setFixedSize(60,60);

    if(key != 999)
        this->connect(btn,&QPushButton::clicked,this,[=](){ButtonsClickedSlot(key);});
    else
        this->connect(btn,&QPushButton::clicked,this,[=](){this->NumKeyboardClose();});

    return btn;
}

void DB_Hmi_Gui_Numkeyboard::UpdatePos()
{
    QWidget *widget = qApp->focusWidget();
   // QWidget *widget = keyBoard->getFocusedWidget();
    if (!widget)
        return;
    QRect widgetRect = widget->rect();
    QPoint panelPos = QPoint(widgetRect.left(), widgetRect.bottom() + 2);
    panelPos = widget->mapToGlobal(panelPos);

    QDesktopWidget *deskWgt = QApplication::desktop();
    int KeyBoardWidth=rect().width();
    int KeyBoardHeight=rect().height();
    if(panelPos.x()+KeyBoardWidth > deskWgt->width() && panelPos.y()+KeyBoardHeight < deskWgt->height())//宽越界
    {
        QPoint RBpos=QPoint(widgetRect.right(),widgetRect.bottom()+2);
        RBpos=widget->mapToGlobal(RBpos);
        QPoint pos;
        pos.setX(RBpos.x()-KeyBoardWidth);
        pos.setY(RBpos.y());
        move(pos);
    }
    else if(panelPos.x()+KeyBoardWidth < deskWgt->width() && panelPos.y()+KeyBoardHeight > deskWgt->height())//高越界
    {
        QPoint LTpos=QPoint(widgetRect.left(),widgetRect.top()-2);
        LTpos=widget->mapToGlobal(LTpos);
        QPoint pos;
        pos.setX(LTpos.x());
        pos.setY(LTpos.y()-KeyBoardHeight);
        move(pos);
    }
    else if(panelPos.x()+KeyBoardWidth > deskWgt->width() && panelPos.y()+KeyBoardHeight > deskWgt->height())//宽和高都越界
    {
        QPoint RTpos=QPoint(widgetRect.right(),widgetRect.top()-2);
        RTpos=widget->mapToGlobal(RTpos);
        QPoint pos;
        pos.setX(RTpos.x()-KeyBoardWidth);
        pos.setY(RTpos.y()-KeyBoardHeight);
        move(pos);
    }
    else//不越界
    {
        move(panelPos);
    }
}

void DB_Hmi_Gui_Numkeyboard::ShowAndUpdatePos()
{
    if(AlpKeyShow==true)
    {
        return;
    }
    else
    {
        show();
        UpdatePos();
        selectAllText();
    }

}

void DB_Hmi_Gui_Numkeyboard::selectAllText()
{
    keybd_event(VK_HOME, 0, 0, 0);//按键按下
    keybd_event(VK_HOME, 0, KEYEVENTF_KEYUP, 0);//按键松开
    Sleep(100);

    keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);//按键按下
    keybd_event(VK_END, 0,KEYEVENTF_EXTENDEDKEY | 0, 0);//按键按下
    Sleep(100);
    keybd_event(VK_END, 0, KEYEVENTF_EXTENDEDKEY| KEYEVENTF_KEYUP, 0);//按键松开
    keybd_event(VK_SHIFT, 0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);//按键松开
}

void DB_Hmi_Gui_Numkeyboard::ButtonsClickedSlot(int key)
{
    keybd_event(key, 0, 0, 0);//按键按下
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);//按键松开
}

void DB_Hmi_Gui_Numkeyboard::NumKeyboardClose()
{
    //ButtonsClickedSlot(VK_TAB);//键盘关闭，按下Tab键，失去焦点；
    close();
}

void DB_Hmi_Gui_Numkeyboard::AlpKeyBoardShow()
{
    hide();
    DB_Hmi_Gui_AlpKeyboard *AlpKey=new DB_Hmi_Gui_AlpKeyboard(this);
    AlpKey->show();
    AlpKeyShow=true;
    connect(AlpKey,SIGNAL(AlpClose()),this,SLOT(AlpKeyBoardClose()));
    connect(AlpKey,SIGNAL(AlpToNum()),this,SLOT(AlpToNumSLot()));
}

void DB_Hmi_Gui_Numkeyboard::AlpKeyBoardClose()
{
    AlpKeyShow=false;
}

void DB_Hmi_Gui_Numkeyboard::AlpToNumSLot()
{
    AlpKeyShow=false;
    show();
}
