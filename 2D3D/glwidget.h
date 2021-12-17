#ifndef GLWIDGET_H
#define GLWIDGET_H
#include<QOpenGLWidget>
#include<QMouseEvent>
#include<QVector3D>
#include<QtGui>
#include<QPushButton>
#include<QWidget>
#include "analyzegcode.h"
//#include "vscreen.h"
class VScreen;
class GLWidget:public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public:
    void setXMoving(int nMove);
    void setYMoving(int nMove);
    void setZMoving(int nMove);
    //void DrawGriXYZaxis();
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void scalingsize(int, int);
    void initXYZview();

signals:
    void Load_File();
    void recievedata(int, int);
    void drawvscreen();
    void redraw();
    void clearpath();
    void recover();
    void draw_xyzaxis();
    void start_sim();
    void pause_sim();
    void load_newfile();
    void nowOpenedFileMsg(QString);
    void gcode(QString s,int row);//opengl
    void AddSpeed();
    void SubSpeed();
public slots:
    void RedrawGL();
    void RecoverGL();//load new file
    void zoomin();
    void zoomout();
    void zoomfit( );
    void zoomfull();
    void clear_path();
    void switch_dime();
    void readend(bool end);
    void get_maxsize(double  x, double  y);
    void startSim_btn_clicked();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent ( QWheelEvent *e );

    void LoadFile();
    void loadfile();
    void send_gcode(QStringList lst);
//	void timerEvent(QTimerEvent *event);

private:
    // VScreen *_theVScreen;
  // Analyzegcode * analyzegcode;
    int _nTimerID;

    int _nXRot;  //旋转
    int _nYRot;
    int _nZRot;

    int _nXMove;  //平移
    int _nYMove;
    double axis_xmove,axis_ymove;
    double   _lfZoom;   //缩放系数
    double max_x;
    double max_y;
    QPoint _theLastPos;  //记录鼠标最后一次按下时的点

    QColor _theQtGreen;  //绿色
    QColor _theQtBlack; //黑色

    QPushButton *dimeSwithch_btn;        //2D/3D
    QPushButton *zoomFit_btn;        //
    QPushButton *zoomIn_btn;     //放大
    QPushButton *zoomOut_btn;    //缩小
    QPushButton *zoomFull_btn;
    QPushButton *redraw_btn;
    QPushButton *pathClear_btn;
    QPushButton *startSim_btn;

    QStringList gfileList;
    QString filename;
};


#endif // GLWIDGET_H
