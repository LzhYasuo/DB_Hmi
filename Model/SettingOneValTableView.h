#ifndef SETTING_ONE_VAL_TABLE_VIEW_H_
#define SETTING_ONE_VAL_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class SettingOneValTableModel;
class QTableView;
class SettingOneValModelDelegate;
class SettingOneValTableView : public QTableView
{
    Q_OBJECT
public:
    SettingOneValTableView(QStringList HorList,int TableMaxNum,int NameWidth,int TableWidth,int DefaultHeight,int TableHeight,int type = 0,QWidget* parent = nullptr);
    SettingOneValTableView(QWidget* parent = nullptr);
    ~SettingOneValTableView();

    void Set_Model_Data(QList<QStringList> data);
signals:
    void TableModityData(int,int,QVariant);
private:
    //model
    SettingOneValTableModel* tableModel;
    //delegate
    SettingOneValModelDelegate* tableDelegate;
    //列名称
    QStringList mHorList;
    //最大值
    int mTableMaxNum;
    //表格第一列名字宽度
    int mNameWidth;
    //表格其余宽度
    int mTableWidth;
    //表格默认高度
    int mDefaultHeight;
    //表头高度
    int mTableHeight;
    //
    int mType;
};


#endif //SETTING_ONE_VAL_TABLE_VIEW_H_
