#ifndef _PUBLIC_CONTROL_H_
#define _PUBLIC_CONTROL_H_

#include <QWidget>
class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QToolButton;
class Public_Control : public QWidget
{
    Q_OBJECT
public:
    //按钮
    static QToolButton* Get_ToolButton(QString name,QString Icon = "",int Width = 0,int Height = 0,QString Style = "");
    static QPushButton* Get_Button(QString name,QString Icon = "",int Width = 0,int Height = 0,QString Style = "");
    static QPushButton* Get_ButtonIconSize(QString name,QString Icon = "",int Width = 0,int Height = 0,int IconWidth = 32,int IconHeight = 32,QString Style = "");
    static QHBoxLayout* Get_HLayout(int SpaceValue = 0,int left = 0,int Up = 0,int Right = 0,int Down = 0);
    static QVBoxLayout* Get_VLayout(int SpaceValue = 0,int left = 0,int Up = 0,int Right = 0,int Down = 0);
    //标签
    static QLabel* Get_Label(QString name,QString Icon = "",QString Style = "");
    //标签 值 标签的对象名称 值的对象名称 只是为了更好的找到这个索引进行修改
    static QWidget* Create_Labal_Value(QString Text,QString Value,QString TextObjName,QString ValueObjName);

    static Public_Control* Get();

    double Get_DeskX();
    double Get_DeskY();
    void Set_DeskX(double);
    void Set_DeskY(double);
private:
    Public_Control();
    ~Public_Control();


    double X = 1.0;
    double Y = 1.0;
};


#endif //_PUBLIC_CONTROL_H_
