#ifndef LABELEDIT_H
#define LABELEDIT_H

#include <QLineEdit>

#include <QMouseEvent>

class LabelEdit : public QLineEdit
{
    Q_OBJECT
public:
    LabelEdit();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void sendPressed();
    void sendDoublePressed();
    void sendReleased();
    void sendMove();

private:
    bool isLPress;   // 左键是否按下
};

#endif // LABELEDIT_H
