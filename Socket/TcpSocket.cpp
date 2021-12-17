#include "TcpSocket.h"
#include <QHostAddress>
#include <QThread>
#include <QTimer>


TcpSocket::TcpSocket()
{

}

TcpSocket::TcpSocket(QString ip,quint64 post)
    :mIp(ip),mPost(post)
{

}

TcpSocket::~TcpSocket()
{
    if(Connect_Timer != nullptr)
        Connect_Timer->deleteLater();
    if(mSend_Timer != nullptr)
        mSend_Timer->deleteLater();
    if(mSocket != nullptr)
        mSocket->deleteLater();
}

bool TcpSocket::isOpen(QString ip,quint64 post)
{

}

void TcpSocket::Start_Connect()
{
#if 1
    Connect_Timer = new QTimer();
    Connect_Timer->setInterval(5000);
    mSocket = new QTcpSocket();
    this->connect(Connect_Timer,&QTimer::timeout,this,&TcpSocket::Slot_Socket_ReConnect);
    this->connect(mSocket,&QTcpSocket::readyRead, this,&TcpSocket::SlotReadyRead);
    this->connect(mSocket,&QTcpSocket::connected,this,&TcpSocket::doprocess_connected);
    this->connect(mSocket,&QTcpSocket::disconnected,this,&TcpSocket::doprocess_disconnect);
    mSocket->connectToHost(mIp,mPost);
    mSocket->waitForConnected(50000);
#endif
}

void TcpSocket::SlotReadyRead()
{
#if 1
//    mMutex.lock();
    if(mSocket->bytesAvailable() > 0)
    {
        QByteArray byes = mSocket->readAll();
        if(!byes.isEmpty())
        {
            emit TcpAcceptMsg_File(byes);
            emit Bytes_Send(byes.data());
            waitForReadyRead(100);
        }
    }
    //    mMutex.unlock();
#else
    if (mSocket->bytesAvailable() > 0)
    {
        char Data[2048];

        char* pData = Data;

        int dataLen = sizeof(Data) - 1;

        int nLen = 0;

        while((nLen = read(pData, dataLen)) > 0)

        {

            dataLen -= nLen;

            pData += nLen;
        }

        *pData = '\0';
        emit TcpAcceptMsg_File(Data);
        emit Bytes_Send(Data);
    }
#endif
}

//连接成功的槽函数
void TcpSocket::doprocess_connected()
{
    qDebug() << "connectok";
    emit Tcp_Conected_Sussess();
#if 0
    mSend_Timer = new QTimer();
    mSend_Timer->setInterval(1000);
    this->connect(mSend_Timer,&QTimer::timeout,this,&TcpSocket::Slot_Send_Timeout);
#endif
}

void TcpSocket::Send_Data(QString msg)
{
    mMutex.lock();
    QString cmd = msg;
    if(cmd.isEmpty())
    {
        mMutex.unlock();
        return;
    }
    if(!cmd.endsWith("\n"))
        cmd.append("\n");
    int datelen = cmd.length();
    int mLen = 0;
    while(datelen > 0)
    {
        mLen = (int)mSocket->write(cmd.toLatin1(),cmd.length());
        qDebug() << cmd.toLatin1();
        if(mLen > 0)
        {
            mSocket->waitForBytesWritten();
        }
        if(mLen == -1)
        {
            mMutex.unlock();
            return;
        }
        datelen -= mLen;
    }
    emit TcpSendMsg_File(msg);
    mMutex.unlock();
}

void TcpSocket::doprocess_disconnect()
{
    //断开打开重连计时器
    Connect_Timer->start();

#if 0
    mSocket->disconnectFromHost();
    mSocket->waitForDisconnected();
#endif
}

void TcpSocket::Slot_Socket_ReConnect()
{
    Connect_Timer->stop();
    m_Count++;
    if(m_Count <= 3)
    {
        qDebug() << QString("开始进行第%1次重连").arg(m_Count);
        mSocket->abort();
        qDebug() << mIp << mPost;
        mSocket->connectToHost((QHostAddress)mIp,mPost);
        if(mSocket->waitForConnected())
        {
            qDebug() << "恭喜你重连成功！！";
            mSend_Error = 0;
            emit ReConnectSuccess();
            return;
        }
        Connect_Timer->start();
        return;
    }
    else
    {
        emit Socket_Finish();
        mSocket->close();
    }
}

#if 0
//心跳检测发送1判断是否已经断开
void TcpSocket::Slot_Send_Timeout()
{
    if(mSocket->write("1"/*,sizeof("1")*/) > 0)
    {
        //把发送失败计数器给0
        //重新给予三次机会
        mSend_Error = 0;
        return;
    }
    else
    {
        mSend_Error++;
        //发送失败达到3次
        if(mSend_Error >= 3)
        {
            mSend_Timer->stop();
            Slot_Socket_ReConnect();
        }
    }
}
#endif

void TcpSocket::Start_Connect_Timer()
{
    Connect_Timer->start();
}
