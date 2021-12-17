#include "DB_Hmi_Gui_System.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QStackedWidget>
#include <QDebug>
#include <QtConcurrent>
#include <QFile>

#include "DB_Hmi_Gui_System_Io.h"
#include "Public/Public_Str.h"
#include "Public/Public_Control.h"
#include "Public/Public_Function.h"
#include "../Model/CyclePLastTableView.h"
#include "../Model/CyclePLessTableView.h"
#include "../Model/CyclePMoreTableView.h"
#include "../Model/DTableView.h"
#include "../Model/GTableView.h"
#include "../Model/HTableView.h"
#include "../Socket/RunTcp.h"

#include "../Ini_Dbdata/Setting_Data.h"


DB_Hmi_Body_System::DB_Hmi_Body_System(QWidget* parent)
    :QWidget(parent)
{
    this->init();
}

DB_Hmi_Body_System::~DB_Hmi_Body_System()
{

}

void DB_Hmi_Body_System::init()
{
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    QWidget* InitWidget = InitLayout();

    layout->addWidget(InitWidget);

    this->setLayout(layout);
}

QWidget* DB_Hmi_Body_System::InitLayout()
{
    QWidget* m_Widget = new QWidget();
    QHBoxLayout* mHLayout = new QHBoxLayout();

    QStackedWidget* mSWidget = new QStackedWidget();
    QWidget* InformationWidget = Create_System_Switch_Page(InformationPage);
    QWidget* PLCMonitoringWidget = Create_System_Switch_Page(PLCMonitoringPage);
    DB_Hmi_Gui_System_Io* CNCInputWidget = new DB_Hmi_Gui_System_Io();
    DB_Hmi_Gui_System_Io* CNCOutputWidget = new DB_Hmi_Gui_System_Io();
    QWidget* PanelInputWidget = Create_System_Switch_Page(PanelInputPage);
    QWidget* PanelOutputWidget = Create_System_Switch_Page(PanelOutputPage);
    QWidget* CompensationValueWidget = Create_System_Switch_Page(CompensationValuePage);

    mSWidget->addWidget(InformationWidget);
    mSWidget->addWidget(PLCMonitoringWidget);
    mSWidget->addWidget(CNCInputWidget);
    mSWidget->addWidget(CNCOutputWidget);
    mSWidget->addWidget(PanelInputWidget);
    mSWidget->addWidget(PanelOutputWidget);
    mSWidget->addWidget(CompensationValueWidget);


    QWidget* button_Widget = Create_Button_Widget();

    mHLayout->addWidget(mSWidget);
    mHLayout->addWidget(button_Widget);
    mHLayout->setStretchFactor(mSWidget,6);
    mHLayout->setStretchFactor(button_Widget,1);
    m_Widget->setLayout(mHLayout);

    this->connect(this,&DB_Hmi_Body_System::SwitchSWidgetPage,this,[=](int index){mSWidget->setCurrentIndex(index);});
    this->connect(RunTcp::Get(),&RunTcp::Set_PlcIn_Signal,CNCInputWidget,&DB_Hmi_Gui_System_Io::Set_PLCIO);
    this->connect(RunTcp::Get(),&RunTcp::Set_PLCOut_Signal,CNCOutputWidget,&DB_Hmi_Gui_System_Io::Set_PLCIO);

    return m_Widget;
}

#if 0
//封装程序的QGroupBox以及内部的内容
QGroupBox* DB_Hmi_Body_System::Create_Program_Box()
{
    QGroupBox* Program_Box = new QGroupBox();
    Program_Box->setTitle("程序");
    QVBoxLayout* Program_Box_Layout = new QVBoxLayout();
    Program_Box_Layout->setSpacing(0);
    Program_Box_Layout->setContentsMargins(0,0,0,0);

    QLabel* lbl_Program_num = new QLabel();
    lbl_Program_num->setText("程序号");
    QLabel* lbl_Parent_Program_num = new QLabel();
    lbl_Parent_Program_num->setText("子程序号");
    QLabel* lbl_Procedures_section_no = new QLabel();
    lbl_Procedures_section_no->setText("程序段号");
    QLabel* lbl_Workpiece_rotation = new QLabel();
    lbl_Workpiece_rotation->setText("工件旋转");
    QLabel* lbl_Proportion_rotating = new QLabel();
    lbl_Proportion_rotating->setText("比例缩放");

    Program_Box_Layout->addWidget(lbl_Program_num,0,Qt::AlignCenter);
    Program_Box_Layout->addWidget(lbl_Parent_Program_num,0,Qt::AlignCenter);
    Program_Box_Layout->addWidget(lbl_Procedures_section_no,0,Qt::AlignCenter);
    Program_Box_Layout->addWidget(lbl_Workpiece_rotation,0,Qt::AlignCenter);
    Program_Box_Layout->addWidget(lbl_Proportion_rotating,0,Qt::AlignCenter);
    Program_Box->setLayout(Program_Box_Layout);

    return Program_Box;
}
#endif

#if 0
//封装返回工件原点的QGroupBox以及内部的内容
QGroupBox* DB_Hmi_Body_System::Create_Origin_workpiece_Box()
{
    QGroupBox* Origin_workpiece_Box = new QGroupBox();
    Origin_workpiece_Box->setTitle("返回工件原点");

    QVBoxLayout* Origin_workpiece_Layout = new QVBoxLayout();
    Origin_workpiece_Layout->setSpacing(0);
    Origin_workpiece_Layout->setContentsMargins(0,0,0,0);

    QRadioButton* btn_First = new QRadioButton();
    btn_First->setText("第一次加工起点");
    QRadioButton* btn_two = new QRadioButton();
    btn_two->setText("第二次加工起点");
    QRadioButton* btn_three = new QRadioButton();
    btn_three->setText("第三次加工起点");
    QRadioButton* btn_four = new QRadioButton();
    btn_four->setText("第四次加工起点");
    QRadioButton* btn_five = new QRadioButton();
    btn_five->setText("第五次加工起点");

    Origin_workpiece_Layout->addWidget(btn_First,0,Qt::AlignCenter);
    Origin_workpiece_Layout->addWidget(btn_two,0,Qt::AlignCenter);
    Origin_workpiece_Layout->addWidget(btn_three,0,Qt::AlignCenter);
    Origin_workpiece_Layout->addWidget(btn_four,0,Qt::AlignCenter);
    Origin_workpiece_Layout->addWidget(btn_five,0,Qt::AlignCenter);
    Origin_workpiece_Box->setLayout(Origin_workpiece_Layout);

    return Origin_workpiece_Box;
}
#endif

//封装右边按钮的Widget
QWidget* DB_Hmi_Body_System::Create_Button_Widget()
{
    QWidget* button_Widget = new QWidget();
    button_Widget->setObjectName("button_Widget");
    button_Widget->setStyleSheet("QWidget#button_Widget{background-color:#666666;}");

    QVBoxLayout* button_Layout = new QVBoxLayout();
    button_Layout->setSpacing(0);
    button_Layout->setContentsMargins(0,0,20,0);

    QPushButton* btn_information = Create_Button("信息显示",B_Top,0,":/Icon/Img/Icon/pbtn_1_on.png");
    QPushButton* btn_cnc_input = Create_Button("PLC监控",B_Body,1,":/Icon/Img/Icon/pbtn_2_off.png");
    QPushButton* btn_cnc_output = Create_Button("CNC输入",B_Body,2,":/Icon/Img/Icon/pbtn_3_off.png");
    QPushButton* btn_plc_input = Create_Button("CNC输出",B_Body,3,":/Icon/Img/Icon/pbtn_4_off.png");
    QPushButton* btn_plc_output = Create_Button("面板输入",B_Body,4,":/Icon/Img/Icon/pbtn_5_off.png");
    QPushButton* btn_panel_output = Create_Button("面板输出",B_Body,5,":/Icon/Img/Icon/pbtn_6_off.png");
    QPushButton* btn_compensation_value = Create_Button(" 补偿值 ",B_Body,6,":/Icon/Img/Icon/pbtn_7_off.png");
    QPushButton* btn_parameter_value = Create_Button(" 参数值 ",B_Bottom,7,":/Icon/Img/Icon/pbtn_8_off.png");

    btn_information->click();
    button_Layout->addStretch();
    button_Layout->addWidget(btn_information);
    button_Layout->addWidget(btn_cnc_input);
    button_Layout->addWidget(btn_cnc_output);
    button_Layout->addWidget(btn_plc_input);
    button_Layout->addWidget(btn_plc_output);
    button_Layout->addWidget(btn_panel_output);
    button_Layout->addWidget(btn_compensation_value);
    button_Layout->addWidget(btn_parameter_value);
    button_Layout->addStretch();

    button_Widget->setLayout(button_Layout);

    this->connect(this,&DB_Hmi_Body_System::ButtonClicked,this,[=](QPushButton* btn){
       QList<QPushButton*> btnList = button_Widget->findChildren<QPushButton*>();
       btnList.at(0)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_1_off.png"));
       btnList.at(1)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_2_off.png"));
       btnList.at(2)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_3_off.png"));
       btnList.at(3)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_4_off.png"));
       btnList.at(4)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_5_off.png"));
       btnList.at(5)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_6_off.png"));
       btnList.at(6)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_7_off.png"));
       btnList.at(7)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_8_off.png"));
       if(btn == btnList.at(0))
       {
            btnList.at(0)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_1_on.png"));
       }
       else if(btn == btnList.at(1))
       {
           btnList.at(1)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_2_on.png"));
       }
       else if(btn == btnList.at(2))
       {
           btnList.at(2)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_3_on.png"));
       }
       else if(btn == btnList.at(3))
       {
           btnList.at(3)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_4_on.png"));
       }
       else if(btn == btnList.at(4))
       {
           btnList.at(4)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_5_on.png"));
       }
       else if(btn == btnList.at(5))
       {
           btnList.at(5)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_6_on.png"));
       }
       else if(btn == btnList.at(6))
       {
           btnList.at(6)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_7_on.png"));
       }
       else if(btn == btnList.at(7))
       {
           btnList.at(7)->setIcon(QIcon(":/Icon/Img/Icon/pbtn_8_on.png"));
       }
    });

    return button_Widget;
}

//创建按钮
QPushButton* DB_Hmi_Body_System::Create_Button(QString text,Button_Style style,int index,QString Icon)
{
    QString ButtonStyle = "";
    switch(style)
    {
    case B_Top:
    {
        const QString Top_Button_Style = Public_Str::Get_Sty(Style_Css{SystemRightButtonTop,{}});
        ButtonStyle = Top_Button_Style;
        break;
    }
    case B_Body:
    {
        const QString Button_Style = Public_Str::Get_Sty(Style_Css{SystemRightButtonMid,{}});
        ButtonStyle = Button_Style;
        break;
    }
    case B_Bottom:
    {
        const QString Buttom_Button_Style = Public_Str::Get_Sty(Style_Css{SystemRightButtonBottom,{}});
        ButtonStyle = Buttom_Button_Style;
        break;
    }
    }

    QPushButton* btn_information = new QPushButton();
    btn_information->setIcon(QIcon(Icon));
    btn_information->setIconSize(QSize(32,32));
    btn_information->setText(text);
    btn_information->setFixedHeight(60);
//    btn_information->setFixedSize(130,60);
    btn_information->setStyleSheet(ButtonStyle);
    btn_information->setCheckable(true);
    btn_information->setAutoExclusive(true);
    this->connect(btn_information,&QPushButton::clicked,this,[=](){
        emit SwitchSWidgetPage(index);
        emit ButtonClicked(btn_information);
        if(index == 1)
        {
            this->Write_Io();
        }
    });

    return btn_information;
}

//创建切换界面
QWidget* DB_Hmi_Body_System::Create_System_Switch_Page(SystemSwitchPage type)
{
    QWidget* Widget = nullptr;
    switch(type)
    {
    case InformationPage:
    {
        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(0,0,0,0);

        //G代码
        QGroupBox* GBox = new QGroupBox();
        GBox->setTitle("G代码");
        QVBoxLayout* GBoxLayout = new QVBoxLayout();
        GBoxLayout->setSpacing(0);
        GBoxLayout->setContentsMargins(0,0,0,0);\
        for(int i = 0; i < 14; i++)
        {
            QHBoxLayout* mHLayout = new QHBoxLayout();
            mHLayout->setSpacing(0);
            mHLayout->setContentsMargins(0,0,0,0);
            QLabel* lblG1 = Public_Control::Get_Label("");

            QLabel* lblG2 = Public_Control::Get_Label("");

            QLabel* lblG3 = Public_Control::Get_Label("");

            mHLayout->addWidget(lblG1);
            mHLayout->addWidget(lblG2);
            mHLayout->addWidget(lblG3);
            GBoxLayout->addLayout(mHLayout);
        }
        GBox->setLayout(GBoxLayout);

        QVBoxLayout* mMidLayout = new QVBoxLayout();
        mMidLayout->setSpacing(0);
        mMidLayout->setContentsMargins(0,0,0,0);
        //补偿值
        QGroupBox* CompensationValueBox = new QGroupBox();
        CompensationValueBox->setTitle("补偿值");
        QVBoxLayout* CompensationValueBoxLayout = new QVBoxLayout();
        CompensationValueBoxLayout->setSpacing(0);
        CompensationValueBoxLayout->setContentsMargins(0,0,0,0);
        for(int i = 0; i < 6; i++)
        {
            QLabel* lbl = Public_Control::Get_Label("");
            CompensationValueBoxLayout->addWidget(lbl);
        }
        CompensationValueBox->setLayout(CompensationValueBoxLayout);

        //BCD码
        QGroupBox* BCDBox = new QGroupBox();
        BCDBox->setTitle("BCD码");
        QVBoxLayout* BCDLayout = new QVBoxLayout();
        BCDLayout->setSpacing(0);
        BCDLayout->setContentsMargins(0,0,0,0);
        for(int i = 0; i < 4; i++)
        {
            QLabel* lbl = Public_Control::Get_Label("");
            BCDLayout->addWidget(lbl);
        }
        BCDBox->setLayout(BCDLayout);

        mMidLayout->addWidget(CompensationValueBox);
        mMidLayout->addWidget(BCDBox);

        QVBoxLayout* mButtomLayout = new QVBoxLayout();
        mButtomLayout->setSpacing(0);
        mButtomLayout->setContentsMargins(0,0,0,0);
        //程序
        QGroupBox* ProgramBox = new QGroupBox();
        ProgramBox->setTitle("程序");
        QVBoxLayout* ProgramBoxLayout = new QVBoxLayout();
        ProgramBoxLayout->setSpacing(0);
        ProgramBoxLayout->setContentsMargins(0,0,0,0);
        QStringList ProgramList;
        ProgramList << "程序号" << "子程序号" << "程序段号" << "工件旋转" << "比例缩放";
        for(int i = 0; i < 5; i++)
        {
            QHBoxLayout* mHLayout = new QHBoxLayout();
            mHLayout->setSpacing(0);
            mHLayout->setContentsMargins(0,0,0,0);
            QLabel* lbl_Name = Public_Control::Get_Label(ProgramList.at(i));

            QLabel* lbl_Value = Public_Control::Get_Label("");
            mHLayout->addWidget(lbl_Name);
            mHLayout->addWidget(lbl_Value);
            ProgramBoxLayout->addLayout(mHLayout);
        }
        ProgramBox->setLayout(ProgramBoxLayout);

        QGroupBox* Box = new QGroupBox();

        mButtomLayout->addWidget(ProgramBox);
        mButtomLayout->addWidget(Box);

        mLayout->addWidget(GBox);
        mLayout->addLayout(mMidLayout);
        mLayout->addLayout(mButtomLayout);

        mWidget->setLayout(mLayout);

        Widget = mWidget;

        this->connect(RunTcp::Get(),&RunTcp::Set_BCD_Signal,this,[=](QStringList msg){
            QList<QLabel*> LabelList = BCDBox->findChildren<QLabel*>();
            for(int i = 0; i < msg.size(); i++)
            {
                LabelList.at(i)->setText(msg.at(i));
            }
        });
        this->connect(RunTcp::Get(),&RunTcp::Set_Comp_Signal,this,[=](QStringList msg,QString val,QString val1){
            QList<QLabel*> LabelList = CompensationValueBox->findChildren<QLabel*>();
            QList<QLabel*> ProLabelList = ProgramBox->findChildren<QLabel*>();
            for(int i = 0; i < msg.size(); i++)
            {
                LabelList.at(i)->setText(msg.at(i));
            }
            ProLabelList.at(7)->setText(val);
            ProLabelList.at(9)->setText(val1);
        });
        this->connect(RunTcp::Get(),&RunTcp::Set_Ncda_Signal,this,[=](QStringList msg){
            QStringList List;
            List << "" << "" << "";
            for(int i = 0; i < msg.size(); i++)
            {
                if(msg.at(i).split("_").first() == "prg")
                {
                    List[0] = msg.at(i).split("_").last();
                }
                else if(msg.at(i).split("_").first() == "sub")
                {
                    List[1] = msg.at(i).split("_").last();
                }
                else if(msg.at(i).split("_").first() == "block")
                {
                    List[2] = msg.at(i).split("_").last();
                }
            }
            QList<QLabel*> LabelList = ProgramBox->findChildren<QLabel*>();
            LabelList.at(1)->setText(List.at(0));
            LabelList.at(3)->setText(List.at(1));
            LabelList.at(5)->setText(List.at(2));
        });
        this->connect(RunTcp::Get(),&RunTcp::Set_Gcodes_Signal,this,[=](QStringList msg){
            QList<QLabel*> LabelList = GBox->findChildren<QLabel*>();
            for(int i = 0; i < msg.size(); i++)
            {
                LabelList.at(i)->setText(msg.at(i));
            }
        });
        break;
    }
    case PLCMonitoringPage:
    {
        QWidget* mWidget = new QWidget();
        QVBoxLayout* mLayout = new QVBoxLayout();
        mLayout->setSpacing(10);
        mLayout->setContentsMargins(0,0,0,0);

        QHBoxLayout* TopLayout = new QHBoxLayout();
        TopLayout->setSpacing(0);
        TopLayout->setContentsMargins(0,0,0,0);
        QGroupBox* box = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView1),Setting_Data::Get()->Get_Plc_Bool(PlcMoView1));
        QGroupBox* box1 = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView2),Setting_Data::Get()->Get_Plc_Bool(PlcMoView2));
        QGroupBox* box2 = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView3),Setting_Data::Get()->Get_Plc_Bool(PlcMoView3));
        QGroupBox* box3 = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView4),Setting_Data::Get()->Get_Plc_Bool(PlcMoView4));
        box->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView1));
        box1->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView2));
        box2->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView3));
        box3->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView4));

        TopLayout->addWidget(box);
        TopLayout->addWidget(box1);
        TopLayout->addWidget(box2);
        TopLayout->addWidget(box3);

        QHBoxLayout* BottomLayout = new QHBoxLayout();
        BottomLayout->setSpacing(0);
        BottomLayout->setContentsMargins(0,0,0,0);
        QGroupBox* box4 = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView5),Setting_Data::Get()->Get_Plc_Bool(PlcMoView5));
        QGroupBox* box5 = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView6),Setting_Data::Get()->Get_Plc_Bool(PlcMoView6));
        QGroupBox* box6 = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView7),Setting_Data::Get()->Get_Plc_Bool(PlcMoView7));
        QGroupBox* box7 = Create_PLCBox_Val(Setting_Data::Get()->Get_PLCMoListSystem(PlcMoView8),Setting_Data::Get()->Get_Plc_Bool(PlcMoView8));
        box4->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView5));
        box5->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView6));
        box6->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView7));
        box7->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView8));

        BottomLayout->addWidget(box4);
        BottomLayout->addWidget(box5);
        BottomLayout->addWidget(box6);
        BottomLayout->addWidget(box7);

        mLayout->addLayout(TopLayout);
        mLayout->addLayout(BottomLayout);
        mWidget->setLayout(mLayout);

        Widget = mWidget;
        break;
    }
    case PanelInputPage:
    {
        QWidget* mWidget = new QWidget();
        Widget = mWidget;
        break;
    }
    case PanelOutputPage:
    {
        QWidget* mWidget = new QWidget();
        QVBoxLayout* mLayout = new QVBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(0,0,0,0);

        QHBoxLayout* mTopLayout = new QHBoxLayout();
        mTopLayout->setSpacing(0);
        mTopLayout->setContentsMargins(0,0,0,0);

        QGroupBox* DBox = new QGroupBox();
        DBox->setTitle("D参数");
        QHBoxLayout* DBoxLayout = new QHBoxLayout();
        DBoxLayout->setSpacing(0);
        DBoxLayout->setContentsMargins(0,0,0,0);
        DTableView* DView = new DTableView();
        DBoxLayout->addWidget(DView);
        DBox->setLayout(DBoxLayout);

        QGroupBox* HBox = new QGroupBox();
        HBox->setTitle("H参数");
        QHBoxLayout* HBoxLayout = new QHBoxLayout();
        HBoxLayout->setSpacing(0);
        HBoxLayout->setContentsMargins(0,0,0,0);
        HTableView* HView = new HTableView();
        HBoxLayout->addWidget(HView);
        HBox->setLayout(HBoxLayout);

        QGroupBox* GBox = new QGroupBox();
        GBox->setTitle("G参数");
        QHBoxLayout* GBoxLayout = new QHBoxLayout();
        GBoxLayout->setSpacing(0);
        GBoxLayout->setContentsMargins(0,0,0,0);
        GTableView* GView = new GTableView();
        GBoxLayout->addWidget(GView);
        GBox->setLayout(GBoxLayout);

        mTopLayout->addWidget(DBox);
        mTopLayout->addWidget(HBox);
        mTopLayout->addWidget(GBox);

        QWidget* ButtonWidget = new QWidget();
        QHBoxLayout* ButtonLayout = new QHBoxLayout();
        ButtonLayout->setSpacing(0);
        ButtonLayout->setContentsMargins(0,0,0,0);

        QPushButton* btn_SaveD = new QPushButton();
        btn_SaveD->setText("保存D文件");
        QPushButton* btn_SaveH = new QPushButton();
        btn_SaveH->setText("保存H文件");
        QPushButton* btn_SaveG = new QPushButton();
        btn_SaveG->setText("保存G文件");
        QPushButton* btn_Refrush = new QPushButton();
        btn_Refrush->setText("刷新");
        ButtonLayout->addStretch();
        ButtonLayout->addWidget(btn_SaveD);
        ButtonLayout->addWidget(btn_SaveH);
        ButtonLayout->addWidget(btn_SaveG);
        ButtonLayout->addWidget(btn_Refrush);
        ButtonWidget->setLayout(ButtonLayout);

        mLayout->addLayout(mTopLayout);
        mLayout->addWidget(ButtonWidget);
        mWidget->setLayout(mLayout);
        Widget = mWidget;

        this->connect(btn_SaveD,&QPushButton::clicked,this,[=](){

            qDebug() << "Main" << QThread::currentThreadId();
            QFuture<void> f1;
            f1 = QtConcurrent::run(this,&DB_Hmi_Body_System::Save_D);

            f1.waitForFinished();
            qDebug() << "Main" << QThread::currentThreadId();
        });
        this->connect(btn_SaveH,&QPushButton::clicked,this,[=](){
            qDebug() << "Main" << QThread::currentThreadId();
            QFuture<void> f1;
            f1 = QtConcurrent::run(this,&DB_Hmi_Body_System::Save_H);

            f1.waitForFinished();
            qDebug() << "Main" << QThread::currentThreadId();
        });
        this->connect(btn_SaveG,&QPushButton::clicked,this,[=](){
            qDebug() << "Main" << QThread::currentThreadId();
            QFuture<void> f1;
            f1 = QtConcurrent::run(this,&DB_Hmi_Body_System::Save_G);

            f1.waitForFinished();
            qDebug() << "Main" << QThread::currentThreadId();
        });
        this->connect(btn_Refrush,&QPushButton::clicked,this,[=](){
            QList<HTableView*> viewH = this->findChildren<HTableView*>();
            QList<GTableView*> viewG = this->findChildren<GTableView*>();
            QList<DTableView*> viewD = this->findChildren<DTableView*>();
            viewH.at(0)->Clear_All();
            viewG.at(0)->Clear_All();
            viewD.at(0)->Clear_All();

            //D
            QFile file_D("C:\\PACnc\\DBHMI\\D1");
            if (file_D.exists())
            {
                file_D.remove();
            }
            file_D.close();

            RunTcp::Get()->Write("<load><sub>corr</sub><path>C:\\PACnc\\DBHMI</path><name>D1</name><over>yes</over></load>");

            //H
            QFile file_H("C:\\PACnc\\DBHMI\\H1");
            if(file_H.exists())
            {
                file_H.remove();
            }
            file_H.close();
            RunTcp::Get()->Write("<load><sub>length</sub><path>C:\\PACnc\\DBHMI</path><name>H1</name><over>yes</over></load>");

            //G
            QFile file_G("C:\\PACnc\\DBHMI\\G1");
            if(file_G.exists())
            {
                file_G.remove();
            }
            file_G.close();

            RunTcp::Get()->Write("<load><sub>offset</sub><path>C:\\PACnc\\DBHMI</path><name>G1</name><over>yes</over></load>");
        });

        break;
    }
    case CompensationValuePage:
    {
        QWidget* mWidget = new QWidget();
        QVBoxLayout* mLayout = new QVBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(0,0,0,0);

        QHBoxLayout* mTopLayout = new QHBoxLayout();
        mTopLayout->setSpacing(0);
        mTopLayout->setContentsMargins(0,0,0,0);

        //p1-p400
        QGroupBox* PLessBox = new QGroupBox();
        PLessBox->setTitle("循环参数 P1-P400");
        QHBoxLayout* PLessBoxLayout = new QHBoxLayout();
        PLessBoxLayout->setSpacing(0);
        PLessBoxLayout->setContentsMargins(0,0,0,0);
        CyclePLessTableView* DView = new CyclePLessTableView();
        PLessBoxLayout->addWidget(DView);
        PLessBox->setLayout(PLessBoxLayout);

        QGroupBox* PMoreBox = new QGroupBox();
        PMoreBox->setTitle("循环参数 P400-P800");
        QHBoxLayout* PMoreBoxLayout = new QHBoxLayout();
        PMoreBoxLayout->setSpacing(0);
        PMoreBoxLayout->setContentsMargins(0,0,0,0);
        CyclePMoreTableView* HView = new CyclePMoreTableView();
        PMoreBoxLayout->addWidget(HView);
        PMoreBox->setLayout(PMoreBoxLayout);

        QGroupBox* PLastBox = new QGroupBox();
        PLastBox->setTitle("循环参数 P800-P1000");
        QHBoxLayout* PLastBoxLayout = new QHBoxLayout();
        PLastBoxLayout->setSpacing(0);
        PLastBoxLayout->setContentsMargins(0,0,0,0);
        CyclePLastTableView* GView = new CyclePLastTableView();
        PLastBoxLayout->addWidget(GView);
        PLastBox->setLayout(PLastBoxLayout);

        mTopLayout->addWidget(PLessBox);
        mTopLayout->addWidget(PMoreBox);
        mTopLayout->addWidget(PLastBox);

        QWidget* ButtonWidget = new QWidget();
        QHBoxLayout* ButtonLayout = new QHBoxLayout();
        ButtonLayout->setSpacing(0);
        ButtonLayout->setContentsMargins(0,0,0,0);

        QPushButton* btn_Refrush = new QPushButton();
        btn_Refrush->setText("刷新");
        QPushButton* btn_Save = new QPushButton();
        btn_Save->setText("保存");
        ButtonLayout->addStretch();
        ButtonLayout->addWidget(btn_Save);
        ButtonLayout->addWidget(btn_Refrush);
        ButtonWidget->setLayout(ButtonLayout);

        mLayout->addLayout(mTopLayout);
        mLayout->addWidget(ButtonWidget);
        mWidget->setLayout(mLayout);
        Widget = mWidget;

        this->connect(btn_Refrush,&QPushButton::clicked,this,[=](){
            QList<CyclePLessTableView*> ViewLess = this->findChildren<CyclePLessTableView*>();
            QList<CyclePMoreTableView*> ViewMore = this->findChildren<CyclePMoreTableView*>();
            QList<CyclePLastTableView*> ViewLast = this->findChildren<CyclePLastTableView*>();
            ViewLess.at(0)->Clear_All();
            ViewMore.at(0)->Clear_All();
            ViewLast.at(0)->Clear_All();

            QFile file_Z("C:\\PACnc\\DBHMI\\Z1");
            if(file_Z.exists())
            {
                file_Z.remove();
            }
            file_Z.close();

            RunTcp::Get()->Write("<load><sub>par</sub><path>C:\\PACnc\\DBHMI</path><name>Z1</name><over>yes</over></load>");
        });

        QString FilePath = "C:/PACnc/DBHMI/Z1";
        QFile mFile(FilePath);
        if(mFile.exists())
        {
            mFile.remove();
        }
        mFile.close();

        RunTcp::Get()->Write("<load><sub>par</sub><path>C:\\PACnc\\DBHMI</path><name>Z1</name><over>yes</over></load>");

        this->connect(RunTcp::Get(),&RunTcp::Set_LoadZ_Signal,this,[=]()
        {
            QList<QStringList> LessValue;
            QList<QStringList> MoreValue;
            QList<QStringList> LastValue;
            QString FilePath = "C:/PACnc/DBHMI/Z1";
            QFile cfile(FilePath);
            bool isok = cfile.open(QFile::ReadOnly | QFile::Text);
            if(!isok)
            {
                qDebug() << "文件打开失败咯！";
                return;
            }
            QTextStream in(&cfile);
            QString myText;
            int inum=0;
            while(!in.atEnd())
            {
                myText = in.readLine();
                if(myText.indexOf("=")!=-1)
                {
                    QString nval1,nval2,nval3;
                    int nStart = myText.indexOf("=");
                    int nEnd1 = myText.indexOf("E",nStart+1);
                    int nEnd2 = myText.indexOf("\/",nStart+1);
                    if(nStart==-1 || nEnd1==-1)
                    {
                        nval1=nval2=nval3="";
                    }
                    nval1 = myText.mid(nStart+1,nEnd1-nStart-1);
                    if(nEnd2==-1)
                    {
                        nval2 = myText.mid(nEnd1+1);
                        nval3 = "";
                    }
                    else
                    {
                        nval2=myText.mid(nEnd1+1,nEnd2-nEnd1-1);
                        nval3=myText.mid(nEnd2+1);
                    }
                    double aa = nval1.toDouble()*pow(10,nval2.toInt());
                    QString val = QString::number(aa,'g',15);
                    if(inum==3)
                    {
                        qDebug()<<"double : "<<aa;
                        qDebug()<<"val : "<<val;
                    }
                    if(inum < 400)
                    {
                        QStringList valueList;
                        valueList << val << nval3;
                        LessValue.push_back(valueList);
                    }
                    else if(inum >= 400 && inum < 800)
                    {
                        QStringList valueList;
                        valueList << val << nval3;
                        MoreValue.push_back(valueList);
                    }
                    else if(inum >= 800 && inum < 1000)
                    {
                        QStringList valueList;
                        valueList << val << nval3;
                        LastValue.push_back(valueList);
                    }

                    inum++;
                }
            }
            DView->Set_Value(LessValue);
            HView->Set_Value(MoreValue);
            GView->Set_Value(LastValue);
        });

        this->connect(btn_Save,&QPushButton::clicked,this,[=](){
            QFuture<void> f;
            f = QtConcurrent::run(this,&DB_Hmi_Body_System::Save_Z);
            f.waitForFinished();
        });
    }
    }

    return Widget;
}

void DB_Hmi_Body_System::Save_Z()
{
    QFile file_H("C:\\PACnc\\DBHMI\\Z1");
    if (file_H.exists())
    {
        file_H.remove();
    }
    file_H.close();

    //H
    QString FilePath = "C:\\PACnc\\DBHMI\\Z1";
    QFile cfile(FilePath);
    if(!cfile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
//        QMessageBox::warning(NULL,tr("提示"),tr("新建 Z 参数文件 失败"));
        return;
    }
    QTextStream in(&cfile);
    QString text1;
    in<<"\n"<<"%"<<"\n"<<"ZTAB01\n";
    for(int inum=0;inum<1000;inum++)
    {
        if(inum<9)
        {
            text1="P0000"+QString::number(inum+1)+"=";
        }
        else if(inum<99)
        {
            text1="P000"+QString::number(inum+1)+"=";
        }
        else if(inum<999)
        {
            text1="P00"+QString::number(inum+1)+"=";
        }
        else if(inum<9999)
        {
            text1="P0"+QString::number(inum+1)+"=";
        }
        else if(inum<99999)
        {
            text1="P"+QString::number(inum+1)+"=";
        }
        QString val1,val2;
        if(inum<400)
        {
           QList<CyclePLessTableView*> View = this->findChildren<CyclePLessTableView*>();
           QList<QStringList> List = View.at(0)->Get_Value();
           val1 = List.at(inum).at(0);
           val2 = List.at(inum).at(1);
        }
        else if(inum >= 400 && inum < 800)
        {
            QList<CyclePMoreTableView*> View = this->findChildren<CyclePMoreTableView*>();
            QList<QStringList> List = View.at(0)->Get_Value();
            val1 = List.at(inum - 400).at(0);
            val2 = List.at(inum - 400).at(1);
        }
        else if(inum >= 800 && inum < 1000)
        {
            QList<CyclePLastTableView*> View = this->findChildren<CyclePLastTableView*>();
            QList<QStringList> List = View.at(0)->Get_Value();
            val1 = List.at(inum - 800).at(0);
            val2 = List.at(inum - 800).at(1);
        }
        qDebug() << inum;

//        val1 = P_Txt[inum][0]->text();
//        val2 = P_Txt[inum][1]->text();
        double num1=0;
        int E_val=0;
        if(val1!="")
        {
            num1 = val1.toDouble();
            if(num1>0)
            {
                if(num1>1)
                {
                    for(;num1>5;E_val++)
                    {
                        num1=num1/10.0;
                    }
                }
                else
                {
                    for(;num1<0.5;E_val--)
                    {
                        num1=num1*10.0;
                    }
                }
            }
            else if(qAbs(num1)<0.0001)
            {

            }
            else
            {
                if(num1<-1)
                {
                    for(;num1<-5;E_val++)
                    {
                        num1=num1/10.0;
                    }
                }
                else
                {
                    for(;num1>-0.5;E_val--)
                    {
                        num1=num1*10.0;
                    }
                }
            }
        }
        QString FirstVal = Public_Function::GetAddString(QString::number(num1));
        QString SecondVal = Public_Function::GetAddString(QString::number(E_val));
        in
           <<text1
          //<<num1
           <<FirstVal
           <<"E"
           <<SecondVal
           <<"\/"
           <<val2
           <<"\n";
    }

    cfile.close();

    RunTcp::Get()->Write("<unload><sub>par</sub><path>C:\\PACnc\\DBHMI\\Z1</path><name>Z1</name><over>yes</over></unload>");
}


void DB_Hmi_Body_System::Save_G()
{
    qDebug() << "G : " << QThread::currentThreadId();
    QList<GTableView*> View = this->findChildren<GTableView*>();
    QList<QStringList> List = View.at(0)->Get_Value();
    QStringList Nacd_Name = View.at(0)->Get_Nacd_Name();
    QFile file_G("C:\\PACnc\\DBHMI\\G1");
    if (file_G.exists())
    {
        file_G.remove();
    }
    file_G.close();

    //G
    QString FilePath = "C:\\PACnc\\DBHMI\\G1";
    QFile cfile(FilePath);
    if(!cfile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&cfile);

    in<<"\n"<<"%"<<"\n"<<"GTAB01\n";
    for(int inum=0;inum<6;inum++)
    {
        in
           <<"G"+QString::number(inum+54)
           <<Nacd_Name.at(0)
           <<List.at(inum).at(0)
           <<Nacd_Name.at(1)
           <<List.at(inum).at(1)
           <<Nacd_Name.at(2)
           <<List.at(inum).at(2)
           <<Nacd_Name.at(3)
           <<List.at(inum).at(3)
           << "\n";
    }

    //G
    RunTcp::Get()->Write("<unload><sub>offset</sub><path>C:\\PACnc\\DBHMI\\G1</path><name>G1</name><over>yes</over></unload>");

    cfile.close();
}

void DB_Hmi_Body_System::Save_H()
{
    qDebug() << "H " << QThread::currentThreadId();
    QList<HTableView*> View = this->findChildren<HTableView*>();
    QList<QStringList> msg = View.at(0)->Get_Value();
    QFile file_H("C:\\PACnc\\DBHMI\\H1");
    if (file_H.exists())
    {
        file_H.remove();
    }
    file_H.close();

    //H
    QString FilePath = "C:\\PACnc\\DBHMI\\H1";
    QFile cfile(FilePath);
    if(!cfile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&cfile);
    QString text1;
    in<<"\n"<<"%"<<"\n"<<"HTAB01\n";
    for(int inum=0;inum<128;inum++)
    {
        if(inum<9)
        {
            text1="H00"+QString::number(inum+1)+" Z=";
        }
        else if(inum<99)
        {
            text1="H0"+QString::number(inum+1)+" Z=";
        }
        else
        {
            text1="H"+QString::number(inum+1)+" Z=";
        }

        QString firstval = Public_Function::GetAddString(msg.at(inum).at(0));
        QString secondval = Public_Function::GetAddString(msg.at(inum).at(1));

        in
           <<text1
           <<firstval
           <<" "
           <<secondval
           <<"\n";

    }

    //H
    RunTcp::Get()->Write("<unload><sub>length</sub><path>C:\\PACnc\\DBHMI\\H1</path><name>H1</name><over>yes</over></unload>");

    cfile.close();
}

void DB_Hmi_Body_System::Save_D()
{
    qDebug() << "D " << QThread::currentThreadId();
    QList<DTableView*> View = this->findChildren<DTableView*>();
    QList<QStringList> List = View.at(0)->Get_Value();
    QFile file_D("C:\\PACnc\\DBHMI\\D1");
    if (file_D.exists())
    {
        file_D.remove();
    }
    file_D.close();

    //D
    QString FilePath = "C:\\PACnc\\DBHMI\\D1";
    QFile cfile(FilePath);
    if(!cfile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&cfile);
    QString text1;
    in<<"\n"<<"%"<<"\n"<<"DTAB01\n";
    for(int inum=0;inum<128;inum++)
    {
        if(inum<9)
        {
            text1="D00"+QString::number(inum+1)+"=";
        }
        else if(inum<99)
        {
            text1="D0"+QString::number(inum+1)+"=";
        }
        else
        {
            text1="D"+QString::number(inum+1)+"=";
        }
        QString firstval = Public_Function::GetAddString(List.at(inum).at(0));
        QString secondval = Public_Function::GetAddString(List.at(inum).at(1));

        in
           <<text1
           <<firstval
           <<" "
           <<secondval
           <<" "
           <<"R0\n";
    }

    //D
    RunTcp::Get()->Write("<unload><sub>corr</sub><path>C:\\PACnc\\DBHMI\\D1</path><name>D1</name><over>yes</over></unload>");

    cfile.close();
}

//创建PLC监控的8参数
QGroupBox* DB_Hmi_Body_System::Create_PLCBox_Val(QList<QStringList> List,bool state)
{
    QStringList InOutType;
    QList<int> AddSecNum;
    int FirVal = 0;
    QList<QPushButton*> BtnList;

    QGroupBox* box = new QGroupBox();
    QVBoxLayout* Layout = new QVBoxLayout();
    Layout->setSpacing(0);
    Layout->setContentsMargins(0,0,0,0);

    if(state)
    {
        for(int i = 0; i < List.at(0).size(); i++)
        {
            if(List.at(0).at(i).isEmpty())
                continue;
            if(List.at(0).at(i).indexOf("Ix") == -1 && List.at(0).at(i).indexOf("QX") == -1)
            {
                continue;
            }
            QString Second = List.at(0).at(i).split(".").last();
            if(List.at(0).at(i).indexOf("Ix") != -1)
            {
                QString Fir = List.at(0).at(i).split(".").first().split("Ix").last();
                if(Fir.isEmpty())
                    continue;
                IOVal << "in";
                AddFirVal << Fir.toInt();
                FirVal = Fir.toInt();
                if(Second.isEmpty())
                    AddSecNum << 0;
                AddSecNum << Second.toInt();
            }
            else if(List.at(0).at(i).indexOf("QX") != -1)
            {
                QString Fir = List.at(0).at(i).split(".").first().split("QX").last();
                if(Fir.isEmpty())
                    continue;
                IOVal << "out";
                AddFirVal << Fir.toInt();
                FirVal = Fir.toInt();
                if(Second.isEmpty())
                    AddSecNum << 0;
                AddSecNum << Second.toInt();
            }

            QHBoxLayout* mHbox = new QHBoxLayout();
            mHbox->setSpacing(0);
            mHbox->setContentsMargins(0,0,0,0);
            QLabel* lbl_plc = Public_Control::Get_Label(List.at(0).at(i));
            lbl_plc->setFixedHeight(40);

            QPushButton* btn = Public_Control::Get_Button("","",0,0,"border:none;");
            BtnList << btn;
            btn->setObjectName(QString("%1btn%2").arg(FirVal).arg(AddSecNum.at(i)));
            btn->setFixedHeight(40);

            QLabel* lbl_Name = Public_Control::Get_Label(List.at(1).at(i));

            mHbox->addWidget(lbl_plc);
            mHbox->addWidget(btn);
            mHbox->addWidget(lbl_Name);
            Layout->addLayout(mHbox);
        }
    }
    Layout->addStretch();
    box->setLayout(Layout);

    this->connect(RunTcp::Get(),&RunTcp::Set_PLCIoInOutStareSignal,this,[=](QVariant val,int state){
        for(int z=0;z<AddSecNum.size();z++)
        {
            int j = AddSecNum.at(z);
            qDebug() << state;
            qDebug() << j << (1 << (j - 1));
            if(state & (1<<(j-1)))
            {
                for(int Count = 0; Count < BtnList.size(); Count++)
                {
                    if(BtnList.at(Count)->objectName().split("btn").first() == val)
                    {
                        if(BtnList.at(Count)->objectName().split("btn").last().toInt() == j)
                        {
                            BtnList.at(Count)->setIcon(QIcon(":/Img/system/on_1.png"));
                        }
                    }
                }
            }
            else
            {
                for(int Count = 0; Count < BtnList.size(); Count++)
                {
                    if(BtnList.at(Count)->objectName().split("btn").first() == val)
                    {
                        if(BtnList.at(Count)->objectName().split("btn").last().toInt() == j)
                        {
                            BtnList.at(Count)->setIcon(QIcon(":/Img/system/off_1.png"));
                        }
                    }
                }
            }
        }
    });

    return box;
}


void DB_Hmi_Body_System::Write_Io()
{
    QList<int> Send_Num;
    for(int i = 0; i < AddFirVal.size(); i++)
    {
        if(!Send_Num.contains(AddFirVal.at(i)))
        {
            RunTcp::Get()->Write(QString("<io><sub>%1</sub><st>plc</st><ri>%2</ri><auto>yes</auto><time>300</time></io>").arg(IOVal.at(i)).arg(AddFirVal.at(i)));
            Send_Num.push_back(AddFirVal.at(i));
        }
    }
}
