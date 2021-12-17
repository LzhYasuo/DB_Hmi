#ifndef _CYCLE_P_MORE_TABLE_VIEW_H_
#define _CYCLE_P_MORE_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class CyClePMoreTableModel;
class QTableView;
class CyClePMoreTableDelegate;
class CyclePMoreTableView : public QTableView
{
    Q_OBJECT
public:
    CyclePMoreTableView(QWidget* parent = nullptr);
    ~CyclePMoreTableView();

    void Clear_All();

    void Set_Value(QList<QStringList>);
    QList<QStringList> Get_Value();

private:
    void View_Init();
    //model
    CyClePMoreTableModel* tableModel;
    //delegate
    CyClePMoreTableDelegate* tableDelegate;
};


#endif //_CYCLE_P_LAST_TABLE_VIEW_H_
