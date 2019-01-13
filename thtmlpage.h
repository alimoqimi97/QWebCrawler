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
#include <QSslConfiguration>
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
    int Number;

    QNetworkAccessManager * mng;

public:
    THtmlPage();
    THtmlPage(const THtmlPage &other,QObject *parent = 0);

    THtmlPage operator=(THtmlPage &other);

    //      get and set methods     //

    void setNumber(int num)
    {
        this->Number = num;
    }
    int getNumber()
    {
        return this->Number;
    }

    void setMng(QNetworkAccessManager * m)
    {
        this->mng = m;
    }
    QNetworkAccessManager *getMng()
    {
        return this->mng;
    }

    void setDwlUtil(QNetworkReply * du);
    QNetworkReply * getDwlUtil() const;

    void setDepth(int depth);
    int getDepth() const;

    void setDownloadQueue(QQueue<QString> & dq);
    QQueue<QString> getDownloadQueue() const;

    void setAddress(QString adrs);
    QString getAddress() const;

    void setHtmlFile(QByteArray * hf);
    QByteArray * getHtmlFile() const;

    //      =================       //

    //          public methods      //
    QList<QString> getLinks(QString rootaddress);
    void ExtractLinksToDownloadQueue(QString rtad);
    void DownLoadFile(QNetworkAccessManager * manager);
    void PrintHtmlCode();
    void DisconnectPage();

    //          =============       //

//    under testing part        //
    //          destructor          //
    ~THtmlPage()
    {
        delete this->HtmlFile;
    }
//---------------               //
signals:

    void downloadFinished(int f);
    void ProcessDownloadedFile(THtmlPage *page);

public slots:
    void NewFound();
    void NetworkErrorOccured();
    void SslErrorOccured();
    void AfterDownload(QNetworkReply *reply);
    void ReplyFinished();
};

QTextStream & operator<<(QTextStream & sout,THtmlPage & p);


#endif // THTMLPAGE_H
