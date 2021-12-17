#ifndef _PUBLIC_VAR_H_
#define _PUBLIC_VAR_H_

#include <QList>
#include <QMutex>
#include <QObject>

class Public_Var :public QObject
{
    Q_OBJECT
private:
    Public_Var();
    ~Public_Var();
    void Init();
public:
    //这边的都是Get 获取 Set 设置 Set对应一个Get Set发送的时候同时刷新界面
    //单例模式
    static Public_Var* Get();

private:
    QMutex mux;
    static Public_Var* Var;
};

#endif //_PUBLIC_VAR_H_
