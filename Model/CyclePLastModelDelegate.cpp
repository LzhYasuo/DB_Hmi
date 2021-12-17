#include "CyclePLastModelDelegate.h"
#include <QPainter>
#include <QDebug>

CyClePLastModelItem::CyClePLastModelItem(QObject* parent)
    :QObject(parent)
{

}

CyClePLastModelItem::~CyClePLastModelItem()
{

}

CyClePLastTableModel::CyClePLastTableModel()
{
    Ary_row_List = new QList<CyClePLastModelItem*>();
//    QStringList ver;

//    for(int i = 1; i <= 128; i++)
//    {
//        CyClePLastModelItem* date = new CyClePLastModelItem();
//        date->Set_Name("#" + QString("%1").arg(i));
//        date->Set_PName("");
//        date->Set_PValue("");
//        Ary_row_List->push_back(date);
//    }
}

CyClePLastTableModel::~CyClePLastTableModel()
{

}

Qt::ItemFlags CyClePLastTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
}

int CyClePLastTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return Ary_row_List->size();
}
int CyClePLastTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 3;
}
QVariant CyClePLastTableModel::data(const QModelIndex &index, int role) const
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
            return Ary_row_List->at(index.row())->Get_HName();
        else if(index.column() == 2)
            return Ary_row_List->at(index.row())->Get_HValue();
    }
    return QVariant();
}
QVariant CyClePLastTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void CyClePLastTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void CyClePLastTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void CyClePLastTableModel::RefrushModel(CyClePLastModelItem* item)
{
    const int count = Ary_row_List->size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List->push_back(item);
    endInsertRows();
}

void CyClePLastTableModel::PushBackData(QList<QStringList> data)
{
    Ary_row_List->clear();

    for(int i = 0; i < data.size(); i++)
    {
        QString Namevalue = data.at(i).at(0);
        QString Pvalue = data.at(i).at(1);
        CyClePLastModelItem* Item = new CyClePLastModelItem();
        Item->Set_Name(QString::number(i + 1));
        Item->Set_PName(Namevalue);
        Item->Set_PValue(Pvalue);
        Ary_row_List->push_back(Item);
    }

    RefrushModelData();
}

QList<QStringList> CyClePLastTableModel::PopBackData()
{
    QList<QStringList> List;
    for(int i = 0; i < Ary_row_List->size(); i++)
    {
        QStringList msg;
        msg << Ary_row_List->at(i)->Get_HName();
        msg << Ary_row_List->at(i)->Get_HValue();
        List.push_back(msg);
    }

    return List;
}

void CyClePLastTableModel::Clear_Table_Data()
{
    for(int i = 0; i < Ary_row_List->size(); i++)
    {
        Ary_row_List->at(0)->deleteLater();
    }
    Ary_row_List->clear();
}

bool CyClePLastTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(Ary_row_List == nullptr || Ary_row_List->size() < 1 || !index.isValid())
        return false;
    if  (role == Qt::TextAlignmentRole)
         {
             return int (Qt::AlignHCenter | Qt::AlignVCenter);
         }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        Get_Name = Ary_row_List->at(index.row())->Get_Name();
        Get_Name = Get_Name.split("#").last();
        if(index.column() == 0)
        {
            Ary_row_List->at(index.row())->Set_Name(value.toString());
        }
        else if(index.column() == 1)
        {
            QRegExp rxs("^[\\+\\-]?[\\d]+(\\.[\\d]+)?$");
            if(rxs.exactMatch (value.toString()))
                Ary_row_List->at(index.row())->Set_PName(value.toString());
        }
        else if(index.column() == 2)
        {
            QRegExp rxs("^[^\u4e00-\u9fa5]+$");
            if(rxs.exactMatch (value.toString()))
                Ary_row_List->at(index.row())->Set_PValue(value.toString());

        }

        return true;
    }
    return false;
}

void CyClePLastTableModel::PushBackModel(QList<QVariant> list)
{
//    int num = list.at(0).toString().split("D").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutter_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutting_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));
//    int num = list.at(0).toString().split("H").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Length_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Length_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));

    RefrushModelData();
}

void CyClePLastTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

CyClePLastTableDelegate::CyClePLastTableDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

CyClePLastTableDelegate::~CyClePLastTableDelegate()
{

}

void CyClePLastTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
//        QString name = QString::number(mos,10,4);
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 2)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
//        QString name = QString::number(mos,10,4);
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else
    {
        QItemDelegate::paint(painter,option,index);
    }
}
