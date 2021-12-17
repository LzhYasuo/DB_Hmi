#ifndef _DB_HMI_GUI_SETTING_H_
#define _DB_HMI_GUI_SETTING_H_

#include <QWidget>

enum Button_Style_Set_Up
{
    B_TOP = 1,
    B_BODY = 2,
    B_BOTTOM
};

enum SettingSwitchPage
{
    IOSetPage,
    MachineSetPage,
};

class QPushButton;
class QGroupBox;
class QHBoxLayout;
class DB_Hmi_Gui_Setting : public QWidget
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Setting(QWidget* parent = nullptr);
    ~DB_Hmi_Gui_Setting();

private:
    //初始化
    void init();
    //界面初始化
    QWidget* InitLayout();
    //Set界面的创建
//    QWidget* Init_Set_Widget();
    //IO/驱动 配置
//    QWidget* Init_IO_driver_configuration_Widget();
    //机床设置1跟2的GroupBox
//    QGroupBox* Create_Box(QStringList,QList<double>,QStringList);
    //文字-spin-文字的一个Layout
//    QHBoxLayout* Label_Double_Spin_Layout(QString,double,QString);
    //创建按钮
    QPushButton* Create_Button(QString,Button_Style_Set_Up);
    //创建不同的界面
    QWidget* Create_System_Switch_Page(SettingSwitchPage);
private:
    const QString mIniDbHmi = "C:\\PACnc\\DBHMI\\cfg\\Setting.ini";
    bool AxValue = 0;
    bool ginit_checked = false;
    QStringList List37;
    QStringList List38;
signals:
    void UpdateAX();
};

#endif //_DB_HMI_GUI_SETTING_H_
