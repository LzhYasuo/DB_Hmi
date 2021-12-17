#ifndef _DB_HMI_GUI_SYSTEM_IO_H_
#define _DB_HMI_GUI_SYSTEM_IO_H_

#include <QWidget>

class DB_Hmi_Gui_System_Io : public QWidget
{
    Q_OBJECT
public:
    DB_Hmi_Gui_System_Io(QWidget* parent = nullptr);
    ~DB_Hmi_Gui_System_Io();

public slots:
    void Set_PLCIO(QStringList,int);
    void Set_PLCIO_Stare(bool,int);

private:
    void init();
    QWidget* InitWidget();
    QWidget* Column_Init();
};


#endif //_DB_HMI_GUI_SYSTEM_IO_H_
