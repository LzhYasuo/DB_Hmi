#ifndef SETTING_FOUR_VAL_TABLE_VIEW_H_
#define SETTING_FOUR_VAL_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class SettingFourValTableModel;
class QTableView;
class SettingFourValModelDelegate;
class SettingFourValTableView : public QTableView
{
    Q_OBJECT
public:
    SettingFourValTableView(QStringList HorList,int TableMaxNum,int NameWidth,int TableWidth,int DefaultHeight,int TableHeight,QWidget* parent = nullptr);
    SettingFourValTableView(QWidget* parent = nullptr);
    ~SettingFourValTableView();

    void Set_Model_Data(QList<QStringList> data);

signals:
    void TableModityData(int,int,QVariant);

private:
    //model
    SettingFourValTableModel* tableModel;
//    //delegate
    SettingFourValModelDelegate* tableDelegate;
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
};


#endif //SETTING_FOUR_VAL_TABLE_VIEW_H_
