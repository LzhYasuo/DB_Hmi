#ifndef _DATA_SETTINGDBDATA_H
#define _DATA_SETTINGDBDATA_H

#include <QObject>
#include <QVariant>

struct DB_Data_Key_Value
{
    QString p;
    QVariant value;
};

struct DB_data_Key_Cut_Value
{
    QStringList p;
    QList<QVariant> value;
};

enum Setting_Type
{
    Setting_Global,
    Setting_Cutting,
    Setting_Perforated,
};

//全局
enum GlobalSettingType
{
    inifrogJump1,                   //无蛙跳上抬高度
    iniReturnStr,                  //加工结束返回工件起点
    iniFixedHightCutting1,          //Z轴高度
    iniFeeding1,                    //送料类型
    iniFeeding2,                    //送料速度
    iniFeeding3,                    //送料长度
    iniFeeding4,                    //送料次数
    inidefault1,                    //X轴刀缝优化
    inidefault2,                    //X轴刀缝补偿起点
    inidefault3,                    //45度刀缝补偿
    inidefault4,                    //90度刀缝补偿
    inidefault5,                    //135度刀缝补偿
    inidefault6,                    //强点射时间
    inidefault7,                    //强点射功率
    inidefault8,                    //弱点射时间
    inidefault9,                    //弱点射功率
    iniGlobalSettingType1,          //蛙跳
    iniGlobalSettingType2,          //
    iniGlobalSettingType3,          //
    iniGlobalSettingType4,          //
    iniGlobalSettingType5,          //
    iniGlobalSettingType6,          //
    iniGlobalSettingType7,          //
    iniGlobalSettingType8,          //
    iniGlobalSettingType9,          //
    iniGlobalSettingType10,         //
    iniGlobalSettingType11,         //
};

struct GlobalValue
{
    GlobalSettingType type;
    QString Text;
    QString unit;
    int max;
    int min;
    int decimalPoint;
    DB_Data_Key_Value PValue;
    QStringList ComboxList;
};

//切割
enum CuttingSettingType
{
    iniCuttingTableType1,
    iniCuttingTableType2,
    iniCuttingTableType3,
    iniCuttingTableType4,
    iniCuttingTableType5,
    iniCuttingTableType6,
    iniCuttingTableType7,
    iniCuttingTableType8,
    iniCuttingTableType9,
    iniCuttingTableType10,
    iniCuttingTableType11,
    iniCuttingTableType12,
    iniCuttingTableType13,
    iniCuttingTableType14,
    iniCuttingTableType15,
    iniCuttingTableType16,
    iniCuttingTableType17,
    iniCuttingTableType18,
    iniCuttingTableType19,
};

struct CuttingValue
{
    CuttingSettingType type;
    QString Add_Type;
    QString Text;
    QString unit;
    int max;
    int min;
    int decimalPoint;
    int Gui_Type;
    QList<DB_Data_Key_Value> PValue_List;
    QStringList ComboxList = QStringList();
};

//穿孔
enum PerforatedSettingType
{
    iniPerforatedSettingType1,
    iniPerforatedSettingType2,
    iniPerforatedSettingType3,
    iniPerforatedSettingType4,
    iniPerforatedSettingType5,
    iniPerforatedSettingType6,
    iniPerforatedSettingType7,
    iniPerforatedSettingType8,
    iniPerforatedSettingType9,
    iniPerforatedSettingType10,
    iniPerforatedSettingType11,
    iniPerforatedSettingType12,

    iniPerforatedSetting2Type1,
    iniPerforatedSetting2Type2,
    iniPerforatedSetting2Type3,
    iniPerforatedSetting2Type4,
    iniPerforatedSetting2Type5,
    iniPerforatedSetting2Type6,
    iniPerforatedSetting2Type7,
    iniPerforatedSetting2Type8,
    iniPerforatedSetting2Type9,
    iniPerforatedSetting2Type10,
    iniPerforatedSetting2Type11,
    iniPerforatedSetting2Type12,

    iniPerforatedSetting3Type1,
    iniPerforatedSetting3Type2,
    iniPerforatedSetting3Type3,
    iniPerforatedSetting3Type4,
    iniPerforatedSetting3Type5,
    iniPerforatedSetting3Type6,
    iniPerforatedSetting3Type7,
    iniPerforatedSetting3Type8,
    iniPerforatedSetting3Type9,
    iniPerforatedSetting3Type10,
    iniPerforatedSetting3Type11,
    iniPerforatedSetting3Type12,

};

struct PerforatedValue
{
    PerforatedSettingType type;
    QString Text;
    QString unit;
    int max;
    int min;
    int decimalPoint;
    DB_Data_Key_Value PValue;
    QStringList ComboxList;
};

class DataDbdata;
class Data_Setting;
class Data_SettingDbData : public QObject
{
    Q_OBJECT
public:
    //全局参数的 可以3个模式通用接口 只是想着那在程序中太长了,所以分三个接口 理直气壮！
    int Get_GlobalMax(GlobalSettingType);
    int Get_GlobalMin(GlobalSettingType);
    int Get_GlobalDecimal(GlobalSettingType);
    QString Get_GlobalText(GlobalSettingType);
    QString Get_GlobalUnit(GlobalSettingType);
    QString Get_GlobalP(GlobalSettingType);
    QVariant Get_GlobalValue(GlobalSettingType);
    QStringList Get_GlobalComboxList(GlobalSettingType);

    QStringList Get_GlobalPList();
    QVariantList Get_GlobalValueList();

    //PushBack
    void GlobalPush(GlobalValue);
    //Set
    void Set_GlobalPValue(QVariantList);
    void Set_GlobalValue(GlobalSettingType,QVariant);
#if 0
    void Set_GlbalMax(GlobalSettingType,int);
    void Set_GlobalMin(GlobalSettingType,int);
    void Set_GlobalDecimal(GlobalSettingType,int);
    void Set_GlobalText(GlobalSettingType,QString);
    void Set_GlobalUnit(GlobalSettingType,QString);
    void Set_GlobalP(GlobalSettingType,QString);
    void Set_GlobalValue(GlobalSettingType,QVariant);
    void Set_GlobalComboxList(GlobalSettingType,QStringList);
#endif

    //切割参数
    int Get_CuttingMax(CuttingSettingType type);
    int Get_CuttingMin(CuttingSettingType type);
    int Get_CuttingDecimal(CuttingSettingType type);
    int Get_CuttingGuiType(CuttingSettingType type);
    QString Get_CuttingText(CuttingSettingType type);
    QString Get_CuttingUnit(CuttingSettingType type);
    QString Get_CuttingP(CuttingSettingType type,QVariant value);
    QVariant Get_CuttingValue(CuttingSettingType type,QString key);
    QStringList Get_CuttingComboxList(CuttingSettingType type);

    int Get_CuttingMax(int index);
    int Get_CuttingMin(int index);
    int Get_CuttingDecimal(int index);
    int Get_CuttingGuiType(int index);
    QString Get_CuttingText(int index);
    QString Get_CuttingUnit(int index);
    QString Get_CuttingP(int index,QVariant value);
    QVariant Get_CuttingValue(int index,QString key);
    QStringList Get_CuttingComboxList(int index);

    QList<int> Get_CuttingListMax();
    QList<int> Get_CuttingListMin();
    QList<int> Get_CuttingListDecimal();
    QList<int> Get_CuttingListGuiType();
    QStringList Get_CuttingListText();
    QStringList Get_CuttingListUnit();
    QStringList Get_CuttingListP(CuttingSettingType type);
    QList<QVariant> Get_CuttingListValue(CuttingSettingType type);
    QList<QStringList> Get_CuttingComboxListList();

    QStringList Get_CuttingListP();
    QVariantList Get_CuttingListValue();
    QVariant Get_CuttingValue(int index,int index1);
    //pushBack
    void CuttingPush(CuttingValue);

    //切割参数更多的值
    QString Add_CuttingType();
    //切割参数的最大数量
    int Get_Max_Cutting_num();

    //Set
    void Set_CuttingPValue(QVariantList msg);
    void Set_CuttingValue(CuttingSettingType,QVariantList);
    void Set_CuttingValue(int index,QVariantList);
    void Set_CuttingValue(int index,int index1,QVariant);
#if 0
    void Set_CuttingMax(CuttingSettingType type,int value);
    void Set_CuttingMin(CuttingSettingType type,int value);
    void Set_CuttingDecimal(CuttingSettingType type,int value);
    void Set_CuttingText(CuttingSettingType type,QString value);
    void Set_CuttingUnit(CuttingSettingType type,QString value);
    void Set_CuttingP(CuttingSettingType type,QVariant value,QString p);
    void Set_CuttingValue(CuttingSettingType type,QString p,QVariant value);
    void Set_CuttingComboxList(CuttingSettingType,QStringList value);

//    void Set_CuttingP(CuttingSettingType type,QStringList p);
//    void Set_CuttingValue(CuttingSettingType type,QList<QVariant> valueList);
#endif
    //穿孔参数
    int Get_PerforatedMax(PerforatedSettingType type);
    int Get_PerforatedMin(PerforatedSettingType type);
    int Get_PerforatedDecimal(PerforatedSettingType type);
    QString Get_PerforatedText(PerforatedSettingType type);
    QString Get_PerforatedUnit(PerforatedSettingType type);
    QString Get_PerforatedP(PerforatedSettingType type);
    QVariant Get_PerforatedValue(PerforatedSettingType type);
    QStringList Get_PerforatedComboxList(PerforatedSettingType type);

    QStringList Get_PerforatedPList();
    QVariantList Get_PerforatedValueList();

    //Data状态
    void PushDataState(QList<bool> s) {DataState = s;}
    QList<bool> PopDataState() {return DataState;}

    //pushback
    void PerforatedPush(PerforatedValue);
    //Set
    void Set_PerforatedPValue(QVariantList);
    void Set_PerforatedValue(PerforatedSettingType,QVariant);
#if 0
    void Set_PerforatedMax(PerforatedSettingType type,int value);
    void Set_PerforatedMin(PerforatedSettingType type,int value);
    void Set_PerforatedDecimal(PerforatedSettingType type,int value);
    void Set_PerforatedText(PerforatedSettingType type,QString value);
    void Set_PerforatedUnit(PerforatedSettingType type,QString value);
    void Set_PerforatedP(PerforatedSettingType type,QString value);
    void Set_PerforatedValue(PerforatedSettingType type,QVariant value);
    void Set_PerforatedComboxList(PerforatedSettingType type,QStringList value);
#endif

    //单例模式
    static Data_SettingDbData* Get();
public slots:
    //把数据写入数据库
    void DB_Write_into();
    //把数据写入Ini
    void Ini_Write_into(QString Text,int Max,int Min,int Decimal,int GuiType,QStringList PList,QStringList ComboList);
    //Ini数据删除
    void Ini_Delete_into(QStringList msg);
    //数据库另存为
    void DB_File_SaveAS(QString);
    //把数据写入到CNC
    void DB_Send_CncPlc();
private:
    Data_SettingDbData();
    ~Data_SettingDbData();

signals:
    //删除ini数据
    void Delete_into_ini_Signal(QStringList);
    //写入ini数据
    void Write_into_ini_Signal(QString Text,int Max,int Min,int Decimal,int GuiType,QStringList PList,QStringList comboList);
    //写入初始化的数据
    void Write_into_DB_Signal(QList<QStringList>,QList<QVariantList>);
    //
    void Save_As_DB_Signal(QString);

    //刷新全局变量
    void Refursh_Global();
    //刷新穿孔变量
    void Refursh_Perforated();
    //刷新切割变量
    void Refursh_Cutting();
private:
    QList<GlobalValue> GlobalList;
    QList<CuttingValue> CuttingList;
    QList<PerforatedValue> PerforatedList;

    QList<bool> DataState;
};


#endif //_DATA_SETTINGDBDATA_H
