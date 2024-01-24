

//
#include <QCoreApplication>
#include <QDebug>

#include "CUnRAR.h"


int main(int Argc, char *Argv[])
{
    QCoreApplication a(Argc, Argv);

    //setlocale(LC_CTYPE, "");
    //setlocale(LC_ALL, "en_US.utf8");
    setlocale(LC_ALL, "");

    do{


    qDebug("%d.", UnRAR(L"./test/bin.rar", L""));
    qDebug("%d.", UnRAR(L"./test/bin.exe.rar", L""));
    qDebug("");

    qDebug("%d.", UnRAR(L"./test/单密/unrardll.rar", L""));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll.rar", L"q1w2e3-"));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll.rar", L"q1w2e3"));
    qDebug("");

    qDebug("%d.", UnRAR(L"./test/单密/unrardll多.rar", L""));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll多.rar", L"q1w2e3-"));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll多.rar", L"q1w2e3"));
    qDebug("");

    qDebug("%d.", UnRAR(L"./test/单密/unrardll密名.rar", L""));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll密名.rar", L"q1w2e3-"));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll密名.rar", L"q1w2e3"));
    qDebug("");
    //
    qDebug("%d.", UnRAR(L"./test/单密/unrardll密名多.rar", L""));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll密名多.rar", L"q1w2e3-"));
    qDebug("%d.", UnRAR(L"./test/单密/unrardll密名多.rar", L"q1w2e3"));
    qDebug("");

    qDebug("%d.", UnRAR(L"./test/多密/多密.part01.rar", L""));
    qDebug("%d.", UnRAR(L"./test/多密/多密.part01.rar", L"q1w2e3-"));
    qDebug("%d.", UnRAR(L"./test/多密/多密.part01.rar", L"q1w2e3"));
    qDebug("");

    qDebug("%d.", UnRAR(L"./test/多密/密名/unrardll-700b3.part1.rar", L""));
    qDebug("%d.", UnRAR(L"./test/多密/密名/unrardll-700b3.part1.rar", L"q1w2e3-"));
    qDebug("%d.", UnRAR(L"./test/多密/密名/unrardll-700b3.part1.rar", L"q1w2e3"));
    qDebug("");

    }while(true);

    return a.exec();
}



