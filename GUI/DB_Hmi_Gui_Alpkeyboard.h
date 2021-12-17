#ifndef DB_HMI_GUI_ALPKEYBOARD_H_
#define DB_HMI_GUI_ALPKEYBOARD_H_

#include <QWidget>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QDebug>
#include "windows.h"

enum ChangeType
{
    NO_CHANGE,      //不变化
    NUM_CHANGE,     //数字变化
    LETTER_CHANGE,  //字母变化
};
//#include "KeyBoard/numkeyboard.h"

//namespace Ui {
//class AlpKeyboard;
//}

class QPushButton;
class DB_Hmi_Gui_AlpKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit DB_Hmi_Gui_AlpKeyboard(QWidget *parent = 0);
    ~DB_Hmi_Gui_AlpKeyboard();
    void Alp_Upper();
    void Alp_Lower();
    void ShiftClickedButtonText();
    void ShiftUnClickedButtonText();
    bool GetCapsButtonStatus();
    void CheckCapsButtonClicked();
    void CheckShiftButtonClicked();
    void ShowAndUpdataPos();
    void SendWarrning();

signals:
    void AlpClose();
    void AlpToNum();

    void Key_Cap();
    void Key_SHIFT();
    //长亮Cap
    void CapLight(bool);
    //长亮SHIFT
    void ShiftLight(bool);
    //长亮ALT
    void AltLight(bool);
    //长亮Ctrl
    void CrtlLight(bool);

    //提示是否大小写
    void UpdateWarrning(bool);

protected:
    void closeEvent(QCloseEvent *);
#if 0
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
#endif

protected slots:
    void ButtonsClickSlot(int key);
    void LShiftButtonClickSlot();
    void CtrlButtonClickSlot();
    void AltButtonClickSlot();
    void CapsButtonClickSlot();
    void NumKeyBoardShow();
    void CloseButtonSlot();

private:
    QWidget* InitWidget();
    QPushButton* Get_Button(QString text,QString Change_Text,QString style,int key,ChangeType = NO_CHANGE);

private:
    bool isCap =false;
    bool isShift = false;
    bool isCtrl = false;
    bool isAlt = false;
    //bool isLShiftPressed,isCtrlPressed,isRShiftPressed,isAltPressed,isCapsPressed;
};

#endif // DB_HMI_GUI_ALPKEYBOARD_H_
