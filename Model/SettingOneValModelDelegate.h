#ifndef _SETTING_ONE_VAL_MODEL_DELEGATE_H_
#define _SETTING_ONE_VAL_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>

class SettingOneValModelItem : public QObject
{
    Q_OBJECT
public:
    SettingOneValModelItem(QObject* parent = nullptr);
    ~SettingOneValModelItem();


    void Set_Name(QString n) {Name = n;}
    void Set_FirstVal(QString n) {FirstVal = n;}

    inline QString Get_FirstVal() {return FirstVal;}
    inline QString Get_Name() {return Name;}
private:
    //长度补偿
    QString FirstVal;
    //姓名
    QString Name;
};

class SettingOneValTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    SettingOneValTableModel(int TableMaxNum);
    SettingOneValTableModel();
    ~SettingOneValTableModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(SettingOneValModelItem*);
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
    QList<SettingOneValModelItem*>* Ary_row_List;
    QString Get_Name = "";
    QString Get_FirstValue = "";
    QString Get_SecondValue = "";
    int mTableMaxNum;
};

class SettingOneValModelDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit SettingOneValModelDelegate(QObject *parent = nullptr);
    virtual ~SettingOneValModelDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //_SETTING_ONE_VAL_MODEL_DELEGATE_H_
