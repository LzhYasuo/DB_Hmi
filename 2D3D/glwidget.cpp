#include "glwidget.h"
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QVector3D>
#include <QtGui>
#include <math.h>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

//#include <GLUT.H>
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif
GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    _nXRot = 0;
    _nYRot = 0;
    _nZRot = 0;
    _nXMove = 0;
    _nYMove = 0;
    _lfZoom = 0.8;

    _theQtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    _theQtBlack = QColor::fromCmykF(1.0, 1.0, 1.0, 0.0);

    int sizea,sizeb;
    sizea = 50;
    sizeb = 50;
    QPushButton* btn_load = new QPushButton();
    btn_load->setFixedSize(sizea,sizeb);
    btn_load->setText("读取");
    dimeSwithch_btn = new QPushButton;        //2D/3D
    dimeSwithch_btn->setFixedSize(sizea,sizeb);
    dimeSwithch_btn->setText("2D/3D");
    zoomFit_btn = new QPushButton;         //
    zoomFit_btn->setFixedSize(sizea,sizeb);
    zoomFit_btn->setText("适应");
    zoomIn_btn = new QPushButton;        //放大
    zoomIn_btn->setFixedSize(sizea,sizeb);
    zoomIn_btn->setText("放大");
    zoomOut_btn = new QPushButton;       //缩小
    zoomOut_btn->setFixedSize(sizea,sizeb);
    zoomOut_btn->setText("缩小");
    zoomFull_btn = new QPushButton;
    zoomFull_btn->setFixedSize(sizea,sizeb);
    zoomFull_btn->setText("填充");
    redraw_btn = new QPushButton;
    redraw_btn->setFixedSize(sizea,sizeb);
    redraw_btn->setText("清轨迹");
    pathClear_btn = new QPushButton;
    pathClear_btn->setFixedSize(sizea,sizeb);
    pathClear_btn->setText("清空");
    startSim_btn = new QPushButton;
    startSim_btn->setFixedSize(sizea,sizeb);
    startSim_btn->setText("开始");
    QPushButton* btn_AddSpeed = new QPushButton();
    btn_AddSpeed->setFixedSize(sizea,sizeb);
    btn_AddSpeed->setText("搞快点");
    QPushButton* btn_SubSpeed = new QPushButton();
    btn_SubSpeed->setFixedSize(sizea,sizeb);
    btn_SubSpeed->setText("搞慢点");

    QVBoxLayout *btn_vlayout =new QVBoxLayout();
    btn_vlayout->addStretch();
    btn_vlayout->addWidget(btn_load);
    btn_vlayout->addWidget(startSim_btn);
    btn_vlayout->addWidget(dimeSwithch_btn);
    btn_vlayout->addWidget(zoomFit_btn);
    btn_vlayout->addWidget(zoomOut_btn);
    btn_vlayout->addWidget(zoomIn_btn);
    btn_vlayout->addWidget(zoomFull_btn);
    btn_vlayout->addWidget(redraw_btn);
    btn_vlayout->addWidget(pathClear_btn);
    btn_vlayout->addWidget(btn_AddSpeed);
    btn_vlayout->addWidget(btn_SubSpeed);
    QHBoxLayout *mainlayout = new QHBoxLayout();

    mainlayout->addStretch();//增加伸缩量
    mainlayout->addLayout(btn_vlayout);
    this->setLayout(mainlayout);

    connect(btn_load,&QPushButton::clicked,this,&GLWidget::LoadFile);
    connect(dimeSwithch_btn,SIGNAL(clicked()),this,SLOT(switch_dime()));
    connect(pathClear_btn,SIGNAL(clicked()),this,SLOT(clear_path()));
    connect(zoomFull_btn,SIGNAL(clicked()),this,SLOT(zoomfull()));
    connect(zoomIn_btn,SIGNAL(clicked()),this,SLOT(zoomin()));
    connect(zoomOut_btn,SIGNAL(clicked()),this,SLOT(zoomout()));
    connect(zoomFit_btn,SIGNAL(clicked()),this,SLOT(zoomfit()));
    connect(redraw_btn,SIGNAL(clicked()),this,SLOT(RedrawGL()));
    connect(startSim_btn,SIGNAL(clicked()),this,SLOT(startSim_btn_clicked()));
    connect(btn_AddSpeed,&QPushButton::clicked,this,[=](){emit AddSpeed();});
    connect(btn_SubSpeed,&QPushButton::clicked,this,[=](){emit SubSpeed();});
}

void GLWidget::LoadFile()
{
   QFileDialog *fileDialog = new QFileDialog();
   static QString path = "./";

   filename = fileDialog->getOpenFileName(this, "Select job", path, "CNC Files (*.nc *.cnc *.ngc *.gc *.iso *.tap)");

   path = QFileInfo(filename).path();
   if (filename.isEmpty()) {return; }
   emit load_newfile();

   loadfile();

}
void GLWidget::loadfile()//加载加工文件
{
    QFile file( filename );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    emit nowOpenedFileMsg(filename);
    QString date = file.readAll ();
    gfileList = date.split ("\n");
    send_gcode(gfileList) ;
    filename=":/new/prefix1/macro.cnc";
    emit nowOpenedFileMsg(filename);
    QFile file1( filename );
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
}
void GLWidget::send_gcode(QStringList lst) {
    for (int i = 0;i < lst.size();i++ )
    {
        emit gcode(lst.at(i),i) ;
    }
}

GLWidget::~GLWidget()
{
}
void GLWidget::scalingsize(int longdata, int widthdata)//外部接入
{

}

void GLWidget::initXYZview()
{
    setXMoving(0);
    setYMoving(0);
    _lfZoom = 0.8;
    update();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _nXRot)
    {
        _nXRot = angle;
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _nYRot)
    {
        _nYRot = angle;
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _nZRot)
    {
        _nZRot = angle;
        update();
    }
}

void GLWidget::setXMoving(int nMove)
{
    if (nMove != _nXMove)
    {
        _nXMove = nMove;
        update();
    }
}

void GLWidget::setYMoving(int nMove)
{
    if (nMove != _nYMove)
    {
        _nYMove = nMove;
        update();
    }
}

void GLWidget::initializeGL()
{
    glClearColor(0.0,0.0,0.0,0.0); //设置当前清除颜色

    //glEnable(GL_DEPTH_TEST); //启用深度测试，这样，在后面的物体会被挡着，例如房子后面有棵树，如果不启用深度测试，你先画了房子再画树，树会覆盖房子的；但启用深度测试后无论你怎么画，树一定在房子后面（被房子挡着)
    glEnable(GL_CULL_FACE);   //开启剔除操作效果
    glShadeModel(GL_FLAT/*GL_SMOOTH*/);//平滑着色

// 	glEnable(GL_LIGHTING);  //启用光照,后面的渲染中使用光照
// 	glEnable(GL_LIGHT0);    //第0号光照，需要指定GL_LIGHT0

    glEnable(GL_MULTISAMPLE); //开启多重缓存
//    glutInit(this);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//    glutDisplayFunc(mydisplay);
//    glutTimerFunc(500, TimerFunc, 1);

//    glutMainLoop();
//	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //指定第0号光源的位置
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓冲以及深度缓冲

    glLoadIdentity();  //将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作

    glPushMatrix();
    glTranslatef(axis_xmove, axis_ymove, -10.0);
    glRotatef(_nXRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(_nYRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(_nZRot / 16.0, 0.0, 0.0, 1.0);
    emit draw_xyzaxis();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(_nXMove/400.0, _nYMove/400.0, -10.0);
    glRotatef(_nXRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(_nYRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(_nZRot / 16.0, 0.0, 0.0, 1.0);

    glScalef(_lfZoom,_lfZoom,_lfZoom);
    emit drawvscreen();
    glPopMatrix();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);//视口的横纵比跟视景体的横纵比不一样，绘制的图形就是变形的

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

#ifdef QT_OPENGL_ES_1
    //glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
    if (width <= height) {
        axis_xmove = -0.45;
        axis_ymove =  -0.45 * (GLfloat)height/(GLfloat)width;
        glOrthof(-0.5, 0.5, -0.5 * (GLfloat)height/(GLfloat)width, 0.5 * (GLfloat)height/(GLfloat)width, 4.0, 15.0);
    }
    else {
        axis_xmove = -0.45*(GLfloat)width/(GLfloat)height;
        axis_ymove =  -0.45;
        glOrthof(-0.5*(GLfloat)width/(GLfloat)height, 0.5*(GLfloat)width/(GLfloat)height, -0.5, 0.5, 4.0, 15.0);
    }
#else
    if (width <= height)
    {
        axis_xmove = -0.45;
        axis_ymove =  -0.45 * (GLfloat)height/(GLfloat)width;
        glOrtho(-0.5, 0.5, -0.5 * (GLfloat)height/(GLfloat)width, 0.5 * (GLfloat)height/(GLfloat)width, 4.0, 15.0);
    }
    else
    {
        axis_xmove = -0.45*(GLfloat)width/(GLfloat)height;
        axis_ymove =  -0.45;
        glOrtho(-0.5*(GLfloat)width/(GLfloat)height, 0.5*(GLfloat)width/(GLfloat)height, -0.5, 0.5, 4.0, 15.0);
    }
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    _theLastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(QApplication::keyboardModifiers () == Qt::ControlModifier)  //旋转
    {
        int dx = event->x() - _theLastPos.x();
        int dy = event->y() - _theLastPos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            setXRotation(_nXRot + 8 * dy);
            setYRotation(_nYRot + 8 * dx);
        }
        else if (event->buttons() & Qt::RightButton)
        {
            setXRotation(_nXRot + 8 * dy);
            setZRotation(_nZRot + 8 * dx);
        }
    }
    else   //平移
    {
        int dx = event->x() - _theLastPos.x();
        int dy = event->y() - _theLastPos.y();
        if (event->buttons() & Qt::LeftButton)
        {
            setXMoving(_nXMove + dx);
            setYMoving(_nYMove - dy);
        }
    }
    _theLastPos = event->pos(); //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
}

//缩放
void GLWidget::wheelEvent ( QWheelEvent *e )
{
    if(e->delta()>0)  //正数值表示滑轮相对于用户在向前滑动
    {
        if(_lfZoom*1.5 > 100)	return;
        _lfZoom *= 1.5;
        _nXMove = _nXMove+_nXMove*0.5;
        _nYMove = _nYMove+(_nYMove)*0.5;
    }
    else if(e->delta()<0)  //负数值表示滑轮相对于用户是向后滑动的
    {
        if(_lfZoom*0.7 < 0.02)	return;
        _lfZoom *= 0.7;
        _nXMove = _nXMove-_nXMove*0.3;
        _nYMove = _nYMove-(_nYMove)*0.3;
    }
    update();

    setXMoving(_nXMove);
    setYMoving(_nYMove);
}


void GLWidget::RedrawGL()
{
    emit redraw();
    if (startSim_btn->text() == "暂停")
    {
        startSim_btn->setText("开始");
        emit  pause_sim();
    }
    update();
}

void GLWidget::RecoverGL()
{   emit recover();
    if (startSim_btn->text() == "暂停")
    {
        startSim_btn->setText("开始");
        emit  pause_sim();
    }
    update();
}

void GLWidget::zoomin()
{

    if(_lfZoom*1.5 > 100)	{return;}
    _lfZoom *= 1.5;
    _nXMove = _nXMove+_nXMove*0.5;
    _nYMove = _nYMove+(_nYMove)*0.5;

   update();

   setXMoving(_nXMove);
   setYMoving(_nYMove);
}

void GLWidget::zoomout(){


    if(_lfZoom*0.7 < 0.02)	{return;}
    _lfZoom *= 0.7;
    _nXMove = _nXMove-_nXMove*0.3;
    _nYMove = _nYMove-(_nYMove)*0.3;

    update();

    setXMoving(_nXMove);
    setYMoving(_nYMove);

}

void GLWidget::zoomfit()
{
      _lfZoom = 0.75;
      setXMoving(0);
      setYMoving(0);
      update();
}

void GLWidget::zoomfull()
{
    _lfZoom = 0.8;
    setXMoving(0);
    setYMoving(0);
    update();
}

void GLWidget::clear_path()
{
   emit clearpath();
      update();
}

void GLWidget::switch_dime()
{
    if ((_nXRot !=0) ||(_nYRot !=0) ||(_nZRot !=0)   )
    {
        _nXRot = 0;
        _nYRot = 0;
        _nZRot = 0;
    }
    else
    {
        _nXRot = 4880;
        _nYRot = 5752;
        _nZRot = 480;
    }
    update();
}

void GLWidget::readend(bool end)
{
    if (end ==true)
    {
        update();

    }
}

void GLWidget::get_maxsize(double x, double y)
{
    max_x = x;
    max_y = y;
}

void GLWidget::startSim_btn_clicked()
{
    if (startSim_btn->text() == "开始")
    {
        startSim_btn->setText("暂停");
        emit  start_sim();}
    else
    {
        startSim_btn->setText("开始");
        emit pause_sim();
    }
}
