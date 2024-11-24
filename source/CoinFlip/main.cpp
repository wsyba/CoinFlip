#include "mainscene.h"

#include <QApplication>

// #include "dataconfig.h"
// #include "QDebug"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    w.show();

    // const int num = 10;
    // dataConfig datac;
    // for(int i = 0; i < datac.mData[num].size(); ++i)
    // {
    //     for(int j = 0; j < datac.mData[num][0].size(); ++j)
    //     {
    //         qDebug() << datac.mData[num][i][j];
    //     }
    // }

    // dataConfig datac;
    // int num = datac.mData[1].size();
    // QVector<QVector<int>> * gameArray = new QVector<QVector<int>>(num, QVector<int>(num, 0));
    // qDebug() << gameArray->size() << " " << gameArray[0].size();


    return a.exec();
}
