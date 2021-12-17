#include "Setting_Data.h"
#include <QDebug>

Setting_Data::Setting_Data()
{

}

Setting_Data::~Setting_Data()
{

}

Setting_Data* Setting_Data::Get()
{
    static Setting_Data Data;
    return &Data;
}

QList<QStringList> Setting_Data::GET_FourData(ViewType type,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{
    QList<QStringList> StrList;
    switch(type)
    {
    case MainViewType:
    {
        if(Mtype == MainView4)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    StrList.push_back(MainDataList.at(i).Name);
                    StrList.push_back(MainDataList.at(i).ChineseName);
                    StrList.push_back(MainDataList.at(i).EnglishName);
                    StrList.push_back(MainDataList.at(i).PLcInput);
                    StrList.push_back(MainDataList.at(i).PLCOutput);
                }
            }
        }
        break;
    }
    case ManualViewType:
    {
        if(Matype == ManualView1)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    StrList.push_back(ManualDataList.at(i).Name);
                    StrList.push_back(ManualDataList.at(i).ChineseName);
                    StrList.push_back(ManualDataList.at(i).EnglishName);
                    StrList.push_back(ManualDataList.at(i).PLcInput);
                    StrList.push_back(ManualDataList.at(i).PLCOutput);
                }
            }
        }
        break;
    }
    case AutoViewType:
    {
        if(Atype == AutoView1)
        {
            for(int i = 0; i < AutoDataList.size(); i++)
            {
                if(AutoDataList.at(i).type == Atype)
                {
                    StrList.push_back(AutoDataList.at(i).Name);
                    StrList.push_back(AutoDataList.at(i).ChineseName);
                    StrList.push_back(AutoDataList.at(i).EnglishName);
                    StrList.push_back(AutoDataList.at(i).PLcInput);
                    StrList.push_back(AutoDataList.at(i).PLCOutput);
                }
            }
        }
        else if(Atype == AutoView2)
        {
            for(int i = 0; i < AutoDataList.size(); i++)
            {
                if(AutoDataList.at(i).type == Atype)
                {
                    StrList.push_back(AutoDataList.at(i).Name);
                    StrList.push_back(AutoDataList.at(i).ChineseName);
                    StrList.push_back(AutoDataList.at(i).EnglishName);
                    StrList.push_back(AutoDataList.at(i).PLcInput);
                    StrList.push_back(AutoDataList.at(i).PLCOutput);
                }
            }
        }
        break;
    }
    }
    return StrList;
}

QList<QStringList> Setting_Data::GET_ThreeData(ViewType type,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{
    QList<QStringList> StrList;
    switch(type)
    {
    case MainViewType:
    {
        if(Mtype == MainView1)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    StrList.push_back(MainDataList.at(i).Name);
                    StrList.push_back(MainDataList.at(i).ChineseName);
                    StrList.push_back(MainDataList.at(i).EnglishName);
                    StrList.push_back(MainDataList.at(i).PLCOutput);
                }
            }
        }
        else if(Mtype == MainView2)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    StrList.push_back(MainDataList.at(i).Name);
                    StrList.push_back(MainDataList.at(i).ChineseName);
                    StrList.push_back(MainDataList.at(i).EnglishName);
                    StrList.push_back(MainDataList.at(i).PLCOutput);
                }
            }
        }
        else if(Mtype == MainView3)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    StrList.push_back(MainDataList.at(i).Name);
                    StrList.push_back(MainDataList.at(i).ChineseName);
                    StrList.push_back(MainDataList.at(i).EnglishName);
                    StrList.push_back(MainDataList.at(i).PLCOutput);
                }
            }
        }
        break;
    }
    case ManualViewType:
    {
        if(Matype == ManualView3)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    StrList.push_back(ManualDataList.at(i).Name);
                    StrList.push_back(ManualDataList.at(i).ChineseName);
                    StrList.push_back(ManualDataList.at(i).EnglishName);
                    StrList.push_back(ManualDataList.at(i).PLCOutput);
                }
            }
        }
        else if(Matype == ManualView5)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    StrList.push_back(ManualDataList.at(i).Name);
                    StrList.push_back(ManualDataList.at(i).ChineseName);
                    StrList.push_back(ManualDataList.at(i).EnglishName);
                    StrList.push_back(ManualDataList.at(i).PLcInput);
                }
            }
        }
        break;
    }
    case PLCMoViewType:
    {
        if(!(Ptype == PLCNothing))
        {
            for(int i = 0; i < PlcDataList.size(); i++)
            {
                if(PlcDataList.at(i).type == Ptype)
                {
                    StrList.push_back(PlcDataList.at(i).Name);
                    StrList.push_back(PlcDataList.at(i).PLCPathList);
                    StrList.push_back(PlcDataList.at(i).ChineseList);
                    StrList.push_back(PlcDataList.at(i).EnglishList);
                }
            }
        }
        break;
    }
    }
    return StrList;
}

QList<QStringList> Setting_Data::GET_TwoData(ViewType type,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{
    QList<QStringList> StrList;
    switch(type)
    {
    case ManualViewType:
    {
        if(Matype == ManualView2)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    StrList.push_back(ManualDataList.at(i).Name);
                    StrList.push_back(ManualDataList.at(i).PLcInput);
                    StrList.push_back(ManualDataList.at(i).PLCOutput);
                }
            }
        }
        break;
    }
    case DataViewType:
    {
        if(Dtype == DataView)
        {
            for(int i = 0; i < DataDataList.size(); i++)
            {
                if(DataDataList.at(i).type == Dtype)
                {
                    StrList.push_back(DataDataList.at(i).Name);
                    StrList.push_back(DataDataList.at(i).ChineseName);
                    StrList.push_back(DataDataList.at(i).EnglishName);
                }
            }
        }
        break;
    }
    }
    return StrList;
}

QList<QStringList> Setting_Data::GET_OneData(ViewType type,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{
    QList<QStringList> strList;
    switch(type)
    {
    case MainViewType:
    {
        if(Mtype == MainView5)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    strList.push_back(MainDataList.at(i).Name);
                    strList.push_back(MainDataList.at(i).strPaths);
                }
            }
        }
        else if(Mtype == MainView6)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    strList.push_back(MainDataList.at(i).Name);
                    strList.push_back(MainDataList.at(i).strPaths);
                }
            }
        }
        break;
    }
    case ManualViewType:
    {
        if(Matype == ManualView4)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    strList.push_back(ManualDataList.at(i).Name);
                    strList.push_back(ManualDataList.at(i).PLCOutput);
                }
            }
        }
        break;
    }
    }
    return strList;
}

QList<bool> Setting_Data::Get_Data_Bool()
{
    for(int i = 0 ; i < DataDataList.size(); i++)
    {
        if(DataDataList.at(i).type == DataFun)
        {
            return DataDataList.at(i).State;
        }
    }
}

bool Setting_Data::Get_Plc_Bool(PlcMoType type)
{
    for(int i = 0; i < PlcDataList.size(); i++)
    {
        if(PlcDataList.at(i).type == type)
        {
            return PlcDataList.at(i).state;
        }
    }
}

QString Setting_Data::Get_Plc_Title(PlcMoType type)
{
    for(int i = 0; i < PlcDataList.size(); i++)
    {
        if(PlcDataList.at(i).type == type)
        {
            return PlcDataList.at(i).title;
        }
    }
}

void Setting_Data::Set_FourData(ViewType type,QList<QStringList> StrList,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{

    switch(type)
    {
    case MainViewType:
    {
        if(Mtype == MainView4)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
//                    MainDataList[i].Name = StrList.at(0);
                    MainDataList[i].ChineseName = StrList.at(0);
                    MainDataList[i].EnglishName = StrList.at(1);
                    MainDataList[i].PLcInput = StrList.at(2);
                    MainDataList[i].PLCOutput = StrList.at(3);
                }
            }
        }
        break;
    }
    case ManualViewType:
    {
        if(Matype == ManualView1)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    //MainDataList[i].Name = StrList.at(0);
                    ManualDataList[i].ChineseName = StrList.at(0);
                    ManualDataList[i].EnglishName = StrList.at(1);
                    ManualDataList[i].PLcInput = StrList.at(2);
                    ManualDataList[i].PLCOutput = StrList.at(3);
                }
            }
        }
        break;
    }
    case AutoViewType:
    {
        if(Atype == AutoView1)
        {
            for(int i = 0; i < AutoDataList.size(); i++)
            {
                if(AutoDataList.at(i).type == Atype)
                {
                    //MainDataList[i].Name = StrList.at(0);
                    AutoDataList[i].ChineseName = StrList.at(0);
                    AutoDataList[i].EnglishName = StrList.at(1);
                    AutoDataList[i].PLcInput = StrList.at(2);
                    AutoDataList[i].PLCOutput = StrList.at(3);
                }
            }
        }
        else if(Atype == AutoView2)
        {
            for(int i = 0; i < AutoDataList.size(); i++)
            {
                if(AutoDataList.at(i).type == Atype)
                {
                    //MainDataList[i].Name = StrList.at(0);
                    AutoDataList[i].ChineseName = StrList.at(0);
                    AutoDataList[i].EnglishName = StrList.at(1);
                    AutoDataList[i].PLcInput = StrList.at(2);
                    AutoDataList[i].PLCOutput = StrList.at(3);
                }
            }
        }
        break;
    }
    }
}

void Setting_Data::Set_ThreeData(ViewType type,QList<QStringList> StrList,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{
    switch(type)
    {
    case MainViewType:
    {
        if(Mtype == MainView1)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    MainDataList[i].ChineseName = StrList.at(0);
                    MainDataList[i].EnglishName = StrList.at(1);
                    MainDataList[i].PLCOutput = StrList.at(2);
                }
            }
        }
        else if(Mtype == MainView2)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    MainDataList[i].ChineseName = StrList.at(0);
                    MainDataList[i].EnglishName = StrList.at(1);
                    MainDataList[i].PLCOutput = StrList.at(2);
                }
            }
        }
        else if(Mtype == MainView3)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    MainDataList[i].ChineseName = StrList.at(0);
                    MainDataList[i].EnglishName = StrList.at(1);
                    MainDataList[i].PLCOutput = StrList.at(2);
                }
            }
        }
        break;
    }
    case ManualViewType:
    {
        if(Matype == ManualView3)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    ManualDataList[i].ChineseName = StrList.at(0);
                    ManualDataList[i].EnglishName = StrList.at(1);
                    ManualDataList[i].PLcInput = StrList.at(2);
                }
            }
        }
        else if(Matype == ManualView5)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    ManualDataList[i].ChineseName = StrList.at(0);
                    ManualDataList[i].EnglishName = StrList.at(1);
                    ManualDataList[i].PLcInput = StrList.at(2);
                }
            }
        }
        break;
    }
    case PLCMoViewType:
    {
        if(Ptype == PLCNothing)
            return;
        for(int i = 0; i < ManualDataList.size(); i++)
        {
            if(PlcDataList.at(i).type == Ptype)
            {
                PlcDataList[i].PLCPathList = StrList.at(0);
                PlcDataList[i].ChineseList = StrList.at(1);
                PlcDataList[i].EnglishList = StrList.at(2);
            }
        }
        break;
    }
    }
}

void Setting_Data::Set_TwoData(ViewType type,QList<QStringList> StrList,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{
    switch(type)
    {
    case ManualViewType:
    {
        if(Matype == ManualView2)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    ManualDataList[i].PLcInput = StrList.at(0);
                    ManualDataList[i].PLCOutput = StrList.at(1);
                }
            }
        }
        break;
    }
    case DataViewType:
    {
        if(Dtype == DataView)
        {
            for(int i = 0; i < DataDataList.size(); i++)
            {
                if(DataDataList.at(i).type == Dtype)
                {
                    DataDataList[i].ChineseName = StrList.at(0);
                    DataDataList[i].EnglishName = StrList.at(1);
                }
            }
        }
        break;
    }
    }
}

void Setting_Data::Set_OneData(ViewType type,QList<QStringList> StrList,MainType Mtype/* = MainNothing*/,ManualType Matype/* = ManualNothing*/,AutoType Atype/* = AutoNothing*/,
                      DataType Dtype/* = DataNothing*/,PlcMoType Ptype/* = PLCNothing*/)
{
    switch(type)
    {
    case MainViewType:
    {
        if(Mtype == MainView5)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    MainDataList[i].strPaths = StrList.at(0);
                }
            }
        }
        else if(Mtype == MainView6)
        {
            for(int i = 0; i < MainDataList.size(); i++)
            {
                if(MainDataList.at(i).type == Mtype)
                {
                    MainDataList[i].strPaths = StrList.at(0);
                }
            }
        }
        break;
    }
    case ManualViewType:
    {
        if(Matype == ManualView4)
        {
            for(int i = 0; i < ManualDataList.size(); i++)
            {
                if(ManualDataList.at(i).type == Matype)
                {
                    ManualDataList[i].PLCOutput = StrList.at(0);
                }
            }
        }
        break;
    }
    }
}

void Setting_Data::Set_MainListData(MainType type,int row,int col,QVariant Data)
{
    QVariant SaveData;
    for(int i = 0; i < MainDataList.size(); i++)
    {
        if(MainDataList.at(i).type == type)
        {
            if(type == MainView1 || type == MainView2 || type == MainView3)
            {
                if(col == 1)
                {
                    SaveData = MainDataList.at(i).ChineseName[row];
                    MainDataList[i].ChineseName[row] = Data.toString();
                }
                else if(col == 2)
                {
                    SaveData = MainDataList.at(i).EnglishName[row];
                    MainDataList[i].EnglishName[row] = Data.toString();
                }
                else if(col == 3)
                {
                    SaveData = MainDataList.at(i).PLCOutput[row];
                    MainDataList[i].PLCOutput[row] = Data.toString();
                }
                break;
            }
            else if(type == MainView4)
            {
                if(col == 1)
                {
                    SaveData = MainDataList.at(i).ChineseName[row];
                    MainDataList[i].ChineseName[row] = Data.toString();
                }
                else if(col == 2)
                {
                    SaveData = MainDataList.at(i).EnglishName[row];
                    MainDataList[i].EnglishName[row] = Data.toString();
                }
                else if(col == 3)
                {
                    SaveData = MainDataList.at(i).PLcInput[row];
                    MainDataList[i].PLcInput[row] = Data.toString();
                }
                else if(col == 4)
                {
                    SaveData = MainDataList.at(i).PLCOutput[row];
                    MainDataList[i].PLCOutput[row] = Data.toString();
                }
                break;
            }
            else if(type == MainView5 || type == MainView6)
            {
                if(col == 1)
                {
                    SaveData = MainDataList.at(i).strPaths[row];
                    MainDataList[i].strPaths[row] = Data.toString();
                    break;
                }
            }
        }
    }
    PushBackMofityList(MainViewType,type,row,col,SaveData);
//    int ModifyTableNum = type;
//    if(type == MainView1)
//        ModifyTableNum = 1;
//    else if(type == MainView2)
//        ModifyTableNum = 2;
//    else if(type == MainView3)
//        ModifyTableNum = 3;
//    else if(type == MainView4)
//        ModifyTableNum = 4;
//    else if(type == MainView5)
//        ModifyTableNum = 5;
//    else if(type == MainView6)
//        ModifyTableNum = 6;
}
void Setting_Data::Set_ManualListData(ManualType type,int row,int col,QVariant Data)
{
    QVariant SaveData;
    for(int i = 0; i < ManualDataList.size(); i++)
    {
        if(ManualDataList.at(i).type == type)
        {
            if(type == ManualView1)
            {
                if(col == 1)
                {
                    SaveData = ManualDataList.at(i).ChineseName.at(row);
                    ManualDataList[i].ChineseName[row] = Data.toString();
                }
                else if(col == 2)
                {
                    SaveData = ManualDataList.at(i).EnglishName.at(row);
                    ManualDataList[i].EnglishName[row] = Data.toString();
                }
                else if(col == 3)
                {
                    SaveData = ManualDataList.at(i).PLcInput.at(row);
                    ManualDataList[i].PLcInput[row] = Data.toString();
                }
                else if(col == 4)
                {
                    SaveData = ManualDataList.at(i).PLCOutput.at(row);
                    ManualDataList[i].PLCOutput[row] = Data.toString();
                }
                break;
            }
            else if(type == ManualView2)
            {
                if(col == 1)
                {
                    SaveData = ManualDataList.at(i).PLcInput.at(row);
                    ManualDataList[i].PLcInput[row] = Data.toString();
                }
                else if(col == 2)
                {
                    SaveData = ManualDataList.at(i).PLCOutput.at(row);
                    ManualDataList[i].PLCOutput[row] = Data.toString();
                }
                break;
            }
            else if(type == ManualView3 || type == ManualView5)
            {
                if(col == 1)
                {
                    SaveData = ManualDataList.at(i).ChineseName.at(row);
                    ManualDataList[i].ChineseName[row] = Data.toString();
                }
                else if(col == 2)
                {
                    SaveData = ManualDataList.at(i).EnglishName.at(row);
                    ManualDataList[i].EnglishName[row] = Data.toString();
                }
                else if(row == 3)
                {
                    SaveData = ManualDataList.at(i).PLcInput.at(row);
                    ManualDataList[i].PLcInput[row] = Data.toString();
                }
                break;
            }
            else if(type == ManualView4)
            {
                if(col == 1)
                {
                    SaveData = ManualDataList.at(i).PLCOutput.at(row);
                    ManualDataList[i].PLCOutput[row] = Data.toString();
                }
                break;
            }
        }
    }
    PushBackMofityList(DataViewType,type,row,col,SaveData);
//    if(type == ManualView1)
//        ModifyTableNum = 1;
//    else if(type == ManualView2)
//        ModifyTableNum = 2;
//    else if(type == ManualView3)
//        ModifyTableNum = 3;
//    else if(type == ManualView4)
//        ModifyTableNum = 4;
//    else if(type == ManualView5)
//        ModifyTableNum = 5;
}
void Setting_Data::Set_AutotData(AutoType type,int row,int col,QVariant Data)
{
    QVariant SaveData;
    for(int i = 0; i < AutoDataList.size(); i++)
    {
        if(AutoDataList.at(i).type == type)
        {
            if(type == AutoView1 || type == AutoView2)
            {
                if(col == 1)
                {
                    SaveData = AutoDataList.at(i).ChineseName.at(row);
                    AutoDataList[i].ChineseName[row] = Data.toString();
                }
                else if(col == 2)
                {
                    SaveData = AutoDataList.at(i).EnglishName.at(row);
                    AutoDataList[i].EnglishName[row] = Data.toString();
                }
                else if(col == 3)
                {
                    SaveData = AutoDataList.at(i).PLcInput.at(row);
                    AutoDataList[i].PLcInput[row] = Data.toString();
                }
                else if(col == 4)
                {
                    SaveData = AutoDataList.at(i).PLCOutput.at(row);
                    AutoDataList[i].PLCOutput[row] = Data.toString();
                }
                break;
            }
        }
    }
    PushBackMofityList(AutoViewType,type,row,col,SaveData);
}

void Setting_Data::Set_DataData(DataType type,int row,int col,QVariant Data)
{
    QVariant SaveData;
    for(int i = 0; i < DataDataList.size(); i++)
    {
        if(DataDataList.at(i).type == type)
        {
            if(type == DataView)
            {
                if(col == 1)
                {
                    SaveData = DataDataList.at(i).ChineseName.at(row);
                    DataDataList[i].ChineseName[row] = Data.toString();
                }
                else if(col == 2)
                {
                    SaveData = DataDataList.at(i).EnglishName.at(row);
                    DataDataList[i].EnglishName[row] = Data.toString();
                }
            }
            else if(type == DataFun)
            {
                SaveData = DataDataList.at(i).State.at(row);
                DataDataList[i].State[row] = Data.toBool();
            }
            break;
        }
    }
    PushBackMofityList(DataViewType,type,row,col,SaveData);
}
void Setting_Data::Set_PlcMoListData(PlcMoType type,int row,int col,QVariant Data)
{
    QVariant SaveData;
    for(int i = 0; i < PlcDataList.size(); i++)
    {
        if(PlcDataList.at(i).type == type)
        {
            if(col == 1)
            {
                SaveData = PlcDataList.at(i).PLCPathList.at(row);
                PlcDataList[i].PLCPathList[row] = Data.toString();
            }
            else if(col == 2)
            {
                SaveData = PlcDataList.at(i).ChineseList.at(row);
                PlcDataList[i].ChineseList[row] = Data.toString();
            }
            else if(col == 3)
            {
                SaveData = PlcDataList.at(i).EnglishList.at(row);
                PlcDataList[i].EnglishList[row] = Data.toString();
            }
            break;
        }
    }
    PushBackMofityList(PLCMoViewType,type,row,col,SaveData);
}

void Setting_Data::Set_Plc_Bool(PlcMoType type,bool s)
{
    QVariant SaveData;
    int row = 0;
    for(int i = 0; i < PlcDataList.size(); i++)
    {
        if(PlcDataList.at(i).type == type)
        {
            if(PlcDataList.at(i).type == type)
            {
                SaveData = PlcDataList.at(i).state;
                PlcDataList[i].state = s;
                row = i;
            }
        }
    }
    PushBackMofityList(PLCMoViewType,type,row,5,SaveData);
}

void Setting_Data::Set_Plc_Title(PlcMoType type,QString str)
{
    QVariant SaveData;
    int row = 0;
    for(int i = 0; i < PlcDataList.size(); i++)
    {
        if(PlcDataList.at(i).type == type)
        {
            if(PlcDataList.at(i).type == type)
            {
                SaveData = PlcDataList.at(i).title;
                PlcDataList[i].title = str;
                row = i;
            }
        }
    }
    PushBackMofityList(PLCMoViewType,type,row,6,SaveData);
}

void Setting_Data::PushBackMofityList(ViewType type,int table,int row,int col,QVariant Data)
{
    //不管一个表被修改多少次 我们只需要第一次的值即可
    for(int i = 0; i < MoifyList.size(); i++)
    {
        if(type == MoifyList.at(i).type)
        {
            if(table == MoifyList.at(i).Table)
            {
                if(col == MoifyList.at(i).col)
                {
                    if(row == MoifyList.at(i).index)
                    {
                        return;
                    }
                }
            }
        }
    }

    ModifyData moData;
    moData.type = type;
    moData.Table = table;
    moData.index = row;
    moData.col = col;
    moData.Data = Data;
    MoifyList.push_back(moData);
}

void Setting_Data::PopBackMofityList()
{
    for(int i = 0; i < MoifyList.size(); i++)
    {
        if(MoifyList.at(i).type == MainViewType)
        {
            if(MoifyList.at(i).Table == 1 || MoifyList.at(i).Table == 2 || MoifyList.at(i).Table == 3)
            {
                if(MoifyList.at(i).col == 1)
                {
                    MainDataList[MoifyList.at(i).Table - 1].ChineseName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 2)
                {
                    MainDataList[MoifyList.at(i).Table - 1].EnglishName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 3)
                {
                    MainDataList[MoifyList.at(i).Table - 1].PLCOutput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
            else if(MoifyList.at(i).Table == 4)
            {
                if(MoifyList.at(i).col == 1)
                {
                    MainDataList[MoifyList.at(i).Table - 1].ChineseName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 2)
                {
                    MainDataList[MoifyList.at(i).Table - 1].EnglishName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 3)
                {
                    MainDataList[MoifyList.at(i).Table - 1].PLcInput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 3)
                {
                    MainDataList[MoifyList.at(i).Table - 1].PLCOutput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
            else if(MoifyList.at(i).Table == 5 || MoifyList.at(i).Table == 6)
            {
                if(MoifyList.at(i).col == 1)
                {
                    MainDataList[MoifyList.at(i).Table - 1].strPaths[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
        }
        else if(MoifyList.at(i).type == ManualViewType)
        {
            if(MoifyList.at(i).Table == 1)
            {
                if(MoifyList.at(i).col == 1)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].ChineseName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 2)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].EnglishName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 3)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].PLcInput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 4)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].PLCOutput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
            else if(MoifyList.at(i).Table == 2)
            {
                if(MoifyList.at(i).col == 1)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].PLcInput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 2)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].PLCOutput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
            else if(MoifyList.at(i).Table == 3 || MoifyList.at(i).Table == 5)
            {
                if(MoifyList.at(i).col == 1)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].ChineseName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 2)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].EnglishName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 3)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].PLcInput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
            else if(MoifyList.at(i).Table == 4)
            {
                if(MoifyList.at(i).col == 1)
                {
                    ManualDataList[MoifyList.at(i).Table - 1].PLCOutput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
        }
        else if(MoifyList.at(i).type == AutoViewType)
        {
            if(MoifyList.at(i).col == 1)
            {
                AutoDataList[MoifyList.at(i).Table - 1].ChineseName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
            }
            else if(MoifyList.at(i).col == 2)
            {
                AutoDataList[MoifyList.at(i).Table - 1].EnglishName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
            }
            else if(MoifyList.at(i).col == 3)
            {
                AutoDataList[MoifyList.at(i).Table - 1].PLcInput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
            }
            else if(MoifyList.at(i).col == 4)
            {
                AutoDataList[MoifyList.at(i).Table - 1].PLCOutput[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
            }
        }
        else if(MoifyList.at(i).type == DataViewType)
        {
            if(MoifyList.at(i).Table == 1)
            {
                if(MoifyList.at(i).col == 1)
                {
                    DataDataList[MoifyList.at(i).Table - 1].ChineseName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
                else if(MoifyList.at(i).col == 2)
                {
                    DataDataList[MoifyList.at(i).Table - 1].EnglishName[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
                }
            }
            else if(MoifyList.at(i).Table == 2)
            {
                DataDataList[MoifyList.at(i).Table - 1].State[MoifyList.at(i).index] = MoifyList.at(i).Data.toBool();
            }
        }
        else if(MoifyList.at(i).type == PLCMoViewType)
        {
            if(MoifyList.at(i).col == 1)
            {
                PlcDataList[MoifyList.at(i).Table - 1].PLCPathList[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
            }
            else if(MoifyList.at(i).col == 2)
            {
                PlcDataList[MoifyList.at(i).Table - 1].ChineseList[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
            }
            else if(MoifyList.at(i).col == 3)
            {
                PlcDataList[MoifyList.at(i).Table - 1].EnglishList[MoifyList.at(i).index] = MoifyList.at(i).Data.toString();
            }
            else if(MoifyList.at(i).col == 5)
            {
                PlcDataList[MoifyList.at(i).Table - 1].state = MoifyList.at(i).Data.toBool();
            }
            else if(MoifyList.at(i).col == 6)
            {
                qDebug() << MoifyList.at(i).Data.toString();
                PlcDataList[MoifyList.at(i).Table - 1].title = MoifyList.at(i).Data.toString();
            }
        }
    }
}

void Setting_Data::Write_Val_For_Ini()
{
    MoifyList.clear();
    emit Write_Init();
}

void Setting_Data::RestoreList()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        Set_MainListData(MainView1,i,1,"");
        Set_MainListData(MainView1,i,2,"");
        Set_MainListData(MainView1,i,3,"");
    }
    for(int i = 0; i < 6; i++)
    {
        Set_MainListData(MainView2,i,1,"");
        Set_MainListData(MainView2,i,2,"");
        Set_MainListData(MainView2,i,3,"");
    }
    for(int i = 0; i < 4; i++)
    {
        Set_MainListData(MainView3,i,1,"");
        Set_MainListData(MainView3,i,2,"");
        Set_MainListData(MainView3,i,3,"");
    }
    for(int i = 0; i < 4; i++)
    {
        Set_MainListData(MainView4,i,1,"");
        Set_MainListData(MainView4,i,2,"");
        Set_MainListData(MainView4,i,3,"");
        Set_MainListData(MainView4,i,4,"");
    }
    Set_MainListData(MainView5,0,1,"");
    for(int i = 0; i < 4; i++)
    {
        Set_MainListData(MainView6,i,1,"");
    }

    //手动全部设置为空 并保存在修改列表
    for(int i = 0; i < 8; i++)
    {
        Set_ManualListData(ManualView1,i,1,"");
        Set_ManualListData(ManualView1,i,2,"");
        Set_ManualListData(ManualView1,i,3,"");
        Set_ManualListData(ManualView1,i,4,"");
    }
    Set_ManualListData(ManualView2,0,1,"");
    Set_ManualListData(ManualView2,0,2,"");
    for(int i = 0; i < 4; i++)
    {
        Set_ManualListData(ManualView3,i,1,"");
        Set_ManualListData(ManualView3,i,2,"");
        Set_ManualListData(ManualView3,i,3,"");
    }
    Set_ManualListData(ManualView4,0,1,"");
    Set_ManualListData(ManualView4,1,1,"");
    for(int i = 0; i < 2; i++)
    {
        Set_ManualListData(ManualView5,i,1,"");
        Set_ManualListData(ManualView5,i,2,"");
        Set_ManualListData(ManualView5,i,3,"");
    }

    //自动设置为空
    for(int i = 0; i < 8; i++)
    {
        Set_AutotData(AutoView1,i,1,"");
        Set_AutotData(AutoView1,i,2,"");
        Set_AutotData(AutoView1,i,3,"");
        Set_AutotData(AutoView1,i,4,"");
        Set_AutotData(AutoView2,i,1,"");
        Set_AutotData(AutoView2,i,2,"");
        Set_AutotData(AutoView2,i,3,"");
        Set_AutotData(AutoView2,i,4,"");
    }

    //工艺库设置为空
    for(int i = 0; i < 8; i++)
    {
        Set_DataData(DataView,i,1,"");
        Set_DataData(DataView,i,1,"");
    }

    for(int i = 0; i < 11; i++)
    {
        Set_DataData(DataFun,i,0,false);
    }

    //PLC监控设置为空
    for(int i = 0; i < 8; i++)
    {
        PlcMoType type = PLCNothing;
        if(i == 0)
            type = PlcMoView1;
        else if(i == 1)
            type = PlcMoView2;
        else if(i == 2)
            type = PlcMoView3;
        else if(i == 3)
            type = PlcMoView4;
        else if(i == 4)
            type = PlcMoView5;
        else if(i == 5)
            type = PlcMoView6;
        else if(i == 6)
            type = PlcMoView7;
        else if(i == 7)
            type = PlcMoView8;

        Set_PlcMoListData(type,i,5,false);
        Set_PlcMoListData(type,i,6,"");
        for(int z = 0 ; z < 8; z++)
        {
            Set_PlcMoListData(type,z,1,"");
            Set_PlcMoListData(type,z,2,"");
            Set_PlcMoListData(type,z,3,"");
        }
    }

    emit InitTable();
}

void Setting_Data::Set_SettingData(SettingType type,QList<QVariant> v)
{
    for(int i = 0; i < SettingList.size(); i++)
    {
        if(SettingList.at(i).type == type)
        {
            SettingList[i].name = v.at(0).toString();
            SettingList[i].unit = v.at(1).toString();
            SettingList[i].p = v.at(2).toString();
            SettingList[i].value = v.at(3).toString();
            break;
        }
    }
}

QList<QVariant> Setting_Data::Get_SettingData(SettingType type)
{
    QList<QVariant> List;
    for(int i = 0; i < SettingList.size(); i++)
    {
        if(SettingList.at(i).type == type)
        {
            List.push_back(SettingList.at(i).name);
            List.push_back(SettingList.at(i).unit);
            List.push_back(SettingList.at(i).p);
            List.push_back(SettingList.at(i).value);
            break;
        }
    }
    return List;
}

void Setting_Data::SettingPushBack(SettingData v)
{
    SettingList.push_back(v);
}

void Setting_Data::SettingValue(SettingType type,QVariant v)
{
    for(int i = 0; i < SettingList.size(); i++)
    {
        if(SettingList.at(i).type == type)
        {
            SettingList[i].value = v;
        }
    }
}

QStringList Setting_Data::Get_AllP()
{
    QStringList PList;
    for(int i = 0; i < SettingList.size(); i++)
    {
        PList.push_back(SettingList.at(i).p);
    }

    return PList;
}

QList<QVariant> Setting_Data::Get_AllValue()
{
    QList<QVariant> ValueList;
    for(int i = 0; i < SettingList.size(); i++)
    {
        ValueList.push_back(SettingList.at(i).value);
    }

    return ValueList;
}

QList<QStringList> Setting_Data::Get_PLCMoListSystem(PlcMoType type)
{
    QList<QStringList> msg;
    for(int i = 0; i < PlcDataList.size(); i++)
    {
        if(PlcDataList.at(i).type == type)
        {
            msg.push_back(PlcDataList.at(i).PLCPathList);
            msg.push_back(PlcDataList.at(i).ChineseList);
            msg.push_back(PlcDataList.at(i).EnglishList);
            break;
        }
    }
    return msg;
}
