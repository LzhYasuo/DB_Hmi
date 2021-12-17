#include "DB_Hmi_Gui_3D.h"
#include <QHBoxLayout>
#include <2D3D/analyzegcode.h>
#include <2D3D/glwidget.h>
#include <2D3D/vscreen.h>

DB_Hmi_Gui_3D::DB_Hmi_Gui_3D(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

DB_Hmi_Gui_3D::~DB_Hmi_Gui_3D()
{

}

void DB_Hmi_Gui_3D::init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = init_Conotrol();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget* DB_Hmi_Gui_3D::init_Conotrol()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    GLWidget* glWidget = new GLWidget(this);
    glWidget->initXYZview();
    VScreen* _theVScreen = new VScreen(this);
    Analyzegcode* analyzegcode=new Analyzegcode(this) ;
    connect(glWidget,SIGNAL(start_sim( )),_theVScreen,SLOT(start_Sim()));
    connect(glWidget,SIGNAL(pause_sim( )),_theVScreen,SLOT(pause_Sim(  )));
    connect(glWidget,SIGNAL(drawvscreen( )),_theVScreen,SLOT(DrawVScreen(  )));
    connect(glWidget,SIGNAL(redraw()),_theVScreen,SLOT(Redraw(  )));
    connect(glWidget,SIGNAL(clearpath()),_theVScreen,SLOT(clear_path( )));
    connect(glWidget,SIGNAL(recover()),_theVScreen,SLOT(recover( )));
    connect(glWidget,SIGNAL(draw_xyzaxis()),_theVScreen,SLOT(DrawGriXYZaxis( )));
    connect(_theVScreen,SIGNAL(Update()),glWidget,SLOT(update()));
    connect(analyzegcode,SIGNAL(readend(bool )),glWidget,SLOT(readend(bool )));
    connect(glWidget ,SIGNAL(load_newfile()),glWidget,SLOT(RecoverGL()));
    connect(glWidget ,SIGNAL(load_newfile()),analyzegcode,SLOT(clear_drawData()));
    connect(glWidget ,SIGNAL(nowOpenedFileMsg(QString )),this,SLOT(getMsg(QString) ));
    connect(glWidget ,SIGNAL(load_newfile()),_theVScreen,SLOT(redrawset()));
    connect(glWidget,SIGNAL(gcode(QString,int )),analyzegcode,SLOT(get_gcode(QString,int )));
    connect(analyzegcode,SIGNAL(readend(bool )),_theVScreen,SLOT(readend(bool )));
    connect(analyzegcode,SIGNAL( draw_value(draw_data )),_theVScreen,SLOT(getvalue(draw_data )));

    mLayout->addWidget(glWidget);
    mWidget->setLayout(mLayout);

    return mWidget;
}
