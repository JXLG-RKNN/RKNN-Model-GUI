#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QSpinBox>
#include "labeledit.h"

class MyLineEdit : public QWidget
{
    Q_OBJECT;

public:
    MyLineEdit();

    // 设置label文本
    void setLabelText(QString label);
    // 设置输入文本
    void setLineText(QString text);
    // 设置只读
    void setReadOnly(bool ro);

    // 获取label文本
    QString getLabelText();
    // 获取LineEdit文本
    QString getLineText();
    // 获取SpinBox文本
    QString getLayoutText();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void mousePressed();
    void mouseReleased();
    void mouseMove();

signals:
    void sendSelf(MyLineEdit *w);

private:
    bool isLPress;   // 左键是否按下
    QPoint startP;   // 移动前距离窗口的位置
    QPoint yuanP;    // 移动前距离屏幕的位置

public:
    LabelEdit labelEdit;  // 标签
    QSpinBox numSpinBox;  // 层级
    QLineEdit lineEdit;   // 输入文本
};

#endif // MYLINEEDIT_H
