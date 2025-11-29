#include "mywidgetdraw.h"
#include "QMimeData"

#include <QDragEnterEvent>

extern bool g_isDrag;

MyWidgetDraw::MyWidgetDraw(QWidget *parent)
    : QWidget{parent}
{}


void MyWidgetDraw::dragEnterEvent(QDragEnterEvent *event)
{
    if(g_isDrag and (event->mimeData()->text() == "Input"
         or event->mimeData()->text() == "Output"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MyWidgetDraw::dragMoveEvent(QDragMoveEvent *event)
{
    if(g_isDrag and (event->mimeData()->text() == "Input"
         or event->mimeData()->text() == "Output"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MyWidgetDraw::dropEvent(QDropEvent *event)
{
    // 实现拖动控件并创建
    QPoint mouseP = event->position().toPoint();
    if (g_isDrag
        and mouseP.x() >= 0
        and mouseP.y() >= 0
        and mouseP.x() <= this->width()
        and mouseP.y() <= this->height())
    {
        if(event->mimeData()->text() == "Input"
            or event->mimeData()->text() == "Output")
        {
            MyLineEdit *mLineEdit = new MyLineEdit();
            mLineEdit->setLabelText(event->mimeData()->text()+":");
            if (event->mimeData()->text() == "Output")
                mLineEdit->setReadOnly(true);
            mLineEdit->setParent(this);
            mLineEdit->show();
            mLineEdit->move(mouseP);
            emit sendLineEdit(mLineEdit);
        }
    }
}
