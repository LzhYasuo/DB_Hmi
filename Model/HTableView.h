#ifndef H_TABLE_VIEW_H_
#define H_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class HTableModel;
class QTableView;
class HTableDelegate;
class HTableView : public QTableView
{
    Q_OBJECT
public:
    HTableView(QWidget* parent = nullptr);
    ~HTableView();
    void Clear_All();

    QList<QStringList> Get_Value();
private:
    void View_Init();
    //model
    HTableModel* tableModel;
    //delegate
    HTableDelegate* tableDelegate;
};


#endif //H_TABLE_VIEW_H_
