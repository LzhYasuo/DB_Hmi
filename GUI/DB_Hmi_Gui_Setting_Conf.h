#ifndef _DB_HMI_GUI_SETTING_CONF_H_
#define _DB_HMI_GUI_SETTING_CONF_H_

#include <QWidget>
#include <QIODevice>
#include <QDialog>


enum SystemConfSwitchPage
{
    MainPage,
    ManualPage,
    AutoPage,
    DataPage,
    PLCMo1Page,
    PLCMO2Page,
};

class DB_Hmi_Gui_Setting_Conf : public QWidget
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Setting_Conf(QWidget* parent = nullptr);
    ~DB_Hmi_Gui_Setting_Conf();
private:
    void init();
    QWidget* InitWidget();
    QWidget* Create_Setting_Conf_Switch_Page(SystemConfSwitchPage);
    QWidget* Create_PlcGroup(QStringList msg);
};


#endif // _DB_HMI_GUI_SETTING_CONF_H_
