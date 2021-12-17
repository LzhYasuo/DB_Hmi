#ifndef _CYCLE_P_LESS_TABLE_VIEW_H_
#define _CYCLE_P_LESS_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class CyClePLessTableModel;
class QTableView;
class CyClePLessTableDelegate;
class CyclePLessTableView : public QTableView
{
    Q_OBJECT
public:
    CyclePLessTableView(QWidget* parent = nullptr);
    ~CyclePLessTableView();

    void Clear_All();

    void Set_Value(QList<QStringList> List);
    QList<QStringList> Get_Value();

private:
    void View_Init();
    //model
    CyClePLessTableModel* tableModel;
    //delegate
    CyClePLessTableDelegate* tableDelegate;
};


#endif //_CYCLE_P_LAST_TABLE_VIEW_H_
