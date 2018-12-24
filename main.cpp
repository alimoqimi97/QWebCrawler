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
    QWebCrawler WebCrawler ;
    int Depth = 0;
    QString WebAddress;

    cout << "Enter your WebAddress : ";
    qin >> WebAddress;

    cout << "Depth = ";
    qin >> Depth;
    WebCrawler.setDownloadLevel(Depth);

    WebCrawler.StartOrdering(WebAddress);

    return a.exec();
}
