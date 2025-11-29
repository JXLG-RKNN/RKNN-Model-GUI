#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <winnewproject.h>
#include "mylineedit.h"
#include "winoptions.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

extern int g_curPageIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 更新页面显示控件
    void updatePageEdit();


private slots:
    // 视图--工具栏
    void on_action_ToolBar_triggered(bool checked);
    // 视图--控件栏
    void on_action_Object_triggered(bool checked);
    // 选项设置
    void on_action_Options_triggered();

    void on_action_NewProject_triggered();

    void on_action_NewFile_triggered();

    void on_action_NewProject_ToolBar_triggered();

    void on_action_NewFile_ToolBar_triggered();
    // 新建文本文件控件栏按钮
    void createNewTextButton(QString textName);

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<MyLineEdit*>> mInputList;  // 输入
    std::vector<std::vector<MyLineEdit*>> mOutputList;  // 输出

    std::vector<QPushButton*> btnList;   // 页面按钮列表

    QString projectPath; // 项目地址

    // 新窗口成员
    std::unique_ptr<WinOptions> winOptions;
    std::unique_ptr<WinNewProject> winNewProject;
};
#endif // MAINWINDOW_H
