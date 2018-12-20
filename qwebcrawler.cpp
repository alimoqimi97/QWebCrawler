#include "qwebcrawler.h"

QWebCrawler::QWebCrawler(QObject *parent) :
    QObject(parent)
{
    QList<QByteArray *> l;

    this->DownloadedFiles.insert(".html",l);
    this->DownloadedFiles.insert(".jpg",l);
    this->DownloadedFiles.insert(".png",l);
    this->DownloadedFiles.insert(".mp3",l);
    this->DownloadedFiles.insert(".mp4",l);
}

void QWebCrawler::setDownloadLevel(int level)
{
    this->DownloadLevel = level;
}

int QWebCrawler::getDownloadLevel()
{
    return this->DownloadLevel;
}

void QWebCrawler::setHtmlFiles(TTree<THtmlPage> hf)
{
    this->HtmlFiles = hf;
}

TTree<THtmlPage> QWebCrawler::getHtmlFiles()
{
    return this->HtmlFiles;
}

void QWebCrawler::setDownloadedLinks(QList<QString> &links)
{
    this->DownloadedLinks = links;
}

QList<QString> QWebCrawler::getDownloadedLinks()
{
    return this->DownloadedLinks;
}

void QWebCrawler::setDownloadedFiles(mos files)
{
    this->DownloadedFiles = files;
}

mos QWebCrawler::getDownloadedFiles()
{
    return this->DownloadedFiles;
}

void QWebCrawler::StartOrdering(QString inlink, int dlevel)
{
    TNode<THtmlPage> * n = new TNode<THtmlPage>();
    THtmlPage first;

    first.setAddress(inlink);
    first.DownLoadFile(WebManager);
    first.setNumber(0);
    n->setData(first);
    this->HtmlFiles.setRoot(n);

    this->ExecuteLevelDownloading(this->HtmlFiles.getRoot(),dlevel);
}

void QWebCrawler::ExecuteLevelDownloading(TNode<THtmlPage> *current, int level)
{
    //        QString format;
    int csize = 0;

    if((level < 0) | (current == nullptr))
    {
        return;
    }

    current->getData().ExtractLinksToDownloadQueue();
    csize = current->getChilds().size();

    for(int i = 0 ; i < csize ; i++)
    {
        THtmlPage p;

        p.setNumber(i + 1);
        p.setAddress(current->getData().getDownloadQueue().at(i));
        p.DownLoadFile(this->WebManager);
        this->HtmlFiles.Insert(p,current);
        this->DownloadedFiles[".html"].push_back(p.getHtmlFile());
    }

    for(int j = 0 ; j < current->getChilds().size() ; j++)
    {
        this->ExecuteLevelDownloading(current->getChilds().at(j),level - 1);
    }
    //          creating directory for downloadedfiles...       //
}

//void QWebCrawler::NewFound()
//{
//    cout << "New file for download is available..." << endl;
//}

//void QWebCrawler::ErrorOccured()
//{
//    cout << "Error occured..." << endl;
//}

//void QWebCrawler::AfterDownload()
//{
//    QByteArray ba = this->reply->readAll();

//    cout << "download finished..." << endl;

//    for(int i = 0 ; i < ba.size() ; i++)
//    {
//        cout << ba.at(i);
//    }
//    cout << endl;

//}
