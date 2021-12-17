#ifndef _DB_HMI_GUI_MAIN_BODY_H_
#define _DB_HMI_GUI_MAIN_BODY_H_

#include <QWidget>

class DB_Hmi_Gui_Numkeyboard;
class Db_Hmi_Gui_Main_Body : public QWidget
{
    Q_OBJECT
public:
    Db_Hmi_Gui_Main_Body(QWidget* parent = nullptr);
    ~Db_Hmi_Gui_Main_Body();

public slots:
    void Slot_Switch_Page(int);

private:
    void init();
    QWidget* InitWidget();
private:
    bool PasswdSure = false;
};

#endif //_DB_HMI_GUI_MAIN_BODY_H_
