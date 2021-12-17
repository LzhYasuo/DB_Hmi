#include "GUI/DB_Hmi.h"
#include <QApplication>
#include <QTextCodec>
#include <windows.h>

int main(int argc, char *argv[])
{

    //设置中文编码
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("GBK");
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);
#endif

    QApplication a(argc, argv);
    DB_Hmi w;
    w.show();



    return a.exec();
}
