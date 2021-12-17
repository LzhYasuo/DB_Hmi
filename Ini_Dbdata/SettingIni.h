#ifndef _SETTING_INI_H_
#define _SETTING_INI_H_

#include <QObject>

class MainDataList;
class QSettings;
class SettingIni : public QObject
{
    Q_OBJECT
public:
    SettingIni();
    ~SettingIni();

    void Write_For_Ini();
private:
    void initMainSet();
    void initManualSet();
    void initAutoSet();
    void initDataSet();
    void initPlcMoSet();
    void initSettingSet();

private:
    QStringList Get_SettingStr(QString str)
    {
        QStringList msg;
        if(str.isEmpty())
            return msg;

        msg << str.split(":");
        return msg;
    }

private:
    QSettings* Conf;

};

#endif //_SETTING_INI_H_
