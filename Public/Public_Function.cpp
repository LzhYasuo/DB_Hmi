#include "Public_Function.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QTranslator>
#include <QTextCodec>
#include <QThread>
#include <QProcess>
#include <QSettings>
#include <QFileDialog>
#include <QTimer>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>
#include <QLineEdit>
#include <QProgressBar>
#include <QRadioButton>
#include <QPainter>

Public_Function::Public_Function(QWidget *parent)
    : QWidget(parent)
{
}

Public_Function::~Public_Function()
{

}

char Public_Function::convertCharToHex(char ch)
{
    /*
    0x30等于十进制的48，48也是0的ASCII值，，
    1-9的ASCII值是49-57，，所以某一个值－0x30，，
    就是将字符0-9转换为0-9

    */
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}

void Public_Function::convertStringToHex(const QString &str, QByteArray &byteData)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    byteData.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = convertCharToHex(hstr);
        lowhexdata = convertCharToHex(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        byteData[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    byteData.resize(hexdatalen);
}

QString Public_Function::GetAddString(QString s)
{
    if((s.indexOf("+") > -1) || (s.indexOf("-") > -1))
        return s;
    else if(s.indexOf("+") == -1 && s.indexOf("-") == -1)
    {
        if(s.toDouble() > 0.00000)
        {
            s = "+" + s;
        }
        else
            s = "-" + s;

        return s;
    }
    else
        return s;
}

bool Public_Function::Contrast_List_Str(QStringList list,QString str)
{
    for(int i = 0; i < list.count(); i++)
    {
        if(list.at(i) == str)
        {
            return false;
        }
    }
    return true;
}

bool Public_Function::removeListSize(QList<QStringList> str)
{
    for(int i = 0; i < str.size(); i++)
    {
        for(int k = i + 1; k < str.size(); k++)
        {
            if(str.at(i).size() != str.at(k).size())
            {
                qDebug() << str.at(k);
                qDebug() << str.at(i).size() << str.at(k).size() << i << k;
                return false;
            }
        }
    }
    return true;
}

bool Public_Function::removeListSame(QStringList *list)
{
    for (int i = 0; i < list->count(); i++)
    {
        for (int k = i + 1; k <  list->count(); k++)
        {
            if ( list->at(i) ==  list->at(k))
            {
                return false;
            }
        }
    }
    return true;
}


QString Public_Function::CovFileSize( const uint64_t &unSize )
{
    QString sSize;
    double fSize = unSize * 1.0;
    if(fSize < 1024)//byte
    {
        sSize = QString("%1").sprintf("%.2f B", fSize);
    }
    else if( fSize >= 1024 && fSize < 1024*1024 )//kb
    {
        fSize = fSize/1024;
        sSize = QString("%1").sprintf("%.2f KB", fSize);
    }
    else if( fSize >= 1024*1024 && fSize < 1024*1024*1024)//mb
    {
        fSize = fSize/1024/1024;
        sSize = QString("%1").sprintf("%.2f MB", fSize);
    }
    else if( fSize >= 1024*1024*1024 && fSize < 1024 * 1024 * 1024 * 1024 )//gb
    {
        fSize = fSize/1024/1024/1024;
        sSize = QString("%1").sprintf("%.2f GB", fSize);
    }
    else{
        fSize = fSize/1024/1024/1024/1024;
        sSize = QString("%1").sprintf("%.2f TB", fSize);
    }
    return sSize;
}

//返回桌面宽度
int Public_Function::deskWidth()
{
    static int width;
    if(width == 0)
        width = qApp->desktop()->availableGeometry().width();

    return width;
}

//返回桌面高度
int Public_Function::deskHeight()
{
    static int height;
    if(height == 0)
        height = qApp->desktop()->availableGeometry().height();

    return height;
}

//返回程序文件名称
QString Public_Function::appName()
{
    static QString name;
    if(name.isEmpty())
    {
        name = qApp->applicationName();
        QStringList list = name.split("/");
        name = list.at(list.count() - 1).split(".").at(0);
    }
    return name;
}

//返回程序当前所在路径
QString Public_Function::appPath()
{
    //如果定义在Android下面
#ifdef Q_OS_ANDROID
    return QString("/sdcard/Android/%1").arg(appName());
#else
    return qApp->applicationDirPath();
#endif
}

//初始化随机数种子
void Public_Function::initRand()
{
    QTime t = QTime::currentTime();
    //msec 返回毫秒部分(0到999)的时间。
    //返回时间的第二部分(0到59)。
    qsrand(t.msec() + t.second() * 1000);
}

//初始化数据库
void Public_Function::initDb(const QString &dbName)
{
    initFile(QString(":/%1.db").arg(appName()), dbName);
}

//初始化文件,不存在则拷贝
void Public_Function::initFile(const QString &sourceName, const QString &targetName)
{
    QFile file(targetName);
    if (!file.exists() || file.size() == 0)
    {
        file.remove();
        Public_Function::copyFile(sourceName, targetName);
    }
}

//新建目录
void Public_Function::newDir(const QString &dirName)
{
    QString strDir = dirName;
    //如果路径中包含斜杠字符则说明是绝对路径
    //linux系统路径字符带有 /  windows系统 路径字符带有 :/
    if(!strDir.startsWith("/") && !strDir.contains(":/"))
        strDir = QString("%1/%2").arg(Public_Function::appPath()).arg(strDir);

    QDir dir(strDir);
    if (!dir.exists())
        dir.mkpath(strDir);
}

//写入消息到额外的的消息日志文件
void Public_Function::writeInfo(const QString &info, bool needWrite, const QString &filePath,const QString &FileName)
{
    if(!needWrite)
        return;

    QString fileName = QString("%1/%2%3_%4reinfo.txt")
            .arg(Public_Function::appPath()).arg(filePath).arg(Public_Function::appName()).arg(FileName)/*.arg(QDate::currentDate().toString())*/;

    QFile File(fileName);
    if(File.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text))
    {
        QTextStream stream(&File);
        stream << "\n" << QDateTime::currentDateTime().toString() << " " << info;
        File.close();
    }

}
void Public_Function::writeError(const QString &info, bool needWrite, const QString &filePath,const QString &FileName)
{
    if(!needWrite)
        return;
    QString fileName = QString("%1/%2%3_%4reerror.txt")
            .arg(Public_Function::appPath()).arg(filePath).arg(Public_Function::appName()).arg(FileName)/*.arg(QDate::currentDate().toString())*/;

    QFile File(fileName);
    if(File.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text))
    {
        QTextStream stream(&File);
        stream << "\n" << QDateTime::currentDateTime().toString() << " " << info;
        File.close();
    }
}

//设置无边框窗体
void Public_Function::setFramelessForm(QWidget *widgetMain, QWidget *widgetTitle, QLabel *labIco, QPushButton *btnClose, bool tool)
{
    //    labIco->setFixedWidth(TitleMinSize);
    //    btnClose->setFixedWidth(TitleMinSize);
}

//九宫格图片 horzSplit-宫格1/3/7/9宽度  vertSplit-宫格1/3/7/9高度  dstWidth-目标图片宽度  dstHeight-目标图片高度
QPixmap Public_Function::ninePatch(const QString &picName, int horzSplit, int vertSplit, int dstWidth, int dstHeight)
{
    QPixmap pix(picName);
    ninePatch(pix,horzSplit,vertSplit,dstWidth,dstHeight);

    return pix;
}

//九宫格图片 horzSplit-宫格1/3/7/9宽度  vertSplit-宫格1/3/7/9高度  dstWidth-目标图片宽度  dstHeight-目标图片高度
QPixmap Public_Function::ninePatch(const QPixmap &pix, int horzSplit, int vertSplit, int dstWidth, int dstHeight)
{
    int pixWidth = pix.width();
    int pixHeight = pix.height();

    QPixmap pix1 = pix.copy(0, 0, horzSplit, vertSplit);
    QPixmap pix2 = pix.copy(horzSplit, 0, pixWidth - horzSplit * 2, vertSplit);
    QPixmap pix3 = pix.copy(pixWidth - horzSplit, 0, horzSplit, vertSplit);

    QPixmap pix4 = pix.copy(0, vertSplit, horzSplit, pixHeight - vertSplit * 2);
    QPixmap pix5 = pix.copy(horzSplit, vertSplit, pixWidth - horzSplit * 2, pixHeight - vertSplit * 2);
    QPixmap pix6 = pix.copy(pixWidth - horzSplit, vertSplit, horzSplit, pixHeight - vertSplit * 2);

    QPixmap pix7 = pix.copy(0, pixHeight - vertSplit, horzSplit, vertSplit);
    QPixmap pix8 = pix.copy(horzSplit, pixHeight - vertSplit, pixWidth - horzSplit * 2, pixWidth - horzSplit * 2);
    QPixmap pix9 = pix.copy(pixWidth - horzSplit, pixHeight - vertSplit, horzSplit, vertSplit);

    //保持高度拉宽
    pix2 = pix2.scaled(dstWidth - horzSplit * 2, vertSplit, Qt::IgnoreAspectRatio);
    //保持宽度拉高
    pix4 = pix4.scaled(horzSplit, dstHeight - vertSplit * 2, Qt::IgnoreAspectRatio);
    //宽高都缩放
    pix5 = pix5.scaled(dstWidth - horzSplit * 2, dstHeight - vertSplit * 2, Qt::IgnoreAspectRatio);
    //保持宽度拉高
    pix6 = pix6.scaled(horzSplit, dstHeight - vertSplit * 2, Qt::IgnoreAspectRatio);
    //保持高度拉宽
    pix8 = pix8.scaled(dstWidth - horzSplit * 2, vertSplit);

    QPixmap resultImg(dstWidth, dstHeight);
    resultImg.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&resultImg);
    if (!resultImg.isNull()) {
        painter.drawPixmap(0, 0, pix1);
        painter.drawPixmap(horzSplit, 0, pix2);
        painter.drawPixmap(dstWidth - horzSplit, 0, pix3);

        painter.drawPixmap(0, vertSplit, pix4);
        painter.drawPixmap(horzSplit, vertSplit, pix5);
        painter.drawPixmap(dstWidth - horzSplit, vertSplit, pix6);

        painter.drawPixmap(0, dstHeight - vertSplit, pix7);
        painter.drawPixmap(horzSplit, dstHeight - vertSplit, pix8);
        painter.drawPixmap(dstWidth - horzSplit, dstHeight - vertSplit, pix9);
    }
    painter.end();
    return resultImg;
}

//设置标签颜色
void Public_Function::setLabStyle(QLabel *lab, quint8 type, const QString &bgColor, const QString &textColor)
{
    QString colorBg = bgColor;
    QString colorText = textColor;

    //如果设置了新颜色则启用新颜色
    if (bgColor.isEmpty() || textColor.isEmpty()) {
        if (type == 0) {
            colorBg = "#D64D54";
            colorText = "#FFFFFF";
        } else if (type == 1) {
            colorBg = "#17A086";
            colorText = "#FFFFFF";
        } else if (type == 2) {
            colorBg = "#47A4E9";
            colorText = "#FFFFFF";
        } else if (type == 3) {
            colorBg = "#282D30";
            colorText = "#FFFFFF";
        } else if (type == 4) {
            colorBg = "#0E99A0";
            colorText = "#FFFFFF";
        } else if (type == 5) {
            colorBg = "#A279C5";
            colorText = "#FFFFFF";
        } else if (type == 6) {
            colorBg = "#8C2957";
            colorText = "#FFFFFF";
        } else if (type == 7) {
            colorBg = "#04567E";
            colorText = "#FFFFFF";
        } else if (type == 8) {
            colorBg = "#FD8B28";
            colorText = "#FFFFFF";
        } else if (type == 9) {
            colorBg = "#5580A2";
            colorText = "#FFFFFF";
        }
    }

    QStringList qss;
    //禁用颜色
    //    qss << QString("QLabel::disabled{background:none;color:%1;}").arg(Public_Function::BorderColor);
    //正常颜色
    qss << QString("QLabel{border:none;background-color:%1;color:%2;}").arg(colorBg).arg(colorText);
    lab->setStyleSheet(qss.join(""));
}

//设置窗体居中显示
void Public_Function::setFormInCenter(QWidget *frm)
{
    int frmW = frm->width();
    int frmH = frm->height();
    QDesktopWidget w;
    int deskWidth = w.availableGeometry().width();
    int deskHeight = w.availableGeometry().height();
    QPoint pos((deskWidth - frmW) / 2,(deskHeight - frmH) / 2);
    frm->move(pos);
}

//设置翻译文件
void Public_Function::setTranslator(const QString &qmFile)
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(qmFile);
    qApp->installTranslator(translator);
}

//设置编码
void Public_Function::setCode()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec* codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
}

//设置延时
void Public_Function::sleep(int msec)
{
    if (msec > 0)
    {
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
        QTime endTime = QTime::currentTime().addMSecs(msec);
        while (QTime::currentTime() < endTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
#else
        QThread::msleep(msec);
#endif

    }
}
//设置系统时间
void Public_Function::setSystemDateTime(const QString &year, const QString &month, const QString &day,
                                        const QString &hour, const QString &min, const QString &sec)
{
#ifdef Q_OS_WIN
    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
#else
    QString cmd = QString("date %1%2%3%4%5.%6").arg(month).arg(day).arg(hour).arg(min).arg(year).arg(sec);
    system(cmd.toLatin1());
    system("hwclock -w");
#endif
}

//设置开机自启动
void Public_Function::runWithSystem(const QString &strName, const QString &strPath, bool autoRun)
{
#ifdef Q_OS_WIN
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    reg.setValue(strName, autoRun ? strPath : "");
#endif
}

//判断是否是IP地址
bool Public_Function::isIP(const QString &ip)
{
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(ip);
}

//判断是否是MAC地址
bool Public_Function::isMac(const QString &mac)
{
    QRegExp RegExp("^[A-F0-9]{2}(-[A-F0-9]{2}){5}$");
    return RegExp.exactMatch(mac);
}

//判断是否是合法的电话号码
bool Public_Function::isTel(const QString &tel)
{
    if (tel.length() != 11)
        return false;

    if (!tel.startsWith("13") && !tel.startsWith("14") && !tel.startsWith("15") && !tel.startsWith("18"))
        return false;

    return true;
}

//判断是否是合法的邮箱地址
bool Public_Function::isEmail(const QString &email)
{
    if (!email.contains("@") || !email.contains(".com"))
        return false;
    return true;
}

//16进制字符串转10进制
int Public_Function::strHexToDecimal(const QString &strHex)
{
    bool ok;
    return strHex.toInt(&ok,16);
}

//10进制字符串转10进制
int Public_Function::strDecimalToDecimal(const QString &strDecimal)
{
    bool ok;
    return strDecimal.toInt(&ok,10);
}

//2进制字符串转10进制
int Public_Function::strBinToDecimal(const QString &strBin)
{
    bool ok;
    return strBin.toInt(&ok,2);
}

//16进制字符串转2进制字符串
QString Public_Function::strHexToStrBin(const QString &strHex)
{
    uchar deciml = strHexToDecimal(strHex);
    QString bin = QString::number(deciml,2);
    uchar len = bin.length();

    if(len < 8)
        for(int i = 0; i < 8 - len; i++)
            bin = "0" + bin;

    return bin;
}
//10进制转2进制字符串一个字节
QString Public_Function::decimalToStrBin1(int decimal)
{
    QString bin = QString::number(decimal,2);
    uchar len = bin.length();

    //一个字节8位
    if(len < 8)
        for(int i = 0; i < 8 - len; i++)
            bin = "0" + bin;

    return bin;

}
//10进制转2进制字符串两个字节
QString Public_Function::decimalToStrBin2(int decimal)
{
    QString bin = QString::number(decimal,2);
    uchar len = bin.length();

    if(len < 8)
        for(int i = 0; i < 16 - len; i++)
            bin = "0" + bin;

    return bin;
}
//10进制转16进制字符串,补零.
QString Public_Function::decimalToStrHex(int decimal)
{
    QString bin = QString::number(decimal,16);
    if (bin.length() == 1)
        bin = "0" + bin;
    return bin;
}

//int转字节数组
QByteArray Public_Function::intToByte(int i)
{
    QByteArray result;
    result.resize(4);
    result[3] = (uchar)(0x000000ff & i);
    result[2] = (uchar)((0x0000ff00 & i) >> 8);
    result[1] = (uchar)((0x00ff0000 & i) >> 16);
    result[0] = (uchar)((0xff000000 & i) >> 24);
    return result;
}

//int转字节数组
QByteArray Public_Function::intToByteRec(int i)
{
    QByteArray result;
    result.resize(4);
    result[0] = (uchar)(0x000000ff & i);
    result[1] = (uchar)((0x0000ff00 & i) >> 8);
    result[2] = (uchar)((0x00ff0000 & i) >> 16);
    result[3] = (uchar)((0xff000000 & i) >> 24);
    return result;
}

//字节数组转int
int Public_Function::byteToInt(const QByteArray &data)
{
    int i = data.at(3) & 0x000000ff;
    i |= ((data.at(2) << 8) & 0x0000ff00);
    i |= ((data.at(1) << 16) & 0x00ff0000);
    i |= ((data.at(0) << 24) & 0xff000000);
    return i;

}
//字节数组转int
int Public_Function::byteToIntRec(const QByteArray &data)
{
    int i = data.at(0) & 0x000000ff;
    i |= ((data.at(1) << 8) & 0x0000ff00);
    i |= ((data.at(2) << 16) & 0x00ff0000);
    i |= ((data.at(3) << 24) & 0xff000000);

    return i;
}
//字节数组转int
quint32 Public_Function::byteToUInt(const QByteArray &data)
{
    quint32 i = data.at(3) & 0x000000ff;
    i |= ((data.at(2) << 8) & 0x0000ff00);
    i |= ((data.at(1) << 16) & 0x00ff0000);
    i |= ((data.at(0) << 24) & 0xff000000);

    return i;
}
//字节数组转int
quint32 Public_Function::byteToUIntRec(const QByteArray &data)
{
    quint32 i = data.at(0) & 0x000000ff;
    i |= ((data.at(1) << 8) & 0x0000ff00);
    i |= ((data.at(2) << 16) & 0x00ff0000);
    i |= ((data.at(3) << 24) & 0xff000000);

    return i;
}

//ushort转字节数组
QByteArray Public_Function::ushortToByte(ushort i)
{
    QByteArray result;
    result.resize(2);
    result[1] = (uchar)((0x000000ff & i));
    result[0] = (uchar)((0x0000ff00 & i) << 8);
    return result;
}

//ushort转字节数组
QByteArray Public_Function::ushortToByteRec(ushort i)
{
    QByteArray result;
    result.resize(2);
    result[0] = (uchar)((0x000000ff & i));
    result[1] = (uchar)((0x0000ff00 & i) << 8);
    return result;
}

//字节数组转ushort
int Public_Function::byteToUShort(const QByteArray &data)
{
    int i = data.at(1) & 0x000000ff;
    i |= ((data.at(0) << 8) & 0x0000ff00);

    if (i >= 32768)
        i = i - 65536;
    return i;
}

//字节数组转ushort
int Public_Function::byteToUShortRec(const QByteArray &data)
{
    int i = data.at(0) & 0x000000ff;
    i |= ((data.at(1) << 8) & 0x0000ff00);

    if (i >= 32768)
        i = i - 65536;
    return i;
}

//异或加密算法
QString Public_Function::getXorEncryptDecrypt(const QString &str, char key)
{
    QByteArray data = str.toLatin1();
    int size = data.size();
    for (int i = 0; i < size; i++)
        data[i] = data[i] ^ key;

    return QLatin1String(data);
}

//异或校验
uchar Public_Function::getOrCode(const QByteArray &data)
{
    int len = data.length();
    uchar result = 0;
    for (int i = 0; i < len; i++)
        result ^= data.at(i);

    return result;
}

//计算校验码
uchar Public_Function::getCheckCode(const QByteArray &data)
{
    int len = data.length();
    uchar temp = 0;

    for (uchar i = 0; i < len; i++)
        temp += data.at(i);

    return temp % 256;
}

//获取保存的文件
QString Public_Function::getSaveName(const QString &filter, QString defaultDir)
{
    return QFileDialog::getSaveFileName(nullptr, "选择文件", defaultDir, filter);
}

//获取选择的文件
QString Public_Function::getFileName(const QString &filter, QString defaultDir)
{
    return QFileDialog::getOpenFileName(nullptr, "选择文件", defaultDir, filter);
}

//非阻塞保存文件对话框
QString Public_Function::saveFileName(const QString &filter, const QString &defaultDir, const QString &fileName)
{
    QString file;
    QFileDialog dialog;
    dialog.setFixedSize(900, 600);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setWindowTitle("保存文件");
    dialog.setLabelText(QFileDialog::Accept, "保存(&S)");
    dialog.setLabelText(QFileDialog::Reject, "取消(&C)");
    dialog.selectFile(fileName);
    dialog.setNameFilter(filter);
    dialog.setDirectory(defaultDir);

    if (dialog.exec() == 1)
    {
        file = dialog.selectedFiles().value(0);
        file = QFileInfo(file).suffix().isEmpty() ? "" : file;
    }

    return file;
}

//获取选择的文件集合
QStringList Public_Function::getFileNames(const QString &filter, QString defaultDir)
{
    return QFileDialog::getOpenFileNames(nullptr, "选择文件", defaultDir, filter);
}

//获取选择的目录
QString Public_Function::getFolderName()
{
    return QFileDialog::getExistingDirectory();
}

//获取文件名,含拓展名
QString Public_Function::getFileNameWithExtension(const QString &strFilePath)
{
    QFileInfo fileInfo(strFilePath);
    return fileInfo.fileName();
}

//获取选择文件夹中的文件
QStringList Public_Function::getFolderFileNames(const QStringList &filter)
{
    QStringList fileList;
    QString strFolder = QFileDialog::getExistingDirectory();

    if(!(strFolder.length() == 0))
    {
        QDir dir(strFolder);
        if(dir.exists())
        {
            fileList = dir.entryList(filter);
        }
    }

    return fileList;
}

//文件夹是否存在
bool Public_Function::folderIsExist(const QString &strFolder)
{
    QDir dir(strFolder);
    return dir.exists();
}

//文件是否存在
bool Public_Function::fileIsExist(const QString &strFile)
{
    QFile file(strFile);
    return file.exists();
}

//复制文件
bool Public_Function::copyFile(const QString &sourceFile, const QString &targetFile)
{
    bool ok;
    ok = QFile::copy(sourceFile,targetFile);
    //将复制过去的文件只读属性取消
    ok = QFile::setPermissions(targetFile,QFile::WriteOwner);

    return ok;
}

//删除文件夹下所有文件
void Public_Function::deleteDirectory(const QString &path)
{
    QDir dir(path);
    if(dir.exists())
        return;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();

    for(int i = 0; i < fileList.size(); i++)
    {
        QFileInfo fi = fileList.at(i);
        if(fi.isFile())
            fi.dir().remove(fi.fileName());
        else
        {
            deleteDirectory(fi.absoluteFilePath());
            dir.rmdir(fi.absoluteFilePath());
        }

    }
}
//判断IP地址及端口是否在线
bool Public_Function::ipLive(const QString &ip, int port, int timeout)
{
    //局部的事件循环,不卡主界面
    QEventLoop eventLoop;
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timer.setSingleShot(true);
    timer.start(timeout);

    QTcpSocket socket;
    connect(&socket,&QTcpSocket::connected,&eventLoop,&QEventLoop::quit);
    socket.connectToHost(ip, port);
    eventLoop.exec();
    bool ok = (socket.state() == QAbstractSocket::ConnectedState);

    return ok;
}
//获取网页所有源代码
QString Public_Function::getHtml(const QString &url)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get(QNetworkRequest(url));
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(manager,&QNetworkAccessManager::finished,&eventLoop,&QEventLoop::quit);
    eventLoop.exec();
    responseData = reply->readAll();

    return QString(responseData);
}

//获取本机公网IP地址
QString Public_Function::getNetIP(const QString &webCode)
{

}

//获取本机IP
QString Public_Function::getLocalIP()
{
    QStringList ips;
    QList<QHostAddress> addrs = QNetworkInterface::allAddresses();
    for(int i = 0; i < addrs.size(); i++)
    {
        QHostAddress addr = addrs.at(i);
        QString ip = addr.toString();
        if (Public_Function::isIP(ip))
            ips << ip;
    }
    QString ip = "127.0.0.1";
    for(int i = 0; i < ips.size(); i++)
    {
        QString str = ips.at(i);
        if(str.startsWith("192.168.1") || str.startsWith("192"))
        {
            ip = str;
            break;
        }
    }

    return ip;
}

//Url地址转为IP地址
QString Public_Function::urlToIP(const QString &url)
{
    QHostInfo host = QHostInfo::fromName(url);
    return host.addresses().at(0).toString();
}

//字符串补全
QString Public_Function::getValue(quint8 value)
{
    QString result = QString::number(value);
    if(result.length() <= 1)
        result = "0" + result;
    return result;
}

//判断是否通外网
bool Public_Function::isWebOk()
{
    //能接通百度IP说明可以通外网
    return ipLive("115.239.211.112", 80);
}

//初始化表格
void Public_Function::initTableView(QTableView *tableView, int rowHeight, bool headVisible, bool edit)
{
    //奇数偶数行颜色交替
    tableView->setAlternatingRowColors(false);
    //垂直表头是否可见
    tableView->verticalHeader()->setVisible(headVisible);
    //选中一行表头是否加粗
    tableView->horizontalHeader()->setHighlightSections(false);
    //最后一行拉伸填充
    tableView->horizontalHeader()->setStretchLastSection(true);
    //行标题最小宽度尺寸
    tableView->horizontalHeader()->setMinimumSectionSize(0);
    //行标题最大高度
    tableView->horizontalHeader()->setMaximumHeight(rowHeight);
    //默认行高
    tableView->verticalHeader()->setDefaultSectionSize(rowHeight);
    //选中时一行整体选中
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //只允许选择单个
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //表头不可单击
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    tableView->horizontalHeader()->setSectionsClickable(false);
#else
    tableView->horizontalHeader()->setClickable(false);
#endif

    //鼠标按下即进入编辑模式
    if (edit)
        tableView->setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::DoubleClicked);
    else
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//弹出消息框
void Public_Function::showMessageBoxInfo(const QString &info, int closeSec, bool exec)
{

}

//弹出错误框
void Public_Function::showMessageBoxError(const QString &info, int closeSec, bool exec)
{

}

//弹出询问框
int Public_Function::showMessageBoxQuestion(const QString &info)
{

}

//弹出右下角信息框
void Public_Function::showTipBox(const QString &title, const QString &tip, bool fullScreen,bool center, int closeSec)
{

}

//隐藏右下角信息框
void Public_Function::hideTipBox()
{

}

//弹出输入框
QString Public_Function::showInputBox(const QString &title, int type, int closeSec,
                                      const QString &placeholderText, bool pwd,
                                      const QString &defaultValue)
{

}
//弹出日期选择框
void Public_Function::showDateSelect(QString &dateStart, QString &dateEnd, const QString &format)
{

}

//设置按钮样式
QString Public_Function::setPushButtonQss(QPushButton *btn,                   //按钮对象
                                          int radius,                         //圆角半径
                                          int padding,                        //间距
                                          const QString &normalColor,         //正常颜色
                                          const QString &normalTextColor,     //文字颜色
                                          const QString &hoverColor,          //悬停颜色
                                          const QString &hoverTextColor,      //悬停文字颜色
                                          const QString &pressedColor,        //按下颜色
                                          const QString &pressedTextColor)    //按下文字颜色
{
    QStringList list;
    list.append(QString("QPushButton{border-style:none;padding:%1px;border-radius:%2px;color:%3;background:%4;}")
                .arg(padding).arg(radius).arg(normalTextColor).arg(normalColor));
    list.append(QString("QPushButton:hover{color:%1;background:%2;}")
                .arg(hoverTextColor).arg(hoverColor));
    list.append(QString("QPushButton:pressed{color:%1;background:%2;}")
                .arg(pressedTextColor).arg(pressedColor));

    QString qss = list.join("");
    btn->setStyleSheet(qss);
    return qss;
}
//设置文本框样式
QString Public_Function::setLineEditQss(QLineEdit *txt,                     //文本框对象
                                        int radius,                         //圆角半径
                                        int borderWidth,                    //边框大小
                                        const QString &normalColor,         //正常颜色
                                        const QString &focusColor)          //选中颜色
{
    QStringList list;
    list.append(QString("QLineEdit{border-style:none;padding:3px;border-radius:%1px;border:%2px solid %3;}")
                .arg(radius).arg(borderWidth).arg(normalColor));
    list.append(QString("QLineEdit:focus{border:%1px solid %2;}")
                .arg(borderWidth).arg(focusColor));

    QString qss = list.join("");
    txt->setStyleSheet(qss);
    return qss;
}
//设置进度条样式
QString Public_Function::setProgressBarQss(QProgressBar *bar,
                                           int barHeight,                   //进度条高度
                                           int barRadius,                   //进度条半径
                                           int fontSize,                    //文字字号
                                           const QString &normalColor,      //正常颜色
                                           const QString &chunkColor)       //进度颜色
{
    QStringList list;
    list.append(QString("QProgressBar{font:%1pt;background:%2;max-height:%3px;border-radius:%4px;text-align:center;border:1px solid %2;}")
                .arg(fontSize).arg(normalColor).arg(barHeight).arg(barRadius));
    list.append(QString("QProgressBar:chunk{border-radius:%2px;background-color:%1;}")
                .arg(chunkColor).arg(barRadius));

    QString qss = list.join("");
    bar->setStyleSheet(qss);
    return qss;
}
//设置滑块条样式
QString Public_Function::setSliderQss(QSlider *slider,              //滑动条对象
                            int sliderHeight,                       //滑动条高度
                            const QString &normalColor,             //正常颜色
                            const QString &grooveColor,             //滑块颜色
                            const QString &handleBorderColor,       //指示器边框颜色
                            const QString &handleColor,             //指示器颜色
                            const QString &textColor)               //文字颜色
{
    int sliderRadius = sliderHeight / 2;
    int handleSize = (sliderHeight * 3) / 2 + (sliderHeight / 5);
    int handleRadius = handleSize / 2;
    int handleOffset = handleRadius / 2;

    QStringList list;
    int handleWidth = handleSize + sliderHeight / 5 - 1;
    list.append(QString("QSlider::horizontal{min-height:%1px;color:%2;}").arg(sliderHeight * 2).arg(textColor));
    list.append(QString("QSlider::groove:horizontal{background:%1;height:%2px;border-radius:%3px;}")
                .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::add-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
                .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::sub-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
                .arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::handle:horizontal{width:%3px;margin-top:-%4px;margin-bottom:-%4px;border-radius:%5px;"
                        "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 %1,stop:0.8 %2);}")
                .arg(handleColor).arg(handleBorderColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

    //偏移一个像素
    handleWidth = handleSize + sliderHeight / 5;
    list.append(QString("QSlider::vertical{min-width:%1px;color:%2;}").arg(sliderHeight * 2).arg(textColor));
    list.append(QString("QSlider::groove:vertical{background:%1;width:%2px;border-radius:%3px;}")
                .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::add-page:vertical{background:%1;width:%2px;border-radius:%3px;}")
                .arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::sub-page:vertical{background:%1;width:%2px;border-radius:%3px;}")
                .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::handle:vertical{height:%3px;margin-left:-%4px;margin-right:-%4px;border-radius:%5px;"
                        "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 %1,stop:0.8 %2);}")
                .arg(handleColor).arg(handleBorderColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

    QString qss = list.join("");
    slider->setStyleSheet(qss);
    return qss;
}
//设置单选框样式
QString Public_Function::setRadioButtonQss(QRadioButton *rbtn,  //单选框对象
                                 int indicatorRadius,           //指示器圆角角度
                                 const QString &normalColor,    //正常颜色
                                 const QString &checkColor)     //选中颜色
{
    int indicatorWidth = indicatorRadius * 2;

    QStringList list;
    list.append(QString("QRadioButton::indicator{border-radius:%1px;width:%2px;height:%2px;}")
                .arg(indicatorRadius).arg(indicatorWidth));
    list.append(QString("QRadioButton::indicator::unchecked{background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                        "stop:0.6 #FFFFFF,stop:0.7 %1);}").arg(normalColor));
    list.append(QString("QRadioButton::indicator::checked{background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                        "stop:0 %1,stop:0.3 %1,stop:0.4 #FFFFFF,stop:0.6 #FFFFFF,stop:0.7 %1);}").arg(checkColor));

    QString qss = list.join("");
    rbtn->setStyleSheet(qss);
    return qss;
}
//设置滚动条样式
QString Public_Function::setScrollBarQss(QWidget *scroll,           //滚动条对象
                               int radius,                          //圆角角度
                               int min,                             //指示器最小长度
                               int max,                             //滚动条最大长度
                               const QString &bgColor,              //背景色
                               const QString &handleNormalColor,    //指示器正常颜色
                               const QString &handleHoverColor,     //指示器悬停颜色
                               const QString &handlePressedColor)   //指示器按下颜色
{
//滚动条离背景间隔
    int padding = 0;

    QStringList list;

    //handle:指示器,滚动条拉动部分 add-page:滚动条拉动时增加的部分 sub-page:滚动条拉动时减少的部分 add-line:递增按钮 sub-line:递减按钮

    //横向滚动条部分
    list.append(QString("QScrollBar:horizontal{background:%1;padding:%2px;border-radius:%3px;min-height:%4px;max-height:%4px;}")
                .arg(bgColor).arg(padding).arg(radius).arg(max));
    list.append(QString("QScrollBar::handle:horizontal{background:%1;min-width:%2px;border-radius:%3px;}")
                .arg(handleNormalColor).arg(min).arg(radius));
    list.append(QString("QScrollBar::handle:horizontal:hover{background:%1;}")
                .arg(handleHoverColor));
    list.append(QString("QScrollBar::handle:horizontal:pressed{background:%1;}")
                .arg(handlePressedColor));
    list.append(QString("QScrollBar::add-page:horizontal{background:none;}"));
    list.append(QString("QScrollBar::sub-page:horizontal{background:none;}"));
    list.append(QString("QScrollBar::add-line:horizontal{background:none;}"));
    list.append(QString("QScrollBar::sub-line:horizontal{background:none;}"));

    //纵向滚动条部分
    list.append(QString("QScrollBar:vertical{background:%1;padding:%2px;border-radius:%3px;min-width:%4px;max-width:%4px;}")
                .arg(bgColor).arg(padding).arg(radius).arg(max));
    list.append(QString("QScrollBar::handle:vertical{background:%1;min-height:%2px;border-radius:%3px;}")
                .arg(handleNormalColor).arg(min).arg(radius));
    list.append(QString("QScrollBar::handle:vertical:hover{background:%1;}")
                .arg(handleHoverColor));
    list.append(QString("QScrollBar::handle:vertical:pressed{background:%1;}")
                .arg(handlePressedColor));
    list.append(QString("QScrollBar::add-page:vertical{background:none;}"));
    list.append(QString("QScrollBar::sub-page:vertical{background:none;}"));
    list.append(QString("QScrollBar::add-line:vertical{background:none;}"));
    list.append(QString("QScrollBar::sub-line:vertical{background:none;}"));

    QString qss = list.join("");
    scroll->setStyleSheet(qss);
    return qss;
}
