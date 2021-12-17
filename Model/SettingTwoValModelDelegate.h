#ifndef _SETTING_TWO_VAL_MODEL_DELEGATE_H_
#define _SETTING_TWO_VAL_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>

class SettingTwoValModelItem : public QObject
{
    Q_OBJECT
public:
    SettingTwoValModelItem(QObject* parent = nullptr);
    ~SettingTwoValModelItem();


    void Set_Name(QString n) {Name = n;}

    inline QString Get_FirstVal() {return FirstVal;}
    inline QString Get_SecondVal() {return SecondVal;}
    inline QString Get_Name() {return Name;}

    void Set_FirstVal(QString n) {FirstVal = n;}
    void Set_SecondVal(QString n) {SecondVal = n;}
private:
    //长度补偿
    QString FirstVal;
    QString SecondVal;
    //姓名
    QString Name;
};

class SettingTwoValTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    SettingTwoValTableModel(int MaxNum);
    SettingTwoValTableModel();
    ~SettingTwoValTableModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(SettingTwoValModelItem*);
    void setHorizontalHeaderList(QStringList hHeadList);
    void setVerticalHeaderList(QStringList VHeadList);
    void PushBackModel(QList<QVariant>);
    void RefrushModelData();
    void PushBackData(QList<QStringList> data);


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
signals:
    void ModityData(int,int,QVariant);
private:
    QStringList horizontal_header_list;
    QStringList vertical_header_list;
    QList<SettingTwoValModelItem*>* Ary_row_List;
    QString Get_Name = "";
    QString Get_FirstValue = "";
    QString Get_SecondValue = "";
    int mMaxTableNum;
};

class SettingTwoValModelDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit SettingTwoValModelDelegate(QObject *parent = nullptr);
    virtual ~SettingTwoValModelDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //_SETTING_TWO_VAL_MODEL_DELEGATE_H_
