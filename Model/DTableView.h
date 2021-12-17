#ifndef _D_TABLE_VIEW_H_
#define _D_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class DTableModel;
class QTableView;
class DTableDelegate;
class DTableView : public QTableView
{
    Q_OBJECT
public:
    DTableView(QWidget* parent = nullptr);
    ~DTableView();

    QList<QStringList> Get_Value();

    void Clear_All();

private:
    void View_Init();
    //model
    DTableModel* tableModel;
    //delegate
    DTableDelegate* tableDelegate;
};


#endif //_D_TABLE_VIEW_H_
