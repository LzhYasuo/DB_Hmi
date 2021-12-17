#include "DB_Hmi_Gui_Auto_Manual.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QPixmap>
#include <QBitmap>

#include "DB_Hmi_Gui_3D.h"
#include "Public/Public_Control.h"
#include "Public/Public_Str.h"
#include "Public/Public_Function.h"
#include "DB_Hmi_Gui_NumKeyBoard.h"
#include "Socket/RunTcp.h"

DB_Hmi_Gui_Auto_Manual::DB_Hmi_Gui_Auto_Manual(QWidget* parent)
    :QWidget (parent)
{
    this->init();
//    Key = new DB_Hmi_Gui_Numkeyboard(this);
}

DB_Hmi_Gui_Auto_Manual::~DB_Hmi_Gui_Auto_Manual()
{

}

//bool DB_Hmi_Gui_Auto_Manual::eventFilter(QObject *obj, QEvent *event)
//{
//    if(obj->inherits("QDoubleSpinBox")  /*||(obj->inherits("QLineEdit") && !obj->parent()->inherits("QDialog"))*/)
//    {
//        if(event->type()==QEvent::FocusIn)
//        {
//            Key->ShowAndUpdatePos();
//        }
//        else if(event->type()==QEvent::FocusOut)
//        {
//            Key->close();
//        }
//    }
//    else if(obj->inherits("QSpinBox"))
//    {
//        if(event->type()==QEvent::FocusIn)
//        {
//            Key->ShowAndUpdatePos();
//        }
//        else if(event->type()==QEvent::FocusOut)
//        {
//            Key->close();
//        }
//    }
//    return QWidget::eventFilter(obj, event);
//#if 0
//    QList<QDoubleSpinBox*> boxList = this->findChildren<QDoubleSpinBox*>();
//    for(int i = 0; i < boxList.size(); i++)
//    {
//        if(obj == boxList.at(i))
//        {
//            if(event->type()==QEvent::FocusIn)
//            {
//                Key->ShowAndUpdatePos();
//            }
//            else if(event->type()==QEvent::FocusOut)
//            {
//                Key->close();
//            }
//        }
//    }
//    QList<QSpinBox*> IBoxList = this->findChildren<QSpinBox*>();
//    for(int i = 0; i < IBoxList.size(); i++)
//    {
//        if(obj == IBoxList.at(i))
//        {
//            if(event->type()==QEvent::FocusIn)
//            {
//                Key->ShowAndUpdatePos();
//            }
//            else if(event->type()==QEvent::FocusOut)
//            {
//                Key->close();
//            }
//        }
//    }
//    return QWidget::eventFilter(obj, event);
//#endif
//}

void DB_Hmi_Gui_Auto_Manual::init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = InitWidget();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget* DB_Hmi_Gui_Auto_Manual::InitWidget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    DB_Hmi_Gui_3D* OpenGLWidget = new DB_Hmi_Gui_3D();

    QWidget* RightWidget = new QWidget();
    RightWidget->setObjectName("RightWidget");
    RightWidget->setStyleSheet("#RightWidget{background-color:rgb(150,150,150);border:1px solid rgb(230,230,230);}");
    QVBoxLayout* RightLayout = new QVBoxLayout();
    RightLayout->setSpacing(3);
    RightLayout->setContentsMargins(5,5,5,5);

    QWidget* RightTopWigdet = Create_RightTopWidget();

    QWidget* RightTopButtonWidget = Create_RightTopButton();

    QWidget* StackedWidget = Create_StackedWidget();

    QWidget* RightBottomTopWidget = Create_RightBottomTopButton();

    QWidget* RightBottomBottomWidget = Create_RightBottomBottomButton();

    const QString EditStyle = "color:rgb(255,0,0);";
    QTextEdit* Edit = new QTextEdit();
    Edit->setStyleSheet(EditStyle);

    RightLayout->addWidget(RightTopWigdet);
    RightLayout->addWidget(RightTopButtonWidget);
    RightLayout->addWidget(StackedWidget);
    RightLayout->addWidget(RightBottomTopWidget);
    RightLayout->addWidget(RightBottomBottomWidget);
    RightLayout->addWidget(Edit);
    RightLayout->setStretchFactor(RightTopWigdet,3);
    RightLayout->setStretchFactor(RightTopButtonWidget,2);
    RightLayout->setStretchFactor(StackedWidget,1);
    RightLayout->setStretchFactor(RightBottomTopWidget,4);
    RightLayout->setStretchFactor(RightBottomBottomWidget,4);
    RightLayout->setStretchFactor(Edit,2);
    RightWidget->setLayout(RightLayout);

    mLayout->addWidget(OpenGLWidget);
    mLayout->addWidget(RightWidget);
    mLayout->setStretchFactor(OpenGLWidget,4);
    mLayout->setStretchFactor(RightWidget,1);
    mWidget->setLayout(mLayout);

    this->connect(RunTcp::Get(),&RunTcp::Set_AlarmValue_Signal,this,[=](QList<QVariant> List){
        Edit->append(List.at(0).toString() + " : " + List.at(1).toString() + " : " + List.at(2).toString());
    });

    return mWidget;
}

QWidget* DB_Hmi_Gui_Auto_Manual::Create_RightTopWidget()
{
    const QString LeftUpKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopKeyUpStyle,{}});
    const QString LeftDownKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopKeyDownStyle,{}});
    const QString LeftLeftKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopKeyLeftStyle,{}});
    const QString LeftRightKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopKeyRightStyle,{}});
    const QString LeftMidKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopKeyMidStyle,{}});

    const QString MidUpKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopMidUpStyle,{}});
    const QString MidDownKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopMidDownStyle,{}});
    const QString MidinverseKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopMidinverseStyle,{}});
    const QString MidShunKeyButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopMidShunStyle,{}});
    const QString RightButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopRightButtonStyle,{}});

    QWidget* RightTopWidget = new QWidget();
    RightTopWidget->setObjectName("RightTopWidget");
    RightTopWidget->setStyleSheet("#RightTopWidget{border:1px solid rgb(230,230,230);}");

//    RightTopWidget->setFixedHeight(150);
    QHBoxLayout* mRightTopLayout = new QHBoxLayout();
    mRightTopLayout->setSpacing(5);
    mRightTopLayout->setContentsMargins(5,5,5,5);

    QWidget* RightTopLeftMidWidget = new QWidget();
    RightTopLeftMidWidget->setObjectName("RightTopLeftMidWidget");
    RightTopLeftMidWidget->setStyleSheet("#RightTopLeftMidWidget{border:1px solid rgb(230,230,230);}");
    QHBoxLayout* RightTopLeftMidLayout = new QHBoxLayout();
    RightTopLeftMidLayout->setSpacing(0);
    RightTopLeftMidLayout->setContentsMargins(0,0,0,0);

    //右上的最左
    QWidget* RightTopLeftWidget = new QWidget();
    RightTopLeftWidget->setFixedWidth(150);
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QPushButton* LeftKeyButton = Get_Button("","",35,85,"VISO_BTN_LEFT",LeftLeftKeyButtonStyle);
    QPushButton* UpKeyButton = Get_Button("","",85,35,"VISO_BTN_UP",LeftUpKeyButtonStyle);
    QPushButton* DownKeyButton = Get_Button("","",85,35,"VISO_BTN_DOWN",LeftDownKeyButtonStyle);
    QPushButton* RightKeyButton = Get_Button("","",35,85,"VISO_BTN_RIGHT",LeftRightKeyButtonStyle);
    QPushButton* MidKeyButton = Get_Button("","",65,65,"VISO_BTN_SURE",LeftMidKeyButtonStyle);
//    mLayout->addWidget(LeftKeyButton,0,Qt::AlignLeft);
//    mLayout->addWidget(UpKeyButton,0,Qt::AlignTop);
//    mLayout->addWidget(DownKeyButton,0,Qt::AlignBottom);
//    mLayout->addWidget(RightKeyButton,0,Qt::AlignRight);
//    mLayout->addWidget(MidKeyButton,0,Qt::AlignCenter);
//    RightTopLeftWidget->setLayout(mLayout);
#if 1
    LeftKeyButton->setParent(RightTopLeftWidget);
    UpKeyButton->setParent(RightTopLeftWidget);
    DownKeyButton->setParent(RightTopLeftWidget);
    RightKeyButton->setParent(RightTopLeftWidget);
    MidKeyButton->setParent(RightTopLeftWidget);
    LeftKeyButton->setGeometry(10,30,35,85);
    UpKeyButton->setGeometry(30,10,85,35);
    DownKeyButton->setGeometry(30,100,85,35);
    RightKeyButton->setGeometry(100,30,35,85);
    MidKeyButton->setGeometry(40,40,65,65);
#endif


    //右上的中部
    QWidget* RightTopMidWidget = new QWidget();
//    RightTopMidWidget->setFixedWidth(100);
    QVBoxLayout* RightTopMidLayout = new QVBoxLayout();
    RightTopMidLayout->setSpacing(0);
    RightTopMidLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout* RightTopMidTopLayout = new QHBoxLayout();
    RightTopMidTopLayout->setSpacing(10);
    RightTopMidTopLayout->setContentsMargins(5,10,5,10);
    QPushButton* btn_Up = Get_Button("","",0,40,"VISO_UP",MidUpKeyButtonStyle);
    QPushButton* btn_inverse = Get_Button("","",0,40,"VISO_PRE",MidDownKeyButtonStyle);
//    RightTopMidTopLayout->addStretch();
    RightTopMidTopLayout->addWidget(btn_Up);
//    RightTopMidTopLayout->addStretch();
    RightTopMidTopLayout->addWidget(btn_inverse);
//    RightTopMidTopLayout->addStretch();

    QHBoxLayout* RightTopMidBottomLayout = new QHBoxLayout();
    RightTopMidBottomLayout->setSpacing(10);
    RightTopMidBottomLayout->setContentsMargins(5,10,5,10);
    QPushButton* btn_Down = Get_Button("","",0,40,"VISO_DOWN",MidinverseKeyButtonStyle);
    QPushButton* btn_shun = Get_Button("","",0,40,"VISO_NEXT",MidShunKeyButtonStyle);
//    RightTopMidBottomLayout->addStretch();
    RightTopMidBottomLayout->addWidget(btn_Down);
//    RightTopMidBottomLayout->addStretch();
    RightTopMidBottomLayout->addWidget(btn_shun);
//    RightTopMidBottomLayout->addStretch();

    RightTopMidLayout->addLayout(RightTopMidTopLayout);
    RightTopMidLayout->addLayout(RightTopMidBottomLayout);
    RightTopMidWidget->setLayout(RightTopMidLayout);

    //右上的最右
    QWidget* RightTopBottomWidget = new QWidget();
//    RightTopBottomWidget->setFixedWidth(100);
    RightTopBottomWidget->setObjectName("RightTopBottomWidget");
    RightTopBottomWidget->setStyleSheet("#RightTopBottomWidget{border:1px solid rgb(230,230,230);}");
    QVBoxLayout* RightTopBottomLayout = new QVBoxLayout();
    RightTopBottomLayout->setSpacing(0);
    RightTopBottomLayout->setContentsMargins(5,5,5,5);

    QPushButton* btn_tag = Get_Button("","",0,40,"VISO_TRRBTN1",RightButtonStyle);
    QPushButton* btn_returntag = Get_Button("","",0,40,"VISO_TRRBTN2",RightButtonStyle);
    QWidget* XWidget = Public_Control::Create_Labal_Value("X","","RightTopXText","RightTopXValue");
    QWidget* YWidget = Public_Control::Create_Labal_Value("Y","","RightTopYText","RightTopYValue");

    RightTopBottomLayout->addWidget(btn_tag);
    RightTopBottomLayout->addWidget(btn_returntag);
    RightTopBottomLayout->addWidget(XWidget);
    RightTopBottomLayout->addWidget(YWidget);
    RightTopBottomWidget->setLayout(RightTopBottomLayout);

    RightTopLeftMidLayout->addWidget(RightTopLeftWidget);
    RightTopLeftMidLayout->addWidget(RightTopMidWidget);
    RightTopLeftMidLayout->setStretchFactor(RightTopLeftWidget,1);
    RightTopLeftMidLayout->setStretchFactor(RightTopMidWidget,1);
    RightTopLeftMidWidget->setLayout(RightTopLeftMidLayout);

    mRightTopLayout->addWidget(RightTopLeftMidWidget);
    mRightTopLayout->addWidget(RightTopBottomWidget);
    mRightTopLayout->setStretchFactor(RightTopLeftMidWidget,3);
    mRightTopLayout->setStretchFactor(RightTopBottomWidget,1);
    RightTopWidget->setLayout(mRightTopLayout);

    return RightTopWidget;
}

QWidget* DB_Hmi_Gui_Auto_Manual::Create_RightTopButton()
{
    QWidget* RightTopButtonWidget = new QWidget();
    RightTopButtonWidget->setObjectName("RightTopButtonWidget");
    RightTopButtonWidget->setStyleSheet("#RightTopButtonWidget{border:1px solid rgb(230,230,230)}");
//    RightTopButtonWidget->setFixedHeight(110);
    QVBoxLayout* RightTopButtonLayout = new QVBoxLayout();
    RightTopButtonLayout->setSpacing(5);
    RightTopButtonLayout->setContentsMargins(5,5,5,5);

    const QString RightTopButtonTopStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopMidButtonStyle,{}});

    //上半部的按钮
    QHBoxLayout* RightTopButtonTopLayout = new QHBoxLayout();
    RightTopButtonTopLayout->setSpacing(0);
    RightTopButtonTopLayout->setContentsMargins(0,0,0,0);

    QPushButton* btn_1 = Get_Button("",":/Icon/Img/Icon/backpoint.png",100,50,"VISO_TBTN1",RightTopButtonTopStyle);
    QPushButton* btn_2 = Get_Button("",":/Icon/Img/Icon/jcont32.png",100,50,"VISO_TBTN2",RightTopButtonTopStyle);
    QPushButton* btn_3 = Get_Button("",":/Icon/Img/Icon/jincr32.png",100,50,"VISO_TBTN3",RightTopButtonTopStyle);
    QPushButton* btn_4 = Get_Button("",":/Icon/Img/Icon/jwheel32.png",100,50,"VISO_TBTN4",RightTopButtonTopStyle);

//    RightTopButtonTopLayout->addStretch();
    RightTopButtonTopLayout->addWidget(btn_1);
    RightTopButtonTopLayout->addWidget(btn_2);
    RightTopButtonTopLayout->addWidget(btn_3);
    RightTopButtonTopLayout->addWidget(btn_4);
//    RightTopButtonTopLayout->addStretch();

    //下半部的按钮
    QHBoxLayout* RightTopButtonBottomLayout = new QHBoxLayout();
    RightTopButtonBottomLayout->setSpacing(0);
    RightTopButtonBottomLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_5 = Get_Button("",":/Icon/Img/Icon/backpoint.png",100,50,"VISO_TBTN5",RightTopButtonTopStyle);
    QPushButton* btn_6 = Get_Button("",":/Icon/Img/Icon/jcont32.png",100,50,"VISO_TBTN6",RightTopButtonTopStyle);
    QPushButton* btn_7 = Get_Button("",":/Icon/Img/Icon/jincr32.png",100,50,"VISO_TBTN7",RightTopButtonTopStyle);
    QPushButton* btn_8 = Get_Button("",":/Icon/Img/Icon/jwheel32.png",100,50,"VISO_TBTN8",RightTopButtonTopStyle);

//    RightTopButtonBottomLayout->addStretch();
    RightTopButtonBottomLayout->addWidget(btn_5);
    RightTopButtonBottomLayout->addWidget(btn_6);
    RightTopButtonBottomLayout->addWidget(btn_7);
    RightTopButtonBottomLayout->addWidget(btn_8);
//    RightTopButtonBottomLayout->addStretch();

    RightTopButtonLayout->addLayout(RightTopButtonTopLayout);
    RightTopButtonLayout->addLayout(RightTopButtonBottomLayout);
    RightTopButtonWidget->setLayout(RightTopButtonLayout);

    return RightTopButtonWidget;
}

//右边的Stacked
QWidget* DB_Hmi_Gui_Auto_Manual::Create_StackedWidget()
{
    const QString DoubleStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopMidDoubleSPinStyle,{}});
    const QString RadioStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopMidRadioButtonStyle,{}});

    QWidget* mWidget = new QWidget();
//    mWidget->setFixedHeight(45);
    mWidget->setObjectName("mWidget");
    mWidget->setStyleSheet("#mWidget{border:1px solid rgb(230,230,230);}");

    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(5);
    mLayout->setContentsMargins(5,5,5,5);

    QStackedWidget* mSWidget = new QStackedWidget();

    QWidget* FirstWidget = new QWidget();
    QHBoxLayout* FirstLayout = new QHBoxLayout();
    FirstLayout->setSpacing(0);
    FirstLayout->setContentsMargins(0,0,0,0);

    QRadioButton* btn_small = new QRadioButton();
    btn_small->setText("0.1mm");
//    btn_small->setFixedHeight(40);
    btn_small->setStyleSheet(RadioStyle);

    QRadioButton* btn_1small = new QRadioButton();
    btn_1small->setText("1mm");
    btn_1small->setStyleSheet(RadioStyle);

    QRadioButton* btn_5small = new QRadioButton();
    btn_5small->setText("5mm");
    btn_5small->setStyleSheet(RadioStyle);

    QRadioButton* btn_10small = new QRadioButton();
    btn_10small->setText("10mm");
    btn_10small->setStyleSheet(RadioStyle);

    QHBoxLayout* mOther = new QHBoxLayout();
    mOther->setSpacing(0);
    mOther->setContentsMargins(0,0,0,0);

    QRadioButton* btn_15small = new QRadioButton();
    btn_15small->setStyleSheet(RadioStyle);
    QDoubleSpinBox* box = new QDoubleSpinBox();
    box->setStyleSheet("");
    mOther->addWidget(btn_15small);
    mOther->addWidget(box);

    FirstLayout->addWidget(btn_small);
    FirstLayout->addWidget(btn_1small);
    FirstLayout->addWidget(btn_5small);
    FirstLayout->addWidget(btn_10small);
    FirstLayout->addLayout(mOther);
    FirstWidget->setLayout(FirstLayout);

    QWidget* SecondWidget = new QWidget();
    QHBoxLayout* SecondLayout = new QHBoxLayout();
    SecondLayout->setSpacing(0);
    SecondLayout->setContentsMargins(0,0,0,0);

    QPushButton* btn_1 = Get_Button("");
    QPushButton* btn_2 = Get_Button("");
    QPushButton* btn_3 = Get_Button("");
    QPushButton* btn_4 = Get_Button("");
    QPushButton* btn_5 = Get_Button("");
    QPushButton* btn_6 = Get_Button("");
    QPushButton* btn_7 = Get_Button("");

    SecondLayout->addWidget(btn_1);
    SecondLayout->addWidget(btn_2);
    SecondLayout->addWidget(btn_3);
    SecondLayout->addWidget(btn_4);
    SecondLayout->addWidget(btn_5);
    SecondLayout->addWidget(btn_6);
    SecondLayout->addWidget(btn_7);
    SecondWidget->setLayout(SecondLayout);

    mSWidget->addWidget(FirstWidget);
    mSWidget->addWidget(SecondWidget);

    mLayout->addWidget(mSWidget);
    mWidget->setLayout(mLayout);

    return mWidget;

}

//右下上面的按钮
QWidget* DB_Hmi_Gui_Auto_Manual::Create_RightBottomTopButton()
{
    QWidget* mWidget = new QWidget();
    mWidget->setObjectName("mWidget");
    mWidget->setStyleSheet("#mWidget{border:1px solid rgb(230,230,230)}");
//    mWidget->setFixedHeight(190);

    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(2);
    mLayout->setContentsMargins(2,2,2,2);

    //左边的
    QWidget* mLeftWidget = new QWidget();
    mLeftWidget->setObjectName("mLeftWidget");
    mLeftWidget->setStyleSheet("#mLeftWidget{border:2px solid rgb(150,150,150)}");
    QVBoxLayout* mLeft = new QVBoxLayout();
    mLeft->setSpacing(0);
    mLeft->setContentsMargins(2,2,2,2);

    const QString ButtonStyle = Public_Str::Get_Sty(Style_Css{AutoManualRightTopBottomTopButtonSytle,{}});
    //左边的上面一层
    QHBoxLayout* mLeftFirst = new QHBoxLayout();
    mLeftFirst->setSpacing(0);
    mLeftFirst->setContentsMargins(0,0,0,0);
    QPushButton* btn_1 = Get_Button("","",0,45,"VISO_MLBTN1",ButtonStyle);
    QPushButton* btn_2 = Get_Button("","",0,45,"VISO_MLBTN2",ButtonStyle);
    QPushButton* btn_3 = Get_Button("","",0,45,"VISO_MLBTN3",ButtonStyle);
    mLeftFirst->addWidget(btn_1);
    mLeftFirst->addWidget(btn_2);
    mLeftFirst->addWidget(btn_3);

    //左边的第二层
    QHBoxLayout* mLeftSecond = new QHBoxLayout();
    mLeftSecond->setSpacing(0);
    mLeftSecond->setContentsMargins(0,0,0,0);
    QPushButton* btn_4 = Get_Button("","",0,45,"VISO_MLBTN4",ButtonStyle);
    QDoubleSpinBox* lbl_1 = new QDoubleSpinBox();
    lbl_1->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
//    lbl_1->setFixedHeight(45);
    QPushButton* btn_6 = Get_Button("","",0,45,"VISO_MLBTN5",ButtonStyle);
    mLeftSecond->addWidget(btn_4);
    mLeftSecond->addWidget(lbl_1);
    mLeftSecond->addWidget(btn_6);

    //左边的第三层
    QHBoxLayout* mLeftThird = new QHBoxLayout();
    mLeftThird->setSpacing(0);
    mLeftThird->setContentsMargins(0,0,0,0);
    QPushButton* btn_7 = Get_Button("","",0,45,"VISO_MLBTN6",ButtonStyle);
    mLeftThird->addWidget(btn_7);

    //左边的第四层
    QHBoxLayout* mLeftFour = new QHBoxLayout();
    mLeftFour->setSpacing(0);
    mLeftFour->setContentsMargins(0,0,0,0);
    QPushButton* btn_8 = Get_Button("","",0,45,"VISO_MLBTN7",ButtonStyle);
    QPushButton* btn_9 = Get_Button("","",0,45,"VISO_MLBTN8",ButtonStyle);
    mLeftFour->addWidget(btn_8);
    mLeftFour->addWidget(btn_9);

    mLeft->addLayout(mLeftFirst);
    mLeft->addLayout(mLeftSecond);
    mLeft->addLayout(mLeftThird);
    mLeft->addLayout(mLeftFour);
    mLeftWidget->setLayout(mLeft);

    //右边的
    QWidget* mRightWidget = new QWidget();
    mRightWidget->setObjectName("mLeftWidget");
    mRightWidget->setStyleSheet("#mLeftWidget{border:2px solid rgb(150,150,150)}");
    QVBoxLayout* mRight = new QVBoxLayout();
    mRight->setSpacing(0);
    mRight->setContentsMargins(2,2,2,2);

    //右边的上面一层
    QHBoxLayout* mRightFirst = new QHBoxLayout();
    mRightFirst->setSpacing(0);
    mRightFirst->setContentsMargins(0,0,0,0);
    QPushButton* btn_10 = Get_Button("","",0,45,"VISO_MRBTN1",ButtonStyle);
    QPushButton* btn_11 = Get_Button("","",0,45,"VISO_MRBTN2",ButtonStyle);
    mRightFirst->addWidget(btn_10);
    mRightFirst->addWidget(btn_11);

    //右边的第二层
    QHBoxLayout* mRightSecond = new QHBoxLayout();
    mRightSecond->setSpacing(0);
    mRightSecond->setContentsMargins(0,0,0,0);
    QPushButton* btn_12 = Get_Button("","",0,45,"VISO_MRBTN3",ButtonStyle);
    QDoubleSpinBox* box_1 = new QDoubleSpinBox();
    box_1->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
//    box_1->setFixedHeight(45);
    mRightSecond->addWidget(btn_12);
    mRightSecond->addWidget(box_1);

    //右边的第三层
    QHBoxLayout* mRightThird = new QHBoxLayout();
    mRightThird->setSpacing(0);
    mRightThird->setContentsMargins(0,0,0,0);
    QPushButton* btn_13 = Get_Button("","",0,45,"VISO_MRBTN4",ButtonStyle);
    QDoubleSpinBox* box_2 = new QDoubleSpinBox();
    //box_2->setFixedHeight(45);
    box_2->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    mRightThird->addWidget(btn_13);
    mRightThird->addWidget(box_2);

    //右边的第四层
    QHBoxLayout* mRightFour = new QHBoxLayout();
    mRightFour->setSpacing(0);
    mRightFour->setContentsMargins(0,0,0,0);
    QPushButton* btn_14 = Get_Button("","",0,45,"VISO_MRBTN5",ButtonStyle);
    mRightFour->addWidget(btn_14);

    mRight->addLayout(mRightFirst);
    mRight->addLayout(mRightSecond);
    mRight->addLayout(mRightThird);
    mRight->addLayout(mRightFour);
    mRightWidget->setLayout(mRight);

    mLayout->addWidget(mLeftWidget);
    mLayout->addWidget(mRightWidget);

    mWidget->setLayout(mLayout);

    return mWidget;
}


//右下下面的按钮
QWidget* DB_Hmi_Gui_Auto_Manual::Create_RightBottomBottomButton()
{
    const QString ButtonStyle = "QPushButton"
                                "{"
                                "border-image:url(:/Icon/Img/Icon/default.png);"
                                "}"
                                "QPushButton:pressed"
                                "{"
                                "border-image:url(:/Img/right.png);"
                                "}";
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    //第一层的按钮
    QHBoxLayout* mTopLayout = new QHBoxLayout();
    mTopLayout->setSpacing(3);
    mTopLayout->setContentsMargins(3,0,3,0);

    QPushButton* btn_1 = Get_Button("","",0,65,"VISO_BBTN1",ButtonStyle);
    QPushButton* btn_2 = Get_Button("","",0,65,"VISO_BBTN2",ButtonStyle);
    QPushButton* btn_3 = Get_Button("","",0,65,"VISO_BBTN3",ButtonStyle);
    QPushButton* btn_4 = Get_Button("","",0,65,"VISO_BBTN4",ButtonStyle);

    mTopLayout->addWidget(btn_1);
    mTopLayout->addWidget(btn_2);
    mTopLayout->addWidget(btn_3);
    mTopLayout->addWidget(btn_4);

    //第二层的按钮
    QHBoxLayout* mMidLayout = new QHBoxLayout();
    mMidLayout->setSpacing(3);
    mMidLayout->setContentsMargins(3,0,3,0);

    QPushButton* btn_5 = Get_Button("","",0,65,"VISO_BBTN5",ButtonStyle);
    QPushButton* btn_6 = Get_Button("","",0,65,"VISO_BBTN6",ButtonStyle);
    QPushButton* btn_7 = Get_Button("","",0,65,"VISO_BBTN7",ButtonStyle);
    QPushButton* btn_8 = Get_Button("","",0,65,"VISO_BBTN8",ButtonStyle);

    mMidLayout->addWidget(btn_5);
    mMidLayout->addWidget(btn_6);
    mMidLayout->addWidget(btn_7);
    mMidLayout->addWidget(btn_8);

    //第三层的按钮
    QHBoxLayout* mButtomLayout = new QHBoxLayout();
    mButtomLayout->setSpacing(3);
    mButtomLayout->setContentsMargins(3,0,3,0);

    QPushButton* btn_9 = Get_Button("","",0,65,"VISO_BBTN9",ButtonStyle);
    QPushButton* btn_10 = Get_Button("","",0,65,"VISO_BBTN10",ButtonStyle);
    QPushButton* btn_11 = Get_Button("","",0,65,"VISO_BBTN11",ButtonStyle);
    QPushButton* btn_12 = Get_Button("","",0,65,"VISO_BBTN12",ButtonStyle);

    mButtomLayout->addWidget(btn_9);
    mButtomLayout->addWidget(btn_10);
    mButtomLayout->addWidget(btn_11);
    mButtomLayout->addWidget(btn_12);

    mLayout->addLayout(mTopLayout);
    mLayout->addLayout(mMidLayout);
    mLayout->addLayout(mButtomLayout);
    mWidget->setLayout(mLayout);

    return mWidget;
}

//PLCSet 接口
void DB_Hmi_Gui_Auto_Manual::PLCSet(QString name,int i)
{
    RunTcp::Get()->WritePlc(QString("<set><var>.%1</var><val>%2</val></set>").arg(name).arg(i));
}

//PLCGet 接口
void DB_Hmi_Gui_Auto_Manual::PLCGet(QString name,int)
{
//    RunTcp::Get()->WritePlc(QString("<get><var>.%1</var><val>0</val></get>").arg(name));
}

QPushButton* DB_Hmi_Gui_Auto_Manual::Get_Button(QString name,QString Icon,int Width,int Height,QString PlcName,QString Style)
{
    const QIcon icon = QIcon(Icon);
    const QString btnStyle = Style;
    QPushButton* btn = new QPushButton();
    btn->setIcon(icon);
    btn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
//    if(Width != 0)
//        btn->setFixedWidth(Width);
//    if(Height != 0)
//        btn->setFixedHeight(Height);
    btn->setIconSize(QSize(30,30));
    btn->setText(name);
    btn->setStyleSheet(btnStyle);

    this->connect(btn,&QPushButton::pressed,this,[=](){
        PLCSet(PlcName,1);
    });
    this->connect(btn,&QPushButton::released,this,[=](){
        PLCSet(PlcName,0);
    });

    return btn;

}


