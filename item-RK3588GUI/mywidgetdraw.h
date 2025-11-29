#ifndef MYWIDGETDRAW_H
#define MYWIDGETDRAW_H

#include <QWidget>
#include "mylineedit.h"

class MyWidgetDraw : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidgetDraw(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void sendLineEdit(MyLineEdit *mEdit);    // 输入端信号
};

#endif // MYWIDGETDRAW_H
