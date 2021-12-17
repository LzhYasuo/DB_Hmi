#include "Tcp_Send_Thread.h"
#include <QTimer>
#include <qDebug>

Tcp_Send_Thread::Tcp_Send_Thread(QObject *parent) : QObject(parent)
{
}

//循环发送包
void Tcp_Send_Thread::While_Send()
{
#if 1
    if(SendPkt.size() > 0)
    {
        mlock.lock();
        SendMsg = SendPkt.takeFirst();
        emit SendMsg_File(SendMsg);
        emit Socket_Write(SendMsg);
        mlock.unlock();
    }
    if(pSendPkt.size() > 0)
    {
        mlock.lock();
        SendMsg = pSendPkt.takeFirst();
        emit SendMsg_File(SendMsg);
        emit PlcSocket_Write(SendMsg);
        mlock.unlock();
    }
#else
    //发送给CNC的数据
    int SendPktCOunt = SendPkt.size();
    for(int i = 0; i < SendPktCOunt; i++)
    {
        //日志文件发送与处理
        emit SendMsg_File(SendPkt.at(i));
        emit Socket_Write(SendPkt.at(i));
    }
    for(int j = 0; j < SendPktCOunt; j++)
    {
        mlock.lock();
        SendPkt.removeAt(0);
        mlock.unlock();
    }

    //发送给PLC的数据
    int pSendPktCount= pSendPkt.size();
    for(int i = 0; i < pSendPktCount; i++)
    {
        //日志文件发送与处理
        emit SendMsg_File(pSendPkt.at(i));
        emit PlcSocket_Write(pSendPkt.at(i));
    }
    for(int j = 0; j < pSendPktCount; j++)
    {
        mlock.lock();
        pSendPkt.removeAt(0);
        mlock.unlock();
    }
#endif
#if 0
    while(!SendPkt.isEmpty() || isStop)
    {
        emit Socket_Write(SendPkt.front().toLatin1(),sizeof(SendPkt.front().length()));
        mlock.lock();
        SendPkt.pop_front();
        mlock.unlock();
    }
#endif
}

//计时器跑起来不断检测有没有包进入
//这里不能依赖while
//依赖while卡死程序
void Tcp_Send_Thread::run()
{
    m_Timer = new QTimer();
    m_Timer->setInterval(1);
    this->connect(m_Timer,&QTimer::timeout,this,&Tcp_Send_Thread::While_Send);
    m_Timer->start();
}

//停止循环
void Tcp_Send_Thread::Slot_While_Finish()
{
    m_Timer->stop();
    isStop = true;
    emit Send_Finish();
}

//接受Cnc包 Pushback
void Tcp_Send_Thread::Slot_SendPushBack(QString msg)
{
    if(!msg.isEmpty())
    {
        mlock.lock();
        SendPkt.push_back(msg);
        mlock.unlock();
    }
}

//接受Plc包 pushback
void Tcp_Send_Thread::Slot_pSendPushBack(QString msg)
{
    if(!msg.isEmpty())
    {
        mlock.lock();
        pSendPkt.push_back(msg);
        mlock.unlock();
    }
}
