#include "mytoolbutton.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>
#include <QIcon>

MyToolButton::MyToolButton(QWidget *parent)
    : QToolButton{ parent }
{
}

MyToolButton::~MyToolButton()
{

}

void MyToolButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        pressPos = event->pos();
    }

    QWidget::mousePressEvent(event);
}

void MyToolButton::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) // 左键拖拽
    {
        if ((event->pos() - pressPos).manhattanLength() >= QApplication::startDragDistance())
        {
            QMimeData* mime = new QMimeData();
            // mime->setData();
            mime->setText(this->text());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mime);
            // 拖动时显示Icon图片
            QPixmap movPixmap = this->icon().pixmap(QSize{35, 35});
            drag->setPixmap(movPixmap);
            drag->exec(Qt::MoveAction);
        }
    }
}

void MyToolButton::dragEnterEvent(QDragEnterEvent *event)
{
    MyToolButton *source = reinterpret_cast<MyToolButton*>(event->source());
    if(source != nullptr && source != this)
    {
        event->accept();
    }

    QWidget::dragEnterEvent(event);
}

void MyToolButton::dragMoveEvent(QDragMoveEvent *event)
{
    MyToolButton *source = reinterpret_cast<MyToolButton*>(event->source());
    if(source != nullptr && source != this)
    {
        event->accept();
    }

    QWidget::dragMoveEvent(event);
}

