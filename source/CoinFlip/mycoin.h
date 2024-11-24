#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString);
    //翻转金币
    void changeFlag();
    void mousePressEvent(QMouseEvent *e);

    int posX;
    int posY;
    bool flag;
    //金->银 监听
    QTimer * timer1;
    //银->金 监听
    QTimer * timer2;

    int min = 1;
    int max = 8;
    bool isAnimation = false;
    bool isWin = false;

signals:
};

#endif // MYCOIN_H
