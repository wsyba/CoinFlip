#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
#include "QLabel"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    explicit PlayScene(int);

private:
    unsigned int LevelIndex;
    QVector<QVector<int>> * gameArray;
    QVector<QVector<MyCoin*>> * coinBtn;
    QLabel * winLabel;

    void paintEvent(QPaintEvent *event);

    //翻转周围金币
    void coinFlipAround(int x, int y);

    //显示成功图片
    void displayWinImg();

signals:
    void playSceneBack();
};

#endif // PLAYSCENE_H
