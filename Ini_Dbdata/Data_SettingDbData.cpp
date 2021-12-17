#include "Data_SettingDbData.h"
#include <QDebug>
#include <QDateTime>

Data_SettingDbData* Data_SettingDbData::Get()
{
    static Data_SettingDbData data;
    return &data;
}


Data_SettingDbData::Data_SettingDbData()
{

}

Data_SettingDbData::~Data_SettingDbData()
{

}

int Data_SettingDbData::Get_GlobalMax(GlobalSettingType type)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).max;
        }
    }
    return -1;
}

int Data_SettingDbData::Get_GlobalMin(GlobalSettingType type)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).min;
        }
    }
    return -1;
}

int Data_SettingDbData::Get_GlobalDecimal(GlobalSettingType type)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).decimalPoint;
        }
    }

    return -1;
}

QString Data_SettingDbData::Get_GlobalText(GlobalSettingType type)
{
        for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).Text;
        }
    }
    return "";
}

QString Data_SettingDbData::Get_GlobalUnit(GlobalSettingType type)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).unit;
        }
    }

    return "";
}

QString Data_SettingDbData::Get_GlobalP(GlobalSettingType type)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).PValue.p;
        }
    }
    return "";
}

QVariant Data_SettingDbData::Get_GlobalValue(GlobalSettingType type)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).PValue.value;
        }
    }
    return QVariant();
}

QStringList Data_SettingDbData::Get_GlobalComboxList(GlobalSettingType type)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            return GlobalList.at(i).ComboxList;
        }
    }
    return QStringList();
}

QStringList Data_SettingDbData::Get_GlobalPList()
{
    QStringList val;
    for(int i = 0; i < GlobalList.size(); i++)
    {
        val.push_back(GlobalList.at(i).PValue.p);
    }
    return val;
}

QVariantList Data_SettingDbData::Get_GlobalValueList()
{
    QVariantList val;
    for(int i = 0; i < GlobalList.size(); i++)
    {
        val.push_back(GlobalList.at(i).PValue.value);
    }
    return val;
}


#if 0
void Data_SettingDbData::Set_GlbalMax(GlobalSettingType type,int value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].max = value;
        }
    }
}
void Data_SettingDbData::Set_GlobalMin(GlobalSettingType type,int value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].min = value;
        }
    }
}
void Data_SettingDbData::Set_GlobalDecimal(GlobalSettingType type,int value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].decimalPoint = value;
        }
    }
}
void Data_SettingDbData::Set_GlobalText(GlobalSettingType type,QString value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].Text = value;
        }
    }
}
void Data_SettingDbData::Set_GlobalUnit(GlobalSettingType type,QString value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].unit = value;
        }
    }
}
void Data_SettingDbData::Set_GlobalP(GlobalSettingType type,QString value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].PValue.p = value;
        }
    }
}
void Data_SettingDbData::Set_GlobalValue(GlobalSettingType type,QVariant value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].PValue.value = value;
        }
    }
}

void Data_SettingDbData::Set_GlobalComboxList(GlobalSettingType type,QStringList valueList)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].ComboxList = valueList;
        }
    }
}
#endif

void Data_SettingDbData::GlobalPush(GlobalValue v)
{
    GlobalList.push_back(v);
}

void Data_SettingDbData::Set_GlobalPValue(QVariantList msg)
{
    if(msg.size() != GlobalList.size() * 2)
    {
        return;
    }
    int PValueCount = 0;
    for(int i = 0; i < GlobalList.size(); i++)
    {
        for(int j = 0; j < 2; j++,PValueCount++)
        {
            if(PValueCount % 2 == 0)
                GlobalList[i].PValue.p = msg.at(PValueCount).toString();
            else if(PValueCount % 2 == 1)
                GlobalList[i].PValue.value = msg.at(PValueCount);
        }
    }
    emit Refursh_Global();
}

void Data_SettingDbData::Set_GlobalValue(GlobalSettingType type,QVariant value)
{
    for(int i = 0; i < GlobalList.size(); i++)
    {
        if(GlobalList.at(i).type == type)
        {
            GlobalList[i].PValue.value = value;
        }
    }
}

//切割参数
int Data_SettingDbData::Get_CuttingMax(CuttingSettingType type)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            return CuttingList.at(i).max;
        }
    }
    return 0;
}

int Data_SettingDbData::Get_CuttingMin(CuttingSettingType type)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            return CuttingList.at(i).min;
        }
    }
    return 0;
}
int Data_SettingDbData::Get_CuttingDecimal(CuttingSettingType type)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            return CuttingList.at(i).decimalPoint;
        }
    }
    return 0;
}

int Data_SettingDbData::Get_CuttingGuiType(CuttingSettingType type)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            return CuttingList.at(i).Gui_Type;
        }
    }
    return 0;
}

QString Data_SettingDbData::Get_CuttingText(CuttingSettingType type)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            return CuttingList.at(i).Text;
        }
    }
    return "";
}

QString Data_SettingDbData::Get_CuttingUnit(CuttingSettingType type)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            return CuttingList.at(i).unit;
        }
    }
    return "";
}

QString Data_SettingDbData::Get_CuttingP(CuttingSettingType type,QVariant value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int pValueCount = 0; pValueCount < CuttingList.at(i).PValue_List.size(); pValueCount++)
            {
                if(CuttingList.at(i).PValue_List.at(pValueCount).value == value)
                {
                    return CuttingList.at(i).PValue_List.at(pValueCount).p;
                }
            }
        }
    }
    return "";
}

QVariant Data_SettingDbData::Get_CuttingValue(CuttingSettingType type,QString key)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int pValueCount = 0; pValueCount < CuttingList.at(i).PValue_List.size(); pValueCount++)
            {
                if(CuttingList.at(i).PValue_List.at(i).p == key)
                {
                    return CuttingList.at(i).PValue_List.at(i).value;
                }
            }
        }
    }
    return QVariant();
}

QStringList Data_SettingDbData::Get_CuttingComboxList(CuttingSettingType type)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            return CuttingList.at(i).ComboxList;
        }
    }
    return QStringList();
}

int Data_SettingDbData::Get_CuttingMax(int index)
{
    if(index < CuttingList.size())
    {
        return CuttingList[index].max;
    }
    return 0;
}

int Data_SettingDbData::Get_CuttingMin(int index)
{
    if(index < CuttingList.size())
    {
        return CuttingList[index].min;
    }
    return 0;
}

int Data_SettingDbData::Get_CuttingDecimal(int index)
{
    if(index < CuttingList.size())
    {
        return CuttingList[index].decimalPoint;
    }
    return 0;
}

int Data_SettingDbData::Get_CuttingGuiType(int index)
{
    if(index < CuttingList.size())
    {
        return CuttingList[index].Gui_Type;
    }
    return 0;
}

QString Data_SettingDbData::Get_CuttingText(int index)
{
    if(index < CuttingList.size())
    {
        return CuttingList[index].Text;
    }
    return "";
}

QString Data_SettingDbData::Get_CuttingUnit(int index)
{
    if(index < CuttingList.size())
    {
        return CuttingList[index].unit;
    }
    return "";
}

QString Data_SettingDbData::Get_CuttingP(int index,QVariant value)
{
    if(index < CuttingList.size())
    {
        for(int i = 0; i < CuttingList.at(index).PValue_List.size(); i++)
        {
            if(CuttingList.at(index).PValue_List.at(i).value == value)
            {
                return CuttingList.at(index).PValue_List.at(i).p;
            }
        }
    }
    return "";
}

QVariant Data_SettingDbData::Get_CuttingValue(int index,QString key)
{
    if(index < CuttingList.size())
    {
        for(int i = 0; i < CuttingList.at(index).PValue_List.size(); i++)
        {
            if(CuttingList.at(index).PValue_List.at(i).p == key)
            {
                return CuttingList.at(index).PValue_List.at(i).value;
            }
        }
    }
    return QVariant();
}

QStringList Data_SettingDbData::Get_CuttingComboxList(int index)
{
    if(index < CuttingList.size())
    {
        return CuttingList[index].ComboxList;
    }
    return QStringList();
}

QList<int> Data_SettingDbData::Get_CuttingListMax()
{
    QList<int> ValueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        ValueList.push_back(CuttingList.at(i).max);
    }
    return ValueList;
}

QList<int> Data_SettingDbData::Get_CuttingListMin()
{
    QList<int> ValueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        ValueList.push_back(CuttingList.at(i).min);
    }
    return ValueList;
}

QList<int> Data_SettingDbData::Get_CuttingListDecimal()
{
    QList<int> ValueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        ValueList.push_back(CuttingList.at(i).decimalPoint);
    }
    return ValueList;
}

QList<int> Data_SettingDbData::Get_CuttingListGuiType()
{
    QList<int> ValueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        ValueList.push_back(CuttingList.at(i).Gui_Type);
    }
    return ValueList;
}

QStringList Data_SettingDbData::Get_CuttingListText()
{
    QStringList ValueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        ValueList.push_back(CuttingList.at(i).Text);
    }
    return ValueList;
}
QStringList Data_SettingDbData::Get_CuttingListUnit()
{
    QStringList ValueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        ValueList.push_back(CuttingList.at(i).unit);
    }
    return ValueList;
}
QStringList Data_SettingDbData::Get_CuttingListP(CuttingSettingType type)
{
    QStringList pList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int pValueCount = 0; pValueCount < CuttingList.at(i).PValue_List.size(); pValueCount++)
            {
                pList.push_back(CuttingList.at(i).PValue_List.at(pValueCount).p);
            }
        }
    }
    return pList;
}
QList<QVariant> Data_SettingDbData::Get_CuttingListValue(CuttingSettingType type)
{
    QList<QVariant> ValueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int pValueCount = 0; pValueCount < CuttingList.at(i).PValue_List.size(); pValueCount++)
            {
                ValueList.push_back(CuttingList.at(i).PValue_List.at(pValueCount).value);
            }
        }
    }
    return ValueList;
}
QList<QStringList> Data_SettingDbData::Get_CuttingComboxListList()
{
    QList<QStringList> valueList;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        valueList.push_back(CuttingList.at(i).ComboxList);
    }
    return valueList;
}

QStringList Data_SettingDbData::Get_CuttingListP()
{
    QStringList str;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        for(int j = 0; j < CuttingList.at(i).PValue_List.size(); j++)
        {
            str.push_back(CuttingList.at(i).PValue_List.at(j).p);
        }
    }
    return str;
}

QVariantList Data_SettingDbData::Get_CuttingListValue()
{
    QVariantList str;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        for(int j = 0; j < CuttingList.at(i).PValue_List.size(); j++)
        {
            str.push_back(CuttingList.at(i).PValue_List.at(j).value);
        }
    }
    return str;
}

QVariant Data_SettingDbData::Get_CuttingValue(int index,int index1)
{
    return CuttingList.at(index).PValue_List.at(index1).value;
}

#if 0
void Data_SettingDbData::Set_CuttingMax(CuttingSettingType type,int value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            CuttingList[i].max = value;
        }
    }
}

void Data_SettingDbData::Set_CuttingMin(CuttingSettingType type,int value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            CuttingList[i].min = value;
        }
    }
}
void Data_SettingDbData::Set_CuttingDecimal(CuttingSettingType type,int value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            CuttingList[i].decimalPoint = value;
        }
    }
}
void Data_SettingDbData::Set_CuttingText(CuttingSettingType type,QString value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            CuttingList[i].Text = value;
        }
    }
}
void Data_SettingDbData::Set_CuttingUnit(CuttingSettingType type,QString value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            CuttingList[i].unit = value;
        }
    }
}
void Data_SettingDbData::Set_CuttingP(CuttingSettingType type,QVariant value,QString p)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int pCount = 0; pCount < CuttingList.at(i).PValue_List.size(); pCount++)
            {
                if(CuttingList.at(i).PValue_List.at(pCount).value == value)
                {
                    CuttingList[i].PValue_List[pCount].p = p;
                }
            }
        }
    }
}

#if 0
void Data_SettingDbData::Set_CuttingP(CuttingSettingType type,QStringList p)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int z = 0; z < p.size(); z++)
            {
                CuttingList.at(i).PValue_List.at(i)->p = p.at(z);
            }
        }
    }
}

void Set_CuttingValue(CuttingSettingType type,QList<QVariant> valueList);
#endif

void Data_SettingDbData::Set_CuttingValue(CuttingSettingType type,QString p,QVariant value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int pCount = 0; pCount < CuttingList.at(i).PValue_List.size(); pCount++)
            {
                if(CuttingList.at(i).PValue_List.at(pCount).p == p)
                {
                    CuttingList[i].PValue_List[pCount].value = value;
                }
            }
        }
    }
}

void Data_SettingDbData::Set_CuttingComboxList(CuttingSettingType type,QStringList value)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            CuttingList[i].ComboxList = value;
        }
    }
}
#endif

void Data_SettingDbData::Set_CuttingPValue(QVariantList msg)
{
    if(msg.size() != CuttingList.size() * 16)
    {
        return;
    }
    int msgCount = 0;
    for(int i = 0; i < CuttingList.size(); i++)
    {
        for(int j = 0; j <  8 ; j++)
        {
            for(int z = 0 ; z < 2; z++,msgCount++)
            {
                if( msgCount % 2  == 0)
                    CuttingList[i].PValue_List[j].p = msg.at(msgCount).toString();
                else if(msgCount % 2 == 1)
                    CuttingList[i].PValue_List[j].value = msg.at(msgCount);
            }
        }
    }
    emit Refursh_Cutting();
}

void Data_SettingDbData::Set_CuttingValue(CuttingSettingType type,QVariantList list)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(CuttingList.at(i).type == type)
        {
            for(int Listcount = 0; Listcount < list.size(); Listcount++)
            {
                CuttingList[i].PValue_List[Listcount].value = list.at(Listcount);
            }
        }
    }
}

void Data_SettingDbData::Set_CuttingValue(int index,QVariantList list)
{
    for(int i = 0; i < CuttingList.size(); i++)
    {
        if(i == index)
        {
            for(int Listcount = 0; Listcount < list.size(); Listcount++)
            {
                CuttingList[i].PValue_List[Listcount].value = list.at(Listcount);
            }
        }
    }
}

void Data_SettingDbData::Set_CuttingValue(int index,int index1,QVariant list)
{
    CuttingList[index].PValue_List[index1].value = list;
}

void Data_SettingDbData::CuttingPush(CuttingValue val)
{
    CuttingList.push_back(val);
}

//穿孔参数
int Data_SettingDbData::Get_PerforatedMax(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).max;
        }
    }
    return 0;
}

int Data_SettingDbData::Get_PerforatedMin(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).min;
        }
    }
    return 0;
}

int Data_SettingDbData::Get_PerforatedDecimal(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).decimalPoint;
        }
    }
    return 0;
}

QString Data_SettingDbData::Get_PerforatedText(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).Text;
        }
    }
    return "";
}

QString Data_SettingDbData::Get_PerforatedUnit(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).unit;
        }
    }
    return "";
}

QVariant Data_SettingDbData::Get_PerforatedValue(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).PValue.value;
        }
    }
    return QVariant();
}

QStringList Data_SettingDbData::Get_PerforatedComboxList(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).ComboxList;
        }
    }
    return QStringList();
}

QString Data_SettingDbData::Get_PerforatedP(PerforatedSettingType type)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            return PerforatedList.at(i).PValue.p;
        }
    }
    return "";
}

QStringList Data_SettingDbData::Get_PerforatedPList()
{
    QStringList val;
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        val.push_back(PerforatedList.at(i).PValue.p);
    }
    return val;
}

QVariantList Data_SettingDbData::Get_PerforatedValueList()
{
    QVariantList val;
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        val.push_back(PerforatedList.at(i).PValue.value);
    }
    return val;
}

#if 0
void Data_SettingDbData::Set_PerforatedMax(PerforatedSettingType type,int value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].max = value;
        }
    }
}

void Data_SettingDbData::Set_PerforatedMin(PerforatedSettingType type,int value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].min = value;
        }
    }
}

void Data_SettingDbData::Set_PerforatedDecimal(PerforatedSettingType type,int value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].decimalPoint = value;
        }
    }
}

void Data_SettingDbData::Set_PerforatedText(PerforatedSettingType type,QString value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].Text = value;
        }
    }
}

void Data_SettingDbData::Set_PerforatedUnit(PerforatedSettingType type,QString value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].unit = value;
        }
    }
}

void Data_SettingDbData::Set_PerforatedP(PerforatedSettingType type,QString value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].PValue.p = value;
        }
    }
}

void Data_SettingDbData::Set_PerforatedValue(PerforatedSettingType type,QVariant value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].PValue.value = value;
        }
    }
}

void Data_SettingDbData::Set_PerforatedComboxList(PerforatedSettingType type,QStringList value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            GlobalList[i].ComboxList = value;
        }
    }
}
#endif

void Data_SettingDbData::PerforatedPush(PerforatedValue val)
{
    PerforatedList.push_back(val);
}

void Data_SettingDbData::Set_PerforatedPValue(QVariantList msg)
{
    if(msg.size() != PerforatedList.size() * 2)
    {
        return;
    }
    int PValueCount = 0;
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        for(int j = 0; j < 2; j++,PValueCount++)
        {
            if(PValueCount % 2 == 0)
                PerforatedList[i].PValue.p = msg.at(PValueCount).toString();
            else if(PValueCount % 2 == 1)
                PerforatedList[i].PValue.value = msg.at(PValueCount);
        }
    }
    emit Refursh_Perforated();
}

void Data_SettingDbData::Set_PerforatedValue(PerforatedSettingType type,QVariant value)
{
    for(int i = 0; i < PerforatedList.size(); i++)
    {
        if(PerforatedList.at(i).type == type)
        {
            PerforatedList[i].PValue.value = value;
        }
    }
}

int Data_SettingDbData::Get_Max_Cutting_num()
{
    return CuttingList.size();
}

QString Data_SettingDbData::Add_CuttingType()
{
   const QString msg = "iniCuttingTableType";
   return msg + QString::number(CuttingList.size());
}

void Data_SettingDbData::Ini_Write_into(QString Text,int Max,int Min,int Decimal,int GuiType,QStringList PList,QStringList ComboList)
{
    emit Write_into_ini_Signal(Text,Max,Min,Decimal,GuiType,PList,ComboList);
}

void Data_SettingDbData::Ini_Delete_into(QStringList msg)
{
    emit Delete_into_ini_Signal(msg);
}

//数据写入数据库
void Data_SettingDbData::DB_Write_into()
{
   QStringList GlobalStrList = Get_GlobalPList();
   QVariantList GlobalValueList = Get_GlobalValueList();

   QStringList CuttingStrList = Get_CuttingListP();
   QVariantList CuttingValueList = Get_CuttingListValue();

   QStringList PerforatedStrList = Get_PerforatedPList();
   QVariantList PerforatedValueList = Get_PerforatedValueList();

   QList<QStringList> val;
   val << GlobalStrList << CuttingStrList << PerforatedStrList;
   QList<QVariantList> valueval;
   valueval << GlobalValueList << CuttingValueList << PerforatedValueList;

   emit Write_into_DB_Signal(val,valueval);
}

void Data_SettingDbData::DB_Send_CncPlc()
{
    QStringList GlobalStrList = Get_GlobalPList();
    QVariantList GlobalValueList = Get_GlobalValueList();

    QStringList CuttingStrList = Get_CuttingListP();
    QVariantList CuttingValueList = Get_CuttingListValue();

    QStringList PerforatedStrList = Get_PerforatedPList();
    QVariantList PerforatedValueList = Get_PerforatedValueList();

    GlobalStrList << CuttingStrList << PerforatedStrList;
    GlobalValueList << CuttingValueList << PerforatedValueList;

    if(GlobalStrList.size() != GlobalValueList.size())
    {
        qDebug() << "参数不对等！";
        return;
    }
    QString P;
    QString Value;
    for(int i = 0; i < GlobalStrList.size(); i++)
    {
        P += GlobalStrList.at(i) + ",";
        Value += GlobalValueList.at(i).toString() + ",";
    }
    P = P.left(P.length() - 1);
    Value = Value.left(Value.length() - 1);
}

void Data_SettingDbData::DB_File_SaveAS(QString msg)
{
    emit Save_As_DB_Signal(msg);
}
