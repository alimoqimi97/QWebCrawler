#ifndef QWEBCRAWLER_H
#define QWEBCRAWLER_H

#include "thtmlpage.h"
#include "ttree.h"
#include <QObject>
#include <QNetworkReply>
#include <QByteArray>
#include <iostream>
#include <QMap>
#include <QList>
#include <QString>
using namespace std;

typedef QMap<QString,QList<QByteArray *>> mos;

class QWebCrawler : public QObject
{
    Q_OBJECT

private:
    int DownloadLevel;
    TTree<THtmlPage> HtmlFiles;
    QList<QString> DownloadedLinks;
    QMap<QString,QList<QByteArray *>> DownloadedFiles;
    QNetworkAccessManager WebManager;

public:
    explicit QWebCrawler(QObject *parent = 0);

    //          get and set methods               //
    void setDownloadLevel(int level);
    int getDownloadLevel();

    void setHtmlFiles(TTree<THtmlPage> hf);
    TTree<THtmlPage> getHtmlFiles();

    void setDownloadedLinks(QList<QString> & links);
    QList<QString> getDownloadedLinks();

    void setDownloadedFiles(mos files);
    mos getDownloadedFiles();
    //          ================            //

    //          public methods          //
    void StartOrdering(QString inlink,int dlevel);
    void ExecuteLevelDownloading(TNode<THtmlPage> * current,int level);

signals:

public slots:
    //          undertesting part..         //
    void StartLevelDownloading(int dlevel)
    {
        this->ExecuteLevelDownloading(this->HtmlFiles.getRoot(),dlevel);
    }
    //          ==================          //

//    void NewFound();
//    void ErrorOccured();
//    void AfterDownload();

};

#endif // QWEBCRAWLER_H
