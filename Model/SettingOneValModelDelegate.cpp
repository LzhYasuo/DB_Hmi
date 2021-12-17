#include "SettingOneValModelDelegate.h"
#include <QPainter>
#include <QDebug>

SettingOneValModelItem::SettingOneValModelItem(QObject* parent)
    :QObject(parent)
{

}

SettingOneValModelItem::~SettingOneValModelItem()
{

}

SettingOneValTableModel::SettingOneValTableModel(int TableMaxNum)
    :mTableMaxNum(TableMaxNum)
{
    Ary_row_List = new QList<SettingOneValModelItem*>();
}

SettingOneValTableModel::SettingOneValTableModel()
{

}

SettingOneValTableModel::~SettingOneValTableModel()
{

}

Qt::ItemFlags SettingOneValTableModel::flags(const QModelIndex &index) const
{
    if(index.column() != 0)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index);
}

int SettingOneValTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return mTableMaxNum;
}
int SettingOneValTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 2;
}
QVariant SettingOneValTableModel::data(const QModelIndex &index, int role) const
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
    }
    return QVariant();
}
QVariant SettingOneValTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void SettingOneValTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void SettingOneValTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void SettingOneValTableModel::RefrushModel(SettingOneValModelItem* item)
{
    const int count = Ary_row_List->size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List->push_back(item);
    endInsertRows();
}

bool SettingOneValTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(Ary_row_List == nullptr || Ary_row_List->size() < 1 || !index.isValid())
        return false;
    if  (role == Qt::TextAlignmentRole)
         {
             return int (Qt::AlignHCenter | Qt::AlignVCenter);
         }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == 1)
        {
            Ary_row_List->at(index.row())->Set_FirstVal(value.toString());
        }

        emit ModityData(index.row(),index.column(),value);

        return true;
    }
    return false;
}

void SettingOneValTableModel::PushBackData(QList<QStringList> data)
{
    Ary_row_List->clear();
    QStringList name = data.at(0);
    QStringList FirstList = data.at(1);

    for(int i = 0; i < mTableMaxNum; i++)
    {
        SettingOneValModelItem* Item = new SettingOneValModelItem();
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

        Ary_row_List->push_back(Item);
    }

    RefrushModelData();
}

void SettingOneValTableModel::PushBackModel(QList<QVariant> list)
{
//    int num = list.at(0).toString().split("D").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutter_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutting_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));
//    int num = list.at(0).toString().split("H").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Length_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Length_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));

    RefrushModelData();
}

void SettingOneValTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

SettingOneValModelDelegate::SettingOneValModelDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

SettingOneValModelDelegate::~SettingOneValModelDelegate()
{

}

void SettingOneValModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
    else
    {
        QItemDelegate::paint(painter,option,index);
    }
}
