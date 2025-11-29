#ifndef MYTOOLBUTTON_H
#define MYTOOLBUTTON_H

#include <QObject>
#include <QToolButton>

class MyToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit MyToolButton(QWidget *parent = nullptr);
    ~MyToolButton();

signals:
    void sendCreate(QString typeText);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

private:
    QPoint pressPos;
};

#endif // MYTOOLBUTTON_H
