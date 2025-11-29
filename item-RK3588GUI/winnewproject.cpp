#include "winnewproject.h"
#include "ui_winnewproject.h"

#include <QDir>
#include <QMessageBox>


extern bool g_createNewType;

WinNewProject::WinNewProject(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WinNewProject)
{
    ui->setupUi(this);
    this->setWindowTitle("新建");
    // 初始化窗口
    this->setFixedSize(this->width(),this->height());   // 固定窗口大小
}

WinNewProject::~WinNewProject()
{
    delete ui;
}

void WinNewProject::createNewProjectDir()
{
    QString folderPath = ui->lineEdit->text();
    folderPath = "./project/" + folderPath;
    projectPath = folderPath+"/";
    QDir dir;
    // 判断 project/
    if (!dir.exists("./project"))
    {
        if (dir.mkdir("./project"))
        {
            qDebug() << "文件夹" << "project/" << "创建成功！";
        } else {
            qDebug() << "文件夹" << "project/" << "创建失败！";
        }
    }
    if (!dir.exists(folderPath)) {
        if (dir.mkdir(folderPath)) {
            qDebug() << "文件夹" << folderPath << "创建成功！";
            emit getNewProjectPath(projectPath);
        } else {
            QMessageBox msg;
            msg.setWindowTitle(" ");
            msg.setText("文件夹"+folderPath+"创建失败！   \n");
            msg.exec();
            qDebug() << "文件夹" << folderPath << "创建失败！";
        }
    } else {
        QMessageBox msg;
        msg.setWindowTitle(" ");
        msg.setText("文件夹"+folderPath+"已存在！   \n");
        msg.exec();
        emit getNewProjectPath(projectPath);
        qDebug() << "文件夹" << folderPath << "已存在！";
    }
}

void WinNewProject::createNewText()
{
    QString textPath = projectPath + ui->lineEdit->text() + ".txt";
    QFile file(textPath);

    // 打开文件（如果不存在则创建）
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Utf8);
        out << "项目地址: " + projectPath + "\n"; // 写入内容
        out << "Encoding: UTF-8\n\n";
        out << "------------------模型输入输出数据------------------\n";
        file.close();
        emit getNewTextName(ui->lineEdit->text());
        qDebug() << "文件"+textPath+"创建并写入成功！";
    } else {
        QMessageBox msg;
        msg.setWindowTitle(" ");
        msg.setText("文件夹"+ui->lineEdit->text() + ".txt"+"创建失败！   \n");
        msg.exec();
        qDebug() << "文件创建失败！";
    }
}

void WinNewProject::accept()
{
    if (g_createNewType)
    {
        createNewText();
    } else {
        createNewProjectDir();
    }
    ui->lineEdit->clear();
    QDialog::accept();
}

void WinNewProject::reject()
{
    ui->lineEdit->clear();
    QDialog::reject();
}

