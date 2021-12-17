#ifndef PUBLIC_FUNCTION_H
#define PUBLIC_FUNCTION_H

#include <QWidget>
#include <QCoreApplication>


class QLabel;
class QPushButton;
class QLineEdit;
class QTableView;
class QProgressBar;
class QSlider;
class QRadioButton;
class Public_Function : public QWidget
{
    Q_OBJECT

public:
    Public_Function(QWidget *parent = 0);
    ~Public_Function();

    static char convertCharToHex(char ch);
    //Char 转16进制
    static void convertStringToHex(const QString &str, QByteArray &byteData);
    //QString 转16进制
    static QString GetAddString(QString s);
    //对比QString 与 列表是否有相等
    static bool Contrast_List_Str(QStringList,QString);
    //查看QStringList中是否大小一致
    static bool removeListSize(QList<QStringList> str);
    //查看List中项有没有相等的
    static bool removeListSame(QStringList *list);
    //转化大小
    static QString CovFileSize( const uint64_t &unSize );
    //返回桌面宽度
    static int deskWidth();
    //返回桌面高度
    static int deskHeight();
    //返回程序文件名称
    static QString appName();
    //返回程序当前所在路径
    static QString appPath();
    //初始化随机数种子
    static void initRand();
    //初始化数据库
    static void initDb(const QString &dbName);
    //初始化文件,不存在则拷贝
    static void initFile(const QString &sourceName, const QString &targetName);
    //新建目录
    static void newDir(const QString &dirName);
    //写入消息到额外的的消息日志文件
    static void writeInfo(const QString &info, bool needWrite = false, const QString &filePath = "log",const QString &FileName = "");
    static void writeError(const QString &info, bool needWrite = false, const QString &filePath = "log",const QString &FileName = "");
    //设置无边框窗体
    static void setFramelessForm(QWidget *widgetMain, QWidget *widgetTitle, QLabel *labIco, QPushButton *btnClose, bool tool = true);
    //九宫格图片 horzSplit-宫格1/3/7/9宽度  vertSplit-宫格1/3/7/9高度  dstWidth-目标图片宽度  dstHeight-目标图片高度
    static QPixmap ninePatch(const QString &picName, int horzSplit, int vertSplit, int dstWidth, int dstHeight);
    static QPixmap ninePatch(const QPixmap &pix, int horzSplit, int vertSplit, int dstWidth, int dstHeight);
    //设置标签颜色
    static void setLabStyle(QLabel *lab, quint8 type, const QString &bgColor = "", const QString &textColor = "");
    //设置窗体居中显示
    static void setFormInCenter(QWidget *frm);
    //设置翻译文件
    static void setTranslator(const QString &qmFile = ":/image/qt_zh_CN.qm");
    //设置编码
    static void setCode();
    //设置延时
    static void sleep(int msec);
    //设置系统时间
    static void setSystemDateTime(const QString &year, const QString &month, const QString &day,
                                  const QString &hour, const QString &min, const QString &sec);
    //设置开机自启动
    static void runWithSystem(const QString &strName, const QString &strPath, bool autoRun = true);
    //判断是否是IP地址
    static bool isIP(const QString &ip);
    //判断是否是MAC地址
    static bool isMac(const QString &mac);
    //判断是否是合法的电话号码
    static bool isTel(const QString &tel);
    //判断是否是合法的邮箱地址
    static bool isEmail(const QString &email);
    //16进制字符串转10进制
    static int strHexToDecimal(const QString &strHex);
    //10进制字符串转10进制
    static int strDecimalToDecimal(const QString &strDecimal);
    //2进制字符串转10进制
    static int strBinToDecimal(const QString &strBin);
    //16进制字符串转2进制字符串
    static QString strHexToStrBin(const QString &strHex);
    //10进制转2进制字符串一个字节
    static QString decimalToStrBin1(int decimal);
    //10进制转2进制字符串两个字节
    static QString decimalToStrBin2(int decimal);
    //10进制转16进制字符串,补零.
    static QString decimalToStrHex(int decimal);
    //int转字节数组
    static QByteArray intToByte(int i);
    //int转字节数组
    static QByteArray intToByteRec(int i);
    //字节数组转int
    static int byteToInt(const QByteArray &data);
    //字节数组转int
    static int byteToIntRec(const QByteArray &data);
    //字节数组转int
    static quint32 byteToUInt(const QByteArray &data);
    //字节数组转int
    static quint32 byteToUIntRec(const QByteArray &data);
    //ushort转字节数组
    static QByteArray ushortToByte(ushort i);
    //ushort转字节数组
    static QByteArray ushortToByteRec(ushort i);
    //字节数组转ushort
    static int byteToUShort(const QByteArray &data);
    //字节数组转ushort
    static int byteToUShortRec(const QByteArray &data);
    //异或加密算法
    static QString getXorEncryptDecrypt(const QString &str, char key);
    //异或校验
    static uchar getOrCode(const QByteArray &data);
    //计算校验码
    static uchar getCheckCode(const QByteArray &data);
    //获取保存的文件
    static QString getSaveName(const QString &filter, QString defaultDir = QCoreApplication::applicationDirPath());
    //获取选择的文件
    static QString getFileName(const QString &filter, QString defaultDir = QCoreApplication::applicationDirPath());
    //非阻塞保存文件对话框
    static QString saveFileName(const QString &filter, const QString &defaultDir = "", const QString &fileName = "");
    //获取选择的文件集合
    static QStringList getFileNames(const QString &filter, QString defaultDir = QCoreApplication::applicationDirPath());
    //获取选择的目录
    static QString getFolderName();
    //获取文件名,含拓展名
    static QString getFileNameWithExtension(const QString &strFilePath);
    //获取选择文件夹中的文件
    static QStringList getFolderFileNames(const QStringList &filter);
    //文件夹是否存在
    static bool folderIsExist(const QString &strFolder);
    //文件是否存在
    static bool fileIsExist(const QString &strFile);
    //复制文件
    static bool copyFile(const QString &sourceFile, const QString &targetFile);
    //删除文件夹下所有文件
    static void deleteDirectory(const QString &path);
    //判断IP地址及端口是否在线
    static bool ipLive(const QString &ip, int port, int timeout = 1000);
    //获取网页所有源代码
    static QString getHtml(const QString &url);
    //获取本机公网IP地址
    static QString getNetIP(const QString &webCode);
    //获取本机IP
    static QString getLocalIP();
    //Url地址转为IP地址
    static QString urlToIP(const QString &url);
    //字符串补全
    static QString getValue(quint8 value);
    //判断是否通外网
    static bool isWebOk();
    //初始化表格
    static void initTableView(QTableView *tableView, int rowHeight = 25, bool headVisible = false, bool edit = false);
    //弹出消息框
    static void showMessageBoxInfo(const QString &info, int closeSec = 0, bool exec = false);
    //弹出错误框
    static void showMessageBoxError(const QString &info, int closeSec = 0, bool exec = false);
    //弹出询问框
    static int showMessageBoxQuestion(const QString &info);
    //弹出+隐藏右下角信息框
    static void showTipBox(const QString &title, const QString &tip, bool fullScreen = false,
                           bool center = true, int closeSec = 0);
    //隐藏右下角信息框
    static void hideTipBox();
    //弹出输入框
    static QString showInputBox(const QString &title, int type = 0, int closeSec = 0,
                                const QString &placeholderText = QString(), bool pwd = false,
                                const QString &defaultValue = QString());
    //弹出日期选择框
    static void showDateSelect(QString &dateStart, QString &dateEnd, const QString &format = "yyyy-MM-dd");
    //设置按钮样式
    static QString setPushButtonQss(QPushButton *btn,                               //按钮对象
                                    int radius = 5,                                 //圆角半径
                                    int padding = 8,                                //间距
                                    const QString &normalColor = "#34495E",         //正常颜色
                                    const QString &normalTextColor = "#FFFFFF",     //文字颜色
                                    const QString &hoverColor = "#4E6D8C",          //悬停颜色
                                    const QString &hoverTextColor = "#F0F0F0",      //悬停文字颜色
                                    const QString &pressedColor = "#2D3E50",        //按下颜色
                                    const QString &pressedTextColor = "#B8C6D1");   //按下文字颜色
    //设置文本框样式
    static QString setLineEditQss(QLineEdit *txt,                                   //文本框对象
                                  int radius = 3,                                   //圆角半径
                                  int borderWidth = 2,                              //边框大小
                                  const QString &normalColor = "#DCE4EC",           //正常颜色
                                  const QString &focusColor = "#34495E");           //选中颜色
    //设置进度条样式
    static QString setProgressBarQss(QProgressBar *bar,
                                     int barHeight = 8,                             //进度条高度
                                     int barRadius = 5,                             //进度条半径
                                     int fontSize = 9,                              //文字字号
                                     const QString &normalColor = "#E8EDF2",        //正常颜色
                                     const QString &chunkColor = "#E74C3C");        //进度颜色
    //设置滑块条样式
    static QString setSliderQss(QSlider *slider,                                    //滑动条对象
                                int sliderHeight = 8,                               //滑动条高度
                                const QString &normalColor = "#E8EDF2",             //正常颜色
                                const QString &grooveColor = "#1ABC9C",             //滑块颜色
                                const QString &handleBorderColor = "#1ABC9C",       //指示器边框颜色
                                const QString &handleColor = "#FFFFFF",             //指示器颜色
                                const QString &textColor = "#000000");              //文字颜色
    //设置单选框样式
    static QString setRadioButtonQss(QRadioButton *rbtn,                            //单选框对象
                                     int indicatorRadius = 8,                       //指示器圆角角度
                                     const QString &normalColor = "#D7DBDE",        //正常颜色
                                     const QString &checkColor = "#34495E");        //选中颜色
    //设置滚动条样式
    static QString setScrollBarQss(QWidget *scroll,                                 //滚动条对象
                                   int radius = 6,                                  //圆角角度
                                   int min = 120,                                   //指示器最小长度
                                   int max = 12,                                    //滚动条最大长度
                                   const QString &bgColor = "#606060",              //背景色
                                   const QString &handleNormalColor = "#34495E",    //指示器正常颜色
                                   const QString &handleHoverColor = "#1ABC9C",     //指示器悬停颜色
                                   const QString &handlePressedColor = "#E74C3C");  //指示器按下颜色
    //    //CRC校验
    //    static quint16 getRevCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
    //    static quint16 getCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
    //    static quint16 getModbus16(quint8 *data, int len);
    //    static QByteArray getCRCCode(const QByteArray &data);
};

#endif // PUBLIC_FUNCTION_H
