#ifndef _DB_HMI_GUI_DATA_ADDLINE_H_
#define _DB_HMI_GUI_DATA_ADDLINE_H_


#include <QDialog>

class DB_Hmi_Gui_Data_AddLine : public QDialog
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Data_AddLine(QWidget* Widget = nullptr);
    ~DB_Hmi_Gui_Data_AddLine();

    void Clear();
private:
    void Init();
    QWidget* InitWidget();

signals:
    void Add_Line(int index);
    void Add_Line_Data(QString Text,int Max,int Min,int Decimal,int GuiType,QStringList PList,QStringList ComboList = QStringList());

private slots:
    void Button_Clicked_Slot();
    void ComboBox_Switch_Slot(int index);
    void ComboBox_Change_Slot(int index);
};


#endif //_DB_HMI_GUI_DATA_ADDLINE_H_
