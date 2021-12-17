#ifndef _DB_HMI_GUI_AUTO_MANUAL_H_
#define _DB_HMI_GUI_AUTO_MANUAL_H_

#include <QWidget>

class QPushButton;
class DB_Hmi_Gui_Numkeyboard;
class DB_Hmi_Gui_Auto_Manual : public QWidget
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Auto_Manual(QWidget* parent = nullptr);
    ~DB_Hmi_Gui_Auto_Manual();

//    bool eventFilter(QObject *obj, QEvent *event);
private:
    void init();
    QWidget* InitWidget();

    //右上的Widget
    QWidget* Create_RightTopWidget();
    //右上的按钮合集
    QWidget* Create_RightTopButton();
    //右边的Stacked
    QWidget* Create_StackedWidget();
    //右下上面的按钮
    QWidget* Create_RightBottomTopButton();
    //右下下面的按钮
    QWidget* Create_RightBottomBottomButton();

    //PLCSet 接口
    void PLCSet(QString name,int);
    //PLCGet 接口
    void PLCGet(QString name,int);

    //
    QPushButton* Get_Button(QString name,QString Icon = "",int Width = 0,int Height = 0,QString plcName = "",QString Style = "");
private:
//    DB_Hmi_Gui_Numkeyboard* Key;
};

#endif //_DB_HMI_GUI_AUTO_MANUAL_H_
