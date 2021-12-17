#ifndef G_MODEL_DELEGATE_H_
#define G_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>

class GModelItem : public QObject
{
    Q_OBJECT
public:
    GModelItem(QObject* parent = nullptr);
    ~GModelItem();


    void Set_Name(QString n) {Name = n;}
    void Set_AVaule(QString n) {AValue = n;}
    void Set_YValue(QString n) {YValue = n;}
    void Set_ZValue(QString n) {ZValue = n;}
    void Set_XValue(QString n) {XValue = n;}

    inline QString Get_AValue() {return AValue;}
    inline QString Get_YValue() {return YValue;}
    inline QString Get_ZValue() {return ZValue;}
    inline QString Get_XValue() {return XValue;}
    inline QString Get_Name() {return Name;}
private:
    //长度补偿
    QString XValue;
    QString YValue;
    QString ZValue;
    QString AValue;
    //姓名
    QString Name;
};

class GTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    GTableModel();
    ~GTableModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(GModelItem*);
    void setHorizontalHeaderList(QStringList hHeadList);
    void setVerticalHeaderList(QStringList VHeadList);
    void PushBackModel(QList<QVariant>);
    void RefrushModelData();
    void ListPushBack(QList<QVariant>);
    void ListPushBack(QList<QStringList>);
    QList<QStringList> ListPopBack();
    QString Get_NcdaName(QString);
    QStringList Get_NameNcda();
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
    QList<GModelItem*>* Ary_row_List;
    QString Get_Name = "";
    QString Get_FirstValue = "";
    QString Get_SecondValue = "";
    QStringList NacdName;
};

class GTableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit GTableDelegate(QObject *parent = nullptr);
    virtual ~GTableDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //G_MODEL_DELEGATE_H_
