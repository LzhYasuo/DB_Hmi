#ifndef _DATA_SETTING_H_
#define _DATA_SETTING_H_

#include <QObject>

//Global,
//Cutting,
//Perforated



#define DB_CONFI

class Data_Setting : public QObject
{
    Q_OBJECT
public:
    Data_Setting();
    ~Data_Setting();
    //取配置文件列表内部的值 :
    QStringList Get_SettingStr(QString str);
    //取配置文件列表内部的值 * :
    QList<QStringList> Get_SettingStrList(QString str);
    //取配置文件列表内部的值 *
    QStringList Get_SettingStrStringList(QString str);
    //
    QString ADD_Str_For_List(QStringList,int i,QString msg);
private slots:
    //把数据写入ini文件
    void Write_into_ini_Slot(QString Text,int Max,int Min,int Decimal,int Gui_Type,QStringList PList,QStringList ComboxList);
    //吧ini文件的数据删除
    void Delete_into_ini_Slot(QStringList);
    void Delete_Data_for_Ini(QString);
private:
    void InitGlobalList();
    void InitCuttingList();
    void InitPerforatedList();
    void InitDataState();
private:
    bool isOpen = true;
};


#endif //_DATA_SETTING_H_
