#include "Tcp_Accept_Thread.h"
#include <QTimer>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QMetaType>

Tcp_Accept_Thread::Tcp_Accept_Thread()
{
    qRegisterMetaType<DirType>("DirType");
    qRegisterMetaType<AxesType>("AxesType");
    qRegisterMetaType<FileType>("FileType");
}

Tcp_Accept_Thread::~Tcp_Accept_Thread()
{

}

//循环发送包
void Tcp_Accept_Thread::While_Accept()
{
#if 1
    if(AcceptList.size() > 0)
    {
        mlock.lock();
        AcceptMsg = AcceptList.takeFirst();
        if(AcceptMsg.indexOf("<err>") == -1)
        {
            emit AcceptMsg_File(AcceptMsg);
            //这里或许可以加个bool判断 如果有一项成了就直接跳出去
            //不过感觉也没啥必要 因为就算不返回bool也不占用什么效率
            Judge_axes(AcceptMsg);
            Judge_recoed(AcceptMsg);
            Judge_dir(AcceptMsg);
            Judge_feed(AcceptMsg);
            Judge_spindle(AcceptMsg);
            Judge_file(AcceptMsg);
            Judge_Alarm(AcceptMsg);
            Judge_Gcodes(AcceptMsg);
            Judge_Comp(AcceptMsg);
            Judge_BCD(AcceptMsg);
            Judge_Ncda(AcceptMsg);
            Judge_PlcIO(AcceptMsg);
            Judge_Switch(AcceptMsg);
            Judge_Appl2(AcceptMsg);
            Judge_Name(AcceptMsg);
            Judge_Getp(AcceptMsg);
            Judge_Load(AcceptMsg);
        }
        else if(AcceptList.indexOf("<err>") > -1)
        {
            Judge_Error(AcceptMsg);
        }
        mlock.unlock();
    }
#else
    int count = AcceptList.size();
    for(int i = 0; i < count; i++)
    {
        //如果接受的数据没有错误
        if(AcceptList.indexOf("<err>") == -1)
        {
            emit AcceptMsg_File(AcceptList.at(i));
            //这里或许可以加个bool判断 如果有一项成了就直接跳出去
            //不过感觉也没啥必要 因为就算不返回bool也不占用什么效率
            Judge_axes(AcceptList.at(i));
            Judge_recoed(AcceptList.at(i));
            Judge_dir(AcceptList.at(i));
            Judge_feed(AcceptList.at(i));
            Judge_spindle(AcceptList.at(i));
            Judge_file(AcceptList.at(i));
            Judge_Alarm(AcceptList.at(i));
            Judge_Gcodes(AcceptList.at(i));
            Judge_Comp(AcceptList.at(i));
            Judge_BCD(AcceptList.at(i));
            Judge_Ncda(AcceptList.at(i));
            Judge_PlcIO(AcceptList.at(i));
            Judge_Switch(AcceptList.at(i));
            Judge_Appl2(AcceptList.at(i));
            Judge_Name(AcceptList.at(i));
            Judge_Getp(AcceptList.at(i));
            Judge_Load(AcceptList.at(i));
//            Judge_PLC_Value(AcceptList.at(i));
        }
        else if(AcceptList.indexOf("<err>") == 0)
        {
            qDebug() << AcceptList.at(i);
            Judge_Error(AcceptList.at(i));
        }
    }
    for(int j = 0; j < count; j++)
    {
        mlock.lock();
        AcceptList.removeAt(0);
        mlock.unlock();
    }
#endif
#if 0
    while(!AcceptList.isEmpty() || isStop)
    {
        qDebug() << AcceptList.front();
        //如果接受的数据没有错误
        if(AcceptList.indexOf("<err>") == -1)
        {
            //这里或许可以加个bool判断 如果有一项成了就直接跳出去
            //不过感觉也没啥必要
            Judge_axes(AcceptList.front());
            Judge_recoed(AcceptList.front());
            Judge_dir(AcceptList.front());
        }
        mlock.lock();
        AcceptList.pop_front();
        mlock.unlock();
    }
#endif
}

bool Tcp_Accept_Thread::Judge_recoed(QString str)
{
    if(str.split(">").first().split("<").last() == "record")
    {
        QVariant TypeHead = GetValFromFeedback(str,"rec").toString().split(" ").first();
        QVariant Value = GetValFromFeedback(str,"rec");
        QVariant XValue;
        QVariant YValue;

        QList<QVariant> ValueList;

        if(Value.toString().indexOf("X=") != -1)
            XValue = Value.toString().split("X=").last().split(" ").first();
        if(Value.toString().indexOf("Y=") != -1)
            YValue = Value.toString().split("Y=").last().split(" ").first();

        ValueList.push_back(TypeHead);
        ValueList.push_back(XValue);
        ValueList.push_back(YValue);

        emit Set_RecoedValue(ValueList);

        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_file(QString str)
{
    if(str.split(">").first().split("<").last() == "file")
    {
        if(GetValFromFeedback(str,"eof") == "yes")
            return false;
        QVariant TypeName = GetValFromFeedback(str,"sub");
        QList<QVariant> ValueList;
        //G1
        if(TypeName.toString() == "offset")
        {
            QVariant TableHead = GetValFromFeedback(str,"rec").toString().split(" ").first();
            QVariant Value = GetValFromFeedback(str,"rec");
            QVariant XValue;
            QVariant YValue;
            QVariant ZValue;
            QVariant AValue;
            if(Value.toString().indexOf("X=") != -1)
                XValue = Value.toString().split("X=").last().split(" ").first();
            if(Value.toString().indexOf("Y=") != -1)
                YValue = Value.toString().split("Y=").last().split(" ").first();
            if(Value.toString().indexOf("Z=") != -1)
                ZValue = Value.toString().split("Z=").last().split(" ").first();
            if(Value.toString().indexOf("A=") != -1)
                AValue = Value.toString().split("A=").last().split(" ").first();

            ValueList.push_back(TableHead);
            ValueList.push_back(XValue);
            ValueList.push_back(YValue);
            ValueList.push_back(ZValue);
            ValueList.push_back(AValue);

            emit Set_FileValue(G1,ValueList);
        }
        //以下的表格都是在一个列表之中的
        //H1
        else if(TypeName.toString() == "length")
        {
            //名字
            QVariant Name = GetValFromFeedback(str,"rec").toString().split(" ").first();
            //第一个值
            QVariant FirstValue = GetValFromFeedback(str,"rec").toString().split("Z=").last().split(" ").first();
            //第二个值
            QVariant SecondValue = GetValFromFeedback(str,"rec").toString().split("Z=").last().split(" ").last();

            //名字应该不需要保存
            //所以list pushback2个Value即可
            ValueList.push_back(Name);
            ValueList.push_back(FirstValue);
            ValueList.push_back(SecondValue);

            emit Set_FileValue(H1,ValueList);

            //发送一个信号
        }
        //D1
        else if(TypeName.toString() == "corr")
        {
            //名字
            QVariant Name = GetValFromFeedback(str,"rec").toString().split("=").first();
            //第一个值
            QVariant FirstValue = GetValFromFeedback(str,"rec").toString().split("=").last().split(" R0").first().split(" ").first();
            //第二个值
            QVariant SecondValue = GetValFromFeedback(str,"rec").toString().split("=").last().split(" R0").first().split(" ").last();

            //因为是表格融合
            //这个也不需要保存名字
            ValueList.push_back(Name);
            ValueList.push_back(FirstValue);
            ValueList.push_back(SecondValue);

            emit Set_FileValue(D1,ValueList);
        }
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_dir(QString str)
{

    //<dir><sub>plc</sub></dir>
    //<dir><sub>mp</sub></dir>
    if(str.split(">").first().split("<").last() == "dir")
    {
        if(GetValFromFeedback(str,"eof") == "yes")
            return false;
        QList<QVariant> DirList;
        //路径
        QVariant Dir = GetValFromFeedback(str,"path");
        //名字
        QVariant Name = GetValFromFeedback(str,"name");
        //plc 还是 mp 类型
        QVariant Type = GetValFromFeedback(str,"sub");
        //直接找到这个文件拿文件信息
        QFileInfo info(Dir.toString() + "\\" + Name.toString());
        //最后一次修改的时间
        QVariant Modify_Time = info.lastModified();
        //现在加载进去的时间 应该可以理解成载入时间 不清楚 到时候再算
        QVariant Read_Time = QDateTime::currentDateTime();

        DirList.push_back(Dir);
        DirList.push_back(Name);
        DirList.push_back(Modify_Time);
        DirList.push_back(Read_Time);

        if(Type.toString() == "plc")
        {
            emit Set_DirValue(DIR_PLC,DirList);
            //发送更新PLC路径名字的一个信号
        }
        else if(Type.toString() == "mp")
        {
            emit Set_DirValue(DIR_MP,DirList);
            //发送一个更新mp路径名字的一个信号
        }
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_version(QString str)
{
    if(str.split(">").first().split("<").last() == "version")
    {
        QVariant nVer = GetValFromFeedback(str,"ncver");
        QVariant sVer = GetValFromFeedback(str,"srvver");

        //发送一个CNC版本的信号
        //发送一个hmi版本的信号
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_spindle(QString str)
{
#if 0
    //判断一下是不是转速
    if(str.split(">").first().split("<").last() == "spindle")
    {
        //这种东西真是 莫名其妙 脑瘫CNC你妈死了我是你爹
        QVariant num = GetValFromFeedback(str,"nmb");
        QList<QVariant> SpindeleValueList;

        //最大值是不变的
        QVariant max = GetValFromFeedback(str,"max");
        QVariant act = GetValFromFeedback(str,"act" + num.toString());
        QVariant bar = GetValFromFeedback(str,"bar" + num.toString());
        SpindeleValueList.push_back(act);
        SpindeleValueList.push_back(max);
        SpindeleValueList.push_back(bar);
//        //直接发送信号告诉他转速是啥 完事了铁子
    }
#endif
    //上面这种情况对应多种主轴
    //因为我们只有一个主轴
    //所以只需要有一个即可
    if(str.split(">").first().split("<").last() == "spindle")
    {
        QList<QVariant> SpindeleValueList;
        QVariant max = GetValFromFeedback(str,"max");
        QVariant act = GetValFromFeedback(str,"act1");
        QVariant bar = GetValFromFeedback(str,"bar1");
        if(!max.toString().isEmpty() && !act.toString().isEmpty() && !bar.toString().isEmpty())
        {
            SpindeleValueList.push_back(act);
            SpindeleValueList.push_back(max);
            SpindeleValueList.push_back(bar);
            emit Set_SpindleValue(SpindeleValueList);
        }
        //直接发送信号就完事了嗷
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_feed(QString str)
{
    //判断一下是不是速度
    if(str.split(">").first().split("<").last() == "feed")
    {
        QList<QVariant> FeedValueList;
        QVariant max = GetValFromFeedback(str,"max");
        QVariant act = GetValFromFeedback(str,"act");
        QVariant bar = GetValFromFeedback(str,"bar");
        FeedValueList.push_back(act);
        FeedValueList.push_back(max);
        FeedValueList.push_back(bar);

        emit Set_FeedValue(FeedValueList);
        return true;
    }
    return false;
}

//判断是否是轴
bool Tcp_Accept_Thread::Judge_axes(QString str)
{
    //判断一下是不是轴
    if(str.split(">").first().split("<").last() == "axes")
    {
        QList<QVariant> CoordValueList;
        //X
        QVariant ax1 = GetValFromFeedback(str,"ax1");
        //Y
        QVariant ax2 = GetValFromFeedback(str,"ax2");
        //Z
        QVariant ax3 = GetValFromFeedback(str,"ax3");
        //A
        QVariant ax4 = GetValFromFeedback(str,"ax4");
        //
        QVariant ax5 = GetValFromFeedback(str,"ax5");
        //
        QVariant ax6 = GetValFromFeedback(str,"ax6");
        //什么类型的坐标
        QVariant type = GetValFromFeedback(str,"sub");
        CoordValueList.push_back(ax1);
        CoordValueList.push_back(ax2);
        CoordValueList.push_back(ax3);
        CoordValueList.push_back(ax4);
        CoordValueList.push_back(ax5);
        CoordValueList.push_back(ax6);

        //看看是什么坐标系 KV 剩余 工件 等坐标
        //机械坐标
        //我不知道这份代码会不会被人看到
        //但是这个玩意是真脑瘫
        if(type == "pos")
        {
            emit Set_AxesValue(POS,CoordValueList);
        }
        //电压值
        else if(type == "voltage")
        {
            emit Set_AxesValue(VOITAGE,CoordValueList);
        }
        //滞后值
        else if(type == "lag")
        {
            emit Set_AxesValue(LAG,CoordValueList);
        }
        //工件坐标
        else if(type == "rem")
        {
            emit Set_AxesValue(REM,CoordValueList);
        }
        //剩余坐标
        else if(type == "end")
        {
            emit Set_AxesValue(END,CoordValueList);
        }
        //KV因子
        else if(type == "gain")
        {
            emit Set_AxesValue(GAIN,CoordValueList);
        }
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Alarm(QString str)
{
    if(str.split(">").first().split("<").last() == "alarm")
    {
        QList<QVariant> AlarmList;
        //No 的 值
        QVariant noValue = GetValFromFeedback(str,"no");
        //prio
        QVariant prioValue = GetValFromFeedback(str,"prio");
        //st
        QVariant stValue = GetValFromFeedback(str,"st");

        AlarmList.push_back(noValue);
        AlarmList.push_back(prioValue);
        AlarmList.push_back(stValue);

        emit Set_AlarmValue(AlarmList);
        return true;
    }
    return false;
}

//判断G代码
bool Tcp_Accept_Thread::Judge_Gcodes(QString str)
{
    QStringList msg;
    if(str.split(">").first().split("<").last() == "gcodes")
    {
        for(int i = 0; i < 40; i++)
        {
            QVariant Value = GetValFromFeedback(str,"g" + QString::number(i + 1));
            msg << Value.toString();
        }
        emit Set_Gcodes(msg);
        return true;
    }
    return false;
}

//判断补偿值
bool Tcp_Accept_Thread::Judge_Comp(QString str)
{
    QStringList msg;
    QString value;
    QString value1;
    if(str.split(">").first().split("<").last() == "comp")
    {
        for(int i = 0; i < 6; i++)
        {
            QVariant Value = GetValFromFeedback(str,"c" + QString::number(i + 1));
            msg << Value.toString();
        }
        if(str.indexOf("<r>")!=-1)
        {
            value = GetValFromFeedback(str,"r").toString();
        }
        if(str.indexOf("<s>") != -1)
        {
            value1 = GetValFromFeedback(str,"s").toString();
        }
        emit Set_Comp(msg,value,value1);
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_BCD(QString str)
{
    QStringList msg;
    if(str.split(">").first().split("<").last() == "bcd")
    {
        for(int i = 0; i < 4; i++)
        {
            QVariant Value = GetValFromFeedback(str,"c" + QString::number(i + 1));
            msg << Value.toString();
        }
        emit Set_BCD(msg);
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Ncda(QString str)
{
    if(str.split(">").first().split("<").last() == "ncda")
    {
        qDebug() << "ncda" << str;
        QStringList Main_Ncda;
        QStringList System_Ncda;
        QStringList Setting_Ncda;
        if(str.indexOf("<prg>")!=-1)//程序号
        {
            System_Ncda << "prg_" + GetValFromFeedback(str,"prg").toString();
        }
        if(str.indexOf("<sub>")!=-1)//子程序号
        {
            System_Ncda << "sub_" + GetValFromFeedback(str,"sub").toString();
        }
        if(str.indexOf("<block>")!=-1)//程序段号
        {
            System_Ncda << "block_" + GetValFromFeedback(str,"block").toString();
        }
        if(str.indexOf("<status>")!=-1)//
        {
            Main_Ncda << "status_" + (GetValFromFeedback(str,"status").toString());
        }
        if(str.indexOf("mode")!=-1)
        {
            Main_Ncda << "mode_" + (GetValFromFeedback(str,"mode").toString());
        }
        if(str.indexOf("mmode")!=-1)
        {
            Main_Ncda << "mmode_" + (GetValFromFeedback(str,"mmode").toString());
        }
        if(str.indexOf("amode")!=-1)
        {
            Main_Ncda << "amode" + (GetValFromFeedback(str,"amode").toString());
        }
        if(str.indexOf("gini") != -1)
        {
            Setting_Ncda << "gini" + GetValFromFeedback(str,"gini").toString();
        }
        if(str.indexOf("raxes") != -1)
        {
            Setting_Ncda << "raxes" + GetValFromFeedback(str,"raxes").toString();
        }
        if(Main_Ncda.size() > 0)
            emit Set_Ncda_Main(Main_Ncda);
        if(System_Ncda.size() > 2)
            emit Set_Ncda_System(System_Ncda);
        if(Setting_Ncda.size() > 0)
            emit Set_Ncda_Setting(Setting_Ncda);
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_PlcIO(QString str)
{
    QStringList msg;
    QString Io_Auto;
    if(str.split(">").first().split("<").last() == "io")
    {
        if(GetValFromFeedback(str,"st") == "plc")
        {
            if(str.indexOf("v") == -1)
            {
                return true;
            }
            QVariant Value = GetValFromFeedback(str,"ri");
            QVariant State = GetValFromFeedback(str,"v");

            Set_PLCIoInOutStare(Value,State.toInt());
        }
        else
        {
            if(str.indexOf("name") == -1)
            {
                return true;
            }
            if(GetValFromFeedback(str,"sub") == "out")
            {
                for(int i = 0; i < 32; i++)
                {
                    msg << GetValFromFeedback(str,"b" + QString::number(i + 1)).toString();
                    Io_Auto = "." + msg.at(i) + ",";
                    Io_Auto = Io_Auto.left(Io_Auto.length() - 1);
                }
                CNC_IO_Output = msg;
                emit Set_PLCOutPut(msg,PLC_Out_Num);
                PLC_Out_Num += 1;
                return true;
            }
            else if(GetValFromFeedback(str,"sub") == "in")
            {
                for(int i = 0; i < 32; i++)
                {
                    msg << GetValFromFeedback(str,"b" + QString::number(i + 1)).toString();
                    Io_Auto = "." + msg.at(i) + ",";
                    Io_Auto = Io_Auto.left(Io_Auto.length() - 1);
                }
                CNC_IO_Input = msg;
                emit Set_PLCInPut(msg,PlC_In_Num);
                PlC_In_Num += 1;
                return true;
            }
        }
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_PLC_Value(QString str)
{
    for(int i = 0; i < CNC_IO_Input.size(); i++)
    {
        if(str.indexOf("<." + CNC_IO_Input.at(i) + ">1</.") != -1)
        {
            emit Set_PLCIoInStare(true,i);
        }
        else if(str.indexOf("<." + CNC_IO_Input.at(i) + ">1</.") != -1)
        {
            emit Set_PLCIoInStare(false,i);
        }
    }
    for(int i = 0; i < CNC_IO_Output.size(); i++)
    {
        if(str.indexOf("<." + CNC_IO_Output.at(i) + ">1</.") != -1)
        {
            emit Set_PLCIoOutStare(true,i);
        }
        else if(str.indexOf("<." + CNC_IO_Output.at(i) + ">1</.") != -1)
        {
            emit Set_PLCIoOutStare(false,i);
        }
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Switch(QString str)
{
    QStringList msg;
    if(str.split(">").first().split("<").last() == "switch")
    {
        if(!GetValFromFeedback(str,"n1").toString().isEmpty())
        {
            msg << GetValFromFeedback(str,"n1").toString();
        }
        if(!GetValFromFeedback(str,"n2").toString().isEmpty())
        {
            msg << GetValFromFeedback(str,"n2").toString();
        }
        else
        if(!GetValFromFeedback(str,"n3").toString().isEmpty())
        {
            msg << GetValFromFeedback(str,"n3").toString();
        }
        else
        if(!GetValFromFeedback(str,"n4").toString().isEmpty())
        {
            msg << GetValFromFeedback(str,"n4").toString();
        }
        else
        if(!GetValFromFeedback(str,"n5").toString().isEmpty())
        {
            msg << GetValFromFeedback(str,"n5").toString();
        }
        if(!GetValFromFeedback(str,"n6").toString().isEmpty())
        {
            msg << GetValFromFeedback(str,"n6").toString();
        }
        else

        emit Set_Switch(msg);

        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Appl2(QString str)
{
    QStringList msg;
    QStringList List;
    if(str.split(">").first().split("<").last() == "appl2")
    {
        int num = GetValFromFeedback(str,"id").toInt();
        if(num == 1337)
        {
            msg << GetValFromFeedback(str,"v1").toString();
            msg << GetValFromFeedback(str,"v2").toString();
            msg << GetValFromFeedback(str,"v3").toString();
            msg << GetValFromFeedback(str,"v4").toString();
            emit Set_Appl2_37(msg);
            return true;
        }
        else if(num == 1338)
        {
            List << GetValFromFeedback(str,"v1").toString();
            List << GetValFromFeedback(str,"v2").toString();
            List << GetValFromFeedback(str,"v3").toString();
            List << GetValFromFeedback(str,"v4").toString();
            emit Set_App12_38(List);
        }
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Name(QString str)
{
    QStringList msg;
    if(str.split(">").first().split("<").last() == "names")
    {
        if(GetValFromFeedback(str,"n1") != -1)
        {
            msg << GetValFromFeedback(str,"n1").toString();
        }
        if(GetValFromFeedback(str,"n2") != -1)
        {
            msg << GetValFromFeedback(str,"n2").toString();
        }
        if(GetValFromFeedback(str,"n3") != -1)
        {
            msg << GetValFromFeedback(str,"n3").toString();
        }
        if(GetValFromFeedback(str,"n4") != -1)
        {
            msg << GetValFromFeedback(str,"n4").toString();
        }
        if(GetValFromFeedback(str,"n5") != -1)
        {
            msg << GetValFromFeedback(str,"n5").toString();
        }
        if(GetValFromFeedback(str,"n6") != -1)
        {
            msg << GetValFromFeedback(str,"n6").toString();
        }
        emit Set_Name(msg);
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Load(QString str)
{
    if(str.split(">").first().split("<").last() == "load")
    {
        QString FileName = GetValFromFeedback(str,"files").toString();
        if(!FileName.isEmpty())
        {
            emit Set_Load(FileName);
            return true;
        }
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Getp(QString str)
{
    QStringList msg;
    QStringList Name;
    QStringList Value;
    if(str.split(">").first().split("<").last() == "getp")
    {
        msg << str.split("<p");
        for(int i = 1; i < msg.size(); i++)
        {
            Name << msg.at(i).split(">").first();
            Value << msg.at(i).split("</").first().split(">").last();
        }
        emit Set_Setp(Name,Value);
        return true;
    }
    return false;
}

bool Tcp_Accept_Thread::Judge_Error(QString str)
{
    qDebug() << str;
    emit Set_Error(GetValFromFeedback(str,"err").toString());
}

//获取XML具体数值
QVariant Tcp_Accept_Thread::GetValFromFeedback(QString str, QString val)
{
    QString nval = "<"+val+">";
    int nStart=str.indexOf(nval);
    int nEnd = str.indexOf("</"+val+">");
    if(nStart==-1 || nEnd==-1)
    {
        return "";
    }
//    qDebug()<<nStart<<nEnd<<nEnd-nStart-nval.length();
    return str.mid(nStart+nval.length(),nEnd-nStart-nval.length());
}

//开启循环
void Tcp_Accept_Thread::run()
{
    mTimer = new QTimer();
    mTimer->setInterval(1);
    this->connect(mTimer,&QTimer::timeout,this,&Tcp_Accept_Thread::While_Accept);
    mTimer->start();
}

//暂停循环
void Tcp_Accept_Thread::Slot_While_Finish()
{
    mTimer->stop();
    isStop = true;
    emit Accept_Finish();
}

//接受来到的数据
void Tcp_Accept_Thread::Slot_AcceptPushBack(QString msg)
{
    //这里不清楚对面发送过来的有几包
    //不推荐使用ReadAll
    //但是也不知道对面的数据有多少
    //不推荐使用Read
    //但是也不知道对面发送的数据是否具有分割号
    //也不能使用ReadLine
    //暂时用着ReadAll
    if(!msg.isEmpty())
    {
        mlock.lock();
        QStringList list;
        list << msg.split("\n");
        for(int i = 0; i < list.size(); i++)
        {
            AcceptList.push_back(list.at(i));
        }
        mlock.unlock();
    }
}
