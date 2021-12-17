#ifndef D_MODEL_DELEGATE_H_
#define D_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QVariant>

class DModelItem : public QObject
{
    Q_OBJECT
public:
    DModelItem(QObject* parent = nullptr);
    ~DModelItem();


    void Set_Name(QString n) {Name = n;}
    void Set_DName(QString n) {DName = n;}
    void Set_DValue(QString n) {DValue = n;}

    inline QString Get_DName() {return DName;}
    inline QString Get_DValue() {return DValue;}
    inline QString Get_Name() {return Name;}
private:
    //长度补偿
    QString DName;
    QString DValue;
    //姓名
    QString Name;
};

class DTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    DTableModel();
    ~DTableModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(DModelItem*);
    void setHorizontalHeaderList(QStringList hHeadList);
    void setVerticalHeaderList(QStringList VHeadList);
    void PushBackModel(QList<QVariant>);
    void RefrushModelData();
    void ListPushBack(QList<QVariant>);
    void ListPushBack(QList<QStringList>);
    QList<QStringList> ListPopBack();
    void Clear_Table_Data();


    bool VerifyNumber(QString str)
    {
        std::string temp = str.toStdString();
        for (int i = 0; i < str.length(); i++)
        {
            if (temp[i]<'0' || temp[i]>'9')
            {
                if(i == 0 && temp[0] == '-')
                    continue;
                return false;
            }
        }

        return true;
    }
private:
    QStringList horizontal_header_list;
    QStringList vertical_header_list;
    QList<DModelItem*>* Ary_row_List;
    QString Get_Name = "";
    QString Get_FirstValue = "";
    QString Get_SecondValue = "";
};

class DTableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DTableDelegate(QObject *parent = nullptr);
    virtual ~DTableDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //D_MODEL_DELEGATE_H_
