#include "DB_Hmi_Gui_Main_Body.h"
#include <QHBoxLayout>
#include <QStackedWidget>

#include "DB_Hmi_Gui_Auto_Manual.h"
#include "DB_Hmi_Gui_Data.h"
#include "DB_Hmi_Gui_Setting.h"
#include "DB_Hmi_Gui_System.h"
#include "DB_Hmi_Gui_Passwd.h"
#include "DB_Hmi_Gui_NumKeyBoard.h"

Db_Hmi_Gui_Main_Body::Db_Hmi_Gui_Main_Body(QWidget* parent/* = nullptr*/)
    :QWidget (parent)
{
    this->init();
    qApp->installEventFilter(this);
}

Db_Hmi_Gui_Main_Body::~Db_Hmi_Gui_Main_Body()
{

}

void Db_Hmi_Gui_Main_Body::init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = InitWidget();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget* Db_Hmi_Gui_Main_Body::InitWidget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QStackedWidget* mSWidget = new QStackedWidget();
    mSWidget->setObjectName("mSWidget");
    DB_Hmi_Gui_Auto_Manual* Auto_Manual = new DB_Hmi_Gui_Auto_Manual(this);
    Auto_Manual->setObjectName("Auto_Manual");
//    Auto_Manual->installEventFilter(this);
    DB_Hmi_Gui_Data* Data = new DB_Hmi_Gui_Data(this);
//    Data->installEventFilter(this);
    DB_Hmi_Body_System* System = new DB_Hmi_Body_System(this);
//    System->installEventFilter(this);
    DB_Hmi_Gui_Setting* Setting = new DB_Hmi_Gui_Setting(this);
//    Setting->installEventFilter(this);


    mSWidget->addWidget(Auto_Manual);
    mSWidget->addWidget(Data);
    mSWidget->addWidget(System);
    mSWidget->addWidget(Setting);

    mSWidget->setCurrentIndex(0);

    mLayout->addWidget(mSWidget);
    mWidget->setLayout(mLayout);
    return mWidget;
}

void Db_Hmi_Gui_Main_Body::Slot_Switch_Page(int page)
{
    QStackedWidget* mSWidget = this->findChild<QStackedWidget*>("mSWidget");
    if(page == 3)
    {
        if(!PasswdSure)
        {
            DB_Hmi_Gui_Passwd* passwd = new DB_Hmi_Gui_Passwd();
            bool isok = passwd->exec();
            if(isok == 1)
            {
                passwd->deleteLater();
                passwd = nullptr;
                PasswdSure = true;
                mSWidget->setCurrentIndex(page);
            }
        }
        else
            mSWidget->setCurrentIndex(page);
    }
    else
        mSWidget->setCurrentIndex(page);
}
