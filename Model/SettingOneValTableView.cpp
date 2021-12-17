#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>

#include "SettingOneValModelDelegate.h"
#include "SettingOneValTableView.h"
#include <Public/Public_Str.h>

SettingOneValTableView::SettingOneValTableView(QStringList HorList,int TableMaxNum,int NameWidth,int TableWidth,int DefaultHeight,int TableHeight,int type,QWidget* parent)
    :QTableView (parent),
      mHorList(HorList),
      mTableMaxNum(TableMaxNum),
      mNameWidth(NameWidth),
      mTableWidth(TableWidth),
      mDefaultHeight(DefaultHeight),
      mTableHeight(TableHeight),
      mType(type)

{
    // Model
    tableModel = new SettingOneValTableModel(TableMaxNum);
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new SettingOneValModelDelegate;
    this->setItemDelegate(tableDelegate);

    tableModel->setHorizontalHeaderList(mHorList);
    //显示子网格
    this->setShowGrid(true);
    //取消进度条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置宽度
    this->verticalHeader()->setVisible(false);
    this->setColumnWidth(0,mNameWidth);
    this->setColumnWidth(1,mTableWidth);
    //禁止拖拽
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    //设置默认高度
    this->verticalHeader()->setDefaultSectionSize(mDefaultHeight);
    //设置表头高度
    this->horizontalHeader()->setFixedHeight(TableHeight);
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

    this->connect(tableModel,&SettingOneValTableModel::ModityData,this,&SettingOneValTableView::TableModityData);
}

SettingOneValTableView::SettingOneValTableView(QWidget* parent/* = nullptr*/)
{

}

SettingOneValTableView::~SettingOneValTableView()
{

}

void SettingOneValTableView::Set_Model_Data(QList<QStringList> data)
{
        tableModel->PushBackData(data);
}
