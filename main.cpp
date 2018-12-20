#include "qwebcrawler.h"
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QTextStream>
#include <QSslError>
#include <QtNetwork>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream qin(stdin);
    QWebCrawler WebCrawler;
    int Depth = 0;
    QString WebAddress;

    cout << "Enter your WebAddress :" << endl;
    qin >> WebAddress;

    cout << "Depth = " << endl;
    qin >> Depth;

    WebCrawler.StartOrdering(WebAddress,Depth);

    return a.exec();
}
