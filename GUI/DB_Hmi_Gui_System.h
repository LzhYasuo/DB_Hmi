#ifndef _DB_HMI_GUI_SYSTEM_H_
#define _DB_GUI_GUI_SYSTEM_H_

#include <QWidget>

enum Button_Style
{
    B_Top = 1,
    B_Body = 2,
    B_Bottom
};

enum SystemSwitchPage
{
    InformationPage,
    PLCMonitoringPage,
    PanelInputPage,
    PanelOutputPage,
    CompensationValuePage,
};

class QGroupBox;
class QPushButton;
class DB_Hmi_Body_System:public QWidget
{
    Q_OBJECT
public:
    DB_Hmi_Body_System(QWidget* parent = nullptr);
    ~DB_Hmi_Body_System();

signals:
    void SwitchSWidgetPage(int index);
    void ButtonClicked(QPushButton*);
private:
    void init();
    QWidget* InitLayout();

    //封装程序的QGroupBox以及内部的内容
//    QGroupBox* Create_Program_Box();
    //封装返回工件原点的QGroupBox以及内部的内容
//    QGroupBox* Create_Origin_workpiece_Box();
    //封装右边按钮的Widget
    QWidget* Create_Button_Widget();
    //创建按钮
    QPushButton* Create_Button(QString,Button_Style,int,QString);
    //创建切换界面
    QWidget* Create_System_Switch_Page(SystemSwitchPage);
    //
    QGroupBox* Create_PLCBox_Val(QList<QStringList> List,bool state);

    void Write_Io();

    //保存Z文件
    void Save_Z();
    void Save_G();
    void Save_H();
    void Save_D();

private:
    QList<int> AddFirVal;
    QList<QString> IOVal;
};

#endif //_DB_GUI_GUI_SYSTEM_H_
