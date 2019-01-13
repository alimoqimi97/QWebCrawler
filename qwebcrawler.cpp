#include "qwebcrawler.h"

QWebCrawler::QWebCrawler(QObject *parent) :
    QObject(parent),DownloadLevel(0)
{
    this->WebManager = new QNetworkAccessManager();
    QList<QByteArray *> l;

    this->DownloadedFiles.insert(".html",l);
    this->DownloadedFiles.insert(".jpg",l);
    this->DownloadedFiles.insert(".png",l);
    this->DownloadedFiles.insert(".mp3",l);
    this->DownloadedFiles.insert(".mp4",l);

    this->ProjectPath = "D:/Qt/Qt5.3.2/Tools/QtCreator/bin/build-QWebCrawler-Desktop_Qt_5_3_MinGW_32bit-Debug/debug/";

    this->DirMaker.setPath(this->ProjectPath);
}

void QWebCrawler::setDownloadLevel(int level)
{
    this->DownloadLevel = level;
}

int QWebCrawler::getDownloadLevel()
{
    return this->DownloadLevel;
}

void QWebCrawler::setHtmlFiles(TTree<THtmlPage *> hf)
{
    this->HtmlFiles = hf;
}

TTree<THtmlPage *> QWebCrawler::getHtmlFiles()
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

void QWebCrawler::StartOrdering(QString inlink)
{
    TNode<THtmlPage *> *n = new TNode<THtmlPage *>();
    THtmlPage *first = new THtmlPage();

    //initial level : download the first page by manual     //
    first->setAddress(inlink);
    first->setDepth(0);
    first->DownLoadFile(WebManager);
    this->ConnectPage(first);
    n->setData(first);

    // inserting in tree        //
    this->HtmlFiles.setRoot(n);
}

void QWebCrawler::ExecuteLevelDownloading(TNode<THtmlPage *> *current)
{
    //        QString format;
    int csize = 0;

    //          inserting the downloaded file in QMap...        //
    this->DownloadedFiles[".html"].push_back(current->getData()->getHtmlFile());

    //  disconnecting current page from webmanager for preventing of redownloading of file..
    current->getData()->DisconnectPage();
//    this->disconnect(this->WebManager,SIGNAL(finished(QNetworkReply*)),current->getData(),SLOT(AfterDownload(QNetworkReply*)));

    //          testing             //
//    cout << "page Number: " << current->getData()->getNumber() << endl;
//    cout <<"current depth: " << current->getData()->getDepth() << endl;
//    cout << "download level: " << this->DownloadLevel << endl;
//    cout <<"current father: " << current->getFather() << endl;
//    cout << "Tree size: " << this->HtmlFiles.getSize() << endl;
    //          =======             //


    //      testing         //
//    QTextStream q(stdout);

//    if(current->getData()->getNumber() == 1)
//    {
//        if(current->getData()->getHtmlFile() ==nullptr)
//        {
//            cout << "file isn't downloaded" << endl;
//            exit(0);
//        }
//        for(int i = 0 ; i < current->getData()->getHtmlFile()->size() ; i++)
//        {
//            q << current->getData()->getHtmlFile()->at(i);
//        }
//        q << endl;
//        exit(0);
//    }
    //      -------         //




    if((current->getData()->getDepth() == this->DownloadLevel) | (current == nullptr))
    {
        exit(0);
    }

    //          extracting all links of the page(html code of webpage)    //
    current->getData()->ExtractLinksToDownloadQueue(this->HtmlFiles.getRoot()->getData()->getAddress());

    csize = current->getData()->getDownloadQueue().size();

    QList<QString> dq = current->getData()->getDownloadQueue();

    for(int i = 0 ; i < csize ; i++)
    {
        THtmlPage *p = new THtmlPage();

        //      inserting page info     //
        p->setAddress(dq.at(i));
        p->setDepth(current->getData()->getDepth() + 1);
        p->setNumber(i + 1);
        p->setMng(this->WebManager);

        //     calling download command for each page   //
        p->DownLoadFile(this->WebManager);
        this->ConnectPage(p);

        //   inserting in tree          //
        this->HtmlFiles.Insert(p,current);
    }

    //          creating directory for downloadedfiles...       //
    if(!current->getData()->getHtmlFile()->isEmpty())
    {
        this->MakeDirectory(current->getData()->getAddress(),current->getData()->getHtmlFile());
    }
}

void QWebCrawler::ConnectPage(THtmlPage *hp)
{
    this->connect(hp,SIGNAL(ProcessDownloadedFile(THtmlPage*)),this,SLOT(StartLevelDownloading(THtmlPage*)));
}

void QWebCrawler::MakeDirectory(QString address, QByteArray *htmlfile)
{
    QString filename;

    address = address.remove("https://");

    QString filepath = this->ProjectPath + "Downloaded/" + address;
    this->DirMaker.mkpath(filepath);

    filename = this->DirMaker.dirName();
    filename.append(".html");

    //          testing         //
//    cout << "filename: " << filename.toStdString() << endl;
    //          -------         //

    //inserting html file in directory...       //
    QFile file(filepath.append(filename));
    QTextStream fd(&file);

    file.open(QIODevice::WriteOnly);

    for(int i = 0 ; i < htmlfile->size() ; i++)
    {
        fd << htmlfile->at(i);
    }

    file.close();

    //      creating text file of html datas    //
    QFile txtfile(filepath.append(".txt"));
    QTextStream tf(&txtfile);

    txtfile.open(QIODevice::WriteOnly);

    for(int i = 0 ; i < htmlfile->size() ; i++)
    {
        tf << htmlfile->at(i);
    }

    txtfile.close();
}

void QWebCrawler::StartLevelDownloading(THtmlPage *pag)
{
    TNode<THtmlPage *> *g = this->HtmlFiles.Find(pag);

    this->ExecuteLevelDownloading(g);
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
