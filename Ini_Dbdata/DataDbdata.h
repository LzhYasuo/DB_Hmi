#ifndef _DBTA_DBDATA_H_
#define _DBTA_DBDATA_H_

#include <QObject>
#include <QSqlDatabase>
#include <QVariantList>

enum DataType
{
    Global,
    Perforated,
    Cut,
};

class DataDbdata : public QObject
{
    Q_OBJECT
public:
    DataDbdata();
    ~DataDbdata();

    //检测是否能打开数据库
    bool isOpen();
    //打印错误
    void PrinftError();
    //关闭退出数据库
    void Close();
    //把数据写入文件中
    void Write_Data(QStringList,QVariantList,DataType);
    //修改数据
//    void Modity_Data(QVariant,QVariant,QString);
    //查询数据
//    QVariant Find_Data(QString ID,DataType);
    //删除数据
//    void Delete_Data(QString ID,DataType);
    //返回类型对应的列表名称
    QString Get_libName(DataType);
    //打开一个新文件
    bool OpenFileName(QString FileName);
    //查询总数
    int SelectCuttingCount();
    //对比值是否相等 如果不相等则数据库不对等
    bool ContrastData();
    //数据库的数据写给内存
    void WritetoMemory();
private:
    //重载的写入
    void Write_Data_Str(QStringList,QVariantList,QString);
    //创建默认数据库文件
    void CreateDataBaseFile();
    bool OpenDataBase();

private slots:
    void Write_Data_Slot(QList<QStringList>,QList<QVariantList>);
    //数据库另存为
    void Save_As_DB_Slot(QString msg);

signals:
    void InitDataFile();
    void Data_Write_File();
    void UpdateData();
private:
     QSqlDatabase m_db;
     const QString DbPath = "D:\\DBASE\\mDataFile.db";
};


#endif //_DBTA_DBDATA_H_
