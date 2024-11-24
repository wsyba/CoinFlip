#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include "QString"

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    // normalImg表示正常显示的图片，pressImg表示按下时显示的图片
    explicit MyPushButton(QString normalImg, QString pressImg = "");
    void zoom1();
    void zoom2();
private:
    QString normalImgPath;
    QString pressImgParh;

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
};

#endif // MYPUSHBUTTON_H
