#include "DB_Hmi.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QDateTime>
#include <QProcess>
#include "windows.h"
#include <QDebug>
#include <QSettings>
#include <QTextCodec>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <windows.h>
#include <QMetaProperty>
#include <winuser.h>

#include "Public/Public_Function.h"
#include "Public/Public_Control.h"
#include "Public/Public_Str.h"
#include "DB_Hmi_Gui_Main_Body.h"
#include "DB_Hmi_Gui_NumKeyBoard.h"
#include "Socket/RunTcp.h"
#include "Ini_Dbdata/Setting_Data.h"

//typedef struct tagWNDINFO
//{
//    DWORD dwRuncontrolId;
//    HWND hWnd;
//} WNDINFO, *LPWNDINFO;

DB_Hmi::DB_Hmi(QWidget *parent)
    : QWidget(parent)
{
    RunTcp::Get()->NetWorkInit();
    RunTcp::Get()->CncOpen("127.0.0.1",62937);
    RunTcp::Get()->PlcOpen("127.0.0.1",62944);
    Key = new DB_Hmi_Gui_Numkeyboard();
    this->installEventFilter(this);
    this->setFixedSize(Public_Function::deskWidth(),Public_Function::deskHeight());
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->Init();
    startTimer(1000);

//    Resize(this);

    qApp->installEventFilter(this);
    RunTcp::Get()->Socket_Write_Init();
}

DB_Hmi::~DB_Hmi()
{

}

bool DB_Hmi::eventFilter(QObject *obj, QEvent *event)
{
    if(obj->inherits("QDoubleSpinBox"))
    {
        if(event->type()==QEvent::FocusIn)
        {
            Key->ShowAndUpdatePos();
        }
        else if(event->type()==QEvent::FocusOut)
        {
            Key->close();
        }
    }
    else if(obj->inherits("QSpinBox"))
    {
        if(event->type()==QEvent::FocusIn)
        {
            Key->ShowAndUpdatePos();
        }
        else if(event->type()==QEvent::FocusOut)
        {
            Key->close();
        }
    }
//    else if(obj->inherits("QTableView"))
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
    return QWidget::eventFilter(obj, event);
#if 0
    QList<QDoubleSpinBox*> boxList = this->findChildren<QDoubleSpinBox*>();
    for(int i = 0; i < boxList.size(); i++)
    {
        if(obj == boxList.at(i))
        {
            if(event->type()==QEvent::FocusIn)
            {
                Key->ShowAndUpdatePos();
            }
            else if(event->type()==QEvent::FocusOut)
            {
                Key->close();
            }
        }
    }
    QList<QSpinBox*> IBoxList = this->findChildren<QSpinBox*>();
    for(int i = 0; i < IBoxList.size(); i++)
    {
        if(obj == IBoxList.at(i))
        {
            if(event->type()==QEvent::FocusIn)
            {
                Key->ShowAndUpdatePos();
            }
            else if(event->type()==QEvent::FocusOut)
            {
                Key->close();
            }
        }
    }
    return QWidget::eventFilter(obj, event);
#endif
}

//BOOL CALLBACK EnumWindowsProc_1(HWND hwnd,LPARAM lparam) ;

////退出
//BOOL CALLBACK EnumWindowsProc_1(HWND hWnd,LPARAM lParam)
//{
//    DWORD dwProcessId;
//    GetWindowThreadProcessId(hWnd, &dwProcessId);
//    LPWNDINFO pInfo = (LPWNDINFO)lParam;
//    if(dwProcessId == pInfo->dwRuncontrolId)
//    {
//        ::SendMessage(hWnd, WM_APP + 99, NULL, (LPARAM)lParam);
//    }
//    return TRUE;
//}

void DB_Hmi::closeEvent(QCloseEvent *event)
{
//    if(m_ResetHMI == true)
//    {
//        event->accept();
//    }
//    else if (!(QMessageBox::information(this,tr("关闭提示"),tr("是否要退出程序?"),tr("是"),tr("否"))))
//    {
//        DWORD pRuncontrolID = -1;
//        WNDINFO bc;

////        ProcessControl pED;

//        event->accept();

////        pED.FindProcessIDFromName("runcontrol.exe",pRuncontrolID);

//        bc.dwRuncontrolId = pRuncontrolID;
//        bc.hWnd = NULL;
//        EnumWindows(EnumWindowsProc_1,(LPARAM)&bc);
//    }
//    else
//    {
//        event->ignore();
//    }
}

//void DB_Hmi::Init_Conf()
//{
//    QList<bool> DataList = Setting_Data::Get()->Get_Data_Bool();
//    bool ret = DataList.at(DataList.size() - 2);
////    ui->Rate_Frame->setVisible(ret);

//    ret= DataList.at(DataList.size() - 1);
////    ui->frame_7->setVisible(ret);
////    ui->line_5->setVisible(ret);

////    VISI_Rate
////            <<m_getdata.value("/Main/VISI_BTN1_1b/").toString()
////            <<m_getdata.value("/Main/VISI_BTN1_2b/").toString()
////            <<m_getdata.value("/Main/VISI_BTN1_3b/").toString()
////            <<m_getdata.value("/Main/VISI_BTN1_4b/").toString();


////    QLabelUI_Txt
////            <<ui->data_1
////            <<ui->data_2
////            <<ui->data_3
////            <<ui->data_4
////            <<ui->data_5
////            <<ui->data_6;

////    CountUI_Label
////            <<ui->Count_LabValue1
////            <<ui->Count_LabValue2;

//    QStringList indicMainName = Setting_Data::Get()->GET_ThreeData(MainViewType,MainView1).at(1);
//    QStringList inforMainName = Setting_Data::Get()->GET_ThreeData(MainViewType,MainView2).at(1);
//    QStringList RunMainName = Setting_Data::Get()->GET_ThreeData(MainViewType,MainView3).at(1);
//    QStringList MainMainName = Setting_Data::Get()->GET_FourData(MainViewType,MainView4).at(1);

////    for(int i = )

//    QStringList msg;
//    QStringList IndicMain = Setting_Data::Get()->GET_ThreeData(MainViewType,MainView1).at(3);
//    QStringList InforMain = Setting_Data::Get()->GET_ThreeData(MainViewType,MainView2).at(3);
//    QStringList RunMain = Setting_Data::Get()->GET_ThreeData(MainViewType,MainView3).at(3);
//    QStringList MainMain = Setting_Data::Get()->GET_FourData(MainViewType,MainView4).at(3);
//    VISI_Rate = MainMain;
//    for(int i = 0; i < IndicMain.size(); i++)
//    {
//        msg << IndicMain.at(i);
//    }
//    for(int i = 0; i < InforMain.size(); i++)
//    {
//        msg << InforMain.at(i);
//    }
//    for(int i = 0; i < RunMain.size(); i++)
//    {
//        msg << RunMain.at(i);
//    }
//    for(int i = 0; i < MainMain.size(); i++)
//    {
//        msg << MainMain.at(i);
//    }
//    QString str="";
//    for(int i=0;i<msg.size();i++)
//    {
//        if(msg[i]!="")
//        {
//            str.append("."+msg[i]+",");
//        }
//    }
//    m_PLCStatus.append(str);
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_1b").toString()
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_2b").toString()
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_3b").toString()
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_4b").toString()
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_5b").toString()
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_6b").toString()
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_7b").toString()
////        <<m_getdata.value("/IndicatorLight/VISO_Lamp_8b").toString()

////        <<m_getdata.value("/InformationDisplay/VISO_Lamp_2").toString()
////        <<m_getdata.value("/InformationDisplay/VISO_Lamp_4").toString()
////        <<m_getdata.value("/InformationDisplay/VISO_Lamp_6").toString()
////        <<m_getdata.value("/InformationDisplay/VISO_Lamp_8").toString()
////        <<m_getdata.value("/InformationDisplay/VISO_Lamp_10").toString()
////        <<m_getdata.value("/InformationDisplay/VISO_Lamp_12").toString()

////        <<m_getdata.value("/RunCount/VISO_Lamp_2/").toString()
////        <<m_getdata.value("/RunCount/VISO_Lamp_3/").toString()

////        <<m_getdata.value("/Main/VISO_BTN1_1b/").toString()
////        <<m_getdata.value("/Main/VISO_BTN1_2b/").toString()
////        <<m_getdata.value("/Main/VISO_BTN1_3b/").toString()
////        <<m_getdata.value("/Main/VISO_BTN1_4b/").toString();

////    QString str="";
////    for(int i=0;i<plc_val.size();i++)
////    {
////        if(plc_val[i]!="")
////        {
////            str.append("."+plc_val[i]+",");
////        }
////    }
////    m_PLCStatus.append(str);
//}

//初始化
void DB_Hmi::Init()
{
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(5);
    mLayout->setContentsMargins(0,0,0,0);

    //Top
    QWidget* Top = InitTopWidget();
    Top->setFixedHeight(150);
    //Main
    Db_Hmi_Gui_Main_Body* Main = new Db_Hmi_Gui_Main_Body(this);
    Main->setObjectName("Main");
    //Bottom
    QWidget* Bottom = InitBottomWidget();
    Bottom->setFixedHeight(50);

    mLayout->addWidget(Top);
    mLayout->addWidget(Main);
    mLayout->addWidget(Bottom);
    this->setLayout(mLayout);

    this->connect(this,&DB_Hmi::Signal_Switch_Page,Main,&Db_Hmi_Gui_Main_Body::Slot_Switch_Page);
}

//初始化头部
QWidget* DB_Hmi::InitTopWidget()
{
    const QString TopStyle = Public_Str::Get_Sty(Style_Css{TopWidgetStyle,{}});
    QWidget* mWidget = new QWidget();
    mWidget->setObjectName("TopWidget");
    mWidget->setStyleSheet(QString("#TopWidget{%1}").arg(TopStyle));

    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(5);
    mLayout->setContentsMargins(0,0,0,0);

    QStringList Str;
    Str << "机床就位" << "自动连续" << "轴静止" << "未回零" << "门脉冲" << "强脉冲"
        << "定高切割" << "激光发射" << "焦点4" << "焦点1" << "焦点2" << "焦点3";
    QWidget* TableWidget = Create_Label_Table(Str);

    QWidget* CoordWidget = Create_Coord_Group();

    QWidget* informationWidget = Create_information_Group();

    QWidget* Close_Logo_Widget = Create_logo_Close_Widget();
    mLayout->addWidget(TableWidget);
    mLayout->addWidget(CoordWidget);
    mLayout->addWidget(informationWidget);
    mLayout->addStretch(8);
    mLayout->addWidget(Close_Logo_Widget);
    mLayout->setStretchFactor(TableWidget,2);
    mLayout->setStretchFactor(CoordWidget,1);
    mLayout->setStretchFactor(informationWidget,1);
    mLayout->setStretchFactor(Close_Logo_Widget,2);

    mWidget->setLayout(mLayout);

    return mWidget;
}

//初始化底部
QWidget* DB_Hmi::InitBottomWidget()
{
    QWidget* mWidget = new QWidget();
    mWidget->setObjectName("mWidget");
    mWidget->setStyleSheet("QWidget#mWidget{background-color:#666666};");

    QHBoxLayout* mHLayout = new QHBoxLayout();
    mHLayout->setSpacing(0);
    mHLayout->setContentsMargins(0,0,0,0);

    QWidget* Label_Widget = new QWidget();
    Label_Widget->setFixedSize(200,50);
    QVBoxLayout* Label_Layout = new QVBoxLayout();
    Label_Layout->setSpacing(0);
    Label_Layout->setContentsMargins(0,0,0,0);

    const QString lbl_Now_Time_Style = "font: 11pt ""黑体"";color:rgb(255,255,255);";
    QWidget* AddWork_Time_Widget = Public_Control::Create_Labal_Value("加工时间 :","00:00:00:00","AddWorkTimeText","AddWorkTimeValue");
    AddWork_Time_Widget->setStyleSheet(lbl_Now_Time_Style);
    QLabel* lbl_Now_Time = new QLabel();
    lbl_Now_Time->setStyleSheet(lbl_Now_Time_Style);
    lbl_Now_Time->setText(QDateTime::currentDateTime().toString());

    Label_Layout->addWidget(AddWork_Time_Widget,Qt::AlignCenter);
    Label_Layout->addWidget(lbl_Now_Time,0,Qt::AlignCenter);

    Label_Widget->setLayout(Label_Layout);

    QHBoxLayout* btn_Layout = new QHBoxLayout();
    btn_Layout->setSpacing(10);
    btn_Layout->setContentsMargins(0,0,0,0);

    QPushButton* btn_Manual = Public_Control::Get_Button("手动自动",":/Icon/Img/Icon/manual2.png");
    QPushButton* btn_Data = Public_Control::Get_Button("数据",":/Icon/Img/Icon/data1.png");
    QPushButton* btn_System = Public_Control::Get_Button("系统",":/Icon/Img/Icon/system1.png");
    QPushButton* btn_Set_up = Public_Control::Get_Button("设置",":/Icon/Img/Icon/setting1.png");

    btn_Manual->setFixedSize(100,45);
    btn_Data->setFixedSize(100,45);
    btn_System->setFixedSize(100,45);
    btn_Set_up->setFixedSize(100,45);

    this->connect(btn_Manual,&QPushButton::clicked,this,[=](){
        emit Signal_Switch_Page(0);
        btn_Manual->setIcon(QIcon(":/Icon/Img/Icon/manual2.png"));
        btn_Data->setIcon(QIcon(":/Icon/Img/Icon/data1.png"));
        btn_System->setIcon(QIcon(":/Icon/Img/Icon/system1.png"));
        btn_Set_up->setIcon(QIcon(":/Icon/Img/Icon/setting1.png"));
    });
    this->connect(btn_Data,&QPushButton::clicked,this,[=](){
        emit Signal_Switch_Page(1);
        btn_Manual->setIcon(QIcon(":/Icon/Img/Icon/manual1.png"));
        btn_Data->setIcon(QIcon(":/Icon/Img/Icon/data2.png"));
        btn_System->setIcon(QIcon(":/Icon/Img/Icon/system1.png"));
        btn_Set_up->setIcon(QIcon(":/Icon/Img/Icon/setting1.png"));
    });
    this->connect(btn_System,&QPushButton::clicked,this,[=](){
        emit Signal_Switch_Page(2);
        btn_Manual->setIcon(QIcon(":/Icon/Img/Icon/manual1.png"));
        btn_Data->setIcon(QIcon(":/Icon/Img/Icon/data1.png"));
        btn_System->setIcon(QIcon(":/Icon/Img/Icon/system2.png"));
        btn_Set_up->setIcon(QIcon(":/Icon/Img/Icon/setting1.png"));
    });
    this->connect(btn_Set_up,&QPushButton::clicked,this,[=](){
        emit Signal_Switch_Page(3);
        btn_Manual->setIcon(QIcon(":/Icon/Img/Icon/manual1.png"));
        btn_Data->setIcon(QIcon(":/Icon/Img/Icon/data1.png"));
        btn_System->setIcon(QIcon(":/Icon/Img/Icon/system1.png"));
        btn_Set_up->setIcon(QIcon(":/Icon/Img/Icon/setting2.png"));
    });

    btn_Layout->addWidget(btn_Manual);
    btn_Layout->addWidget(btn_Data);
    btn_Layout->addWidget(btn_System);
    btn_Layout->addWidget(btn_Set_up);


    QHBoxLayout* Right_Layout = new QHBoxLayout();
    Right_Layout->setSpacing(10);
    Right_Layout->setContentsMargins(0,0,0,0);

    QPushButton* btn_exe = Public_Control::Get_Button("",":/Icon/Img/Icon/exe_1.png");
    QPushButton* btn_Reset = Public_Control::Get_Button("复位",":/Img/reset1.png");

    btn_exe->setFixedSize(80,45);
    btn_Reset->setFixedSize(150,45);

    Right_Layout->addWidget(btn_exe);
    Right_Layout->addWidget(btn_Reset);

    mHLayout->addWidget(Label_Widget,0,Qt::AlignLeft);
    mHLayout->addStretch();
    mHLayout->addLayout(btn_Layout,Qt::AlignCenter);
    mHLayout->addStretch();
    mHLayout->addLayout(Right_Layout,Qt::AlignRight);

    mWidget->setLayout(mHLayout);

    this->connect(btn_exe,&QPushButton::clicked,this,[=](){
        QSettings m_getdata(mIniDBHmi, QSettings::IniFormat);
        m_getdata.setIniCodec(QTextCodec::codecForName("GB2312"));
        QString exe_filepath=m_getdata.value("/filepath/exe1/").toString();

        QProcess *Process=new QProcess;
        Process->start(exe_filepath,QStringList(exe_filepath));//带空格。能够启动
    });

    this->connect(this,&DB_Hmi::Refresh_Time,this,[=](){
        lbl_Now_Time->setText(QDateTime::currentDateTime().toString());
    });

    this->connect(btn_Reset,&QPushButton::pressed,this,[=](){
        const QString image1="background-color: rgb(201, 201, 201);border:none;color:rgb(0,0,0)";
        RunTcp::Get()->WritePlc("<set><var>.VISI_RESET</var><val>1</val></set>");
//        btn_Reset->setStyleSheet(image1);
//        btn_Reset->setIcon(QIcon(":/Img/reset1.png"));
//        btn_Reset->setIconSize(QSize(32,32));
    });

    this->connect(btn_Reset,&QPushButton::released,this,[=](){
        const QString image2="background-color: rgb(240, 240, 240);border:none;color:rgb(10,10,10)";
        RunTcp::Get()->WritePlc("<set><var>.VISI_RESET</var><val>0</val></set>");
//        btn_Reset->setStyleSheet(image2);
//        btn_Reset->setIcon(QIcon(":/Img/reset2.png"));
//        btn_Reset->setIconSize(QSize(32,32));
    });
    return mWidget;
}

//初始化中间部分
QWidget* DB_Hmi::InitMainWidget()
{
    QWidget* mWidget = new QWidget();

    return mWidget;
}

//创建Label排序的列表
QWidget* DB_Hmi::Create_Label_Table(QStringList StrList)
{
    const QString TableLabelWidget = Public_Str::Get_Sty(Style_Css{TableLabelWidgetStyle,{}});
    QWidget* mWidget = new QWidget();
//    mWidget->setFixedWidth(250);
    mWidget->setObjectName("TableLabelWidget");
    mWidget->setStyleSheet(QString("#TableLabelWidget{%1}").arg(TableLabelWidget));

    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(5,5,5,5);

    //因为Table只创建一次就不封装了
    //第一层
    QHBoxLayout* mFirstLayout = new QHBoxLayout();
    mFirstLayout->setSpacing(0);
    mFirstLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl1 = Get_Label(StrList.at(0),NO1);
    QLabel* lbl2 = Get_Label(StrList.at(1),NO2);
    QLabel* lbl3 = Get_Label(StrList.at(2),NO3);
    mFirstLayout->addWidget(lbl1);
    mFirstLayout->addWidget(lbl2);
    mFirstLayout->addWidget(lbl3);

    //第二层
    QHBoxLayout* mSecondLayout = new QHBoxLayout();
    mFirstLayout->setSpacing(0);
    mFirstLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl4 = Get_Label(StrList.at(3),NO1);
    QLabel* lbl5 = Get_Label(StrList.at(4),NO2);
    QLabel* lbl6 = Get_Label(StrList.at(5),NO3);
    mSecondLayout->addWidget(lbl4);
    mSecondLayout->addWidget(lbl5);
    mSecondLayout->addWidget(lbl6);

    //第三层
    QHBoxLayout* mThirdLayout = new QHBoxLayout();
    mFirstLayout->setSpacing(0);
    mFirstLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl7 = Get_Label(StrList.at(6),NO1);
    QLabel* lbl8 = Get_Label(StrList.at(7),NO2);
    QLabel* lbl9 = Get_Label(StrList.at(8),NO3);
    mThirdLayout->addWidget(lbl7);
    mThirdLayout->addWidget(lbl8);
    mThirdLayout->addWidget(lbl9);

    //第四层
    QHBoxLayout* mFourLayout = new QHBoxLayout();
    mFirstLayout->setSpacing(0);
    mFirstLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl10 = Get_Label(StrList.at(9),NO1);
    QLabel* lbl11 = Get_Label(StrList.at(10),NO2);
    QLabel* lbl12 = Get_Label(StrList.at(11),NO3);
    mFourLayout->addWidget(lbl10);
    mFourLayout->addWidget(lbl11);
    mFourLayout->addWidget(lbl12);

    mLayout->addLayout(mFirstLayout);
    mLayout->addLayout(mSecondLayout);
    mLayout->addLayout(mThirdLayout);
    mLayout->addLayout(mFourLayout);
    mWidget->setLayout(mLayout);

    this->connect(RunTcp::Get(),&RunTcp::Set_Main_Ncda_Signal,this,[=](QStringList List)
    {
        QStringList msg;
        msg << "" << "" << "" << "";
        for(int i = 0; i < List.size(); i++)
        {
            if(List.at(i).split("_").first() == "status")
            {
                msg[0] = List.at(i).split("_").last();
            }
            else if(List.at(i).split("_").first() == "mode")
            {
                msg[1] = List.at(i).split("_").last();
            }
            else if(List.at(i).split("_").first() == "mmode")
            {
                msg[2] = List.at(i).split("_").last();
            }
            else if(List.at(i).split("_").first() == "amode")
            {
                msg[3] = List.at(i).split("_").last();
            }
        }
        if(!msg.at(0).isEmpty())
        {
            if(msg.at(0).toInt() == 1)
            {
                lbl1->setText(tr("紧急停止"));
                lbl1->setStyleSheet("background-color: rgb(255, 0, 0);border:none;color:rgb(26,26,26)");
            }
            else if(msg.at(0).toInt() == 2)
            {
                lbl1->setText(tr("无进给"));
                lbl1->setStyleSheet("background-color: rgb(255, 255, 0);border:none;color:rgb(26,26,26)");
            }
            else if(msg.at(0).toInt() == 3)
            {
                lbl1->setText(tr("无驱动"));
                lbl1->setStyleSheet("background-color: rgb(255, 255, 0);border:none;color:rgb(26,26,26)");
            }
            else if(msg.at(0).toInt() == 4)
            {
                lbl1->setText(tr("机床停止"));
                lbl1->setStyleSheet("background-color: rgb(255, 255, 0);border:none;color:rgb(26,26,26)");
            }
            else if(msg.at(0).toInt() == 5)
            {
                lbl1->setText(tr("机床就位"));
                lbl1->setStyleSheet("background-color: rgb(255, 255, 0);border:none;color:rgb(26,26,26)");
            }
            else if(msg.at(0).toInt() == 6)
            {
                lbl1->setText(tr("运行中"));
                lbl1->setStyleSheet("background-color: rgb(0, 255, 0);border:none;color:rgb(26,26,26)");
            }
        }

        if(!msg.at(1).isEmpty())
        {
            //不知道啥玩意
            if(MainStackTabEnable == false)
            {
                MainStackTabEnable = true;
            }
            else
            {
                lbl2->setStyleSheet("background-color: rgb(230, 230, 230);border:none;color:rgb(0,0,0)");
                //自动
                if(msg.at(1).toInt() == 0)
                {
                    lbl2->setText("自动连续");
                    //跳页
                }
                else if(msg.at(1).toInt() == 1)
                {
                    lbl2->setText(tr("自动单段"));
                    //跳页
                }
                else if(msg.at(1).toInt() == 2)
                {
                    lbl2->setText(tr("MDI"));
                    //跳页
                }
                else if(msg.at(1).toInt() == 3)
                {
                    if(!msg.at(2).isEmpty())
                    {
                       if(msg.at(2).toInt() == 0)
                       {
                           lbl2->setText(tr("手动方式"));
                       }
                       else if(msg.at(2).toInt() == 1)
                       {
                           lbl2->setText(tr("连续进给"));
                       }
                       else if(msg.at(2).toInt() == 2)
                       {
                           lbl2->setText(tr("增量进给"));
                       }
                       else if(msg.at(2).toInt() == 3)
                       {
                           lbl2->setText(tr("手轮进给"));
                       }
                       else if(msg.at(2).toInt() == 4)
                       {
                           lbl2->setText(tr("回零模式"));
                       }
                       else if(msg.at(2).toInt() == 5)
                       {
                           lbl2->setText(tr("断点返回"));
                       }
                    }
                    else
                    {
                        lbl2->setText(tr("手动方式"));
                    }
                }
                else if(msg.at(1).toInt() == 5)
                {
                    lbl2->setText(tr("回零中"));
                    lbl2->setStyleSheet("background-color: rgb(0, 255, 0);border:none;color:rgb(0,0,0)");
                }
                //其余的松开
            }
        }
        else
        {
            if(msg.at(2).isEmpty())
            {
                //QString msg=str.mid(str.indexOf("<mmode>")+7,str.indexOf("</mmode>")-str.indexOf("<mmode>")-7);
                if(msg.at(2).toInt() == 1)
                {
                    lbl2->setText(tr("连续进给"));
                }else if(msg.at(2).toInt() == 2)
                {
                    lbl2->setText(tr("增量进给"));
                }else if(msg.at(2).toInt() == 3)
                {
                    lbl2->setText(tr("手轮进给"));
                }else if(msg.at(2).toInt() == 4)
                {
                    lbl2->setText(tr("回零模式"));
                }else if(msg.at(2).toInt() == 5)
                {
                    lbl2->setText(tr("断点返回"));
                }
            }
            if(msg.at(3).isEmpty())
            {
                if(msg.at(3).toInt() == 0)
                {
                    lbl2->setText(tr("自动连续"));
                }else if(msg.at(3).toInt() == 1)
                {
                    lbl2->setText(tr("自动单段"));
                }else if(msg.at(3).toInt() == 2)
                {
                    lbl2->setText("MDI");
                }
            }
        }
    });

    return mWidget;
}

//创建机床坐标的坐标组
QWidget* DB_Hmi::Create_Coord_Group()
{
    const QString Coord_Widget_Style = Public_Str::Get_Sty(Style_Css{CoordGroupStyle,{}});
    QWidget* mWidget = new QWidget();
//    mWidget->setFixedWidth(150);
    mWidget->setObjectName("CoordWidget");
    mWidget->setStyleSheet(QString("#CoordWidget{%1}").arg(Coord_Widget_Style));

    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(8,8,8,8);

    //组控件
    QGroupBox* Coord_Box = new QGroupBox();
    Coord_Box->setAlignment(Qt::AlignCenter);
    Coord_Box->setTitle("机床坐标");

    QVBoxLayout* Coord_Layout = new QVBoxLayout();
    Coord_Layout->setSpacing(5);
    Coord_Layout->setContentsMargins(8,8,8,8);

    QWidget* xWidget = Public_Control::Create_Labal_Value("X:","+00000.000","XText","XValue");
    QWidget* yWidget = Public_Control::Create_Labal_Value("Y:","+00000.000","YText","YValue");
    QWidget* zWidget = Public_Control::Create_Labal_Value("Z:","+00000.000","ZText","ZValue");
    QWidget* aWidget = Public_Control::Create_Labal_Value("A:","+00000.000","AText","AValue");
    QWidget* cWidget = Public_Control::Create_Labal_Value("?:","+00000.000","CText","CValue");
    QWidget* lWidget = Public_Control::Create_Labal_Value("?:","+00000.000","LText","LValue");
    xWidget->setVisible(false);
    yWidget->setVisible(false);
    zWidget->setVisible(false);
    aWidget->setVisible(false);
    cWidget->setVisible(false);
    lWidget->setVisible(false);

    Coord_Layout->addWidget(xWidget);
    Coord_Layout->addWidget(yWidget);
    Coord_Layout->addWidget(zWidget);
    Coord_Layout->addWidget(aWidget);
    Coord_Layout->addWidget(cWidget);
    Coord_Layout->addWidget(lWidget);
    Coord_Layout->addStretch();
    Coord_Box->setLayout(Coord_Layout);

    mLayout->addWidget(Coord_Box);
    mWidget->setLayout(mLayout);

    this->connect(RunTcp::Get(),&RunTcp::Set_Name_Signal,this,[=](QStringList msg){
        QLabel* lblXValue = xWidget->findChild<QLabel*>("XText");
        QLabel* lblYValue = yWidget->findChild<QLabel*>("YText");
        QLabel* lblzWidget = zWidget->findChild<QLabel*>("ZText");
        QLabel* lblaWidget = aWidget->findChild<QLabel*>("AText");
        QLabel* lblcWidget = cWidget->findChild<QLabel*>("CText");
        QLabel* lbllWidget = lWidget->findChild<QLabel*>("LText");
        if(!msg.at(0).isEmpty())
        {
            xWidget->setVisible(true);
            lblXValue->setText(msg.at(0));
        }
        if(!msg.at(1).isEmpty())
        {
            yWidget->setVisible(true);
            lblYValue->setText(msg.at(1));
        }
        if(!msg.at(2).isEmpty())
        {
            zWidget->setVisible(true);
            lblzWidget->setText(msg.at(2));
        }
        if(!msg.at(3).isEmpty())
        {
            aWidget->setVisible(true);
            lblaWidget->setText(msg.at(3));
        }
        if(!msg.at(4).isEmpty())
        {
            cWidget->setVisible(true);
            lblcWidget->setText(msg.at(4));
        }
        if(!msg.at(5).isEmpty())
        {
            lWidget->setVisible(true);
            lbllWidget->setText(msg.at(5));
        }
    });

    this->connect(RunTcp::Get(),&RunTcp::Set_AxesPosSignal,this,[=](QList<QVariant> List){
        QLabel* lblXValue = xWidget->findChild<QLabel*>("XValue");
        QLabel* lblYValue = yWidget->findChild<QLabel*>("YValue");
        QLabel* lblzWidget = zWidget->findChild<QLabel*>("ZValue");
        QLabel* lblaWidget = aWidget->findChild<QLabel*>("AValue");
        QLabel* lblcWidget = cWidget->findChild<QLabel*>("CValue");
        QLabel* lbllWidget = lWidget->findChild<QLabel*>("LValue");

        if(!List.at(0).toString().isEmpty())
            lblXValue->setText(List.at(0).toString());
        if(!List.at(1).toString().isEmpty())
            lblYValue->setText(List.at(1).toString());
        if(!List.at(2).toString().isEmpty())
            lblzWidget->setText(List.at(2).toString());
        if(!List.at(3).toString().isEmpty())
            lblaWidget->setText(List.at(3).toString());
        if(!List.at(4).toString().isEmpty())
            lblcWidget->setText(List.at(4).toString());
        if(!List.at(5).toString().isEmpty())
            lbllWidget->setText(List.at(5).toString());
    });

    return mWidget;
}

//创建信息的坐标组
QWidget* DB_Hmi::Create_information_Group()
{
    const QString Coord_Widget_Style = Public_Str::Get_Sty(Style_Css{InformationGroupStyle,{}});
    QWidget* mWidget = new QWidget();
//    mWidget->setFixedWidth(150);
    mWidget->setObjectName("CoordWidget");
    mWidget->setStyleSheet(QString("#CoordWidget{%1}").arg(Coord_Widget_Style));

    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(5,5,5,5);

    //组控件
    QGroupBox* Coord_Box = new QGroupBox();
    Coord_Box->setAlignment(Qt::AlignCenter);
    Coord_Box->setTitle("信息");

    QVBoxLayout* Coord_Layout = new QVBoxLayout();
    Coord_Layout->setSpacing(0);
    Coord_Layout->setContentsMargins(8,8,8,8);

    //感应电压
    QWidget* VoltageWidget = Public_Control::Create_Labal_Value("感应电压:","+00000.000","VoltageText","VoltageValue");
    //焦点偏移
    QWidget* FocesShiftWidget = Public_Control::Create_Labal_Value("焦点偏移:","+00000.000","FocesShiftText","FocesShiftValue");
    //Z轴高度
    QWidget* zHeightWidget = Public_Control::Create_Labal_Value("Z轴高度:","+00000.000","zHeightText","zHeightValue");
    //切割速度
    QWidget* CutSpeedWidget = Public_Control::Create_Labal_Value("切割速度:","+00000.000","CutSpeedText","CutSpeedValue");
    //预设速度A
    QWidget* PresetSpeedWidget = Public_Control::Create_Labal_Value("预设速度:","+00000.000","PresetSpeedText","PresetSpeedValue");
    //当前图层
    QWidget* CurrentLayerWidget = Public_Control::Create_Labal_Value("当前图层:","+00000.000","CurrentLayerText","CurrentLayerValue");

    Coord_Layout->addWidget(VoltageWidget);
    Coord_Layout->addWidget(FocesShiftWidget);
    Coord_Layout->addWidget(zHeightWidget);
    Coord_Layout->addWidget(CutSpeedWidget);
    Coord_Layout->addWidget(PresetSpeedWidget);
    Coord_Layout->addWidget(CurrentLayerWidget);
    Coord_Box->setLayout(Coord_Layout);

    mLayout->addWidget(Coord_Box);
    mWidget->setLayout(mLayout);

    return mWidget;
}

//创建logo以及退出等信息界面
QWidget* DB_Hmi::Create_logo_Close_Widget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QStackedWidget* mSWidget = new QStackedWidget();
    mSWidget->setFixedWidth(340);
//    QWidget* First = Create_SWidget(FirstWidget);
    QWidget* First = new QWidget();
    QWidget* Second = Create_SWidget(SecondWidget);
    mSWidget->addWidget(First);
    mSWidget->addWidget(Second);
    mSWidget->setCurrentIndex(0);


    QPushButton* btn_Logo = Public_Control::Get_Button("");
    btn_Logo->setFixedWidth(150);
    btn_Logo->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    this->connect(btn_Logo,&QPushButton::clicked,this,[=](){
       if(isOpen)
       {
           mSWidget->setCurrentIndex(0);
       }
       else
       {
           mSWidget->setCurrentIndex(1);
       }
       isOpen = !isOpen;
    });

    mLayout->addStretch();
    mLayout->addWidget(mSWidget);
    mLayout->addWidget(btn_Logo);
    mLayout->setStretchFactor(mSWidget,2);
    mLayout->setStretchFactor(btn_Logo,1);;
    mWidget->setLayout(mLayout);

    return mWidget;

}

QWidget* DB_Hmi::Create_SWidget(StackedSwitch sw)
{
    QWidget* mWidget = nullptr;
    switch(sw)
    {
    case FirstWidget:
    {
        QWidget* Widget = new QWidget();
        QHBoxLayout* Layout = new QHBoxLayout();
        Layout->setSpacing(5);
        Layout->setContentsMargins(5,5,5,5);

        QGroupBox* Coord_Box = new QGroupBox();
        Coord_Box->setObjectName("Coord_Box");
        Coord_Box->setFixedWidth(150);
        Coord_Box->setAlignment(Qt::AlignCenter);
        Coord_Box->setTitle("加工计数");

        QVBoxLayout* Coord_Layout = new QVBoxLayout();
        Coord_Layout->setSpacing(0);
        Coord_Layout->setContentsMargins(0,0,0,0);

        //预计个数
        QWidget* NumberExpectedWidget = Public_Control::Create_Labal_Value("感应电压:","+00000.000","NumberExpectedText","NumberExpectedValue");
        //焦点偏移
        QWidget* HasProcessedWidget = Public_Control::Create_Labal_Value("焦点偏移:","+00000.000","HasProcessedText","HasProcessedValue");
        //清空计数
        QPushButton* btn_Clear = Public_Control::Get_Button("清空计数");

        Coord_Layout->addWidget(NumberExpectedWidget);
        Coord_Layout->addWidget(HasProcessedWidget);
        Coord_Layout->addWidget(btn_Clear);
        Coord_Box->setLayout(Coord_Layout);

        QWidget* mRightWidget = new QWidget();
        mRightWidget->setFixedWidth(180);
        QHBoxLayout* mRightLayout = new QHBoxLayout();
        mRightLayout->setSpacing(0);
        mRightLayout->setContentsMargins(0,0,0,0);

        QGroupBox* mBox = new QGroupBox();
        mBox->setFixedWidth(150);

        QVBoxLayout* ButtonLayout = new QVBoxLayout();
        ButtonLayout->setSpacing(0);
        ButtonLayout->setContentsMargins(0,0,0,0);
        QPushButton* btn_120 = Public_Control::Get_Button("120%");
        btn_120->setFixedWidth(30);
        QPushButton* btn_Add = Public_Control::Get_Button("+");
        btn_Add->setFixedWidth(30);
        QPushButton* btn_Sub = Public_Control::Get_Button("-");
        btn_Sub->setFixedWidth(30);
        QPushButton* btn_Zore = Public_Control::Get_Button("0%");
        btn_Zore->setFixedWidth(30);
        ButtonLayout->addWidget(btn_120);
        ButtonLayout->addWidget(btn_Add);
        ButtonLayout->addWidget(btn_Sub);
        ButtonLayout->addWidget(btn_Zore);

        mRightLayout->addWidget(mBox);
        mRightLayout->addLayout(ButtonLayout);
        mRightWidget->setLayout(mRightLayout);

        Layout->addWidget(Coord_Box);
        Layout->addWidget(mRightWidget);
        Widget->setLayout(Layout);

        mWidget = Widget;
        break;
    }
    case SecondWidget:
    {
        QWidget* Widget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(0,0,0,0);

        QWidget* mBottomWidget = new QWidget();
        QVBoxLayout* mButtonLayout = new QVBoxLayout();
        mButtonLayout->setSpacing(0);
        mButtonLayout->setContentsMargins(0,0,0,0);

        QHBoxLayout* TopButtom = new QHBoxLayout();
        TopButtom->setSpacing(0);
        TopButtom->setContentsMargins(0,0,0,0);
        QPushButton* btn_OpenPA = Public_Control::Get_Button("打开PA","",0,75);
        QPushButton* btn_ReStart = Public_Control::Get_Button("重启Hmi","",0,75);
        QPushButton* btn_LanguageSwitch = Public_Control::Get_Button("语言切换","",0,75);
        TopButtom->addWidget(btn_OpenPA);
        TopButtom->addWidget(btn_ReStart);
        TopButtom->addWidget(btn_LanguageSwitch);

        QHBoxLayout* BottomButtom = new QHBoxLayout();
        BottomButtom->setSpacing(0);
        BottomButtom->setContentsMargins(0,0,0,0);
        QPushButton* btn_Min = Public_Control::Get_Button("最小化","",0,75);
        QPushButton* btn_Close = Public_Control::Get_Button("退出","",0,75);
        QPushButton* btn_ShutDown = Public_Control::Get_Button("关机","",0,75);
        BottomButtom->addWidget(btn_Min);
        BottomButtom->addWidget(btn_Close);
        BottomButtom->addWidget(btn_ShutDown);

        mButtonLayout->addLayout(TopButtom);
        mButtonLayout->addLayout(BottomButtom);
        mBottomWidget->setLayout(mButtonLayout);

        mLayout->addStretch();
        mLayout->addWidget(mBottomWidget);
        Widget->setLayout(mLayout);

        this->connect(btn_OpenPA,&QPushButton::clicked,this,[=](){
            QProcess Process(this);
            Process.startDetached("hmiframe -p:hmi");
        });
        this->connect(btn_ReStart,&QPushButton::clicked,this,[=](){
            this->close();
            QTime n=QTime::currentTime();
            QTime now;
            do{
                now=QTime::currentTime();
            }while(n.msecsTo(now) <= 1000);
            QProcess::startDetached(qApp->applicationFilePath(),QStringList("-qws"));
        });
        this->connect(btn_Close,&QPushButton::clicked,this,[=](){this->close();});
        this->connect(btn_Min,&QPushButton::clicked,this,[=](){this->showMinimized();});
        this->connect(btn_ShutDown,&QPushButton::clicked,this,[=](){

            HANDLE hToken;
            TOKEN_PRIVILEGES tkp;

            //获取进程标志
            if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
                return false;

            //获取关机特权的LUID
            LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
            tkp.PrivilegeCount = 1;
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            //获取这个进程的关机特权
            AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
            if (GetLastError() != ERROR_SUCCESS) return false;

            // 强制关闭计算机
            if ( !ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))
                return false;
            return true;
        });

        mWidget = Widget;
        break;
    }
    }

    return mWidget;
}

//创建Label
//为了切换模式可以变颜色所以添加了这个枚举这个索引值
QLabel* DB_Hmi::Get_Label(QString text,Light_Model str)
{
    const QString label_Style = Public_Str::Get_Sty(Style_Css{GetLabelStyle,{}});
    QLabel* label = new QLabel();
    label->setStyleSheet(label_Style);
    label->setAlignment(Qt::AlignCenter);
    label->setText(text);

    return label;
}

void DB_Hmi::timerEvent(QTimerEvent *e)
{
    emit Refresh_Time();
}

void DB_Hmi::Resize(QWidget* pWidget)
{
    if(!pWidget){
            return;
        }
        QDesktopWidget* desktopWidget = QApplication::desktop();
        //获取可用桌面大小
        QRect deskRect = desktopWidget->availableGeometry();
        // 如果分辨率已经在1920及以上，则不需要进行处理
        if(deskRect.width() >= 1920){
            return;
        }
        //仅使用x比例，否则窗口会变形
        float scale = deskRect.width() / 1920.0;
        QObjectList lst = pWidget->children();
        QPoint pt(0,0);
        for(auto l : lst)
        {
            auto widget = qobject_cast<QWidget*>(l);
            if(widget)
            {
                pt = widget->pos();

                widget->move(QPoint(pt.x() * scale, pt.y() * scale));
                widget->resize(widget->width() * scale, widget->height() * scale);

                QFont font;
                int nIndex = widget->metaObject()->indexOfProperty("font");
                auto propertyFont = widget->metaObject()->property(nIndex);

                QVariant var =  propertyFont.read(widget);
                if(var.canConvert(QMetaType::QFont))
                {
                    font = var.value<QFont>();

                    font.setPointSizeF(font.pointSizeF() * scale);
                    propertyFont.write(widget,QVariant::fromValue(font));
                }

                QPixmap pixmap;
                nIndex = widget->metaObject()->indexOfProperty("pixmap");
                auto pixmapProp = widget->metaObject()->property(nIndex);

                var = pixmapProp.read(widget);
                if(var.canConvert(QMetaType::QPixmap))
                {
                    pixmap = var.value<QPixmap>();
                    if(!pixmap.isNull())
                    {
                        QSize sizePixmap(pixmap.size().width() * scale, pixmap.size().height() * scale);

                        pixmap =  pixmap.scaled(sizePixmap);
                        pixmapProp.write(widget,QVariant::fromValue(pixmap));
                    }
                }
            }
        }

        pWidget->resize(pWidget->width() * scale, pWidget->height() * scale);
//    int currentScreenWid = QApplication::desktop()->width();
//    int currentScreenHei = QApplication::desktop()->height();
//    qDebug() << currentScreenHei << currentScreenWid;
//    double factorx = currentScreenWid / 1920;
//    double factory = currentScreenHei / 1080;
//    if(currentScreenWid >= 1920 && currentScreenHei >= 1080)
//        return;
//    int widgetX = this->x();
//    int widgetY = this->y();
//    int widgetWid = this->width();
//    int widgetHei = this->height();
//    int nWidgetX = (int)(widgetX*factorx);
//    int nWidgetY = (int)(widgetY*factory);
//    int nWidgetWid = (int)(widgetWid*factorx);
//    int nWidgetHei = (int)(widgetHei*factory);
//    this->setGeometry(nWidgetX,nWidgetY,nWidgetWid,nWidgetHei);
}
