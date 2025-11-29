#ifndef WINNEWPROJECT_H
#define WINNEWPROJECT_H

#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class WinNewProject;
}

class WinNewProject : public QDialog
{
    Q_OBJECT

public:
    explicit WinNewProject(QWidget *parent = nullptr);
    ~WinNewProject();
    // 新建项目文件夹
    void createNewProjectDir();
    // 新建文本
    void createNewText();

signals:
    void getNewProjectPath(QString folderPath);
    void getNewTextName(QString textName);

protected:
    void accept() override;
    void reject() override;

private:
    Ui::WinNewProject *ui;
    // 文件夹路径
    QString projectPath;
};

#endif // WINNEWPROJECT_H
