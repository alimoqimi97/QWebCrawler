#ifndef THTMLPAGE_H
#define THTMLPAGE_H


#include <QRegularExpressionMatch>
#include <QRegularExpression>
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

typedef QMap<QString,QList<QString>> qm;


class THtmlPage : public QObject
{
    Q_OBJECT
private:
    QNetworkReply * dwlutil;
    int Number;
    QQueue<QString> DownloadQueue;
    QString Address;
    QByteArray * HtmlFile;
public:
    THtmlPage();
    THtmlPage(const THtmlPage &other);

    THtmlPage operator=(THtmlPage &other);

    //      get and set methods     //

    void setDwlUtil(QNetworkReply * du);
    QNetworkReply * getDwlUtil() const;

    void setNumber(int n);
    int getNumber() const;

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

    //          =============       //
signals:

public slots:
    void NewFound();
    void NetworkErrorOccured();
    void SslErrorOccured();
    void AfterDownload();
};

#endif // THTMLPAGE_H
