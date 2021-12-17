#ifndef DB_HMI_H
#define DB_HMI_H

#include <QWidget>

enum Light_Model
{
    NO1,
    NO2,
    NO3,
    NO4,
    NO5,
    NO6,
    NO7,
    NO8,
    NO9,
    NO10,
    NO11,
    NO12,
};

enum StackedSwitch
{
    FirstWidget,
    SecondWidget,
};

class QPushButton;
class QLabel;
class DB_Hmi_Gui_Numkeyboard;
class DB_Hmi : public QWidget
{
    Q_OBJECT

public:
    DB_Hmi(QWidget *parent = 0);
    ~DB_Hmi();

private:
    //初始化
    void Init();
    //初始化头部
    QWidget* InitTopWidget();
    //初始化底部
    QWidget* InitBottomWidget();
    //初始化中间部分
    QWidget* InitMainWidget();
    //创建Label
    QLabel* Get_Label(QString text,Light_Model);
    //----------------Top的函数
    //创建Label排序的列表
    QWidget* Create_Label_Table(QStringList);
    //创建机床坐标的坐标组
    QWidget* Create_Coord_Group();
    //创建信息的坐标组
    QWidget* Create_information_Group();
    //创建logo以及退出等信息界面
    QWidget* Create_logo_Close_Widget();
    //创建StackedWidget的子界面
    QWidget* Create_SWidget(StackedSwitch);

    void timerEvent(QTimerEvent *e);
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void Resize(QWidget*);

    void Init_Conf();

signals:
    void Signal_Switch_Page(int);
    void Refresh_Time();
    void ButtonClicked(QPushButton*);

private:
    bool isOpen = false;
    bool MainStackTabEnable = true;
    QString m_PLCStatus;
    QStringList VISI_Rate;
    QStringList NameList;
    const QString mIniDBHmi = "C:\\PACnc\\DBHMI\\cfg\\Setting.ini";
    DB_Hmi_Gui_Numkeyboard* Key;

    bool m_ResetHMI = false;

};

#endif // DB_HMI_H
