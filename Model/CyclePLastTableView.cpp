#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>

#include "CyclePLastModelDelegate.h"
#include "CyclePLastTableView.h"
#include <Public/Public_Str.h>

CyclePLastTableView::CyclePLastTableView(QWidget* parent/* = nullptr*/)
{
    // Model
    tableModel = new CyClePLastTableModel();
    this->setModel(tableModel);
    // Delegate
    CyClePLastTableDelegate* tableDelegate = new CyClePLastTableDelegate;
    this->setItemDelegate(tableDelegate);

    View_Init();
}

CyclePLastTableView::~CyclePLastTableView()
{

}

void CyclePLastTableView::Clear_All()
{
    tableModel->Clear_Table_Data();
}

void CyclePLastTableView::Set_Value(QList<QStringList> msg)
{
    tableModel->PushBackData(msg);
}

QList<QStringList> CyclePLastTableView::Get_Value()
{
    return tableModel->PopBackData();
}

void CyclePLastTableView::View_Init()
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

    connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
}

void CyclePLastTableView::onTableClicked(const QModelIndex &index)
{
//    qDebug() << index.row();
}
