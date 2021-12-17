#ifndef TCP_ACCEPT_THREAD_H_
#define TCP_ACCEPT_THREAD_H_

#include <QObject>
#include <QMutex>
#include <QVariant>
#include <QList>

enum AxesType
{
    POS,            //机械坐标
    VOITAGE,        //电压值
    LAG,            //滞后值
    REM,            //工件坐标
    END,            //剩余坐标
    GAIN,           //KV因子
};

enum DirType
{
    DIR_PLC,        //PLC信息
    DIR_MP,         //MP信息
};

enum FileType
{
    G1,             //G1文件
    D1,             //D1文件
    H1              //H1文件
};

class QTimer;
class Tcp_Accept_Thread : public QObject
{
    Q_OBJECT
public:
    Tcp_Accept_Thread();
    ~Tcp_Accept_Thread();
public slots:
    //有数据读入进来的时候
    void Slot_AcceptPushBack(QString);
    //线程停止
    void Slot_While_Finish();
    //开启循环
    void run();
signals:
    void MsgShow(QString);
    void Accept_Finish();
    //
    void Set_RecoedValue(QList<QVariant>);
    //
    void Set_DirValue(DirType,QList<QVariant>);
    //
    void Set_AxesValue(AxesType,QList<QVariant>);
    //
    void Set_FeedValue(QList<QVariant>);
    //
    void Set_SpindleValue(QList<QVariant>);
    //返回文件信息
    void Set_FileValue(FileType,QList<QVariant>);
    //返回警报
    void Set_AlarmValue(QList<QVariant>);
    //Ncda_Main
    void Set_Ncda_Main(QStringList);
    //Ncda_System
    void Set_Ncda_System(QStringList);
    //Ncda_Setting
    void Set_Ncda_Setting(QStringList);
    //返回PLC输出名称
    void Set_PLCOutPut(QStringList,int);
    //返回PLC输入名称
    void Set_PLCInPut(QStringList,int);
    //返回补偿值信号
    void Set_Comp(QStringList,QString,QString);
    //返回G代码
    void Set_Gcodes(QStringList);
    //返回BCD段信号
    void Set_BCD(QStringList);
    //返回错误信息
    void Set_Error(QString);
    //返回PLC输出状态
    void Set_PLCIoOutStare(bool,int);
    //返回PLC输入状态
    void Set_PLCIoInStare(bool,int);
    //返回PLC输出输入状态
    void Set_PLCIoInOutStare(QVariant,int);
    //返回不知道啥
    void Set_Switch(QStringList);
    //返回龙门轴
    void Set_Appl2_37(QStringList);
    //返回关联轴
    void Set_App12_38(QStringList);
    //返回轴的名称
    void Set_Name(QStringList);
    //返回SetP的名称跟参数
    void Set_Setp(QStringList,QStringList);
    //返回CNC读取文件
    void Set_Load(QString Cfile);
    //写入日志文件
    void AcceptMsg_File(QString msg);


#if 0
    //Ncda程序号
    void Set_Ncda_Prg(QString);
    //Ncda子程序号
    void Set_Ncda_Sub(QString);
    //Ncda程序段号
    void Set_Ncda_block(QString);
    //Ncda状态
    void Set_Ncda_status(QString);
    //Ncda模式
    void Set_Ncda_Mode(QString);
    //Ncda mmode 不知道什么鸡巴玩意
    void Set_Ncda_Mmode(QString);
    //Ncda amode 不知道什么鸡巴玩意
    void Set_Ncda_Amode(QString);
    //Ncda Gini
    void Set_Ncda_Gini(QString);
    //Ncda Raxes
    void Set_Ncda_Raxes(QString);
    //返回加工方式机床信号
    void Set_Ncda(QStringList);
    //返回主界面加工方式机床信号
    void Set_MainNcda(QStringList);
    //返回设置界面加工方式机床信号
    void Set_SetNcda(QStringList);
#endif

private slots:
    void While_Accept();
private:
    //List
    QStringList AcceptList;
    //锁
    QMutex mlock;
    //计时器
    QTimer* mTimer;
    //是否暂停循环
    bool isStop = false;
    //
    int Size;
private:
    //获取XML具体数值
    QVariant GetValFromFeedback(QString str, QString val);
    //判断轴数据
    bool Judge_axes(QString);
    //判断速度
    bool Judge_feed(QString);
    //判断转速
    bool Judge_spindle(QString);
    //判断版本号
    bool Judge_version(QString);
    //判断MP Plc
    bool Judge_dir(QString);
    //判断File
    bool Judge_file(QString);
    //判断Record
    bool Judge_recoed(QString);
    //判断Alarm
    bool Judge_Alarm(QString);
    //判断G代码
    bool Judge_Gcodes(QString);
    //判断补偿值
    bool Judge_Comp(QString);
    //判断BCD段
    bool Judge_BCD(QString);
    //判断加工方式机床状态方式
    bool Judge_Ncda(QString);
    //判断PLC输入输出
    bool Judge_PlcIO(QString);
    //输出判断Error状态
    bool Judge_Error(QString);
    //判断文件load
    bool Judge_Load(QString);
    //判断PLCIO的PLC状态
    bool Judge_PLC_Value(QString);
    //不知道判断什么玩意
    bool Judge_Switch(QString);
    //判断龙门轴字母以及关联轴
    bool Judge_Appl2(QString);
    //判断名字
    bool Judge_Name(QString);
    //判断getp
    bool Judge_Getp(QString);
    //PLC值
private:
    int PLC_Out_Num = 0;
    int PlC_In_Num = 0;
    QStringList CNC_IO_Output;
    QStringList CNC_IO_Input;
    QString AcceptMsg;
};


#endif //TCP_ACCEPT_THREAD_H_
