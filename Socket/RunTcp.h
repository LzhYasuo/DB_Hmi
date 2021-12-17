#ifndef RUN_TCP_H_
#define RUN_TCP_H_

#include <QObject>
#include <QSharedPointer>
#include <QMutex>
#include <QVariant>

class Tcp_Accept_Thread;
class Tcp_Send_Thread;
class TcpSocket;
class RunTcp : public QObject
{
    Q_OBJECT
public:
    //单例模式
    static RunTcp* Get();
    //如果要写入数据
    void Write(QString msg);
    //创建CNCSocket并进行连接
    bool CncOpen(QString ip,quint64 port);
    //创建PLCSocket并进行连接
    bool PlcOpen(QString ip,quint64 port);
    //关闭Socket
    void Close();
    //写入G1文件
    void WriteG1(QString,QString X = "",QString Y = "",QString Z = "",QString A = "");
    //写入D1文件
    void WriteD1(QString,QString first,QString second);
    //写入H1文件
    void WriteH1(QString,QString first,QString second);
    //写入Plc数据
    void WritePlc(QString);
    //
    void NetWorkInit();
    //重连之后auto信息重新发送
    void ReConnect_SendInit();

    //Socket数据初始化发送
    void Socket_Write_Init();
private:
    RunTcp();
    ~RunTcp();

signals:
    //销毁线程对象
    void Thread_Finish();
    //发送线程接受数据
    void WriteData(QString msg);
    //发送线程接受PLC数据
    void pWriteData(QString msg);

#if 0
    void Set_Ncda_Sub_Signal(QString);
    void Set_Ncda_Prg_Signal(QString);
    void Set_Ncda_Block_Signal(QString);
    void Set_Ncda_Status_Signal(QString);
    void Set_Ncda_Mode_Signal(QString);
    void Set_Ncda_Mmode_Signal(QString);
    void Set_Ncda_Amode_Signal(QString);
    void Set_Ncda_Gini_Signal(QString);
    void Set_Ncda_Raxes_Signal(QString);
#endif
    void Set_AlarmValue_Signal(QList<QVariant>);
    void Set_GFileValue_Signal(QList<QVariant>);
    void Set_DFileValue_Signal(QList<QVariant>);
    void Set_HFileValue_Signal(QList<QVariant>);
    void Set_Gcodes_Signal(QStringList);
    void Set_BCD_Signal(QStringList);
    void Set_Ncda_Signal(QStringList);
    void Set_Main_Ncda_Signal(QStringList);
    void Set_Comp_Signal(QStringList,QString,QString);
    void Set_PLCOut_Signal(QStringList,int);
    void Set_PlcIn_Signal(QStringList,int);
    void Set_PLCIoInOutStareSignal(QVariant,int);
    void Set_AxesPosSignal(QList<QVariant>);
    void Set_Switch_Signal(QStringList);
    void Set_Appl2_37Signal(QStringList);
    void Set_Appl2_38Signal(QStringList);
    void Set_SetNcda_Signal(QStringList);
    void Set_Name_Signal(QStringList);
    void Set_SetP_Signal(QStringList,QStringList);
    void Set_LoadZ_Signal();
    void Set_LoadD_Signal();
    void Set_LoadG_Signal();
    void Set_LoadH_Signal();
private:
    //创建发送线程跟发送对象
    void Accept_Send_Init();

private slots:
    //CNCSocket连接成功信号
//    void Slot_Cnc_Tcp_Connect_Success();
    //PlcSocket连接成功信号
//    void Slot_Plc_Tcp_Connect_Success();
private:
    //单例模式
    static RunTcp* mTcp;
    //Socket连接对象数量
    int Socket_Connect_Num = 0;
    //接受线程
    Tcp_Accept_Thread* Accept_obj;
    //发送线程
    Tcp_Send_Thread* Send_obj;
    //锁
    QMutex mux;
    //是否连接成功
    bool isConnect = true;
};

#endif
