#include "DataDbdata.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QFuture>
#include <QtConcurrent>

#include "Public/Public_Function.h"
#include "Data_SettingDbData.h"

DataDbdata::DataDbdata()
{
    this->connect(Data_SettingDbData::Get(),&Data_SettingDbData::Save_As_DB_Signal,this,&DataDbdata::Save_As_DB_Slot);
    this->connect(this,&DataDbdata::InitDataFile,Data_SettingDbData::Get(),&Data_SettingDbData::DB_Write_into);
    this->connect(Data_SettingDbData::Get(),&Data_SettingDbData::Write_into_DB_Signal,this,&DataDbdata::Write_Data_Slot);
    isOpen();
//        QMessageBox::information(nullptr,"错误","数据库打开失败咯");
//    else
//        QMessageBox::information(nullptr,"数据库打开成功","将采用系统提供无参数数据库,如要保存参数请新建并写入！");
}

DataDbdata::~DataDbdata()
{
    Close();
}

bool DataDbdata::isOpen()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
    }
    if(!m_db.open())
        return false;
    else
    {
        bool isopen = OpenDataBase();
        return isopen;
    }
}

//打开默认文件 查看是否存在 若文件存在则直接创建
bool DataDbdata::OpenDataBase()
{
    QFile file(DbPath);
    if(!file.exists())
    {
        CreateDataBaseFile();
    }
    if (!m_db.open())
    {
        return false;
    }
    m_db.setDatabaseName(DbPath);
    m_db.close();
    return true;
}

void DataDbdata::CreateDataBaseFile()
{
    QFile mDataFile(DbPath);
    bool ok = mDataFile.open(QIODevice::WriteOnly);
    if(ok)
    {
        m_db.setDatabaseName(DbPath);
        if(!m_db.open())
        {
            QMessageBox::information(nullptr,"错误","你的鸡巴人品不行打不开数据库");
            return;
        }
        QSqlQuery query;
        query.exec("create table GlobalLib(id int primary key,value varchar)");
        query.exec("create table CutLib(id int primary key,value varchar)");
        query.exec("create table PerforatedLib(id int primary key,value varchar)");
        //发送默认数据到数据库中
        emit InitDataFile();
        m_db.close();
    }
    mDataFile.close();
}

//把数据写入文件中
void DataDbdata::Write_Data(QStringList Idlist,QVariantList Valuelist,DataType type)
{
    if(type == Global)
    {
        const QString& str = "GlobalLib";
        QFuture<void> f2 = QtConcurrent::run(this,&DataDbdata::Write_Data_Str,Idlist,Valuelist,str);
        f2.waitForFinished();
//        Write_Data_Str(Idlist,Valuelist,"GlobalLib");
    }
    else if(type == Perforated)
    {
        const QString& str = "PerforatedLib";
        QFuture<void> f2 = QtConcurrent::run(this,&DataDbdata::Write_Data_Str,Idlist,Valuelist,str);
        f2.waitForFinished();
//        Write_Data_Str(Idlist,Valuelist,"PerforatedLib");
    }
    else if(type == Cut)
    {
        const QString& str = "CutLib";
        QFuture<void> f2 = QtConcurrent::run(this,&DataDbdata::Write_Data_Str,Idlist,Valuelist,str);
        f2.waitForFinished();
//        Write_Data_Str(Idlist,Valuelist,"CutLib");
    }
}

void DataDbdata::Write_Data_Str(QStringList Idlist,QVariantList Valuelist,QString LibName)
{
    if (!m_db.open())
    {
        return;
    }
    QSqlQuery query;
    m_db.transaction();
    for(int i = 0; i < Idlist.size(); i++)
    {
        query.exec(QString("SELECT * FROM %1 where id = %2").arg(LibName).arg(Idlist.at(i)));
        if(query.first())
        {
            query.exec(QString("update %1 set value = '%2' where id = %3;").arg(LibName).arg(Valuelist.at(i).toString()).arg(Idlist.at(i)));
        }
        else
        {
            QString Sid = Idlist.at(i);
            int id = Sid.split("P").last().toInt();
            query.exec(QString("insert into %1 values(%2,'%3')").arg(LibName).arg(id).arg(Valuelist.at(i).toString()));
        }
    }
    m_db.commit();
    m_db.close();
}

#if 0
QVariant DataDbdata::Find_Data(QString ID,DataType type)
{
    QString tableName = Get_libName(type);
    if (!m_db.open())
    {
        return "";
    }

    QSqlQuery query;
    query.exec(QString("SELECT * FROM %1 where id = %2").arg(tableName).arg(ID));
    if(query.first())
    {
        QVariant value = query.value(1);
        m_db.close();
        return value;
    }
//    while(query.next())
//    {
//        int tmpId=query.value(0).toInt();
//        if(id == tmpId)
//        {
//            QString value=query.value(1).toString();
//            m_db.close();
//            return value;
//        }
//    }
    m_db.close();
    return "";
}
#endif

#if 0
void DataDbdata::Delete_Data(QString ID,DataType Type)
{
    QString tableName = Get_libName(Type);
    if (!m_db.open())
    {
        return;
    }

    QSqlQuery query;
    query.exec(QString("delete from %1 where id = %2").arg(tableName).arg(ID));
    m_db.close();
}
#endif

#if 0
void DataDbdata::Modity_Data(QVariant Id, QVariant Value,QString libName)
{
    if (!m_db.open())
    {
        return;
    }

    QSqlQuery query;

    query.exec(QString("update %1 set value = '%2' where id = %3;").arg(libName).arg(Value.toString()).arg(Id.toString()));
}
#endif

bool DataDbdata::OpenFileName(QString FileName)
{
    qDebug() << FileName;
    if(!FileName.endsWith(".db"))
    {
        //提示
        bool isok = QMessageBox::information(nullptr,"提示","系统将会清空你文件内部所有资源,转化成数据库文件,是否同意",QMessageBox::Yes | QMessageBox::No);
        if(isok)
        {
            QFile mDataFile(QString("%1.db").arg(FileName));
            bool ok = mDataFile.open(QIODevice::WriteOnly);
            if(!ok)
            {
                QMessageBox::information(nullptr,"提示","创建文件失败咯！！");
                return false;
            }
            m_db.setDatabaseName(mDataFile.fileName());
            if (!m_db.open())
            {
                return false;
            }

            QSqlQuery query;
            query.exec("create table GlobalLib(id int primary key,value varchar)");
            query.exec("create table CutLib(id int primary key,value varchar)");
            query.exec("create table PerforatedLib(id int primary key,value varchar)");
            //不管内部有没有数据 都要发送初始化数据
            //如果内部有数据的话他会插入失败
            emit InitDataFile();

            m_db.close();
            mDataFile.close();
            return false;
        }
    }

    m_db.setDatabaseName(FileName);
    if (!m_db.open())
    {
        return false;
    }

#if 0
    m_db.setDatabaseName(FileName);
    QSqlQuery query;
    query.exec("create table GlobalLib(id int primary key,value varchar)");
    query.exec("create table CutLib(id int primary key,value varchar)");
    query.exec("create table PerforatedLib(id int primary key,value varchar)");
#endif
    //不管内部有没有数据 都要发送初始化数据
    //如果内部有数据的话他会插入失败
    //emit ContrastAndP();
    //先判断载入的数据库的大小是否跟配置文件的数量相等
    if(SelectCuttingCount() != Data_SettingDbData::Get()->Get_CuttingListP().size())
    {
        QMessageBox::information(nullptr,"错误","载入的数据库大小不跟配置文件中的数据数量对等！");
        return false;
    }
    if(ContrastData())
    {
        QMessageBox::information(nullptr,"错误","载入的数据库的数据类型跟配置文件中的数据类型不对等!");
        return false;
    }
    m_db.setDatabaseName(FileName);
    WritetoMemory();

    m_db.close();

    return true;
}

QString DataDbdata::Get_libName(DataType type)
{
    if(type == Global)
    {
        return "GlobalLib";
    }
    else if(type == Perforated)
    {
        return "PerforatedLib";
    }
    else if(Cut)
    {
        return "CutLib";
    }
}

int DataDbdata::SelectCuttingCount()
{
    if(!m_db.open())
        return -1;

    QSqlQuery query;
    query.exec("SELECT COUNT(value) FROM CutLib");
    if(query.first())
    {
        return query.value(0).toInt();
    }
    return -1;
}

bool DataDbdata::ContrastData()
{
    if(!m_db.open())
        return false;

    QStringList str = Data_SettingDbData::Get()->Get_CuttingListP();
    QSqlQuery query;
    qDebug() << str;
    query.exec("SELECT * FROM CutLib");
    int i = 0;
    while(query.next())
    {
        qDebug () << query.value(0).toString() << str.at(i).split("P").last();
//        if(query.value(0).toString() != str.at(i).split("P").last())
//            return false;
        i++;
    }
    return true;
}

void DataDbdata::Close()
{
    m_db.close();
    QFile mDataFile(DbPath);
    mDataFile.remove();
    QSqlDatabase::removeDatabase("QSQLITE");
}

void DataDbdata::PrinftError()
{
    qDebug() <<  m_db.lastError();
}

void DataDbdata::Write_Data_Slot(QList<QStringList> str,QList<QVariantList> val)
{
    Write_Data(str.at(0),val.at(0),Global);
    Write_Data(str.at(1),val.at(1),Cut);
    Write_Data(str.at(2),val.at(2),Perforated);
}

void DataDbdata::WritetoMemory()
{
    QVariantList GValue;
    QVariantList CValue;
    QVariantList PValue;
    m_db.transaction();

    QSqlQuery query;
    query.exec("SELECT * FROM GlobalLib");
    while(query.next())
    {
        GValue << query.value(0) << query.value(1);
    }
    query.exec("Select * from PerforatedLib");
    while(query.next())
    {
        PValue << query.value(0) << query.value(1);
    }
    query.exec("select * from CutLib");
    while(query.next())
    {
        qDebug() << query.value(0) << query.value(1);
        CValue << query.value(0) << query.value(1);
    }
    m_db.commit();

    Data_SettingDbData::Get()->Set_GlobalPValue(GValue);
    Data_SettingDbData::Get()->Set_CuttingPValue(CValue);
    Data_SettingDbData::Get()->Set_PerforatedPValue(PValue);
}

void DataDbdata::Save_As_DB_Slot(QString msg)
{
//    QString dbName = m_db.databaseName();
    QFile mDataFile(msg);
    bool ok = mDataFile.open(QIODevice::WriteOnly);
    if(!ok)
    {
        //创建数据库
        QMessageBox::information(nullptr,"提示","创建文件失败咯！！");
        return;
    }
    m_db.setDatabaseName(mDataFile.fileName());
    if (!m_db.open())
    {
        return;
    }
    QSqlQuery query;
    m_db.transaction();
    query.exec("SELECT name _id FROM sqlite_master WHERE type ='table';");
    while(query.exec())
    {
        query.exec(QString("Drop Table %1").arg(query.value(0).toString()));
    }
    query.exec("create table GlobalLib(id int primary key,value varchar)");
    query.exec("create table CutLib(id int primary key,value varchar)");
    query.exec("create table PerforatedLib(id int primary key,value varchar)");
    m_db.commit();
    //不管内部有没有数据 都要发送初始化数据
    //如果内部有数据的话他会插入失败
    emit InitDataFile();

    m_db.close();
    mDataFile.close();
    return;

}
