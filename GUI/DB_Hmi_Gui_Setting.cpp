#include "DB_Hmi_Gui_Setting.h"
#include "QHBoxLayout"
#include <QStackedWidget>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>

#include "../Socket/RunTcp.h"
#include "DB_Hmi_Gui_Setting_Conf.h"
#include "../Ini_Dbdata/Setting_Data.h"
#include "../GUI/DB_Hmi_Gui_Change_Passwd.h"
#include "Public/Public_Control.h"
#include "Public/Public_Str.h"

DB_Hmi_Gui_Setting::DB_Hmi_Gui_Setting(QWidget* parent)
    :QWidget (parent)
{
    this->init();
}
DB_Hmi_Gui_Setting::~DB_Hmi_Gui_Setting()
{

}

void DB_Hmi_Gui_Setting::init()
{
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    QWidget* InitWidget = InitLayout();

    layout->addWidget(InitWidget);

    this->setLayout(layout);
}
QWidget* DB_Hmi_Gui_Setting::InitLayout()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mHLayout = new QHBoxLayout();
    mHLayout->setSpacing(10);
    mHLayout->setContentsMargins(10,10,10,10);

    QStackedWidget* mSWidget = new QStackedWidget();
    QWidget* IoSetWidget = Create_System_Switch_Page(IOSetPage);
    QWidget* MachineWidget = Create_System_Switch_Page(MachineSetPage);

    mSWidget->addWidget(IoSetWidget);
    mSWidget->addWidget(MachineWidget);

    QWidget* mRightWidget = new QWidget();
    mRightWidget->setObjectName("mRightWidget");
    mRightWidget->setStyleSheet("QWidget#mRightWidget{background-color:rgb(150,150,150);}");
    QVBoxLayout* Layout = new QVBoxLayout();
    Layout->setSpacing(20);
    Layout->setContentsMargins(0,0,20,0);

    QVBoxLayout* button_Layout = new QVBoxLayout();
    button_Layout->setSpacing(0);
    button_Layout->setContentsMargins(0,0,0,0);

    QPushButton* btn_information = Create_Button("PLC显示",B_TOP);
    QPushButton* btn_cnc_input = Create_Button("机床参数",B_BODY);
    QPushButton* btn_cnc_output = Create_Button("IO/驱动配置",B_BODY);
    QPushButton* btn_plc_input = Create_Button("机床设置",B_BODY);
    QPushButton* btn_plc_output = Create_Button("日志文件",B_BODY);
    QPushButton* btn_panel_input = Create_Button("逻辑分析仪",B_BODY);
    QPushButton* btn_panel_output = Create_Button("编辑NC程序",B_BODY);
    QPushButton* btn_compensation_value = Create_Button("修改密码",B_BOTTOM);

    this->connect(btn_cnc_output,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(0);});
    this->connect(btn_plc_input,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(1);});
    this->connect(btn_information,&QPushButton::clicked,this,[=](){
        QString fileName;
        fileName = "C:\\PACnc\\IEC1131\\IEC1131 Engl\\plc1131-3.exe";
        QProcess *process=new QProcess;
        QDir::setCurrent(QFileInfo(fileName).path());//进入程序所在文件夹
        process->start(QFileInfo(fileName).fileName());//执行程序
        if(!(process->state()!=QProcess::NotRunning))//如果程序执行成功返回false，失败返回true
            QMessageBox::warning(this,tr("警告！"),tr("PLC暂时无法打开，请刷新后重试！"));
    });
    this->connect(btn_plc_output,&QPushButton::clicked,this,[=](){
        QProcess Process(this);
        Process.startDetached("hmiframe -p:logbook");
    });
    this->connect(btn_cnc_input,&QPushButton::clicked,this,[=](){
        QProcess Process(this);
        Process.startDetached("hmiframe -p:setuptool");
    });
    this->connect(btn_panel_input,&QPushButton::clicked,this,[=](){
        QProcess Process(this);
        Process.startDetached("hmiframe -p:la");
    });
    this->connect(btn_panel_output,&QPushButton::clicked,this,[=](){
        QProcess Process(this);
        Process.startDetached("hmiframe -p:nceditor");
    });
    this->connect(btn_compensation_value,&QPushButton::clicked,this,[=](){
        DB_Hmi_Gui_Change_Passwd* passwd = new DB_Hmi_Gui_Change_Passwd();
        bool isok = passwd->exec();
        if(isok == 1)
        {
            passwd->deleteLater();
            passwd = nullptr;
            QMessageBox::information(this,"成功","密码已经修改并且即可生效哦!");
        }
    });

    btn_cnc_output->click();

    button_Layout->addStretch();
    button_Layout->addWidget(btn_information);
    button_Layout->addWidget(btn_cnc_input);
    button_Layout->addWidget(btn_cnc_output);
    button_Layout->addWidget(btn_plc_input);
    button_Layout->addWidget(btn_plc_output);
    button_Layout->addWidget(btn_panel_input);
    button_Layout->addWidget(btn_panel_output);
    button_Layout->addWidget(btn_compensation_value);
    button_Layout->addStretch();

    Layout->addLayout(button_Layout);
    mRightWidget->setLayout(Layout);

    mHLayout->addWidget(mSWidget);
    mHLayout->addWidget(mRightWidget);
    mHLayout->setStretchFactor(mSWidget,6);
    mHLayout->setStretchFactor(mRightWidget,1);

    mWidget->setLayout(mHLayout);

    return mWidget;

}

#if 0
QWidget* DB_Hmi_Gui_Setting::Init_Set_Widget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QGroupBox* Set_Box = new QGroupBox();
    Set_Box->setTitle("Set");
    Set_Box->setStyleSheet("QGroupBox"
                        "{"
                        "font: 12pt ""黑体"";"
                        "border: 3px solid white;"
                        "margin-top:6px;"
                        "}"
                        "QGroupBox:title"
                        "{"
                        "subcontrol-origin: margin;"
                        "subcontrol-position: top center;"
                        "color:rgb(0,0,0);"
                        "}");
    QHBoxLayout* Set_Layout = new QHBoxLayout();
    Set_Layout->setSpacing(10);
    Set_Layout->setContentsMargins(20,20,20,20);

    QStringList Str_Name;
    Str_Name << "激光点射时间" << "激光点射功率" << "激光点射频率" << "点射沾空比率" <<
                "切割关光延时" << "默认气压设置" << "首次开气延时" << "开气切换延时" <<
                "默认随动高度" << "无蛙跳上抬";

    QList<double> Spin_Value;
    for(int i = 0; i < 10; i++)
        Spin_Value.push_back(0.00);


    QStringList Str_Unit;
    Str_Unit << "毫秒" << "%" << "HZ" << "%" << "ms" << "Bar" << "毫秒" << "毫秒"
             << "毫秒" << "毫秒" << "毫米";

    QVBoxLayout* Machine_Tool_Layout = new QVBoxLayout();
    Machine_Tool_Layout->setSpacing(0);
    Machine_Tool_Layout->setContentsMargins(0,0,0,0);
    QGroupBox* Machine_tool_Set_box = Create_Box(Str_Name,Spin_Value,Str_Unit);
    Machine_tool_Set_box->setFixedSize(600,500);
    Machine_tool_Set_box->setTitle("机床设置一");
    Machine_tool_Set_box->setAlignment(Qt::AlignHCenter);
    Machine_tool_Set_box->setStyleSheet("QGroupBox"
                                        "{"
                                        "font: 12pt ""黑体"";"
                                        "border: 3px solid white;"
                                        "margin-top:6px;"
                                        "}"
                                        "QGroupBox:title"
                                        "{"
                                        "subcontrol-origin: margin;"
                                        "subcontrol-position: top center;"
                                        "color:rgb(0,0,0);"
                                        "}");
    Machine_Tool_Layout->addWidget(Machine_tool_Set_box);
    Machine_Tool_Layout->addStretch();

    QVBoxLayout* Machine_Tool1_Layout = new QVBoxLayout();
    Machine_Tool_Layout->setSpacing(0);
    Machine_Tool_Layout->setContentsMargins(0,0,0,0);
    QGroupBox* Machine_tool_Set_Second_box = Create_Box(Str_Name,Spin_Value,Str_Unit);
    Machine_tool_Set_Second_box->setTitle("机床设置二");
    Machine_tool_Set_Second_box->setFixedSize(600,500);
    Machine_tool_Set_Second_box->setAlignment(Qt::AlignCenter);
    Machine_tool_Set_Second_box->setStyleSheet("QGroupBox"
                                               "{"
                                               "font: 12pt ""黑体"";"
                                               "border: 3px solid white;"
                                               "margin-top:6px;"
                                               "}"
                                               "QGroupBox:title"
                                               "{"
                                               "subcontrol-origin: margin;"
                                               "subcontrol-position: top center;"
                                               "color:rgb(0,0,0);"
                                               "}");
    Machine_Tool1_Layout->addWidget(Machine_tool_Set_Second_box);
    Machine_Tool1_Layout->addStretch();

    QVBoxLayout* Right_Layout = new QVBoxLayout();
    Right_Layout->setSpacing(0);
    Right_Layout->setContentsMargins(0,0,0,0);

    QGroupBox* Cnc_parameter_Box = new QGroupBox();
    Cnc_parameter_Box->setFixedSize(200,100);
    Cnc_parameter_Box->setTitle("参数");
    QHBoxLayout* Cnc_parameter_Layout = new QHBoxLayout();
    Cnc_parameter_Layout->setSpacing(0);
    Cnc_parameter_Layout->setContentsMargins(10,10,10,10);

    const QString btn_Cnc_Parameter_Style = "background-color:rgb(0,0,0);"
                                            "color:rgb(255,255,255);";
    QPushButton* btn_Cnc_Parameter = new QPushButton();
    btn_Cnc_Parameter->setText("cnc参数");
    btn_Cnc_Parameter->setFixedHeight(60);
    btn_Cnc_Parameter->setStyleSheet(btn_Cnc_Parameter_Style);
    Cnc_parameter_Layout->addWidget(btn_Cnc_Parameter);
    Cnc_parameter_Box->setLayout(Cnc_parameter_Layout);

    const QString btn_Sure_Style = "";
    QPushButton* btn_Sure = new QPushButton();
    btn_Sure->setFixedSize(180,60);
    btn_Sure->setText("确定");
    btn_Sure->setStyleSheet(btn_Sure_Style);

    Right_Layout->addWidget(Cnc_parameter_Box);
    Right_Layout->addStretch();
    Right_Layout->addWidget(btn_Sure);

    Set_Layout->addLayout(Machine_Tool_Layout);
    Set_Layout->addLayout(Machine_Tool1_Layout);
    Set_Layout->addLayout(Right_Layout);
    Set_Box->setLayout(Set_Layout);

    mLayout->addWidget(Set_Box);
    mWidget->setLayout(mLayout);

    return mWidget;
}

QGroupBox* DB_Hmi_Gui_Setting::Create_Box(QStringList Str_Name, QList<double> doubleList, QStringList Str_Unit)
{
    QGroupBox* Machine_tool_Set_box = new QGroupBox();
    QVBoxLayout* Machine_tool_Set_Layout = new QVBoxLayout();
    Machine_tool_Set_Layout->setSpacing(0);
    Machine_tool_Set_Layout->setContentsMargins(0,0,0,0);

    for(int i = 0; i < Str_Name.size(); i++)
    {
        QHBoxLayout* Layout = Label_Double_Spin_Layout(Str_Name.at(i),doubleList.at(i),Str_Unit.at(i));
        Machine_tool_Set_Layout->addLayout(Layout);
    }

    Machine_tool_Set_box->setLayout(Machine_tool_Set_Layout);

    return Machine_tool_Set_box;
}

QWidget* DB_Hmi_Gui_Setting::Init_IO_driver_configuration_Widget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(20,20,20,20);

    QGroupBox* mBox = new QGroupBox();
    mBox->setStyleSheet("QGroupBox"
                        "{"
                        "font: 12pt ""黑体"";"
                        "border: 3px solid white;"
                        "margin-top:6px;"
                        "}"
                        "QGroupBox:title"
                        "{"
                        "subcontrol-origin: margin;"
                        "subcontrol-position: top center;"
                        "color:rgb(0,0,0);"
                        "}");
    mBox->setTitle("IO/驱动 配置");
    QHBoxLayout* mBox_Layout = new QHBoxLayout();
    mBox_Layout->setSpacing(10);
    mBox_Layout->setContentsMargins(10,10,10,10);

    QVBoxLayout* mEditLayout = new QVBoxLayout();
    mEditLayout->setSpacing(0);
    mEditLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl_FileName = new QLabel();
    QTextEdit* t_Edit = new QTextEdit();
    t_Edit->setReadOnly(true);
    mEditLayout->addWidget(lbl_FileName);
    mEditLayout->addWidget(t_Edit);

    QVBoxLayout* mSecondEditLayout = new QVBoxLayout();
    mSecondEditLayout->setSpacing(0);
    mSecondEditLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl_FileName1 = new QLabel();
    QTextEdit* t_Second_Edit = new QTextEdit();
    t_Second_Edit->setReadOnly(true);
    mSecondEditLayout->addWidget(lbl_FileName1);
    mSecondEditLayout->addWidget(t_Second_Edit);

    QVBoxLayout* mThirdEditLayout = new QVBoxLayout();
    mThirdEditLayout->setSpacing(0);
    mThirdEditLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl_FileName2 = new QLabel();
    QTextEdit* t_Third_Edit = new QTextEdit();
    t_Third_Edit->setReadOnly(true);
    mThirdEditLayout->addWidget(lbl_FileName2);
    mThirdEditLayout->addWidget(t_Third_Edit);

    mBox_Layout->addLayout(mEditLayout);
    mBox_Layout->addLayout(mSecondEditLayout);
    mBox_Layout->addLayout(mThirdEditLayout);
    mBox->setLayout(mBox_Layout);

    mLayout->addWidget(mBox);
    mWidget->setLayout(mLayout);

    return mWidget;
}

QHBoxLayout* DB_Hmi_Gui_Setting::Label_Double_Spin_Layout(QString t,double num,QString t1)
{
    QHBoxLayout* Layout = new QHBoxLayout();
    Layout->setSpacing(0);
    Layout->setContentsMargins(0,0,0,0);

    const QString lbl_Text_Style = "";
    QLabel* lbl_Text = new QLabel();
    lbl_Text->setText(t);
    lbl_Text->setStyleSheet(lbl_Text_Style);

    QDoubleSpinBox* Double_Spin = new QDoubleSpinBox();
    Double_Spin->setValue(num);

    QLabel* lbl_Text1 = new QLabel();
    lbl_Text1->setText(t1);
    lbl_Text1->setStyleSheet(lbl_Text_Style);

    Layout->addWidget(lbl_Text);
    Layout->addWidget(Double_Spin);
    Layout->addWidget(lbl_Text1);

    return Layout;
}
#endif

QPushButton* DB_Hmi_Gui_Setting::Create_Button(QString text,Button_Style_Set_Up style)
{
    QString ButtonStyle = "";
    switch(style)
    {
    case B_TOP:
    {
        const QString Top_Button_Style = Public_Str::Get_Sty(Style_Css{SettingRightButtonTop,{}});
        ButtonStyle = Top_Button_Style;
        break;
    }
    case B_BODY:
    {
        const QString Button_Style = Public_Str::Get_Sty(Style_Css{SettingRightButtonMid,{}});
        ButtonStyle = Button_Style;
        break;
    }
    case B_BOTTOM:
    {
        const QString Buttom_Button_Style = Public_Str::Get_Sty(Style_Css{SettingRightButtonBottom,{}});
        ButtonStyle = Buttom_Button_Style;
        break;
    }
    }

    QPushButton* btn_information = new QPushButton();
    btn_information->setText(text);
    btn_information->setFixedHeight(60);
//    btn_information->setFixedSize(170,60);
    btn_information->setStyleSheet(ButtonStyle);
    btn_information->setCheckable(true);
    btn_information->setAutoExclusive(true);

    return btn_information;
}

QWidget* DB_Hmi_Gui_Setting::Create_System_Switch_Page(SettingSwitchPage type)
{
    QWidget* Widget = new QWidget();
    switch(type)
    {
    case IOSetPage:
    {
        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(20,20,20,20);

        QGroupBox* mBox = new QGroupBox();
        mBox->setTitle("IO/驱动 配置");

        QHBoxLayout* mBox_Layout = new QHBoxLayout();
        mBox_Layout->setSpacing(10);
        mBox_Layout->setContentsMargins(10,10,10,10);

        QVBoxLayout* mEditLayout = new QVBoxLayout();
        mEditLayout->setSpacing(5);
        mEditLayout->setContentsMargins(0,0,0,0);
        QLabel* lbl_FileName = new QLabel();
        lbl_FileName->setText("C:\\PACnc\\User data\\PAIOCfg.ini");
        lbl_FileName->setStyleSheet("font: 10pt;");
        QTextEdit* t_Edit = new QTextEdit();
        t_Edit->setReadOnly(true);
        mEditLayout->addWidget(lbl_FileName);
        mEditLayout->addWidget(t_Edit);

        QVBoxLayout* mSecondEditLayout = new QVBoxLayout();
        mSecondEditLayout->setSpacing(5);
        mSecondEditLayout->setContentsMargins(0,0,0,0);
        QLabel* lbl_FileName1 = new QLabel();
        lbl_FileName1->setStyleSheet("font: 10pt;");
        lbl_FileName1->setText("C:\\PACnc\\User data\\PAIOCfg.out");
        QTextEdit* t_Second_Edit = new QTextEdit();
        t_Second_Edit->setReadOnly(true);
        mSecondEditLayout->addWidget(lbl_FileName1);
        mSecondEditLayout->addWidget(t_Second_Edit);

        QVBoxLayout* mThirdEditLayout = new QVBoxLayout();
        mThirdEditLayout->setSpacing(5);
        mThirdEditLayout->setContentsMargins(0,0,0,0);
        QLabel* lbl_FileName2 = new QLabel();
        lbl_FileName2->setStyleSheet("font: 10pt;");
        lbl_FileName2->setText("C:\\PACnc\\User data\\DriveCfg.ini");
        QTextEdit* t_Third_Edit = new QTextEdit();
        t_Third_Edit->setReadOnly(true);
        mThirdEditLayout->addWidget(lbl_FileName2);
        mThirdEditLayout->addWidget(t_Third_Edit);

        mBox_Layout->addLayout(mEditLayout);
        mBox_Layout->addLayout(mSecondEditLayout);
        mBox_Layout->addLayout(mThirdEditLayout);
        mBox->setLayout(mBox_Layout);

        mLayout->addWidget(mBox);
        mWidget->setLayout(mLayout);

        Widget = mWidget;

        QFile FileFirst("C:\\PACnc\\User data\\PAIOCfg.ini");
        if(FileFirst.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QTextStream in(&FileFirst);
            while(!in.atEnd())
            {
                 t_Edit->append(in.readLine());
            }
        }
        QFile FileSecond("C:\\PACnc\\User data\\PAIOCfg.out");
        if(FileSecond.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QTextStream in(&FileSecond);
            while(!in.atEnd())
            {
                 t_Second_Edit->append(in.readLine());
            }
        }
        QFile ThirdFirst("C:\\PACnc\\User data\\DriveCfg.ini");
        if(ThirdFirst.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QTextStream in(&ThirdFirst);
            while(!in.atEnd())
            {
                 t_Third_Edit->append(in.readLine());
            }
        }
        break;
    }
    case MachineSetPage:
    {
        const QString btn_Cnc_Parameter_Style = Public_Str::Get_Sty(Style_Css{SettingButton,{}});

        QWidget* mWidget = new QWidget();
        QVBoxLayout* mLayout = new QVBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(2,2,2,2);

        QGroupBox* Box = new QGroupBox();
        Box->setTitle("SET");
        QVBoxLayout* BoxLayout = new QVBoxLayout();
        BoxLayout->setSpacing(0);
        BoxLayout->setContentsMargins(20,20,20,20);

        QHBoxLayout* Top = new QHBoxLayout();
        Top->setSpacing(0);
        Top->setContentsMargins(0,0,0,0);

        //机床设置
        QGroupBox* ManBox = new QGroupBox();
        ManBox->setFixedSize(300,400);
        ManBox->setTitle("机床参数");
        ManBox->setAlignment(Qt::AlignCenter);
        QVBoxLayout* ManBoxLayout = new QVBoxLayout();
        ManBoxLayout->setSpacing(0);
        ManBoxLayout->setContentsMargins(0,0,0,0);
        QList<SettingType> typeList;
        typeList << Settingini1 << Settingini2 << Settingini3 << Settingini4 << Settingini5 << Settingini6 << Settingini7 << Settingini8
                 << Settingini9 << Settingini10 << Settingini11 << Settingini12 << Settingini13 << Settingini14 <<Settingini15 << Settingini16
                 << Settingini17 << Settingini18 << Settingini19 << Settingini20;
        for(int i = 0; i < 10; i++)
        {
            QList<QVariant> List = Setting_Data::Get()->Get_SettingData(typeList.at(i));
            QHBoxLayout* LabelLayout = new QHBoxLayout();
            LabelLayout->setSpacing(0);
            LabelLayout->setContentsMargins(0,0,0,0);
            QLabel* lbl_Name = Public_Control::Get_Label(List.at(0).toString());

            QDoubleSpinBox* DouleSpinbox = new QDoubleSpinBox();
            DouleSpinbox->setObjectName(QString("Doublebox%1").arg(List.at(2).toString()));
            DouleSpinbox->setValue(List.at(3).toDouble());
            void (QDoubleSpinBox::*DoubleSpinChange)(double) = &QDoubleSpinBox::valueChanged;
            this->connect(DouleSpinbox,DoubleSpinChange,this,[=](double d){
                Setting_Data::Get()->SettingValue(typeList.at(i),d);
            });

            QLabel* lbl_Unit = Public_Control::Get_Label(List.at(1).toString());
            LabelLayout->addWidget(lbl_Name);
            LabelLayout->addWidget(DouleSpinbox);
            LabelLayout->addWidget(lbl_Unit);
            ManBoxLayout->addLayout(LabelLayout);
        }
        ManBox->setLayout(ManBoxLayout);

        //机床参数2
        QGroupBox* ManBox1 = new QGroupBox();
        ManBox1->setFixedSize(300,400);
        ManBox1->setTitle("机床设置2");
        ManBox1->setAlignment(Qt::AlignCenter);
        QVBoxLayout* ManBoxLayout1 = new QVBoxLayout();
        ManBoxLayout1->setSpacing(0);
        ManBoxLayout1->setContentsMargins(0,0,0,0);

        for(int i = 0; i < 10 ; i++)
        {
            QList<QVariant> List = Setting_Data::Get()->Get_SettingData(typeList.at(i + 10));
            QHBoxLayout* LabelLayout = new QHBoxLayout();
            LabelLayout->setSpacing(0);
            LabelLayout->setContentsMargins(0,0,0,0);
            QLabel* lbl_Name = Public_Control::Get_Label(List.at(0).toString());

            QDoubleSpinBox* DouleSpinbox = new QDoubleSpinBox();
            DouleSpinbox->setValue(List.at(3).toDouble());
            DouleSpinbox->setObjectName(QString("Doublebox%1").arg(List.at(2).toString()));
            void (QDoubleSpinBox::*DoubleSpinChange)(double) = &QDoubleSpinBox::valueChanged;
            this->connect(DouleSpinbox,DoubleSpinChange,this,[=](double d){
                Setting_Data::Get()->SettingValue(typeList.at(i + 10),d);
            });

            QLabel* lbl_Unit = Public_Control::Get_Label(List.at(1).toString());
            LabelLayout->addWidget(lbl_Name);
            LabelLayout->addWidget(DouleSpinbox);
            LabelLayout->addWidget(lbl_Unit);
            ManBoxLayout1->addLayout(LabelLayout);
        }
        ManBox1->setLayout(ManBoxLayout1);

        //尾部
        QWidget* TopLastWidget = new QWidget();
        TopLastWidget->setFixedSize(150,400);
        QVBoxLayout* TopLast = new QVBoxLayout();
        TopLast->setSpacing(0);
        TopLast->setContentsMargins(0,0,0,0);

        //参数
        QGroupBox* ValBox = new QGroupBox();
        ValBox->setFixedSize(150,100);
        ValBox->setTitle("参数");
        QHBoxLayout* ValBoxLayout = new QHBoxLayout();
        ValBoxLayout->setSpacing(0);
        ValBoxLayout->setContentsMargins(0,0,0,0);
        QPushButton* btn_Val = Public_Control::Get_Button("CNC参数","",130,40,btn_Cnc_Parameter_Style);
        ValBoxLayout->addWidget(btn_Val);
        ValBox->setLayout(ValBoxLayout);

        //监控
        QGroupBox* MonitoringBox = new QGroupBox();
        MonitoringBox->setTitle("监控");
        QVBoxLayout* MonitoringLayout = new QVBoxLayout();
        MonitoringLayout->setSpacing(0);
        MonitoringLayout->setContentsMargins(10,0,0,0);

        QPushButton* btn_CuttingHead = Public_Control::Get_Button("切割头","",130,40,btn_Cnc_Parameter_Style);
        QPushButton* btn_Block1 = Public_Control::Get_Button("调高器1","",130,40,btn_Cnc_Parameter_Style);
        QPushButton* btn_Block2 = Public_Control::Get_Button("调高器2","",130,40,btn_Cnc_Parameter_Style);
        QPushButton* btn_Laser = Public_Control::Get_Button("激光器","",130,40,btn_Cnc_Parameter_Style);

        MonitoringLayout->addWidget(btn_CuttingHead);
        MonitoringLayout->addWidget(btn_Block1);
        MonitoringLayout->addWidget(btn_Block2);
        MonitoringLayout->addWidget(btn_Laser);
        MonitoringBox->setLayout(MonitoringLayout);

        //配置
        QHBoxLayout* buttonConfiguartionLayout = new QHBoxLayout();
        buttonConfiguartionLayout->setSpacing(0);
        buttonConfiguartionLayout->setContentsMargins(0,0,0,0);
        QPushButton* btn_Configuration = Public_Control::Get_Button("配置","",130,40,btn_Cnc_Parameter_Style);
        buttonConfiguartionLayout->addWidget(btn_Configuration);

        TopLast->addWidget(ValBox);
        TopLast->addWidget(MonitoringBox);
        TopLast->addLayout(buttonConfiguartionLayout);
        TopLastWidget->setLayout(TopLast);

        Top->addWidget(ManBox);
        Top->addWidget(ManBox1);
        Top->addWidget(TopLastWidget);
        Top->addStretch();

        QVBoxLayout* BottomLast = new QVBoxLayout();
        BottomLast->setSpacing(30);
        BottomLast->setContentsMargins(0,30,0,0);
        //确定
        QPushButton* btn_Sure = Public_Control::Get_Button("确定","",130,40,btn_Cnc_Parameter_Style);

        QHBoxLayout* mAxLayout = new QHBoxLayout();
        mAxLayout->setSpacing(20);
        mAxLayout->setContentsMargins(0,0,0,0);
        QPushButton* btn_AxInit = Public_Control::Get_Button("龙门轴初始化","",130,40,btn_Cnc_Parameter_Style);

        QWidget* AxInitWidget = new QWidget();
        AxInitWidget->hide();
        AxInitWidget->setFixedSize(200,40);
        QHBoxLayout* AxInitLayout = new QHBoxLayout();
        AxInitLayout->setSpacing(0);
        AxInitLayout->setContentsMargins(0,0,0,0);
        const QString btn_Style = "background-color: rgb(150, 150, 150);";
        QPushButton* btn_X = Public_Control::Get_Button("X","",0,40,btn_Style);
        QPushButton* btn_Y = Public_Control::Get_Button("Y","",0,40,btn_Style);
        QPushButton* btn_Z = Public_Control::Get_Button("Z","",0,40,btn_Style);
        QPushButton* btn_A = Public_Control::Get_Button("A","",0,40,btn_Style);
        QPushButton* btn_C = Public_Control::Get_Button("C","",0,40,btn_Style);
        QPushButton* btn_L = Public_Control::Get_Button("P","",0,40,btn_Style);
        AxInitLayout->addWidget(btn_X);
        AxInitLayout->addWidget(btn_Y);
        AxInitLayout->addWidget(btn_Z);
        AxInitLayout->addWidget(btn_A);
        AxInitLayout->addWidget(btn_C);
        AxInitLayout->addWidget(btn_L);
        AxInitWidget->setLayout(AxInitLayout);

        mAxLayout->addWidget(btn_AxInit);
        mAxLayout->addWidget(AxInitWidget);
        mAxLayout->addStretch();

        BottomLast->addWidget(btn_Sure);
        BottomLast->addLayout(mAxLayout);

        BoxLayout->addLayout(Top);
        BoxLayout->addLayout(BottomLast);
        BoxLayout->addStretch();
        Box->setLayout(BoxLayout);

        mLayout->addWidget(Box);
        mWidget->setLayout(mLayout);

        Widget = mWidget;

        QString PLCPVar = "";
        QStringList msg = Setting_Data::Get()->Get_AllP();
        for(int i = 0; i < msg.size(); i++)
        {
            PLCPVar += msg.at(i) + ",";
        }
        PLCPVar = PLCPVar.left(PLCPVar.length() - 1);
        RunTcp::Get()->Write(QString("<getp><par>%1</par></getp>").arg(PLCPVar));

        this->connect(RunTcp::Get(),&RunTcp::Set_SetP_Signal,this,[=](QStringList n,QStringList v){
           QList<QDoubleSpinBox*> douList = ManBox->findChildren<QDoubleSpinBox*>();
           QList<QDoubleSpinBox*> dou1List = ManBox1->findChildren<QDoubleSpinBox*>();
           for(int i = 0; i < douList.size(); i++)
           {
               QString Sindex = dou1List.at(i)->objectName().split("P").last();
               int index = Sindex.toInt();
               for(int Count = 0; Count < n.size(); Count++)
               {
                   if(n.at(Count).toInt() == index)
                   {
                       douList.at(i)->setValue(v.at(Count).toDouble());
                       continue;
                   }
               }
           }
        });

        this->connect(RunTcp::Get(),&RunTcp::Set_SetNcda_Signal,this,[=](QStringList List){
            QStringList msg;
            msg << "" << "";
            for(int i = 0; i < List.size(); i++)
            {
                if(List.at(i).split("_").first() == "gini")
                {
                    msg[0] = List.at(i).split("_").last();
                }
                else if(List.at(i).split("_").first() == "raxes")
                {
                    msg[1] = List.at(i).split("_").last();
                }
            }
            if(!msg.at(0).isEmpty())
            {
                if(msg.at(0).toInt() == 1)
                {
//                    if(bMainStack==5)
//                    RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>off</ax1><ax2>off</ax2><ax3>off</ax3><ax4>off</ax4><ax5>off</ax5><ax6>off</ax6></selax>");
                    AxInitWidget->setVisible(true);
                    ginit_checked=true;
                    btn_Configuration->setStyleSheet("background-color:rgb(14, 114, 198);color:rgb(230,230,230);");
                }
                else
                {
//                    if(bMainStack==5)
//                    RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>off</ax1><ax2>off</ax2><ax3>off</ax3><ax4>off</ax4><ax5>off</ax5><ax6>off</ax6></selax>");
                    AxInitWidget->setVisible(false);
                    ginit_checked=false;
                    btn_Configuration->setStyleSheet("background-color:rgb(100, 100, 100);color:rgb(230,230,230);");
                }
            }
            if(!msg.at(1).isEmpty())
            {
                if(ginit_checked)
                {
                    QString qsval = msg.at(1);
                    if(qsval=="1")
                    {
                        btn_X->setStyleSheet("background-color: rgb(14, 114, 198);");
                        btn_Y->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Z->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_A->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_C->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_L->setStyleSheet("background-color: rgb(150, 150, 150);");
                    }
                    else if(qsval=="2")
                    {
                        btn_X->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Y->setStyleSheet("background-color: rgb(14, 114, 198);");
                        btn_Z->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_A->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_C->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_L->setStyleSheet("background-color: rgb(150, 150, 150);");
                    }
                    else if(qsval=="4")
                    {
                        btn_X->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Y->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Z->setStyleSheet("background-color: rgb(14, 114, 198);");
                        btn_A->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_C->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_L->setStyleSheet("background-color: rgb(150, 150, 150);");
                    }
                    else if(qsval=="8")
                    {
                        btn_X->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Y->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Z->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_A->setStyleSheet("background-color: rgb(14, 114, 198);");
                        btn_C->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_L->setStyleSheet("background-color: rgb(150, 150, 150);");
                    }
                    else if(qsval=="16")
                    {
                        btn_X->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Y->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Z->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_A->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_C->setStyleSheet("background-color: rgb(14, 114, 198);");
                        btn_L->setStyleSheet("background-color: rgb(150, 150, 150);");
                    }
                    else if(qsval=="32")
                    {
                        btn_X->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Y->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_Z->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_A->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_C->setStyleSheet("background-color: rgb(150, 150, 150);");
                        btn_L->setStyleSheet("background-color: rgb(14, 114, 198);");
                    }
                }
            }
        });
        this->connect(RunTcp::Get(),&RunTcp::Set_Name_Signal,this,[=](QStringList msg){
            ginit_checked=false;
            btn_X->setVisible(false);
            btn_Y->setVisible(false);
            btn_Z->setVisible(false);
            btn_A->setVisible(false);
            btn_C->setVisible(false);
            btn_L->setVisible(false);
            if(!msg.at(0).isEmpty())
            {
                btn_X->setVisible(true);
            }
            if(!msg.at(1).isEmpty())
            {
                btn_Y->setVisible(true);
            }
            if(!msg.at(2).isEmpty())
            {
                btn_Z->setVisible(true);
            }
            if(!msg.at(3).isEmpty())
            {
                btn_A->setVisible(true);
            }
            if(!msg.at(4).isEmpty())
            {
                btn_C->setVisible(true);
            }
            if(!msg.at(5).isEmpty())
            {
                btn_L->setVisible(true);
            }
            btn_X->setText(msg.at(0));
            btn_Y->setText(msg.at(1));
            btn_Z->setText(msg.at(2));
            btn_A->setText(msg.at(3));
            btn_C->setText(msg.at(4));
            btn_L->setText(msg.at(5));
        });
        this->connect(RunTcp::Get(),&RunTcp::Set_Appl2_37Signal,this,[=](QStringList msg){
            List37 = msg;
            if(List38.size() > 0)
            {
                emit UpdateAX();
            }
        });
        this->connect(RunTcp::Get(),&RunTcp::Set_Appl2_38Signal,this,[=](QStringList msg){
            List38 = msg;
            if(List37.size() > 0)
            {
                emit UpdateAX();
            }
        });
        this->connect(this,&DB_Hmi_Gui_Setting::UpdateAX,this,[=](){
            btn_X->setEnabled(false);
            btn_Y->setEnabled(false);
            btn_Z->setEnabled(false);
            btn_A->setEnabled(false);
            btn_C->setEnabled(false);
            btn_L->setEnabled(false);
            if(List38.at(0).toInt() != 0)
            {
                if(List37.at(0) =="0")
                    btn_X->setEnabled(true);
                if(List37.at(0)=="1")
                    btn_Y->setEnabled(true);
                if(List37.at(0)=="2")
                    btn_Z->setEnabled(true);
                if(List37.at(0)=="3")
                    btn_A->setEnabled(true);
                if(List37.at(0)=="4")
                    btn_C->setEnabled(true);
                if(List37.at(0)=="5")
                    btn_L->setEnabled(true);
            }
            if(List38.at(1).toInt() != 0)
            {
                if(List37.at(0)=="0")
                    btn_X->setEnabled(true);
                if(List37.at(1)=="1")
                    btn_Y->setEnabled(true);
                if(List37.at(1)=="2")
                    btn_Z->setEnabled(true);
                if(List37.at(1)=="3")
                    btn_A->setEnabled(true);
                if(List37.at(1)=="4")
                    btn_C->setEnabled(true);
                if(List37.at(1)=="5")
                    btn_L->setEnabled(true);
            }
            if(List38.at(2).toInt() != 0)
            {
                if(List37.at(2)=="0")
                    btn_X->setEnabled(true);
                if(List37.at(2)=="1")
                    btn_Y->setEnabled(true);
                if(List37.at(2)=="2")
                    btn_Z->setEnabled(true);
                if(List37.at(2)=="3")
                    btn_A->setEnabled(true);
                if(List37.at(2)=="4")
                    btn_C->setEnabled(true);
                if(List37.at(2)=="5")
                    btn_L->setEnabled(true);
            }
            if(List38.at(3).toInt() != 0)
            {
                if(List37.at(3)=="0")
                    btn_X->setEnabled(true);
                if(List37.at(3)=="1")
                    btn_Y->setEnabled(true);
                if(List37.at(3)=="2")
                    btn_Z->setEnabled(true);
                if(List37.at(3)=="3")
                    btn_A->setEnabled(true);
                if(List37.at(3)=="4")
                    btn_C->setEnabled(true);
                if(List37.at(3)=="5")
                    btn_L->setEnabled(true);
            }
        });

        this->connect(btn_Configuration,&QPushButton::clicked,this,[=](){
            DB_Hmi_Gui_Setting_Conf* conf = new DB_Hmi_Gui_Setting_Conf();
            conf->show();
        });
        this->connect(btn_CuttingHead,&QPushButton::clicked,this,[=](){
            QSettings m_getdata(mIniDbHmi, QSettings::IniFormat);
            m_getdata.setIniCodec(QTextCodec::codecForName("GB2312"));
            QString exe_filepath=m_getdata.value("/filepath/exe2/").toString();

            QProcess *Process=new QProcess;
            Process->start(exe_filepath,QStringList(exe_filepath));//带空格。能够启动
        });
        this->connect(btn_Block1,&QPushButton::clicked,this,[=](){
            QSettings m_getdata(mIniDbHmi, QSettings::IniFormat);
            m_getdata.setIniCodec(QTextCodec::codecForName("GB2312"));
            QString exe_filepath=m_getdata.value("/filepath/exe3/").toString();

            QProcess *Process=new QProcess;
            Process->start(exe_filepath,QStringList(exe_filepath));//带空格。能够启动
        });
        this->connect(btn_Block2,&QPushButton::clicked,this,[=](){
            QSettings m_getdata(mIniDbHmi, QSettings::IniFormat);
            m_getdata.setIniCodec(QTextCodec::codecForName("GB2312"));
            QString exe_filepath=m_getdata.value("/filepath/exe4/").toString();

            QProcess *Process=new QProcess;
            Process->start(exe_filepath,QStringList(exe_filepath));//带空格。能够启动
        });
        this->connect(btn_Laser,&QPushButton::clicked,this,[=](){
            QSettings m_getdata(mIniDbHmi, QSettings::IniFormat);
            m_getdata.setIniCodec(QTextCodec::codecForName("GB2312"));
            QString exe_filepath=m_getdata.value("/filepath/exe5/").toString();

            QProcess *Process=new QProcess;
            Process->start(exe_filepath,QStringList(exe_filepath));//带空格。能够启动
        });
        this->connect(btn_X,&QPushButton::clicked,this,[=](){
            RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>on</ax1><ax2>off"
                                 "</ax2><ax3>off</ax3><ax4>off</ax4><ax5>off</ax5><ax6>off</ax6></selax>");});
        this->connect(btn_Y,&QPushButton::clicked,this,[=](){
            RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>off</ax1><ax2>on"
                                 "</ax2><ax3>off</ax3><ax4>off</ax4><ax5>off</ax5><ax6>off</ax6></selax>");
        });
        this->connect(btn_A,&QPushButton::clicked,this,[=](){
            RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>off</ax1><ax2>off"
                                 "</ax2><ax3>on</ax3><ax4>off</ax4><ax5>off</ax5><ax6>off</ax6></selax>");
        });
        this->connect(btn_Z,&QPushButton::clicked,this,[=](){
            RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>off</ax1><ax2>off"
                                 "</ax2><ax3>off</ax3><ax4>on</ax4><ax5>off</ax5><ax6>off</ax6></selax>");
        });
        this->connect(btn_C,&QPushButton::clicked,this,[=](){
            RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>off</ax1><ax2>off"
                                 "</ax2><ax3>off</ax3><ax4>off</ax4><ax5>on</ax5><ax6>off</ax6></selax>");
        });
        this->connect(btn_L,&QPushButton::clicked,this,[=](){
            RunTcp::Get()->Write("<selax><req>yes</req><st>nc1</st><sub>ref</sub><ax1>off</ax1><ax2>off"
                                 "</ax2><ax3>off</ax3><ax4>off</ax4><ax5>off</ax5><ax6>on</ax6></selax>");
        });
        this->connect(btn_Sure,&QPushButton::clicked,this,[=](){
            QStringList PList = Setting_Data::Get()->Get_AllP();
            QList<QVariant> ValueList = Setting_Data::Get()->Get_AllValue();
            QString SendP;
            QString SendValue;
            for(int i = 0; i < PList.size(); i++)
            {
                SendP += PList.at(i) + ",";
            }
            for(int i = 0; i < ValueList.size(); i++)
            {
                SendValue += ValueList.at(i).toString() + ",";
            }
            SendP = SendP.left(SendP.length() - 1);
            SendValue = SendValue.left(SendValue.length() - 1);
            RunTcp::Get()->Write(QString("<setp><par>%1</par><val>%2</val></setp>")
                                 .arg(SendP).arg(SendValue));
        });
        this->connect(btn_AxInit,&QPushButton::clicked,this,[=](){
            if(ginit_checked)
            {
                RunTcp::Get()->Write("<switch><sub>ginit</sub><sw>0</sw></switch>");
                AxInitWidget->setVisible(false);
            }
            else
            {
                RunTcp::Get()->Write("<switch><sub>ginit</sub><sw>1</sw></switch>");
                AxInitWidget->setVisible(true);
            }
            btn_X->setStyleSheet("background-color: rgb(150, 150, 150);");
            btn_Y->setStyleSheet("background-color: rgb(150, 150, 150);");
            btn_Z->setStyleSheet("background-color: rgb(150, 150, 150);");
            btn_A->setStyleSheet("background-color: rgb(150, 150, 150);");
            btn_C->setStyleSheet("background-color: rgb(150, 150, 150);");
            btn_L->setStyleSheet("background-color: rgb(150, 150, 150);");
        });
        break;

    }
    }
    return Widget;
}
