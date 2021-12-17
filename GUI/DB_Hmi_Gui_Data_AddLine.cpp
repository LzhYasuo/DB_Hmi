#include "DB_Hmi_Gui_Data_AddLine.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QLabel>

#include <QMessageBox>

DB_Hmi_Gui_Data_AddLine::DB_Hmi_Gui_Data_AddLine(QWidget* Widget)
    :QDialog(Widget)
{
    this->Init();
    this->setFixedSize(300,595);
}

DB_Hmi_Gui_Data_AddLine::~DB_Hmi_Gui_Data_AddLine()
{

}

void DB_Hmi_Gui_Data_AddLine::Init()
{
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = InitWidget();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget* DB_Hmi_Gui_Data_AddLine::InitWidget()
{
    QWidget* mWidget = new QWidget();
    mWidget->setStyleSheet("font : 13pt ""黑体""; ");
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QLineEdit* Edit = new QLineEdit();
    Edit->setObjectName("NameEdit");
    Edit->setFixedHeight(35);
    Edit->setPlaceholderText(tr("请输入这行的名称"));

    QComboBox* box = new QComboBox();
    box->setObjectName("ComBox");
    box->setFixedHeight(35);
    box->addItem("SpinBox");
    box->addItem("DoubleSpin");
    box->addItem("ComboBox");

    QComboBox* box1 = new QComboBox();
    box1->setObjectName("ComBox1");
    box1->setFixedHeight(35);
    box1->addItem("1");
    box1->addItem("2");
    box1->addItem("3");
    box1->addItem("4");
    box1->addItem("5");

    //正则表达式 限制数字
    QRegExp rx("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);

    QLineEdit* MinEdit = new QLineEdit();
    MinEdit->setObjectName("MinEdit");
    MinEdit->setPlaceholderText(tr("请输入这个控件的最小值"));
    MinEdit->setFixedHeight(35);
    MinEdit->setValidator(pReg);

    QLineEdit* MaxEdit = new QLineEdit();
    MaxEdit->setObjectName("MaxEdit");
    MaxEdit->setPlaceholderText(tr("请输入这个控件的最大值"));
    MaxEdit->setFixedHeight(35);
    MinEdit->setValidator(pReg);

    QValidator* validator = new QIntValidator( 1, 3, this );
    QLineEdit* DecimalEdit = new QLineEdit();
    DecimalEdit->setObjectName("DecimalEdit");
    DecimalEdit->setFixedHeight(35);
    DecimalEdit->setPlaceholderText(tr("请输入这个控件的小数点"));
    DecimalEdit->setEnabled(false);
    DecimalEdit->setValidator(validator);

    mLayout->addWidget(Edit);
    mLayout->addWidget(box);
    mLayout->addWidget(box1);
    mLayout->addWidget(MinEdit);
    mLayout->addWidget(MaxEdit);
    mLayout->addWidget(DecimalEdit);

    for(int j = 0; j < 5; j++)
    {
        QLineEdit* boxValue = new QLineEdit();
        boxValue->setFixedHeight(35);
        boxValue->setObjectName("boxValue" + QString::number(j));
        boxValue->setPlaceholderText(QString("请输入下拉框第%1个项").arg(j + 1));
        boxValue->setEnabled(false);
        if(j > 0)
            boxValue->hide();
        mLayout->addWidget(boxValue);
    }

    for(int i = 0; i < 8; i++)
    {
        QValidator* pValidator = new QIntValidator( 1, 10000, this );
        QLineEdit* P = new QLineEdit();
        P->setObjectName("P" + QString::number(i + 1));
        P->setPlaceholderText(QString("请输入第%1个P参数").arg(i + 1));
        P->setFixedHeight(35);
        P->setValidator(pValidator);
        mLayout->addWidget(P);
    }

    QPushButton* btn_Sure = new QPushButton();
    btn_Sure->setText("确定");
    btn_Sure->setFixedHeight(35);
    QPushButton* btn_Quit = new QPushButton();
    btn_Quit->setText("取消");
    btn_Quit->setFixedHeight(35);
    mLayout->addWidget(btn_Sure);
    mLayout->addWidget(btn_Quit);

    this->connect(btn_Sure,&QPushButton::clicked,this,&DB_Hmi_Gui_Data_AddLine::Button_Clicked_Slot);
    this->connect(btn_Quit,&QPushButton::clicked,this,[=](){done(0);});
    this->connect(box,SIGNAL(activated(int)),this,SLOT(ComboBox_Switch_Slot(int)));
    this->connect(box1,SIGNAL(activated(int)),this,SLOT(ComboBox_Change_Slot(int)));
    mWidget->setLayout(mLayout);

    return mWidget;
}

void DB_Hmi_Gui_Data_AddLine::ComboBox_Switch_Slot(int index)
{
    QLineEdit *Decimal = this->findChild<QLineEdit *>("DecimalEdit");
    QLineEdit *min = this->findChild<QLineEdit *>("MinEdit");
    QLineEdit *max = this->findChild<QLineEdit *>("MaxEdit");
    QLineEdit *boxValue = this->findChild<QLineEdit *>("boxValue0");
    QLineEdit *boxValue1 = this->findChild<QLineEdit *>("boxValue1");
    QLineEdit *boxValue2 = this->findChild<QLineEdit *>("boxValue2");
    QLineEdit *boxValue3 = this->findChild<QLineEdit *>("boxValue3");
    QLineEdit *boxValue4 = this->findChild<QLineEdit *>("boxValue4");
    if(index == 0)
    {
         Decimal->setEnabled(false);
         min->setEnabled(true);
         max->setEnabled(true);
         boxValue->setEnabled(false);
         boxValue1->setEnabled(false);
         boxValue2->setEnabled(false);
         boxValue3->setEnabled(false);
         boxValue4->setEnabled(false);

         Decimal->clear();
         boxValue->clear();
         boxValue1->clear();
         boxValue2->clear();
         boxValue3->clear();
         boxValue4->clear();
    }
    else if(index == 1)
    {
        min->setEnabled(true);
        max->setEnabled(true);
        Decimal->setEnabled(true);

        boxValue->setEnabled(false);
        boxValue1->setEnabled(false);
        boxValue2->setEnabled(false);
        boxValue3->setEnabled(false);
        boxValue4->setEnabled(false);
        boxValue->clear();
        boxValue1->clear();
        boxValue2->clear();
        boxValue3->clear();
        boxValue4->clear();
    }
    else if(index == 2)
    {
        Decimal->setEnabled(false);
        min->setEnabled(false);
        max->setEnabled(false);
        Decimal->clear();
        min->clear();
        max->clear();
        boxValue->setEnabled(true);
        boxValue1->setEnabled(true);
        boxValue2->setEnabled(true);
        boxValue3->setEnabled(true);
        boxValue4->setEnabled(true);
    }
}

void DB_Hmi_Gui_Data_AddLine::Button_Clicked_Slot()
{
    QList<QLineEdit*> LineEdit = this->findChildren<QLineEdit*>();
    for(int i = 0; i < LineEdit.size(); i++)
    {
        if(LineEdit.at(i)->isHidden())
            continue;
        if(!LineEdit.at(i)->isEnabled())
            continue;
        if(LineEdit.at(i)->text().isEmpty())
        {
            QMessageBox::information(this,"Error","Parameter is Empty");
            return;
        }
    }
    QLineEdit* min = this->findChild<QLineEdit*>("MinEdit");
    QLineEdit* max = this->findChild<QLineEdit*>("MaxEdit");
    if(min->text().toInt() > max->text().toInt())
    {
        QMessageBox::information(this,"Error","MinValue > MaxValue");
        return;
    }
    QComboBox* Box = this->findChild<QComboBox*>("ComBox");
    QLineEdit* NameEdit = this->findChild<QLineEdit*>("NameEdit");
    QStringList PList;
    for(int i = 0; i < 8; i++)
    {
        QLineEdit* P = this->findChild<QLineEdit*>("P" + QString::number(i + 1));
        PList << P->text();
        qDebug() << PList;
    }
    //SpinBox
    if(Box->currentIndex() == 0)
    {
        emit Add_Line_Data(NameEdit->text(),max->text().toInt(),min->text().toInt(),0,1,PList);
    }
    //DoubleSpinBox
    else if(Box->currentIndex() == 1)
    {
        QLineEdit* DecimalEdit = this->findChild<QLineEdit*>("DecimalEdit");
        emit Add_Line_Data(NameEdit->text(),max->text().toInt(),min->text().toInt(),DecimalEdit->text().toInt(),2,PList);
    }
    else if(Box->currentIndex() == 2)
    {
        QComboBox* box = this->findChild<QComboBox*>("ComBox1");
        int num = box->currentText().toInt();
        QStringList ComList;
        for(int i = 0; i < num; i++)
        {
            QLineEdit* box = this->findChild<QLineEdit*>("boxValue" + QString::number(i));
            qDebug() << box->text();
            ComList << box->text();
        }
        qDebug() << ComList;
        emit Add_Line_Data(NameEdit->text(),0,0,0,3,PList,ComList);
    }

    done(1);
}

void DB_Hmi_Gui_Data_AddLine::ComboBox_Change_Slot(int index)
{
    if(index == 0)
    {
        QLineEdit *boxValue1 = this->findChild<QLineEdit *>("boxValue1");
        QLineEdit *boxValue2 = this->findChild<QLineEdit *>("boxValue2");
        QLineEdit *boxValue3 = this->findChild<QLineEdit *>("boxValue3");
        QLineEdit *boxValue4 = this->findChild<QLineEdit *>("boxValue4");
        boxValue1->hide();
        boxValue2->hide();
        boxValue3->hide();
        boxValue4->hide();
        this->setFixedSize(300,595);
    }
    else if(index == 1)
    {
        QLineEdit *boxValue1 = this->findChild<QLineEdit *>("boxValue1");
        QLineEdit *boxValue2 = this->findChild<QLineEdit *>("boxValue2");
        QLineEdit *boxValue3 = this->findChild<QLineEdit *>("boxValue3");
        QLineEdit *boxValue4 = this->findChild<QLineEdit *>("boxValue4");
        boxValue1->show();
        boxValue2->hide();
        boxValue3->hide();
        boxValue4->hide();
        this->setFixedSize(300,630);
    }
    else if(index == 2)
    {
        QLineEdit *boxValue1 = this->findChild<QLineEdit *>("boxValue1");
        QLineEdit *boxValue2 = this->findChild<QLineEdit *>("boxValue2");
        QLineEdit *boxValue3 = this->findChild<QLineEdit *>("boxValue3");
        QLineEdit *boxValue4 = this->findChild<QLineEdit *>("boxValue4");
        boxValue1->show();
        boxValue2->show();
        boxValue3->hide();
        boxValue4->hide();
        this->setFixedSize(300,665);
    }
    else if(index == 3)
    {
        QLineEdit *boxValue1 = this->findChild<QLineEdit *>("boxValue1");
        QLineEdit *boxValue2 = this->findChild<QLineEdit *>("boxValue2");
        QLineEdit *boxValue3 = this->findChild<QLineEdit *>("boxValue3");
        QLineEdit *boxValue4 = this->findChild<QLineEdit *>("boxValue4");
        boxValue1->show();
        boxValue2->show();
        boxValue3->show();
        boxValue4->hide();
        this->setFixedSize(300,700);
    }
    else if(index == 4)
    {
        QLineEdit *boxValue1 = this->findChild<QLineEdit *>("boxValue1");
        QLineEdit *boxValue2 = this->findChild<QLineEdit *>("boxValue2");
        QLineEdit *boxValue3 = this->findChild<QLineEdit *>("boxValue3");
        QLineEdit *boxValue4 = this->findChild<QLineEdit *>("boxValue4");
        boxValue1->show();
        boxValue2->show();
        boxValue3->show();
        boxValue4->show();
        this->setFixedSize(300,735);
    }
}

void DB_Hmi_Gui_Data_AddLine::Clear()
{
    QList<QComboBox*> BoxList = this->findChildren<QComboBox*>();
    BoxList.at(0)->setCurrentIndex(0);
    QList<QLineEdit*> LineEdit = this->findChildren<QLineEdit*>();
    for(int i = 0; i < LineEdit.size(); i++)
    {
        LineEdit.at(i)->setText("");
    }
}
