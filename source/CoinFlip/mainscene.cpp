#include "mainscene.h"
#include "ui_mainscene.h"
#include "QPainter"
#include "QPixmap"
#include "mypushbutton.h"
#include "QTimer"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置窗口名称
    this->setWindowTitle("翻金币");
    //设置窗口大小
    this->setFixedSize(320, 500);
    //设置标题图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置退出
    connect(ui->actionQuit, &QAction::triggered, [=](){
        this->close();
    });

    //开始按键音效


    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    //开始按键点击事件, 动画效果
    connect(startBtn, &MyPushButton::clicked, [=](){
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500, this, [=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });

    //接收ChooseLevelScene窗口的Back信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=](){
        this->setGeometry(chooseScene->geometry());
        this->show();
    });
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;

    //设置背景图
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //设置标题图
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);

}

MainScene::~MainScene()
{
    delete ui;
}
