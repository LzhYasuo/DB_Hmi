#include "SettingFourValModelDelegate.h"
#include <QPainter>
#include <QDebug>

SettingFourValModelItem::SettingFourValModelItem(QObject* parent)
    :QObject(parent)
{

}

SettingFourValModelItem::~SettingFourValModelItem()
{

}

SettingFourValTableModel::SettingFourValTableModel()
{

}

SettingFourValTableModel::SettingFourValTableModel(int TableMaxNum)
    :mTableMaxNum(TableMaxNum)
{
    Ary_row_List = new QList<SettingFourValModelItem*>();
}

SettingFourValTableModel::~SettingFourValTableModel()
{

}

Qt::ItemFlags SettingFourValTableModel::flags(const QModelIndex &index) const
{
    if(index.column() != 0)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index);
}

int SettingFourValTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return mTableMaxNum;
}
int SettingFourValTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 5;
}
QVariant SettingFourValTableModel::data(const QModelIndex &index, int role) const
{
    if(Ary_row_List == nullptr || Ary_row_List->size() < 1 || !index.isValid())
        return QVariant();
    if  (role == Qt::TextAlignmentRole)
         {
             return  int (Qt::AlignHCenter | Qt::AlignVCenter);
         }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == 0)
            return Ary_row_List->at(index.row())->Get_Name();
        else if(index.column() == 1)
            return Ary_row_List->at(index.row())->Get_FirstVal();
        else if(index.column() == 2)
        {
            return Ary_row_List->at(index.row())->Get_SecondValue();
        }
        else if(index.column() == 3)
        {
            return Ary_row_List->at(index.row())->Get_ThirdVal();
        }
        else if(index.column() == 4)
        {
            return Ary_row_List->at(index.row())->Get_FourValue();
        }
    }
    return QVariant();
}
QVariant SettingFourValTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(horizontal_header_list.size() > section)
                return horizontal_header_list[section];
            else
                return QVariant();
        }
        if(orientation == Qt::Vertical)
        {
            if(vertical_header_list.size() > section)
                return vertical_header_list[section];
            else
                return QVariant();
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void SettingFourValTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void SettingFourValTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void SettingFourValTableModel::RefrushModel(SettingFourValModelItem* item)
{
    const int count = Ary_row_List->size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List->push_back(item);
    endInsertRows();
}

bool SettingFourValTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(Ary_row_List == nullptr || Ary_row_List->size() < 1 || !index.isValid())
        return false;
    if  (role == Qt::TextAlignmentRole)
         {
             return int (Qt::AlignHCenter | Qt::AlignVCenter);
         }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
//        if(index.column() == 0)
//        {
//            Ary_row_List->at(index.row())->Set_Name(value.toString());
//        }
        if(index.column() == 1)
        {
            Ary_row_List->at(index.row())->Set_FirstVal(value.toString());
        }
        else if(index.column() == 2)
        {
            Ary_row_List->at(index.row())->Set_SecondVal(value.toString());
        }
        else if(index.column() == 3)
        {
            Ary_row_List->at(index.row())->Set_ThirdVal(value.toString());
        }
        else if(index.column() == 4)
        {
            Ary_row_List->at(index.row())->Set_FourVal(value.toString());
        }

        emit ModityData(index.row(),index.column(),value);

        return true;
    }
    return false;
}

void SettingFourValTableModel::PushBackData(QList<QStringList> data)
{
    Ary_row_List->clear();
    QStringList name = data.at(0);
    QStringList FirstList = data.at(1);
    QStringList SecondList = data.at(2);
    QStringList ThirdList = data.at(3);
    QStringList fourList = data.at(4);

    for(int i = 0; i < mTableMaxNum; i++)
    {
        SettingFourValModelItem* Item = new SettingFourValModelItem();
        if(name.size() < i + 1)
        {
            Item->Set_Name("");
        }
        else
        {
            Item->Set_Name(name.at(i));
        }
        if(FirstList.size() < i + 1)
        {
            Item->Set_FirstVal("");
        }
        else
        {
            Item->Set_FirstVal(FirstList.at(i));
        }
        if(SecondList.size() < i + 1)
        {
            Item->Set_SecondVal("");
        }
        else
        {
            Item->Set_SecondVal(SecondList.at(i));
        }
        if(ThirdList.size() < i + 1)
        {
            Item->Set_ThirdVal("");
        }
        else
        {
            Item->Set_ThirdVal(ThirdList.at(i));
        }
        if(fourList.size() < i + 1)
        {
            Item->Set_FourVal("");
        }
        else
        {
            Item->Set_FourVal(fourList.at(i));
        }

        Ary_row_List->push_back(Item);
    }

    RefrushModelData();
}

void SettingFourValTableModel::PushBackModel(QList<QVariant> list)
{
//    int num = list.at(0).toString().split("D").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutter_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutting_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));
//    int num = list.at(0).toString().split("H").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Length_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Length_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));

    RefrushModelData();
}

void SettingFourValTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

SettingFourValModelDelegate::SettingFourValModelDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

SettingFourValModelDelegate::~SettingFourValModelDelegate()
{

}

void SettingFourValModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.model()->data(index,Qt::DisplayRole).toString() == "")
        return;
    if(index.column() == 0)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->fillRect(option.rect,QBrush(QColor(180,180,180)));
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 1)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 2)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 3)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 4)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else
    {
        QItemDelegate::paint(painter,option,index);
    }
}
