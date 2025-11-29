#ifndef WINOPTIONS_H
#define WINOPTIONS_H

#include <QAbstractButton>
#include <QDialog>

struct OptionStruct
{
    std::unordered_map<int, int> pageIndexModel;  // 页面对应的模型索引
    std::vector<QString> cbModelList;  // 模型url地址列表
    OptionStruct() = default;
    ~OptionStruct() {
        pageIndexModel.clear();
        cbModelList.clear();
    }
};

extern OptionStruct g_optionStruct;
extern int g_curPageIndex;

namespace Ui {
class WinOptions;
}

class WinOptions : public QDialog
{
    Q_OBJECT

public:
    explicit WinOptions(QWidget *parent = nullptr);
    ~WinOptions();

private slots:
    void on_btn_Model_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
    void accept() override;
    void reject() override;

private:
    Ui::WinOptions *ui;

    std::vector<QString> modelList;  // 模型url地址列表
};

#endif // WINOPTIONS_H
