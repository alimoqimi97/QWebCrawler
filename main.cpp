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
    QWebCrawler WebCrawler ;
    //          debugging           //
//    THtmlPage d;
//    QByteArray deb("href=");
//    QByteArray b("https://www.varzesh3.com/");
//    b.append('"');
//    b.prepend('"');
//    deb.append(b);
//    TTree<THtmlPage *> dtree;
//    TNode<THtmlPage *> dnode;

//    d.setDepth(0);
//    d.setHtmlFile(&deb);
//    d.setAddress("https://www.varzesh3.com/");
//    dnode.setData(&d);
//    dtree.setRoot(&dnode);
//    WebCrawler.setHtmlFiles(dtree);
//    WebCrawler.setDownloadLevel(2);
//    WebCrawler.ExecuteLevelDownloading(WebCrawler.getHtmlFiles().getRoot());
//    exit(0);
    //          ==========          //


    QTextStream qin(stdin);
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
