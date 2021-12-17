#ifndef _DB_HMI_GUI_CHANGE_PASSWD_H_
#define _DB_HMI_GUI_CHANGE_PASSWD_H_

#include <QWidget>
#include <QDialog>

class DB_Hmi_Gui_AlpKeyboard;
class QLineEdit;
class DB_Hmi_Gui_Change_Passwd : public QDialog
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Change_Passwd(QWidget* parent = nullptr);
    ~DB_Hmi_Gui_Change_Passwd();

private:
    int OldPawdIsTrue();

signals:
    void ChangeState(bool);

private slots:
    void Clicked_Sure_Slot();
private:
    //鼠标点击 移动
    void mousePressEvent(QMouseEvent* event);
    //初始化
    void Init();
    //初始化界面
    QWidget* InitWidget();
    //旧密码
    QLineEdit* OldPawd;
    //第一次输入新密码
    QLineEdit* newPawd;
    //第二次输入新密码
    QLineEdit* SurenewPaswd;
    //键盘
    DB_Hmi_Gui_AlpKeyboard* Key;
    //密码是不是正确的
    int PawdisTure = 0;
};


#endif //_DB_HMI_GUI_CHANGE_PASSWD_H_
