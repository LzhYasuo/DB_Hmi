#include "DB_Hmi_Gui_Data.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QScrollArea>
#include <QDebug>
#include <QTextCodec>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QCheckBox>

#include "Public/Public_Function.h"
#include <Public/Public_Control.h>
#include <Public/Public_Str.h>
#include "DB_Hmi_Gui_Data_AddLine.h"
#include "DB_Hmi_Gui_Data_SubLine.h"
#include "DB_Hmi_Gui_NumKeyBoard.h"
#include "../Ini_Dbdata/DataDbdata.h"
#include "../Ini_Dbdata/DataSetting.h"
#include "../Socket/RunTcp.h"

DB_Hmi_Gui_Data::DB_Hmi_Gui_Data(QWidget* parent)
    :QWidget (parent)
{
    IniData = new Data_Setting();
    DbData = new DataDbdata();
    Key = new DB_Hmi_Gui_Numkeyboard(this);

    this->connect(this,&DB_Hmi_Gui_Data::AsSaveFile,Data_SettingDbData::Get(),&Data_SettingDbData::DB_File_SaveAS);
    this->connect(this,&DB_Hmi_Gui_Data::GuiDataWriteintoDB,Data_SettingDbData::Get(),&Data_SettingDbData::DB_Write_into);
    this->connect(this,&DB_Hmi_Gui_Data::GuiDataWriteintoCNCPLC,Data_SettingDbData::Get(),&Data_SettingDbData::DB_Send_CncPlc);
    mAddLine = new DB_Hmi_Gui_Data_AddLine();
    this->connect(mAddLine,&DB_Hmi_Gui_Data_AddLine::Add_Line_Data,Data_SettingDbData::Get(),&Data_SettingDbData::Ini_Write_into);
    mSubLine = new DB_Hmi_Gui_Data_SubLine(Data_SettingDbData::Get()->Get_CuttingListText());
    this->connect(mSubLine,&DB_Hmi_Gui_Data_SubLine::Sub_Line_Data,Data_SettingDbData::Get(),&Data_SettingDbData::Ini_Delete_into);
    this->init();

}

DB_Hmi_Gui_Data::~DB_Hmi_Gui_Data()
{
    IniData->deleteLater();
    DbData->deleteLater();
}

//bool DB_Hmi_Gui_Data::eventFilter(QObject *obj, QEvent *event)
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
//}


void DB_Hmi_Gui_Data::init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = InitWidget();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget* DB_Hmi_Gui_Data::InitWidget()
{
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(5,0,5,0);

    const QString TitleStyle = Public_Str::Get_Sty(Style_Css{DataTitleStyle,{}});

    //顶部
    QHBoxLayout* SwitchButtonLabelLayout = new QHBoxLayout();
    SwitchButtonLabelLayout->setSpacing(0);
    SwitchButtonLabelLayout->setContentsMargins(0,0,0,0);
    //全局设置
    QPushButton* btn_GlobalSwitch = Public_Control::Get_Button("全局设置");
    //切割设置
    QPushButton* btn_CuttingSwitch = Public_Control::Get_Button("切割设置");
    //穿孔设置
    QPushButton* btn_PerforatedSwitch = Public_Control::Get_Button("穿孔设置");
    //文件路径
    QLabel* lbl_File_Path = Public_Control::Get_Label("D\\DBase\\Dbase.db","",TitleStyle);
    //增加行按钮
    QPushButton* btn_AddLine = Public_Control::Get_Button("增加行");
    //删除行按钮
    QPushButton* btn_SubLine = Public_Control::Get_Button("删除行");

    btn_GlobalSwitch->setFixedSize(100,35);
    btn_CuttingSwitch->setFixedSize(100,35);
    btn_PerforatedSwitch->setFixedSize(100,35);
    lbl_File_Path->setFixedSize(500,35);
    btn_AddLine->setFixedSize(100,35);
    btn_SubLine->setFixedSize(100,35);

    btn_AddLine->setEnabled(false);
    btn_SubLine->setEnabled(false);

    SwitchButtonLabelLayout->addWidget(btn_GlobalSwitch);
    SwitchButtonLabelLayout->addWidget(btn_CuttingSwitch);
    SwitchButtonLabelLayout->addWidget(btn_PerforatedSwitch);
    SwitchButtonLabelLayout->addSpacing(50);
    SwitchButtonLabelLayout->addWidget(lbl_File_Path);
    SwitchButtonLabelLayout->addStretch();
    SwitchButtonLabelLayout->addWidget(btn_AddLine);
    SwitchButtonLabelLayout->addWidget(btn_SubLine);

    //中部
    QGroupBox* mMidGroup = new QGroupBox();
    mMidGroup->setObjectName("mMidGroup");
    mMidGroup->setStyleSheet("#mMidGroup{background-color:rgb(255,255,255);}");
    QHBoxLayout* mMidLayout = new QHBoxLayout();
    mMidLayout->setSpacing(0);
    mMidLayout->setContentsMargins(0,0,0,0);

    QStackedWidget* mSWidget = new QStackedWidget();
    QWidget* GlobalWidget = SetSwitchWidget(GlobalWidgetType);
    QWidget* CuttingWidget = SetSwitchWidget(CuttingWidgetType);
    QWidget* PerforatedWidget = SetSwitchWidget(PerforatedWidgetType);
    mSWidget->addWidget(GlobalWidget);
    mSWidget->addWidget(CuttingWidget);
    mSWidget->addWidget(PerforatedWidget);

    mMidLayout->addWidget(mSWidget);
    mMidGroup->setLayout(mMidLayout);

    //底部
    QHBoxLayout* FileButtonLayout = new QHBoxLayout();
    FileButtonLayout->setSpacing(0);
    FileButtonLayout->setContentsMargins(0,0,0,0);

    //打开文件
    QPushButton* btn_OpenFile = Public_Control::Get_ButtonIconSize("打开文件",":/Icon/Img/Icon/Openfile.png",0,0,20,20);
    //另存为
    QPushButton* btn_asSaveFile = Public_Control::Get_ButtonIconSize("另存为",":/Icon/Img/Icon/SaveAs.png",0,0,20,20);
    //写入
    QPushButton* btn_WriteFile = Public_Control::Get_ButtonIconSize("写入",":/Icon/Img/Icon/OK.png",0,0,20,20);
    //保存
    QPushButton* btn_SaveFile = Public_Control::Get_ButtonIconSize("保存",":/Icon/Img/Icon/save.png",0,0,20,20);

    btn_OpenFile->setFixedSize(80,30);
    btn_asSaveFile->setFixedSize(80,30);
    btn_WriteFile->setFixedSize(80,30);
    btn_SaveFile->setFixedSize(80,30);

    FileButtonLayout->addStretch();
    FileButtonLayout->addWidget(btn_OpenFile);
    FileButtonLayout->addWidget(btn_asSaveFile);
    FileButtonLayout->addWidget(btn_WriteFile);
    FileButtonLayout->addWidget(btn_SaveFile);

    mLayout->addLayout(SwitchButtonLabelLayout);
    mLayout->addWidget(mMidGroup);
    mLayout->addLayout(FileButtonLayout);

    mWidget->setLayout(mLayout);

    this->connect(btn_AddLine,&QPushButton::clicked,this,[=]()
    {
        bool reply = mAddLine->exec();
        if(reply == 0)
        {
            mAddLine->Clear();
        }
        else if(reply == 1)
        {
            mAddLine->Clear();
        }

    });
    this->connect(btn_SubLine,&QPushButton::clicked,this,[=]()
    {
        bool reply = mSubLine->exec();
        if(reply == 0)
        {

        }
        else if(reply == 1)
        {

        }
    });
    this->connect(btn_GlobalSwitch,&QPushButton::clicked,this,[=]()
    {
        btn_AddLine->setEnabled(false);
        btn_SubLine->setEnabled(false);
        mSWidget->setCurrentIndex(0);
    });
    this->connect(btn_CuttingSwitch,&QPushButton::clicked,this,[=]()
    {
        mSWidget->setCurrentIndex(1);
        btn_AddLine->setEnabled(true);
        btn_SubLine->setEnabled(true);
    });
    this->connect(btn_PerforatedSwitch,&QPushButton::clicked,this,[=]()
    {
        btn_AddLine->setEnabled(false);
        btn_SubLine->setEnabled(false);
        mSWidget->setCurrentIndex(2);
    });
    this->connect(btn_OpenFile,&QPushButton::clicked,this,[=](){
        QString str = QFileDialog::getOpenFileName(this,"OpenDBFile","D:\\DBASE\\","database_file(*.db);;Allfile(*.*)");
        if(str.isEmpty())
        {
            QMessageBox::warning(this,"打开文件失败","Orz打开文件失败咯");
            return;
        }
        if(DbData->OpenFileName(str))
            lbl_File_Path->setText(str);
    });
    this->connect(btn_asSaveFile,&QPushButton::clicked,this,[=](){
        QString str = QFileDialog::getSaveFileName(this,"OpenDBFile","D:\\DBASE\\","database_file(*.db);");
        if(str.isEmpty())
        {
            QMessageBox::warning(this,"打开文件失败","Orz打开文件失败咯");
            return;
        }
        emit AsSaveFile(str);
        //Public_Function::copyFile();
//        QFile mDataFile(QString("%1.db").arg(str));
//        bool ok = mDataFile.open(QIODevice::WriteOnly);
//        if(!ok)
//        {
//            QMessageBox::information(nullptr,"提示","创建文件失败咯！！");
//            return;
//        }
    });
    this->connect(btn_SaveFile,&QPushButton::clicked,this,[=](){
        emit GuiDataWriteintoDB();
    });
    this->connect(btn_WriteFile,&QPushButton::clicked,this,[=](){
        QStringList GlobalStrList = Data_SettingDbData::Get()->Get_GlobalPList();
        QVariantList GlobalValueList = Data_SettingDbData::Get()->Get_GlobalValueList();

        QStringList CuttingStrList = Data_SettingDbData::Get()->Get_CuttingListP();
        QVariantList CuttingValueList = Data_SettingDbData::Get()->Get_CuttingListValue();

        QStringList PerforatedStrList = Data_SettingDbData::Get()->Get_PerforatedPList();
        QVariantList PerforatedValueList = Data_SettingDbData::Get()->Get_PerforatedValueList();

        if(GlobalStrList.size() != GlobalValueList.size())
        {
            qDebug() << "参数不对等！";
            return;
        }
        if(PerforatedStrList.size() != PerforatedValueList.size())
        {
            qDebug() << "参数不对等！";
            return;
        }
        if(CuttingStrList.size() != CuttingValueList.size())
        {
            qDebug() << "参数不对等！";
            return;
        }
        //全局参数发送
        QString P;
        QString Value;
        for(int i = 0; i < GlobalStrList.size(); i++)
        {
            P += GlobalStrList.at(i) + ",";
            Value += GlobalValueList.at(i).toString() + ",";
        }
        P = P.left(P.length() - 1);
        Value = Value.left(Value.length() - 1);
        RunTcp::Get()->Write(QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value));
//        qDebug() << QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value);

        //穿孔参数发送
        P.clear();
        Value.clear();
        for(int i = 0; i < PerforatedStrList.size(); i++)
        {
            P += PerforatedStrList.at(i) + ",";
            Value += PerforatedValueList.at(i).toString() + ",";
        }
        P = P.left(P.length() - 1);
        Value = Value.left(Value.length() - 1);

        RunTcp::Get()->Write(QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value));
//        qDebug() << QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value);

        //切割参数发送
        if(CuttingStrList.size() > 60)
        {
            P.clear();
            Value.clear();
            int Count = 0;
            for(int i = 0; i < CuttingStrList.size(); i++)
            {
                P += CuttingStrList.at(i) + ",";
                Value += CuttingValueList.at(i).toString() + ",";
                Count ++;
                if(i == CuttingStrList.size() - 1)
                {
                    P = P.left(P.length() - 1);
                    Value = Value.left(Value.length() - 1);
                    RunTcp::Get()->Write(QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value));
                    qDebug() << QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value);
                    Count = 0;
                    Value.clear();
                    P.clear();
                    break;
                }
                if(Count >= 60)
                {
                    P = P.left(P.length() - 1);
                    Value = Value.left(Value.length() - 1);
                    RunTcp::Get()->Write(QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value));
                    qDebug() << QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value);
                    Count = 0;
                    Value.clear();
                    P.clear();
                    continue;
                }
            }
        }
        else
        {
            P.clear();
            Value.clear();
            for(int i = 0; i < CuttingStrList.size(); i++)
            {
                P += "P" + CuttingStrList.at(i) + ",";
                Value += CuttingValueList.at(i).toString() + ",";
            }
            P = P.left(P.length() - 1);
            Value = Value.left(Value.length() - 1);

            RunTcp::Get()->Write(QString("<setp><par>%1</par><val>%2</val></setp>").arg(P).arg(Value));
        }
    });
    //this->connect()
    return mWidget;
}

QWidget* DB_Hmi_Gui_Data::SetSwitchWidget(SwitchPageType type)
{
    QWidget* Widget = nullptr;
    switch(type)
    {
    case GlobalWidgetType:
    {
        QList<bool> DataState = Data_SettingDbData::Get()->PopDataState();

        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(5);
        mLayout->setContentsMargins(5,5,5,5);

        //切割设置
        QGroupBox* CuttingGroup = new QGroupBox();
        CuttingGroup->setMinimumWidth(400);
        CuttingGroup->setTitle("切割设置");
        CuttingGroup->setAlignment(Qt::AlignCenter);

        QVBoxLayout* CuttingLayout = new QVBoxLayout();
        CuttingLayout->setSpacing(5);
        CuttingLayout->setContentsMargins(10,10,10,10);

        QHBoxLayout* TopLayout = new QHBoxLayout();
        TopLayout->setSpacing(0);
        TopLayout->setContentsMargins(0,0,0,0);

        //蛙跳
        QGroupBox* leapfrogGroup = new QGroupBox();
        leapfrogGroup->setTitle("蛙跳设置");
        leapfrogGroup->setCheckable(true);
        leapfrogGroup->setChecked(false);
        QVBoxLayout* LeapFoogLayout = new QVBoxLayout();
        LeapFoogLayout->setSpacing(0);
        LeapFoogLayout->setContentsMargins(0,0,0,0);

        QWidget* leapfrogWid1 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType1),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType1),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType1),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType1),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType1),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType1));

        QWidget* leapfrogWid2 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType2),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType2),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType2),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType2),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType2),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType2));

        QWidget* leapfrogWid3 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType3),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType3),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType3),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType3),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType3),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType3));

        QWidget* leapfrogWid4 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType4),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType4),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType4),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType4),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType4),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType4));

        QWidget* leapfrogWid5 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType5),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType5),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType5),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType5),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType5),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType5));

        LeapFoogLayout->addWidget(leapfrogWid1);
        LeapFoogLayout->addWidget(leapfrogWid2);
        LeapFoogLayout->addWidget(leapfrogWid3);
        LeapFoogLayout->addWidget(leapfrogWid4);
        LeapFoogLayout->addWidget(leapfrogWid5);
        leapfrogGroup->setLayout(LeapFoogLayout);


        //返回设置
        QGroupBox* ReturnGroup = new QGroupBox();
        ReturnGroup->setTitle("返回设置");
        ReturnGroup->setFixedHeight(230);
        QVBoxLayout* ReturnLayout = new QVBoxLayout();
        ReturnLayout->setSpacing(0);
        ReturnLayout->setContentsMargins(5,5,5,5);

        QStringList ComboxName = Data_SettingDbData::Get()->Get_GlobalComboxList(iniReturnStr);
        QRadioButton* btn1 = new QRadioButton();
        btn1->setText(ComboxName.at(0));

        QRadioButton* btn2 = new QRadioButton();
        btn2->setText(ComboxName.at(1));

        QRadioButton* btn3 = new QRadioButton();
        btn3->setText(ComboxName.at(2));

        QRadioButton* btn4 = new QRadioButton();
        btn4->setText(ComboxName.at(3));

        int ButtonStare = Data_SettingDbData::Get()->Get_GlobalValue(iniReturnStr).toInt();
        if(ButtonStare == 0)
            btn1->click();
        else if(ButtonStare == 1)
            btn2->click();
        else if(ButtonStare == 2)
            btn3->click();
        else if(ButtonStare == 3)
            btn4->click();

        ReturnLayout->addWidget(btn1);
        ReturnLayout->addWidget(btn2);
        ReturnLayout->addWidget(btn3);
        ReturnLayout->addWidget(btn4);
        ReturnGroup->setLayout(ReturnLayout);

        TopLayout->addWidget(leapfrogGroup);
        TopLayout->addWidget(ReturnGroup);

        //无蛙跳上抬高度
        QGroupBox* NoLeapLenghtGroup = new QGroupBox();
        NoLeapLenghtGroup->setFixedHeight(30);
        QHBoxLayout* NoLeapLenghtLayout = new QHBoxLayout();
        NoLeapLenghtLayout->setSpacing(0);
        NoLeapLenghtLayout->setContentsMargins(0,0,0,0);

        QWidget* NoLeapLenghWidget = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inifrogJump1),
                                                                 Data_SettingDbData::Get()->Get_GlobalUnit(inifrogJump1),
                                                                 2,Data_SettingDbData::Get()->Get_GlobalMax(inifrogJump1),
                                                                 Data_SettingDbData::Get()->Get_GlobalMin(inifrogJump1),
                                                                 Data_SettingDbData::Get()->Get_GlobalDecimal(inifrogJump1),
                                                                 Data_SettingDbData::Get()->Get_GlobalValue(inifrogJump1));
        NoLeapLenghtLayout->addWidget(NoLeapLenghWidget);
        NoLeapLenghtLayout->addStretch();
        NoLeapLenghtGroup->setLayout(NoLeapLenghtLayout);

        //Z轴切割
        QGroupBox* ZCoordCuttingGroup = new QGroupBox();
        ZCoordCuttingGroup->setTitle("[z轴切割](备用)");
        ZCoordCuttingGroup->setFixedHeight(50);
        ZCoordCuttingGroup->setCheckable(true);
        ZCoordCuttingGroup->setChecked(false);
//        ZCoordCuttingGroup->setFixedWidth(750);

        QHBoxLayout* ZCoordCuttingLayout = new QHBoxLayout();
        ZCoordCuttingLayout->setSpacing(10);
        ZCoordCuttingLayout->setContentsMargins(0,0,0,0);

        QLabel* lbl_ZCoordHeight = Public_Control::Get_Label(Data_SettingDbData::Get()->Get_GlobalText(iniFixedHightCutting1));
        QDoubleSpinBox* box = new QDoubleSpinBox();
        box->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniFixedHightCutting1).toInt());
        box->setRange(Data_SettingDbData::Get()->Get_GlobalMin(iniFixedHightCutting1),Data_SettingDbData::Get()->Get_GlobalMax(iniFixedHightCutting1));
        box->setDecimals(Data_SettingDbData::Get()->Get_GlobalDecimal(iniFixedHightCutting1));
        QPushButton* btn_EntryZValue = Public_Control::Get_Button("录入Z值");

        lbl_ZCoordHeight->setFixedWidth(50);
        box->setFixedWidth(100);

        ZCoordCuttingLayout->addWidget(lbl_ZCoordHeight);
        ZCoordCuttingLayout->addWidget(box);
        ZCoordCuttingLayout->addWidget(btn_EntryZValue);
        ZCoordCuttingGroup->setLayout(ZCoordCuttingLayout);

        //送料模式
        QGroupBox* FeedModelGroup = new QGroupBox();
        FeedModelGroup->setTitle("[送料模式]");
        FeedModelGroup->setFixedHeight(200);

        QVBoxLayout* FeedModelLayout = new QVBoxLayout();
        FeedModelLayout->setSpacing(0);
        FeedModelLayout->setContentsMargins(0,0,0,0);

        QWidget* FeedTypeWidget = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniFeeding1),"",3,0,0,0,
                                                              Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding1),QSize(0,0),QSize(0,0),QSize(0,0)
                                                              ,false,Data_SettingDbData::Get()->Get_GlobalComboxList(iniFeeding1));

        QWidget* FeedSpeedWidget = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniFeeding2),Data_SettingDbData::Get()->Get_GlobalUnit(iniFeeding2),
                                                               2,Data_SettingDbData::Get()->Get_GlobalMax(iniFeeding2),Data_SettingDbData::Get()->Get_GlobalMin(iniFeeding2),
                                                               Data_SettingDbData::Get()->Get_GlobalDecimal(iniFeeding2),Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding2));

        QWidget* FeedLenghtWidget = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniFeeding3),Data_SettingDbData::Get()->Get_GlobalUnit(iniFeeding3),
                                                                2,Data_SettingDbData::Get()->Get_GlobalMax(iniFeeding3),Data_SettingDbData::Get()->Get_GlobalMin(iniFeeding3),
                                                                Data_SettingDbData::Get()->Get_GlobalDecimal(iniFeeding3),Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding3));

        QWidget* FeednumWidget = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniFeeding4),Data_SettingDbData::Get()->Get_GlobalUnit(iniFeeding4),
                                                             1,Data_SettingDbData::Get()->Get_GlobalMax(iniFeeding4),Data_SettingDbData::Get()->Get_GlobalMin(iniFeeding4),
                                                             Data_SettingDbData::Get()->Get_GlobalDecimal(iniFeeding4),Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding4));

        FeedModelLayout->addWidget(FeedTypeWidget);
        FeedModelLayout->addWidget(FeedSpeedWidget);
        FeedModelLayout->addWidget(FeedLenghtWidget);
        FeedModelLayout->addWidget(FeednumWidget);
        FeedModelGroup->setLayout(FeedModelLayout);

        CuttingLayout->addLayout(TopLayout);
        CuttingLayout->addWidget(NoLeapLenghtGroup);
        CuttingLayout->addWidget(ZCoordCuttingGroup);
        CuttingLayout->addWidget(FeedModelGroup);
        CuttingLayout->addStretch();
        CuttingGroup->setLayout(CuttingLayout);

        //寻边使能
        QGroupBox* EdgeGroup = new QGroupBox();
        EdgeGroup->setTitle("寻边使能");
        QVBoxLayout* EdgeLayout = new QVBoxLayout();
        EdgeLayout->setSpacing(20);
        EdgeLayout->setContentsMargins(0,0,0,0);

        QWidget* EdgeGroupWid1 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType6),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType6),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType6),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType6),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType6),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType6),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);

        QWidget* EdgeGroupWid2 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType7),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType7),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType7),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType7),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType7),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType7),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);

        QWidget* EdgeGroupWid3 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType8),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType8),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType8),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType8),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType8),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType8),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);

        QWidget* EdgeGroupWid4 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType9),Data_SettingDbData::Get()->Get_GlobalUnit(iniGlobalSettingType9),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(iniGlobalSettingType9),Data_SettingDbData::Get()->Get_GlobalMin(iniGlobalSettingType9),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(iniGlobalSettingType9),Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType9),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);

        QHBoxLayout* EegeGroupBototm = new QHBoxLayout();
        QCheckBox* CBox1 = new QCheckBox();
        CBox1->setFixedWidth(100);
        CBox1->setText(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType10));
        QCheckBox* CBox2 = new QCheckBox();
        CBox2->setFixedWidth(100);
        CBox2->setText(Data_SettingDbData::Get()->Get_GlobalText(iniGlobalSettingType11));
        EegeGroupBototm->addWidget(CBox1);
        EegeGroupBototm->addWidget(CBox2);
        EegeGroupBototm->addStretch();
        EdgeLayout->addWidget(EdgeGroupWid1);
        EdgeLayout->addWidget(EdgeGroupWid2);
        EdgeLayout->addWidget(EdgeGroupWid3);
        EdgeLayout->addWidget(EdgeGroupWid4);
        EdgeLayout->addLayout(EegeGroupBototm);
        EdgeLayout->addStretch();
        EdgeGroup->setLayout(EdgeLayout);

        //默认设置
        QGroupBox* DefaultGroup = new QGroupBox();
        DefaultGroup->setTitle("[默认设置]");
        DefaultGroup->setAlignment(Qt::AlignCenter);
        QVBoxLayout* DefaultLayout = new QVBoxLayout();
        DefaultLayout->setSpacing(0);
        DefaultLayout->setContentsMargins(0,0,0,0);

        QWidget* wid1 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault1),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault1),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(inidefault1),Data_SettingDbData::Get()->Get_GlobalMin(inidefault1),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault1),Data_SettingDbData::Get()->Get_GlobalValue(inidefault1),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid2 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault2),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault2),
                                                    1,Data_SettingDbData::Get()->Get_GlobalMax(inidefault2),Data_SettingDbData::Get()->Get_GlobalMin(inidefault2),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault2),Data_SettingDbData::Get()->Get_GlobalValue(inidefault2),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid3 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault3),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault3),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(inidefault3),Data_SettingDbData::Get()->Get_GlobalMin(inidefault3),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault3),Data_SettingDbData::Get()->Get_GlobalValue(inidefault3),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid4 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault4),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault4),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(inidefault4),Data_SettingDbData::Get()->Get_GlobalMin(inidefault4),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault4),Data_SettingDbData::Get()->Get_GlobalValue(inidefault4),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid5 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault5),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault5),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(inidefault5),Data_SettingDbData::Get()->Get_GlobalMin(inidefault5),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault5),Data_SettingDbData::Get()->Get_GlobalValue(inidefault5),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid6 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault6),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault6),
                                                    1,Data_SettingDbData::Get()->Get_GlobalMax(inidefault6),Data_SettingDbData::Get()->Get_GlobalMin(inidefault6),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault6),Data_SettingDbData::Get()->Get_GlobalValue(inidefault6),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid7 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault7),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault7),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(inidefault7),Data_SettingDbData::Get()->Get_GlobalMin(inidefault7),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault7),Data_SettingDbData::Get()->Get_GlobalValue(inidefault7),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid8 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault8),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault8),
                                                    1,Data_SettingDbData::Get()->Get_GlobalMax(inidefault8),Data_SettingDbData::Get()->Get_GlobalMin(inidefault8),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault8),Data_SettingDbData::Get()->Get_GlobalValue(inidefault8),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);
        QWidget* wid9 = CreateLabelValueLabelWidget(Data_SettingDbData::Get()->Get_GlobalText(inidefault9),Data_SettingDbData::Get()->Get_GlobalUnit(inidefault9),
                                                    2,Data_SettingDbData::Get()->Get_GlobalMax(inidefault9),Data_SettingDbData::Get()->Get_GlobalMin(inidefault9),
                                                    Data_SettingDbData::Get()->Get_GlobalDecimal(inidefault9),Data_SettingDbData::Get()->Get_GlobalValue(inidefault9),
                                                    QSize(100,0),QSize(120,0),QSize(30,0),true);

        DefaultLayout->addWidget(wid1);
        DefaultLayout->addWidget(wid2);
        DefaultLayout->addWidget(wid3);
        DefaultLayout->addWidget(wid4);
        DefaultLayout->addWidget(wid5);
        DefaultLayout->addWidget(wid6);
        DefaultLayout->addWidget(wid7);
        DefaultLayout->addWidget(wid8);
        DefaultLayout->addWidget(wid9);
        DefaultLayout->addStretch();

        DefaultGroup->setLayout(DefaultLayout);

        mLayout->addWidget(CuttingGroup);
        mLayout->addWidget(EdgeGroup);
        mLayout->addWidget(DefaultGroup);
        mWidget->setLayout(mLayout);
        Widget = mWidget;

        if(!DataState.at(0))
            leapfrogGroup->hide();
        if(!DataState.at(1))
            NoLeapLenghtGroup->hide();
        if(!DataState.at(2))
            ZCoordCuttingGroup->hide();
        if(!DataState.at(3))
            EdgeGroup->hide();

        this->connect(btn1,&QRadioButton::clicked,this,[=](){
           Data_SettingDbData::Get()->Set_GlobalValue(iniReturnStr,0);
        });
        this->connect(btn2,&QPushButton::clicked,this,[=](){
           Data_SettingDbData::Get()->Set_GlobalValue(iniReturnStr,1);
        });
        this->connect(btn3,&QRadioButton::clicked,this,[=](){
           Data_SettingDbData::Get()->Set_GlobalValue(iniReturnStr,2);
        });
        this->connect(btn4,&QPushButton::clicked,this,[=](){
           Data_SettingDbData::Get()->Set_GlobalValue(iniReturnStr,3);
        });

        QDoubleSpinBox* NoLeapLenghBox = NoLeapLenghWidget->findChild<QDoubleSpinBox*>("ValueBox");
        QComboBox* FeedTypeBox = FeedTypeWidget->findChild<QComboBox*>("ValueBox");
        QDoubleSpinBox* FeedSpeedBox = FeedSpeedWidget->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* FeedLenghtBox = FeedLenghtWidget->findChild<QDoubleSpinBox*>("ValueBox");
        QSpinBox* FeednumBox = FeednumWidget->findChild<QSpinBox*>("ValueBox");
        QDoubleSpinBox* DefaultBox1 = wid1->findChild<QDoubleSpinBox*>("ValueBox");
        QSpinBox* DefaultBox2 = wid2->findChild<QSpinBox*>("ValueBox");
        QDoubleSpinBox* DefaultBox3 = wid3->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* DefaultBox4 = wid4->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* DefaultBox5 = wid5->findChild<QDoubleSpinBox*>("ValueBox");
        QSpinBox* DefaultBox6 = wid6->findChild<QSpinBox*>("ValueBox");
        QDoubleSpinBox* DefaultBox7 = wid7->findChild<QDoubleSpinBox*>("ValueBox");
        QSpinBox* DefaultBox8 = wid8->findChild<QSpinBox*>("ValueBox");
        QDoubleSpinBox* DefaultBox9 = wid9->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* leapfrogBox1 = leapfrogWid1->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* leapfrogBox2 = leapfrogWid2->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* leapfrogBox3 = leapfrogWid3->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* leapfrogBox4 = leapfrogWid4->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* leapfrogBox5 = leapfrogWid5->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* EdgeGroupBox1 = EdgeGroupWid1->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* EdgeGroupBox2 = EdgeGroupWid2->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* EdgeGroupBox3 = EdgeGroupWid3->findChild<QDoubleSpinBox*>("ValueBox");
        QDoubleSpinBox* EdgeGroupBox4 = EdgeGroupWid4->findChild<QDoubleSpinBox*>("ValueBox");

        void (QDoubleSpinBox::*DoubleSpinChange)(double) = &QDoubleSpinBox::valueChanged;
        void (QSpinBox::*SpinBox)(int) = &QSpinBox::valueChanged;
        void (QComboBox::*ComBoChange)(int) = &QComboBox::activated;

        this->connect(CBox1,&QCheckBox::stateChanged,this,[=](int state){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType10,state);
        });
        this->connect(CBox2,&QCheckBox::stateChanged,this,[=](int state){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType11,state);
        });
        this->connect(FeedTypeBox,ComBoChange,this,[=](int index){
            Data_SettingDbData::Get()->Set_GlobalValue(iniFeeding1,index);
        });
        this->connect(NoLeapLenghBox,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(inifrogJump1,d);
        });
        this->connect(FeedSpeedBox,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniFeeding2,d);
        });
        this->connect(FeedLenghtBox,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniFeeding3,d);
        });
        this->connect(DefaultBox1,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault1,d);
        });
        this->connect(DefaultBox3,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault3,d);
        });
        this->connect(DefaultBox4,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault4,d);
        });
        this->connect(DefaultBox5,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault5,d);
        });
        this->connect(DefaultBox7,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault7,d);
        });
        this->connect(DefaultBox9,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault9,d);
        });
        this->connect(leapfrogBox1,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType1,d);
        });
        this->connect(leapfrogBox2,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType2,d);
        });
        this->connect(leapfrogBox3,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType3,d);
        });
        this->connect(leapfrogBox4,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType4,d);
        });
        this->connect(leapfrogBox5,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType5,d);
        });
        this->connect(EdgeGroupBox1,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType6,d);
        });
        this->connect(EdgeGroupBox2,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType7,d);
        });
        this->connect(EdgeGroupBox3,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType8,d);
        });
        this->connect(EdgeGroupBox4,DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_GlobalValue(iniGlobalSettingType9,d);
        });
        //INT
        this->connect(FeednumBox,SpinBox,this,[=](int i){
            Data_SettingDbData::Get()->Set_GlobalValue(iniFeeding4,i);
        });
        this->connect(DefaultBox2,SpinBox,this,[=](int i){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault2,i);
        });
        this->connect(DefaultBox6,SpinBox,this,[=](int i){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault6,i);
        });
        this->connect(DefaultBox8,SpinBox,this,[=](int i){
            Data_SettingDbData::Get()->Set_GlobalValue(inidefault8,i);
        });

        this->connect(Data_SettingDbData::Get(),&Data_SettingDbData::Refursh_Global,this,[=]()
        {
            NoLeapLenghBox->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inifrogJump1).toDouble());
            FeedTypeBox->setCurrentIndex(Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding1).toInt());
            FeedSpeedBox->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding2).toDouble());
            FeedLenghtBox->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding3).toDouble());
            FeednumBox->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding4).toInt());
            DefaultBox1->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault1).toDouble());
            DefaultBox2->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault2).toInt());
            DefaultBox3->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault3).toDouble());
            DefaultBox4->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault4).toDouble());
            DefaultBox5->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault5).toDouble());
            DefaultBox6->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault6).toInt());
            DefaultBox7->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault7).toDouble());
            DefaultBox8->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault8).toInt());
            DefaultBox9->setValue(Data_SettingDbData::Get()->Get_GlobalValue(inidefault9).toDouble());
            leapfrogBox1->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType1).toDouble());
            leapfrogBox2->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType2).toDouble());
            leapfrogBox3->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType3).toDouble());
            leapfrogBox4->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType4).toDouble());
            leapfrogBox5->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType5).toDouble());
            EdgeGroupBox1->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType6).toDouble());
            EdgeGroupBox2->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType7).toDouble());
            EdgeGroupBox3->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType8).toDouble());
            EdgeGroupBox4->setValue(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType9).toDouble());
            CBox1->setChecked(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType10).toInt());
            CBox2->setChecked(Data_SettingDbData::Get()->Get_GlobalValue(iniGlobalSettingType11).toInt());
            FeedTypeBox->setCurrentIndex(Data_SettingDbData::Get()->Get_GlobalValue(iniFeeding1).toInt());

            int RadioValue = Data_SettingDbData::Get()->Get_GlobalValue(iniReturnStr).toInt();
            if(RadioValue == 0)
            {
                btn1->click();
            }
            else if(RadioValue == 1)
            {
                btn2->click();
            }
            else if(RadioValue == 2)
            {
                btn3->click();
            }
            else if(RadioValue == 3)
            {
                btn4->click();
            }
        });
        break;
    }
    case PerforatedWidgetType:
    {
        QList<bool> DataState = Data_SettingDbData::Get()->PopDataState();
        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(0,0,0,0);

        QList<PerforatedSettingType> PerforationType1;
        PerforationType1 << iniPerforatedSettingType1 << iniPerforatedSettingType2 << iniPerforatedSettingType3 << iniPerforatedSettingType4
                         << iniPerforatedSettingType5 << iniPerforatedSettingType6 << iniPerforatedSettingType7 << iniPerforatedSettingType8
                         << iniPerforatedSettingType9 << iniPerforatedSettingType10 << iniPerforatedSettingType11 << iniPerforatedSettingType12;

        QList<PerforatedSettingType> PerforationType2;
        PerforationType2 << iniPerforatedSetting2Type1 << iniPerforatedSetting2Type2 << iniPerforatedSetting2Type3 << iniPerforatedSetting2Type4
                         << iniPerforatedSetting2Type5 << iniPerforatedSetting2Type6 << iniPerforatedSetting2Type7 << iniPerforatedSetting2Type8
                         << iniPerforatedSetting2Type9 << iniPerforatedSetting2Type10 << iniPerforatedSetting2Type11 << iniPerforatedSetting2Type12;

        QList<PerforatedSettingType> PerforationType3;
        PerforationType3 << iniPerforatedSetting3Type1 << iniPerforatedSetting3Type2 << iniPerforatedSetting3Type3 << iniPerforatedSettingType4
                         << iniPerforatedSetting3Type5 << iniPerforatedSetting3Type6 << iniPerforatedSetting3Type7 << iniPerforatedSetting3Type8
                         << iniPerforatedSetting3Type9 << iniPerforatedSetting3Type10 << iniPerforatedSetting3Type11 << iniPerforatedSetting3Type12;
        QWidget* PerforationWidget1 = Create_PerforatedWidget(PerforationType3,":/Img/Per3.png","穿孔参数3",3);

        QWidget* PerforationWidget2 = Create_PerforatedWidget(PerforationType2,":/Img/PerforatedPaint.png","穿孔参数2",2);

        QWidget* PerforationWidget3 = Create_PerforatedWidget(PerforationType1,":/Img/Per1.png","穿孔参数1",1);
        mLayout->addWidget(PerforationWidget1);
        mLayout->addWidget(PerforationWidget2);
        mLayout->addWidget(PerforationWidget3);
        mWidget->setLayout(mLayout);

        Widget = mWidget;\
        if(!DataState.at(4))
            PerforationWidget1->hide();
        if(!DataState.at(5))
            PerforationWidget2->hide();
        if(!DataState.at(6))
            PerforationWidget3->hide();

        break;

    }
    case CuttingWidgetType:
    {
        QWidget* mMainWidget = new QWidget();
        QHBoxLayout* mMainLayout = new QHBoxLayout();
        mMainLayout->setSpacing(0);
        mMainLayout->setContentsMargins(0,0,0,0);

        QScrollArea* Area = new QScrollArea();
        Area->setObjectName("Area");
        Area->setStyleSheet("#Area{border:none;}");
        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(5);
        mLayout->setContentsMargins(0,0,0,0);

        //工艺参数列表
        QGroupBox* ProcessVarGroup = new QGroupBox();
        ProcessVarGroup->setTitle("工艺参数");
        ProcessVarGroup->setStyleSheet("font:12pt ""黑体"" ");
        ProcessVarGroup->setAlignment(Qt::AlignCenter);

        QVBoxLayout* ProcessVarLayout = new QVBoxLayout();
        ProcessVarLayout->setSpacing(0);
        ProcessVarLayout->setContentsMargins(0,0,0,0);

        QStringList CuttingTableName;
        for(int i = 0; i < Data_SettingDbData::Get()->Get_Max_Cutting_num(); i++)
        {
            CuttingTableName = Data_SettingDbData::Get()->Get_CuttingListText();
        }

        QWidget* ProcessVarWidget = InitCuttingTableName(CuttingTableName);

        ProcessVarLayout->addWidget(ProcessVarWidget);
        ProcessVarGroup->setLayout(ProcessVarLayout);

        //标线层
        QGroupBox* markGroup = new QGroupBox();
        markGroup->setTitle("标线层");
        markGroup->setAlignment(Qt::AlignCenter);
        markGroup->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* markLayout = new QVBoxLayout();
        markLayout->setSpacing(0);
        markLayout->setContentsMargins(0,0,0,0);
        QWidget* markWidget = InitCuttingTableValue(0);
        markLayout->addWidget(markWidget);
        markGroup->setLayout(markLayout);

        //切刀层1
        QGroupBox* CutterGroup1 = new QGroupBox();
        CutterGroup1->setTitle("切刀层");
        CutterGroup1->setAlignment(Qt::AlignCenter);
        CutterGroup1->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* CutterLayout = new QVBoxLayout();
        CutterLayout->setSpacing(0);
        CutterLayout->setContentsMargins(0,0,0,0);
        QWidget* CutterWidget = InitCuttingTableValue(1);
        CutterLayout->addWidget(CutterWidget);
        CutterGroup1->setLayout(CutterLayout);

        //切刀层2
        QGroupBox* CutterGroup2 = new QGroupBox();
        CutterGroup2->setTitle("切刀层2");
        CutterGroup2->setAlignment(Qt::AlignCenter);
        CutterGroup2->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* CutterLayout2 = new QVBoxLayout();
        CutterLayout2->setSpacing(0);
        CutterLayout2->setContentsMargins(0,0,0,0);
        QWidget* CutterWidget2 = InitCuttingTableValue(2);
        CutterLayout2->addWidget(CutterWidget2);
        CutterGroup2->setLayout(CutterLayout2);

        //1.05切到层
        QGroupBox* CutterGroup3 = new QGroupBox();
        CutterGroup3->setTitle("1.05切刀层");
        CutterGroup3->setAlignment(Qt::AlignCenter);
        CutterGroup3->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* CutterLayout3 = new QVBoxLayout();
        CutterLayout3->setSpacing(0);
        CutterLayout3->setContentsMargins(0,0,0,0);
        QWidget* CutterWidget3 = InitCuttingTableValue(3);
        CutterLayout3->addWidget(CutterWidget3);
        CutterGroup3->setLayout(CutterLayout3);

        //压线层
        QGroupBox* LinePressGroup = new QGroupBox();
        LinePressGroup->setTitle("压线层1");
        LinePressGroup->setAlignment(Qt::AlignCenter);
        LinePressGroup->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* LinePressLayout = new QVBoxLayout();
        LinePressLayout->setSpacing(0);
        LinePressLayout->setContentsMargins(0,0,0,0);
        QWidget* LinePressWidget = InitCuttingTableValue(4);
        LinePressLayout->addWidget(LinePressWidget);
        LinePressGroup->setLayout(LinePressLayout);

        //压线层2
        QGroupBox* LinePressGroup2 = new QGroupBox();
        LinePressGroup2->setTitle("压线层2");
        LinePressGroup2->setAlignment(Qt::AlignCenter);
        LinePressGroup2->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* LinePressLayout2 = new QVBoxLayout();
        LinePressLayout2->setSpacing(0);
        LinePressLayout2->setContentsMargins(0,0,0,0);
        QWidget* LinePressWidget2 = InitCuttingTableValue(5);
        LinePressLayout2->addWidget(LinePressWidget2);
        LinePressGroup2->setLayout(LinePressLayout2);

        //外框层1
        QGroupBox* FrameGroup = new QGroupBox();
        FrameGroup->setTitle("外框层1");
        FrameGroup->setAlignment(Qt::AlignCenter);
        FrameGroup->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* FrameLayout = new QVBoxLayout();
        FrameLayout->setSpacing(0);
        FrameLayout->setContentsMargins(0,0,0,0);
        QWidget* FrameWidget = InitCuttingTableValue(6);
        FrameLayout->addWidget(FrameWidget);
        FrameGroup->setLayout(FrameLayout);

        //外框层2
        QGroupBox* FrameGroup2 = new QGroupBox();
        FrameGroup2->setTitle("外框层2");
        FrameGroup2->setAlignment(Qt::AlignCenter);
        FrameGroup2->setStyleSheet("font:12pt ""黑体"" ");
        QVBoxLayout* FrameLayout2 = new QVBoxLayout();
        FrameLayout2->setSpacing(0);
        FrameLayout2->setContentsMargins(0,0,0,0);
        QWidget* FrameWidget2 = InitCuttingTableValue(7);
        FrameLayout2->addWidget(FrameWidget2);
        FrameGroup2->setLayout(FrameLayout2);

        mLayout->addWidget(ProcessVarGroup);
        mLayout->addWidget(markGroup);
        mLayout->addWidget(CutterGroup1);
        mLayout->addWidget(CutterGroup2);
        mLayout->addWidget(CutterGroup3);
        mLayout->addWidget(LinePressGroup);
        mLayout->addWidget(LinePressGroup2);
        mLayout->addWidget(FrameGroup);
        mLayout->addWidget(FrameGroup2);
        mWidget->setLayout(mLayout);
        Area->setWidget(mWidget);

        mMainLayout->addWidget(Area);
        mMainWidget->setLayout(mMainLayout);
        Widget = mMainWidget;



        break;
    }

    }

    return Widget;
}


QWidget* DB_Hmi_Gui_Data::CreateLabelValueLabelWidget(QString Text,QString unitText,int model,int max,int min,int decimalPoint,
                                                     QVariant Value,QSize TextSize,QSize ValueSize,QSize UnitSize,bool isStretch,
                                                      QStringList comboxNameTable)
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(10);
    mLayout->setContentsMargins(5,5,5,5);

    QLabel* lbl_Text = Public_Control::Get_Label(Text);
    if(TextSize.width() != 0)
        lbl_Text->setFixedWidth(TextSize.width());
    if(TextSize.height() != 0)
        lbl_Text->setFixedHeight(TextSize.height());
    lbl_Text->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QDoubleSpinBox* Dbox = nullptr;
    QSpinBox* Ibox = nullptr;
    QComboBox* Cbox = nullptr;
    if(model == 1)
    {
        Ibox = new QSpinBox();
        if(ValueSize.width() != 0)
            Ibox->setFixedWidth(ValueSize.width());
        if(ValueSize.height() != 0)
            Ibox->setFixedHeight(ValueSize.height());
        Ibox->setRange(min,max);
        Ibox->setValue(Value.toInt());
        Ibox->setObjectName("ValueBox");
    }
    else if(model == 2)
    {
        Dbox = new QDoubleSpinBox();
        if(ValueSize.width() != 0)
            Dbox->setFixedWidth(ValueSize.width());
        if(ValueSize.height() != 0)
            Dbox->setFixedHeight(ValueSize.height());
        if(decimalPoint != -1)
            Dbox->setDecimals(decimalPoint);

        Dbox->setRange(min,max);
        Dbox->setValue(Value.toDouble());
        Dbox->setObjectName("ValueBox");
    }
    else if(model == 3)
    {
        Cbox = new QComboBox();
        if(ValueSize.width() != 0)
            Cbox->setFixedWidth(ValueSize.width());
        if(ValueSize.height() != 0)
            Cbox->setFixedHeight(ValueSize.height());
        if(comboxNameTable.size() != 0)
        {
            for(int i = 0; i < comboxNameTable.size(); i++)
            {
                Cbox->addItem(comboxNameTable.at(i));
            }
        }
        Cbox->setCurrentIndex(Value.toInt());
        Cbox->setObjectName("ValueBox");
    }

    QLabel* lbl_Unit = Public_Control::Get_Label(unitText);
    if(UnitSize.width() != 0)
        lbl_Unit->setFixedWidth(UnitSize.width());
    if(UnitSize.height() != 0)
        lbl_Unit->setFixedWidth(UnitSize.height());
    lbl_Unit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    mLayout->addWidget(lbl_Text);
    if(model == 1)
        mLayout->addWidget(Ibox);
    else if(model == 2)
        mLayout->addWidget(Dbox);
    else if(Cbox)
        mLayout->addWidget(Cbox);
    mLayout->addWidget(lbl_Unit);
    if(isStretch)
        mLayout->addStretch();
    mWidget->setLayout(mLayout);


    return mWidget;
}

QWidget* DB_Hmi_Gui_Data::CreateValueLabelWidget(QString str,int min,int max)
{
    QWidget* mWidget = new QWidget();
    mWidget->setFixedHeight(40);
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QSpinBox* box = new QSpinBox();
    box->setObjectName("ValueBox");
    box->setFixedSize(80,40);
    box->setRange(min,max);

    QLabel* lbl_Str = Public_Control::Get_Label(str);

    mLayout->addWidget(box);
    mLayout->addWidget(lbl_Str);
    mLayout->addStretch();
    mWidget->setLayout(mLayout);

    return mWidget;
}

//初始化切割列表名称
QWidget* DB_Hmi_Gui_Data::InitCuttingTableName(QStringList list)
{
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    for(int i = 0; i < list.size(); i++)
    {
        const QString lblStyle = Public_Str::Get_Sty(Style_Css{DataCuttingLabelStyle,{}});
        QLabel* lbl = Public_Control::Get_Label(list.at(i));
        lbl->setFixedSize(195,45);
        lbl->setStyleSheet(lblStyle);
        mLayout->addWidget(lbl);
    }
    mWidget->setLayout(mLayout);

    return mWidget;
}

//初始化列表值
QWidget* DB_Hmi_Gui_Data::InitCuttingTableValue(int layerNum)
{
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(3,3,3,3);

    for(int i = 0; i < Data_SettingDbData::Get()->Get_Max_Cutting_num(); i++)
    {
        //SpinBox
        if(Data_SettingDbData::Get()->Get_CuttingGuiType(i) == 1)
        {
            const QString BoxStyle = Public_Str::Get_Sty(Style_Css{DataCuttingSpinboxStyle,{}});
            QSpinBox* box = new QSpinBox();
            box->setObjectName(QString::number(layerNum) + "box" + QString::number(i));
            box->setStyleSheet(BoxStyle);
            box->setFixedSize(195,45);
            box->setRange(Data_SettingDbData::Get()->Get_CuttingMin(i),Data_SettingDbData::Get()->Get_CuttingMax(i));
            mLayout->addWidget(box);
        }
        //DoubleSpinBox
        else if(Data_SettingDbData::Get()->Get_CuttingGuiType(i) == 2)
        {
            const QString BoxStyle = Public_Str::Get_Sty(Style_Css{DataCuttingDoubleSpinboxStyle,{}});
            QDoubleSpinBox* box = new QDoubleSpinBox();
            box->setObjectName(QString::number(layerNum) + "box" + QString::number(i));
            box->setStyleSheet(BoxStyle);
            box->setFixedSize(195,45);
            box->setRange(Data_SettingDbData::Get()->Get_CuttingMin(i),Data_SettingDbData::Get()->Get_CuttingMax(i));
            box->setDecimals(Data_SettingDbData::Get()->Get_CuttingDecimal(i));
            mLayout->addWidget(box);
        }
        //ComboBox
        else if(Data_SettingDbData::Get()->Get_CuttingGuiType(i) == 3)
        {
            QComboBox* box = new QComboBox();
            box->setObjectName(QString::number(layerNum) + "box" + QString::number(i));
            box->setFixedSize(195,45);
            for(int Count = 0; Count < Data_SettingDbData::Get()->Get_CuttingComboxList(i).size(); Count++)
            {
                box->addItem(Data_SettingDbData::Get()->Get_CuttingComboxList(i).at(Count));
            }
            mLayout->addWidget(box);
        }
    }
    mWidget->setLayout(mLayout);

    void (QDoubleSpinBox::*DoubleSpinChange)(double) = &QDoubleSpinBox::valueChanged;
    void (QSpinBox::*SpinChange)(int) = &QSpinBox::valueChanged;
    void (QComboBox::*ComboChange)(int) = &QComboBox::activated;

    QList<QSpinBox*> SpinList = mWidget->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> DoubleSpinList = mWidget->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> ComboList = mWidget->findChildren<QComboBox*>();

    this->connect(Data_SettingDbData::Get(),&Data_SettingDbData::Refursh_Cutting,this,[=](){
        for(int i = 0; i < SpinList.size(); i++)
        {
            int name = SpinList.at(i)->objectName().split("box").last().toInt();
            SpinList.at(i)->setValue(Data_SettingDbData::Get()->Get_CuttingValue(name,layerNum).toInt());
        }
        for(int i = 0; i < DoubleSpinList.size(); i++)
        {
            int name = DoubleSpinList.at(i)->objectName().split("box").last().toInt();
            DoubleSpinList.at(i)->setValue(Data_SettingDbData::Get()->Get_CuttingValue(name,layerNum).toInt());
        }
        for(int i = 0; i < ComboList.size(); i++)
        {
            int name = ComboList.at(i)->objectName().split("box").last().toInt();
            ComboList.at(i)->setCurrentIndex(Data_SettingDbData::Get()->Get_CuttingValue(name,layerNum).toInt());
        }
    });

    for(int i = 0; i < SpinList.size(); i++)
    {
        int name = SpinList.at(i)->objectName().split("box").last().toInt();
        this->connect(SpinList.at(i),SpinChange,this,[=](int i){
            Data_SettingDbData::Get()->Set_CuttingValue(name,layerNum,i);
        });
    }
    for(int j = 0; j < DoubleSpinList.size(); j++)
    {
        int name = DoubleSpinList.at(j)->objectName().split("box").last().toInt();
        this->connect(DoubleSpinList.at(j),DoubleSpinChange,this,[=](double d){
            Data_SettingDbData::Get()->Set_CuttingValue(name,layerNum,d);
        });
    }
    for(int i = 0; i < ComboList.size(); i++)
    {
        int name = ComboList.at(i)->objectName().split("box").last().toInt();
        this->connect(ComboList.at(i),ComboChange,this,[=](int z){
           Data_SettingDbData::Get()->Set_CuttingValue(name,layerNum,z);
        });
    }

    return mWidget;
}


QWidget* DB_Hmi_Gui_Data::Create_PerforatedWidget(QList<PerforatedSettingType> type,QString Paint,QString text,int Model)
{
    QList<bool> DataState = Data_SettingDbData::Get()->PopDataState();
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QVBoxLayout* mVLayout = new QVBoxLayout();
    mVLayout->setSpacing(0);
    mVLayout->setContentsMargins(0,0,0,0);
    QWidget* LeftWigdet = new QWidget();
    if(Model == 1)
        LeftWigdet->setFixedSize(300,540);
    else if(Model == 2)
        LeftWigdet->setFixedSize(300,630);
    else if(Model == 3)
        LeftWigdet->setFixedSize(300,750);
    LeftWigdet->setStyleSheet(QString("border-image:url(%1);").arg(Paint));
    mVLayout->addStretch();
    mVLayout->addWidget(LeftWigdet);

    QVBoxLayout* mModelLayout = new QVBoxLayout();
    mModelLayout->setSpacing(0);
    mModelLayout->setContentsMargins(0,20,0,0);


    QGroupBox* PerforateRreservedGroup = new QGroupBox();
    PerforateRreservedGroup->setTitle("预留孔选择");
    PerforateRreservedGroup->setFixedHeight(50);
    PerforateRreservedGroup->setFixedWidth(300);
    QHBoxLayout* PerforateRreservedLayout = new QHBoxLayout();
    PerforateRreservedLayout->setSpacing(0);
    PerforateRreservedLayout->setContentsMargins(0,0,0,0);
    QComboBox* ReeservedBox = new QComboBox();
    ReeservedBox->addItem("不穿孔");
    ReeservedBox->addItem("一级穿孔");
    ReeservedBox->addItem("二级穿孔");
    ReeservedBox->addItem("三级穿孔");
    PerforateRreservedLayout->addWidget(ReeservedBox);
    PerforateRreservedLayout->addStretch();
    PerforateRreservedGroup->setLayout(PerforateRreservedLayout);

    QGroupBox* PerforatedGroup = new QGroupBox();
    PerforatedGroup->setFixedWidth(300);
    PerforatedGroup->setFixedHeight(495);
    PerforatedGroup->setTitle(text);

    QVBoxLayout* PerforatedLayout = new QVBoxLayout();
    PerforatedLayout->setSpacing(0);
    PerforatedLayout->setContentsMargins(0,0,0,0);

    QWidget* PerforatedTimeWidget = CreateValueLabelWidget(Data_SettingDbData::Get()->Get_PerforatedText(type.at(0)),
                                                           Data_SettingDbData::Get()->Get_PerforatedMin(type.at(0)),
                                                           Data_SettingDbData::Get()->Get_PerforatedMax(type.at(0)));
    QComboBox* box = new QComboBox();
    box->setFixedSize(80,40);
    for(int i = 0; i < Data_SettingDbData::Get()->Get_PerforatedComboxList(type.at(1)).size(); i++)
    {
        box->addItem(Data_SettingDbData::Get()->Get_PerforatedComboxList(type.at(1)).at(i));
    }
    QSpinBox* box1 = new QSpinBox();
    box1->setFixedSize(80,40);
    box1->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(2)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(2)));

    QWidget* PerforatedPowerWidget = CreateValueLabelWidget(Data_SettingDbData::Get()->Get_PerforatedText(type.at(3)),
                                                            Data_SettingDbData::Get()->Get_PerforatedMin(type.at(3)),
                                                            Data_SettingDbData::Get()->Get_PerforatedMax(type.at(3)));
    QSpinBox* box2 = new QSpinBox();
    box2->setFixedSize(80,40);
    box2->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(4)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(4)));

    QDoubleSpinBox* box3 = new QDoubleSpinBox();
    box3->setFixedSize(80,40);
    box3->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(5)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(5)));
    box3->setDecimals(Data_SettingDbData::Get()->Get_PerforatedDecimal(type.at(5)));

    QSpinBox* box4 = new QSpinBox();
    box4->setFixedSize(80,40);
    box4->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(6)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(6)));

    QWidget* PerforatedHeightWidget = CreateValueLabelWidget(Data_SettingDbData::Get()->Get_PerforatedText(type.at(7)),
                                                             Data_SettingDbData::Get()->Get_PerforatedMin(type.at(7)),
                                                             Data_SettingDbData::Get()->Get_PerforatedMax(type.at(7)));
    QDoubleSpinBox* box5 = new QDoubleSpinBox();
    box5->setFixedSize(80,40);
    box5->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(8)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(8)));
    box5->setDecimals(Data_SettingDbData::Get()->Get_PerforatedDecimal(type.at(8)));

    QDoubleSpinBox* box6 = new QDoubleSpinBox();
    box6->setFixedSize(80,40);
    box6->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(9)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(9)));
    box6->setDecimals(Data_SettingDbData::Get()->Get_PerforatedDecimal(type.at(9)));

    QSpinBox* box7 = new QSpinBox();
    box7->setFixedSize(80,40);
    box7->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(10)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(10)));

    QSpinBox* box8 = new QSpinBox();
    box8->setFixedSize(80,40);
    box8->setRange(Data_SettingDbData::Get()->Get_PerforatedMin(type.at(11)),Data_SettingDbData::Get()->Get_PerforatedMax(type.at(11)));

    PerforatedLayout->addWidget(PerforatedTimeWidget);
    PerforatedLayout->addWidget(box);
    PerforatedLayout->addWidget(box1);
    PerforatedLayout->addWidget(PerforatedPowerWidget);
    PerforatedLayout->addWidget(box2);
    PerforatedLayout->addWidget(box3);
    PerforatedLayout->addWidget(box4);
    PerforatedLayout->addWidget(PerforatedHeightWidget);
    PerforatedLayout->addWidget(box5);
    PerforatedLayout->addWidget(box6);
    PerforatedLayout->addWidget(box7);
    PerforatedLayout->addWidget(box8);
    PerforatedGroup->setLayout(PerforatedLayout);

    mModelLayout->addWidget(PerforateRreservedGroup);
    mModelLayout->setSpacing(100);
    mModelLayout->addWidget(PerforatedGroup);
    if(Model == 3)
        mModelLayout->addStretch();

//    mLayout->addStretch();
    mLayout->addLayout(mVLayout);
    mLayout->addLayout(mModelLayout);
//    mLayout->addStretch();
    mWidget->setLayout(mLayout);

    if(Model != 1)
        PerforateRreservedGroup->deleteLater();



    QSpinBox* PTimeBox = PerforatedTimeWidget->findChild<QSpinBox*>("ValueBox");
    QSpinBox* PPowerBox = PerforatedPowerWidget->findChild<QSpinBox*>("ValueBox");
    QSpinBox* PHeightBox = PerforatedHeightWidget->findChild<QSpinBox*>("ValueBox");

    void (QDoubleSpinBox::*DoubleSpinChange)(double) = &QDoubleSpinBox::valueChanged;
    void (QSpinBox::*SpinChange)(int) = &QSpinBox::valueChanged;
    void (QComboBox::*ComboChange)(int) = &QComboBox::activated;

    this->connect(box,ComboChange,this,[=](int i){
       Data_SettingDbData::Get()->Set_PerforatedValue(type.at(1),i);
    });
    this->connect(PTimeBox,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(0),i);
    });
    this->connect(PPowerBox,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(3),i);
    });
    this->connect(PHeightBox,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(7),i);
    });
    this->connect(box1,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(2),i);
    });
    this->connect(box2,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(4),i);
    });
    this->connect(box4,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(6),i);
    });
    this->connect(box7,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(10),i);
    });
    this->connect(box8,SpinChange,this,[=](int i){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(11),i);
    });
    this->connect(box3,DoubleSpinChange,this,[=](double d){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(5),d);
    });
    this->connect(box5,DoubleSpinChange,this,[=](double d){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(8),d);
    });
    this->connect(box6,DoubleSpinChange,this,[=](double d){
        Data_SettingDbData::Get()->Set_PerforatedValue(type.at(9),d);
    });

    this->connect(Data_SettingDbData::Get(),&Data_SettingDbData::Refursh_Perforated,this,[=](){
        box->setCurrentIndex(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(1)).toInt());
        PTimeBox->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(0)).toInt());
        PPowerBox->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(3)).toInt());
        PHeightBox->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(7)).toInt());
        box1->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(2)).toInt());
        box2->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(4)).toInt());
        box4->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(6)).toInt());
        box7->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(10)).toInt());
        box8->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(11)).toInt());

        box3->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(5)).toDouble());
        box5->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(8)).toDouble());
        box6->setValue(Data_SettingDbData::Get()->Get_PerforatedValue(type.at(9)).toDouble());
    });

    return mWidget;
}
