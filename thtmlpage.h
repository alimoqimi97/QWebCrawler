#ifndef THTMLPAGE_H
#define THTMLPAGE_H

#include <QRegularExpressionMatch>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QQueue>
#include <QByteArray>
#include <QList>
#include <QString>
#include <QMap>
#include <QObject>
#include <iostream>
using namespace std;

class QWebCrawler;


typedef QMap<QString,QList<QString>> qm;


class THtmlPage : public QObject
{
    Q_OBJECT
private:
    QNetworkReply * dwlutil;
    QQueue<QString> DownloadQueue;
    int Depth;
    QString Address;
    QByteArray * HtmlFile;
public:
    THtmlPage();
    THtmlPage(const THtmlPage &other,QObject *parent = 0);

    THtmlPage operator=(THtmlPage &other);

    //      get and set methods     //

    void setDwlUtil(QNetworkReply * du);
    QNetworkReply * getDwlUtil() const;

    void setDepth(int depth);
    int getDepth() const;

//    void setNumber(int n);
//    int getNumber() const;

    void setDownloadQueue(QQueue<QString> & dq);
    QQueue<QString> getDownloadQueue() const;

    void setAddress(QString adrs);
    QString getAddress() const;

    void setHtmlFile(QByteArray * hf);
    QByteArray * getHtmlFile() const;

    //      =================       //

    //          public methods      //
    QList<QString> getLinks();
    void ExtractLinksToDownloadQueue();
    void DownLoadFile(QNetworkAccessManager & manager);
    void PrintHtmlCode();

    //          =============       //
signals:

    void downloadFinished(int f);
    void ProcessDownloadedFile(THtmlPage *page);

    //          testing             //
//    void End();
    //          =======             //

public slots:
    void NewFound();
    void NetworkErrorOccured();
    void SslErrorOccured();
    void AfterDownload(QNetworkReply *reply);
};

QTextStream & operator<<(QTextStream & sout,THtmlPage & p);


#endif // THTMLPAGE_H
