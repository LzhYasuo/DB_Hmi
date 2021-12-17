#include "DModelDelegate.h"
#include <QPainter>
#include <QDebug>
#include <QFile>

#include "../Socket/RunTcp.h"

DModelItem::DModelItem(QObject* parent)
    :QObject(parent)
{

}

DModelItem::~DModelItem()
{

}

DTableModel::DTableModel()
{
    Ary_row_List = new QList<DModelItem*>();
#if 0
    this->connect(RunTcp::Get(),&RunTcp::Set_DFileValue_Signal,this,[=](QList<QVariant> List){
        this->ListPushBack(List);
    });
#else
    QFile file_D("C:\\PACnc\\DBHMI\\D1");
    if (file_D.exists())
    {
        file_D.remove();
    }
    file_D.close();

    //D
    RunTcp::Get()->Write("<load><sub>corr</sub><path>C:\\PACnc\\DBHMI</path><name>D1</name><over>yes</over></load>");

    this->connect(RunTcp::Get(),&RunTcp::Set_LoadD_Signal,this,[=](){
        QList<QStringList> List;
        QString FilePath = "C:\\PACnc\\DBHMI\\D1";
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
                int nEnd1 = myText.indexOf(" ");
                int nEnd2 = myText.indexOf(" ",nEnd1+1);
                if(nStart==-1 || nEnd1==-1 || nEnd2==-1)
                {
                    nval1=nval2="";
                }
                nval1=myText.mid(nStart+1,nEnd1-nStart-1);
                nval2=myText.mid(nEnd1+1,nEnd2-nEnd1-1);

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
    //        DModelItem* date = new DModelItem();
    //        date->Set_Name("#" + QString("%1").arg(i));
    //        date->Set_DName("");
    //        date->Set_DValue("");
    //        Ary_row_List->push_back(date);
    //    }
}

DTableModel::~DTableModel()
{

}

Qt::ItemFlags DTableModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0)
        return QAbstractItemModel::flags(index);
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
}

int DTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return Ary_row_List->size();
}
int DTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 3;
}
QVariant DTableModel::data(const QModelIndex &index, int role) const
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
            return Ary_row_List->at(index.row())->Get_DName();
        else if(index.column() == 2)
            return Ary_row_List->at(index.row())->Get_DValue();
    }
    return QVariant();
}
QVariant DTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void DTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void DTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void DTableModel::RefrushModel(DModelItem* item)
{
    const int count = Ary_row_List->size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List->push_back(item);
    endInsertRows();
}

bool DTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
            Ary_row_List->at(index.row())->Set_DName(value.toString());
        }
        else if(index.column() == 2)
        {
            Ary_row_List->at(index.row())->Set_DValue(value.toString());
        }
//        RunTcp::Get()->WriteD1(Get_Name,Ary_row_List->at(index.row())->Get_DName(),Ary_row_List->at(index.row())->Get_DValue());
        return true;
    }
    return false;
}

void DTableModel::ListPushBack(QList<QStringList> msg)
{
    for(int i = 0; i < msg.size(); i++)
    {
        DModelItem* date = new DModelItem();
        date->Set_Name("D" + QString::number(i + 1));
        date->Set_DName(msg.at(i).at(0));
        date->Set_DValue(msg.at(i).at(1));
        Ary_row_List->push_back(date);
        RefrushModelData();
    }
}

void DTableModel::ListPushBack(QList<QVariant> List)
{
     DModelItem* date = new DModelItem();
     date->Set_Name(List.at(0).toString());
     date->Set_DName(List.at(1).toString());
     date->Set_DValue(List.at(2).toString());
     Ary_row_List->push_back(date);
     RefrushModelData();
}

QList<QStringList> DTableModel::ListPopBack()
{
    QList<QStringList> List;
    for(int i = 0; i < Ary_row_List->size(); i++)
    {
        QStringList msg;
        msg << Ary_row_List->at(i)->Get_DName();
        msg << Ary_row_List->at(i)->Get_DValue();
        List.push_back(msg);
    }

    return List;
}

void DTableModel::Clear_Table_Data()
{
    for(int i = 0; i < Ary_row_List->size(); i++)
    {
        Ary_row_List->at(0)->deleteLater();
    }
    Ary_row_List->clear();
}

void DTableModel::PushBackModel(QList<QVariant> list)
{
//    int num = list.at(0).toString().split("D").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutter_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutting_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));
//    int num = list.at(0).toString().split("H").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Length_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Length_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));

    RefrushModelData();
}

void DTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

DTableDelegate::DTableDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

DTableDelegate::~DTableDelegate()
{

}

void DTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
