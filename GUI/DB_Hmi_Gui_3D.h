#ifndef _DB_HMI_GUI_3D_H_
#define _DB_HMI_GUI_3D_H_

#include <QWidget>

class DB_Hmi_Gui_3D : public QWidget
{
    Q_OBJECT

public:
    explicit DB_Hmi_Gui_3D(QWidget *parent = 0);
    ~DB_Hmi_Gui_3D();

    void init();
    QWidget* init_Conotrol();

private:
};

#endif // _DB_HMI_GUI_3D_H_
