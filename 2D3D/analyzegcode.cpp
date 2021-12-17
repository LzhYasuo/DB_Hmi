#include "analyzegcode.h"
#include <QDebug>
#include <qmath.h>
const double Pi=3.1414926536f;
Analyzegcode::Analyzegcode(QWidget *parent) :
    QWidget(parent)
{
    startornot = false;
    endornot = false;
    absornot = true;
    errorornot = false;

    xcoor = 0.0;
    ycoor = 0.0;
    zcoor = 0.0;
    draw_type = -1;
    current_row = 0;

    icoor = 0.0;
    jcoor = 0.0;
    kcoor = 0.0;
    rcoor = 0.0;
    clear_drawData();
    x_max = 0.0;
    y_max = 0.0;
    z_max = 0.0;


   old_x = 0.0;
   old_y = 0.0;
   old_z = 0.0;


   new_x = 0.0;
   new_y = 0.0;
   new_z = 0.0;
   new_i = 0.0;
   new_j = 0.0;
   new_k = 0.0;
   new_r = 0.0;
   Ra = 0.0;
   ratio = 1;
   center_point.x = 0.0;
   center_point.y = 0.0;
   center_point.z = 0.0;
   start_point = center_point;
   end_point = center_point;
   center1 = center_point;
   center2 = center_point;
   row_count = 0;

}

Analyzegcode::~Analyzegcode()
{

}
void Analyzegcode::clear_drawData() {

    draw_Data.tool_pos_x.clear();
    draw_Data.tool_pos_y.clear();
    draw_Data.tool_pos_z.clear();
    draw_Data.tool_drawColor_a.clear();
    draw_Data.tool_drawColor_b.clear();
    draw_Data.tool_drawColor_c.clear();

    draw_Data.path_pos_x.clear();
    draw_Data.path_pos_y.clear();
    draw_Data.path_pos_z.clear();
    draw_Data.path_drawColor_a.clear();
    draw_Data.path_drawColor_b.clear();
    draw_Data.path_drawColor_c.clear();

    draw_Data.max_x = 0.0;
    draw_Data.max_y = 0.0;
    draw_Data.max_z = 0.0;
    draw_Data.path_current_line.clear();
    draw_Data.tool_current_line.clear();
    draw_Data.rowCount = 0;


    scan_Data.codetype.clear();
    scan_Data.drawtype.clear();
    scan_Data.xcoor.clear();
    scan_Data.ycoor.clear();
    scan_Data.zcoor.clear();
    scan_Data.icoor.clear();
    scan_Data.jcoor.clear();
    scan_Data.kcoor.clear();
    scan_Data.rcoor.clear();
    scan_Data.current_line.clear();



    row_count = 0;
    current_drawLine = "";
    ratio = 1;

    startornot = false;
    endornot = false;
    absornot = true;
    errorornot = false;

    xcoor = 0.0;
    ycoor = 0.0;
    zcoor = 0.0;
    draw_type = -1;
    current_row = 0;

    icoor = 0.0;
    jcoor = 0.0;
    kcoor = 0.0;
    rcoor = 0.0;

    x_max = 0.0;
    y_max = 0.0;
    z_max = 0.0;


   old_x = 0.0;
   old_y = 0.0;
   old_z = 0.0;


   new_x = 0.0;
   new_y = 0.0;
   new_z = 0.0;
   new_i = 0.0;
   new_j = 0.0;
   new_k = 0.0;
   new_r = 0.0;
   Ra = 0.0;
   ratio = 1;
   center_point.x = 0.0;
   center_point.y = 0.0;
   center_point.z = 0.0;
   start_point = center_point;
   end_point = center_point;
   center1 = center_point;
   center2 = center_point;
   row_count = 0;

}

void Analyzegcode::readgcodefile(QString s,int rowcount)
{ //qDebug()<<QString("s :%1 ").arg(s);

    int gindex,mindex,findex,sindex,tindex,hindex,dindex,nindex;
    int xindex,yindex,zindex,rindex,iindex,jindex,kindex;
    int aindex,bindex,cindex,uindex,vindex,windex ;
    int count;//存储指令出现的次数
    int G_count[49];
    for (int i =0;i<49;i++){
        G_count[i]=0;
    }
    int M_count[12];
    for (int i =0;i<12;i++){
        M_count[i]=0;
    }
    double X,Y,Z,A,B,C,U,V,W,R,I,J,K;//坐标值
    double F;//进给速度
    double S;//主轴速度
    QString T,H,D,N;//
    QString _test_code;
    QString Gcode, allgcode ;//G指令
    QString FS ;//F指令
    QString SS ;//S指令
    QString TS,HS,DS,NS ;// 指令
    QString Mcode, allmcode,MS ;//M指令

    bool x_existed,y_existed,z_existed;
    x_existed=false;
    y_existed=false;
    z_existed=false;
//**************注释*******************
//**************************************
    //有；
    if(s.indexOf("；")>-1)
    {
        s=s.left(s.indexOf("；"));
    }
    //有；
    if(s.indexOf(";")>-1)
    {
        s=s.left(s.indexOf(";"));
    }
    //有（
    if(s.indexOf("（")>-1)
    {
        //有）
        if(s.indexOf("）")>-1)
        {
            QString s1,s2;
            s1 = s.left(s.indexOf("（"));
            s2 = s.mid(s.indexOf("）")+1);
            s = s1+s2;
        }
        else
        {
            //发送错误报告
        }
    }
    //有（
    if(s.indexOf("(")>-1)
    {
        //有）
        if(s.indexOf(")")>-1)
        {
            QString s1,s2;
            s1 = s.left(s.indexOf("("));
            s2 = s.mid(s.indexOf(")")+1);
            s = s1+s2;
        }
        else
        {
            //发送错误报告
        }
    }

    if ((s.trimmed()!="") && (s.indexOf("%")<0)  && (s.indexOf("N")<0) && (s.indexOf("G")<0) && (s.indexOf("X")<0) &&
        (s.indexOf("Y")<0) && (s.indexOf("Z")<0) && (s.indexOf("A")<0) && (s.indexOf("B")<0) && (s.indexOf("C")<0) &&
        (s.indexOf("U")<0) && (s.indexOf("V")<0) && (s.indexOf("W")<0) && (s.indexOf("R")<0) && (s.indexOf("J")<0) &&
        (s.indexOf("K")<0) && (s.indexOf("I")<0) && (s.indexOf("F")<0) && (s.indexOf("S")<0) && (s.indexOf("T")<0) &&
        (s.indexOf("D")<0) && (s.indexOf("H")<0) && (s.indexOf("M")<0) && (s.indexOf("P")<0) && (s.indexOf("L")<0) &&
        (s.indexOf("Q")<0))
        {
            //发送错误报告
        }
//**************Gcode*******************
//**************************************
    count=s.count("G");//查看有几个G指令
    if(count>-1)
    {
        for(int i=0;i<count;i++)
        {
            gindex=s.indexOf("G");
            Gcode=code(s.mid(gindex+1).trimmed());
            if (s.mid(gindex+1,1)==" ")
            {

            }
            else
            {
                switch (Gcode.toInt())
                {
                case 0:
                {
                    G_count[0]++;
                    if (G_count[0]>1)
                    {
                        //发送错误报告
                    }
                    else
                    {
                        startornot=true;
                        endornot=false;
                        drawing_type=GCODE_POSITIONING;//快速定位
                        draw_type=0;
                    }
                    break;
                }
                case 1:
                {
                    G_count[1]++;
                    if (G_count[1]>1)
                    {
                        //发送错误报告
                    }
                    else
                    {
                        startornot=true;//直线插补
                        endornot=false;
                        drawing_type=GCODE_DRAW_LINE;
                        draw_type=1;
                    }
                    break;
                }

                case 2:
                {
                    G_count[2]++;
                    if (G_count[2]>1)
                    {
                        //发送错误报告
                    }
                    else
                    {
                        startornot=true;//顺圆插补
                        endornot=false;
                        drawing_type=GCODE_DRAW_CLOCKWISE_CIRCLE;
                        draw_type=2;
                    }
                    break;
                }
                case 3:
                {
                    G_count[3]++;
                    if (G_count[3]>1)
                    {

                    }
                    else
                    {
                        startornot=true;//顺圆插补
                        endornot=false;
                        drawing_type=GCODE_DRAW_ANTICLOCKWISE_CIRCLE;
                        draw_type=3;
                    }
                    break;
                }
                case 4:
                {
                    G_count[4]++;
                    if (G_count[4]>1)
                    {

                    }
                    else
                    {
                        startornot=true;//顺圆插补
                        endornot=false;
                        drawing_type=GCODE_PAUSE;
                        draw_type=10;
                    }
                    break;
                }
                case 17:
                {
                    //XY平面选择
                    G_count[5]++;
                    if (G_count[5]>1)
                    {

                    }
                    else
                    {
                        if(  drawing_type==GCODE_DRAW_CLOCKWISE_CIRCLE )
                        {
                            drawing_type=GCODE_DRAW_XY_CLOCKWISE_CIRCLE;
                            draw_type=4;
                        }
                        if(  drawing_type==GCODE_DRAW_ANTICLOCKWISE_CIRCLE )
                        {
                            drawing_type=GCODE_DRAW_XY_ANTICLOCKWISE_CIRCLE;
                            draw_type=7;
                        }
                    }
                    break;
                }
                case 18:
                {//ZX平面选择
                    G_count[6]++;
                    if (G_count[6]>1)
                    {

                    }
                    else
                    {
                        if(  drawing_type==GCODE_DRAW_CLOCKWISE_CIRCLE )
                        {
                            drawing_type=GCODE_DRAW_ZX_CLOCKWISE_CIRCLE;
                            draw_type=5;
                        }
                        if(  drawing_type==GCODE_DRAW_ANTICLOCKWISE_CIRCLE )
                        {
                            drawing_type=GCODE_DRAW_ZX_ANTICLOCKWISE_CIRCLE;
                            draw_type=8;
                        }
                    }
                    break;
                }
                case 19:
                {//YZ平面选择
                    G_count[7]++;
                    if (G_count[7]>1)
                    {

                    }
                    else
                    {

                        if(  drawing_type==GCODE_DRAW_CLOCKWISE_CIRCLE )
                        {
                            drawing_type=GCODE_DRAW_YZ_CLOCKWISE_CIRCLE;
                            draw_type=6;
                        }
                        if(  drawing_type==GCODE_DRAW_ANTICLOCKWISE_CIRCLE)
                        {
                            drawing_type=GCODE_DRAW_YZ_ANTICLOCKWISE_CIRCLE;
                            draw_type=9;
                        }
                    }
                    break;
                }
                case 90:
                    G_count[23]++;
                    if (G_count[23]>1)
                    {

                    }
                    else
                    {
                        absornot = true;
                    }
                    break;//绝对式编程
                case 91:
                    G_count[24]++;
                    if (G_count[24]>1)
                    {
                        errorornot = true;
                        QString ss = QString(" Same command '%1' used! ").arg("G" +Gcode);
                        emit error_rowinfo(current_row,ss);
                    }
                    else
                    {
                        absornot=false;
                    }
                    break;//增量式编程

                default :
                    break;
                }
            }
        }
    }
//**************Mcode*******************
//**************************************
    MS=s;
    count=MS.count("M");//查看有几个m指令
    if(count>-1){
        for(int i=0;i<count;i++)
        {
            mindex=MS.indexOf("M") ;
            if (MS.mid(mindex+1,1)==" ")
            {

            }
            else
            {
                Mcode=code(MS.mid(mindex+1).trimmed());
                switch (Mcode.toInt())
                {
                case 30:
                {//程序结束并返回程序起点
                    M_count[3]++;
                    if (M_count[3]>1)
                    {

                    }
                    else
                    {
                        startornot=false;
                        endornot=true;
                    }
                    break;
                }
                case 2:
                {//程序结束
                    M_count[4]++;
                    if (M_count[4]>1)
                    {

                    }
                    else
                    {
                        startornot=false;
                        endornot=true;
                    }
                    break;
                }
                default:
                    break;
                }
            }
            MS=MS.mid(mindex+1);
        }
    }
 //**************%code*******************
 //**************************************
    QString name =s;
    QString namecode;
    int nameindex;
    if(name.indexOf("%")>-1)
    {
        //有%
        nameindex=name.indexOf("%");
        if (name.mid(nameindex+1,1)==" ")
        {
        }
        else
        {
            namecode=code1(name.mid(nameindex+1 ).trimmed());
        }
    }
 //**************Ncode*******************
 //**************************************
    NS=s;
    if(NS.indexOf("N")>-1)
    {//有N
        nindex=NS.indexOf("N");
        if (NS.mid(nindex+1,1)==" ")
        {

        }
        else
        {
            N = code1(NS.mid(nindex+1 ).trimmed());
        }
    }
//**************Tcode*******************
//**************************************
    TS=s;
    if(TS.indexOf("T")>-1)
    {
        //有T
        tindex=TS.indexOf("T");
        if (TS.mid(tindex+1,1)==" ")
        {

        }
        else
        {
            T=code1(TS.mid(tindex+1 ).trimmed());
        }
    }
//**************Hcode*******************
//**************************************
    HS=s;
    if(HS.indexOf("H")>-1)
    {
        //有H
        hindex=HS.indexOf("H");
        if (HS.mid(hindex+1,1)==" ")
        {

        }
        else
        {
            H=code1(HS.mid(hindex+1 ).trimmed());
        }
    }
//**************Dcode*******************
//**************************************
    DS=s;
    if(DS.indexOf("D")>-1)
    {
        //有D
        dindex=DS.indexOf("D");
        if (DS.mid(dindex+1,1)==" ")
        {

        }
        else
        {
            D=code1(DS.mid(dindex+1 ).trimmed());
        }

    }
//**************Fcode*******************
//**************************************
    FS=s;
    if(FS.indexOf("F")>-1)
    {
        //有F
        findex=FS.indexOf("F");
        if (FS.mid(findex+1,1)==" ")
        {
        }
        else
        {
            F=value(FS.mid(findex+1).trimmed());
        }
    }
//**************Scode*******************
//**************************************
    SS=s;
    if(SS.indexOf("S")>-1){//有F
        sindex=SS.indexOf("S");
        if (SS.mid(sindex+1,1)==" ")
        {

        }
        else
        {
            S=value(SS.mid(sindex+1).trimmed());


        }
    }
//**************X,Y,Z,A,B,C,U,V,W,I,J,K,Rcode*******************
//**************************************************
    if(s.indexOf("X")>-1)
    {
        //有X
        xindex=s.indexOf("X");
        if(s.mid(xindex+1,1)==" ")
        {

        }
        else
        {
            x_existed=true;
            X=value(s.mid(xindex+1).trimmed());
            xcoor=X;
        }
    }

    if(s.indexOf("Y")>-1)
    {
        //有Y
        yindex=s.indexOf("Y");
        if(s.mid(yindex+1,1)==" ")
        {

        }
        else
        {
            y_existed=true;
            Y=value(s.mid(yindex+1).trimmed());
            ycoor=Y  ;
        }

    }
#if 1
    if(s.indexOf("A")>-1)
    {
        //有Z
        zindex=s.indexOf("A");
        if(s.mid(zindex+1,1)==" ")
        {

        }
        else
        {
            z_existed=true;
            Z=value(s.mid(zindex+1).trimmed());
            zcoor = Z ;
        }
    }
#endif
#if 0
    if(s.indexOf("A")>-1)
    {
        //有A
        aindex=s.indexOf("A");
        if(s.mid(aindex+1,1)==" ")
        {

        }
        else
        {
            A=value(s.mid(aindex+1).trimmed());
        }
    }
#endif
    if(s.indexOf("B")>-1)
    {
        //有B
        bindex=s.indexOf("B");
        if(s.mid(bindex+1,1)==" ")
        {
        }
        else
        {
            B=value(s.mid(bindex+1).trimmed());
        }
    }
    if(s.indexOf("C")>-1)
    {
        //有C
        cindex=s.indexOf("C");
        if(s.mid(cindex+1,1)==" ")
        {

        }
        else
        {
            C=value(s.mid(cindex+1).trimmed());
        }
    }
    if(s.indexOf("U")>-1)
    {
        //有U
        uindex=s.indexOf("U");
        if(s.mid(uindex+1,1)==" ")
        {

        }
        else
        {
            U=value(s.mid(uindex+1).trimmed());
        }
    }
    if(s.indexOf("V")>-1)
    {
        //有V
        vindex=s.indexOf("V");
        if(s.mid(vindex+1,1)==" ")
        {

        }
        else
        {
            V=value(s.mid(vindex+1).trimmed());
        }
    }
    if(s.indexOf("W")>-1)
    {
        //有W
        windex=s.indexOf("W");
        if(s.mid(windex+1,1)==" ")
        {

        }
        else
        {
            W=value(s.mid(windex+1).trimmed());
        }
    }
    if(s.indexOf("R")>-1)
    {
        //有R
        rindex=s.indexOf("R");
        if ((draw_type<2) ||(draw_type>9) )
        {

        }
        if(s.mid(rindex+1,1)==" "){

        }
        else
        {
            R=value(s.mid(rindex+1).trimmed());
            rcoor =R ;
        }
    }
    else
    {
        rcoor =0.0 ;
    }
    if(s.indexOf("I")>-1)
    {
        //有I
        iindex=s.indexOf("I");
        if ((draw_type<2) ||(draw_type>9))
        {

        }
        if(s.mid(iindex+1,1)==" ")
        {

        }
        else
        {
            I=value(s.mid(iindex+1).trimmed());
            icoor =I ;
        }
    }
    else
    {
        icoor =0.0 ;
    }

    if(s.indexOf("J")>-1)
    {
        //有J
        jindex=s.indexOf("J");
        if(s.mid(jindex+1,1)==" ")
        {
        }
        else
        {
            J=value(s.mid(jindex+1).trimmed());
            jcoor =J ;
        }
    }
    else
    {
        jcoor =0.0 ;
    }
    if(s.indexOf("K")>-1)
    {
        //有K
        kindex=s.indexOf("K");
        if(s.mid(kindex+1,1)==" ")
        {

        }
        else
        {
            K=value(s.mid(kindex+1).trimmed());
            kcoor =K ;
        }
    }
    else
    {
        kcoor =0.0 ;
    }
    if((draw_type == 2) && (y_existed == true) && (x_existed == true)) {draw_type = 4;}
    if((draw_type == 3) && (y_existed == true) && (x_existed == true)) {draw_type = 7;}
    if((draw_type == 2) && (y_existed == true) && (z_existed == true)) {draw_type = 6;}
    if((draw_type == 3) && (y_existed == true) && (z_existed == true)) {draw_type = 9;}
    if((draw_type == 2) && (z_existed == true) && (x_existed == true)) {draw_type = 5;}
    if((draw_type == 3) && (z_existed == true) && (x_existed == true)) {draw_type = 8;}
    if(startornot == true)
    {
        row_count++;
        scan_Data.codetype.append(QString::number(absornot));
        scan_Data.drawtype.append(QString::number(draw_type));
        scan_Data.xcoor.append(QString::number(xcoor));
        scan_Data.ycoor.append(QString::number(ycoor));
        scan_Data.zcoor.append(QString::number(zcoor));
        scan_Data.icoor.append(QString::number(icoor));
        scan_Data.jcoor.append(QString::number(jcoor));
        scan_Data.kcoor.append(QString::number(kcoor));
        scan_Data.rcoor.append(QString::number(rcoor));
        scan_Data.current_line.append(QString::number(rowcount));
    }
    if (endornot == true)
    {
        row_count++;
        draw_Data.rowCount = row_count;
        ratio = 100;
        scan_maxsize(scan_Data);
        draw_Data.max_x = x_max;
        draw_Data.max_y = y_max;
        draw_Data.max_z = z_max;
        emit draw_value(draw_Data);
        emit readend(true);
        endornot = false;
        x_max = 0.0;
        y_max = 0.0;
        z_max = 0.0;
    }
}

double Analyzegcode::value(QString s)
{
    QString str;
    for(int k=0;k<s.length();k++)
    {
        if( s.mid(k,1)=="0"||s.mid(k,1)=="1"||s.mid(k,1)=="2"||s.mid(k,1)=="3"||s.mid(k,1)=="4"||s.mid(k,1)=="5"||s.mid(k,1)=="6"||s.mid(k,1)=="7"||s.mid(k,1)=="8"||s.mid(k,1)=="9"||s.mid(k,1)=="."||s.mid(k,1)=="-"||s.mid(k,1)=="+")
        {
            str.append(s.mid(k,1));
        }
        else
        {
            break;
        }
    }
    if ((check_data_valid(str))&&( str!="")&&( str!=".")&&( str!="+")&&( str!="-")  )
    {
        return str.toDouble();
    }
    else
    {
        return 0;
    }
}

QString Analyzegcode::code(QString s)
{
    QString str;
    for(int k=0;k<s.length();k++)
    {
        if( s.mid(k,1)=="0"||s.mid(k,1)=="1"||s.mid(k,1)=="2"||s.mid(k,1)=="3"||s.mid(k,1)=="4"
            ||s.mid(k,1)=="5"||s.mid(k,1)=="6"||s.mid(k,1)=="7"||s.mid(k,1)=="8"||s.mid(k,1)=="9" )
        {
            str.append(s.mid(k,1));
        }
        else
        {
            break;
        }
    }
    if ((str == "") || (str.length()>2))
    {
        return "";
    }
    else
    {
        return str ;
    }
}
QString Analyzegcode::code1(QString s)
{
    QString str;
    for(int k=0;k<s.length();k++)
    {
        if( s.mid(k,1)=="0"||s.mid(k,1)=="1"||s.mid(k,1)=="2"||s.mid(k,1)=="3"||s.mid(k,1)=="4"||
            s.mid(k,1)=="5"||s.mid(k,1)=="6"||s.mid(k,1)=="7"||s.mid(k,1)=="8"||s.mid(k,1)=="9" )
        {
            str.append(s.mid(k,1));
        }
        else
        {
            break;
        }
    }
    if ((str ==""))
    {
        return "";
    }
    else
    {
        return str ;
    }
}
QString Analyzegcode::code2(QString s)//用于检测整行代码是否有违规字符
{
    QString str;
    for(int k=0;k<s.length();k++)
    {
        if( s.mid(k,1)=="0"||s.mid(k,1)=="1"||s.mid(k,1)=="2"||s.mid(k,1)=="3"||s.mid(k,1)=="4"||s.mid(k,1)=="5"||s.mid(k,1)=="6"||s.mid(k,1)=="7"||s.mid(k,1)=="8"||s.mid(k,1)=="9" ||s.mid(k,1)=="."||s.mid(k,1)=="+"||s.mid(k,1)=="-")
        {
            str.append(s.mid(k,1));
        }
        else
        {
            break;
        }
    }
    return str ;
}
QString Analyzegcode::code3(QString s)//指令后面有空格
{
    QString str;
    for(int k=0;k<s.length();k++)
    {
        if( s.mid(k,1)=="0"||s.mid(k,1)=="1"||s.mid(k,1)=="2"||s.mid(k,1)=="3"||s.mid(k,1)=="4"||s.mid(k,1)=="5"||s.mid(k,1)=="6"||s.mid(k,1)=="7"||s.mid(k,1)=="8"||s.mid(k,1)=="9" ||s.mid(k,1)==" " )
        {
            str.append(s.mid(k,1));
        }
        else
        {
            break;
        }

    }
    for(int k=0;k<str.length();k++)
    {
        if (str.right(1) ==" ")
        {
            str=str.left(str.length()-1);
        }
    }
    return str ;
}

QString Analyzegcode::code4(QString s)//数据后面有空格
{
    QString str;
    for(int k=0;k<s.length();k++)
    {
        if( s.mid(k,1)=="0"||s.mid(k,1)=="1"||s.mid(k,1)=="2"||s.mid(k,1)=="3"||s.mid(k,1)=="4"||s.mid(k,1)=="5"||s.mid(k,1)=="6"||s.mid(k,1)=="7"||s.mid(k,1)=="8"||s.mid(k,1)=="9" ||s.mid(k,1)=="."||s.mid(k,1)=="+"||s.mid(k,1)=="-"||s.mid(k,1)==" ")
        {
            str.append(s.mid(k,1));
        }
        else
        {
            break;
        }
    }
    for(int k=0;k<str.length();k++)
    {
        if (str.right(1) ==" ")
        {
            str=str.left(str.length()-1);
        }
    }
    return str ;
}

void Analyzegcode:: get_gcode(QString s, int rowcount)
{
    current_row = rowcount;
    readgcodefile(s,rowcount);
}

bool Analyzegcode::check_data_valid(QString s )
{
    int dot_count;
    int sign_count;
    dot_count = 0;
    sign_count = 0;
    for(int k=0;k<s.length();k++)
    {
        if (s.mid(k,1) == ".")
        {
            dot_count++;
            if (dot_count >1)
            {
                return false;
            }
        }
        if ((s.mid(k,1) == "+")||(s.mid(k,1) == "-"))
        {
            sign_count++;
            if (sign_count >1)
            {
                return false;
            }
        }
    }
    return true;
}

bool Analyzegcode::check_command_valid(QString s)
{
    int dot_count;
    int sign_count;
    dot_count = 0;
    sign_count = 0;
    for(int k=0;k<s.length();k++)
    {
        if (s.mid(k,1) == ".")
        {
            dot_count++;
            if (dot_count >1)
            {
                return false;
            }

        }
        if ((s.mid(k,1) == "+")||(s.mid(k,1) == "-"))
        {
            sign_count++;
            if (sign_count >1)
            {
                return false;
            }
        }
    }
    return true;
}

void Analyzegcode::scan_maxsize(scan_data data1)
{
    int count = 0;
    double x_pos = 0.0;
    double y_pos = 0.0;
    double z_pos = 0.0;
    old_x = 0.0;
    old_y = 0.0;
    old_z = 0.0;
    new_x = 0.0;
    new_y = 0.0;
    new_z = 0.0;
    new_i = 0.0;
    new_j = 0.0;
    new_k = 0.0;
    new_r = 0.0;
    Ra = 0.0;

    center_point.x = 0.0;
    center_point.y = 0.0;
    center_point.z = 0.0;
    start_point = center_point;
    end_point = center_point;
    center1 = center_point;
    center2 = center_point;

    int DRAWINGTYPE = -1;
    int CODE_TYPE = -1;
    QString X,Y,Z,I,J,K,R;
    for (int i = 0;i < data1.codetype.size();i++)
    {
        CODE_TYPE = data1.codetype.at(i).toInt();
        DRAWINGTYPE = data1.drawtype.at(i).toInt();
        current_drawLine = data1.current_line.at(i);
        if (CODE_TYPE == 1) {//绝对值编程
            new_x = data1.xcoor.at(i).toDouble();
            new_y = data1.ycoor.at(i).toDouble();
            new_z = data1.zcoor.at(i).toDouble();
            new_i = data1.icoor.at(i).toDouble();
            new_j = data1.jcoor.at(i).toDouble();
            new_k = data1.kcoor.at(i).toDouble();
            new_r = data1.rcoor.at(i).toDouble();
        }
        else
        {
            // 增量式编程
            new_x = data1.xcoor.at(i).toDouble() + old_x;
            new_y = data1.ycoor.at(i).toDouble() + old_y;
            new_z = data1.zcoor.at(i).toDouble() + old_z;
            new_i = data1.icoor.at(i).toDouble();
            new_j = data1.jcoor.at(i).toDouble();
            new_k = data1.kcoor.at(i).toDouble();
            new_r = data1.rcoor.at(i).toDouble();
        }
        if (DRAWINGTYPE == 0)
        {
            count = ratio * sqrt((new_x - old_x) * (new_x - old_x) + (new_y - old_y) * (new_y - old_y) + (new_z - old_z) * (new_z - old_z)) ;
            if (count < 10) { count = 10;}
            if (count > 20) { count = 20;}

            x_max = abs(new_x) > abs(x_max) ? abs(new_x) : abs(x_max);
            y_max = abs(new_y) > abs(y_max) ? abs(new_y) : abs(y_max);
            z_max = abs(new_z) > abs(z_max) ? abs(new_z) : abs(z_max);

            for (int i = 0;i < count+1;i++)
            {
                x_pos = old_x + ((i) * (new_x - old_x)) / count;
                y_pos = old_y + ((i) * (new_y - old_y)) / count;
                z_pos = old_z + ((i) * (new_z - old_z)) / count;

                draw_Data.tool_pos_x.append(QString::number(x_pos));
                draw_Data.tool_pos_y.append(QString::number(y_pos));
                draw_Data.tool_pos_z.append(QString::number(z_pos));
                draw_Data.tool_drawColor_a.append(QString::number(0));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            x_pos = 0.0;
            y_pos = 0.0;
            z_pos = 0.0;

            draw_Data.path_pos_x.append(QString::number(old_x));
            draw_Data.path_pos_y.append(QString::number(old_y));
            draw_Data.path_pos_z.append(QString::number(old_z));
            draw_Data.path_drawColor_a.append(QString::number(1));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(0));
            draw_Data.path_current_line.append(current_drawLine);
            draw_Data.path_pos_x.append(QString::number(new_x));
            draw_Data.path_pos_y.append(QString::number(new_y));
            draw_Data.path_pos_z.append(QString::number(new_z));
            draw_Data.path_drawColor_a.append(QString::number(1));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(0));
            draw_Data.path_current_line.append(current_drawLine);
        }
        if (DRAWINGTYPE == 1)
        {
            //直线
            count = ratio * sqrt((new_x - old_x) * (new_x - old_x) + (new_y - old_y) * (new_y - old_y) + (new_z - old_z) * (new_z - old_z)) ;
            if (count < 10) { count = 10;}
            if (count > 20) { count = 20;}
            x_max = abs(new_x) > abs(x_max) ? abs(new_x) : abs(x_max);
            y_max = abs(new_y) > abs(y_max) ? abs(new_y) : abs(y_max);
            z_max = abs(new_z) > abs(z_max) ? abs(new_z) : abs(z_max);
            for (int i = 0;i < count+1;i++)
            {
                x_pos = old_x + ((i) * (new_x - old_x)) / count;
                y_pos = old_y + ((i) * (new_y - old_y)) / count;
                z_pos = old_z + ((i) * (new_z - old_z)) / count;
                draw_Data.tool_pos_x.append(QString::number(x_pos));
                draw_Data.tool_pos_y.append(QString::number(y_pos));
                draw_Data.tool_pos_z.append(QString::number(z_pos));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            x_pos = 0.0;
            y_pos = 0.0;
            z_pos = 0.0;

            draw_Data.path_pos_x.append(QString::number(old_x));
            draw_Data.path_pos_y.append(QString::number(old_y));
            draw_Data.path_pos_z.append(QString::number(old_z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
            draw_Data.path_pos_x.append(QString::number(new_x));
            draw_Data.path_pos_y.append(QString::number(new_y));
            draw_Data.path_pos_z.append(QString::number(new_z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        if (DRAWINGTYPE == 4)
        {
            //XY顺圆
            start_point.x = old_x;
            start_point.y = old_y;
            start_point.z = old_z;
            end_point.x = new_x;
            end_point.y = new_y;
            end_point.z = new_y;
            z_max = abs(new_z) > abs(z_max) ? abs(new_z) : abs(z_max);
            if(new_r != 0)
            {
                Ra = new_r;
                double length ;
                double angle;
                length = calculat_linelength(start_point.x,start_point.y,end_point.x,end_point.y);
                if (Ra<0)
                {
                    angle = 2 * Pi - calculat_angle(Ra,length);
                }
                else
                {
                    angle = calculat_angle(Ra,length);
                }
                Ra=abs(Ra);
                Circle_Center( start_point.x,  start_point.y, end_point.x, end_point.y,Ra );
                R_pcircle(1,angle );
            }
            else{
                Ra = sqrt(new_i * new_i + new_j * new_j);
                center_point.x = old_x + new_i;
                center_point.y = old_y + new_j;
                center_point.z = old_z;
                IJK_pcircle(1);
            }
        }
        if (DRAWINGTYPE == 5)
        {
            //ZX顺圆
            start_point.x = old_x;
            start_point.y = old_y;
            start_point.z = old_z;
            end_point.x = new_x;
            end_point.y = new_y;
            end_point.z = new_y;
            y_max = abs(new_y) > abs(y_max) ? abs(new_y) : abs(y_max);
            if ( new_r != 0 )
            {
                Ra = new_r;
                double length ;
                double angle;
                length = calculat_linelength(start_point.z,start_point.x,end_point.z,end_point.x);

                if (Ra<0)
                {
                    angle = 2*Pi - calculat_angle(Ra,length);
                }
                else
                {
                    angle = calculat_angle(Ra,length);
                }
                Ra=abs(Ra);
                Circle_Center( start_point.z,  start_point.x, end_point.z, end_point.x,Ra );
                R_pcircle(2,angle );
            }
            else
            {
                Ra=sqrt(new_i*new_i+new_k*new_k);
                center_point.x = old_x + new_i;
                center_point.y = old_y ;
                center_point.z = old_z + new_k;
                IJK_pcircle(2 );
            }
        }
        if (DRAWINGTYPE == 6)
        {
            //YZ顺圆
            start_point.x = old_x;
            start_point.y = old_y;
            start_point.z = old_z;
            end_point.x = new_x;
            end_point.y = new_y;
            end_point.z = new_y;
            x_max = abs(new_x) > abs(x_max)?abs(new_x): abs(x_max);
            if( new_r!=0 )
            {
                Ra = new_r;
                double length ;
                double angle;
                length = calculat_linelength(start_point.y,start_point.z,end_point.y,end_point.z);
                if (Ra<0)
                {
                    angle = 2*Pi - calculat_angle(Ra,length);
                }
                else
                {
                    angle = calculat_angle(Ra,length);
                }
                Ra=abs(Ra);
                Circle_Center( start_point.y,  start_point.z, end_point.y, end_point.z,Ra );
                R_pcircle(3,angle );
            }
            else
            {
                Ra=sqrt(new_k * new_k + new_j * new_j);
                center_point.x = old_x ;
                center_point.y = old_y + new_j;
                center_point.z = old_z + new_k;
                IJK_pcircle(3 );
            }
        }
        if (DRAWINGTYPE == 7)
        {
            //XY逆圆
            start_point.x = old_x;
            start_point.y = old_y;
            start_point.z = old_z;
            end_point.x = new_x;
            end_point.y = new_y;
            end_point.z = new_y;
            z_max = abs(new_z) > abs(z_max) ? abs(new_z) : abs(z_max);
            if( new_r!=0 )
            {
                Ra = new_r;
                double length ;
                double angle;
                length = calculat_linelength(start_point.x,start_point.y,end_point.x,end_point.y);
                if (Ra<0)
                {
                    angle = 2 * Pi - calculat_angle(Ra,length);
                }
                else
                {
                    angle = calculat_angle(Ra,length);
                }
                Ra=abs(Ra);
                Circle_Center( start_point.x,  start_point.y, end_point.x, end_point.y,Ra  );
                R_ncircle( 1,angle);
            }
            else
            {
                Ra = sqrt(new_i * new_i + new_j * new_j);
                center_point.x = old_x + new_i;
                center_point.y = old_y + new_j;
                center_point.z = old_z ;
                IJK_ncircle(1);
            }
        }
        if (DRAWINGTYPE == 8)
        {
            //ZX逆圆
            start_point.x = old_x;
            start_point.y = old_y;
            start_point.z = old_z;
            end_point.x = new_x;
            end_point.y = new_y;
            end_point.z = new_y;
            y_max = abs(new_y) > abs(y_max) ? abs(new_y) : abs(y_max);
            if( new_r!=0 )
            {
                Ra = new_r;
                double length ;
                double angle;
                length = calculat_linelength(start_point.z,start_point.x,end_point.z,end_point.x);
                if (Ra<0)
                {
                    angle = 2 * Pi - calculat_angle(Ra,length);
                }
                else
                {
                    angle = calculat_angle(Ra,length);
                }
                Ra = abs(Ra);
                Circle_Center( start_point.z,  start_point.x, end_point.z, end_point.x,Ra  );
                R_ncircle(2,angle );
            }
            else
            {
                Ra = sqrt(new_i  *new_i + new_k * new_k);
                center_point.x = old_x + new_i;
                center_point.y = old_y ;
                center_point.z = old_z + new_k;
                IJK_ncircle(2 );
            }
        }
        if (DRAWINGTYPE == 9)
        {
            //YZ逆圆
            start_point.x = old_x;
            start_point.y = old_y;
            start_point.z = old_z;
            end_point.x = new_x;
            end_point.y = new_y;
            end_point.z = new_y;
            x_max = abs(new_x) > abs(x_max) ? abs(new_x): abs(x_max);
            if( new_r!=0 )
            {
                Ra = new_r;
                double length ;
                double angle;
                length = calculat_linelength(start_point.y,start_point.z,end_point.y,end_point.z);

                if (Ra<0)
                {
                    angle = 2*Pi-calculat_angle(Ra,length);
                }
                else
                {
                    angle = calculat_angle(Ra,length);
                }
                Ra = abs(Ra);
                Circle_Center( start_point.y,  start_point.z, end_point.y, end_point.z,Ra  );
                R_ncircle(3,angle );
            }
            else
            {
                Ra=sqrt(new_k * new_k + new_j * new_j);
                center_point.x = old_x ;
                center_point.y = old_y + new_j;
                center_point.z = old_z + new_k;
                IJK_ncircle( 3);
            }
        }
        old_x = new_x;
        old_y = new_y;
        old_z = new_z;
        start_point.x = 0.0;
        start_point.y = 0.0;
        start_point.z = 0.0;
        end_point.x = 0.0;
        end_point.y = 0.0;
        end_point.z = 0.0;
        }
}

void Analyzegcode::R_pcircle(int type, double angle)
{
    //顺时针
    Point p1,p2;//起点。终点
    Point p3,p5,p4;
    int count = 0;
    double l = angle * Ra;
    count = ratio * l;
    if (count < 15) { count = 15;}
    if (count > 20) { count = 20;}
    double angle1,angle2;
    double gap1,gap2;
    if (type == 1)
    {
        //xy
        p1.x = start_point.x;
        p1.y = start_point.y;
        p2.x = end_point.x;
        p2.y = end_point.y;
    }
    if (type == 2 )
    {
        //zx
        p1.x = start_point.z;
        p1.y = start_point.x;
        p2.x = end_point.z;
        p2.y = end_point.x;
    }
    if (type == 3)
    {
        //yz
        p1.x = start_point.y;
        p1.y = start_point.z;
        p2.x = end_point.y;
        p2.y = end_point.z;
    }
    if (p1.x > center1.x)
    {
        if (p1.y > center1.y)
        {
            angle1 = acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x + Ra * cos(angle1 - angle);
            p3.y = center1.y + Ra * sin(angle1 - angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
        else
        {
            angle1 = -acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x + Ra * cos(angle1 - angle);
            p3.y = center1.y + Ra * sin(angle1 - angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
    }
    else
    {
        if (p1.y > center1.y)
        {
            angle1 = Pi-acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x + Ra * cos(angle1 - angle);
            p3.y = center1.y + Ra * sin(angle1 - angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);

        }
        else
        {
            angle1 = Pi+acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x+Ra*cos(angle1-angle);
            p3.y = center1.y+Ra*sin(angle1-angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
    }
    if (p1.x > center2.x)
    {
        if (p1.y > center2.y)
        {
            angle2 = acos(abs((p1.x-center2.x)/Ra));
            p5.x = center2.x+Ra*cos(angle2-angle);
            p5.y = center2.y+Ra*sin(angle2-angle);
            gap2 = calculat_linelength(p5.x,p5.y,p2.x,p2.y);
        }
        else
        {
            angle2 = -acos(abs((p1.x-center2.x)/Ra));
            p5.x = center2.x+Ra*cos(angle2-angle);
            p5.y = center2.y+Ra*sin(angle2-angle);
            gap2 = calculat_linelength(p5.x,p5.y,p2.x,p2.y);
        }
    }
    else
    {
        if (p1.y > center2.y)
        {
            angle2 = Pi-acos(abs((p1.x-center2.x)/Ra));
            p5.x = center2.x+Ra*cos(angle2-angle);
            p5.y = center2.y+Ra*sin(angle2-angle);
            gap2 = calculat_linelength(p5.x,p5.y,p2.x,p2.y);
        }
        else
        {
            angle2 = Pi+acos(abs((p1.x-center2.x)/Ra));
            p5.x = center2.x+Ra*cos(angle2-angle);
            p5.y = center2.y+Ra*sin(angle2-angle);
            gap2 = calculat_linelength(p5.x,p5.y,p2.x,p2.y);
        }
    }
    if (gap1 > gap2)
    {
        if (type == 1)
        {
            //xy
            p4.z = start_point.z;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;

            for(int i=0;i<count+1;i++)
            {
                p4.x=center2.x+Ra*cos(angle2-(angle*i)/count);
                p4.y=center2.y+Ra*sin(angle2-(angle*i)/count);
            }
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.x=center2.x+Ra*cos(angle2-(angle*i)/30);
            p4.y=center2.y+Ra*sin(angle2-(angle*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        center_point.x = center2.x;
        center_point.y = center2.y;
        center_point.z = start_point.z;
        IJK_pcircle(1);
    }
    if (type == 2 )
    {
        //zx
        p4.y = start_point.y;
        p1.x = start_point.x ;
        p1.y = start_point.y ;
        p1.z = start_point.z ;
        for(int i=0;i<count+1;i++)
        {
            p4.z=center2.x+Ra*cos(angle2-((angle)*i)/count);
            p4.x=center2.y+Ra*sin(angle2-((angle)*i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.z=center2.x+Ra*cos(angle2-(angle*i)/30);
            p4.x=center2.y+Ra*sin(angle2-(angle*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        center_point.x = center2.y;
        center_point.y = start_point.y  ;
        center_point.z = center2.x;
        IJK_pcircle(2);
    }
    if (type == 3)
    {
        //yz
        p4.x  = start_point.x;
        p1.x = start_point.x ;
        p1.y = start_point.y ;
        p1.z = start_point.z ;
        for(int i=0;i<count+1;i++)
        {
            p4.y=center2.x+Ra*cos(angle2-((angle)*i)/count);
            p4.z=center2.y+Ra*sin(angle2-((angle)*i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.y=center2.x+Ra*cos(angle2-(angle*i)/30);
            p4.z=center2.y+Ra*sin(angle2-(angle*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        center_point.x = start_point.x;
        center_point.y = center2.x ;
        center_point.z = center2.y ;
        IJK_pcircle(3);
    }
    else
    {
        //圆点为 center1
        if (type == 1)
        {
            //xy
            p4.z = start_point.z;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++)
            {
                p4.x=center1.x+Ra*cos(angle1-((angle)*i)/count);
                p4.y=center1.y+Ra*sin(angle1-((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++)
            {
                p4.x=center1.x+Ra*cos(angle1-(angle*i)/30);
                p4.y=center1.y+Ra*sin(angle1-(angle*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.z = start_point.z;
            center_point.x=center1.x ;
            center_point.y=center1.y ;
            IJK_pcircle(1);
        }
        if (type == 2 )
        {
            //zx
            p4.y = start_point.y;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++){
                p4.z=center1.x+Ra*cos(angle1-((angle)*i)/count);
                p4.x=center1.y+Ra*sin(angle1-((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++)
            {
                p4.z=center1.x+Ra*cos(angle1-(angle*i)/30);
                p4.x=center1.y+Ra*sin(angle1-(angle*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.y = start_point.y;
            center_point.z=center1.x ;
            center_point.x=center1.y ;
            IJK_pcircle(2);
        }
        if (type == 3)
        {
            //yz
            p4.x  = start_point.x;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++)
            {
                p4.y=center1.x+Ra*cos(angle1-((angle)*i)/count);
                p4.z=center1.y+Ra*sin(angle1-((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++)
            {
                p4.y=center1.x+Ra*cos(angle1-(angle*i)/30);
                p4.z=center1.y+Ra*sin(angle1-(angle*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.x = start_point.x;
            center_point.y = center1.x ;
            center_point.z = center1.y ;
            IJK_pcircle(3);
        }
    }
}

void Analyzegcode::R_ncircle(int type , double angle)
{
    //逆时针
    Point p1,p2;//起点。终点
    Point p3,p4;
    int count = 0;
    double l = angle * Ra;
    count = ratio * l;
    if (count < 15) { count = 15;}
    if (count > 20) { count = 20;}
    // qDebug()<<QString("count:%1").arg(count);
    double angle1,angle2;
    double gap1,gap2;
    if (type == 1) {//xy
        p1.x = start_point.x;
        p1.y = start_point.y;
        p2.x = end_point.x;
        p2.y = end_point.y;
    }
    if (type == 2 ) {//zx
        p1.x = start_point.z;
        p1.y = start_point.x;
        p2.x = end_point.z;
        p2.y = end_point.x;
    }
    if (type == 3) {//yz
        p1.x = start_point.y;
        p1.y = start_point.z;
        p2.x = end_point.y;
        p2.y = end_point.z;
    }
    if (p1.x > center1.x)
    {
        if (p1.y > center1.y)
        {
            angle1 = acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x + Ra * cos(angle1 + angle);
            p3.y = center1.y + Ra * sin(angle1 + angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
        else
        {
            angle1 = -acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x + Ra * cos(angle1 + angle);
            p3.y = center1.y + Ra * sin(angle1 + angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
    }
    else
    {
        if (p1.y > center1.y)
        {
            angle1 = Pi-acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x + Ra * cos(angle1 + angle);
            p3.y = center1.y + Ra * sin(angle1 + angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
        else
        {
            angle1 = Pi+acos(abs((p1.x - center1.x)/Ra));
            p3.x = center1.x + Ra * cos(angle1 + angle);
            p3.y = center1.y + Ra * sin(angle1 + angle);
            gap1 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
    }
    if (p1.x > center2.x)
    {
        if (p1.y > center2.y)
        {
            angle2 = acos((abs(p1.x - center2.x)/Ra));
            p3.x = center2.x + Ra * cos(angle2 + angle);
            p3.y = center2.y + Ra * sin(angle2 + angle);
            gap2 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
        else
        {
            angle2 = -acos((abs(p1.x - center2.x)/Ra));
            p3.x = center2.x + Ra * cos(angle2 + angle);
            p3.y = center2.y + Ra * sin(angle2 + angle);
            gap2 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
    }
    else
    {
        if (p1.y > center2.y)
        {
            angle2 = Pi-acos((abs(p1.x - center2.x)/Ra));
            p3.x = center2.x + Ra * cos(angle2 + angle);
            p3.y = center2.y + Ra * sin(angle2 + angle);
            gap2 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }
        else
        {
            angle2 = Pi+acos((abs(p1.x - center2.x)/Ra));
            p3.x = center2.x + Ra * cos(angle2 + angle);
            p3.y = center2.y + Ra * sin(angle2 + angle);
            gap2 = calculat_linelength(p3.x,p3.y,p2.x,p2.y);
        }

    }
    if (gap1 > gap2)
    {
        //圆点为 center2
        if (type == 1)
        {
            //xy
            p4.z = start_point.z;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++)
            {
                p4.x=center2.x+Ra*cos(angle2+((angle)*i)/count);
                p4.y=center2.y+Ra*sin(angle2+((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++)
            {
                p4.x=center2.x+Ra*cos(angle2+((angle)*i)/30);
                p4.y=center2.y+Ra*sin(angle2+((angle)*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.z = start_point.z;
            center_point.x=center2.x ;
            center_point.y=center2.y ;
            IJK_ncircle(1);
        }
        if (type == 2 )
        {
            //zx
            p4.y = start_point.y;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++)
            {
                p4.z=center2.x+Ra*cos(angle2+((angle)*i)/count);
                p4.x=center2.y+Ra*sin(angle2+((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++){
                p4.z=center2.x+Ra*cos(angle2+((angle)*i)/30);
                p4.x=center2.y+Ra*sin(angle2+((angle)*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.y = start_point.y;
            center_point.z=center2.x ;
            center_point.x=center2.y ;
            IJK_ncircle(2);
        }
        if (type == 3)
        {
            //yz
            p4.x  = start_point.x;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++)
            {
                p4.y=center2.x+Ra*cos(angle2+((angle)*i)/count);
                p4.z=center2.y+Ra*sin(angle2+((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++)
            {
                p4.y=center2.x+Ra*cos(angle2+((angle)*i)/30);
                p4.z=center2.y+Ra*sin(angle2+((angle)*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.x  = start_point.x;
            center_point.y=center2.x ;
            center_point.z=center2.y ;
            IJK_ncircle(3);
        }
    }
    else
    {
        //圆点为 center1

        if (type == 1) {//xy
            p4.z = start_point.z;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++){
                p4.x=center1.x+Ra*cos(angle1+((angle)*i)/count);
                p4.y=center1.y+Ra*sin(angle1+((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++){
                p4.x=center1.x+Ra*cos(angle1+((angle)*i)/30);
                p4.y=center1.y+Ra*sin(angle1+((angle)*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.z = start_point.z;
            center_point.x=center1.x ;
            center_point.y=center1.y ;
            IJK_ncircle(1);
        }
        if (type == 2 )
        {
            //zx
            p4.y = start_point.y;
            p1.x = start_point.x ;
            p1.y = start_point.y ;
            p1.z = start_point.z ;
            for(int i=0;i<count+1;i++){
                p4.z=center1.x+Ra*cos(angle1+((angle)*i)/count);
                p4.x=center1.y+Ra*sin(angle1+((angle)*i)/count);
                draw_Data.tool_pos_x.append(QString::number(p4.x));
                draw_Data.tool_pos_y.append(QString::number(p4.y));
                draw_Data.tool_pos_z.append(QString::number(p4.z));
                draw_Data.tool_drawColor_a.append(QString::number(1));
                draw_Data.tool_drawColor_b.append(QString::number(1));
                draw_Data.tool_drawColor_c.append(QString::number(0));
                draw_Data.tool_current_line.append(current_drawLine);
            }
            for(int i=0;i<31;i++)
            {
                p4.z=center1.x+Ra*cos(angle1+((angle)*i)/30);
                p4.x=center1.y+Ra*sin(angle1+((angle)*i)/30);
                draw_Data.path_pos_x.append(QString::number(p4.x));
                draw_Data.path_pos_y.append(QString::number(p4.y));
                draw_Data.path_pos_z.append(QString::number(p4.z));
                draw_Data.path_drawColor_a.append(QString::number(0));
                draw_Data.path_drawColor_b.append(QString::number(0));
                draw_Data.path_drawColor_c.append(QString::number(1));
                draw_Data.path_current_line.append(current_drawLine);
            }
            center_point.y = start_point.y;
            center_point.z=center1.x ;
            center_point.x=center1.y ;
            IJK_ncircle(2);
        }
    }
    if (type == 3)
    {
        //yz
        p4.x = start_point.x;
        p1.x = start_point.x ;
        p1.y = start_point.y ;
        p1.z = start_point.z ;
        for(int i=0;i<count+1;i++){
            p4.y=center1.x+Ra*cos(angle1+((angle)*i)/count);
            p4.z=center1.y+Ra*sin(angle1+((angle)*i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.y=center1.x+Ra*cos(angle1+((angle)*i)/30);
            p4.z=center1.y+Ra*sin(angle1+((angle)*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        center_point.x = start_point.x;
        center_point.y=center1.x ;
        center_point.z=center1.y ;
        IJK_ncircle(3)	;
    }
}
void Analyzegcode::IJK_pcircle(int type)
{
    //顺时针
    Point p1,p2;//起点。终点
    Point p0;//圆心
    Point p3,p4;//画图的起点。终点
    double maxx,maxy;
    int count = 0;
    double l;

    Point right,left,up,down;
    double angle1 ,angle;
    double A,B;

    int type1,type2;
    int type3;
    A=0;
    B=0;
    angle1=0;
    angle=0;

    if (type == 1)
    {
        //xy
        type3=1;
        p1.x = start_point.x;
        p1.y = start_point.y;
        p2.x = end_point.x;
        p2.y = end_point.y;
        p0.x = center_point.x;
        p0.y = center_point.y;
        right.x=center_point.x+Ra;
        right.y=center_point.y;
        left.x=center_point.x-Ra;
        left.y=center_point.y;
        up.y=center_point.y+Ra;
        up.x=center_point.x;
        down.y=center_point.y-Ra;
        down.x=center_point.x;
    }
    if (type == 2 )
    {
        //zx
        type3=2;
        p1.x = start_point.z;
        p1.y = start_point.x;
        p2.x = end_point.z;
        p2.y = end_point.x;
        p0.x = center_point.z;
        p0.y = center_point.x;
        right.x=center_point.z+Ra;
        right.y=center_point.x;
        left.x=center_point.z-Ra;
        left.y=center_point.y;
        up.y=center_point.x+Ra;
        up.x=center_point.z;
        down.y=center_point.x-Ra;
        down.x=center_point.z;
    }
    if (type == 3)
    {
        //yz
        type3=3;
        p1.x = start_point.y;
        p1.y = start_point.z;
        p2.x = end_point.y;
        p2.y = end_point.z;
        p0.x = center_point.y;
        p0.y = center_point.z;
        right.x=center_point.y+Ra;
        right.y=center_point.z;
        left.x=center_point.y-Ra;
        left.y=center_point.z;
        up.y=center_point.z+Ra;
        up.x=center_point.y;
        down.y=center_point.z-Ra;
        down.x=center_point.y;
    }

    if (p1.x > p0.x)
    {
        //右上四分一圆
        if (p1.y > p0.y)
        {
            type1 = 1;
        }
        //右下四分一圆
        else
        {
            type1 = 2;
        }
    }
    else
    {
        //左上四分一圆
        if (p1.y > p0.y)
        {
            type1 = 4;
        }
        //左下四分一圆
        else
        {
            type1 = 3;
        }
    }
    if (p2.x > p0.x)
    {
        //右上四分一圆
        if (p2.y > p0.y)
        {
            type2 = 1;
        }
        //右下四分一圆
        else
        {
            type2 = 2;
        }
    }
    else
    {
        //左上四分一圆
        if (p2.y > p0.y)
        {
            type2 = 4;
        }
        //左下四分一圆
        else
        {
            type2 = 3;
        }
    }
    if ((p1.x==right.x)||(p1.x==left.x))
    {
        A=0;
    }
    else
    {
        A = acos(abs(p1.x  - p0.x )/Ra);
    }
    if( (int)(abs(p2.x  - p0.x )/Ra)!=1 )
    {
        B = acos( abs(p2.x  - p0.x )/Ra);
    }
    else
    {
        B=0;
    }

    //整圆
    if ((p1.x == p2.x) && (p1.y == p2.y))
    {
        maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
        maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
        angle = 2 * Pi;
        if (type1==1) {angle1 = A;}
        if (type1==2) {angle1 = -A;}
        if (type1==3) {angle1 = Pi + A;}
        if (type1==4) {angle1 = Pi - A;}

    }
    //非整圆
    else
    {
        switch (type1)
        {
        case 1:
        {
            if ((type2 == 1) && (p2.x > p1.x))
            {
                //<90
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                angle1 =  A;
                angle = A - B;
            }
            if ((type2 == 1) && (p2.x < p1.x))
            {
                //>270
                angle1 = A;
                angle = 2 * Pi + A - B;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 1) && (p2.x == p1.x))
            {
                angle1 = A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }

            if (type2 == 2)
            {
                angle1 = A;
                angle = A + B;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(right.x) ? maxx : abs(right.x);
            }
            if (type2 == 3)
            {
                angle1 = A;
                angle = A + Pi - B;
                maxy = abs(p1.y) > abs(down.y) ? abs(p1.y) : abs(down.y);
                maxx = abs(p2.x) > abs(right.x) ? abs(p2.x) : abs(right.x);

            }
            if (type2 == 4)
            {
                angle1 = A;
                angle = A + B + Pi;
                maxx = abs(left.x) > abs(right.x) ? abs(left.x) : abs(right.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(down.y)? abs(maxy) : abs(down.y);
            }
            break;
        }
        case 2:
        {
            if ((type2 == 2) && (p2.x > p1.x))
            {
                //>270
                angle1 = -A;
                angle = B + 2 * Pi - A;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 2) && (p2.x < p1.x))
            {
                //<90
                angle1 = -A;
                angle = B - A;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if ((type2 == 2) && (p2.x == p1.x))
            {
                angle1 = -A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if (type2 == 3) {
                angle1 = -A;
                angle = -B + Pi - A;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(down.y) ? abs(maxy) : abs(down.y);
            }
            if (type2 == 4)
            {
                angle1 = -A;
                angle = B + Pi - A;
                maxy = abs(p2.y) > abs(down.y)? abs(p2.y) : abs(down.y);
                maxx = abs(p1.x) > abs(left.x)? abs(p1.x): abs(left.x);
            }
            if (type2 == 1)
            {
                angle1 = -A;
                angle = -B + 2 * Pi - A;
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(left.x) ? abs(maxx) : abs(left.x);
            }
            break;
        }
        case 3:
        {
            if ((type2 == 3) && (p2.x > p1.x))
            {
                //>270
                angle1 = Pi + A;
                angle = -B + 2 * Pi + A;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 3) && ((p2.x < p1.x)))
            {
                //<90
                angle1 = Pi + A;
                angle = -B + A;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if ((type2 == 3) && (p2.x ==p1.x))
            {
                angle1 = Pi+A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if (type2 == 4)
            {
                angle1 = Pi + A;
                angle = A + B;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(left.x) ? abs(maxx) : abs(left.x);
            }
            if (type2 == 1)
            {
                angle1 = Pi + A;
                angle = -B + Pi + A;
                maxx = abs(p2.x) > abs(left.x) ? abs(p2.x) : abs(left.x);
                maxy = abs(p1.y) > abs(up.y) ? abs(p1.y) : abs(up.y);
            }
            if (type2 == 2)
            {
                angle1 = Pi + A;
                angle = B + Pi + A;
                maxx = abs(left.x) > abs(right.x) ? abs(left.x): abs(right.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(up.y) ? abs(maxy) : abs(up.y);
            }
            break;
        }
        case 4:
        {
            if ((type2 == 4) && (p2.x > p1.x))
            {
                //<90
                angle1 = Pi - A;
                angle = B - A;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if ((type2 == 4) && (p2.x < p1.x))
            {
                //>270
                angle1 = Pi - A;
                angle = B - A + 2 * Pi;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 4) && (p2.x == p1.x))
            {
                //
                angle1 = Pi-A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if (type2 == 1)
            {
                angle1 = Pi - A;
                angle = Pi - B - A;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(up.y) ? abs(maxy) : abs(up.y);
            }
            if (type2 == 2)
            {
                angle1 = Pi - A;
                angle = Pi + B - A;
                maxx = abs(p1.x) > abs(right.x) ? abs(p1.x) : abs(right.x);
                maxy = abs(up.y) > abs(p2.y) ? abs(up.y) : abs(p2.y);
            }
            if (type2 == 3)
            {
                angle1 = Pi - A;
                angle = 2 * Pi - B - A;
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(right.x) ? abs(maxx) : abs(right.x);
            }
            break;
        }
        default:break;
        }
    }
    l = angle * Ra;
    count = ratio * l;
    if (count < 15) { count = 15;}
    if (count > 20) { count = 20;}
    if (type3  == 1)
    {
        //xy
        p3.x = start_point.x ;
        p3.y = start_point.y ;
        p3.z = start_point.z ;
        p4.z = start_point.z ;

        for (int i = 0;i < count+1;i++)
        {
            p4.x = center_point.x + Ra * cos(angle1 - (angle * i)/count);
            p4.y = center_point.y + Ra * sin(angle1 - (angle * i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.x=center_point.x+Ra*cos(angle1-((angle)*i)/30);
            p4.y=center_point.y+Ra*sin(angle1-((angle)*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        x_max = abs(x_max) > abs(maxx) ? abs(x_max) : abs(maxx);
        y_max = abs(y_max) > abs(maxy) ? abs(y_max) : abs(maxy);
    }
    if (type3 == 2 )
    {
        //zx
        p3.x = start_point.x ;
        p3.y = start_point.y ;
        p3.z = start_point.z ;
        p4.y = start_point.y ;
        for (int i = 0;i < count+1;i++)
        {
            p4.z = center_point.z + Ra * cos(angle1 - (angle * i)/count);
            p4.x = center_point.x + Ra * sin(angle1 - (angle * i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.z=center_point.z+Ra*cos(angle1-((angle)*i)/30);
            p4.x=center_point.x+Ra*sin(angle1-((angle)*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        z_max = abs(z_max) > abs(maxx) ? abs(z_max) : abs(maxx);
        x_max = abs(x_max) > abs(maxy) ? abs(x_max) : abs(maxy);
    }
    if (type3 == 3)
    {
        //yz
        p3.x = start_point.x ;
        p3.y = start_point.y ;
        p3.z = start_point.z ;
        p4.x = start_point.x ;
        for (int i = 0;i < count+1;i++)
        {
            p4.y = center_point.y + Ra * cos(angle1 - (angle * i)/count);
            p4.z = center_point.z + Ra * sin(angle1 - (angle * i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++){
            p4.y=center_point.y+Ra*cos(angle1-((angle)*i)/30);
            p4.z=center_point.z+Ra*sin(angle1-((angle)*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        y_max = abs(y_max) > abs(maxx) ? abs(y_max) : abs(maxx);
        z_max = abs(z_max) > abs(maxy) ? abs(z_max) : abs(maxy);
    }
}

void Analyzegcode::IJK_ncircle(int type)
{
    //逆时针
    Point p1,p2;//起点。终点
    Point p0;//圆心
    int count = 0;
    double l;
    Point p3,p4;//画图的起点。终点
    double maxx,maxy;
    Point right,left,up,down;
    int type1,type2;
    double angle1 ,angle;
    double A,B;
    if (type == 1)
    {
        //xy
        p1.x = start_point.x;
        p1.y = start_point.y;
        p2.x = end_point.x;
        p2.y = end_point.y;
        p0.x = center_point.x;
        p0.y = center_point.y;
        right.x = center_point.x + Ra;
        right.y = center_point.y;
        left.x = center_point.x - Ra;
        left.y = center_point.y;
        up.y = center_point.y + Ra;
        up.x = center_point.x;
        down.y = center_point.y - Ra;
        down.x = center_point.x;

    }
    if (type == 2)
    {
        //zx
        p1.x = start_point.z;
        p1.y = start_point.x;
        p2.x = end_point.z;
        p2.y = end_point.x;
        p0.x = center_point.z;
        p0.y = center_point.x;
        right.x=center_point.z+Ra;
        right.y=center_point.x;
        left.x=center_point.z-Ra;
        left.y=center_point.y;
        up.y=center_point.x+Ra;
        up.x=center_point.z;
        down.y=center_point.x-Ra;
        down.x=center_point.z;
    }
    if (type == 3)
    {
        //yz
        p1.x = start_point.y;
        p1.y = start_point.z;
        p2.x = end_point.y;
        p2.y = end_point.z;
        p0.x = center_point.y;
        p0.y = center_point.z;
        right.x=center_point.y+Ra;
        right.y=center_point.z;
        left.x=center_point.y-Ra;
        left.y=center_point.z;
        up.y=center_point.z+Ra;
        up.x=center_point.y;
        down.y=center_point.z-Ra;
        down.x=center_point.y;
    }

    //右半圆
    if (p1.x > p0.x)
    {
        //右上四分一圆
        if (p1.y > p0.y)
        {
            type1 = 1;
        }
        //右下四分一圆
        else
        {
            type1 = 4;
        }
    }
    //左半圆
    else
    {
        //左上四分一圆
        if (p1.y > p0.y)
        {
            type1 = 2;
        }
        //左下四分一圆
        else
        {
            type1 = 3;
        }
    }
    //右半圆
    if (p2.x > p0.x)
    {
        //右上四分一圆
        if (p2.y > p0.y)
        {
            type2 = 1;
        }
        //右下四分一圆
        else
        {
            type2 = 4;
        }
    }
    //左半圆
    else
    {
        //左上四分一圆
        if (p2.y > p0.y)
        {
            type2 = 2;
        }
        //左下四分一圆
        else
        {
            type2 = 3;
        }
    }
    if ((p1.x==right.x)||(p1.x==left.x))
    {
        A=0;
    }
    else
    {
        A = acos(abs(p1.x  - p0.x )/Ra);
    }
    if( (int)(abs(p2.x  - p0.x )/Ra)!=1 )
    {
        B = acos( abs(p2.x  - p0.x )/Ra);
    }
    else
    {
        B=0;
    }
    //整圆
    if ((p1.x == p2.x)&&(p1.y == p2.y))
    {
        angle = 2 * Pi;
        if (type1==1) {angle1 = A;}
        if (type1==2) {angle1 = Pi - A;}
        if (type1==3) {angle1 = Pi + A;}
        if (type1==4) {angle1 = -A;}
        maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
        maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
    }
    //非整圆
    else
    {
        switch (type1)
        {
        case 1:
        {
            if ((type2 == 1) && (p2.x < p1.x))
            {
                //<90
                angle1 =  A;
                angle = B - A;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if ((type2 == 1) && (p2.x > p1.x))
            {
                //>270
                angle1 = A;
                angle = 2 * Pi - A + B;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 1) && (p2.x == p1.x))
            {
                angle1 = A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }

            if (type2 == 2)
            {
                angle1 = A;
                angle = Pi - A - B;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(up.y) ? abs(maxy) : abs(up.y);
            }
            if (type2 == 3)
            {
                angle1 = A;
                angle = B + Pi - A;
                maxx = abs(p1.x) > abs(left.x) ? abs(p1.x) : abs(left.x);
                maxy = abs(p2.y) > abs(up.y) ? abs(p2.y) : abs(up.y);
            }
            if (type2 == 4)
            {
                angle1 = A;
                angle = -A - B + 2 * Pi;
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
                maxx = abs(p1.x) > abs(p2.x)?  abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(left.x) ? abs(maxx) : abs(left.x);
            }
            break;
        }
        case 2:
        {
            if ((type2 == 2) && (p2.x > p1.x))
            {
                //>270
                angle1 = Pi - A;
                angle = A + 2 * Pi - B;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 2) && (p2.x < p1.x))
            {
                //<90
                angle1 = Pi - A;
                angle = A - B;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if ((type2 == 2) && (p2.x == p1.x))
            {
                //>270
                angle1 = Pi-A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if (type2 == 3)
            {
                angle1 = Pi - A;
                angle = A + B;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(left.x) ? abs(maxx) : abs(left.x);
            }
            if (type2 == 4)
            {
                angle1 = Pi - A;
                angle = A + Pi - B;
                maxx = abs(p2.x) > abs(left.x) ? abs(p2.x) : abs(left.x);
                maxy = abs(p1.y) > abs(down.y) ? abs(p1.y) : abs(down.y);
            }
            if (type2 == 1)
            {
                angle1 = Pi - A;
                angle =  B + Pi + A;
                maxx = abs(left.x) > abs(right.x) ? abs(left.x) : abs(right.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(down.y) ? abs(maxy) : abs(down.y);
            }
            break;
        }
        case 3:
        {
            if ((type2 == 3) && (p2.x < p1.x))
            {
                //>270
                angle1 = Pi + A;
                angle = -A + 2 * Pi + B;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 3) && (p2.x > p1.x))
            {
                //<90
                angle1 = Pi + A;
                angle = B - A;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if ((type2 == 3) && (p2.x == p1.x))
            {
                angle1 = Pi+A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if (type2 == 4)
            {
                angle1 = Pi + A;
                angle = Pi - A - B;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(down.y) ? abs(maxy) : abs(down.y);
            }
            if (type2 == 1)
            {
                angle1 = Pi + A;
                angle = -A + Pi + B;
                maxx = abs(right.x) > abs(p1.x) ? abs(right.x): abs(p1.x);
                maxy = abs(p2.y) > abs(down.y) ? abs(p2.y) : abs(down.y);

            }
            if (type2 == 2)
            {
                angle1 = Pi + A;
                angle = -B + 2 * Pi - A;
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(right.x) ? abs(maxx) : abs(right.x);
            }
            break;
        }
        case 4:
        {
            if ((type2 == 4) && (p2.x > p1.x))
            {
                //<90
                angle1 =  - A;
                angle = A - B;
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if ((type2 == 4) && (p2.x < p1.x))
            {
                //>270
                angle1 =  - A;
                angle = A - B + 2 * Pi;
                maxx = abs(right.x) > abs(left.x) ? abs(right.x) : abs(left.x);
                maxy = abs(up.y) > abs(down.y) ? abs(up.y) : abs(down.y);
            }
            if ((type2 == 4) && (p2.x == p1.x))
            {
                angle1 = -A;
                angle =0;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
            }
            if (type2 == 1)
            {
                angle1 =  - A;
                angle = A + B;
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxx = abs(p1.x) > abs(p2.x) ? abs(p1.x) : abs(p2.x);
                maxx = abs(maxx) > abs(right.x) ? abs(maxx) : abs(right.x);
            }
            if (type2 == 2)
            {
                angle1 =  - A;
                angle = Pi + A - B;
                maxx = abs(p2.x) > abs(right.x) ?abs(p2.x):abs(right.x);
                maxy = abs(p1.y) > abs(up.y) ? abs(p1.y):abs(up.y);
            }
            if (type2==3)
            {
                angle1 =  - A;
                angle = Pi + B + A;
                maxx = abs(left.x) > abs(right.x) ? abs(left.x): abs(right.x);
                maxy = abs(p1.y) > abs(p2.y) ? abs(p1.y) : abs(p2.y);
                maxy = abs(maxy) > abs(up.y) ? abs(maxy) : abs(up.y);
            }
            break;
        }
        default:
            break;
        }
    }
    l = angle * Ra;
    count = ratio * l;
    if (count < 15) { count = 15;}
    if (count > 20) { count = 20;}
    if (type == 1)
    {
        //xy
        p3.x = start_point.x ;
        p3.y = start_point.y ;
        p3.z = start_point.z ;
        p4.z = start_point.z ;
        for (int i = 0;i < count+1;i++)
        {
            p4.x = center_point.x + Ra * cos(angle1 + (angle * i)/count);
            p4.y = center_point.y + Ra * sin(angle1 + (angle * i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.x=center_point.x+Ra*cos(angle1+((angle)*i)/30);
            p4.y=center_point.y+Ra*sin(angle1+((angle)*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        x_max = abs(x_max) > abs(maxx) ? abs(x_max) : abs(maxx);
        y_max = abs(y_max) > abs(maxy) ? abs(y_max) : abs(maxy);
    }
    if (type == 2 )
    {
        //zx
        p3.x = start_point.x ;
        p3.y = start_point.y ;
        p3.z = start_point.z ;
        p4.y = start_point.y ;
        for (int i = 0;i < count+1;i++)
        {
            p4.z = center_point.z + Ra * cos(angle1 + (angle * i)/count);
            p4.x = center_point.x + Ra * sin(angle1 + (angle * i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.z=center_point.z+Ra*cos(angle1+((angle)*i)/30);
            p4.x=center_point.x+Ra*sin(angle1+((angle)*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        z_max = abs(z_max) > abs(maxx) ? abs(z_max) : abs(maxx);
        x_max = abs(x_max) > abs(maxy) ? abs(x_max) : abs(maxy);
    }
    if (type == 3)
    {
        //yz
        p3.x = start_point.x ;
        p3.y = start_point.y ;
        p3.z = start_point.z ;
        p4.x = start_point.x ;
        for (int i = 0;i < count+1;i++)
        {
            p4.y = center_point.y + Ra * cos(angle1 + (angle * i)/count);
            p4.z = center_point.z + Ra * sin(angle1 + (angle * i)/count);
            draw_Data.tool_pos_x.append(QString::number(p4.x));
            draw_Data.tool_pos_y.append(QString::number(p4.y));
            draw_Data.tool_pos_z.append(QString::number(p4.z));
            draw_Data.tool_drawColor_a.append(QString::number(1));
            draw_Data.tool_drawColor_b.append(QString::number(1));
            draw_Data.tool_drawColor_c.append(QString::number(0));
            draw_Data.tool_current_line.append(current_drawLine);
        }
        for(int i=0;i<31;i++)
        {
            p4.y=center_point.y+Ra*cos(angle1+((angle)*i)/30);
            p4.z=center_point.z+Ra*sin(angle1+((angle)*i)/30);
            draw_Data.path_pos_x.append(QString::number(p4.x));
            draw_Data.path_pos_y.append(QString::number(p4.y));
            draw_Data.path_pos_z.append(QString::number(p4.z));
            draw_Data.path_drawColor_a.append(QString::number(0));
            draw_Data.path_drawColor_b.append(QString::number(0));
            draw_Data.path_drawColor_c.append(QString::number(1));
            draw_Data.path_current_line.append(current_drawLine);
        }
        y_max = abs(y_max) > abs(maxx) ? abs(y_max) : abs(maxx);
        z_max = abs(z_max) > abs(maxy) ? abs(z_max) : abs(maxy);
    }
}

double Analyzegcode::calculat_x(double x0,double y0,double y,int k)
{
    double x;
    x=x0+k*sqrt(Ra*Ra-(y-y0)*(y-y0));
    return x;
}
double Analyzegcode::calculat_y(double x0, double y0, double x, int k)
{
    double y;
    y=y0+k*sqrt(Ra*Ra-(x-x0)*(x-x0));
    return y;
}

//4个参数
double Analyzegcode:: Y_Coordinates(double x,double y,double k,double x0)
{
     return k * x0 - k * x + y;
}

void Analyzegcode::Circle_Center(double x1, double y1, double x2, double y2, double dRadius )
{
    double k = 0.0;
    double k_verticle = 0.0;
    double mid_x = 0.0;
    double mid_y = 0.0;
    double a = 1.0;
    double b = 1.0;
    double c = 1.0;
    k = (y2 - y1) / (x2 - x1);
    if(k == 0)
    {
        center1.x = (x1 + x2) / 2.0;
        center2.x = (x1 + x2) / 2.0;
        center1.y = y1 + sqrt(dRadius * dRadius -(x1 - x2) * (x1 - x2) / 4.0);
        center2.y = y2 - sqrt(dRadius * dRadius -(x1 - x2) * (x1 - x2) / 4.0);
    }
    else
    {
        k_verticle = -1.0 / k;
        mid_x = (x1 + x2) / 2.0;
        mid_y = (y1+y2) / 2.0;
        a = 1.0 + k_verticle * k_verticle;
        b = -2 * mid_x - k_verticle * k_verticle * (x1 + x2);
        c = mid_x * mid_x + k_verticle * k_verticle * (x1 + x2) * (x1 + x2) / 4.0 -
            (dRadius * dRadius - ((mid_x - x1) * (mid_x -x1) + (mid_y - y1) * (mid_y - y1)));

        center1.x = (-1.0 * b + sqrt(b * b -4 * a * c)) / (2 * a);
        center2.x = (-1.0 * b - sqrt(b * b -4 * a * c)) / (2 * a);
        center1.y = Y_Coordinates(mid_x,mid_y,k_verticle,center1.x);
        center2.y = Y_Coordinates(mid_x,mid_y,k_verticle,center2.x);
    }
}

double Analyzegcode::calculat_angle(double r,double length)
{
    double angle;
    angle=acos(1-(length*length)/(2*r*r));
    return angle;
}

double Analyzegcode::calculat_linelength(double x1,double y1,double x2,double y2)
{
    double length;
    length=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)) ;
    return length;
}
