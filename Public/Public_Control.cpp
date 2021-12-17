#include <Public/Public_Control.h>
#include <QIcon>
#include <QToolButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>


Public_Control::Public_Control()
{

}

Public_Control::~Public_Control()
{

}

QToolButton* Public_Control::Get_ToolButton(QString name,QString Icon,int Width,int Height,QString Style)
{
    const QIcon icon = QIcon(Icon);
    const QString btnStyle = Style;
    QToolButton* btn = new QToolButton();
    btn->setIcon(icon);
    if(Width != 0)
        btn->setFixedWidth(Width);
    if(Height != 0)
        btn->setFixedHeight(Height);
    btn->setIconSize(QSize(30,30));
    btn->setText(name);
    btn->setStyleSheet(btnStyle);

    return btn;

}

QPushButton* Public_Control::Get_Button(QString name,QString Icon,int Width,int Height,QString Style)
{
    const QIcon icon = QIcon(Icon);
    const QString btnStyle = Style;
    QPushButton* btn = new QPushButton();
    btn->setIcon(icon);
    if(Width != 0)
        btn->setFixedWidth(Width);
    if(Height != 0)
        btn->setFixedHeight(Height);
    btn->setIconSize(QSize(32,32));
    btn->setText(name);
    btn->setStyleSheet(btnStyle);

    return btn;
}

QPushButton* Public_Control::Get_ButtonIconSize(QString name,QString Icon,int Width,int Height,int IconWidth,int IconHeight,QString Style)
{
    const QIcon icon = QIcon(Icon);
    const QString btnStyle = Style;
    QPushButton* btn = new QPushButton();
    btn->setIcon(icon);
    if(Width != 0)
        btn->setFixedWidth(Width);
    if(Height != 0)
        btn->setFixedHeight(Height);
    btn->setIconSize(QSize(IconWidth,IconHeight));
    btn->setText(name);
    btn->setStyleSheet(btnStyle);

    return btn;
}

QLabel* Public_Control::Get_Label(QString name,QString Icon,QString Style)
{
    const QPixmap pix = QPixmap(Icon);
    const QString ButtonStyle = Style;
    QLabel* label = new QLabel();
    label->setPixmap(pix);
    label->setAlignment(Qt::AlignCenter);
    label->setText(name);
    label->setStyleSheet(ButtonStyle);

    return label;
}

QHBoxLayout* Public_Control::Get_HLayout(int SpaceValue, int left, int Up, int Right, int Down)
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(SpaceValue);
    mLayout->setContentsMargins(left,Up,Right,Down);

    return mLayout;
}

QVBoxLayout* Public_Control::Get_VLayout(int SpaceValue, int left, int Up, int Right, int Down)
{
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(SpaceValue);
    mLayout->setContentsMargins(left,Up,Right,Down);

    return mLayout;
}

QWidget* Public_Control::Create_Labal_Value(QString Text,QString Value,QString TextObjName,QString ValueObjName)
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    const QString lbl_Text_Style = "";
    QLabel* lbl_Text = Get_Label(Text);
    lbl_Text->setObjectName(TextObjName);

    const QString lbl_Value_Style = "";
    QLabel* lbl_Value = Get_Label(Value);
    lbl_Value->setObjectName(ValueObjName);

    mLayout->addWidget(lbl_Text);
    mLayout->addWidget(lbl_Value);
    mWidget->setLayout(mLayout);

    return mWidget;
}


double Public_Control::Get_DeskX()
{
    return X;
}

double Public_Control::Get_DeskY()
{
    return Y;
}
void Public_Control::Set_DeskX(double x)
{
    X = x;
}
void Public_Control::Set_DeskY(double y)
{
    Y = y;
}

Public_Control* Public_Control::Get()
{
    static Public_Control x;
    return &x;
}
