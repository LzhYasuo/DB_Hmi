#ifndef G_TABLE_VIEW_H_
#define G_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class GTableModel;
class QTableView;
class GTableDelegate;
class GTableView : public QTableView
{
    Q_OBJECT
public:
    GTableView(QWidget* parent = nullptr);
    ~GTableView();

    QList<QStringList> Get_Value();
    QStringList Get_Nacd_Name();
    void Clear_All();
private:
    void View_Init();
    //model
    GTableModel* tableModel;
    //delegate
    GTableDelegate* tableDelegate;
};


#endif //G_TABLE_VIEW_H_
