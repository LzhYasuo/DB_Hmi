#include "HModelDelegate.h"
#include <QPainter>
#include <QDebug>
#include <QFile>

#include "../Socket/RunTcp.h"

HModelItem::HModelItem(QObject* parent)
    :QObject(parent)
{

}

HModelItem::~HModelItem()
{

}

HTableModel::HTableModel()
{
    Ary_row_List = new QList<HModelItem*>();
#if 0
    this->connect(RunTcp::Get(),&RunTcp::Set_HFileValue_Signal,this,[=](QList<QVariant> msg){
        this->ListPushBack(msg);
    });
#else
    QFile file_H("C:\\PACnc\\DBHMI\\H1");
    if (file_H.exists())
    {
        file_H.remove();
    }
    file_H.close();

    //H
    RunTcp::Get()->Write("<load><sub>length</sub><path>C:\\PACnc\\DBHMI</path><name>H1</name><over>yes</over></load>");

    this->connect(RunTcp::Get(),&RunTcp::Set_LoadH_Signal,this,[=](){
        QList<QStringList> List;
        QString FilePath = "C:\\PACnc\\DBHMI\\H1";
        QFile cfile(FilePath);
        if(!cfile.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << " Could not open the file for reading";
            return;
        }
        QTextStream in(&cfile);
        QString myText;
        while(!in.atEnd())
        {
            myText = in.readLine();
            if(myText.indexOf("=")!=-1)
            {
                QString nval1,nval2;
                int nStart=myText.indexOf("=");
                int nEnd1 = myText.indexOf(" ",nStart+1);
                if(nStart==-1 || nEnd1==-1)
                {
                    nval1=nval2="";
                }
                nval1=myText.mid(nStart+1,nEnd1-nStart-1);
                nval2=myText.mid(nEnd1+1);

                QStringList msg;
                msg << nval1 << nval2;
                List.push_back(msg);
            }
        }
        cfile.close();
        ListPushBack(List);
        return;
    });
#endif
//    QStringList ver;

//    for(int i = 1; i <= 128; i++)
//    {
//        HModelItem* date = new HModelItem();
//        date->Set_Name("#" + QString("%1").arg(i));
//        date->Set_HName("");
//        date->Set_HValue("");
//        Ary_row_List->push_back(date);
//    }
}

HTableModel::~HTableModel()
{

}

Qt::ItemFlags HTableModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0)
        return QAbstractItemModel::flags(index);
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
}

int HTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return Ary_row_List->size();
}
int HTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 3;
}
QVariant HTableModel::data(const QModelIndex &index, int role) const
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
QVariant HTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void HTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void HTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void HTableModel::RefrushModel(HModelItem* item)
{
    const int count = Ary_row_List->size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List->push_back(item);
    endInsertRows();
}

bool HTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(Ary_row_List == nullptr || Ary_row_List->size() < 1 || !index.isValid())
        return false;
    if  (role == Qt::TextAlignmentRole)
         {
             return int (Qt::AlignHCenter | Qt::AlignVCenter);
         }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(!VerifyNumber(value.toString()))
            return false;
        Get_Name = Ary_row_List->at(index.row())->Get_Name();
        if(index.column() == 1)
        {
            Ary_row_List->at(index.row())->Set_HName(value.toString());
        }
        else if(index.column() == 2)
        {
            Ary_row_List->at(index.row())->Set_HValue(value.toString());
        }
#if 0
        RunTcp::Get()->WriteH1(Get_Name,Ary_row_List->at(index.row())->Get_HName(),Ary_row_List->at(index.row())->Get_HValue());
#endif

        return true;
    }
    return false;
}

void HTableModel::PushBackModel(QList<QVariant> list)
{
//    int num = list.at(0).toString().split("D").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutter_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutting_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));
//    int num = list.at(0).toString().split("H").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Length_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Length_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));

    RefrushModelData();
}

void HTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

void HTableModel::ListPushBack(QList<QVariant> List)
{
    HModelItem* date = new HModelItem();
    date->Set_Name(List.at(0).toString());
    date->Set_HName(List.at(1).toString());
    date->Set_HValue(List.at(2).toString());
    Ary_row_List->push_back(date);

    RefrushModelData();
}

void HTableModel::ListPushBack(QList<QStringList> List)
{
    for(int i = 0; i < List.size(); i++)
    {
        HModelItem* date = new HModelItem();
        date->Set_Name("H" + QString::number(i + 1));
        date->Set_HName(List.at(i).at(0));
        date->Set_HValue(List.at(i).at(1));
        Ary_row_List->push_back(date);
    }
    RefrushModelData();
}

QList<QStringList> HTableModel::ListPopBack()
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

void HTableModel::Clear_Table_Data()
{
    for(int i = 0; i < Ary_row_List->size(); i++)
    {
        Ary_row_List->at(0)->deleteLater();
    }
    Ary_row_List->clear();
}

HTableDelegate::HTableDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

HTableDelegate::~HTableDelegate()
{

}

void HTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
        float mos = index.model()->data(index,Qt::DisplayRole).toFloat();
        QString name = QString::number(mos,10,4);
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,name,o);
    }
    else if(index.column() == 2)
    {
        float mos = index.model()->data(index,Qt::DisplayRole).toFloat();
        QString name = QString::number(mos,10,4);
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,name,o);
    }
    else
    {
        QItemDelegate::paint(painter,option,index);
    }
}
