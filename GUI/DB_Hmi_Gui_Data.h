#ifndef _DB_HMI_GUI_DATA_H_
#define _DB_HMI_GUI_DATA_H_

#include <QWidget>
#include <QVariant>
#include "../Ini_Dbdata/Data_SettingDbData.h"

enum SwitchPageType
{
    GlobalWidgetType,
    CuttingWidgetType,
    PerforatedWidgetType
};

class DB_Hmi_Gui_Numkeyboard;
class DB_Hmi_Gui_Data_SubLine;
class DB_Hmi_Gui_Data_AddLine;
class DataDbdata;
class Data_Setting;
class DB_Hmi_Gui_Data : public QWidget
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Data(QWidget* parent = nullptr);
    ~DB_Hmi_Gui_Data();
    //创建中间切换界面
    QWidget* SetSwitchWidget(SwitchPageType);
    //创建Label Value Label 模式 Model 1 int 2 Double 3Combobox
    QWidget* CreateLabelValueLabelWidget(QString Text,QString unitText,int model,int max = 0,int min = 0,int decimalPoint = -1,QVariant Value = 0,
                                         QSize TextSize = QSize(0,0),QSize ValueSize = QSize(0,0),
                                         QSize UnitSize = QSize(0,0),bool isStretch = false,
                                         QStringList comboxNameTable = QStringList());
    //创建Value Label
    QWidget* CreateValueLabelWidget(QString = "",int min = 0,int max = 0);
    //初始化切割列表名称
    QWidget* InitCuttingTableName(QStringList);
    //初始化列表值
    QWidget* InitCuttingTableValue(int index);
    //创建穿孔 穿孔1
    QWidget* Create_PerforatedWidget(QList<PerforatedSettingType>,QString Paint,QString,int Model);
signals:
    void GuiDataWriteintoDB();
    void GuiDataWriteintoCNCPLC();
    void AddLine();
    void AsSaveFile(QString);
private:
    void init();
    QWidget* InitWidget();

    DB_Hmi_Gui_Data_AddLine* mAddLine;
    DB_Hmi_Gui_Data_SubLine* mSubLine;

    Data_Setting* IniData;
    DataDbdata* DbData;

    DB_Hmi_Gui_Numkeyboard* Key;
};

#endif //_DB_HMI_GUI_DATA_H_
