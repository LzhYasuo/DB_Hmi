#ifndef _CYCLE_P_LESS_MODEL_DELEGATE_H_
#define _CYCLE_P_LESS_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>

class CyClePLessModelItem : public QObject
{
    Q_OBJECT
public:
    CyClePLessModelItem(QObject* parent = nullptr);
    ~CyClePLessModelItem();


    void Set_Name(QString n) {Name = n;}
    void Set_PName(QString n) {PName = n;}
    void Set_PValue(QString n) {PValue = n;}

    inline QString Get_PName() {return PName;}
    inline QString Get_PValue() {return PValue;}
    inline QString Get_Name() {return Name;}
private:
    //长度补偿
    QString PName;
    QString PValue;
    //姓名
    QString Name;
};

class CyClePLessTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    CyClePLessTableModel();
    ~CyClePLessTableModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(CyClePLessModelItem*);
    void setHorizontalHeaderList(QStringList hHeadList);
    void setVerticalHeaderList(QStringList VHeadList);
    void PushBackModel(QList<QVariant>);
    void RefrushModelData();
    void PushBackData(QList<QStringList>);
    QList<QStringList> PopBackData();
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
    QList<CyClePLessModelItem*>* Ary_row_List;
    QString Get_Name = "";
    QString Get_FirstValue = "";
    QString Get_SecondValue = "";
};

class CyClePLessTableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CyClePLessTableDelegate(QObject *parent = nullptr);
    virtual ~CyClePLessTableDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //_CYCLE_P_LAST_MODEL_DELEGATE_H_
