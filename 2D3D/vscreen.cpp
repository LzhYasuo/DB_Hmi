#include "vscreen.h"

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QVector3D>
#include<windows.h>
#include <glut.h>
#include <qmath.h>
#include <QMessageBox>
#include "QOpenGLFunctions"
#ifndef PI
#define PI 3.1415926536f
#endif

const GLdouble Pi=3.1414926536f;
#define N 50
#define RADIUS_TOOL 0.0075f
#define RADIUS_AXIS 0.01f

#define PATH_POS_NUM 6

#define GRID_ROW_NUM  6
#define GRID_COL_NUM   16



VScreen::VScreen(QObject *parent)
    : QObject(parent)
{
    redrawset();
    data2 = data1;
    data3 = data1;
    scaling = 1;
    _lfCoordToPos = 0.1/800;
    draw_size_ratio = 1;
    timer = new QTimer(this);//定义一个定时器
    timer->setInterval(10);//设置定时周期为10ms
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_ovf()));
    tool_move_endornot = false;
    installEventFilter(this);
    start_sim_or_not = false;
    toolPath_line = 0;
}

VScreen::~VScreen()
{

}

void VScreen::scalingdata(int longdata, int widthdata)
{
    _lfCoordToPos = longdata>widthdata?  0.1/longdata: 0.1/widthdata;
}

void VScreen::DrawGriXYZaxis()
{
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0,0.0);
    glVertex3f(0,0,0);
    glVertex3f(0.06,0,0);//坐标轴长度
    glEnd();
    glPushMatrix();
    glTranslatef(0.06, 0.0f, 0.0f);//坐标轴圆锥长度
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glutWireCone(0.009,0.03,10,10);
    glPopMatrix();

    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0);
    glVertex3f(0.0,0.06,0);//坐标轴长度
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.06f, 0.0f);//坐标轴圆锥长度
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
    glutWireCone(0.009,0.03,10,10);
    glPopMatrix();

    glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);//glColor3f(0.0,1.0,0.0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,0.06);//坐标轴长度
    glEnd();
    glPushMatrix();
    glTranslatef(0, 0.0f, 0.06f);//坐标轴圆锥长度
    glRotatef(0.0f,0.0f,1.0f,0.0f);
    glutWireCone(0.009,0.03,10,10);
    glPopMatrix();
    glLineWidth(1);
}

void VScreen::DrawGrid()
{
    for(int i=0;i<13;i++)
    {
        if (i!=6)
        {
            glBegin(GL_LINES);
            if(i%2 != 0)
                glColor3f(0.25f,0.25f,0.25f);
            else
                glColor3f(0.5f,0.5f,0.5f);
            glVertex3f(-0.6,-0.6+0.1*i,0.0);
            glVertex3f(0.6,-0.6+0.1*i,0.0);//坐标轴长度
            glEnd();

            glBegin(GL_LINES);
            if(i%2 != 0)
                glColor3f(0.25f,0.25f,0.25f);
            else
                glColor3f(0.5f,0.5f,0.5f);
            glVertex3f(-0.6+0.1*i,-0.6,0);
            glVertex3f(-0.6+0.1*i,0.6,0.0);//坐标轴长度
            glEnd();
        }
    }
    glBegin(GL_LINES);
    glColor3f(0.0f,0.5f,0.5f);//glColor3f(0.0,1.0,0.0);
    glVertex3f( 0 ,-0.6,0.0);
    glVertex3f( 0 ,0.6,0.0);//坐标轴长度
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f,0.5f,0.5f );//glColor3f(0.0,1.0,0.0);
    glVertex3f( -0.6 ,0,0);
    glVertex3f( 0.6 ,0 ,0.0);//坐标轴长度
    glEnd();
}

//根据旋转角度画线
void VScreen::DrawCline(qreal color[3],qreal lfVertex[3])
{
    qreal lfpoint[2][3];
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_LINE_STRIP);
    glVertex3f(lfVertex[0], lfVertex[1], 0);
    glVertex3f(lfVertex[0] + 0.16*cos(lfVertex[2]*PI/180), lfVertex[1] + 0.16*sin(lfVertex[2]*PI/180), 0);
    glEnd();
}

//Z轴方向绘制圆锥  锥顶点、深度
void VScreen::DrawCone(qreal lfVertex[3], qreal depth)
{
    GLfloat x = 0, y = 0, angle = 0;
    glColor3f(0.6f,0.0f,0.6f);
    //绘制三角扇形
    glBegin(GL_TRIANGLES);
    for(angle=0;angle<=2.0f*PI;angle+=0.1f)
    {
        glVertex3f(lfVertex[0], lfVertex[1], lfVertex[2]);//圆锥的锥顶点是三角扇形的公共顶点，沿z轴移动，产生一个圆锥而不是圆
        x = RADIUS_TOOL * sin( angle )/scaling;
        y = RADIUS_TOOL * cos( angle )/scaling;
        glVertex3f(lfVertex[0]+x, lfVertex[1]+y, depth+lfVertex[2]);
        x = RADIUS_TOOL * sin( angle+0.1)/scaling;
        y = RADIUS_TOOL * cos( angle+0.1)/scaling;
        glVertex3f(lfVertex[0]+x, lfVertex[1]+y, depth+lfVertex[2]);
    }
    glEnd();
    //绘制圆锥底面
    glBegin(GL_POLYGON);
    GLfloat part;
    for(short i=0; i<N ; i++)
    {
        part = 1.0/N*i;
        glVertex3f( lfVertex[0]+RADIUS_TOOL*cos(2*PI*part)/scaling, lfVertex[1]+RADIUS_TOOL*sin(2*PI*part)/scaling,depth+lfVertex[2]);//glColor3f()
    }
    glEnd();
}

void VScreen::gain_circleArray(qreal lfVertex[3],float circle1[36][3]) //用三角形逼近画圆
{
    float angle=0;
    for(int i=0;i<36;i++)
    {
        circle1[i][0]=lfVertex[0]+RADIUS_TOOL*cos(angle)/scaling;
        circle1[i][1]=lfVertex[1]+RADIUS_TOOL*sin(angle)/scaling;
        circle1[i][2]=lfVertex[2];
        angle+=2.0*PI/36.0f;
    }
}

//Z轴方向绘制圆柱
void VScreen::DrawCylinder(qreal color[3],qreal lfVertex[3], qreal depth)
{
    float circle[36][3]={0};
    float circle1[36][3]={0};
    gain_circleArray(lfVertex,circle);  //得到底圆坐标数组
    lfVertex[2] = lfVertex[2]+depth;
    float angle_1=0;

    for(int i=0;i<36;i++)
    {
        circle1[i][0]=lfVertex[0]+(RADIUS_TOOL*cos(angle_1))/scaling;
        circle1[i][1]=lfVertex[1]+(RADIUS_TOOL*sin(angle_1))/scaling;
        circle1[i][2]=lfVertex[2];
        angle_1+=2.0*PI/36.0f;
    }

    glColor3f(color[0],color[1],color[2]);
    //用四边形连接成柱面
    for(int i=0;i<36;i++)
    {
        glBegin(GL_QUADS);
        if(i+1==36)
        {
            glVertex3fv(circle[i]);
            glVertex3fv(circle[0]);
            glVertex3fv(circle1[0]);
            glVertex3fv(circle1[i]);
        }
        else
        {
            glVertex3fv(circle[i]);
            glVertex3fv(circle[i+1]);
            glVertex3fv(circle1[i+1]);
            glVertex3fv(circle1[i]);
        }
        glEnd();
    }
    //画顶圆
    glBegin(GL_POLYGON);
    GLfloat part;
    for(short i=0; i<N ; i++)
    {
        part = 1.0/N*i;
        glVertex3f(lfVertex[0]+(RADIUS_TOOL*cos(2*PI*part))/scaling,(lfVertex[1]+(RADIUS_TOOL*sin(2*PI*part))/scaling),(lfVertex[2]));
    }
    glEnd();
}

//画空间轴线
void VScreen::DrawAxisLine(int nXRot, int nYRot, int nZRot)
{
    glLoadIdentity();  //将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
    glTranslatef(-0.0f, 0.0f, -10.0);
    glRotatef(nXRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(nYRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(nZRot / 16.0, 0.0, 0.0, 1.0);

    GLfloat x = 0, y = 0, z = 0, angle = 0;
    glLineWidth(2);

    int nNo=0;
    GLfloat color[3][3]={{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}};
    int axisFlag[3][3]={{1,0,0},{0,1,0},{0,0,1}};
    for(nNo=0;nNo<3;nNo++)
    {
        glBegin(GL_LINES);
        glColor3f(color[nNo][0],color[nNo][1],color[nNo][2]);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(axisFlag[nNo][0]*0.08,axisFlag[nNo][1]*0.08,axisFlag[nNo][2]*0.08);
        glEnd();

        //绘制三角扇形
        glBegin(GL_TRIANGLES);
        angle = 0;
        for(angle=0;angle<=2.0f*PI;angle+=0.1f)
        {
            glVertex3f(axisFlag[nNo][0]*0.09,axisFlag[nNo][1]*0.09,axisFlag[nNo][2]*0.09);//圆锥的锥顶点
            if(nNo == 1)		x = RADIUS_AXIS * cos( angle );
            else		x = nNo==0 ? 0.052f : RADIUS_AXIS * sin( angle );
            y = nNo==1 ?  0.052f : RADIUS_AXIS * cos( angle );
            z = nNo==2 ?  0.052f : RADIUS_AXIS * sin( angle );
            glVertex3f(x, y, z);
            if(nNo == 1)		x = RADIUS_AXIS * cos( angle+0.1 );
            else		x = nNo==0 ? 0.052f : RADIUS_AXIS * sin( angle+0.1 );
            y = nNo==1 ?  0.052f : RADIUS_AXIS * cos( angle+0.1 );
            z = nNo==2 ?  0.052f : RADIUS_AXIS * sin( angle+0.1 );
            glVertex3f(x, y, z);
        }
        glEnd();

        //绘制圆锥底面
        glBegin(GL_POLYGON);
        GLfloat part;
        for(short i=0; i<N ; i++)
        {
            part = 1.0/N*i;
            if(nNo == 0)
                glVertex3f(0.052f, RADIUS_AXIS*sin(2*PI*part), RADIUS_AXIS*cos(2*PI*part));
            else if(nNo == 1)
                glVertex3f(RADIUS_AXIS*sin(2*PI*part), 0.052f, RADIUS_AXIS*cos(2*PI*part));
            else if(nNo == 2)
                glVertex3f(RADIUS_AXIS*cos(2*PI*part), RADIUS_AXIS*sin(2*PI*part), 0.052f);
        }
        glEnd();
    }
    glLineWidth(1);
}

//初始化界面
void VScreen::DrawVScreen()
{
    DrawGrid();
    DrawPath();
    Draw_toolMoving_Path();
    glFlush();
}

void VScreen::DrawPath()
{
    QString x1,y1,z1;
    Point p1,p2;
    if (data1.path_pos_x.size() >0)
    {
        p1.x = QString(data1.path_pos_x.at(0)).toDouble();
        p1.y = QString(data1.path_pos_y.at(0)).toDouble();
        p1.z = QString(data1.path_pos_z.at(0)).toDouble();
        for (int i =1;i < data1.path_pos_x.size();i++)
        {
            p2.x = QString(data1.path_pos_x.at(i)).toDouble();
            p2.y = QString(data1.path_pos_y.at(i)).toDouble();
            p2.z = QString(data1.path_pos_z.at(i)).toDouble();
            Draw_line(p1,p2,QString(data1.path_drawColor_a.at(i)).toDouble(),QString(data1.path_drawColor_b.at(i)).toDouble(),QString(data1.path_drawColor_c.at(i)).toDouble() );
            p1.x = p2.x;
            p1.y = p2.y;
            p1.z = p2.z;
        }
        if (toolPath_line < data3.tool_pos_x.size())
        {
            x1 = data3.tool_pos_x.at(toolPath_line) ;
            _lfCurPos[0] = x1.toDouble() * draw_size_ratio;
            y1 = data3.tool_pos_y.at(toolPath_line) ;
            _lfCurPos[1] = y1.toDouble() * draw_size_ratio;
            z1 = data3.tool_pos_z.at(toolPath_line) ;
            _lfCurPos[2] = z1.toDouble() * draw_size_ratio;
        }
    }
    else
    {
        _lfCurPos[0] = 0;
        _lfCurPos[1] = 0;
        _lfCurPos[2] = 0;
    }
}



void VScreen::Draw_toolMoving_Path()
{
//    if(mToolMoveX.size() < toolPath_line)
//    {
//        for(int i = 0; i < toolPath_line; i++)
//        {
//        }
//    }
#if 1
if(mToolMoveX.size() > 0)
{
    Point p1,p2;
    p1.x = mToolMoveX[0];
    p1.y = mToolMoveY[0];
    p1.z = mToolMoveZ[0];
    for(int i = 0; i < mToolMoveX.size(); i++)
    {
        p2.x = mToolMoveX[i];
        p2.y = mToolMoveY[i];
        p2.z = mToolMoveZ[i];
        Draw_line(p1,p2,mToolMoveColorA[i],mToolMoveColorB[i],mToolMoveColorC[i] );
        p1.x = p2.x;
        p1.y = p2.y;
        p1.z = p2.z;
    }
}
#else
    Point p1,p2;
    p1.x = toolMove_x[0];
    p1.y = toolMove_y[0];
    p1.z = toolMove_z[0];
    for (int i =1;i < 500;i++)
    {
        p2.x = toolMove_x[i];
        p2.y = toolMove_y[i];
        p2.z = toolMove_z[i];
        Draw_line(p1,p2,toolMove_color_a[i],toolMove_color_b[i],toolMove_color_c[i] );
        p1.x = p2.x;
        p1.y = p2.y;
        p1.z = p2.z;
    }
#endif
}

void VScreen::Slot_Add_Speed()
{
    if(Speed >= 100)
        return;
    Speed *= 2;
    qDebug() << Speed;
}

void VScreen::Slot_Sub_Speed()
{
    if(Speed <= 1)
        return;
    Speed /= 2;
}

void VScreen::timer_ovf()
{
#if 1
    for(int i = 0; i < Speed; i++)
    {
        if(isClear)
        {
            PushBackPath();
            isClear = false;
        }
        QString x1,y1,z1;
        if (toolPath_line < data3.tool_pos_x.size())
        {
            x1 = data3.tool_pos_x.at(toolPath_line) ;
            _lfCurPos[0] = x1.toDouble() * draw_size_ratio;
            y1 = data3.tool_pos_y.at(toolPath_line) ;
            _lfCurPos[1] = y1.toDouble() * draw_size_ratio;
            z1 = data3.tool_pos_z.at(toolPath_line) ;
            _lfCurPos[2] = z1.toDouble() * draw_size_ratio;
            tool_current_pointCount++;
            mToolMoveX[toolPath_line] = x1.toDouble();
            mToolMoveY[toolPath_line] = y1.toDouble();
            mToolMoveZ[toolPath_line] = z1.toDouble();
            mToolMoveColorA[toolPath_line] = QString(data3.tool_drawColor_a.at(toolPath_line)).toDouble();
            mToolMoveColorB[toolPath_line] = QString(data3.tool_drawColor_b.at(toolPath_line)).toDouble();
            mToolMoveColorC[toolPath_line] = QString(data3.tool_drawColor_c.at(toolPath_line)).toDouble();

            toolPath_line++;
            emit Update();
        }
        else
        {
            toolPath_line = 0;
            tool_current_pointCount = 0;
            timer->stop();
        }
    }
#else
    for(int i = 0; i < Speed; i++)
    {
        QString x1,y1,z1;
        QString Line;
        int Linecount;
        if (toolPath_line < data3.tool_pos_x.size())
        {
            x1 = data3.tool_pos_x.at(toolPath_line) ;
            _lfCurPos[0] = x1.toDouble() * draw_size_ratio;
            y1 = data3.tool_pos_y.at(toolPath_line) ;
            _lfCurPos[1] = y1.toDouble() * draw_size_ratio;
            z1 = data3.tool_pos_z.at(toolPath_line) ;
            _lfCurPos[2] = z1.toDouble() * draw_size_ratio;
            Line = data3.tool_current_line.at(toolPath_line) ;
            Linecount = data3.rowCount;
            if (tool_current_pointCount < 499)
            {
                tool_current_pointCount++;
                toolMove_x[tool_current_pointCount] = x1.toDouble();
                toolMove_y[tool_current_pointCount] = y1.toDouble();
                toolMove_z[tool_current_pointCount] = z1.toDouble();
                toolMove_color_a[tool_current_pointCount] = QString(data3.tool_drawColor_a.at(toolPath_line)).toDouble();
                toolMove_color_b[tool_current_pointCount] = QString(data3.tool_drawColor_b.at(toolPath_line)).toDouble();
                toolMove_color_c[tool_current_pointCount] = QString(data3.tool_drawColor_c.at(toolPath_line)).toDouble();
            }
            else
            {
                for (int i = 0; i < 499;i++)
                {
                    toolMove_x[i] = toolMove_x[i+1];
                    toolMove_y[i] = toolMove_y[i+1];
                    toolMove_z[i] = toolMove_z[i+1];
                    toolMove_color_a[i] = toolMove_color_a[i+1];
                    toolMove_color_b[i] = toolMove_color_b[i+1];
                    toolMove_color_c[i] = toolMove_color_c[i+1];
                }
                toolMove_x[499] = x1.toDouble();
                toolMove_y[499] = y1.toDouble();
                toolMove_z[499] = z1.toDouble();
                toolMove_color_a[499] = QString(data3.tool_drawColor_a.at(toolPath_line)).toDouble();
                toolMove_color_b[499] = QString(data3.tool_drawColor_b.at(toolPath_line)).toDouble();
                toolMove_color_c[499] = QString(data3.tool_drawColor_c.at(toolPath_line)).toDouble();
            }
            toolPath_line++;
            emit Update();
            emit sendNowDrawingLineNumber(Line.toInt(),Linecount);
        }
        else
        {
            toolPath_line = 0;
            tool_current_pointCount = 0;
            timer->stop();
        }

    }
#endif
}
void VScreen::ScalingSize(double size)
{
    scaling = size;
}

void VScreen::Redraw()
{
    redrawset();
    data1 = data2;
}
void VScreen::clear_path()
{
    timer->stop();
    //只清除data1
    redrawset();
}
void VScreen::recover()
{
    //清空data1,data2
    redrawset();
    data2 = data1;
    data3 = data1;
    toolPath_line = 0;
}

void VScreen::Draw_line(Point st, Point ed, GLfloat color1, GLfloat color2, GLfloat color3)
{
    glBegin(GL_LINES);
    glColor3f(color1, color2, color3);//glColor3f(0.0,1.0,0.0);
    glVertex3f( draw_size_ratio * st.x,draw_size_ratio * st.y,draw_size_ratio * st.z);
    glVertex3f( draw_size_ratio * ed.x,draw_size_ratio * ed.y,draw_size_ratio * ed.z);
    glEnd();

    return;
}

void VScreen::timer1_ovf()
{
}


void VScreen::getvalue(draw_data data)
{
    data1 = data;
    data2 = data;
    data3 = data;
    draw_size_ratio = data.max_x > data.max_y ? data.max_x : data.max_y;
    draw_size_ratio = 0.4 / draw_size_ratio;
}

void VScreen::start_Sim()
{
    start_sim_or_not = true;
    if (tool_move_endornot = true)
    {
//        for(int i=0;i<500;i++)
//        {
//            toolMove_x[i] = 0.0; //
//            toolMove_y[i] = 0.0;
//            toolMove_z[i] = 0.0;
//            toolMove_color_a[i] = 0.0;
//            toolMove_color_b[i] = 0.0;
//            toolMove_color_c[i] = 0.0;
//        }
        tool_move_endornot = false;
    }
    timer->start();
}

void VScreen::pause_Sim()
{
    start_sim_or_not = false;
    timer->stop();
}

void VScreen::readend(bool end)
{
    if (end==true)
    {
    }

}

void VScreen::redrawset()
{
    data1.path_current_line.clear();
    data1.path_pos_x.clear();
    data1.path_pos_y.clear();
    data1.path_pos_z.clear();
    data1.path_drawColor_a.clear();
    data1.path_drawColor_a.clear();
    data1.path_drawColor_c.clear();

    data1.max_x = 0.0;
    data1.max_y = 0.0;
    data1.max_z = 0.0;

    data1.tool_pos_x.clear();
    data1.tool_pos_y.clear();
    data1.tool_pos_z.clear();
    data1.tool_drawColor_a.clear();
    data1.tool_drawColor_b.clear();
    data1.tool_drawColor_c.clear();
    data1.tool_current_line.clear();

    data1.rowCount = 0;
    tool_move_endornot = false;

    for(int i=0;i<4;i++)
    {
        _lfCurPos[i] = 0.0; //当前坐标
    }
    for(int i=0;i<500;i++)
    {
        toolMove_x[i] = 0.0; //
        toolMove_y[i] = 0.0;
        toolMove_z[i] = 0.0;
        toolMove_color_a[i] = 0.0;
        toolMove_color_b[i] = 0.0;
        toolMove_color_c[i] = 0.0;
    }

    mToolMoveX.clear();
    mToolMoveY.clear();
    mToolMoveZ.clear();
    mToolMoveColorA.clear();
    mToolMoveColorB.clear();
    mToolMoveColorC.clear();
    isClear = true;

    tool_current_pointCount = 0;

    toolPath_line = 0;
}

void VScreen::PushBackPath()
{
    for(int i = 0; i < data3.tool_pos_x.size(); i++)
        mToolMoveX.push_back(0.0);
    for(int i = 0; i < data3.tool_pos_y.size(); i++)
        mToolMoveY.push_back(0.0);
    for(int i = 0; i < data3.tool_pos_z.size(); i++)
        mToolMoveZ.push_back(0.0);
    for(int i = 0; i < data3.tool_drawColor_a.size(); i++)
        mToolMoveColorA.push_back(0.0);
    for(int i = 0; i < data3.tool_drawColor_b.size(); i++)
        mToolMoveColorB.push_back(0.0);
    for(int i = 0; i < data3.tool_drawColor_c.size(); i++)
        mToolMoveColorC.push_back(0.0);
}
