#ifndef _CYCLE_P_LAST_TABLE_VIEW_H_
#define _CYCLE_P_LAST_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class CyClePLastTableModel;
class QTableView;
class CyClePLastTableDelegate;
class CyclePLastTableView : public QTableView
{
    Q_OBJECT
public:
    CyclePLastTableView(QWidget* parent = nullptr);
    ~CyclePLastTableView();

    void Clear_All();

    void Set_Value(QList<QStringList> msg);
    QList<QStringList> Get_Value();

private:
    void View_Init();
    //model
    CyClePLastTableModel* tableModel;
    //delegate
    CyClePLastTableDelegate* tableDelegate;

private slots:
    void onTableClicked(const QModelIndex &);
};


#endif //_CYCLE_P_LAST_TABLE_VIEW_H_
