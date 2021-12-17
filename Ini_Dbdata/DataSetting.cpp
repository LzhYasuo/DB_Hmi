#include "DataSetting.h"
#include <QSettings>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>

#include "Public/Public_Function.h"
#include "Data_SettingDbData.h"
#include "Public/Public_Function.h"

Data_Setting::Data_Setting()
{
    this->connect(Data_SettingDbData::Get(),&Data_SettingDbData::Write_into_ini_Signal,this,&Data_Setting::Write_into_ini_Slot);
    this->connect(Data_SettingDbData::Get(),&Data_SettingDbData::Delete_into_ini_Signal,this,&Data_Setting::Delete_into_ini_Slot);
    InitGlobalList();
    InitCuttingList();
    InitPerforatedList();
    InitDataState();
}

Data_Setting::~Data_Setting()
{

}

void Data_Setting::InitGlobalList()
{
    //全局变量列表初始化
    //不排除为配置文件不存在的情况
    //所以在找不到配置文件的时候给一个初始化值也不要让程序崩溃
    QSettings GConfig_Settings("C:\\PACnc\\DBHMI\\cfg\\GlobalConfigurationFile.ini",QSettings::IniFormat);
    GConfig_Settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    //蛙跳
    QStringList frogJump = Get_SettingStr(GConfig_Settings.value("No_frog_leaped_to_the_height").toString());
    //返回设置
    QStringList ReturnSet = Get_SettingStr(GConfig_Settings.value("ReturnSet=").toString());
    //定高切割
    QStringList ZAxisHeight = Get_SettingStr(GConfig_Settings.value("The_Z_axis_is_highly").toString());
    //送料设置
    QStringList FeedingType = Get_SettingStr(GConfig_Settings.value("FeedingType").toString());
    QStringList FeedingSpend = Get_SettingStr(GConfig_Settings.value("Feedingspeed").toString());
    QStringList FeedingLenght = Get_SettingStr(GConfig_Settings.value("FeedingLength").toString());
    QStringList FeedingNum = Get_SettingStr(GConfig_Settings.value("FeedingNum").toString());
    //默认设置
    QStringList default_Settings1 = Get_SettingStr(GConfig_Settings.value("default_Settings1").toString());
    QStringList default_Settings2 = Get_SettingStr(GConfig_Settings.value("default_Settings2").toString());
    QStringList default_Settings3 = Get_SettingStr(GConfig_Settings.value("default_Settings3").toString());
    QStringList default_Settings4 = Get_SettingStr(GConfig_Settings.value("default_Settings4").toString());
    QStringList default_Settings5 = Get_SettingStr(GConfig_Settings.value("default_Settings5").toString());
    QStringList default_Settings6 = Get_SettingStr(GConfig_Settings.value("default_Settings6").toString());
    QStringList default_Settings7 = Get_SettingStr(GConfig_Settings.value("default_Settings7").toString());
    QStringList default_Settings8 = Get_SettingStr(GConfig_Settings.value("default_Settings8").toString());
    QStringList default_Settings9 = Get_SettingStr(GConfig_Settings.value("default_Settings9").toString());
    //蛙跳
    QStringList GlobalSetting1 = Get_SettingStr(GConfig_Settings.value("The_frog_jumps_no_distance").toString());
    QStringList GlobalSetting2 = Get_SettingStr(GConfig_Settings.value("Leap_frog_minimum_height").toString());
    QStringList GlobalSetting3 = Get_SettingStr(GConfig_Settings.value("Leap_frog_maximum_height").toString());
    QStringList GlobalSetting4 = Get_SettingStr(GConfig_Settings.value("Leap_frog_to_a_safe_height").toString());
    QStringList GlobalSetting5 = Get_SettingStr(GConfig_Settings.value("Leap_frog_to_a_placement_height").toString());
    //寻边
    QStringList GlobalSetting6 = Get_SettingStr(GConfig_Settings.value("EdgeFunction1").toString());
    QStringList GlobalSetting7 = Get_SettingStr(GConfig_Settings.value("EdgeFunction2").toString());
    QStringList GlobalSetting8 = Get_SettingStr(GConfig_Settings.value("EdgeFunction3").toString());
    QStringList GlobalSetting9 = Get_SettingStr(GConfig_Settings.value("EdgeFunction4").toString());
    QStringList GlobalSetting10 = Get_SettingStr(GConfig_Settings.value("EdgeFunction5").toString());
    QStringList GlobalSetting11 = Get_SettingStr(GConfig_Settings.value("EdgeFunction6").toString());


    //防止有脑瘫改了配置文件导致at程序崩溃 给他提示并且初始化
    //问:这一步有必要吗?
    //答:你的对你的程序负责
    if(frogJump.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inifrogJump1,"蛙跳无效","mm",1000,0,3,DB_Data_Key_Value{"P921",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inifrogJump1,frogJump.at(0),frogJump.at(1),frogJump.at(2).toInt(),
                                         frogJump.at(3).toInt(),frogJump.at(4).toInt(),DB_Data_Key_Value{frogJump.at(5),0},QStringList()});
    }
    //返回设置1
    if(ReturnSet.size() < 5)
    {
        QStringList str;
        str << "加工结束返回工件起点" << "加工结束返回机床原点" << "加工结束返回设置点（G59）" << "加工结束抬起";
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniReturnStr,"","",0,0,0,DB_Data_Key_Value{"P950",0},str});
    }
    else
    {
        QStringList str;
        str << ReturnSet.at(0) << ReturnSet.at(1) << ReturnSet.at(2) << ReturnSet.at(3);
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniReturnStr,"","",0,0,0,DB_Data_Key_Value{ReturnSet.at(4),0},str});
    }
    //定高切割1
    if(ZAxisHeight.size() < 5)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFixedHightCutting1,"Z轴高度","",1000,-1000,3,DB_Data_Key_Value{"P927",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFixedHightCutting1,ZAxisHeight.at(0),"",ZAxisHeight.at(1).toInt(),
                                         ZAxisHeight.at(2).toInt(),ZAxisHeight.at(3).toInt(),DB_Data_Key_Value{ZAxisHeight.at(4),0},QStringList()});
    }
    //送料设置1
    if(FeedingType.size() < 4)
    {
        QStringList str;
        str << "单板送料" << "连续送料";
        GlobalValue val;
        val.type = iniFeeding1;
        val.ComboxList = str;
        val.Text = "送料类型";
        val.PValue.p = "P941";
        val.PValue.value = 0;
        Data_SettingDbData::Get()->GlobalPush(val);
    }
    else
    {
        QStringList str;
        str << FeedingType.at(1) << FeedingType.at(2);
        GlobalValue val;
        val.type = iniFeeding1;
        val.ComboxList = str;
        val.Text = FeedingType.at(0);
        val.PValue.p = FeedingType.at(3);
        val.PValue.value = 0 ;
        Data_SettingDbData::Get()->GlobalPush(val);
    }
    //送料设置2
    if(FeedingSpend.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFeeding2,"送料速度","米/分",1000,0,2,DB_Data_Key_Value{"P942",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFeeding2,FeedingSpend.at(0),FeedingSpend.at(1),FeedingSpend.at(2).toInt()
                                         ,FeedingSpend.at(4).toInt(),FeedingSpend.at(4).toInt(),DB_Data_Key_Value{FeedingSpend.at(5),0},QStringList()});
    }
    //送料模式3
    if(FeedingLenght.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFeeding3,"送料长度","mm",1000,0,2,DB_Data_Key_Value{"P943",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFeeding3,FeedingLenght.at(0),FeedingLenght.at(1),FeedingLenght.at(2).toInt()
                                         ,FeedingLenght.at(4).toInt(),FeedingLenght.at(4).toInt(),DB_Data_Key_Value{FeedingLenght.at(5),0},QStringList()});
    }
    //送料模式4
    if(FeedingNum.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFeeding4,"送料次数","mm",1000,0,2,DB_Data_Key_Value{"P944",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniFeeding4,FeedingNum.at(0),FeedingNum.at(1),FeedingNum.at(2).toInt()
                                         ,FeedingNum.at(4).toInt(),FeedingNum.at(4).toInt(),DB_Data_Key_Value{FeedingNum.at(5),0},QStringList()});
    }
    //默认设置1
    if(default_Settings1.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault1,"X轴刀缝优化","mm",3,-3,3,DB_Data_Key_Value{"P901",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault1,default_Settings1.at(0),default_Settings1.at(1),default_Settings1.at(2).toInt()
                                         ,default_Settings1.at(3).toInt(),default_Settings1.at(4).toInt(),DB_Data_Key_Value{default_Settings1.at(5),0},QStringList()});
    }
    //默认设置2
    if(default_Settings1.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault2,"X轴刀缝补偿起点","mm",1200,0,0,DB_Data_Key_Value{"P902",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault2,default_Settings2.at(0),default_Settings2.at(1),default_Settings2.at(2).toInt()
                                         ,default_Settings2.at(3).toInt(),default_Settings2.at(4).toInt(),DB_Data_Key_Value{default_Settings2.at(5),0},QStringList()});
    }
    //默认设置3
    if(default_Settings3.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault3,"45度刀缝补偿","mm",2,-2,3,DB_Data_Key_Value{"P903",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault3,default_Settings3.at(0),default_Settings3.at(1),default_Settings3.at(2).toInt()
                                         ,default_Settings3.at(3).toInt(),default_Settings3.at(4).toInt(),DB_Data_Key_Value{default_Settings3.at(5),0},QStringList()});
    }
    //默认设置4
    if(default_Settings4.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault4,"90度刀缝补偿","mm",2,-2,3,DB_Data_Key_Value{"P904",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault4,default_Settings4.at(0),default_Settings4.at(1),default_Settings4.at(2).toInt()
                                         ,default_Settings4.at(3).toInt(),default_Settings4.at(4).toInt(),DB_Data_Key_Value{default_Settings4.at(5),0},QStringList()});
    }
    //默认设置5
    if(default_Settings5.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault5,"135度刀缝补偿","mm",2,-2,3,DB_Data_Key_Value{"P905",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault5,default_Settings5.at(0),default_Settings5.at(1),default_Settings5.at(2).toInt()
                                         ,default_Settings5.at(3).toInt(),default_Settings5.at(4).toInt(),DB_Data_Key_Value{default_Settings5.at(5),0},QStringList()});
    }
    //默认设置6
    if(default_Settings6.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault6,"强点射时间","mm",10000,0,0,DB_Data_Key_Value{"P906",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault6,default_Settings6.at(0),default_Settings6.at(1),default_Settings6.at(2).toInt()
                                         ,default_Settings6.at(3).toInt(),default_Settings6.at(4).toInt(),DB_Data_Key_Value{default_Settings6.at(5),0},QStringList()});
    }
    //默认设置7
    if(default_Settings7.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault7,"强点射功率","mm",100,0,1,DB_Data_Key_Value{"P907",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault7,default_Settings7.at(0),default_Settings7.at(1),default_Settings7.at(2).toInt()
                                         ,default_Settings7.at(3).toInt(),default_Settings7.at(4).toInt(),DB_Data_Key_Value{default_Settings7.at(5),0},QStringList()});
    }
    //默认设置8
    if(default_Settings8.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault8,"弱点射时间","mm",10000,0,0,DB_Data_Key_Value{"P908",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault8,default_Settings8.at(0),default_Settings8.at(1),default_Settings8.at(2).toInt()
                                         ,default_Settings8.at(3).toInt(),default_Settings8.at(4).toInt(),DB_Data_Key_Value{default_Settings8.at(5),0},QStringList()});
    }
    //默认设置9
    if(default_Settings9.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault9,"弱点射功率","%",100,0,1,DB_Data_Key_Value{"P909",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{inidefault9,default_Settings9.at(0),default_Settings9.at(1),default_Settings9.at(2).toInt()
                                         ,default_Settings9.at(3).toInt(),default_Settings9.at(4).toInt(),DB_Data_Key_Value{default_Settings9.at(5),0},QStringList()});
    }
    //蛙跳1
    if(GlobalSetting1.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType1,"蛙跳无效距离","mm",1000,0,3,DB_Data_Key_Value{"P921",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType1,GlobalSetting1.at(0),GlobalSetting1.at(1),GlobalSetting1.at(2).toInt()
                                         ,GlobalSetting1.at(3).toInt(),GlobalSetting1.at(4).toInt(),DB_Data_Key_Value{GlobalSetting1.at(5),0},QStringList()});
    }
    //蛙跳2
    if(GlobalSetting2.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType2,"蛙跳最小高度","mm",1000,0,3,DB_Data_Key_Value{"P922",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType2,GlobalSetting2.at(0),GlobalSetting2.at(1),GlobalSetting2.at(2).toInt()
                                         ,GlobalSetting2.at(3).toInt(),GlobalSetting2.at(4).toInt(),DB_Data_Key_Value{GlobalSetting2.at(5),0},QStringList()});
    }
    //蛙跳3
    if(GlobalSetting3.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType3,"蛙跳最大高度","mm",1000,0,3,DB_Data_Key_Value{"P923",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType3,GlobalSetting3.at(0),GlobalSetting3.at(1),GlobalSetting3.at(2).toInt()
                                         ,GlobalSetting3.at(3).toInt(),GlobalSetting3.at(4).toInt(),DB_Data_Key_Value{GlobalSetting3.at(5),0},QStringList()});
    }
    //蛙跳4
    if(GlobalSetting4.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType4,"蛙跳安全高度","mm",1000,0,3,DB_Data_Key_Value{"P924",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType4,GlobalSetting4.at(0),GlobalSetting4.at(1),GlobalSetting4.at(2).toInt()
                                         ,GlobalSetting4.at(3).toInt(),GlobalSetting4.at(4).toInt(),DB_Data_Key_Value{GlobalSetting4.at(5),0},QStringList()});
    }
    //蛙跳5
    if(GlobalSetting5.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType5,"蛙跳落点高度","mm",1000,0,3,DB_Data_Key_Value{"P925",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType5,GlobalSetting5.at(0),GlobalSetting5.at(1),GlobalSetting5.at(2).toInt()
                                         ,GlobalSetting5.at(3).toInt(),GlobalSetting5.at(4).toInt(),DB_Data_Key_Value{GlobalSetting5.at(5),0},QStringList()});
    }
    //寻边1
    if(GlobalSetting6.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType6,"LX寻边长度","mm",100000,-100000,3,DB_Data_Key_Value{"P931",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType6,GlobalSetting6.at(0),GlobalSetting6.at(1),GlobalSetting6.at(2).toInt()
                                         ,GlobalSetting6.at(3).toInt(),GlobalSetting6.at(4).toInt(),DB_Data_Key_Value{GlobalSetting6.at(5),0},QStringList()});
    }
    //寻边2
    if(GlobalSetting7.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType7,"LY寻边长度","mm",100000,-100000,3,DB_Data_Key_Value{"P932",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType7,GlobalSetting7.at(0),GlobalSetting7.at(1),GlobalSetting7.at(2).toInt()
                                         ,GlobalSetting7.at(3).toInt(),GlobalSetting7.at(4).toInt(),DB_Data_Key_Value{GlobalSetting7.at(5),0},QStringList()});
    }
    //寻边3
    if(GlobalSetting8.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType8,"X原点纠正","mm",1000,-1000,3,DB_Data_Key_Value{"P933",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType8,GlobalSetting8.at(0),GlobalSetting8.at(1),GlobalSetting8.at(2).toInt()
                                         ,GlobalSetting8.at(3).toInt(),GlobalSetting8.at(4).toInt(),DB_Data_Key_Value{GlobalSetting8.at(5),0},QStringList()});
    }
    //寻边4
    if(GlobalSetting9.size() < 6)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType9,"Y原点纠正","mm",1000,-1000,3,DB_Data_Key_Value{"P934",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType9,GlobalSetting9.at(0),GlobalSetting9.at(1),GlobalSetting9.at(2).toInt()
                                         ,GlobalSetting9.at(3).toInt(),GlobalSetting9.at(4).toInt(),DB_Data_Key_Value{GlobalSetting9.at(5),0},QStringList()});
    }
    //寻边5
    if(GlobalSetting10.size() < 2)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType10,"寻边使能","",0,0,0,DB_Data_Key_Value{"P910",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType10,GlobalSetting10.at(0),"",0,0,0,DB_Data_Key_Value{GlobalSetting10.at(1),0},QStringList()});
    }
    //寻边6
    if(GlobalSetting11.size() < 2)
    {
        Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType11,"角度使能","",0,0,0,DB_Data_Key_Value{"P911",0},QStringList()});
    }
    else
    {
       Data_SettingDbData::Get()->GlobalPush(GlobalValue{iniGlobalSettingType11,GlobalSetting11.at(0),"",0,0,0,DB_Data_Key_Value{GlobalSetting11.at(1),0},QStringList()});
    }
}

void Data_Setting::InitCuttingList()
{
    QSettings GConfig_Settings("C:\\PACnc\\DBHMI\\cfg\\CuttingCongigurationFile.ini",QSettings::IniFormat);
    GConfig_Settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    //切割变量列表初始化
    //不排除为配置文件不存在的情况
    //所以在找不到配置文件的时候给一个初始化值也不要让程序崩溃
    QStringList CuttingTablNammList = Get_SettingStr(GConfig_Settings.value("CuttingTableName").toString());
    QStringList CuttingP1List = Get_SettingStr(GConfig_Settings.value("CuttingMarkP").toString());
    QStringList CuttingP2List = Get_SettingStr(GConfig_Settings.value("CuttingLayerofbladeP1").toString());
    QStringList CuttingP3List = Get_SettingStr(GConfig_Settings.value("CuttingLayerofbladeP2").toString());
    QStringList CuttingP4List = Get_SettingStr(GConfig_Settings.value("CuttingLayerofbladeP3").toString());
    QStringList CuttingP5List = Get_SettingStr(GConfig_Settings.value("CuttingLinePressingLayer1").toString());
    QStringList CuttingP6List = Get_SettingStr(GConfig_Settings.value("CuttingLinePressingLayer2").toString());
    QStringList CuttingP7List = Get_SettingStr(GConfig_Settings.value("CuttingFrame1").toString());
    QStringList CuttingP8List = Get_SettingStr(GConfig_Settings.value("CuttingFrame2").toString());
    QList<QStringList> CuttingDefault = Get_SettingStrList(GConfig_Settings.value("CuttingDefault").toString());

    QStringList CuttingTabInitName;
    QStringList CuttingPInit1;
    QStringList CuttingPInit2;
    QStringList CuttingPInit3;
    QStringList CuttingPInit4;
    QStringList CuttingPInit5;
    QStringList CuttingPInit6;
    QStringList CuttingPInit7;
    QStringList CuttingPInit8;
    QList<QStringList> CuttingDefaultInit;
    CuttingTabInitName << "切割速度[mm/min]" << "切割功率(%)" << "割缝起头参数" << "启动功率[%]" << "爬坡起始功率[%]" << "爬坡时间[ms]"
                       << "延时开光[ms]" << "割缝结尾参数" << "关光延时[ms]" << "关光功率[%]" << "其他参数" << "抬枪高度[mm]" << "加速度[%]"
                       << "圆弧精度[mm]" << "拐弯精度[mm]" << "选择功能" << "脉冲选择" << "穿孔模式" << "焦点选择";
    CuttingPInit1 << "P101" << "P102"<<"P103"<<"P104"<<"P105"<<"P106"<<"P107"<<"P108"<<"P109"<<"P110"
                     <<"P111"<<"P112"<<"P113"<<"P114"<<"P115"<<"P116"<<"P117"<<"P118"<<"P119";
    CuttingPInit2 << "P201" << "P202"<<"P203"<<"P204"<<"P205"<<"P206"<<"P207"<<"P208"<<"P209"<<"P210"
                  <<"P211"<<"P212"<<"P213"<<"P214"<<"P215"<<"P216"<<"P217"<<"P218"<<"P219";
    CuttingPInit3 << "P301" << "P302"<<"P303"<<"P304"<<"P305"<<"P306"<<"P307"<<"P308"<<"P309"<<"P310"
                  <<"P311"<<"P312"<<"P313"<<"P314"<<"P315"<<"P316"<<"P317"<<"P318"<<"P319";
    CuttingPInit4 << "P401" << "P402"<<"P403"<<"P404"<<"P405"<<"P406"<<"4107"<<"P408"<<"P409"<<"P410"
                  <<"P411"<<"P412"<<"P413"<<"P414"<<"P415"<<"P416"<<"P417"<<"P418"<<"P419";
    CuttingPInit5 << "P501" << "P502"<<"P503"<<"P504"<<"P505"<<"P506"<<"P507"<<"P508"<<"P509"<<"P510"
                  <<"P511"<<"P512"<<"P513"<<"P514"<<"P515"<<"P516"<<"P517"<<"P518"<<"P519";
    CuttingPInit6 << "P601" << "P602"<<"P603"<<"P604"<<"P605"<<"P606"<<"P607"<<"P608"<<"P609"<<"P610"
                  <<"P611"<<"P612"<<"P613"<<"P614"<<"P615"<<"P616"<<"P617"<<"P618"<<"P619";
    CuttingPInit7 << "P701" << "P702"<<"P703"<<"P704"<<"P705"<<"P706"<<"P707"<<"P708"<<"P709"<<"P710"
                  <<"P711"<<"P712"<<"P713"<<"P714"<<"P715"<<"P716"<<"P717"<<"P718"<<"P719";
    CuttingPInit8 << "P801" << "P802"<<"P803"<<"P804"<<"P805"<<"P806"<<"P807"<<"P808"<<"P809"<<"P810"
                  <<"P811"<<"P812"<<"P813"<<"P814"<<"P815"<<"P816"<<"P817"<<"P818"<<"P819";
    QString msg = "100000:0:0:1*100:0:0:1*0:0:1:1*100:0:0:1*100:0:0:1*100000:0:0:1*100000:0:0:1*0:0:0:1*100000:0:0:1*100:0:0:1*0:0:0:1*50:0:0:1*100 "
                  ":1:0:1*1:0.005:3:2*1:0.005:3:2*50000:0:0:1*连续波:门脉冲:强脉冲:3*不穿孔:穿孔:3*焦点一:焦点二:焦点三:焦点四:3";
    CuttingDefaultInit = Get_SettingStrList(msg);

    QList<CuttingSettingType> enumlist;
    enumlist << iniCuttingTableType1 << iniCuttingTableType2 << iniCuttingTableType3 << iniCuttingTableType4 << iniCuttingTableType5
             << iniCuttingTableType6 << iniCuttingTableType7 << iniCuttingTableType8 << iniCuttingTableType9 << iniCuttingTableType10
             << iniCuttingTableType11 << iniCuttingTableType12 << iniCuttingTableType13 << iniCuttingTableType14 << iniCuttingTableType15
             << iniCuttingTableType16 << iniCuttingTableType17 << iniCuttingTableType18 << iniCuttingTableType19;

    //如果不对称会造成崩溃 至于优化的方法我建议就是把配置文件的值一个个写
    //然后添加到QStringLabel Setting获取的值为空也不会对程序造成影响
    if(CuttingDefault.size() == 0 || !((CuttingTablNammList.size() == CuttingP1List.size()) && (CuttingP1List.size() == CuttingP2List.size()) && (CuttingP2List.size() == CuttingP3List.size())
        &&(CuttingP3List.size() == CuttingP4List.size()) && (CuttingP4List.size() == CuttingP5List.size()) && (CuttingP5List.size() == CuttingP6List.size()) &&
        (CuttingP6List.size() == CuttingP7List.size()) && (CuttingP7List.size() == CuttingP8List.size()) && (CuttingP8List.size() == CuttingDefault.size())))
    {
        isOpen = false;
        CuttingTablNammList = CuttingTabInitName;
        CuttingP1List = CuttingPInit1;
        CuttingP2List = CuttingPInit2;
        CuttingP3List = CuttingPInit3;
        CuttingP4List = CuttingPInit4;
        CuttingP5List = CuttingPInit5;
        CuttingP6List = CuttingPInit6;
        CuttingP7List = CuttingPInit7;
        CuttingP8List = CuttingPInit8;
        CuttingDefault = CuttingDefaultInit;
    }

    //赋值
    for(int i = 0; i< CuttingTablNammList.size(); i++)
    {
        CuttingValue val;
        val.Text = CuttingTablNammList.at(i);
        val.Gui_Type = CuttingDefault.at(i).last().toInt();
        if(i >= 19)
            val.Add_Type = Data_SettingDbData::Get()->Add_CuttingType();
        else
            val.type = enumlist.at(i);

        QList<DB_Data_Key_Value> PValueList;
        QStringList PList;
        PList << CuttingP1List.at(i) << CuttingP2List.at(i) << CuttingP3List.at(i) << CuttingP4List.at(i)
              << CuttingP5List.at(i) << CuttingP6List.at(i) << CuttingP7List.at(i) << CuttingP8List.at(i);
        for(int i = 0; i < PList.size(); i++)
        {
            DB_Data_Key_Value val;
            val.p = PList.at(i);
            val.value = 0;
            PValueList.push_back(val);
        }
        val.PValue_List = PValueList;
        if(val.Gui_Type == 1 || val.Gui_Type == 2)
        {
            //最大值
            val.max = CuttingDefault.at(i).at(0).toInt();
            //最小值
            val.min = CuttingDefault.at(i).at(1).toInt();
            //小数点
            val.decimalPoint = CuttingDefault.at(i).at(2).toInt();
        }
        else if(val.Gui_Type == 3)
        {
            QStringList strList;
            for(int count = 0; count < CuttingDefault.at(i).size() - 1; count++)
            {
                strList.push_back(CuttingDefault.at(i).at(count));
            }
            val.ComboxList = strList;
        }
        Data_SettingDbData::Get()->CuttingPush(val);
    }

}

void Data_Setting::InitPerforatedList()
{
    QSettings GConfig_Settings("C:\\PACnc\\DBHMI\\cfg\\PerforatedConfigurationFile.ini",QSettings::IniFormat);
    GConfig_Settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    //穿孔时间ms
    QStringList PerforatedTime1 = Get_SettingStr(GConfig_Settings.value("PerforatedTime1").toString());
    QStringList PerforatedTime2 = Get_SettingStr(GConfig_Settings.value("PerforatedTime2").toString());
    QStringList PerforatedTime3 = Get_SettingStr(GConfig_Settings.value("PerforatedTime3").toString());
    //穿孔功率%
    QStringList PerforatedPower1 = Get_SettingStr(GConfig_Settings.value("PerforatedPower1").toString());
    QStringList PerforatedPower2 = Get_SettingStr(GConfig_Settings.value("PerforatedPower2").toString());
    QStringList PerforatedPower3 = Get_SettingStr(GConfig_Settings.value("PerforatedPower3").toString());
    QStringList PerforatedPower4 = Get_SettingStr(GConfig_Settings.value("PerforatedPower4").toString());
    //穿孔抬高
    QStringList PerforatedRaise1 = Get_SettingStr(GConfig_Settings.value("PerforatedRaise1").toString());
    QStringList PerforatedRaise2 = Get_SettingStr(GConfig_Settings.value("PerforatedRaise2").toString());
    QStringList PerforatedRaise3 = Get_SettingStr(GConfig_Settings.value("PerforatedRaise3").toString());
    QStringList PerforatedRaise4 = Get_SettingStr(GConfig_Settings.value("PerforatedRaise4").toString());
    QStringList PerforatedRaise5 = Get_SettingStr(GConfig_Settings.value("PerforatedRaise5").toString());

    //穿孔时间1
    if(PerforatedTime1.size() < 7)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType1,"穿孔时间ms","",10000,0,0,DB_Data_Key_Value{"P351",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type1,"穿孔时间ms","",10000,0,0,DB_Data_Key_Value{"P251",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type1,"穿孔时间ms","",10000,0,0,DB_Data_Key_Value{"P151",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType1,PerforatedTime1.at(0),"",PerforatedTime1.at(4).toInt(),
                                         PerforatedTime1.at(5).toInt(),PerforatedTime1.at(6).toInt(),DB_Data_Key_Value{PerforatedTime1.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type1,PerforatedTime1.at(0),"",PerforatedTime1.at(4).toInt(),
                                         PerforatedTime1.at(5).toInt(),PerforatedTime1.at(6).toInt(),DB_Data_Key_Value{PerforatedTime1.at(2),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type1,PerforatedTime1.at(0),"",PerforatedTime1.at(4).toInt(),
                                         PerforatedTime1.at(5).toInt(),PerforatedTime1.at(6).toInt(),DB_Data_Key_Value{PerforatedTime1.at(3),0},QStringList()});
    }
    //穿孔时间2
    if(PerforatedTime2.size() < 7)
    {
        QStringList val;
        val << "Air" << "O2" << "N2" << "H-N2";
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType2,"","",0,0,0,DB_Data_Key_Value{"P352",0},val});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type2,"","",0,0,0,DB_Data_Key_Value{"P252",0},val});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type2,"","",0,0,0,DB_Data_Key_Value{"P152",0},val});
    }
    else
    {
        QStringList val;
        val << PerforatedTime2.at(3) << PerforatedTime2.at(4) << PerforatedTime2.at(5) << PerforatedTime2.at(6);
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType2,"","",0,0,0,DB_Data_Key_Value{PerforatedTime2.at(0),0},val});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type2,"","",0,0,0,DB_Data_Key_Value{PerforatedTime2.at(1),0},val});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type2,"","",0,0,0,DB_Data_Key_Value{PerforatedTime2.at(2),0},val});
    }
    //穿孔时间3
    if(PerforatedTime3.size() < 6)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType3,"","",0,0,0,DB_Data_Key_Value{"P353",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type3,"","",0,0,0,DB_Data_Key_Value{"P253",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type3,"","",0,0,0,DB_Data_Key_Value{"P153",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType3,"","",PerforatedTime3.at(3).toInt(),
                                         PerforatedTime3.at(4).toInt(),PerforatedTime3.at(5).toInt(),DB_Data_Key_Value{PerforatedTime3.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type3,"","",PerforatedTime3.at(3).toInt(),
                                         PerforatedTime3.at(4).toInt(),PerforatedTime3.at(5).toInt(),DB_Data_Key_Value{PerforatedTime3.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type3,"","",PerforatedTime3.at(3).toInt(),
                                         PerforatedTime3.at(4).toInt(),PerforatedTime3.at(5).toInt(),DB_Data_Key_Value{PerforatedTime3.at(2),0},QStringList()});
    }

    //穿孔功率1
    if(PerforatedPower1.size() < 7)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType4,"穿孔功率%","",100,0,0,DB_Data_Key_Value{"P354",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type4,"穿孔功率%","",100,0,0,DB_Data_Key_Value{"P254",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type4,"穿孔功率%","",100,0,0,DB_Data_Key_Value{"P154",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType4,PerforatedPower1.at(0),"",PerforatedPower1.at(4).toInt(),
                                         PerforatedPower1.at(5).toInt(),PerforatedPower1.at(6).toInt(),DB_Data_Key_Value{PerforatedPower1.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type4,PerforatedPower1.at(0),"",PerforatedPower1.at(4).toInt(),
                                         PerforatedPower1.at(5).toInt(),PerforatedPower1.at(6).toInt(),DB_Data_Key_Value{PerforatedPower1.at(2),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type4,PerforatedPower1.at(0),"",PerforatedPower1.at(4).toInt(),
                                         PerforatedPower1.at(5).toInt(),PerforatedPower1.at(6).toInt(),DB_Data_Key_Value{PerforatedPower1.at(3),0},QStringList()});
    }

    //穿孔功率2
    if(PerforatedPower2.size() < 6)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType5,"","",0,0,0,DB_Data_Key_Value{"P355",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type5,"","",0,0,0,DB_Data_Key_Value{"P255",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type5,"","",0,0,0,DB_Data_Key_Value{"P155",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType5,"","",PerforatedPower2.at(3).toInt(),
                                         PerforatedPower2.at(4).toInt(),PerforatedPower2.at(5).toInt(),DB_Data_Key_Value{PerforatedPower2.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type5,"","",PerforatedPower2.at(3).toInt(),
                                         PerforatedPower2.at(4).toInt(),PerforatedPower2.at(5).toInt(),DB_Data_Key_Value{PerforatedPower2.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type5,"","",PerforatedPower2.at(3).toInt(),
                                         PerforatedPower2.at(4).toInt(),PerforatedPower2.at(5).toInt(),DB_Data_Key_Value{PerforatedPower2.at(2),0},QStringList()});
    }

    //穿孔功率3
    if(PerforatedPower3.size() < 6)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType6,"","",0,0,1,DB_Data_Key_Value{"P356",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type6,"","",0,0,1,DB_Data_Key_Value{"P256",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type6,"","",0,0,1,DB_Data_Key_Value{"P156",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType6,"","",PerforatedPower3.at(3).toInt(),
                                         PerforatedPower3.at(4).toInt(),PerforatedPower3.at(5).toInt(),DB_Data_Key_Value{PerforatedPower3.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type6,"","",PerforatedPower3.at(3).toInt(),
                                         PerforatedPower3.at(4).toInt(),PerforatedPower3.at(5).toInt(),DB_Data_Key_Value{PerforatedPower3.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type6,"","",PerforatedPower3.at(3).toInt(),
                                         PerforatedPower3.at(4).toInt(),PerforatedPower3.at(5).toInt(),DB_Data_Key_Value{PerforatedPower3.at(2),0},QStringList()});
    }

    //穿孔功率4
    if(PerforatedPower4.size() < 6)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType7,"","",0,0,1,DB_Data_Key_Value{"P357",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type7,"","",0,0,1,DB_Data_Key_Value{"P357",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type7,"","",0,0,1,DB_Data_Key_Value{"P357",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType7,"","",PerforatedPower4.at(3).toInt(),
                                         PerforatedPower4.at(4).toInt(),PerforatedPower4.at(5).toInt(),DB_Data_Key_Value{PerforatedPower4.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type7,"","",PerforatedPower4.at(3).toInt(),
                                         PerforatedPower4.at(4).toInt(),PerforatedPower4.at(5).toInt(),DB_Data_Key_Value{PerforatedPower4.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type7,"","",PerforatedPower4.at(3).toInt(),
                                         PerforatedPower4.at(4).toInt(),PerforatedPower4.at(5).toInt(),DB_Data_Key_Value{PerforatedPower4.at(2),0},QStringList()});
    }

    //穿孔抬高1
    if(PerforatedRaise1.size() < 7)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType8,"穿孔抬高","",4,1,0,DB_Data_Key_Value{"P358",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type8,"穿孔抬高","",4,1,0,DB_Data_Key_Value{"P258",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type8,"穿孔抬高","",4,1,0,DB_Data_Key_Value{"P158",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType8,PerforatedRaise1.at(0),"",PerforatedRaise1.at(4).toInt(),
                                         PerforatedRaise1.at(5).toInt(),PerforatedRaise1.at(6).toInt(),DB_Data_Key_Value{PerforatedRaise1.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type8,PerforatedRaise1.at(0),"",PerforatedRaise1.at(4).toInt(),
                                         PerforatedRaise1.at(5).toInt(),PerforatedRaise1.at(6).toInt(),DB_Data_Key_Value{PerforatedRaise1.at(2),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type8,PerforatedRaise1.at(0),"",PerforatedRaise1.at(4).toInt(),
                                         PerforatedRaise1.at(5).toInt(),PerforatedRaise1.at(6).toInt(),DB_Data_Key_Value{PerforatedRaise1.at(3),0},QStringList()});
    }

    //穿孔抬高2
    if(PerforatedRaise2.size() < 6)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType9,"","",0,0,1,DB_Data_Key_Value{"P359",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type9,"","",0,0,1,DB_Data_Key_Value{"P259",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type9,"","",0,0,1,DB_Data_Key_Value{"P159",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType9,"","",PerforatedRaise2.at(3).toInt(),
                                         PerforatedRaise2.at(4).toInt(),PerforatedRaise2.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise2.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type9,"","",PerforatedRaise2.at(3).toInt(),
                                         PerforatedRaise2.at(4).toInt(),PerforatedRaise2.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise2.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type9,"","",PerforatedRaise2.at(3).toInt(),
                                         PerforatedRaise2.at(4).toInt(),PerforatedRaise2.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise2.at(2),0},QStringList()});
    }

    //穿孔抬高3
    if(PerforatedRaise3.size() < 6)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType10,"","",0,0,1,DB_Data_Key_Value{"P360",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type10,"","",0,0,1,DB_Data_Key_Value{"P260",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type10,"","",0,0,1,DB_Data_Key_Value{"P160",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType10,"","",PerforatedRaise3.at(3).toInt(),
                                         PerforatedRaise3.at(4).toInt(),PerforatedRaise3.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise3.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type10,"","",PerforatedRaise3.at(3).toInt(),
                                         PerforatedRaise3.at(4).toInt(),PerforatedRaise3.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise3.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type10,"","",PerforatedRaise3.at(3).toInt(),
                                         PerforatedRaise3.at(4).toInt(),PerforatedRaise3.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise3.at(2),0},QStringList()});
    }

    //穿孔抬高4
    if(PerforatedRaise4.size() < 6)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType11,"","",0,0,0,DB_Data_Key_Value{"P361",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type11,"","",0,0,0,DB_Data_Key_Value{"P261",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type11,"","",0,0,0,DB_Data_Key_Value{"P161",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType11,"","",PerforatedRaise4.at(3).toInt(),
                                         PerforatedRaise4.at(4).toInt(),PerforatedRaise4.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise4.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type11,"","",PerforatedRaise4.at(3).toInt(),
                                         PerforatedRaise4.at(4).toInt(),PerforatedRaise4.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise4.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type11,"","",PerforatedRaise4.at(3).toInt(),
                                         PerforatedRaise4.at(4).toInt(),PerforatedRaise4.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise4.at(2),0},QStringList()});
    }

    //穿孔抬高5
    if(PerforatedRaise5.size() < 4)
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType12,"","",0,0,0,DB_Data_Key_Value{"P362",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type12,"","",0,0,0,DB_Data_Key_Value{"P262",0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type12,"","",0,0,0,DB_Data_Key_Value{"P162",0},QStringList()});
    }
    else
    {
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSettingType12,"","",PerforatedRaise5.at(3).toInt(),
                                         PerforatedRaise5.at(4).toInt(),PerforatedRaise5.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise5.at(0),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting2Type12,"","",PerforatedRaise5.at(3).toInt(),
                                         PerforatedRaise5.at(4).toInt(),PerforatedRaise5.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise5.at(1),0},QStringList()});
        Data_SettingDbData::Get()->PerforatedPush(PerforatedValue{iniPerforatedSetting3Type12,"","",PerforatedRaise5.at(3).toInt(),
                                         PerforatedRaise5.at(4).toInt(),PerforatedRaise5.at(5).toInt(),DB_Data_Key_Value{PerforatedRaise5.at(2),0},QStringList()});
    }
}

void Data_Setting::InitDataState()
{
    QSettings Conf("C:\\PACnc\\DBHMI\\cfg\\SettingConfiguration.ini",QSettings::IniFormat);
    Conf.setIniCodec(QTextCodec::codecForName("GB2312"));
    QList<bool> s;
    s << Conf.value("DataFunc/leapfrog").toBool() << Conf.value("DataFunc/NO_leapfrog").toBool() << Conf.value("DataFunc/Fixedhigh_cut").toBool()
              << Conf.value("DataFunc/Edge_search").toBool() << Conf.value("DataFunc/Punch1").toBool() << Conf.value("DataFunc/Punch2").toBool()
              << Conf.value("DataFunc/Punch3").toBool() << Conf.value("DataFunc/Pre_Punch").toBool() << Conf.value("DataFunc/Feed").toBool()
              << Conf.value("DataFunc/RateBtn").toBool() << Conf.value("DataFunc/ProCount").toBool();
    Data_SettingDbData::Get()->PushDataState(s);
}

QStringList Data_Setting::Get_SettingStr(QString str)
{
    QStringList msg;
    if(str.isEmpty())
        return msg;

    msg << str.split(":");
    return msg;
}

QStringList Data_Setting::Get_SettingStrStringList(QString str)
{
    QStringList msg;
    if(str.isEmpty())
        return msg;

    msg << str.split("*");
    return msg;
}

QList<QStringList> Data_Setting::Get_SettingStrList(QString str)
{
    QList<QStringList> msg;
    QStringList strList;
    if(str.isEmpty())
        return msg;
    strList << str.split("*");
    for(int i = 0; i < strList.size(); i++)
    {
        QStringList ary = Get_SettingStr(strList.at(i));
        msg.push_back(ary);
    }

    return msg;
}

void Data_Setting::Write_into_ini_Slot(QString Text,int Max,int Min,int Decimal,int GuiType,QStringList PList,QStringList ComboxList)
{
    if(!isOpen)
    {
        QMessageBox::information(nullptr,"抱歉","配置文件不存在或是配置文件参数不对等,无法为你添加行");
        return;
    }
    QSettings GConfig_Settings("C:\\PACnc\\DBHMI\\cfg\\CuttingCongigurationFile.ini",QSettings::IniFormat);
    GConfig_Settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    //切割变量列表初始化
    //不排除为配置文件不存在的情况
    //所以在找不到配置文件的时候给一个初始化值也不要让程序崩溃
    QString tableName = GConfig_Settings.value("CuttingTableName").toString();
    QString CuttingP1List = GConfig_Settings.value("CuttingMarkP").toString();
    QString CuttingP2List = GConfig_Settings.value("CuttingLayerofbladeP1").toString();
    QString CuttingP3List = GConfig_Settings.value("CuttingLayerofbladeP2").toString();
    QString CuttingP4List = GConfig_Settings.value("CuttingLayerofbladeP3").toString();
    QString CuttingP5List = GConfig_Settings.value("CuttingLinePressingLayer1").toString();
    QString CuttingP6List = GConfig_Settings.value("CuttingLinePressingLayer2").toString();
    QString CuttingP7List = GConfig_Settings.value("CuttingFrame1").toString();
    QString CuttingP8List = GConfig_Settings.value("CuttingFrame2").toString();
    QString CuttingDefault = GConfig_Settings.value("CuttingDefault").toString();

    QStringList OtherDBID = Data_SettingDbData::Get()->Get_GlobalPList();
    QStringList OtherDBID1 = Data_SettingDbData::Get()->Get_PerforatedPList();
    QStringList thisDBID = Data_SettingDbData::Get()->Get_CuttingListP();
    QStringList NameList = Data_SettingDbData::Get()->Get_CuttingListText();

    for(int i = 0; i < PList.size(); i++)
    {
        QStringList str;
        for(int z = 0; z < PList.size(); z++)
        {
            if(z == i)
                continue;
            str << PList.at(z);
        }
        if(!Public_Function::Contrast_List_Str(str,PList.at(i)))
        {
            QMessageBox::information(nullptr,"抱歉",QString("添加的P参数重复"));
            return;
        }
        if(!Public_Function::Contrast_List_Str(OtherDBID,"P" + PList.at(i)))
        {
            QMessageBox::information(nullptr,"抱歉",QString("当前列表索引中所在 %1 P参数,所以无法为你添加行").arg(ComboxList.at(i)));
            return;
        }
        if(!Public_Function::Contrast_List_Str(OtherDBID1,"P" + PList.at(i)))
        {
            QMessageBox::information(nullptr,"抱歉",QString("当前列表索引中所在 %1 P参数,所以无法为你添加行").arg(ComboxList.at(i)));
            return;
        }
        if(!Public_Function::Contrast_List_Str(thisDBID,"P" + PList.at(i)))
        {
            QMessageBox::information(nullptr,"抱歉",QString("当前列表索引中所在 %1 P参数,所以无法为你添加行").arg(ComboxList.at(i)));
            return;
        }
    }

    if(!Public_Function::Contrast_List_Str(NameList,Text))
    {
        QMessageBox::information(nullptr,"抱歉",QString("当前列表索引中所在 %1 名,所以无法为你添加行").arg(Text));
        return;
    }

    QString ComboxboxList = "*";
    for(int i = 0; i < ComboxList.size(); i++)
    {
        ComboxboxList += ComboxList.at(i) + ":";
    }
    ComboxboxList += "3";
    QString Default = "*" + QString::number(Max) + ":" + QString::number(Min) + ":" + QString::number(Decimal) + ":" + QString::number(GuiType);
    QString Name = ":" + Text;
    QString P1 = ":P" + PList.at(0);
    QString P2 = ":P" + PList.at(1);
    QString P3 = ":P" + PList.at(2);
    QString P4 = ":P" + PList.at(3);
    QString P5 = ":P" + PList.at(4);
    QString P6 = ":P" + PList.at(5);
    QString P7 = ":P" + PList.at(6);
    QString P8 = ":P" + PList.at(7);

    GConfig_Settings.setValue("CuttingTableName",tableName + Name);
    GConfig_Settings.setValue("CuttingMarkP",CuttingP1List + P1);
    GConfig_Settings.setValue("CuttingLayerofbladeP1",CuttingP2List + P2);
    GConfig_Settings.setValue("CuttingLayerofbladeP2",CuttingP3List + P3);
    GConfig_Settings.setValue("CuttingLayerofbladeP3",CuttingP4List + P4);
    GConfig_Settings.setValue("CuttingLinePressingLayer1",CuttingP5List + P5);
    GConfig_Settings.setValue("CuttingLinePressingLayer2",CuttingP6List + P6);
    GConfig_Settings.setValue("CuttingFrame1",CuttingP7List + P7);
    GConfig_Settings.setValue("CuttingFrame2",CuttingP8List + P8);

    if(GuiType == 3)
    {
        GConfig_Settings.setValue("CuttingDefault",CuttingDefault + ComboxboxList);
    }
    else if(GuiType == 1 || GuiType == 2)
    {
        GConfig_Settings.setValue("CuttingDefault",CuttingDefault + Default);
    }
}

void Data_Setting::Delete_Data_for_Ini(QString msg)
{
    int index = 0;
    QSettings GConfig_Settings("C:\\PACnc\\DBHMI\\cfg\\CuttingCongigurationFile.ini",QSettings::IniFormat);
    GConfig_Settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    QStringList CuttingTablNammList = Get_SettingStr(GConfig_Settings.value("CuttingTableName").toString());
    QStringList CuttingP1List = Get_SettingStr(GConfig_Settings.value("CuttingMarkP").toString());
    QStringList CuttingP2List = Get_SettingStr(GConfig_Settings.value("CuttingLayerofbladeP1").toString());
    QStringList CuttingP3List = Get_SettingStr(GConfig_Settings.value("CuttingLayerofbladeP2").toString());
    QStringList CuttingP4List = Get_SettingStr(GConfig_Settings.value("CuttingLayerofbladeP3").toString());
    QStringList CuttingP5List = Get_SettingStr(GConfig_Settings.value("CuttingLinePressingLayer1").toString());
    QStringList CuttingP6List = Get_SettingStr(GConfig_Settings.value("CuttingLinePressingLayer2").toString());
    QStringList CuttingP7List = Get_SettingStr(GConfig_Settings.value("CuttingFrame1").toString());
    QStringList CuttingP8List = Get_SettingStr(GConfig_Settings.value("CuttingFrame2").toString());
    QList<QStringList> CuttingDefault = Get_SettingStrList(GConfig_Settings.value("CuttingDefault").toString());
    QStringList CuttingDefaultSize = Get_SettingStrStringList(GConfig_Settings.value("CuttingDefault").toString());
    for(int i = 0; i < CuttingTablNammList.size(); i++)
    {
        if(msg == CuttingTablNammList.at(i))
        {
            index = i;
            break;
        }
    }
    QString tableName = ADD_Str_For_List(CuttingTablNammList,index,":");
    QString p1 = ADD_Str_For_List(CuttingP1List,index,":");
    QString p2 = ADD_Str_For_List(CuttingP2List,index,":");
    QString p3 = ADD_Str_For_List(CuttingP3List,index,":");
    QString p4 = ADD_Str_For_List(CuttingP4List,index,":");
    QString p5 = ADD_Str_For_List(CuttingP5List,index,":");
    QString p6 = ADD_Str_For_List(CuttingP6List,index,":");
    QString p7 = ADD_Str_For_List(CuttingP7List,index,":");
    QString p8 = ADD_Str_For_List(CuttingP8List,index,":");
    QString Default = ADD_Str_For_List(CuttingDefaultSize,index,"*");

    GConfig_Settings.setValue("CuttingTableName",tableName);
    GConfig_Settings.setValue("CuttingMarkP",p1);
    GConfig_Settings.setValue("CuttingLayerofbladeP1",p2);
    GConfig_Settings.setValue("CuttingLayerofbladeP2",p3);
    GConfig_Settings.setValue("CuttingLayerofbladeP3",p4);
    GConfig_Settings.setValue("CuttingLinePressingLayer1",p5);
    GConfig_Settings.setValue("CuttingLinePressingLayer2",p6);
    GConfig_Settings.setValue("CuttingFrame1",p7);
    GConfig_Settings.setValue("CuttingFrame2",p8);
    GConfig_Settings.setValue("CuttingDefault",Default);

}

QString Data_Setting::ADD_Str_For_List(QStringList list,int index,QString msg)
{
    QString Text;
    for(int i = 0; i < list.size(); i++)
    {
        if(index != list.size() - 1)
        {
            if(i == index)
                continue;
            if(i != list.size() - 1)
                Text += list.at(i) + msg;
            else if(i == list.size() - 1)
                Text += list.at(i);
        }
        else
        {
            if(i == index)
                continue;
            if(i != list.size() - 2)
                Text += list.at(i) + msg;
            else if(i == list.size() - 2)
                Text += list.at(i);
        }
    }
    return Text;
}

void Data_Setting::Delete_into_ini_Slot(QStringList str)
{
    if(!isOpen)
    {
        QMessageBox::information(nullptr,"抱歉","配置文件不存在或是配置文件参数不对等,无法为你删除行");
        return;
    }
    for(int i = 0; i < str.size(); i++)
    {
        Delete_Data_for_Ini(str.at(i));
    }
}
