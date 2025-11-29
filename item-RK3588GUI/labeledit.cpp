#include "labeledit.h"

LabelEdit::LabelEdit()
    : isLPress{ false }
{}

void LabelEdit::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->isLPress = true;
        emit sendPressed();
    }

    QLineEdit::mousePressEvent(event);
}

void LabelEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit sendDoublePressed();
    }

    QLineEdit::mouseDoubleClickEvent(event);
}

void LabelEdit::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->isLPress = false;
        emit sendReleased();
    }

    QLineEdit::mouseReleaseEvent(event);
}

void LabelEdit::mouseMoveEvent(QMouseEvent *event)
{
    emit sendMove();
}
