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
#include <QDir>
using namespace std;

typedef QMap<QString,QList<QByteArray *>> mos;

class QWebCrawler : public QObject
{
    Q_OBJECT

private:
    int DownloadLevel;
    TTree<THtmlPage *> HtmlFiles;
    QList<QString> DownloadedLinks;
    QMap<QString,QList<QByteArray *>> DownloadedFiles;
    QNetworkAccessManager *WebManager;
    QDir DirMaker;
    QString ProjectPath;

public:
    explicit QWebCrawler(QObject *parent = 0);

    //          get and set methods               //
    void setDownloadLevel(int level);
    int getDownloadLevel();

    void setHtmlFiles(TTree<THtmlPage *> hf);
    TTree<THtmlPage *> getHtmlFiles();

    void setDownloadedLinks(QList<QString> & links);
    QList<QString> getDownloadedLinks();

    void setDownloadedFiles(mos files);
    mos getDownloadedFiles();
    //          ================            //

    //          public methods          //
    void StartOrdering(QString inlink);
    void ExecuteLevelDownloading(TNode<THtmlPage *> *current);
    void ConnectPage(THtmlPage *hp);

    void MakeDirectory(QString address,QByteArray *htmlfile);

signals:

public slots:
    void StartLevelDownloading(THtmlPage * pag);

    //              testing                 //
    void printHtmlFiles()
    {
        QList<QByteArray *> ::iterator litr;
        QTextStream t(stdout);

        QList<QByteArray *> li = this->DownloadedFiles.value(".html");

        t << "downloaded file number = " << li.size() << endl;

        t << "Files : " << endl;
        for(litr = li.begin() ; litr != li.end() ; litr++)
        {
            t << *litr << endl;
        }

//        this->HtmlFiles.PrintTree(HtmlFiles.getRoot(),t);
    }
    //              ====================                //

//    void NewFound();
//    void ErrorOccured();
//    void AfterDownload();

};

#endif // QWEBCRAWLER_H
