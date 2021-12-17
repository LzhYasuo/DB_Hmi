#ifndef _DB_HMI_GUI_DATA_SUBLINE_H_
#define _DB_HMI_GUI_DATA_SUBLINE_H_

#include <QWidget>
#include <QDialog>

class DB_Hmi_Gui_Data_SubLine : public QDialog
{
    Q_OBJECT
public:
    DB_Hmi_Gui_Data_SubLine(QStringList tableName,QWidget* Widget = nullptr);
    ~DB_Hmi_Gui_Data_SubLine();

    void Clear();

    bool removeListSame(QStringList *list);

signals:
    void Sub_Line_Data(QStringList);

private slots:
    void ButtonClickedSlot();
    void BoxSwitchSlot(int index);

private:
    void Init();
    QWidget* InitWidget();

private:
    QStringList mTableName;
};


#endif //_DB_HMI_GUI_DATA_SUBLINE_H_
