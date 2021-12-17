#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

#include <QTcpSocket>
#include <QMutex>

class Tcp_ReConnected_Thread;
class Tcp_Accept_Thread;
class Tcp_Send_Thread;
class QTimer;
class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket();
    TcpSocket(QString ip,quint64 post);
    ~TcpSocket();

    bool isOpen(QString ip,quint64 post);
    //开始连接
    void Start_Connect();
private slots:
    //连接成功的信号
    void doprocess_connected();
    //连接断开的信号
    void doprocess_disconnect();
    //重连
    void Slot_Socket_ReConnect();
    //有数据传进的槽函数
    void SlotReadyRead();
    //心跳计时器的timeout
//    void Slot_Send_Timeout();
signals:
    //发送Finish让线程退出
    void Thread_Finish();
    //把收到的字节发送给线程处理
    void Bytes_Send(QString);
    //TCP连接成功
    void Tcp_Conected_Sussess();
    //如果开始放了重连也连接不上则Socket消亡
    void Socket_Finish();

    //发送的信息写入日志文件
    void TcpSendMsg_File(QString msg);
    //接受的信息写入日志文件
    void TcpAcceptMsg_File(QString msg);

    //重连成功重新发送CnC
    void ReConnectSuccess();

public slots:
    //开启重连计时器
    void Start_Connect_Timer();
    //发送数据
    void Send_Data(QString);
private:
    //IP
    QString mIp = "";
    //端口
    quint64 mPost = 0;
    //是否连接
//    bool iSConnect = false;
    //重连次数
    int m_Count = 0;
    //重连计时器
    QTimer* Connect_Timer = nullptr;
    //Socket对象
    QTcpSocket* mSocket = nullptr;
    //发送失败次数
    int mSend_Error = 0;
    //心跳跳动计时器
    QTimer* mSend_Timer = nullptr;
    //锁
    QMutex mMutex;
};

#endif //_TCP_SOCKET_H_
