#include "mylineedit.h"

#include <QMouseEvent>
#include <QMimeData>
#include <QPainter>

MyLineEdit::MyLineEdit()
    : isLPress{ false }
{
    // w: 160 h: 25   widget -> label + lineedit
    // 设置大小
    this->setFixedSize(120, 50);

    // 绘制labelEdit
    int labelAdd = 10;
    labelEdit.setParent(this);
    labelEdit.setFixedSize(this->width()/2+labelAdd, 25);
    labelEdit.setReadOnly(true);
    labelEdit.move(this->width()/2-labelAdd,0);
    // 单击
    connect(&labelEdit, &LabelEdit::sendPressed, this, &MyLineEdit::mousePressed);
    // 双击
    connect(&labelEdit, &LabelEdit::sendDoublePressed, [=](){
        labelEdit.setReadOnly(false);
        this->isLPress = false;
    });
    // 按键释放
    connect(&labelEdit, &LabelEdit::sendReleased, this, &MyLineEdit::mouseReleased);
    // 按键移动
    connect(&labelEdit, &LabelEdit::sendMove, this, &MyLineEdit::mouseMove);

    // 绘制ComboBox
    numSpinBox.setParent(this);
    numSpinBox.setMinimum(0);
    numSpinBox.setFixedSize(this->width()/2-labelAdd, 25);
    numSpinBox.move(0, 0);

    // 绘制lineEdit
    lineEdit.setParent(this);
    lineEdit.setFixedSize(this->width(), 25);
    lineEdit.move(0, 25);
}

void MyLineEdit::setLabelText(QString label)
{
    labelEdit.setText(label);
}

void MyLineEdit::setLineText(QString text)
{
    lineEdit.setText(text);
}

void MyLineEdit::setReadOnly(bool ro)
{
    lineEdit.setReadOnly(ro);
}

QString MyLineEdit::getLabelText()
{
    return labelEdit.text();
}

QString MyLineEdit::getLineText()
{
    return lineEdit.text();
}

QString MyLineEdit::getLayoutText()
{
    return numSpinBox.text();
}

void MyLineEdit::mousePressed()
{
    startP = cursor().pos()-window()->pos();
    yuanP = this->pos();
    emit sendSelf(this);   //信号发送该控件地址
    this->isLPress = true;
    labelEdit.setReadOnly(true);
}

void MyLineEdit::mouseReleased()
{
    this->isLPress = false;
}

//移动事件
void MyLineEdit::mouseMove()
{
    QWidget *parentW = this->parentWidget();

    // 先判断是否可以移动到这里
    QPoint movPoint = yuanP+cursor().pos()-window()->pos()-startP;
    if (movPoint.x() >= 0
        and movPoint.y() >= parentW->findChild<QWidget*>("widget_Page")->height()
        and movPoint.x()+this->width() <= parentW->width()
        and movPoint.y()+this->height() <= parentW->height())
    {
        if (this->isLPress)
            this->move(movPoint);
    } else if (movPoint.x() >= 0
       and movPoint.x()+this->width() <= parentW->width())
    {
        if (this->isLPress)
            this->move(movPoint.x(), this->y());
    } else if (movPoint.y() >= parentW->findChild<QWidget*>("widget_Page")->height()
               and movPoint.y()+this->height() <= parentW->height())
    {
        if (this->isLPress)
            this->move(this->x(), movPoint.y());
    }

}

void MyLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->text() == "Input"
        or event->mimeData()->text() == "Output")
    {
        event->ignore();
    } else {
        event->accept();
    }
}

void MyLineEdit::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->text() == "Input"
        or event->mimeData()->text() == "Output")
    {
        event->ignore();
    } else {
        event->accept();
    }
}

void MyLineEdit::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->text() == "Input"
        or event->mimeData()->text() == "Output")
    {
        event->ignore();
    } else {
        event->accept();
    }
}

void MyLineEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QWidget::paintEvent(event);
}

