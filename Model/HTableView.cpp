#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>

#include "HModelDelegate.h"
#include "HTableView.h"
#include <Public/Public_Str.h>

HTableView::HTableView(QWidget* parent/* = nullptr*/)
{
    // Model
    tableModel = new HTableModel();
    this->setModel(tableModel);
    // Delegate
    HTableDelegate* tableDelegate = new HTableDelegate;
    this->setItemDelegate(tableDelegate);

    View_Init();
}

HTableView::~HTableView()
{

}

void HTableView::Clear_All()
{
    tableModel->Clear_Table_Data();
}

QList<QStringList> HTableView::Get_Value()
{
    return tableModel->ListPopBack();
}

void HTableView::View_Init()
{
    QStringList header;
    header << "" << "1" << "2";
    tableModel->setHorizontalHeaderList(header);
    //显示子网格
    this->setShowGrid(true);
    //取消进度条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置宽度
    this->verticalHeader()->setVisible(false);
    this->setColumnWidth(0,50);
    this->setColumnWidth(1,100);
    this->setColumnWidth(2,100);
    //禁止拖拽
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    this->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    //设置默认高度
    this->verticalHeader()->setDefaultSectionSize(30);
    //设置表头高度
    this->horizontalHeader()->setFixedHeight(30);
    //设置行列表头无法点击
    this->setCornerButtonEnabled(false);
    this->horizontalHeader()->setSectionsClickable(false);
    this->verticalHeader()->setSectionsClickable(false);
    //样式表
    const QString headStyle = Public_Str::Get_Sty(Style_Css{SystemPageTableHead,{}});
    this->setStyleSheet("border:none;");
    this->horizontalHeader()->setStyleSheet(headStyle);
    this->setStyleSheet("background-color:rgb(255,255,255);"
                        "border:none;");

}
