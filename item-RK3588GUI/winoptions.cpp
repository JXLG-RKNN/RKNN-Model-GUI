#include "winoptions.h"
#include "ui_winoptions.h"

#include <QFileDialog>
#include <QMessageBox>

OptionStruct g_optionStruct;

extern int g_curPageIndex;

WinOptions::WinOptions(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WinOptions)
{
    ui->setupUi(this);
    // 初始化窗口
    this->setFixedSize(this->width(),this->height());   // 固定窗口大小
    // 设置窗口标题
    this->setWindowTitle("选项设置   ");

}

WinOptions::~WinOptions()
{
    delete ui;
}

void WinOptions::on_btn_Model_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("打开模型文件"), "./", tr("Model Files (*.onnx *.rknn *.tflite)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (file.size() > 0)
        {
            QString temp = *(fileName.split("/").rbegin());
            ui->comboBox_Model->addItem(temp);
            // 更新当前索引
            ui->comboBox_Model->setCurrentText(temp);
            modelList.push_back(fileName);
        } else {
            QMessageBox msgBox;
            msgBox.setText("模型文件打开失败！");
            msgBox.exec();
        }
    }
}

void WinOptions::closeEvent(QCloseEvent *event)
{
    // 还原列表
    modelList = g_optionStruct.cbModelList;
    // 清除所有数据，从列表还原数据
    ui->comboBox_Model->clear();
    for (auto &i : modelList)
    {
        QString temp = *(i.split("/").rbegin());
        ui->comboBox_Model->addItem(temp);
    }
    // 还原当前数据索引
    ui->comboBox_Model->setCurrentIndex(g_optionStruct.pageIndexModel[g_curPageIndex]);

    QDialog::closeEvent(event);
}

void WinOptions::accept()
{
    // 更新数据列表
    g_optionStruct.cbModelList = modelList;
    // 更新页模型索引
    g_optionStruct.pageIndexModel[g_curPageIndex] = ui->comboBox_Model->currentIndex();

    QDialog::accept();
}

void WinOptions::reject()
{
    // 还原列表
    modelList = g_optionStruct.cbModelList;
    // 清除所有数据，从列表还原数据
    ui->comboBox_Model->clear();
    for (auto &i : modelList)
    {
        QString temp = *(i.split("/").rbegin());
        ui->comboBox_Model->addItem(temp);
    }
    // 还原当前数据索引
    ui->comboBox_Model->setCurrentIndex(g_optionStruct.pageIndexModel[g_curPageIndex]);

    QDialog::reject();
}

