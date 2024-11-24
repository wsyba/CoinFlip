#include "mycoin.h"
#include "QPixmap"
#include "QDebug"
#include "QTimer"

MyCoin::MyCoin(QWidget *parent)
    : QPushButton{parent}
{}

MyCoin::MyCoin(QString coinImg)
{
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    QPixmap pixmap;
    bool ret = pixmap.load(coinImg);
    if(!ret)
    {
        qDebug() << coinImg << "图片加载失败！";
    }

    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        pix.load(QString(":/res/Coin000%1.png").arg(min++));

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //停定时器停止条件
        if(min > max)
        {
            min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        pix.load(QString(":/res/Coin000%1.png").arg(max--));

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //停定时器停止条件
        if(max < min)
        {
            max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

void MyCoin::changeFlag()
{
    if(flag)
    {
        timer1->start(30);
        isAnimation = true;
    }
    else
    {
        timer2->start(30);
        isAnimation = true;
    }
    flag = !flag;
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(isAnimation || isWin == true)
    {
        //qDebug() << "已成功，按键禁止";
        return;
    }
    else
    {
        //qDebug() << "未成功，按键允许";
        return QPushButton::mousePressEvent(e);
    }
}

