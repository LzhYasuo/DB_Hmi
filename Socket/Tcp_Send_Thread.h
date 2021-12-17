#ifndef TCP_SEND_THREAD_H_
#define TCP_SEND_THREAD_H_

#include <QObject>
#include <QMutex>

class QTimer;
class QTcpSocket;
class Tcp_Send_Thread : public QObject
{
    Q_OBJECT
public:
    explicit Tcp_Send_Thread(QObject *parent = nullptr);

public slots:
    //停止循环
    void Slot_While_Finish();
    //接受Cnc包
    void Slot_SendPushBack(QString);
    //接受Plc包
    void Slot_pSendPushBack(QString);
    //开启循环
    void run();
private:
    //循环发送
    void While_Send();
signals:
    void Send_Finish();

    void Socket_Write(QString);

    void PlcSocket_Write(QString);

    //写入日志文件
    void SendMsg_File(QString msg);
private:
    QTcpSocket* mSocket;
    //需要发送CNC的字符串
    QStringList SendPkt;
    //需要发送PLC的字符串
    QStringList pSendPkt;
    //是否停止循环
    bool isStop = false;
    //锁
    QMutex mlock;
    //
    QTimer* m_Timer = nullptr;
    //
    int Size;
    //
    QString SendMsg;
};


#endif //TCP_SEND_THREAD_H_
