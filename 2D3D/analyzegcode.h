 #ifndef ANALYZEGCODE_H
#define ANALYZEGCODE_H

#include <QWidget>


class Analyzegcode : public QWidget
{
    Q_OBJECT

public:
    explicit Analyzegcode(QWidget *parent = 0);
    ~Analyzegcode();
    typedef struct
    {
        double max_x;//最大值
        double max_y;
        double max_z;

        QStringList tool_pos_x;//刀具位置点
        QStringList tool_pos_y;
        QStringList tool_pos_z;
        QStringList tool_drawColor_a;//刀具位置点颜色
        QStringList tool_drawColor_b;
        QStringList tool_drawColor_c;
        QStringList tool_current_line;//刀具移动当前加工行号

        QStringList path_pos_x;//轨迹位置点
        QStringList path_pos_y;
        QStringList path_pos_z;
        QStringList path_drawColor_a;//轨迹位置点颜色
        QStringList path_drawColor_b;
        QStringList path_drawColor_c;
        QStringList path_current_line;// 轨迹当前加工行号
        int rowCount;//所有的加工行，用于progressbar
    }draw_data;

    typedef struct
    {   QStringList drawtype;
        QStringList codetype;
        QStringList xcoor;
        QStringList ycoor;
        QStringList zcoor;
        QStringList icoor;
        QStringList jcoor;
        QStringList kcoor;
        QStringList rcoor;
        QStringList current_line;// 轨迹当前加工行号
    }scan_data;
    typedef struct
    {
        double x;
        double y;
        double z;
    }Point;
signals:
    void draw_value(draw_data );
    void readend(bool end);
    void error_rowinfo(int error_row,QString error_info);
private slots:
       void clear_drawData();
       void get_gcode(QString s,int rowcount);
       void readgcodefile(QString s,int rowcount);
       double value(QString s);
       QString code(QString s);
       QString code1(QString s);
       QString code2(QString s);
       QString code3(QString s);
       QString code4(QString s);
       bool check_data_valid(QString s);
       bool check_command_valid(QString s);
       void scan_maxsize(scan_data data1);

       void R_pcircle(int type,double angle);
       void R_ncircle(int type,double angle);
       void IJK_pcircle(int type );
       void IJK_ncircle(int type);

       double calculat_x(double x0,double y0,double y,int k);
       double calculat_y(double x0, double y0, double x, int k);
       double calculat_angle(double r,double length);
       double calculat_linelength(double x1,double y1,double x2,double y2);
       double Y_Coordinates(double x,double y,double k,double x0);//4个参数
       void Circle_Center(double x1, double y1, double x2, double y2, double dRadius );


private:
     int current_row ;
     bool errorornot;//判断是否哪行数据出错
     bool absornot;
     bool startornot;
     bool endornot;
     double xcoor;
     double ycoor;
     double zcoor;
     double icoor;
     double jcoor;
     double kcoor;
     double rcoor;
     int draw_type;

     draw_data draw_Data;
     scan_data scan_Data;
     double x_max;
     double y_max ;
     double z_max;



     double old_x  ;
     double old_y  ;
     double old_z ;


     double new_x  ;
     double new_y  ;
     double new_z ;
     double new_i ;
     double new_j  ;
     double new_k  ;
     double new_r ;
     double Ra  ;
     QString current_drawLine;
     Point center_point,start_point,end_point;
     Point center1,center2;
     int row_count;
     int ratio;
     enum DRAWING_TYPE
     {
         GCODE_POSITIONING=0,
         GCODE_DRAW_LINE=1,
         GCODE_DRAW_CLOCKWISE_CIRCLE=2,//顺时针圆
         GCODE_DRAW_ANTICLOCKWISE_CIRCLE=3,//逆时针圆
         GCODE_DRAW_XY_CLOCKWISE_CIRCLE=4,//顺时针圆
         GCODE_DRAW_ZX_CLOCKWISE_CIRCLE=5,//顺时针圆
         GCODE_DRAW_YZ_CLOCKWISE_CIRCLE=6,//顺时针圆
         GCODE_DRAW_XY_ANTICLOCKWISE_CIRCLE=7,//逆时针圆
         GCODE_DRAW_ZX_ANTICLOCKWISE_CIRCLE=8,//逆时针圆
         GCODE_DRAW_YZ_ANTICLOCKWISE_CIRCLE=9,//逆时针圆
         GCODE_PAUSE=10

     };
     DRAWING_TYPE drawing_type;

};

#endif // ANALYZEGCODE_H
