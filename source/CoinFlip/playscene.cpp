#include "playscene.h"
#include "mypushbutton.h"
#include "QMenuBar"
#include "QAction"
#include "QTimer"
#include "QPainter"
#include "QLabel"
#include "QFont"
#include "mycoin.h"
#include "dataconfig.h"
#include "QDebug"
#include "QPropertyAnimation"

PlayScene::PlayScene(QWidget *parent)
    : QMainWindow{parent}
{}

PlayScene::PlayScene(int i)
{
    LevelIndex = i;

    //设置成功图片
    winLabel = new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0, 0, pix.width(), pix.height());
    winLabel->move((this->width() - pix.width()) * 0.1, -pix.height());

    dataConfig datac;
    int num = datac.mData[LevelIndex].size();
    gameArray = new QVector<QVector<int>>(num, QVector<int>(num, 0));
    coinBtn = new QVector<QVector<MyCoin*>>(num, QVector<MyCoin*>(num));
    for(int i = 0; i < gameArray->size(); ++i)
    {
        for(int j = 0; j < gameArray->size(); ++j)
        {
            (*gameArray)[i][j] = datac.mData[LevelIndex][i][j];
        }
    }

    this->setWindowTitle("翻金币");
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //创建金币背景图片
    for(int i = 0; i < gameArray->size(); ++i)
    {
        for(int j = 0; j < gameArray->size(); ++j)
        {
            QLabel * label = new QLabel;
            label->setParent(this);
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->move((this->width() - gameArray->size() * 50) / 2 + i * 50, (this->height()-gameArray->size()*50)/2 + 10 + j * 50);

            //生成金币
            QString str;
            if((*gameArray)[i][j] == 1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str);
            (*coinBtn)[i][j] = coin;
            coin->setParent(this);
            coin->move((this->width() - gameArray->size() * 50) / 2 + 2 + i * 50, (this->height()-gameArray->size()*50)/2 + 14 + j * 50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = (*gameArray)[i][j];

            //点击金币，进行翻转
            connect(coin, &MyCoin::clicked, [=](){
                coin->changeFlag();
                (*gameArray)[i][j] = (*gameArray)[i][j] == 0 ? 1 : 0;

                //翻转周围金币
                coinFlipAround(i, j);

                //每次翻转金币后判断是否达成成功条件
                int n = gameArray->size();
                coin->isWin = true;
                for(int i = 0; i < n; ++i)
                {
                    for(int j = 0; j < n; ++j)
                    {
                        if((*gameArray)[i][j] == 0)
                        {
                            coin->isWin = false;
                            break;
                        }
                    }
                }

                //如果达成成功条件，则把全部Coin的isWin属性设置为true
                if(coin->isWin)
                {
                    this->displayWinImg();
                    for(int i = 0; i < n; ++i)
                    {
                        for(int j = 0; j < n; ++j)
                        {
                            (*coinBtn)[i][j]->isWin = true;
                        }
                    }
                }
            });
        }
    }

    //设置左下角关卡信息标签
    QLabel * label = new QLabel;
    label->setParent(this);
    label->setText(QString("Level: %1").arg(LevelIndex));
    QFont font;
    font.setFamily("微软雅黑");
    font.setPointSize(20);;
    label->setFont(font);
    label->setFixedSize(120, 50);
    label->move(20, this->height() - label->height());

    //创建Back按键
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width() - closeBtn->width(), this->height() - closeBtn->height());

    connect(closeBtn, &MyPushButton::clicked, [=](){
        QTimer::singleShot(500, this, [=](){
            this->hide();
            emit this->playSceneBack();
        });
    });
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;

    //背景
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //标题
    pix.load(":/res/Title.png");
    //设置缩放
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}

void PlayScene::coinFlipAround(int x, int y)
{
    int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
    for(int k = 0; k < 4; ++k)
    {
        int newX = x + dir[k][0], newY = y + dir[k][1];
        if(newX >= 0 && newX < gameArray->size() && newY >= 0 && newY < gameArray->size())
        {
            (*coinBtn)[newX][newY]->changeFlag();
            (*gameArray)[newX][newY] = (*gameArray)[newX][newY] == 0 ? 1 : 0;
        }
    }
}

void PlayScene::displayWinImg()
{
    qDebug() << "GameWin!";
    QPropertyAnimation * animation = new QPropertyAnimation(winLabel, "geometry");
    //设置时间间隔
    animation->setDuration(1000);
    //设置开始位置
    animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
    //设置结束位置
    animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 114, winLabel->width(), winLabel->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}
