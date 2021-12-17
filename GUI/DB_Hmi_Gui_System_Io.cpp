#include "DB_Hmi_Gui_System_Io.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>

#include "Public/Public_Control.h"
#include "Socket/RunTcp.h"

DB_Hmi_Gui_System_Io::DB_Hmi_Gui_System_Io(QWidget* parent)
    :QWidget (parent)
{
    this->init();
}

DB_Hmi_Gui_System_Io::~DB_Hmi_Gui_System_Io()
{

}

void DB_Hmi_Gui_System_Io::init()
{
    QHBoxLayout* mHbox = new QHBoxLayout();
    mHbox->setSpacing(0);
    mHbox->setContentsMargins(0,0,0,0);

    QWidget* Init = InitWidget();

    mHbox->addWidget(Init);
    this->setLayout(mHbox);
}

QWidget* DB_Hmi_Gui_System_Io::InitWidget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QGroupBox* mBox = new QGroupBox();
    QHBoxLayout* mBoxLayout = new QHBoxLayout();
    mBoxLayout->setSpacing(0);
    mBoxLayout->setContentsMargins(0,0,0,0);

    QWidget* IOColumn = Column_Init();
    IOColumn->setObjectName("IOColumn");
    QWidget* IOColumn1 = Column_Init();
    IOColumn1->setObjectName("IOColumn1");
    QWidget* IOColumn2 = Column_Init();
    QWidget* IOColumn3 = Column_Init();

    mBoxLayout->addWidget(IOColumn);
    mBoxLayout->addWidget(IOColumn1);
    mBoxLayout->addWidget(IOColumn2);
    mBoxLayout->addWidget(IOColumn3);
    mBox->setLayout(mBoxLayout);

    mLayout->addWidget(mBox);
    mWidget->setLayout(mLayout);

    return mWidget;
}


QWidget* DB_Hmi_Gui_System_Io::Column_Init()
{
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    const QString lbl_IO_Style = "image: url(://Img/system/off_1.png);"
                                 "border:none;";
    for(int i = 0; i < 16; i++)
    {
        QHBoxLayout* mHbox = new QHBoxLayout();
        mHbox->setSpacing(0);
        mHbox->setContentsMargins(0,0,0,0);

        QPushButton* btn_Io = Public_Control::Get_Button("","",0,0,lbl_IO_Style);
//        btn_Io->setFixedHeight(40);

        QLabel* lbl_IoText = Public_Control::Get_Label("","");
//        lbl_IoText->setFixedHeight(40);

        mHbox->addWidget(btn_Io);
        mHbox->addWidget(lbl_IoText);

        mLayout->addLayout(mHbox);
    }
    mWidget->setLayout(mLayout);

    return mWidget;
}

void DB_Hmi_Gui_System_Io::Set_PLCIO(QStringList msg,int index)
{
    QList<QLabel*> LabelList = this->findChildren<QLabel*>();
    if(index == 0)
    {
        for(int i = 0; i < msg.size(); i++)
        {
            LabelList.at(i)->setText(msg.at(i));
        }
    }
    else if(index == 1)
    {
        for(int i = 0; i < msg.size(); i++)
        {
            LabelList.at(i + 32)->setText(msg.at(i));
        }
    }
}

void DB_Hmi_Gui_System_Io::Set_PLCIO_Stare(bool,int)
{

}
