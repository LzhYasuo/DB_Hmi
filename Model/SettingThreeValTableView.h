#ifndef SETTING_THREE_VAL_TABLE_VIEW_H_
#define SETTING_THREE_VAL_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class SettingThreeValTableModel;
class QTableView;
class SettingThreeValModelDelegate;
class SettingThreeValTableView : public QTableView
{
    Q_OBJECT
public:
    SettingThreeValTableView(QStringList HorList,int TableMaxNum,int NameWidth,int TableWidth,int DefaultHeight,int TableHeight,QWidget* parent = nullptr);
    SettingThreeValTableView(QWidget* parent = nullptr);
    ~SettingThreeValTableView();

    void Set_Model_Data(QList<QStringList>);
signals:
    void TableModityData(int,int,QVariant);
private:
    //model
    SettingThreeValTableModel* tableModel;
    //delegate
    SettingThreeValModelDelegate* tableDelegate;
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


#endif //SETTING_THREE_VAL_TABLE_VIEW_H_
