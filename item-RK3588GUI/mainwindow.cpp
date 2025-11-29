#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QMimeData>
#include <QPushButton>
#include "mywidgetdraw.h"

// 全局变量
int g_curPageIndex = 0;  // 当前页索引
bool g_createNewType = false;  // 创建文件类型 0:项目文件 1:文本文件
bool g_isDrag = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 新窗口成员初始化
    winOptions = std::make_unique<WinOptions>(this);
    winNewProject = std::make_unique<WinNewProject>(this);

    // 控件初始化设置
    ui->widget_Draw->setAcceptDrops(true);    // 开启识别拖动控件
    ui->action_ToolBar->setChecked(true);     // 初始状态开启
    ui->action_Object->setChecked(true);

    // 信号与槽函数
    connect(ui->widget_Draw, &MyWidgetDraw::sendLineEdit, [=](MyLineEdit *mEdit){
        if (mEdit->labelEdit.text() == "Input:")
            mInputList[g_curPageIndex].push_back(std::move(mEdit));
        else if (mEdit->labelEdit.text() == "Output:")
            mOutputList[g_curPageIndex].push_back(std::move(mEdit));
        connect(mEdit, &MyLineEdit::sendSelf, [=](MyLineEdit *w){
            /*将此小部件提升到父小部件堆栈的顶部*/
            w->raise();
        });
    });
    connect(winNewProject.get(), &WinNewProject::getNewProjectPath, [=](QString folderPath){
        projectPath = folderPath;
    });
    connect(winNewProject.get(), &WinNewProject::getNewTextName, this, &MainWindow::createNewTextButton);
}

MainWindow::~MainWindow()
{
    mInputList.clear();
    mOutputList.clear();
    btnList.clear();
    delete ui;
}


void MainWindow::on_action_ToolBar_triggered(bool checked)
{
    if (checked)
    {
        ui->toolBar->show();
        // 不改变绘画区控件的位置
        for (auto &edit : mInputList[g_curPageIndex])
        {
            edit->move(edit->x(), edit->y() - ui->toolBar->height());
        }
        for (auto &edit : mOutputList[g_curPageIndex])
        {
            edit->move(edit->x(), edit->y() - ui->toolBar->height());
        }
    } else
    {
        ui->toolBar->hide();
        // 不改变绘画区控件的位置
        for (auto &edit : mInputList[g_curPageIndex])
        {
            edit->move(edit->x(), edit->y() + ui->toolBar->height());
        }
        for (auto &edit : mOutputList[g_curPageIndex])
        {
            edit->move(edit->x(), edit->y() + ui->toolBar->height());
        }
    }
}


void MainWindow::on_action_Object_triggered(bool checked)
{
    if (checked)
    {
        ui->sideBar->show();
        // 不改变绘画区控件的位置
        for (auto &edit : mInputList[g_curPageIndex])
        {
            edit->move(edit->x() - ui->sideBar->width(), edit->y());
        }
        for (auto &edit : mOutputList[g_curPageIndex])
        {
            edit->move(edit->x() - ui->sideBar->width(), edit->y());
        }
    } else
    {
        ui->sideBar->hide();
        // 不改变绘画区控件的位置
        for (auto &edit : mInputList[g_curPageIndex])
        {
            edit->move(edit->x() + ui->sideBar->width(), edit->y());
        }
        for (auto &edit : mOutputList[g_curPageIndex])
        {
            edit->move(edit->x() + ui->sideBar->width(), edit->y());
        }
    }
}


void MainWindow::on_action_Options_triggered()
{
    winOptions->show();
}


void MainWindow::on_action_NewProject_triggered()
{
    g_createNewType = false;
    winNewProject->show();
}


void MainWindow::on_action_NewProject_ToolBar_triggered()
{
    on_action_NewProject_triggered();
}


void MainWindow::on_action_NewFile_triggered()
{
    if (projectPath == "")
    {
        QMessageBox msg;
        msg.setWindowTitle(" ");
        msg.setText("请先创建项目！   \n");
        msg.exec();
    } else {
        g_createNewType = true;
        winNewProject->show();
    }
}


void MainWindow::on_action_NewFile_ToolBar_triggered()
{
    on_action_NewFile_triggered();
}

void MainWindow::createNewTextButton(QString textName)
{
    g_isDrag = true;

    int pageNum = btnList.size();
    // 创建按键
    QPushButton *btn = new QPushButton(textName);
    btn->setParent(ui->widget_Page);
    btn->setFixedSize(50, ui->widget_Page->height());
    btn->move(50*pageNum, 0);
    btn->show();
    // 信号与槽
    connect(btn, &QPushButton::pressed, [=](){
        // 按钮高亮
        for (auto &btn : btnList)
        {
            btn->setStyleSheet(" ");
        }
        btn->setStyleSheet("background-color: rgb(154, 153, 150);");
        if (!(mInputList.empty() and mOutputList.empty()))
        {
            // 隐藏
            for (auto &i : mInputList[g_curPageIndex])
            {
                i->hide();
            }
            for (auto &i : mOutputList[g_curPageIndex])
            {
                i->hide();
            }
        }
        g_curPageIndex = pageNum;
        // 更新页面
        if (!(mInputList.empty() and mOutputList.empty()))
        {
            for (auto &i : mInputList[g_curPageIndex])
            {
                i->show();
            }
            for (auto &i : mOutputList[g_curPageIndex])
            {
                i->show();
            }
        }
    });
    // 高亮化
    btn->setStyleSheet("background-color: rgb(154, 153, 150);");
    for (auto &btn : btnList)
    {
        btn->setStyleSheet(" ");
    }

    if (!(mInputList.empty() and mOutputList.empty()))
    {
        // 隐藏
        for (auto &i : mInputList[g_curPageIndex])
        {
            i->hide();
        }
        for (auto &i : mOutputList[g_curPageIndex])
        {
            i->hide();
        }
    }
    // 放入列表
    g_curPageIndex = pageNum;
    btnList.push_back(std::move(btn));
    mInputList.push_back({});
    mOutputList.push_back({});
}

