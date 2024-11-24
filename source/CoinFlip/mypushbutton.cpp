#include "mypushbutton.h"
#include "QDebug"
#include "QPropertyAnimation"
#include "QPixmap"

MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    normalImgPath = normalImg;
    pressImgParh = pressImg;

    QPixmap pixmap;

    bool ret = pixmap.load(normalImgPath);

    //判断图片是否正常加载
    if(!ret)
    {
        qDebug() << normalImgPath << "图片加载失败!";
    }

    //设置图片尺寸
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

}

void MyPushButton::zoom1()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::zoom2()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgParh != "")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressImgParh);
        if(!ret)
        {
            qDebug() << pressImgParh << "图片加载失败";
        }
        this->setFixedSize(pixmap.width(), pixmap.height());
        //this->setStyleSheet("QPushButtom{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath != "")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);
        if(!ret)
        {
            qDebug() << normalImgPath << "图片加载失败";
        }
        this->setFixedSize(pixmap.width(), pixmap.height());
        //this->setStyleSheet("QPushButtom{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
