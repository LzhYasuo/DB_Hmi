#ifndef G_MODEL_DELEGATE_H_
#define G_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>

class HModelItem : public QObject
{
    Q_OBJECT
public:
    HModelItem(QObject* parent = nullptr);
    ~HModelItem();


    void Set_Name(QString n) {Name = n;}
    void Set_HName(QString n) {HName = n;}
    void Set_HValue(QString n) {HValue = n;}

    inline QString Get_HName() {return HName;}
    inline QString Get_HValue() {return HValue;}
    inline QString Get_Name() {return Name;}
private:
    //长度补偿
    QString HName;
    QString HValue;
    //姓名
    QString Name;
};

class HTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    HTableModel();
    ~HTableModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(HModelItem*);
    void setHorizontalHeaderList(QStringList hHeadList);
    void setVerticalHeaderList(QStringList VHeadList);
    void PushBackModel(QList<QVariant>);
    void RefrushModelData();
    void ListPushBack(QList<QVariant> List);
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
    QList<HModelItem*>* Ary_row_List;
    QString Get_Name = "";
    QString Get_FirstValue = "";
    QString Get_SecondValue = "";
    const bool Model = false;
};

class HTableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit HTableDelegate(QObject *parent = nullptr);
    virtual ~HTableDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //G_MODEL_DELEGATE_H_
