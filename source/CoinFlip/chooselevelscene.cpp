#include "chooselevelscene.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"
#include "playscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(320, 588);
    //设置窗体图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //创建Back按键
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width() - closeBtn->width(), this->height() - closeBtn->height());

    connect(closeBtn, &MyPushButton::clicked, [=](){
        QTimer::singleShot(500, this, [=](){
            this->hide();
            emit this->chooseSceneBack();
        });
    });

    for(int i = 0; i < 20; ++i)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        connect(menuBtn, &MyPushButton::clicked, [=](){
            if(pScene == nullptr)
            {
                this->hide();
                pScene = new PlayScene(i + 1);
                pScene->setGeometry(this->geometry());
                pScene->show();

                //连接PlayScnen窗口的返回按键
                connect(pScene, &PlayScene::playSceneBack, [=](){
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = nullptr;
                });
            }
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
