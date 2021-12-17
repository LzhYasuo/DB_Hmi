#ifndef _PUBLIC_STR_H_
#define _PUBLIC_STR_H_
#include <QVariant>
#include <QList>

enum Style_Type
{
    TableLabelWidgetStyle,
    TopWidgetStyle,
    GetLabelStyle,
    CoordGroupStyle,
    InformationGroupStyle,
    AutoManualRightTopKeyUpStyle,               //自动手动右边的最上层的最左的上Key
    AutoManualRightTopKeyDownStyle,             //自动手动右边的最上层的最左的下Key
    AutoManualRightTopKeyLeftStyle,             //自动手动右边的最上层的最左的左Key
    AutoManualRightTopKeyRightStyle,            //自动手动右边的最上层的最左的右Key
    AutoManualRightTopKeyMidStyle,              //自动手动右边的最上层的最左的中Key
    AutoManualRightTopMidUpStyle,               //自动手动右边的最上层的中间的上Key
    AutoManualRightTopMidDownStyle,             //自动手动右边的最上层的中间的下Key
    AutoManualRightTopMidinverseStyle,          //自动手动右边的最上层的中间的逆Key
    AutoManualRightTopMidShunStyle,             //自动手动右边的最上层的中间的顺Key
    AutoManualRightTopRightButtonStyle,         //自动手动右边的最上层的右边的按钮
    AutoManualRightTopMidButtonStyle,           //自动手动右边的中间层的按钮
    AutoManualRightTopBottomTopButtonSytle,     //自动手动右边的下层层的上面的按钮
    AutoManualRightTopBottomBottomButtonStyle,  //自动手动右边的下层层的下面的按钮
    AutoManualRightTopMidDoubleSPinStyle,       //
    AutoManualRightTopMidRadioButtonStyle,      //
    DataCuttingSpinboxStyle,                    //Cutting SpinBox的样式
    DataCuttingDoubleSpinboxStyle,              //Cutting DoubleSpinBox的样式
    DataCuttingLabelStyle,                      //Cutting Label样式表
    DataTitleStyle,                             //Data 标题Label的样式表
    SystemRightButtonTop,                       //
    SystemRightButtonMid,                       //
    SystemRightButtonBottom,                    //
    SettingRightButtonTop,                      //
    SettingRightButtonMid,                      //
    SettingRightButtonBottom,                   //
    SystemPageTableHead,                        //
    SettingButton,                              //
    SettingConfGroup,                           //
};

struct Style_Css
{
    Style_Type type;
    QList<QVariant> value;
};

class QString;
class Public_Str
{
public:
    static QString Get_Sty(Style_Css);
private:
    Public_Str();
    ~Public_Str();
};


#endif //_PUBLIC_STR_H_
