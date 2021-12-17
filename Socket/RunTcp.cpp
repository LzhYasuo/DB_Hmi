#include "RunTcp.h"
#include "TcpSocket.h"
#include <QThread>
#include "Tcp_Send_Thread.h"
#include "Tcp_Accept_Thread.h"
#include "Public/Public_Var.h"
#include "Public/Public_Function.h"

RunTcp* RunTcp::mTcp = new RunTcp();
RunTcp::RunTcp()
{

}

RunTcp::~RunTcp()
{

}

RunTcp* RunTcp::Get()
{
    return mTcp;
}

void RunTcp::Close()
{
    emit Thread_Finish();
}

void RunTcp::Accept_Send_Init()
{
    //创建接受线程对象
    Accept_obj = new Tcp_Accept_Thread();
    //创建接受线程
    QThread* Accept_Thread = new QThread();
    //把接受对象丢入接受线程中
    Accept_obj->moveToThread(Accept_Thread);
    //接受线程start则开启循环
    this->connect(Accept_Thread,&QThread::started,Accept_obj,&Tcp_Accept_Thread::run);
    //如果Tcp线程退出 则接受对象也开始退出
    this->connect(this,&RunTcp::Thread_Finish,Accept_obj,&Tcp_Accept_Thread::Slot_While_Finish);
    //如果收到接受对象传来的退出信号线程开始退出
    this->connect(Accept_obj,&Tcp_Accept_Thread::Accept_Finish,Accept_Thread,&QThread::quit);
//    //如果接受对象解包完成则当前对象接受
//    this->connect(Accept_obj,&Tcp_Accept_Thread::MsgShow,this,&RunTcp::ShowMsg);
    //线程退出则开始销毁对象
    this->connect(Accept_Thread,&QThread::finished,Accept_obj,&Tcp_Accept_Thread::deleteLater);
    this->connect(Accept_Thread,&QThread::finished,Accept_Thread,&QThread::deleteLater);

    Accept_Thread->start();

    //创建发送对象
    Send_obj = new Tcp_Send_Thread();
    //创建发送线程
    QThread* Send_Thread = new QThread();
    //把发送对象丢入发送线程中
    Send_obj->moveToThread(Send_Thread);
    //发送线程start则开启循环
    this->connect(Send_Thread,&QThread::started,Send_obj,&Tcp_Send_Thread::run);
    //如果Close退出 则发送对象也开始退出
    this->connect(this,&RunTcp::Thread_Finish,Send_obj,&Tcp_Send_Thread::Slot_While_Finish);
    //如果当前对象收到了Cnc包则丢入线程中
    this->connect(this,&RunTcp::WriteData,Send_obj,&Tcp_Send_Thread::Slot_SendPushBack);
    //如果当前对象收到了Plc包则丢入线程中
    this->connect(this,&RunTcp::pWriteData,Send_obj,&Tcp_Send_Thread::Slot_pSendPushBack);
    //如果收到发送对象传来的信号则发送线程跟着退出
    this->connect(Send_obj,&Tcp_Send_Thread::Send_Finish,Accept_Thread,&QThread::quit);
    //线程退出则开始销毁对象
    this->connect(Send_Thread,&QThread::finished,Send_obj,&Tcp_Send_Thread::deleteLater);
    this->connect(Send_Thread,&QThread::finished,Send_Thread,&QThread::deleteLater);
    Send_Thread->start();

    //日志文件
    this->connect(Accept_obj,&Tcp_Accept_Thread::AcceptMsg_File,this,[=](QString msg){Public_Function::writeInfo(msg,true,"","AcceptThread");});
    this->connect(Send_obj,&Tcp_Send_Thread::SendMsg_File,this,[=](QString msg){Public_Function::writeInfo(msg,true,"","SendThread");});

    //接受信号
#if 0
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Prg,this,[=](QString msg){emit Set_Ncda_Prg_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Sub,this,[=](QString msg){emit Set_Ncda_Sub_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_block,this,[=](QString msg){emit Set_Ncda_Block_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_status,this,[=](QString msg){emit Set_Ncda_Status_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Mode,this,[=](QString msg){emit Set_Ncda_Mode_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Mmode,this,[=](QString msg){emit Set_Ncda_Mmode_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Amode,this,[=](QString msg){emit Set_Ncda_Amode_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Gini,this,[=](QString msg){emit Set_Ncda_Gini_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Raxes,this,[=](QString msg){emit Set_Ncda_Raxes_Signal(msg);});
#endif

    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_AlarmValue,this,[=](QList<QVariant> list){emit Set_AlarmValue_Signal(list);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Error,this,[=](QString msg){Public_Function::writeError(msg,true,"","Error");});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Setp,this,[=](QStringList n,QStringList v){emit Set_SetP_Signal(n,v);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Name,this,[=](QStringList msg){emit Set_Name_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Setting,this,[=](QStringList msg){emit Set_SetNcda_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Appl2_37,this,[=](QStringList msg){emit Set_Appl2_37Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_App12_38,this,[=](QStringList msg){emit Set_Appl2_38Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Switch,this,[=](QStringList msg){emit Set_Switch_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_Main,this,[=](QStringList msg){emit Set_Main_Ncda_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Gcodes,this,[=](QStringList msg){emit Set_Gcodes_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_BCD,this,[=](QStringList msg){emit Set_BCD_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Ncda_System,this,[=](QStringList msg){emit Set_Ncda_Signal(msg);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Comp,this,[=](QStringList msg,QString val,QString val1){emit Set_Comp_Signal(msg,val,val1);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_PLCInPut,this,[=](QStringList msg,int num){emit Set_PlcIn_Signal(msg,num);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_PLCOutPut,this,[=](QStringList msg,int num){emit Set_PLCOut_Signal(msg,num);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_PLCIoInOutStare,this,[=](QVariant val,bool state){emit Set_PLCIoInOutStareSignal(val,state);});
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_FileValue,this,[=](FileType type,QList<QVariant> value){
        if(type == D1)
        {
            emit Set_DFileValue_Signal(value);
        }
        else if(type == H1)
        {
            emit Set_HFileValue_Signal(value);
        }
        else if(type == G1)
        {
            emit Set_GFileValue_Signal(value);
        }
    });
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_Load,this,[=](QString File){
        if(File == "Z1")
        {
            emit Set_LoadZ_Signal();
        }
        else if(File == "D1")
        {
            emit Set_LoadD_Signal();
        }
        else if(File == "G1")
        {
            emit Set_LoadG_Signal();
        }
        else if(File == "H1")
        {
            emit Set_LoadH_Signal();
        }
    });
    this->connect(Accept_obj,&Tcp_Accept_Thread::Set_AxesValue,this,[=](AxesType type,QList<QVariant> value){
       if(type == POS)
       {
            emit Set_AxesPosSignal(value);
       }
    });
}

//创建CNCsocket
bool RunTcp::CncOpen(QString ip,quint64 port)
{
    TcpSocket* socket = new TcpSocket(ip,port);
    QThread* tcp_Thread = new QThread();
    socket->moveToThread(tcp_Thread);

    //有可能直接关闭程序 Socket无法被释放 所以需要在关闭的时候手动释放Socket
    this->connect(this,&RunTcp::Thread_Finish,tcp_Thread,&QThread::quit);
    //Tcp线程开始start则开始进行连接
    this->connect(tcp_Thread,&QThread::started,socket,&TcpSocket::Start_Connect);
    //Tcp对象如果开始退出则线程开始退出
    this->connect(socket,&TcpSocket::Socket_Finish,tcp_Thread,&QThread::quit);
    //Tcp线程退出则销毁TCP对象
    this->connect(tcp_Thread,&QThread::finished,socket,&TcpSocket::deleteLater);
    //Tcp线程退出则销毁Tcp线程
    this->connect(tcp_Thread,&QThread::finished,tcp_Thread,&QThread::deleteLater);;
    //如果socket有数据传入则接受线程接受
    this->connect(socket,&TcpSocket::Bytes_Send,Accept_obj,&Tcp_Accept_Thread::Slot_AcceptPushBack);
    //发送线程的循环开始解包并且通过Tcp对象发送给服务器
    this->connect(Send_obj,&Tcp_Send_Thread::Socket_Write,socket,&TcpSocket::Send_Data);
    //重连成功重新发送CnC信息
    this->connect(socket,&TcpSocket::ReConnectSuccess,this,&RunTcp::ReConnect_SendInit);
    //启动线程
    tcp_Thread->start();

    //日志文件
    this->connect(socket,&TcpSocket::TcpSendMsg_File,this,[=](QString msg){Public_Function::writeInfo(msg,true,"","TcpSend");});
    this->connect(socket,&TcpSocket::TcpAcceptMsg_File,this,[=](QString msg){Public_Function::writeInfo(msg,true,"","TcpAccept");});

//如果是单Socket的可以这样创建收发线程
#if 0
    //Tcp对象如果连接成功
    this->connect(socket,&TcpSocket::Tcp_Conected_Sussess,this,&RunTcp::Slot_Cnc_Tcp_Connect_Success);
#endif
}

//创建PLCSocket
//只是把对象创建并无需做太多操作 但是要把发送区别开来
//否则每次调用一次 Write 都会一起丢在发送线程中
//发送线程就会有2个相同的msg
bool RunTcp::PlcOpen(QString ip, quint64 port)
{
    TcpSocket* socket = new TcpSocket(ip,port);
    QThread* tcp_Thread = new QThread();
    socket->moveToThread(tcp_Thread);

    //有可能直接关闭程序 Socket无法被释放 所以需要在关闭的时候手动释放Socket
    this->connect(this,&RunTcp::Thread_Finish,tcp_Thread,&QThread::quit);
    //Tcp线程开始start则开始进行连接
    this->connect(tcp_Thread,&QThread::started,socket,&TcpSocket::Start_Connect);
    //Tcp对象如果开始退出则线程开始退出
    this->connect(socket,&TcpSocket::Socket_Finish,tcp_Thread,&QThread::quit);
    //Tcp线程退出则销毁TCP对象
    this->connect(tcp_Thread,&QThread::finished,socket,&TcpSocket::deleteLater);
    //Tcp线程退出则销毁Tcp线程
    this->connect(tcp_Thread,&QThread::finished,tcp_Thread,&QThread::deleteLater);;
    //如果socket有数据传入则接受线程接受
    this->connect(socket,&TcpSocket::Bytes_Send,Accept_obj,&Tcp_Accept_Thread::Slot_AcceptPushBack);
    //发送线程的循环开始解包并且通过Tcp对象发送给服务器
    this->connect(Send_obj,&Tcp_Send_Thread::PlcSocket_Write,socket,&TcpSocket::Send_Data);
    //启动线程
    tcp_Thread->start();

    //日志文件
    this->connect(socket,&TcpSocket::TcpSendMsg_File,this,[=](QString msg){Public_Function::writeInfo(msg,true,"","TcpSend");});
    this->connect(socket,&TcpSocket::TcpAcceptMsg_File,this,[=](QString msg){Public_Function::writeInfo(msg,true,"","TcpAccept");});

//如果是单Socket的可以这样创建收发线程
#if 0
    //Tcp对象如果连接成功
    this->connect(socket,&TcpSocket::Tcp_Conected_Sussess,this,&RunTcp::Slot_Cnc_Tcp_Connect_Success);
#endif
}

//连接成功初始化数据
void RunTcp::Socket_Write_Init()
{
    //pos轴 其实我也不知道是什么 如果有人接收看到这个我建议你问问骆工
    this->Write("<axes><st>nc1</st><sub>pos</sub><auto>yes</auto><time>50</time></axes>");
    //end轴
    this->Write("<axes><st>nc1</st><sub>end</sub><auto>yes</auto><time>50</time></axes>");
    //rem轴
    this->Write("<axes><st>nc1</st><sub>rem</sub><auto>yes</auto><time>50</time></axes>");
    //滞后值
    this->Write("<axes><st>nc1</st><sub>lag</sub><auto>yes</auto><time>50</time></axes>");
    //kv因子
    this->Write("<axes><st>nc1</st><sub>gain</sub><auto>yes</auto><time>50</time></axes>");
    //电压值
    this->Write("<axes><st>nc1</st><sub>voltage</sub><auto>yes</auto><time>50</time></axes>");
    //主轴转速 有6个主轴 这边选择全部获取吧 应该获取1就可以的
    this->Write("<spindle><auto>yes</auto><nmb>all</nmb></spindle>");
    //速度
    this->Write("<feed><st>nc1</st><auto>yes</auto><time>50</time></feed>");
//    //爷忘了这是啥了 注释晚了
//    this->Write("<record><sub>offset</sub><bof>yes</bof></record>");
//    //这个是版本号
//    this->Write("<version><req>yes</req></version>");
//    //plc信息
////    this->Write("<dir><sub>plc</sub></dir>");
//    //mp信息
//    this->Write("<dir><sub>mp</sub></dir>");
    //警报信息
    this->Write("<alarm><auto>yes</auto></alarm>");
    //获取G代码
    this->Write("<gcodes><auto>yes</auto><time>200</time></gcodes>");
    //获取补偿值
    this->Write("<comp><auto>yes</auto><time>200</time></comp>");
    //获取BCD
    this->Write("<bcd><auto>yes</auto><time>200</time></bcd>");
    //获取PLCIO输入
    this->Write("<io><sub>in</sub><st>nc1</st><ri>0</ri></io>");
    this->Write("<io><sub>in</sub><st>nc1</st><ri>0</ri></io>");
    //获取PLCIO输出
    this->Write("<io><sub>out</sub><st>nc1</st><ri>0</ri></io>");
    this->Write("<io><sub>out</sub><st>nc1</st><ri>0</ri></io>");
    //加工方式机床状态方式
    this->Write("<switch><sub>ginit</sub><sw>0</sw></switch>");
    //GantryCommandAxis 关联轴“X/Y"
    this->Write("<appl2><sub>get</sub><type>byte</type><nmb>4</nmb><id>1337</id></appl2>");
    //GantryAxisLetter  龙门轴字母
    this->Write("<appl2><sub>get</sub><type>byte</type><nmb>4</nmb><id>1338</id></appl2>");
    //获取轴名称
    this->Write("<names></names>");
    //加工方式机床状态方式
//    this->Write("<ncda><auto>yes</auto><req>yes</req><var>status,mode,mmode,amode</var></ncda>");//加工方式机床状态方式
    this->Write("<ncda><auto>yes</auto><req>yes</req><var>prg,sub,block,status,mode,mmode,amode,raxes,gini</var></ncda>");
    //H1文件
    this->Write("<file><sub>length</sub><name>1</name></file>");
    //D1文件
    this->Write("<file><sub>corr</sub><name>1</name></file>");
    //G1文件
    this->Write("<file><sub>offset</sub><name>1</name></file>");
}

void RunTcp::ReConnect_SendInit()
{
    //加工方式机床状态方式
    this->Write("<ncda><auto>yes</auto><req>yes</req><var>prg,sub,block,status,mode,mmode,amode,raxes,gini</var></ncda>");
    //警报信息
    this->Write("<alarm><auto>yes</auto></alarm>");
    //获取G代码
    this->Write("<gcodes><auto>yes</auto><time>200</time></gcodes>");
    //获取补偿值
    this->Write("<comp><auto>yes</auto><time>200</time></comp>");
    //获取BCD
    this->Write("<bcd><auto>yes</auto><time>200</time></bcd>");
    //主轴转速 有6个主轴 这边选择全部获取吧 应该获取1就可以的
    this->Write("<spindle><auto>yes</auto><nmb>all</nmb></spindle>");
    //速度
    this->Write("<feed><st>nc1</st><auto>yes</auto><time>50</time></feed>");
    //pos轴 其实我也不知道是什么 如果有人接收看到这个我建议你问问骆工
    this->Write("<axes><st>nc1</st><sub>pos</sub><auto>yes</auto><time>50</time></axes>");
    //end轴
    this->Write("<axes><st>nc1</st><sub>end</sub><auto>yes</auto><time>50</time></axes>");
    //rem轴
    this->Write("<axes><st>nc1</st><sub>rem</sub><auto>yes</auto><time>50</time></axes>");
    //滞后值
    this->Write("<axes><st>nc1</st><sub>lag</sub><auto>yes</auto><time>50</time></axes>");
    //kv因子
    this->Write("<axes><st>nc1</st><sub>gain</sub><auto>yes</auto><time>50</time></axes>");
    //电压值
    this->Write("<axes><st>nc1</st><sub>voltage</sub><auto>yes</auto><time>50</time></axes>");

}

void RunTcp::NetWorkInit()
{
    //直接开启收发线程
    this->Accept_Send_Init();
#if 0
    TcpSocket* socket = new TcpSocket();
    QThread* tcp_Thread = new QThread();
    socket->moveToThread(tcp_Thread);

    //Tcp线程开始start则开始进行连接
    this->connect(tcp_Thread,&QThread::started,socket,&TcpSocket::Start_Connect);
    //Tcp对象如果开始退出则线程开始退出
    this->connect(socket,&TcpSocket::Socket_Finish,tcp_Thread,&QThread::quit);
    //Tcp线程退出则销毁TCP对象
    this->connect(tcp_Thread,&QThread::finished,socket,&TcpSocket::deleteLater);
    //Tcp线程退出则销毁Tcp线程
    this->connect(tcp_Thread,&QThread::finished,tcp_Thread,&QThread::deleteLater);
    //Tcp对象如果连接成功
    this->connect(socket,&TcpSocket::Tcp_Conected_Sussess,this,[=](){this->Slot_Tcp_Connect_Sussess(socket);});
    //启动线程
    tcp_Thread->start();

    socket->open()
#endif
}


#if 0
void RunTcp::Slot_Tcp_Connect_Sussess(TcpSocket* socket)
{
    //创建接受线程对象
    Accept_obj = new Tcp_Accept_Thread();
    //创建接受线程
    QThread* Accept_Thread = new QThread();
    //把接受对象丢入接受线程中
    Accept_obj->moveToThread(Accept_Thread);
    //接受线程start则开启循环
    this->connect(Accept_Thread,&QThread::started,Accept_obj,&Tcp_Accept_Thread::run);
    //如果接受对象解包完成则当前对象接受
    this->connect(Accept_obj,&Tcp_Accept_Thread::MsgShow,this,&RunTcp::ShowMsg);
    //如果Tcp线程退出 则接受对象也开始退出
    this->connect(socket,&TcpSocket::Thread_Finish,Accept_obj,&Tcp_Accept_Thread::Slot_While_Finish);
    //如果收到接受对象传来的退出信号线程开始退出
    this->connect(Accept_obj,&Tcp_Accept_Thread::Accept_Finish,Accept_Thread,&QThread::quit);
    //线程退出则开始销毁对象
    this->connect(Accept_Thread,&QThread::finished,Accept_obj,&Tcp_Accept_Thread::deleteLater);
    this->connect(Accept_Thread,&QThread::finished,Accept_Thread,&QThread::deleteLater);

    //创建发送对象
    Send_obj = new Tcp_Send_Thread();
    //创建发送线程
    QThread* Send_Thread = new QThread();
    //把发送对象丢入发送线程中
    Send_obj->moveToThread(Send_Thread);
    //发送线程start则开启循环
    this->connect(Send_Thread,&QThread::started,Send_obj,&Tcp_Send_Thread::run);
    //如果当前对象收到了包则丢入线程中
    this->connect(this,&RunTcp::WriteData,Send_obj,&Tcp_Send_Thread::Slot_SendPushBack);
    //发送线程的循环开始解包并且通过Tcp对象发送给服务器
    this->connect(Send_obj,&Tcp_Send_Thread::Socket_Write,socket,&TcpSocket::Send_Data);
    //如果Tcp线程退出 则发送对象也开始退出
    this->connect(socket,&TcpSocket::Thread_Finish,Send_obj,&Tcp_Send_Thread::Slot_While_Finish);
    //如果收到发送对象传来的信号则发送线程跟着退出
    this->connect(Send_obj,&Tcp_Send_Thread::Send_Finish,Accept_Thread,&QThread::quit);
    //线程退出则开始销毁对象
    this->connect(Send_Thread,&QThread::finished,Send_obj,&Tcp_Send_Thread::deleteLater);
    this->connect(Send_Thread,&QThread::finished,Send_Thread,&QThread::deleteLater);
}
#endif

void RunTcp::WriteG1(QString Name,QString X/* = ""*/,QString Y/* = ""*/,QString Z/* = ""*/,QString A/* = ""*/)
{
    //因为表格一次只能改动一项 所以这样写没问题
    QString msg = "";
    if(X != "")
        msg = QString("<enter><sub>offset</sub><block>%1 X=%2</block></enter>").arg(Name).arg(X);
    else if(Y != "")
        msg = QString("<enter><sub>offset</sub><block>%1 Y=%2</block></enter>").arg(Name).arg(Y);
    else if(Z != "")
        msg= QString("<enter><sub>offset</sub><block>%1 Z=%2</block></enter>").arg(Name).arg(Z);
    else if(A != "")
        msg= QString("<enter><sub>offset</sub><block>%1 A=%2</block></enter>").arg(Name).arg(A);

    qDebug() << msg;
    this->Write(msg);
}

//写入D1文件
void RunTcp::WriteD1(QString Name,QString first,QString second)
{
    if((first.indexOf("+") == -1))
    {
        first = "+" + first;
    }
    if((second.indexOf("+") == -1))
    {
        second = "+" + second;
    }
    QString msg = QString("<enter><sub>corr</sub><block>%1=%2 %3 R0</block></enter>").arg(Name).arg(first).arg(second);
    qDebug() << msg;
    this->Write(msg);
}

//写入H1文件
void RunTcp::WriteH1(QString Name,QString first,QString second)
{
    if((first.indexOf("+") == -1))
    {
        first = "+" + first;
    }
    if((second.indexOf("+") == -1))
    {
        second = "+" + second;
    }
    QString msg = QString("<enter><sub>length</sub><block>%1 Z=%2 %3</block></enter>").arg(Name).arg(first).arg(second);
    qDebug() << msg;
    this->Write(msg);
}

//写入Cnc数据
void RunTcp::Write(QString msg)
{
    mux.lock();
    if(!isConnect)
    {
        mux.unlock();
        return;
    }
    emit WriteData(msg);
    mux.unlock();
}


//写入Plc数据
void RunTcp::WritePlc(QString msg)
{
    mux.lock();
    if(!isConnect)
    {
        mux.unlock();
        return;
    }
    emit pWriteData(msg);
    mux.unlock();
}
