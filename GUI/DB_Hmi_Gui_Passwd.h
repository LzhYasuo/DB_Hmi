#ifndef DB_HMI_GUI_PASSWD_H_
#define DB_HMI_GUI_PASSWD_H_

#include <QDialog>

class DB_Hmi_Gui_AlpKeyboard;
class QLineEdit;
class DB_Hmi_Gui_Passwd :public QDialog
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Passwd();
    ~DB_Hmi_Gui_Passwd();
    void mousePressEvent(QMouseEvent* event);
private:
    void Init();
    QWidget* InitWidget();

signals:
    void PassWordRight();

private slots:
    void Clicked_Sure_Slot();
private:
    QLineEdit* lineEdit;
    const QString Passwd = "DB009";

    DB_Hmi_Gui_AlpKeyboard* Key;

};

#endif //DB_HMI_GUI_PASSWD_H_
