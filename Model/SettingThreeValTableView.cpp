#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>

#include "SettingThreeValModelDelegate.h"
#include "SettingThreeValTableView.h"
#include <Public/Public_Str.h>

SettingThreeValTableView::SettingThreeValTableView(QStringList HorList,int TableMaxNum,int NameWidth,int TableWidth,int DefaultHeight,int TableHeight,QWidget* parent)
    :QTableView (parent),
      mHorList(HorList),
      mTableMaxNum(TableMaxNum),
      mNameWidth(NameWidth),
      mTableWidth(TableWidth),
      mDefaultHeight(DefaultHeight),
      mTableHeight(TableHeight)

{
    // Model
    tableModel = new SettingThreeValTableModel(mTableMaxNum);
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new SettingThreeValModelDelegate;
    this->setItemDelegate(tableDelegate);

//    QStringList msg;
//    msg << " " << mHorList.at(1) << mHorList.at(2) << mHorList.at(3);
    tableModel->setHorizontalHeaderList(HorList);
    //显示子网格
    this->setShowGrid(true);
    //取消进度条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置宽度
    this->verticalHeader()->setVisible(false);
    this->setColumnWidth(0,mNameWidth);
    this->setColumnWidth(1,mTableWidth);
    this->setColumnWidth(2,mTableWidth);
    this->setColumnWidth(3,mTableWidth);
    //禁止拖拽
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    this->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    this->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
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

    this->connect(tableModel,&SettingThreeValTableModel::ModityData,this,&SettingThreeValTableView::TableModityData);
}

SettingThreeValTableView::SettingThreeValTableView(QWidget* parent/* = nullptr*/)
{

}

SettingThreeValTableView::~SettingThreeValTableView()
{

}


void SettingThreeValTableView::Set_Model_Data(QList<QStringList> data)
{
    tableModel->PushBackData(data);
}

