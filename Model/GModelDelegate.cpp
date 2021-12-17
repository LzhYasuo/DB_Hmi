#include "GModelDelegate.h"
#include <QPainter>
#include <QDebug>
#include <QFile>

#include "../Socket/RunTcp.h"

GModelItem::GModelItem(QObject* parent)
    :QObject(parent)
{

}

GModelItem::~GModelItem()
{

}

GTableModel::GTableModel()
{
    Ary_row_List = new QList<GModelItem*>();
#if 0
    this->connect(RunTcp::Get(),&RunTcp::Set_GFileValue_Signal,[=](QList<QVariant> msg){
        this->ListPushBack(msg);
    });
#else
    QFile file_G("C:\\PACnc\\DBHMI\\G1");
    if (file_G.exists())
    {
        file_G.remove();
    }
    file_G.close();

    //G
    RunTcp::Get()->Write("<load><sub>offset</sub><path>C:\\PACnc\\DBHMI</path><name>G1</name><over>yes</over></load>");

    this->connect(RunTcp::Get(),&RunTcp::Set_LoadG_Signal,this,[=](){
        bool ok = false;
        QList<QStringList> List;
        QString FilePath = "C:\\PACnc\\DBHMI\\G1";
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
                QString nval1,nval2,nval3,nval4;
                int nStart=myText.indexOf("=");
                int nEnd1 = myText.indexOf("=",nStart+1);
                int nEnd2 = myText.indexOf("=",nEnd1+1);
                int nEnd3 = myText.indexOf("=",nEnd2+1);
                if(nStart==-1 || nEnd1==-1 || nEnd2==-1 || nEnd3==-1)
                {
                    nval1=nval2=nval3=nval4="";
                }
                nval1=myText.mid(nStart+1,nEnd1-nStart-1-1);
                nval2=myText.mid(nEnd1+1,nEnd2-nEnd1-1-1);
                nval3=myText.mid(nEnd2+1,nEnd3-nEnd2-1-1);
                nval4=myText.mid(nEnd3+1);

                if(!ok)
                {
                    QString nval = Get_NcdaName(myText.mid(nStart -1 ,nEnd1-nStart-1-1));
                    QString nva2 = Get_NcdaName(myText.mid(nEnd1 - 1,nEnd2-nEnd1-1-1));
                    QString nva3 = Get_NcdaName(myText.mid(nEnd2 -1 ,nEnd3-nEnd2-1-1));
                    QString nva4 = Get_NcdaName(myText.mid(nEnd3 -1));
                    NacdName << nval << nva2 << nva3 << nva4;
                    ok = true;
                }

                QStringList msg;
                msg << nval1 << nval2 << nval3 << nval4;
                List.push_back(msg);
            }
        }
        cfile.close();
        this->ListPushBack(List);
        //QMessageBox::warning(NULL,"警告","close G");
        return;
    });
#endif
//    QStringList ver;

//    for(int i = 1; i <= 128; i++)
//    {
//        GModelItem* date = new GModelItem();
//        date->Set_Name("#" + QString("%1").arg(i));
//        date->Set_XValue("");
//        date->Set_YValue("");
//        date->Set_ZValue("");
//        date->Set_AVaule("");
//        Ary_row_List->push_back(date);
//    }
}

QStringList GTableModel::Get_NameNcda()
{
    return NacdName;
}

void GTableModel::Clear_Table_Data()
{
    for(int i = 0; i < Ary_row_List->size(); i++)
    {
        Ary_row_List->at(0)->deleteLater();
    }
    Ary_row_List->clear();
}

QString GTableModel::Get_NcdaName(QString msg)
{
    if(msg.indexOf("X") != -1)
    {
       return "X";
    }
    if(msg.indexOf("Y") != -1)
    {
        return "Y";
    }
    if(msg.indexOf("Z") != -1)
    {
        return "Z";
    }
    if(msg.indexOf("A") != -1)
    {
        return "A";
    }
//    else if(msg.indexOf("A") == -1)
//    {
//        return "A";
//    }
//    else if(msg.indexOf("AAS") != -1)
//    {
//        return "A";
//    }
//    else if(msg.indexOf("ASF") != -1)
//    {
//        return "B";
//    }
}

GTableModel::~GTableModel()
{

}

Qt::ItemFlags GTableModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0)
        return QAbstractItemModel::flags(index);
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
}

int GTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return Ary_row_List->size();
}
int GTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 5;
}
QVariant GTableModel::data(const QModelIndex &index, int role) const
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
            return Ary_row_List->at(index.row())->Get_XValue();
        else if(index.column() == 2)
            return Ary_row_List->at(index.row())->Get_YValue();
        else if(index.column() == 3)
        {
            return Ary_row_List->at(index.row())->Get_ZValue();
        }
        else if(index.column() == 4)
        {
            return Ary_row_List->at(index.row())->Get_AValue();
        }
    }
    return QVariant();
}
QVariant GTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void GTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void GTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void GTableModel::RefrushModel(GModelItem* item)
{
    const int count = Ary_row_List->size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List->push_back(item);
    endInsertRows();
}

bool GTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
        qDebug() << Get_Name;
        if(index.column() == 1)
        {
            Ary_row_List->at(index.row())->Set_XValue(value.toString());
//            RunTcp::Get()->WriteG1(Get_Name,Ary_row_List->at(index.row())->Get_XValue());
        }
        else if(index.column() == 2)
        {
            Ary_row_List->at(index.row())->Set_YValue(value.toString());
//            RunTcp::Get()->WriteG1(Get_Name,"",Ary_row_List->at(index.row())->Get_YValue());
        }
        else if(index.column() == 3)
        {
            Ary_row_List->at(index.row())->Set_ZValue(value.toString());
//            RunTcp::Get()->WriteG1(Get_Name,"","",Ary_row_List->at(index.row())->Get_ZValue());
        }
        else if(index.column() == 4)
        {
            Ary_row_List->at(index.row())->Set_AVaule(value.toString());
//            RunTcp::Get()->WriteG1(Get_Name,"","","",Ary_row_List->at(index.row())->Get_AValue());
        }

        return true;
    }
    return false;
}

void GTableModel::PushBackModel(QList<QVariant> list)
{
//    int num = list.at(0).toString().split("D").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutter_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Diameter_Cutting_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));
//    int num = list.at(0).toString().split("H").last().toInt();
//    Ary_row_List->at(num - 1)->Set_Length_Compensation(QString::number(list.at(1).toDouble(),10,1));
//    Ary_row_List->at(num - 1)->Set_Length_Wear_Tear(QString::number(list.at(2).toDouble(),10,1));

    RefrushModelData();
}

void GTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

void GTableModel::ListPushBack(QList<QVariant> List)
{
    GModelItem* date = new GModelItem();
    date->Set_Name(List.at(0).toString());
    date->Set_XValue(List.at(1).toString());
    date->Set_YValue(List.at(2).toString());
    date->Set_ZValue(List.at(3).toString());
    date->Set_AVaule(List.at(4).toString());
    Ary_row_List->push_back(date);

    RefrushModelData();
}

void GTableModel::ListPushBack(QList<QStringList> List)
{
    for(int i = 0; i < List.size(); i++)
    {
        GModelItem* date = new GModelItem();
        date->Set_Name("G" + QString::number(54 + i));
        date->Set_XValue(List.at(i).at(0));
        date->Set_YValue(List.at(i).at(1));
        date->Set_ZValue(List.at(i).at(2));
        date->Set_AVaule(List.at(i).at(3));
        Ary_row_List->push_back(date);
    }

    RefrushModelData();
}

QList<QStringList> GTableModel::ListPopBack()
{
    QList<QStringList> List;
    for(int i = 0; i < Ary_row_List->size(); i++)
    {
        QStringList msg;
        msg << Ary_row_List->at(i)->Get_XValue();
        msg << Ary_row_List->at(i)->Get_YValue();
        msg << Ary_row_List->at(i)->Get_ZValue();
        msg << Ary_row_List->at(i)->Get_AValue();
        List.push_back(msg);
    }
    return List;
}

GTableDelegate::GTableDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

GTableDelegate::~GTableDelegate()
{

}

void GTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
    else if(index.column() == 3)
    {
        float mos = index.model()->data(index,Qt::DisplayRole).toFloat();
        QString name = QString::number(mos,10,4);
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,name,o);
    }
    else if(index.column() == 4)
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
