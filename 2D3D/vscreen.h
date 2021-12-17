#ifndef VSCREEN_H
#define VSCREEN_H

#include <QObject>
#include <QColor>
#include <QQueue>
#include <QObject>
#include "analyzegcode.h"
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QVector3D>
#include <QtGui>
#include <QTimer>

class VScreen : public QObject
{
    Q_OBJECT
public:
    explicit VScreen(QObject *parent = 0);
    ~VScreen();
    typedef struct
    {
        double x;
        double y;
        double z;
    }Point;
    typedef struct
    {


        double max_x;
        double max_y;
        double max_z;

        QStringList tool_pos_x;
        QStringList tool_pos_y;
        QStringList tool_pos_z;
        QStringList tool_drawColor_a;
        QStringList tool_drawColor_b;
        QStringList tool_drawColor_c;
        QStringList tool_current_line;//刀具移动当前加工行号

        QStringList path_pos_x;
        QStringList path_pos_y;
        QStringList path_pos_z;
        QStringList path_drawColor_a;
        QStringList path_drawColor_b;
        QStringList path_drawColor_c;
        QStringList path_current_line;// 轨迹当前加工行号
        int rowCount;//所有的加工行，用于progressbar
    }draw_data;


    void DrawCone(qreal lfVertex[3], qreal depth) ;
    void DrawCylinder(qreal color[3],qreal lfVertex[3], qreal depth) ;
    void DrawCline(qreal color[3],qreal lfVertex[3]) ;
    void DrawGrid();

    void DrawAxisLine(int nXRot, int nYRot, int nZRot) ;
    void DrawTool(qreal lfPos[4]) ;
    void gain_circleArray(qreal test[3], float test_1[36][3]);

    void DrawPath();
    void Draw_toolMoving_Path();
    //void Simulation(int line);//刀具仿真

    void scalingdata(int ,int);
    void ScalingSize(double size);

    void Draw_line(Point st,Point ed ,GLfloat color1,GLfloat color2,GLfloat color3);

signals:
    void max_size(double max_x,double max_y);
    void Update();
    void sendNowDrawingLineNumber(int nowLine,int rowcount);
public slots:
    void timer_ovf();
    void timer1_ovf();
    void DrawGriXYZaxis();
    void Redraw();
    void clear_path();
    void DrawVScreen() ;
    void redrawset();
    void recover();//load new file
    void readend(bool end);
    void getvalue(draw_data data);
    void start_Sim();
    void pause_Sim();
    void Slot_Add_Speed();
    void Slot_Sub_Speed();

    void PushBackPath();
private:

    qreal _lfCoordToPos; //坐标值转换为图形的位置单位量（pos = _lfCoordToPos * coord）
    qreal draw_size_ratio;
    qreal _lfCurPos[4]; //刀具当前坐标


    double scaling;
    QTimer *timer;
    qreal _lfOriginOffset[3]; //原点偏移
    qreal _lfToolOffse;


    draw_data data1;//第一次画
    draw_data data2;//重画之后启用
    draw_data data3;//刀具轨迹用
    int toolPath_line;
    int tool_current_pointCount;
    bool tool_move_endornot;
    //bool R_TYPE;//判断大小弧长


    bool start_sim_or_not;

    int Speed = 1;

    QTimer *timer11;
    QList<GLdouble> mToolMoveX;
    QList<GLdouble> mToolMoveY;
    QList<GLdouble> mToolMoveZ;
    QList<GLdouble> mToolMoveColorA;
    QList<GLdouble> mToolMoveColorB;
    QList<GLdouble> mToolMoveColorC;

    GLdouble toolMove_x[500];
    GLdouble toolMove_y[500];
    GLdouble toolMove_z[500];
    GLdouble toolMove_color_a[500];
    GLdouble toolMove_color_b[500];
    GLdouble toolMove_color_c[500];

    bool isClear = true;

};

#endif // VSCREEN_H
