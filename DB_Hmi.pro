#-------------------------------------------------
#
# Project created by QtCreator 2021-01-07T13:09:03
#
#-------------------------------------------------

QT       += opengl core gui network sql concurrent


win32:LIBS += -lOpengl32 \
                -lglu32 \
                -lglut32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DB_Hmi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        GUI/DB_Hmi.cpp \
    Public/Public_Control.cpp \
    Public/Public_Function.cpp \
    Public/Public_Str.cpp \
    Public/Public_Var.cpp \
    GUI/DB_Hmi_Gui_Auto_Manual.cpp \
    GUI/DB_Hmi_Gui_Main_Body.cpp \
    GUI/DB_Hmi_Gui_Data.cpp \
    GUI/DB_Hmi_Gui_Setting.cpp \
    GUI/DB_Hmi_Gui_System.cpp \
    GUI/DB_Hmi_Gui_Data_AddLine.cpp \
    Ini_Dbdata/DataDbdata.cpp \
    Ini_Dbdata/DataSetting.cpp \
    Ini_Dbdata/Data_SettingDbData.cpp \
    GUI/DB_Hmi_Gui_Data_SubLine.cpp \
    GUI/DB_Hmi_Gui_System_Io.cpp \
    Model/CyclePLastModelDelegate.cpp \
    Model/CyclePLastTableView.cpp \
    Model/CyclePLessModelDelegate.cpp \
    Model/CyclePLessTableView.cpp \
    Model/CyclePMoreModelDelegate.cpp \
    Model/CyclePMoreTableView.cpp \
    Model/DModelDelegate.cpp \
    Model/DTableView.cpp \
    Model/GModelDelegate.cpp \
    Model/GTableView.cpp \
    Model/HModelDelegate.cpp \
    Model/HTableView.cpp \
    Model/SettingFourValModelDelegate.cpp \
    Model/SettingFourValTableView.cpp \
    Model/SettingOneValModelDelegate.cpp \
    Model/SettingOneValTableView.cpp \
    Model/SettingThreeValModelDelegate.cpp \
    Model/SettingThreeValTableView.cpp \
    Model/SettingTwoValModelDelegate.cpp \
    Model/SettingTwoValTableView.cpp \
    GUI/DB_Hmi_Gui_Setting_Conf.cpp \
    Ini_Dbdata/SettingIni.cpp \
    Ini_Dbdata/Setting_Data.cpp \
    Socket/RunTcp.cpp \
    Socket/Tcp_Accept_Thread.cpp \
    Socket/Tcp_Send_Thread.cpp \
    Socket/TcpSocket.cpp \
    GUI/DB_Hmi_Gui_Alpkeyboard.cpp \
    GUI/DB_Hmi_Gui_Passwd.cpp \
    GUI/DB_Hmi_Gui_Change_Passwd.cpp \
    GUI/DB_Hmi_Gui_NumKeyBoard.cpp \
    GUI/DB_Hmi_Gui_3D.cpp \
    2D3D/analyzegcode.cpp \
    2D3D/glwidget.cpp \
    2D3D/vscreen.cpp

HEADERS += \
        GUI/DB_Hmi.h \
    Public/Public_Control.h \
    Public/Public_Function.h \
    Public/Public_Str.h \
    Public/Public_Var.h \
    GUI/DB_Hmi_Gui_Auto_Manual.h \
    GUI/DB_Hmi_Gui_Main_Body.h \
    GUI/DB_Hmi_Gui_Data.h \
    GUI/DB_Hmi_Gui_Setting.h \
    GUI/DB_Hmi_Gui_System.h \
    GUI/DB_Hmi_Gui_Data_AddLine.h \
    Ini_Dbdata/DataDbdata.h \
    Ini_Dbdata/DataSetting.h \
    Ini_Dbdata/Data_SettingDbData.h \
    GUI/DB_Hmi_Gui_Data_SubLine.h \
    GUI/DB_Hmi_Gui_System_Io.h \
    Model/CyclePLastModelDelegate.h \
    Model/CyclePLastTableView.h \
    Model/CyclePLessModelDelegate.h \
    Model/CyclePLessTableView.h \
    Model/CyclePMoreModelDelegate.h \
    Model/CyclePMoreTableView.h \
    Model/DModelDelegate.h \
    Model/DTableView.h \
    Model/GModelDelegate.h \
    Model/GTableView.h \
    Model/HModelDelegate.h \
    Model/HTableView.h \
    Model/SettingFourValModelDelegate.h \
    Model/SettingFourValTableView.h \
    Model/SettingOneValModelDelegate.h \
    Model/SettingOneValTableView.h \
    Model/SettingThreeValModelDelegate.h \
    Model/SettingThreeValTableView.h \
    Model/SettingTwoValModelDelegate.h \
    Model/SettingTwoValTableView.h \
    GUI/DB_Hmi_Gui_Setting_Conf.h \
    Ini_Dbdata/SettingIni.h \
    Ini_Dbdata/Setting_Data.h \
    Socket/RunTcp.h \
    Socket/Tcp_Accept_Thread.h \
    Socket/Tcp_Send_Thread.h \
    Socket/TcpSocket.h \
    GUI/DB_Hmi_Gui_Alpkeyboard.h \
    GUI/DB_Hmi_Gui_Passwd.h \
    GUI/DB_Hmi_Gui_Change_Passwd.h \
    GUI/DB_Hmi_Gui_NumKeyBoard.h \
    GUI/DB_Hmi_Gui_3D.h \
    2D3D/analyzegcode.h \
    2D3D/glwidget.h \
    2D3D/vscreen.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
