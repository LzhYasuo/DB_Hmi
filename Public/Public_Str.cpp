#include "Public_Str.h"

#define GET_STR(x) #x

QString Public_Str::Get_Sty(Style_Css code)
{
    QString msg;
    switch(code.type)
    {
    case TableLabelWidgetStyle:
    {
        return GET_STR
        (
           background-color:rgb(150,150,150);
           border:1px solid rgb(255,255,255);
        );
    }
    case TopWidgetStyle:
        {
        return  GET_STR
        (
            background-color:rgb(150,150,150);
        );
        }
    case GetLabelStyle:
    {
        return GET_STR
        (
            background-color:rgb(230,230,230);
            border:1px solid rgb(150,150,150);
        );
    }
    case CoordGroupStyle:
    {
        return GET_STR
        (
            border:1px solid rgb(230,230,230);
        );
    }
    case InformationGroupStyle:
    {
        return GET_STR
        (
            border:1px solid rgb(230,230,230);
        );
    }
    case AutoManualRightTopKeyUpStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                background-color:transparent;
                background:transparent;
                border: 2px groove gray;
                border-style: hidden;
                border-image: url(:/Img/front1.png);
            }
            QPushButton:pressed
            {
                 border-image: url(:/Img/front2.png);
            }
        );
    }
    case AutoManualRightTopKeyDownStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                background-color:transparent;
                background:transparent;
                border: 2px groove gray;
                border-style: hidden;
                border-image: url(:/Img/back1.png);
            }
            QPushButton:pressed
            {
                 border-image: url(:/Img/back2.png);
            }
        );
    }
    case AutoManualRightTopKeyLeftStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                background-color:transparent;
                background:transparent;
                border: 2px groove gray;
                border-style: hidden;
                border-image: url(:/Img/left1.png);
            }
            QPushButton:pressed
            {
                 border-image: url(:/Img/left2.png);
            }
        );
    }
    case AutoManualRightTopKeyRightStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                background-color:transparent;
                background:transparent;
                border: 2px groove gray;
                border-style: hidden;
                border-image: url(:/Img/right1.png);
            }
            QPushButton:pressed
            {
                 border-image: url(:/Img/right2.png);
            }
        );
    }
    case AutoManualRightTopKeyMidStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                background-color:transparent;
                background:transparent;
                border: 2px groove gray;
                border-style: hidden;
                border-image: url(:/Img/fast1.png);
            }
            QPushButton:pressed
            {
                 border-image: url(:/Img/fast2.png);
            }
        );
    }
    case AutoManualRightTopMidUpStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                border-image: url(:/Img/up1.png);
            }
            QPushButton:pressed
            {
                border-image: url(:/Img/up2.png);
            }
        );
    }
    case AutoManualRightTopMidDownStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                border-image: url(:/Img/down1.png);
            }
            QPushButton:pressed
            {
                border-image: url(:/Img/down2.png);
            }
        );
    }
    case AutoManualRightTopMidinverseStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                border-image: url(:/Img/x1.png);
            }
            QPushButton:pressed
            {
                border-image: url(:/Img/x11.png);
            }
        );
    }
    case AutoManualRightTopMidShunStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                border-image: url(:/Img/x2.png);
            }
            QPushButton:pressed
            {
                border-image: url(:/Img/x22.png);
            }
        );
    }
    case AutoManualRightTopRightButtonStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                color:rgb(230,230,230);
                background-color:rgb(100, 100, 100);
                border: 2px groove gray;
            }
            QPushButton:pressed
            {
                background:rgb(255,215,0);
            }

            QPushButton:pressed
            {
                background-color:rgb(14, 114, 198);
            }
        );
    }
    case AutoManualRightTopMidButtonStyle:
    {
        return GET_STR
        (
            QPushButton
            {
                border-image: url(:/Img/1_1.png);
            }
            QPushButton:hover
            {
                border-image: url(:/Img/1_2.png);
            }
            QPushButton:pressed
            {
                border-image: url(:/Img/1_3.png);
            }
        );
    }
    case AutoManualRightTopBottomTopButtonSytle:
    {
        return GET_STR
        (
            QPushButton
            {
                background-color:rgb(225, 225, 230);
                border: 1px groove gray;
            }
            QPushButton:hover
            {
                background:rgb(255,215,0);
            }

            QPushButton:pressed
            {
                background-color:rgb(14, 114, 198);
                border-style: inset;
            }
        );
    }
    case AutoManualRightTopBottomBottomButtonStyle:
    {
        return GET_STR
        (
            QPushButton
            {
               border-image:url(:/Img/default.png);
            }
        );
    }
    case AutoManualRightTopMidDoubleSPinStyle:
    {
        return GET_STR
        (
            QDoubleSpinBox
            {

                background-color: rgb(240, 240, 240);
                border:3px solid grey;
                border-radius:10px;
            }
        );
    }
    case AutoManualRightTopMidRadioButtonStyle:
    {
        return GET_STR
        (
            QRadioButton
            {
                font:12pt 黑体;
            }
        );
    }
    case DataCuttingSpinboxStyle:
    {
        return GET_STR
        (
            QSpinBox
            {
                border:1px solid #242424;
            }

            QSpinBox::up-button
            {
                width:0px;
            }
            QSpinBox::down-button
            {
                width:0px;
            }
        );
    }
    case DataCuttingDoubleSpinboxStyle:
    {
        return GET_STR
        (
            QDoubleSpinBox
            {
                border:1px solid #242424;
            }

            QDoubleSpinBox::up-button
            {
                width:0px;
            }
            QDoubleSpinBox::down-button
            {
                width:0px;
            }
        );
    }
    case DataCuttingLabelStyle:
    {
        return GET_STR
        (
            font : 12pt 黑体;
        );
    }
    case DataTitleStyle:
    {
        return GET_STR
        (
            font : 16pt 黑体;
            color: rgb(6,18,255);
        );
    }
    case SystemRightButtonTop:
    {
        return GET_STR
        (
            QPushButton
            {
            color:rgb(255,255,255);
            background-color:rgb(150,150,150);
            border-top-right-radius:10px;
            }
            QPushButton:checked
            {
            background-color:rgb(255,255,255);
            color:rgb(0,0,0);
            };
        );
    }
    case SystemRightButtonMid:
    {
        return GET_STR
        (
            QPushButton
            {
            color:rgb(255,255,255);
            background-color:rgb(150,150,150);
            border:none;
            }
            QPushButton:checked
            {
            background-color:rgb(255,255,255);
            color:rgb(0,0,0);
            };
        );
    }
    case SystemRightButtonBottom:
    {
        return GET_STR
        (
            QPushButton
            {
            color:rgb(255,255,255);
            background-color:rgb(150,150,150);
            border-bottom-right-radius:10px;
            }
            QPushButton:checked
            {
            background-color:rgb(255,255,255);
            color:rgb(0,0,0);
            };
        );
    }
    case SettingRightButtonTop:
    {
        return GET_STR
        (
            QPushButton
            {
            color:rgb(255,255,255);
            background-color:rgb(50,50,50);
            border-top-right-radius:10px;
            }
            QPushButton:checked
            {
            background-color:rgb(255,255,255);
            color:rgb(0,0,0);
            };
        );
    }
    case SettingRightButtonMid:
    {
        return GET_STR
        (
            QPushButton
            {
            color:rgb(255,255,255);
            background-color:rgb(50,50,50);
            border:none;
            }
            QPushButton:checked
            {
            background-color:rgb(255,255,255);
            color:rgb(0,0,0);
            };
        );
    }
    case SettingRightButtonBottom:
    {
        return GET_STR
        (
            QPushButton
            {
            color:rgb(255,255,255);
            background-color:rgb(50,50,50);
            border-bottom-right-radius:10px;
            }
            QPushButton:checked
            {
            background-color:rgb(255,255,255);
            color:rgb(0,0,0);
            };
        );
    }
    case SystemPageTableHead:
    {
        return GET_STR
        (
                QTableView QHeaderView::section
                {
                background-color:rgb(180,180,180);
                border:1px solid rgb(220,220,220);
                }
        );
    }
    case SettingButton:
    {
        return GET_STR
        (
            QPushButton
            {
            color:rgb(230,230,230);
                background-color:rgb(100, 100, 100);
                border: 2px groove gray;
            }
            QPushButton:hover
            {
                background:rgb(255,215,0);
            }

            QPushButton:pressed
            {
                background-color:rgb(14, 114, 198);
            }
        );
    }
    case SettingConfGroup:
    {
        return GET_STR
        (
            QGroupBox
            {
                border: 2px solid gray;
                border-radius: 5px;
                margin-top: 2ex;
            }

            QGroupBox::title
            {
                subcontrol-origin: margin;

            }
        );
    }

    }
}

