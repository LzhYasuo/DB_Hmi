#ifndef DB_HMI_GUI_NUMKEYBOARD_H_
#define DB_HMI_GUI_NUMKEYBOARD_H_

#include <QWidget>
#include <QButtonGroup>
#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPointer>
#include "windows.h"
#include "DB_Hmi_Gui_Alpkeyboard.h"

//namespace Ui {
//class NumKeyboard;
//}

class QPushButton;
class DB_Hmi_Gui_Numkeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit DB_Hmi_Gui_Numkeyboard(QWidget *parent = 0);
    ~DB_Hmi_Gui_Numkeyboard();
    void UpdatePos();
    void ShowAndUpdatePos();
    void selectAllText();

private:
    QWidget* InitWidget();
    QPushButton* Get_Button(QString text,QString style,int key);


protected slots:
    void ButtonsClickedSlot(int key);
    void NumKeyboardClose();
    void AlpKeyBoardShow();
    void AlpKeyBoardClose();
    void AlpToNumSLot();

private:
    QButtonGroup *ButtonGroup;
    bool AlpKeyShow;

};

#endif // DB_HMI_GUI_NUMKEYBOARD_H_
