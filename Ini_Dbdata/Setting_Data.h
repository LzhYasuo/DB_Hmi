#ifndef _SETTING_DATA_H_
#define _SETTING_DATA_H_


#include <QObject>
#include <QVariant>

enum SettingType
{
    Settingini1,
    Settingini2,
    Settingini3,
    Settingini4,
    Settingini5,
    Settingini6,
    Settingini7,
    Settingini8,
    Settingini9,
    Settingini10,
    Settingini11,
    Settingini12,
    Settingini13,
    Settingini14,
    Settingini15,
    Settingini16,
    Settingini17,
    Settingini18,
    Settingini19,
    Settingini20,
};

enum ViewType
{
    MainViewType,
    ManualViewType,
    AutoViewType,
    DataViewType,
    PLCMoViewType,
};

enum MainType
{
    MainNothing,
    MainView1,
    MainView2,
    MainView3,
    MainView4,
    MainView5,
    MainView6,

};

enum ManualType
{
    ManualNothing,
    ManualView1,
    ManualView2,
    ManualView3,
    ManualView4,
    ManualView5,
};

enum AutoType
{
    AutoNothing,
    AutoView1,
    AutoView2,
};

enum DataType
{
    DataNothing,
    DataView,
    DataFun,
};

enum PlcMoType
{
    PLCNothing,
    PlcMoView1,
    PlcMoView2,
    PlcMoView3,
    PlcMoView4,
    PlcMoView5,
    PlcMoView6,
    PlcMoView7,
    PlcMoView8,
    PLCTitleState,
};

struct MainData
{
    MainType type;
    QStringList Name;
    QStringList ChineseName;
    QStringList EnglishName;
    QStringList PLCOutput;
    QStringList PLcInput;
    QStringList strPaths;
};

struct ManualData
{
    ManualType type;
    QStringList Name;
    QStringList ChineseName;
    QStringList EnglishName;
    QStringList PLCOutput;
    QStringList PLcInput;
};

struct AutoData
{
    AutoType type;
    QStringList Name;
    QStringList ChineseName;
    QStringList EnglishName;
    QStringList PLCOutput;
    QStringList PLcInput;
};

struct DataData
{
    DataType type;
    QStringList Name;
    QStringList ChineseName;
    QStringList EnglishName;
    QList<bool> State;
};

struct PLCMoData
{
    PlcMoType type;
    QStringList Name;
    QStringList PLCPathList;
    QStringList ChineseList;
    QStringList EnglishList;
    bool state;
    QString title;
};

struct ModifyData
{
    ViewType type;      //类型
    int Table;          //具体的表
    int index;          //第几行
    int col;            //第几列
    QVariant Data;      //数据
};

struct SettingData
{
    SettingType type;
    QString name;
    QString unit;
    QString p;
    QVariant value;
};

class Setting_Data : public QObject
{
    Q_OBJECT
public:
    static Setting_Data* Get();
    //Main
    QList<QStringList> GET_FourData(ViewType,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);
    QList<QStringList> GET_ThreeData(ViewType,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);
    QList<QStringList> GET_TwoData(ViewType,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);
    QList<QStringList> GET_OneData(ViewType,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);
    QList<bool> Get_Data_Bool();
    bool Get_Plc_Bool(PlcMoType);
    QString Get_Plc_Title(PlcMoType);

    void Set_FourData(ViewType,QList<QStringList>,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);
    void Set_ThreeData(ViewType,QList<QStringList>,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);
    void Set_TwoData(ViewType,QList<QStringList>,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);
    void Set_OneData(ViewType,QList<QStringList>,MainType = MainNothing,ManualType = ManualNothing,AutoType = AutoNothing,
                          DataType = DataNothing,PlcMoType = PLCNothing);

    void MainPushBack(MainData d) { MainDataList.push_back(d);}
    void ManualPushBack(ManualData d) { ManualDataList.push_back(d);}
    void AutoPushBack(AutoData d) { AutoDataList.push_back(d);}
    void DataPushBack(DataData d) { DataDataList.push_back(d);}
    void PLCPushBack(PLCMoData d) { PlcDataList.push_back(d);}

    QList<MainData> Get_MainList() {return MainDataList;}
    QList<ManualData> Get_ManualList() {return ManualDataList;}
    QList<AutoData> Get_AutoList() {return AutoDataList;}
    QList<DataData> Get_DataList() {return DataDataList;}
    QList<PLCMoData> Get_PLCMoList() {return PlcDataList;}
    QList<QStringList> Get_PLCMoListSystem(PlcMoType);

    void Set_MainListData(MainType,int row,int col,QVariant Data);
    void Set_ManualListData(ManualType,int row,int col,QVariant Data);
    void Set_AutotData(AutoType,int row,int col,QVariant Data);
    void Set_DataData(DataType,int row,int col,QVariant Data);
    void Set_PlcMoListData(PlcMoType,int row,int col,QVariant Data);
    void Set_Plc_Bool(PlcMoType,bool);
    void Set_Plc_Title(PlcMoType,QString);

    void Set_SettingData(SettingType,QList<QVariant> v);
    QList<QVariant> Get_SettingData(SettingType);
    void SettingPushBack(SettingData);
    void SettingValue(SettingType,QVariant);
    QStringList Get_AllP();
    QList<QVariant> Get_AllValue();

    void PushBackMofityList(ViewType type,int table,int row,int col,QVariant Data);
    void PopBackMofityList();
    void Write_Val_For_Ini();
    void RestoreList();
signals:
    void Write_Init();
    void InitTable();

private:
    QList<MainData> MainDataList;
    QList<ManualData> ManualDataList;
    QList<AutoData> AutoDataList;
    QList<DataData> DataDataList;
    QList<PLCMoData> PlcDataList;
    QList<ModifyData> MoifyList;
    QList<SettingData> SettingList;

    Setting_Data();
    ~Setting_Data();
};


#endif //_SETTING_DATA_H_
