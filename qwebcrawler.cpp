#include "qwebcrawler.h"

QWebCrawler::QWebCrawler(QObject *parent) :
    QObject(parent),DownloadLevel(0)
{
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


    //          testing             //
    cout <<"current depth: " << current->getData()->getDepth() << endl;
    cout << "download level: " << this->DownloadLevel << endl;
//    cout <<"current father: " << current->getFather() << endl;
    cout << "Tree size: " << this->HtmlFiles.getSize() << endl;
    //          =======             //

    if((current->getData()->getDepth() > this->DownloadLevel) | (current == nullptr))
    {
        exit(0);
    }

    //          extracting all links of the page(html code of webpage)    //
    current->getData()->ExtractLinksToDownloadQueue();

    csize = current->getData()->getDownloadQueue().size();

    //          testing         //
//    cout << "download Queue size: " << current->getData()->getDownloadQueue().size() << endl;
//    if(csize == 0)
//    {
//        cout << "wow download queue is empty." << endl;
//        exit(0);
//    }
    //          =======         //

    QList<QString> dq = current->getData()->getDownloadQueue();

    for(int i = 0 ; i < csize ; i++)
    {
        THtmlPage *p = new THtmlPage();

        //      inserting page info     //
        p->setAddress(dq.at(i));
        p->setDepth(current->getData()->getDepth() + 1);


        //     calling download command for each page   //
        p->DownLoadFile(this->WebManager);
        this->ConnectPage(p);

        //   inserting in tree          //
        this->HtmlFiles.Insert(p,current);
    }

    //          creating directory for downloadedfiles...       //
    this->MakeDirectory(current->getData()->getAddress(),current->getData()->getHtmlFile());
}

void QWebCrawler::ConnectPage(THtmlPage *hp)
{
    this->connect(hp,SIGNAL(ProcessDownloadedFile(THtmlPage*)),this,SLOT(StartLevelDownloading(THtmlPage*)));
}

void QWebCrawler::MakeDirectory(QString address, QByteArray *htmlfile)
{
    address = address.remove("https://");
    //          testing             //
//    cout << "address: " << address.toStdString() << endl;
//    cout << "file: " << htmlfile << endl;
    //          =======             //

    QString filepath = this->ProjectPath + "Downloaded/" + address;
    this->DirMaker.mkpath(filepath);

    //          testing             //
//    cout <<"filepath: " << filepath.toStdString() << endl;
    //          =======             //


    //inserting html file in directory...       //
    QFile file(filepath.append("dir.html"));
    QTextStream fd(&file);

    file.open(QIODevice::WriteOnly);

//    fd << *htmlfile << endl;

    for(int i = 0 ; i < htmlfile->size() ; i++)
    {
        fd << htmlfile->at(i);
    }

    file.close();
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
