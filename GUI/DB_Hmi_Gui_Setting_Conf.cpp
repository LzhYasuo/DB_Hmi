#include "DB_Hmi_Gui_Setting_Conf.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QStackedWidget>
#include <QLabel>
#include <QDebug>

#include "../Ini_Dbdata/Setting_Data.h"
#include "Public/Public_Control.h"
#include "Public/Public_Str.h"
#include "../Model/SettingTwoValTableView.h"
#include "../Model/SettingFourValTableView.h"
#include "../Model/SettingThreeValTableView.h"
#include "../Model/SettingOneValTableView.h"

#include "../Socket/RunTcp.h"

DB_Hmi_Gui_Setting_Conf::DB_Hmi_Gui_Setting_Conf(QWidget* parent)
    :QWidget (parent)
{
    this->init();
}

DB_Hmi_Gui_Setting_Conf::~DB_Hmi_Gui_Setting_Conf()
{

}

void DB_Hmi_Gui_Setting_Conf::init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = InitWidget();
    mLayout->addWidget(mWidget);

    this->setLayout(mLayout);
}

QWidget* DB_Hmi_Gui_Setting_Conf::InitWidget()
{
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(10,10,10,10);

    QWidget* TopWidget = new QWidget();
    TopWidget->setFixedHeight(30);
    QHBoxLayout* TopLayout = new QHBoxLayout();
    TopLayout->setSpacing(0);
    TopLayout->setContentsMargins(0,0,0,0);

    QPushButton* btn_HmiSet = Public_Control::Get_Button("Hmi设置","",100,30);
    TopLayout->addWidget(btn_HmiSet);
    TopLayout->addStretch();
    TopWidget->setLayout(TopLayout);

    QWidget* MidWidget = new QWidget();
    MidWidget->setObjectName("MidWidget");
    MidWidget->setStyleSheet("#MidWidget{border:2px solid rgb(150,150,150);}");
    QVBoxLayout* MidLayout = new QVBoxLayout();
    MidLayout->setSpacing(0);
    MidLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout* MidTopLayout = new QHBoxLayout();
    MidTopLayout->setSpacing(0);
    MidTopLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_MainSet = Public_Control::Get_Button("主界面配置","",100,30);
    QPushButton* btn_ManualSet = Public_Control::Get_Button("手动界面配置","",100,30);
    QPushButton* btn_AutoSet = Public_Control::Get_Button("自动界面配置","",100,30);
    QPushButton* btn_DataSet = Public_Control::Get_Button("工艺库界面配置","",100,30);
    QPushButton* btn_PLCMo1 = Public_Control::Get_Button("PLC监控1-4","",100,30);
    QPushButton* btn_PLcMo2 = Public_Control::Get_Button("PLC监控5-8","",100,30);
    MidTopLayout->addWidget(btn_MainSet);
    MidTopLayout->addWidget(btn_ManualSet);
    MidTopLayout->addWidget(btn_AutoSet);
    MidTopLayout->addWidget(btn_DataSet);
    MidTopLayout->addWidget(btn_PLCMo1);
    MidTopLayout->addWidget(btn_PLcMo2);
    MidTopLayout->addStretch();

    QStackedWidget* mSWidget = new QStackedWidget();
    mSWidget->setObjectName("mSWidget");
    mSWidget->setStyleSheet("#mSWidget{border:2px solid rgb(150,150,150);}");
    QWidget* Main = Create_Setting_Conf_Switch_Page(MainPage);
    QWidget* Manual = Create_Setting_Conf_Switch_Page(ManualPage);
    QWidget* Auto = Create_Setting_Conf_Switch_Page(AutoPage);
    QWidget* Data = Create_Setting_Conf_Switch_Page(DataPage);
    QWidget* PLCMo1 = Create_Setting_Conf_Switch_Page(PLCMo1Page);
    QWidget* PLCMo2 = Create_Setting_Conf_Switch_Page(PLCMO2Page);


    mSWidget->addWidget(Main);
    mSWidget->addWidget(Manual);
    mSWidget->addWidget(Auto);
    mSWidget->addWidget(Data);
    mSWidget->addWidget(PLCMo1);
    mSWidget->addWidget(PLCMo2);

    MidLayout->addLayout(MidTopLayout);
    MidLayout->addWidget(mSWidget);
    MidWidget->setLayout(MidLayout);

    QWidget* BottomWidget = new QWidget();
    QHBoxLayout* BottomLayout = new QHBoxLayout();
    BottomLayout->setSpacing(0);
    BottomLayout->setContentsMargins(0,0,0,0);

    QPushButton* btn_Restore = Public_Control::Get_Button("恢复默认","",100,30);

    QPushButton* btn_Save = Public_Control::Get_Button("保存","",100,30);

    QPushButton* btn_Quit = Public_Control::Get_Button("退出","",100,30);

    BottomLayout->addStretch();
    BottomLayout->addWidget(btn_Restore);
    BottomLayout->addWidget(btn_Save);
    BottomLayout->addWidget(btn_Quit);
    BottomWidget->setLayout(BottomLayout);

    mLayout->addWidget(TopWidget);
    mLayout->addWidget(MidWidget);
    mLayout->addWidget(BottomWidget);
    mWidget->setLayout(mLayout);

    this->connect(btn_MainSet,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(0);
    });
    this->connect(btn_ManualSet,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(1);
    });
    this->connect(btn_AutoSet,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(2);
    });
    this->connect(btn_DataSet,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(3);
    });
    this->connect(btn_PLCMo1,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(4);
    });
    this->connect(btn_PLcMo2,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(5);
    });

    this->connect(btn_Restore,&QPushButton::clicked,this,[=](){
        Setting_Data::Get()->RestoreList();
    });
    this->connect(btn_Save,&QPushButton::clicked,this,[=](){
        Setting_Data::Get()->Write_Val_For_Ini();
    });
    this->connect(btn_Quit,&QPushButton::clicked,this,[=](){
          Setting_Data::Get()->PopBackMofityList();
          this->deleteLater();
    });

    return mWidget;
}


QWidget* DB_Hmi_Gui_Setting_Conf::Create_Setting_Conf_Switch_Page(SystemConfSwitchPage type)
{
    QWidget* Widget = nullptr;
    switch(type)
    {
    case MainPage:
    {
        QStringList Viewmsg;
        Viewmsg << "" << "中文名称" << "英文名称" << "PLC输出";

        QStringList Viewmsg2;
        Viewmsg2 << "" << "中文名称" << "英文名称" << "PLC输入" << "PLC输出";

        QStringList Viewmsg3;
        Viewmsg3 << "" << "路径";

        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(5);
        mLayout->setContentsMargins(10,10,10,10);

        //--------------------------------------------------------------左边部分
        QWidget* LeftWidget = new QWidget();
        QVBoxLayout* LeftLayout = new QVBoxLayout();
        LeftLayout->setSpacing(5);
        LeftLayout->setContentsMargins(0,0,0,0);

        QGroupBox* Box1 = new QGroupBox();
        Box1->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QVBoxLayout* BoxLayout1 = new QVBoxLayout();
        BoxLayout1->setSpacing(0);
        BoxLayout1->setContentsMargins(0,0,0,0);
        for(int i = 0; i < 3; i++)
        {
            QHBoxLayout* LabelComboxLayout = new QHBoxLayout();
            LabelComboxLayout->setSpacing(0);
            LabelComboxLayout->setContentsMargins(0,0,0,0);
            QLabel* lblName = Public_Control::Get_Label("对");
            QComboBox* CoBox = new QComboBox();
            LabelComboxLayout->addWidget(lblName);
            LabelComboxLayout->addWidget(CoBox);
            BoxLayout1->addLayout(LabelComboxLayout);
        }
        Box1->setLayout(BoxLayout1);

        //左边的第一个列表
        QGroupBox* ViewBox1 = new QGroupBox();
        ViewBox1->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout1 = new QHBoxLayout();
        ViewBoxLayout1->setSpacing(0);
        ViewBoxLayout1->setContentsMargins(10,10,10,10);
        SettingThreeValTableView* View = new SettingThreeValTableView(Viewmsg,8,70,180,87,90);
        View->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(MainViewType,MainView1));
        ViewBoxLayout1->addWidget(View);
        ViewBox1->setLayout(ViewBoxLayout1);

        LeftLayout->addWidget(Box1);
        LeftLayout->addWidget(ViewBox1);
        LeftWidget->setLayout(LeftLayout);
        //--------------------------------------------------------------左边结束

        //--------------------------------------------------------------中间部分
        QWidget* MidWidget = new QWidget();
        QVBoxLayout* MidLayout = new QVBoxLayout();
        MidLayout->setSpacing(5);
        MidLayout->setContentsMargins(0,0,0,0);

        //中间上面的列表
        QGroupBox* ViewBox2 = new QGroupBox();
        ViewBox2->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout2 = new QHBoxLayout();
        ViewBoxLayout2->setSpacing(0);
        ViewBoxLayout2->setContentsMargins(10,10,10,10);
        SettingThreeValTableView* View2 = new SettingThreeValTableView(Viewmsg,6,70,180,58,60);
        View2->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(MainViewType,MainView2));
        ViewBoxLayout2->addWidget(View2);
        ViewBox2->setLayout(ViewBoxLayout2);

        //中间下面的列表
        QGroupBox* ViewBox3 = new QGroupBox();
        ViewBox3->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout3 = new QHBoxLayout();
        ViewBoxLayout3->setSpacing(0);
        ViewBoxLayout3->setContentsMargins(10,10,10,10);
        SettingThreeValTableView* View3 = new SettingThreeValTableView(Viewmsg,3,70,180,105,95);
        View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(MainViewType,MainView3));
        ViewBoxLayout3->addWidget(View3);
        ViewBox3->setLayout(ViewBoxLayout3);
        MidLayout->addWidget(ViewBox2);
        MidLayout->addWidget(ViewBox3);
        MidWidget->setLayout(MidLayout);
        //--------------------------------------------------------------中间部分结束

        //--------------------------------------------------------------右边部分
        QWidget* RightWidget = new QWidget();
        QVBoxLayout* RightLayout = new QVBoxLayout();
        RightLayout->setSpacing(5);
        RightLayout->setContentsMargins(0,0,0,0);

        //右边最上面的
        QGroupBox* ViewBox4 = new QGroupBox();
        ViewBox4->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout4 = new QHBoxLayout();
        ViewBoxLayout4->setSpacing(0);
        ViewBoxLayout4->setContentsMargins(10,10,10,10);
        SettingFourValTableView* View4 = new SettingFourValTableView(Viewmsg2,4,70,135,66,75);
        View4->Set_Model_Data(Setting_Data::Get()->GET_FourData(MainViewType,MainView4));
        ViewBoxLayout4->addWidget(View4);
        ViewBox4->setLayout(ViewBoxLayout4);

        //右边中间的
        QGroupBox* ViewBox5 = new QGroupBox();
        ViewBox5->setFixedHeight(140);
        ViewBox5->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout5 = new QHBoxLayout();
        ViewBoxLayout5->setSpacing(0);
        ViewBoxLayout5->setContentsMargins(10,10,10,10);
        SettingOneValTableView* View5 = new SettingOneValTableView(Viewmsg3,1,70,535,60,60);
        View5->Set_Model_Data(Setting_Data::Get()->GET_OneData(MainViewType,MainView5));
        ViewBoxLayout5->addWidget(View5);
        ViewBox5->setLayout(ViewBoxLayout5);

        //右边最下面的
        QGroupBox* ViewBox6 = new QGroupBox();
        ViewBox6->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout6 = new QHBoxLayout();
        ViewBoxLayout6->setSpacing(0);
        ViewBoxLayout6->setContentsMargins(10,10,10,10);
        SettingOneValTableView* View6 = new SettingOneValTableView(Viewmsg3,4,70,535,68,65);
        View6->Set_Model_Data(Setting_Data::Get()->GET_OneData(MainViewType,MainView6));
        ViewBoxLayout6->addWidget(View6);
        ViewBox6->setLayout(ViewBoxLayout6);

        RightLayout->addWidget(ViewBox4);
        RightLayout->addWidget(ViewBox5);
        RightLayout->addWidget(ViewBox6);
        RightWidget->setLayout(RightLayout);
        //--------------------------------------------------------------中间部分结束

        mLayout->addWidget(LeftWidget);
        mLayout->addWidget(MidWidget);
        mLayout->addWidget(RightWidget);
        mWidget->setLayout(mLayout);

        Widget = mWidget;

        this->connect(View,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_MainListData(MainView1,row,col,value);
        });
        this->connect(View2,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_MainListData(MainView2,row,col,value);
        });
        this->connect(View3,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_MainListData(MainView3,row,col,value);
        });
        this->connect(View4,&SettingFourValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_MainListData(MainView4,row,col,value);
        });
        this->connect(View5,&SettingOneValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_MainListData(MainView5,row,col,value);
        });
        this->connect(View6,&SettingOneValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_MainListData(MainView6,row,col,value);
        });

        this->connect(Setting_Data::Get(),&Setting_Data::InitTable,this,[=](){
            View->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(MainViewType,MainView1));
            View2->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(MainViewType,MainView2));
            View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(MainViewType,MainView3));
            View4->Set_Model_Data(Setting_Data::Get()->GET_FourData(MainViewType,MainView4));
            View5->Set_Model_Data(Setting_Data::Get()->GET_OneData(MainViewType,MainView5));
            View6->Set_Model_Data(Setting_Data::Get()->GET_OneData(MainViewType,MainView6));
        });

        break;
    }
    case ManualPage:
    {
        QStringList msg;
        msg << " " << "中文名称" << "英文名称" << "PLC输入" << "PLC输出";

        QStringList viewmsg2;
        viewmsg2 << "" << "PLC输入" << "PLC输出";

        QStringList viewmsg3;
        viewmsg3 << "" << "中文名称" << "英文名称" << "PLC输入";

        QStringList viewmsg4;
        viewmsg4 << "" << "PLC输出";

        QStringList viewmsg5;
        viewmsg5 << "" << "中文名称" << "英文名称" << "PLC输入";

        QWidget* mWidget = new QWidget();
        QVBoxLayout* mLayout = new QVBoxLayout();
        mLayout->setSpacing(0);
        mLayout->setContentsMargins(0,0,0,0);

        //--------------------------------------------------------------头部部分结束
        QGroupBox* FunBox = new QGroupBox();
        FunBox->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* FunBoxLayout = new QHBoxLayout();
        FunBoxLayout->setSpacing(0);
        FunBoxLayout->setContentsMargins(10,10,10,10);
        SettingFourValTableView* View1 = new SettingFourValTableView(msg,8,70,460,48,40);
        View1->Set_Model_Data(Setting_Data::Get()->GET_FourData(ManualViewType,MainNothing,ManualView1));
        FunBoxLayout->addWidget(View1);
        FunBox->setLayout(FunBoxLayout);
        //--------------------------------------------------------------头部部分结束

        //--------------------------------------------------------------底部部分
        QHBoxLayout* BottomLayout = new QHBoxLayout();
        BottomLayout->setSpacing(5);
        BottomLayout->setContentsMargins(0,0,0,0);

        //底部左
        QWidget* BottomLeftWidget = new QWidget();
        QVBoxLayout* BottomLeftLayout = new QVBoxLayout();
        BottomLeftLayout->setSpacing(0);
        BottomLeftLayout->setContentsMargins(0,0,0,0);

        QGroupBox* ViewBox2 = new QGroupBox();
        ViewBox2->setFixedHeight(120);
        ViewBox2->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout2 = new QHBoxLayout();
        ViewBoxLayout2->setSpacing(0);
        ViewBoxLayout2->setContentsMargins(10,10,10,10);
        SettingTwoValTableView* View2 = new SettingTwoValTableView(viewmsg2,1,70,440,50,50);
        View2->Set_Model_Data(Setting_Data::Get()->GET_TwoData(ManualViewType,MainNothing,ManualView2));
        ViewBoxLayout2->addWidget(View2);
        ViewBox2->setLayout(ViewBoxLayout2);

        QGroupBox* ViewBox3 = new QGroupBox();
        ViewBox3->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout3 = new QHBoxLayout();
        ViewBoxLayout3->setSpacing(0);
        ViewBoxLayout3->setContentsMargins(10,10,10,10);
        SettingThreeValTableView* View3 = new SettingThreeValTableView(viewmsg3,4,70,295,61,60);
        View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(ManualViewType,MainNothing,ManualView3));
        ViewBoxLayout3->addWidget(View3);
        ViewBox3->setLayout(ViewBoxLayout3);

        BottomLeftLayout->addWidget(ViewBox2);
        BottomLeftLayout->addWidget(ViewBox3);
        BottomLeftWidget->setLayout(BottomLeftLayout);

        //底部右
        QWidget* BottomRightWidget = new QWidget();
        QVBoxLayout* BottomRightLayout = new QVBoxLayout();
        BottomRightLayout->setSpacing(0);
        BottomRightLayout->setContentsMargins(0,0,0,0);

        QGroupBox* ViewBox4 = new QGroupBox();
        ViewBox4->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout4 = new QHBoxLayout();
        ViewBoxLayout4->setSpacing(0);
        ViewBoxLayout4->setContentsMargins(10,10,10,10);
        SettingOneValTableView* View4 = new SettingOneValTableView(viewmsg3,2,70,880,63,70);
        View4->Set_Model_Data(Setting_Data::Get()->GET_OneData(ManualViewType,MainNothing,ManualView4));
        ViewBoxLayout4->addWidget(View4);
        ViewBox4->setLayout(ViewBoxLayout4);

        QGroupBox* ViewBox5 = new QGroupBox();
        ViewBox5->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* ViewBoxLayout5 = new QHBoxLayout();
        ViewBoxLayout5->setSpacing(0);
        ViewBoxLayout5->setContentsMargins(10,10,10,10);
        SettingThreeValTableView* View5 = new SettingThreeValTableView(viewmsg5,2,70,300,63,70);
        View5->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(ManualViewType,MainNothing,ManualView5));
        ViewBoxLayout5->addWidget(View5);
        ViewBox5->setLayout(ViewBoxLayout5);

        BottomRightLayout->addWidget(ViewBox4);
        BottomRightLayout->addWidget(ViewBox5);
        BottomRightWidget->setLayout(BottomRightLayout);
        BottomLayout->addWidget(BottomLeftWidget);
        BottomLayout->addWidget(BottomRightWidget);
        //--------------------------------------------------------------底部部分结束

        mLayout->addWidget(FunBox);
        mLayout->addLayout(BottomLayout);
        mWidget->setLayout(mLayout);

        Widget = mWidget;

        this->connect(View1,&SettingFourValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_ManualListData(ManualView1,row,col,value);
        });
        this->connect(View2,&SettingTwoValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_ManualListData(ManualView2,row,col,value);
        });
        this->connect(View3,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_ManualListData(ManualView3,row,col,value);
        });
        this->connect(View4,&SettingOneValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_ManualListData(ManualView4,row,col,value);
        });
        this->connect(View5,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_ManualListData(ManualView5,row,col,value);
        });

        this->connect(Setting_Data::Get(),&Setting_Data::InitTable,this,[=](){
            View1->Set_Model_Data(Setting_Data::Get()->GET_FourData(ManualViewType,MainNothing,ManualView1));
            View2->Set_Model_Data(Setting_Data::Get()->GET_TwoData(ManualViewType,MainNothing,ManualView2));
            View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(ManualViewType,MainNothing,ManualView3));
            View4->Set_Model_Data(Setting_Data::Get()->GET_OneData(ManualViewType,MainNothing,ManualView4));
            View5->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(ManualViewType,MainNothing,ManualView5));
        });

        break;
    }
    case AutoPage:
    {
        QStringList msg;
        msg << " " << "中文名称" << "英文名称" << "PLC输入" << "PLC输出";
        QWidget* mWidget = new QWidget();
        QVBoxLayout* mLayout = new QVBoxLayout();
        mLayout->setSpacing(10);
        mLayout->setContentsMargins(5,5,5,5);

        //--------------------------------------------------------------顶部部分
        QGroupBox* TopBox = new QGroupBox();
        TopBox->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* TopBoxLayout = new QHBoxLayout();
        TopBoxLayout->setSpacing(0);
        TopBoxLayout->setContentsMargins(10,10,10,10);

        SettingFourValTableView* View1 = new SettingFourValTableView(msg,8,70,460,47,40);
        View1->Set_Model_Data(Setting_Data::Get()->GET_FourData(AutoViewType,MainNothing,ManualNothing,AutoView1));
        TopBoxLayout->addWidget(View1);
        TopBox->setLayout(TopBoxLayout);
        //--------------------------------------------------------------顶部部分结束

        //--------------------------------------------------------------底部部分
        QGroupBox* BottomBox = new QGroupBox();
        BottomBox->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* BottomBoxLayout = new QHBoxLayout();
        BottomBoxLayout->setSpacing(0);
        BottomBoxLayout->setContentsMargins(10,10,10,10);

        SettingFourValTableView* View2 = new SettingFourValTableView(msg,8,70,460,47,40);
        View2->Set_Model_Data(Setting_Data::Get()->GET_FourData(AutoViewType,MainNothing,ManualNothing,AutoView2));
        BottomBoxLayout->addWidget(View2);
        BottomBox->setLayout(BottomBoxLayout);
        //--------------------------------------------------------------底部部分结束

        mLayout->addWidget(TopBox);
        mLayout->addWidget(BottomBox);
        mWidget->setLayout(mLayout);
        Widget = mWidget;

        this->connect(View1,&SettingFourValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_AutotData(AutoView1,row,col,value);
        });
        this->connect(View2,&SettingFourValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_AutotData(AutoView2,row,col,value);
        });

        this->connect(Setting_Data::Get(),&Setting_Data::InitTable,this,[=](){
            View1->Set_Model_Data(Setting_Data::Get()->GET_FourData(AutoViewType,MainNothing,ManualNothing,AutoView1));
            View2->Set_Model_Data(Setting_Data::Get()->GET_FourData(AutoViewType,MainNothing,ManualNothing,AutoView2));
        });

        break;
    }
    case DataPage:
    {
        QStringList msg;
        msg << "" << "中文名称" << "英文名称";

        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(10);
        mLayout->setContentsMargins(5,5,5,5);

        //--------------------------------------------------------------左边部分
        QGroupBox* LeftBox = new QGroupBox();
        LeftBox->setFixedHeight(480);
        LeftBox->setTitle("工艺层名称设置");
        LeftBox->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* LeftBoxLayout = new QHBoxLayout();
        LeftBoxLayout->setSpacing(0);
        LeftBoxLayout->setContentsMargins(10,10,10,10);

        SettingTwoValTableView* View = new SettingTwoValTableView(msg,8,50,730,50,50);
        View->Set_Model_Data(Setting_Data::Get()->GET_TwoData(DataViewType,MainNothing,ManualNothing,AutoNothing,DataView));
        LeftBoxLayout->addWidget(View);
        LeftBox->setLayout(LeftBoxLayout);
        //--------------------------------------------------------------左边部分结束

        //--------------------------------------------------------------右边部分
        QGroupBox* RightBox = new QGroupBox();
        RightBox->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        RightBox->setFixedHeight(480);
        RightBox->setFixedWidth(350);
        RightBox->setTitle("工艺层名称设置");
        QHBoxLayout* RightBoxLayout = new QHBoxLayout();
        RightBoxLayout->setSpacing(0);
        RightBoxLayout->setContentsMargins(0,0,0,0);

        QList<bool> StateList = Setting_Data::Get()->Get_Data_Bool();
        QWidget* RightLeft = new QWidget();
        QVBoxLayout* RightLeftLayout = new QVBoxLayout();
        RightLeftLayout->setSpacing(0);
        RightLeftLayout->setContentsMargins(0,0,0,0);
        QCheckBox* RightLeftbox1 = new QCheckBox();
        RightLeftbox1->setText("蛙跳");
        RightLeftbox1->setChecked(StateList.at(0));
        QCheckBox* RightLeftbox2 = new QCheckBox();
        RightLeftbox2->setText("无蛙跳上抬高度");
        RightLeftbox2->setChecked(StateList.at(1));
        QCheckBox* RightLeftbox3 = new QCheckBox();
        RightLeftbox3->setText("定高切割");
        RightLeftbox3->setChecked(StateList.at(2));
        QCheckBox* RightLeftbox4 = new QCheckBox();
        RightLeftbox4->setText("寻边");
        RightLeftbox4->setChecked(StateList.at(3));
        RightLeftLayout->addWidget(RightLeftbox1,0,Qt::AlignHCenter);
        RightLeftLayout->addWidget(RightLeftbox2,0,Qt::AlignHCenter);
        RightLeftLayout->addWidget(RightLeftbox3,0,Qt::AlignHCenter);
        RightLeftLayout->addWidget(RightLeftbox4,0,Qt::AlignHCenter);
        RightLeft->setLayout(RightLeftLayout);

        QWidget* RightMid = new QWidget();
        RightMid->setStyleSheet("border-right:2px solid rgb(150,150,150);"
                                "border-left:2px solid rgb(150,150,150)");
        QVBoxLayout* RightMidLayout = new QVBoxLayout();
        RightMidLayout->setSpacing(0);
        RightMidLayout->setContentsMargins(0,0,0,0);
        QCheckBox* RightMidbox1 = new QCheckBox();
        RightMidbox1->setText("穿孔一");
        RightMidbox1->setChecked(StateList.at(4));
        QCheckBox* RightMidbox2 = new QCheckBox();
        RightMidbox2->setText("穿孔二");
        RightMidbox2->setChecked(StateList.at(5));
        QCheckBox* RightMidbox3 = new QCheckBox();
        RightMidbox3->setText("穿孔三");
        RightMidbox3->setChecked(StateList.at(6));
        QCheckBox* RightMidbox4 = new QCheckBox();
        RightMidbox4->setText("预穿孔选择");
        RightMidbox4->setChecked(StateList.at(7));
        RightMidLayout->addWidget(RightMidbox1,0,Qt::AlignHCenter);
        RightMidLayout->addWidget(RightMidbox2,0,Qt::AlignHCenter);
        RightMidLayout->addWidget(RightMidbox3,0,Qt::AlignHCenter);
        RightMidLayout->addWidget(RightMidbox4,0,Qt::AlignHCenter);
        RightMid->setLayout(RightMidLayout);

        QWidget* RightRight = new QWidget();
        QVBoxLayout* RightRightLayout = new QVBoxLayout();
        RightRightLayout->setSpacing(0);
        RightRightLayout->setContentsMargins(0,0,0,0);
        QCheckBox* RightRightbox1 = new QCheckBox();
        RightRightbox1->setText("送料设置");
        RightRightbox1->setChecked(StateList.at(8));
        QCheckBox* RightRightbox2 = new QCheckBox();
        RightRightbox2->setText("加工技术");
        RightRightbox2->setChecked(StateList.at(9));
        QCheckBox* RightRightbox3 = new QCheckBox();
        RightRightbox3->setText("倍率按钮");
        RightRightbox3->setChecked(StateList.at(10));
        RightRightLayout->addWidget(RightRightbox1,0,Qt::AlignHCenter);
        RightRightLayout->addWidget(RightRightbox2,0,Qt::AlignHCenter);
        RightRightLayout->addWidget(RightRightbox3,0,Qt::AlignHCenter);
        RightRight->setLayout(RightRightLayout);

        RightBoxLayout->addWidget(RightLeft);
        RightBoxLayout->addWidget(RightMid);
        RightBoxLayout->addWidget(RightRight);
        RightBox->setLayout(RightBoxLayout);

        mLayout->addWidget(LeftBox,0,Qt::AlignTop);
        mLayout->addWidget(RightBox,0,Qt::AlignTop);
        mWidget->setLayout(mLayout);

        this->connect(View,&SettingTwoValTableView::TableModityData,this,[=](int row,int col,QVariant value){
           Setting_Data::Get()->Set_DataData(DataView,row,col,value);
        });
        QList<QCheckBox*> BoxList = RightBox->findChildren<QCheckBox*>();
        for(int i = 0; i < BoxList.size(); i++)
        {
            this->connect(BoxList.at(i),&QCheckBox::stateChanged,this,[=](int state){
               Setting_Data::Get()->Set_DataData(DataFun,i,0,state);
            });
        }

        this->connect(Setting_Data::Get(),&Setting_Data::InitTable,this,[=](){
            View->Set_Model_Data(Setting_Data::Get()->GET_TwoData(DataViewType,MainNothing,ManualNothing,AutoNothing,DataView));
            QList<bool> StateList = Setting_Data::Get()->Get_Data_Bool();
            RightLeftbox1->setChecked(StateList.at(0));
            RightLeftbox2->setChecked(StateList.at(1));
            RightLeftbox3->setChecked(StateList.at(2));
            RightLeftbox4->setChecked(StateList.at(3));
            RightMidbox1->setChecked(StateList.at(4));
            RightMidbox2->setChecked(StateList.at(5));
            RightMidbox3->setChecked(StateList.at(6));
            RightMidbox4->setChecked(StateList.at(7));
            RightRightbox1->setChecked(StateList.at(8));
            RightRightbox2->setChecked(StateList.at(9));
            RightRightbox3->setChecked(StateList.at(10));
        });


        Widget = mWidget;
        break;
    }
    case PLCMo1Page:
    {
        QStringList msg;
        msg  << "" << "PLC地址" << "功能(中文)" << "功能(英文)";
        QWidget* mWidget = new QWidget();
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(10);
        mLayout->setContentsMargins(5,5,5,5);

        //左边
        QWidget* LeftWidget = new QWidget();
        QVBoxLayout* LeftLayout = new QVBoxLayout();
        LeftLayout->setSpacing(10);
        LeftLayout->setContentsMargins(0,0,0,0);

        //左上
        QWidget* ViewWidget1 = Create_PlcGroup(msg);
        SettingThreeValTableView* View = ViewWidget1->findChild<SettingThreeValTableView*>("View");
        View->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView1));
        QGroupBox* ViewBox = ViewWidget1->findChild<QGroupBox*>("ViewBox");
        ViewBox->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView1));
        ViewBox->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView1));

        //第二个列表
        QWidget* ViewWidget2 = Create_PlcGroup(msg);
        SettingThreeValTableView* View1 = ViewWidget2->findChild<SettingThreeValTableView*>("View");
        View1->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView2));
        QGroupBox* ViewBox1 = ViewWidget2->findChild<QGroupBox*>("ViewBox");
        ViewBox1->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView2));
        ViewBox1->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView2));

        LeftLayout->addWidget(ViewWidget1);
        LeftLayout->addWidget(ViewWidget2);
        LeftWidget->setLayout(LeftLayout);

        //右边
        QWidget* RightWidget = new QWidget();
        QVBoxLayout* RightLayout = new QVBoxLayout();
        RightLayout->setSpacing(10);
        RightLayout->setContentsMargins(0,0,0,0);

        //第三个列表
        QWidget* ViewWidget3 = Create_PlcGroup(msg);
        SettingThreeValTableView* View2 = ViewWidget3->findChild<SettingThreeValTableView*>("View");
        View2->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView3));
        QGroupBox* ViewBox2 = ViewWidget3->findChild<QGroupBox*>("ViewBox");
        ViewBox2->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView3));
        ViewBox2->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView3));

        //第四个列表
        QWidget* ViewWidget4 = Create_PlcGroup(msg);
        SettingThreeValTableView* View3 = ViewWidget4->findChild<SettingThreeValTableView*>("View");
        View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView4));
        QGroupBox* ViewBox3 = ViewWidget4->findChild<QGroupBox*>("ViewBox");
        ViewBox3->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView4));
        ViewBox3->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView4));

        RightLayout->addWidget(ViewWidget3);
        RightLayout->addWidget(ViewWidget4);
        RightWidget->setLayout(RightLayout);

        mLayout->addWidget(LeftWidget);
        mLayout->addWidget(RightWidget);
        mWidget->setLayout(mLayout);

        Widget = mWidget;

        this->connect(View,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView1,row,col,data);
        });
        this->connect(View1,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView2,row,col,data);
        });
        this->connect(View2,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView3,row,col,data);
        });
        this->connect(View3,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView4,row,col,data);
        });

        QList<QPushButton*> btnList = mWidget->findChildren<QPushButton*>();
        QList<QLineEdit*> EditList = mWidget->findChildren<QLineEdit*>();
        QList<QGroupBox*> GroupList = mWidget->findChildren<QGroupBox*>();

        GroupList.at(0)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView1));
        GroupList.at(0)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView1));
        GroupList.at(1)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView2));
        GroupList.at(1)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView2));
        GroupList.at(2)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView3));
        GroupList.at(2)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView3));
        GroupList.at(3)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView4));
        GroupList.at(3)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView4));

        for(int i = 0; i < 4; i++)
        {
            this->connect(btnList.at(i),&QPushButton::clicked,this,[=](){
                PlcMoType type;
                if(i == 0)
                    type = PlcMoView1;
                else if(i == 1)
                    type = PlcMoView2;
                else if(i == 2)
                    type = PlcMoView3;
                else if(i == 3)
                    type = PlcMoView4;
               if(EditList.at(i)->text().isEmpty())
                   return;
               Setting_Data::Get()->Set_Plc_Title(type,EditList.at(i)->text());
               GroupList.at(i)->setTitle(EditList.at(i)->text());
            });
        }

        this->connect(GroupList.at(0),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView1,GroupList.at(0)->isChecked());
        });
        this->connect(GroupList.at(1),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView2,GroupList.at(1)->isChecked());
        });
        this->connect(GroupList.at(2),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView3,GroupList.at(2)->isChecked());
        });
        this->connect(GroupList.at(3),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView4,GroupList.at(3)->isChecked());
        });

        this->connect(Setting_Data::Get(),&Setting_Data::InitTable,this,[=](){
            View->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView1));
            View1->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView2));
            View2->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView3));
            View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView4));
            GroupList.at(0)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView1));
            GroupList.at(0)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView1));
            GroupList.at(1)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView2));
            GroupList.at(1)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView2));
            GroupList.at(2)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView3));
            GroupList.at(2)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView3));
            GroupList.at(3)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView4));
            GroupList.at(3)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView4));

        });

        break;
    }
    case PLCMO2Page:
    {
        QStringList msg;
        msg  << "" << "PLC地址" << "功能(中文)" << "功能(英文)";
        QWidget* mWidget = new QWidget();
        mWidget->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
        QHBoxLayout* mLayout = new QHBoxLayout();
        mLayout->setSpacing(10);
        mLayout->setContentsMargins(5,5,5,5);

        //左边
        QWidget* LeftWidget = new QWidget();
        QVBoxLayout* LeftLayout = new QVBoxLayout();
        LeftLayout->setSpacing(10);
        LeftLayout->setContentsMargins(0,0,0,0);

        //第一个列表
        QWidget* ViewWidget1 = Create_PlcGroup(msg);
        SettingThreeValTableView* View = ViewWidget1->findChild<SettingThreeValTableView*>("View");
        View->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView5));

        //第二个列表
        QWidget* ViewWidget2 = Create_PlcGroup(msg);
        SettingThreeValTableView* View2 = ViewWidget2->findChild<SettingThreeValTableView*>("View");
        View2->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView6));

        LeftLayout->addWidget(ViewWidget1);
        LeftLayout->addWidget(ViewWidget2);
        LeftWidget->setLayout(LeftLayout);

        //右边
        QWidget* RightWidget = new QWidget();
        QVBoxLayout* RightLayout = new QVBoxLayout();
        RightLayout->setSpacing(10);
        RightLayout->setContentsMargins(0,0,0,0);

        //第三个列表
        QWidget* ViewWidget3 = Create_PlcGroup(msg);
        SettingThreeValTableView* View3 = ViewWidget3->findChild<SettingThreeValTableView*>("View");
        View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView7));

        //第四个列表
        QWidget* ViewWidget4 = Create_PlcGroup(msg);
        SettingThreeValTableView* View4 = ViewWidget4->findChild<SettingThreeValTableView*>("View");
        View4->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView8));


        RightLayout->addWidget(ViewWidget3);
        RightLayout->addWidget(ViewWidget4);
        RightWidget->setLayout(RightLayout);

        mLayout->addWidget(LeftWidget);
        mLayout->addWidget(RightWidget);
        mWidget->setLayout(mLayout);

        Widget = mWidget;

        QList<QPushButton*> btnList = mWidget->findChildren<QPushButton*>();
        QList<QLineEdit*> EditList = mWidget->findChildren<QLineEdit*>();
        QList<QGroupBox*> GroupList = mWidget->findChildren<QGroupBox*>();

        GroupList.at(0)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView5));
        GroupList.at(0)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView5));
        GroupList.at(1)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView6));
        GroupList.at(1)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView6));
        GroupList.at(2)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView7));
        GroupList.at(2)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView7));
        GroupList.at(3)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView8));
        GroupList.at(3)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView8));

        for(int i = 0; i < 4; i++)
        {
            this->connect(btnList.at(i),&QPushButton::clicked,this,[=](){
                PlcMoType type;
                if(i == 0)
                    type = PlcMoView5;
                else if(i == 1)
                    type = PlcMoView6;
                else if(i == 2)
                    type = PlcMoView7;
                else if(i == 3)
                    type = PlcMoView8;
               if(EditList.at(i)->text().isEmpty())
                   return;
               Setting_Data::Get()->Set_Plc_Title(type,EditList.at(i)->text());
               GroupList.at(i)->setTitle(EditList.at(i)->text());
            });
        }

        this->connect(GroupList.at(0),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView5,GroupList.at(0)->isChecked());
        });
        this->connect(GroupList.at(1),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView6,GroupList.at(1)->isChecked());
        });
        this->connect(GroupList.at(2),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView7,GroupList.at(2)->isChecked());
        });
        this->connect(GroupList.at(3),&QGroupBox::clicked,this,[=](){
            Setting_Data::Get()->Set_Plc_Bool(PlcMoView8,GroupList.at(3)->isChecked());
        });

        this->connect(View,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView5,row,col,data);
        });
        this->connect(View2,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView6,row,col,data);
        });
        this->connect(View3,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView7,row,col,data);
        });
        this->connect(View4,&SettingThreeValTableView::TableModityData,this,[=](int row,int col,QVariant data){
            Setting_Data::Get()->Set_PlcMoListData(PlcMoView8,row,col,data);
        });

        this->connect(Setting_Data::Get(),&Setting_Data::InitTable,this,[=](){
            View->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView5));
            View2->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView6));
            View3->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView7));
            View4->Set_Model_Data(Setting_Data::Get()->GET_ThreeData(PLCMoViewType,MainNothing,ManualNothing,AutoNothing,DataNothing,PlcMoView8));
            GroupList.at(0)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView5));
            GroupList.at(0)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView5));
            GroupList.at(1)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView6));
            GroupList.at(1)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView6));
            GroupList.at(2)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView7));
            GroupList.at(2)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView7));
            GroupList.at(3)->setTitle(Setting_Data::Get()->Get_Plc_Title(PlcMoView8));
            GroupList.at(3)->setChecked(Setting_Data::Get()->Get_Plc_Bool(PlcMoView8));
        });

        break;
    }
    }

    return Widget;
}

QWidget* DB_Hmi_Gui_Setting_Conf::Create_PlcGroup(QStringList msg)
{
    QWidget* LeftTopWidget = new QWidget();
    QVBoxLayout* LeftTopLayout = new QVBoxLayout();
    LeftTopLayout->setSpacing(0);
    LeftTopLayout->setContentsMargins(0,0,0,0);

    QWidget* LeftTopButtonWidget = new QWidget();
    LeftTopButtonWidget->setFixedHeight(40);
    QHBoxLayout* LeftTopButtonLayout = new QHBoxLayout();
    LeftTopButtonLayout->setSpacing(0);
    LeftTopButtonLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl_Name = Public_Control::Get_Label("请输出标题");
    lbl_Name->setObjectName("lblName");
    QLineEdit* LeftTopEdit = new QLineEdit();
    LeftTopEdit->setObjectName("Edit");
    QPushButton* btn_LeftTopSure = new QPushButton();
    btn_LeftTopSure->setObjectName("btn");
    LeftTopButtonLayout->addWidget(lbl_Name);
    LeftTopButtonLayout->addWidget(LeftTopEdit);
    LeftTopButtonLayout->addWidget(btn_LeftTopSure);
    LeftTopButtonWidget->setLayout(LeftTopButtonLayout);

    QGroupBox* ViewBox1 = new QGroupBox();
    ViewBox1->setObjectName("ViewBox");
    ViewBox1->setStyleSheet(Public_Str::Get_Sty(Style_Css{SettingConfGroup,{}}));
    ViewBox1->setTitle("请输入标题");
    ViewBox1->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ViewBox1->setCheckable(true);
    QHBoxLayout* ViewBox1Layout = new QHBoxLayout();
    ViewBox1Layout->setSpacing(0);
    ViewBox1Layout->setContentsMargins(10,10,10,10);
    SettingThreeValTableView* view1 = new SettingThreeValTableView(msg,8,55,290,41,47);
    view1->setObjectName("View");
    ViewBox1Layout->addWidget(view1);
    ViewBox1->setLayout(ViewBox1Layout);
    LeftTopLayout->addWidget(LeftTopButtonWidget);
    LeftTopLayout->addWidget(ViewBox1);
    LeftTopWidget->setLayout(LeftTopLayout);

    return LeftTopWidget;
}
