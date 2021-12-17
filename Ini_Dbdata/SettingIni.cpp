#include "SettingIni.h"
#include <QTextCodec>
#include <QSettings>
#include <QDebug>

#include "Setting_Data.h"

static SettingIni ini;

SettingIni::SettingIni()
{
    Conf = new QSettings("C:\\PACnc\\DBHMI\\cfg\\SettingConfiguration.ini",QSettings::IniFormat);
    Conf->setIniCodec(QTextCodec::codecForName("GB2312"));

    initMainSet();
    initManualSet();
    initAutoSet();
    initDataSet();
    initPlcMoSet();
    initSettingSet();

    this->connect(Setting_Data::Get(),&Setting_Data::Write_Init,this,&SettingIni::Write_For_Ini);
}

SettingIni::~SettingIni()
{

}

void SettingIni::initMainSet()
{
    QList<QStringList> StrList;
    QStringList NameList;
    QStringList ChineseNameList;
    QStringList EnglishNameList;
    QStringList PlcOutList;
    QStringList PlcIntList;
    QStringList StrPaths;
    //View1
    for(int i = 0; i < 8; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("IndicatorLight/VISO_Lamp_%1a_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList<< "";
        else
            ChineseNameList << Conf->value(QString("IndicatorLight/VISO_Lamp_%1a_ch").arg(i + 1)).toString();

        if(Conf->value(QString("IndicatorLight/VISO_Lamp_%1a_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList<<"";
        else
            EnglishNameList << Conf->value(QString("IndicatorLight/VISO_Lamp_%1a_en").arg(i + 1)).toString();
        if(Conf->value(QString("IndicatorLight/VISO_Lamp_%1b").arg(i + 1)).toString().isEmpty())
            PlcOutList << "";
        else
            PlcOutList << Conf->value(QString("IndicatorLight/VISO_Lamp_%1b").arg(i + 1)).toString();
    }
    MainData Data;
    Data.type = MainView1;
    Data.Name = NameList;
    Data.ChineseName = ChineseNameList;
    Data.EnglishName = EnglishNameList;
    Data.PLCOutput = PlcOutList;
    Setting_Data::Get()->MainPushBack(Data);
    NameList.clear();
    ChineseNameList.clear();
    EnglishNameList.clear();
    PlcOutList.clear();

    //View2
    for(int i = 0; i < 6; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("InformationDisplay/VISO_Lamp_%1_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList<< "";
        else
            ChineseNameList << Conf->value(QString("InformationDisplay/VISO_Lamp_%1_ch").arg(i + 1)).toString();
        if(Conf->value(QString("InformationDisplay/VISO_Lamp_%1_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("InformationDisplay/VISO_Lamp_%1_en").arg(i + 1)).toString();
        if(Conf->value(QString("InformationDisplay/VISO_Lamp_%1").arg(i + 1)).toString().isEmpty())
            PlcOutList << "";
        else
            PlcOutList << Conf->value(QString("InformationDisplay/VISO_Lamp_%1").arg(i + 1)).toString();
    }
    MainData Data1;
    Data1.type = MainView2;
    Data1.Name = NameList;
    Data1.ChineseName = ChineseNameList;
    Data1.EnglishName = EnglishNameList;
    Data1.PLCOutput = PlcOutList;
    Setting_Data::Get()->MainPushBack(Data1);
    NameList.clear();
    ChineseNameList.clear();
    EnglishNameList.clear();
    PlcOutList.clear();

    //加工计数
    for(int i = 0; i < 6; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("RunCount/VISO_Lamp_%1_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList<< "";
        else
            ChineseNameList << Conf->value(QString("RunCount/VISO_Lamp_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("RunCount/VISO_Lamp_%1_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("RunCount/VISO_Lamp_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("RunCount/VISO_Lamp_%1").arg(i + 1)).toString().isEmpty())
            PlcOutList << "";
        else
            PlcOutList << Conf->value(QString("RunCount/VISO_Lamp_%1").arg(i + 1)).toString();
    }
    MainData Data2;
    Data2.type = MainView3;
    Data2.Name = NameList;
    Data2.ChineseName = ChineseNameList;
    Data2.EnglishName = EnglishNameList;
    Data2.PLCOutput = PlcOutList;
    Setting_Data::Get()->MainPushBack(Data2);
    NameList.clear();
    ChineseNameList.clear();
    EnglishNameList.clear();
    PlcOutList.clear();

    //倍率
    for(int i = 0; i < 4; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("Main/VISO_BTN1_%1a_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList << "";
        else
            ChineseNameList << Conf->value(QString("Main/VISO_BTN1_%1a_ch").arg(i + 1)).toString();

        if(Conf->value(QString("Main/VISO_BTN1_%1a_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("Main/VISO_BTN1_%1a_en").arg(i + 1)).toString();

        if(Conf->value(QString("Main/VISO_BTN1_%1b").arg(i + 1)).toString().isEmpty())
            PlcOutList << "";
        else
            PlcOutList << Conf->value(QString("Main/VISO_BTN1_%1b").arg(i + 1)).toString();

        if(Conf->value(QString("Main/VISI_BTN1_%1b").arg(i + 1)).toString().isEmpty())
            PlcIntList << "";
        else
            PlcIntList << Conf->value(QString("Main/VISI_BTN1_%1b").arg(i + 1)).toString();
    }
    MainData Data3;
    Data3.type = MainView4;
    Data3.Name = NameList;
    Data3.ChineseName = ChineseNameList;
    Data3.EnglishName = EnglishNameList;
    Data3.PLCOutput = PlcOutList;
    Data3.PLcInput = PlcIntList;
    Setting_Data::Get()->MainPushBack(Data3);
    NameList.clear();
    ChineseNameList.clear();
    EnglishNameList.clear();
    PlcOutList.clear();
    PlcIntList.clear();

    //外部可执行程序
    NameList << "外部可执行程序";
    if(Conf->value(("filepath/exe1")).toString().isEmpty())
        StrPaths << "";
    else
        StrPaths << Conf->value(("filepath/exe1")).toString();
    MainData Data4;
    Data4.type = MainView5;
    Data4.Name = NameList;
    Data4.strPaths = StrPaths;
    Setting_Data::Get()->MainPushBack(Data4);
    NameList.clear();
    StrPaths.clear();

    //监视
    NameList << "切割头" << "调高器" << "调高器2" << "激光器";
    for(int i = 0; i < 4; i++)
    {
        if(Conf->value(QString("filepath/exe%1").arg(i + 2)).toString().isEmpty())
            StrPaths << "";
        else
            StrPaths << Conf->value(QString("filepath/exe%1").arg(i + 2)).toString();
    }
    MainData Data5;
    Data5.type = MainView6;
    Data5.Name = NameList;
    Data5.strPaths = StrPaths;
    Setting_Data::Get()->MainPushBack(Data5);
}

void SettingIni::initManualSet()
{
    QStringList NameList;
    QStringList ChineseNameList;
    QStringList EnglishNameList;
    QStringList PLCOutputList;
    QStringList PLcInputList;
    //功能按钮
    for(int i = 0; i < 8; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("ManualFun/VISO_BTN1_%1a_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList << "";
        else
            ChineseNameList << Conf->value(QString("ManualFun/VISO_BTN1_%1a_ch").arg(i + 1)).toString();

        if(Conf->value(QString("ManualFun/VISO_BTN1_%1a_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("ManualFun/VISO_BTN1_%1a_en").arg(i + 1)).toString();

        if(Conf->value(QString("ManualFun/VISI_BTN1_%1b").arg(i + 1)).toString().isEmpty())
            PLcInputList << "";
        else
            PLcInputList << Conf->value(QString("ManualFun/VISI_BTN1_%1b").arg(i + 1)).toString();

        if(Conf->value(QString("ManualFun/VISO_BTN1_%1b").arg(i + 1)).toString().isEmpty())
            PLCOutputList << "";
        else
            PLCOutputList << Conf->value(QString("ManualFun/VISO_BTN1_%1b").arg(i + 1)).toString();
    }
    ManualData Data;
    Data.Name = NameList;
    Data.type = ManualView1;
    Data.ChineseName = ChineseNameList;
    Data.EnglishName = EnglishNameList;
    Data.PLcInput = PLcInputList;
    Data.PLCOutput = PLCOutputList;

    Setting_Data::Get()->ManualPushBack(Data);
    NameList.clear();
    ChineseNameList.clear();
    EnglishNameList.clear();
    PLcInputList.clear();
    PLCOutputList.clear();

    //增量距离
    NameList << "1";
    if(Conf->value("ManualDisTance/VISI_STEP").toString().isEmpty())
        PLcInputList << "";
    else
        PLcInputList << Conf->value("ManualDisTance/VISI_STEP").toString();

    if(Conf->value("ManualDisTance/VISO_STEP").toString().isEmpty())
        PLCOutputList << "";
    else
        PLCOutputList << Conf->value("ManualDisTance/VISO_STEP").toString();
    ManualData Data1;
    Data1.type = ManualView2;
    Data1.Name = NameList;
    Data1.PLcInput = PLcInputList;
    Data1.PLCOutput = PLCOutputList;
    Setting_Data::Get()->ManualPushBack(Data1);
    NameList.clear();
    PLcInputList.clear();
    PLCOutputList.clear();

    //模式
    for(int i = 0; i < 4; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("ManualModel/VISO_BTN1_%1a_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList << "";
        else
            ChineseNameList << Conf->value(QString("ManualModel/VISO_BTN1_%1a_ch").arg(i + 1)).toString();

        if(Conf->value(QString("ManualModel/VISO_BTN1_%1a_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("ManualModel/VISO_BTN1_%1a_en").arg(i + 1)).toString();

        if(Conf->value(QString("ManualModel/VISI_BTN1_%1b").arg(i + 1)).toString().isEmpty())
            PLcInputList << "";
        else
            PLcInputList << Conf->value(QString("ManualModel/VISI_BTN1_%1b").arg(i + 1)).toString();
    }
    ManualData Data2;
    Data2.type = ManualView3;
    Data2.Name = NameList;
    Data2.PLcInput = PLcInputList;
    Data2.ChineseName = ChineseNameList;
    Data2.EnglishName = EnglishNameList;
    Setting_Data::Get()->ManualPushBack(Data2);
    NameList.clear();
    PLcInputList.clear();
    ChineseNameList.clear();
    EnglishNameList.clear();

    //标记1
    NameList << "标记点X坐标" << "标记点Y坐标";
    if(Conf->value("Manualtag2/VISO_MARK_X_POS").toString().isEmpty())
        PLCOutputList << "";
    else
        PLCOutputList << Conf->value("Manualtag2/VISO_MARK_X_POS").toString();

    if(Conf->value("Manualtag2/VISO_MARK_Y_POS").toString().isEmpty())
        PLCOutputList << "";
    else
        PLCOutputList << Conf->value("Manualtag2/VISO_MARK_Y_POS").toString();
    ManualData Data3;
    Data3.type = ManualView4;
    Data3.Name = NameList;
    Data3.PLCOutput = PLCOutputList;
    Setting_Data::Get()->ManualPushBack(Data3);
    NameList.clear();
    PLCOutputList.clear();

    //标记2
    for(int i = 0; i < 2; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("Manualtag/VISO_BTN1_MARK%1_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList << "";
        else
            ChineseNameList << Conf->value(QString("Manualtag/VISO_BTN1_MARK%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("Manualtag/VISO_BTN1_MARK%1_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("Manualtag/VISO_BTN1_MARK%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("Manualtag/VISI_BTN1_MARK%1").arg(i + 1)).toString().isEmpty())
            PLcInputList << "";
        else
            PLcInputList << Conf->value(QString("Manualtag/VISI_BTN1_MARK%1").arg(i + 1)).toString();
    }
    ManualData Data4;
    Data4.type = ManualView5;
    Data4.Name = NameList;
    Data4.ChineseName = ChineseNameList;
    Data4.EnglishName = EnglishNameList;
    Data4.PLcInput = PLcInputList;
    Setting_Data::Get()->ManualPushBack(Data4);
}

void SettingIni::initAutoSet()
{
    QStringList NameList;
    QStringList ChineseNameList;
    QStringList EnglishNameList;
    QStringList PLCOutputList;
    QStringList PLcInputList;
    for(int i = 0; i < 8; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("ConnectButton2/VISO_BTN2_%1a_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList << "";
        else
            ChineseNameList << Conf->value(QString("ConnectButton2/VISO_BTN2_%1a_ch").arg(i + 1)).toString();

        if(Conf->value(QString("ConnectButton2/VISO_BTN2_%1a_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("ConnectButton2/VISO_BTN2_%1a_en").arg(i + 1)).toString();

        if(Conf->value(QString("ConnectButton2/VISI_BTN2_%1b").arg(i + 1)).toString().isEmpty())
            PLcInputList << "";
        else
            PLcInputList << Conf->value(QString("ConnectButton2/VISI_BTN2_%1b").arg(i + 1)).toString();

        if(Conf->value(QString("ConnectButton2/VISO_BTN2_%1b").arg(i + 1)).toString().isEmpty())
            PLCOutputList << "";
        else
            PLCOutputList << Conf->value(QString("ConnectButton2/VISO_BTN2_%1b").arg(i + 1)).toString();
    }

    AutoData Data;
    Data.type = AutoView1;
    Data.Name = NameList;
    Data.ChineseName = ChineseNameList;
    Data.EnglishName = EnglishNameList;
    Data.PLcInput = PLcInputList;
    Data.PLCOutput = PLCOutputList;
    Setting_Data::Get()->AutoPushBack(Data);
    NameList.clear();
    ChineseNameList.clear();
    EnglishNameList.clear();
    PLcInputList.clear();
    PLCOutputList.clear();

    for(int i = 0; i < 8; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("AutoRun/VISO_BTN%1_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList << "";
        else
            ChineseNameList << Conf->value(QString("AutoRun/VISO_BTN%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("AutoRun/VISO_BTN%1_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("AutoRun/VISO_BTN%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("AutoRun/VISI_BTN%1").arg(i + 1)).toString().isEmpty())
            PLcInputList << "";
        else
            PLcInputList << Conf->value(QString("AutoRun/VISI_BTN%1").arg(i + 1)).toString();

        if(Conf->value(QString("AutoRun/VISO_BTN%1").arg(i + 1)).toString().isEmpty())
            PLCOutputList << "";
        else
            PLCOutputList << Conf->value(QString("AutoRun/VISO_BTN%1").arg(i + 1)).toString();
    }
    AutoData Data1;
    Data1.type = AutoView2;
    Data1.Name = NameList;
    Data1.ChineseName = ChineseNameList;
    Data1.EnglishName = EnglishNameList;
    Data1.PLcInput = PLcInputList;
    Data1.PLCOutput = PLCOutputList;
    Setting_Data::Get()->AutoPushBack(Data1);
}

void SettingIni::initDataSet()
{
    QStringList NameList;
    QStringList ChineseNameList;
    QStringList EnglishNameList;
    QList<bool> StateList;

    for(int i = 0; i < 8; i++)
    {
        NameList << QString::number(i + 1);
        if(Conf->value(QString("LaserLayerName/Layer%1_ch").arg(i + 1)).toString().isEmpty())
            ChineseNameList << "";
        else
            ChineseNameList << Conf->value(QString("LaserLayerName/Layer%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("LaserLayerName/Layer%1_en").arg(i + 1)).toString().isEmpty())
            EnglishNameList << "";
        else
            EnglishNameList << Conf->value(QString("LaserLayerName/Layer%1_en").arg(i + 1)).toString();
    }
    DataData Data;
    Data.type = DataView;
    Data.Name = NameList;
    Data.ChineseName = ChineseNameList;
    Data.EnglishName = EnglishNameList;
    Setting_Data::Get()->DataPushBack(Data);


    StateList << Conf->value("DataFunc/leapfrog").toBool() << Conf->value("DataFunc/NO_leapfrog").toBool() << Conf->value("DataFunc/Fixedhigh_cut").toBool()
              << Conf->value("DataFunc/Edge_search").toBool() << Conf->value("DataFunc/Punch1").toBool() << Conf->value("DataFunc/Punch2").toBool()
              << Conf->value("DataFunc/Punch3").toBool() << Conf->value("DataFunc/Pre_Punch").toBool() << Conf->value("DataFunc/Feed").toBool()
              << Conf->value("DataFunc/RateBtn").toBool() << Conf->value("DataFunc/ProCount").toBool();
    DataData Data1;
    Data1.type = DataFun;
    Data1.State = StateList;
    Setting_Data::Get()->DataPushBack(Data1);
}

void SettingIni::initPlcMoSet()
{
    QStringList mNameList = QStringList();
    QStringList mPLCPathList = QStringList();
    QStringList mChineseList = QStringList();
    QStringList mEnglishList = QStringList();
    bool mstate;
    QString mtitle = "";
    for(int Count = 0; Count < 8; Count++)
    {
        mtitle = Conf->value(QString("PLCMonitor/GroupBox%1_Title").arg(Count + 1)).toString();
        mstate = Conf->value(QString("PLCMonitor/GroupBox%1_Enable").arg(Count + 1)).toBool();
        for(int i = 0; i < 8; i++)
        {
            mNameList << QString::number(i + 1);
            if(Conf->value(QString("PLCMonitor/GroupBox%1_Text_%2_ch").arg(Count + 1).arg(i+1)).toString().isEmpty())
                mChineseList << "";
            else
                mChineseList << Conf->value(QString("PLCMonitor/GroupBox%1_Text_%2_ch").arg(Count + 1).arg(i + 1)).toString();

            if(Conf->value(QString("PLCMonitor/GroupBox%1_Text_%2_en").arg(Count + 1).arg(i + 1)).toString().isEmpty())
                mEnglishList << "";
            else
                mEnglishList << Conf->value(QString("PLCMonitor/GroupBox%1_Text_%2_en").arg(Count + 1).arg(i + 1)).toString();

            if(Conf->value(QString("PLCMonitor/GroupBox%1_Text_%2_address").arg(Count + 1).arg(i + 1)).toString().isEmpty())
                mPLCPathList << "";
            else
                mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox%1_Text_%2_address").arg(Count + 1).arg(i + 1)).toString();
        }
        PLCMoData Data;
        if(Count == 0)
            Data.type = PlcMoView1;
        else if(Count == 1)
            Data.type = PlcMoView2;
        else if(Count == 2)
            Data.type = PlcMoView3;
        else if(Count == 3)
            Data.type = PlcMoView4;
        else if(Count == 4)
            Data.type = PlcMoView5;
        else if(Count == 5)
            Data.type = PlcMoView6;
        else if(Count == 6)
            Data.type = PlcMoView7;
        else if(Count == 7)
            Data.type = PlcMoView8;
        Data.Name = mNameList;
        Data.PLCPathList = mPLCPathList;
        Data.state = mstate;
        Data.title = mtitle;
        Data.ChineseList = mChineseList;
        Data.EnglishList = mEnglishList;
        Setting_Data::Get()->PLCPushBack(Data);

        mNameList.clear();
        mPLCPathList.clear();
        mChineseList.clear();
        mEnglishList.clear();
        mtitle.clear();
    }
#if 0
    QStringList mNameList;
    QStringList mPLCPathList;
    QStringList mChineseList;
    QStringList mEnglishList;
    bool mstate;
    QString mtitle;

    mtitle = Conf->value("PLCMonitor/GroupBox1_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox1_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox1_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox1_Text_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox1_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox1_Text_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox1_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox1_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data;
    Data.type = PlcMoView1;
    Data.Name = mNameList;
    Data.PLCPathList = mPLCPathList;
    Data.state = mstate;
    Data.title = mtitle;
    Data.ChineseList = mChineseList;
    Data.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();

    mtitle = Conf->value("PLCMonitor/GroupBox2_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox2_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox2_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox2_Text_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox2_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox2_Text_%1_en").arg(i + 1)).toString();
        if(Conf->value(QString("PLCMonitor/GroupBox2_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox2_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data1;
    Data1.type = PlcMoView2;
    Data1.Name = mNameList;
    Data1.PLCPathList = mPLCPathList;
    Data1.state = mstate;
    Data1.title = mtitle;
    Data1.ChineseList = mChineseList;
    Data1.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data1);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();

    mtitle = Conf->value("PLCMonitor/GroupBox3_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox3_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox3_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox3_Text_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox3_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox3_Text_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox3_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox3_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data2;
    Data2.type = PlcMoView3;
    Data2.Name = mNameList;
    Data2.PLCPathList = mPLCPathList;
    Data2.state = mstate;
    Data2.title = mtitle;
    Data2.ChineseList = mChineseList;
    Data2.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data2);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();

    mtitle = Conf->value("PLCMonitor/GroupBox4_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox4_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox4_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox4_Text_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox4_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox4_Text_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox4_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox4_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data3;
    Data3.type = PlcMoView4;
    Data3.Name = mNameList;
    Data3.PLCPathList = mPLCPathList;
    Data3.state = mstate;
    Data3.title = mtitle;
    Data3.ChineseList = mChineseList;
    Data3.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data3);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();

    mtitle = Conf->value("PLCMonitor/GroupBox5_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox5_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox5_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox5_Text_%1_ch").arg(i + 1)).toString();
        if(Conf->value(QString("PLCMonitor/GroupBox5_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox5_Text_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox5_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox5_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data4;
    Data4.type = PlcMoView5;
    Data4.Name = mNameList;
    Data4.PLCPathList = mPLCPathList;
    Data4.state = mstate;
    Data4.title = mtitle;
    Data4.ChineseList = mChineseList;
    Data4.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data4);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();

    mtitle = Conf->value("PLCMonitor/GroupBox6_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox6_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox6_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox6_Text_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox6_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox6_Text_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox6_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox6_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data5;
    Data5.type = PlcMoView6;
    Data5.Name = mNameList;
    Data5.PLCPathList = mPLCPathList;
    Data5.state = mstate;
    Data5.title = mtitle;
    Data5.ChineseList = mChineseList;
    Data5.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data5);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();

    mtitle = Conf->value("PLCMonitor/GroupBox7_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox7_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox7_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox7_Text_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox7_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox7_Text_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox7_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox7_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data6;
    Data6.type = PlcMoView7;
    Data6.Name = mNameList;
    Data6.PLCPathList = mPLCPathList;
    Data6.state = mstate;
    Data6.title = mtitle;
    Data6.ChineseList = mChineseList;
    Data6.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data6);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();

    mtitle = Conf->value("PLCMonitor/GroupBox8_Title").toString();
    mstate = Conf->value("PLCMonitor/GroupBox8_Enable").toBool();
    for(int i = 0; i < 8; i++)
    {
        mNameList << QString::number(i + 1);
        if(Conf->value(QString("PLCMonitor/GroupBox8_Text_%1_ch").arg(i + 1)).toString().isEmpty())
            mPLCPathList << "";
        else
            mPLCPathList << Conf->value(QString("PLCMonitor/GroupBox8_Text_%1_ch").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox8_Text_%1_en").arg(i + 1)).toString().isEmpty())
            mChineseList << "";
        else
            mChineseList << Conf->value(QString("PLCMonitor/GroupBox8_Text_%1_en").arg(i + 1)).toString();

        if(Conf->value(QString("PLCMonitor/GroupBox8_Text_%1_address").arg(i + 1)).toString().isEmpty())
            mEnglishList << "";
        else
            mEnglishList << Conf->value(QString("PLCMonitor/GroupBox8_Text_%1_address").arg(i + 1)).toString();
    }
    PLCMoData Data7;
    Data7.type = PlcMoView8;
    Data7.Name = mNameList;
    Data7.PLCPathList = mPLCPathList;
    Data7.state = mstate;
    Data7.title = mtitle;
    Data7.ChineseList = mChineseList;
    Data7.EnglishList = mEnglishList;
    Setting_Data::Get()->PLCPushBack(Data7);
    mNameList.clear();
    mChineseList.clear();
    mEnglishList.clear();
    mtitle.clear();
    mPLCPathList.clear();
#endif
}

void SettingIni::initSettingSet()
{
    QSettings* SetConf = new QSettings("C:\\PACnc\\DBHMI\\cfg\\Setting.ini",QSettings::IniFormat);
    SetConf->setIniCodec(QTextCodec::codecForName("UTF-8"));
    QStringList msg;
    for(int i = 0; i < 20; i++)
    {
         QString Value1 = SetConf->value("Settingini" + QString::number(i + 1)).toString();
         msg.push_back(Value1);
    }
    QList<SettingType> typeList;
    typeList << Settingini1 << Settingini2 << Settingini3 << Settingini4 << Settingini5 << Settingini6 << Settingini7 << Settingini8
             << Settingini9 << Settingini10 << Settingini11 << Settingini12 << Settingini13 << Settingini14 <<Settingini15 << Settingini16
             << Settingini17 << Settingini18 << Settingini19 << Settingini20;
    for(int i = 0; i < msg.size(); i++)
    {
        if(msg.at(i).isEmpty())
        {
            SettingData Data;
            Data.type = typeList.at(i);
            Data.name = "没有数据";
            Data.unit = "";
            Data.p = "";
            Data.value = 0;
            Setting_Data::Get()->SettingPushBack(Data);
        }
        else if(!msg.at(i).isEmpty())
        {
            QStringList str = Get_SettingStr(msg.at(i));
            SettingData Data;
            Data.type = typeList.at(i);
            Data.name = str.at(0);
            Data.unit = str.at(1);
            Data.p = str.at(2);
            Data.value = 0;
            Setting_Data::Get()->SettingPushBack(Data);
        }
    }
}

void SettingIni::Write_For_Ini()
{
    QList<MainData> MainList = Setting_Data::Get()->Get_MainList();
    for(int Count = 0; Count < MainList.size(); Count++)
    {
        if(MainList.at(Count).type == MainView1)
        {
            for(int i = 0; i < 8; i++)
            {
                Conf->setValue(QString("IndicatorLight/VISO_Lamp_%1a_ch").arg(i + 1),MainList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("IndicatorLight/VISO_Lamp_%1a_en").arg(i + 1),MainList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("IndicatorLight/VISO_Lamp_%1b").arg(i + 1),MainList.at(Count).PLCOutput.at(i));
            }
        }
        else if(MainList.at(Count).type == MainView2)
        {
            for(int i = 0; i < 6; i++)
            {
                Conf->setValue(QString("InformationDisplay/VISO_Lamp_%1_ch").arg(i + 1),MainList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("InformationDisplay/VISO_Lamp_%1_en").arg(i + 1),MainList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("InformationDisplay/VISO_Lamp_%1").arg(i + 1),MainList.at(Count).PLCOutput.at(i));
            }
        }
        else if(MainList.at(Count).type == MainView3)
        {
            for(int i = 0; i < 6; i++)
            {
                Conf->setValue(QString("RunCount/VISO_Lamp_%1_ch").arg(i + 1),MainList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("RunCount/VISO_Lamp_%1_en").arg(i + 1),MainList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("RunCount/VISO_Lamp_%1").arg(i + 1),MainList.at(Count).PLCOutput.at(i));
            }
        }
        else if(MainList.at(Count).type == MainView4)
        {
            for(int i = 0; i < 4; i++)
            {
                Conf->setValue(QString("Main/VISO_BTN1_%1a_ch").arg(i + 1),MainList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("Main/VISO_BTN1_%1a_en").arg(i + 1),MainList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("Main/VISO_BTN1_%1b").arg(i + 1),MainList.at(Count).PLCOutput.at(i));
                Conf->setValue(QString("Main/VISI_BTN1_%1b").arg(i + 1),MainList.at(Count).PLcInput.at(i));
            }
        }
        else if(MainList.at(Count).type == MainView5)
        {
            Conf->setValue("filepath/exe1",MainList.at(Count).strPaths.at(0));
        }
        else if(MainList.at(Count).type == MainView6)
        {
            for(int i = 0; i < 4; i++)
            {
                Conf->setValue(QString("filepath/exe%1").arg(i + 2),MainList.at(Count).strPaths.at(i));
            }
        }
    }

    QList<ManualData> ManualList = Setting_Data::Get()->Get_ManualList();
    for(int Count = 0; Count < ManualList.size(); Count++)
    {
        if(ManualList.at(Count).type == ManualView1)
        {
            for(int i = 0; i < 8; i++)
            {
                Conf->setValue(QString("ManualFun/VISO_BTN1_%1a_ch").arg(i + 1),ManualList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("ManualFun/VISO_BTN1_%1a_en").arg(i + 1),ManualList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("ManualFun/VISI_BTN1_%1b").arg(i + 1),ManualList.at(Count).PLcInput.at(i));
                Conf->setValue(QString("ManualFun/VISO_BTN1_%1b").arg(i + 1),ManualList.at(Count).PLCOutput.at(i));
            }
        }
        else if(ManualList.at(Count).type == ManualView2)
        {
            Conf->setValue(("ManualDisTance/VISI_STEP"),ManualList.at(Count).PLcInput.at(0));
            Conf->setValue(("ManualDisTance/VISO_STEP"),ManualList.at(Count).PLCOutput.at(0));
        }
        else if(ManualList.at(Count).type == ManualView3)
        {
            for(int i = 0; i < 4; i++)
            {
                Conf->setValue(QString("ManualModel/VISO_BTN1_%1a_ch").arg(i + 1),ManualList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("ManualModel/VISO_BTN1_%1a_en").arg(i + 1),ManualList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("ManualModel/VISI_BTN1_%1b").arg(i + 1),ManualList.at(Count).PLcInput.at(i));
            }
        }
        else if(ManualList.at(Count).type == ManualView4)
        {
            Conf->setValue(("Manualtag2/VISO_MARK_X_POS"),ManualList.at(Count).PLCOutput.at(0));
            Conf->setValue(("Manualtag2/VISO_MARK_Y_POS"),ManualList.at(Count).PLCOutput.at(1));
        }
        else if(ManualList.at(Count).type == ManualView5)
        {
            for(int i = 0; i < 2; i++)
            {
                Conf->setValue(QString("Manualtag/VISO_BTN1_MARK%1_ch").arg(i + 1),ManualList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("Manualtag/VISO_BTN1_MARK%1_en").arg(i + 1),ManualList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("Manualtag/VISI_BTN1_MARK%1").arg(i + 1),ManualList.at(Count).PLcInput.at(i));
            }
        }
    }

    QList<AutoData> AutoList = Setting_Data::Get()->Get_AutoList();
    for(int Count = 0; Count < AutoList.size(); Count++)
    {
        if(AutoList.at(Count).type == AutoView1)
        {
            for(int i = 0 ; i < 8; i++)
            {
                Conf->setValue(QString("ConnectButton2/VISO_BTN2_%1a_ch").arg(i + 1),AutoList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("ConnectButton2/VISO_BTN2_%1a_en").arg(i + 1),AutoList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("ConnectButton2/VISI_BTN2_%1b").arg(i + 1),AutoList.at(Count).PLcInput.at(i));
                Conf->setValue(QString("ConnectButton2/VISO_BTN2_%1b").arg(i + 1),AutoList.at(Count).PLCOutput.at(i));
            }
        }
        else if(AutoList.at(Count).type == AutoView2)
        {
            for(int i = 0; i < 8; i++)
            {
                Conf->setValue(QString("AutoRun/VISO_BTN%1_ch").arg(i + 1),AutoList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("AutoRun/VISO_BTN%1_en").arg(i + 1),AutoList.at(Count).EnglishName.at(i));
                Conf->setValue(QString("AutoRun/VISI_BTN%1").arg(i + 1),AutoList.at(Count).PLcInput.at(i));
                Conf->setValue(QString("AutoRun/VISO_BTN%1").arg(i + 1),AutoList.at(Count).PLCOutput.at(i));
            }
        }
    }

    QList<DataData> DataList = Setting_Data::Get()->Get_DataList();
    for(int Count = 0; Count < DataList.size(); Count++)
    {
        if(DataList.at(Count).type == DataView)
        {
            for(int i = 0; i < 8; i++)
            {
                Conf->setValue(QString("LaserLayerName/Layer%1_ch").arg(i + 1),DataList.at(Count).ChineseName.at(i));
                Conf->setValue(QString("LaserLayerName/Layer%1_en").arg(i + 1),DataList.at(Count).EnglishName.at(i));
            }
        }
        else if(DataList.at(Count).type == DataFun)
        {
            QList<bool> StateList = DataList.at(Count).State;
            Conf->setValue("DataFunc/leapfrog",StateList.at(0));
            Conf->setValue("DataFunc/NO_leapfrog",StateList.at(1));
            Conf->setValue("DataFunc/Fixedhigh_cut",StateList.at(2));
            Conf->setValue("DataFunc/Edge_search",StateList.at(3));
            Conf->setValue("DataFunc/Punch1",StateList.at(4));
            Conf->setValue("DataFunc/Punch2",StateList.at(5));
            Conf->setValue("DataFunc/Punch3",StateList.at(6));
            Conf->setValue("DataFunc/Pre_Punch",StateList.at(7));
            Conf->setValue("DataFunc/Feed",StateList.at(8));
            Conf->setValue("DataFunc/RateBtn",StateList.at(9));
            Conf->setValue("DataFunc/ProCount",StateList.at(10));
        }
    }

    QList<PLCMoData> PlcMoList = Setting_Data::Get()->Get_PLCMoList();
    for(int Count = 0; Count < PlcMoList.size(); Count++)
    {
        Conf->setValue(QString("PLCMonitor/GroupBox%1_Title").arg(Count + 1),PlcMoList.at(Count).title);
        Conf->setValue(QString("PLCMonitor/GroupBox%1_Enable").arg(Count + 1),PlcMoList.at(Count).state);
        for(int i = 0; i < 8; i++)
        {
            Conf->setValue(QString("PLCMonitor/GroupBox%1_Text_%2_ch").arg(Count + 1).arg(i + 1),PlcMoList.at(Count).ChineseList.at(i));
            Conf->setValue(QString("PLCMonitor/GroupBox%1_Text_%2_en").arg(Count + 1).arg(i + 1),PlcMoList.at(Count).EnglishList.at(i));
            Conf->setValue(QString("PLCMonitor/GroupBox%1_Text_%2_address").arg(Count + 1).arg(i + 1),PlcMoList.at(Count).PLCPathList.at(i));
        }
    }
}

