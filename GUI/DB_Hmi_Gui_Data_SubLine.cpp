#include "DB_Hmi_Gui_Data_SubLine.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>

#include "Public/Public_Function.h"

DB_Hmi_Gui_Data_SubLine::DB_Hmi_Gui_Data_SubLine(QStringList tableName, QWidget* Widget)
    : QDialog (Widget),
      mTableName(tableName)
{
    this->setFixedSize(300,105);
    this->Init();
}

DB_Hmi_Gui_Data_SubLine::~DB_Hmi_Gui_Data_SubLine()
{

}

void DB_Hmi_Gui_Data_SubLine::Init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = InitWidget();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget* DB_Hmi_Gui_Data_SubLine::InitWidget()
{
    QWidget* mWidget = new QWidget();
    mWidget->setStyleSheet("font : 13pt ""黑体""; ");
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QComboBox* box = new QComboBox();
    box->setObjectName("ChooseBox");
    box->setFixedHeight(35);
    QLineEdit* boxEdit = new QLineEdit();
    boxEdit->setReadOnly(true);
    boxEdit->setPlaceholderText("请选择你要删除的个数");
    box->setLineEdit(boxEdit);
    box->addItem("1");
    box->addItem("2");
    box->addItem("3");
    box->addItem("4");
    box->addItem("5");
    box->setCurrentIndex(-1);
    mLayout->addWidget(box);

    for(int i = 0; i < 5; i++)
    {
        QComboBox* boxTable = new QComboBox();
        boxTable->setObjectName("boxTable" + QString::number(i));
        boxTable->setFixedHeight(35);
        QLineEdit* boxTableEdit = new QLineEdit();
        boxTableEdit->setReadOnly(true);
        boxTableEdit->setPlaceholderText("请选择你要删除的列表");
        boxTable->setLineEdit(boxTableEdit);
        for(int i = 0; i < mTableName.size(); i++)
        {
            boxTable->addItem(mTableName.at(i));
        }
        boxTable->hide();
        boxTable->setCurrentIndex(-1);
        mLayout->addWidget(boxTable);
    }

    QPushButton* btn_Sure = new QPushButton();
    btn_Sure->setFixedHeight(35);
    btn_Sure->setText("确定");
    QPushButton* btn_Quit = new QPushButton();
    btn_Quit->setText("取消");
    btn_Quit->setFixedHeight(35);

    mLayout->addWidget(btn_Sure);
    mLayout->addWidget(btn_Quit);

    this->connect(btn_Sure,&QPushButton::clicked,this,&DB_Hmi_Gui_Data_SubLine::ButtonClickedSlot);
    this->connect(btn_Quit,&QPushButton::clicked,this,[=]()
    {
        this->Clear();
        done(0);
    });
    this->connect(box,SIGNAL(activated(int)),this,SLOT(BoxSwitchSlot(int)));

    mWidget->setLayout(mLayout);


    return mWidget;
}

void DB_Hmi_Gui_Data_SubLine::BoxSwitchSlot(int index)
{
    QComboBox *boxValue = this->findChild<QComboBox *>("boxTable0");
    QComboBox *boxValue1 = this->findChild<QComboBox *>("boxTable1");
    QComboBox *boxValue2 = this->findChild<QComboBox *>("boxTable2");
    QComboBox *boxValue3 = this->findChild<QComboBox *>("boxTable3");
    QComboBox *boxValue4 = this->findChild<QComboBox *>("boxTable4");
    if(index == 0)
    {
        boxValue->setCurrentIndex(-1);
        boxValue1->setCurrentIndex(-1);
        boxValue2->setCurrentIndex(-1);
        boxValue3->setCurrentIndex(-1);
        boxValue4->setCurrentIndex(-1);
        boxValue->show();
        boxValue1->hide();
        boxValue2->hide();
        boxValue3->hide();
        boxValue4->hide();
        this->setFixedSize(300,140);
    }
    else if(index == 1)
    {
        boxValue2->setCurrentIndex(-1);
        boxValue3->setCurrentIndex(-1);
        boxValue4->setCurrentIndex(-1);
        boxValue->show();
        boxValue1->show();
        boxValue2->hide();
        boxValue3->hide();
        boxValue4->hide();
        this->setFixedSize(300,175);
    }
    else if(index == 2)
    {
        boxValue3->setCurrentIndex(-1);
        boxValue4->setCurrentIndex(-1);
        boxValue->show();
        boxValue1->show();
        boxValue2->show();
        boxValue3->hide();
        boxValue4->hide();
        this->setFixedSize(300,210);
    }
    else if(index == 3)
    {
        boxValue4->setCurrentIndex(-1);
        boxValue->show();
        boxValue1->show();
        boxValue2->show();
        boxValue3->show();
        boxValue4->hide();
        this->setFixedSize(300,245);
    }
    else if(index == 4)
    {
        boxValue->show();
        boxValue1->show();
        boxValue2->show();
        boxValue3->show();
        boxValue4->show();
        this->setFixedSize(300,280);
    }
}

void DB_Hmi_Gui_Data_SubLine::ButtonClickedSlot()
{
    QList<QComboBox*> ComboList = this->findChildren<QComboBox*>();
    for(int i = 0; i < ComboList.size(); i++)
    {
        if(ComboList.at(i)->isHidden())
            continue;
        if(ComboList.at(i)->currentIndex() < 0)
        {
            QMessageBox::information(this,"Error","Parameter is Empt");
            return;
        }
    }
    QStringList str;
    for(int i = 0; i < ComboList.size(); i++)
    {
        if(ComboList.at(i)->isHidden())
            continue;
        if(ComboList.at(i)->objectName() != "ChooseBox")
        {
            str << ComboList.at(i)->currentText();
        }
    }
    bool isok = Public_Function::removeListSame(&str);
    if(isok)
        emit Sub_Line_Data(str);

    done(1);
}

void DB_Hmi_Gui_Data_SubLine::Clear()
{
    QList<QComboBox*> ComboList = this->findChildren<QComboBox*>();
    for(int i = 0; i < ComboList.size(); i++)
    {
        if(ComboList.at(i)->objectName() != "ChooseBox")
        {
            ComboList.at(i)->setCurrentIndex(-1);
            ComboList.at(i)->hide();
        }
        else
        {
            ComboList.at(i)->setCurrentIndex(-1);
        }
    }
    this->setFixedSize(300,105);
}
