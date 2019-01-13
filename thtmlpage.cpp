#include "thtmlpage.h"

THtmlPage::THtmlPage() :dwlutil(nullptr),Depth(0),HtmlFile(nullptr),Number(0)
{
    //    this->connect(dwlutil,SIGNAL(readyRead()),this,SLOT(NewFound()));
    //    this->connect(dwlutil,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(SslErrorOccured()));
    //    this->connect(dwlutil,SIGNAL(sslErrors(QList<QSslError>)),this,SLOT(SslErrorOccured()));
    //    this->connect(dwlutil,SIGNAL(finished()),this,SLOT(AfterDownload()));
}

THtmlPage::THtmlPage(const THtmlPage &other,QObject * parent) :QObject(parent)
{
    this->dwlutil = other.getDwlUtil();
    this->Depth = other.getDepth();
    this->DownloadQueue = other.getDownloadQueue();
    this->Address = other.getAddress();
    this->HtmlFile = other.getHtmlFile();
}

THtmlPage THtmlPage::operator=(THtmlPage &other)
{
    this->dwlutil = other.getDwlUtil();
    this->Depth = other.getDepth();
    this->DownloadQueue = other.getDownloadQueue();
    this->Address = other.getAddress();
    this->HtmlFile = other.getHtmlFile();

    return *this;
}



void THtmlPage::setDwlUtil(QNetworkReply *du)
{
    this->dwlutil = du;
}

QNetworkReply *THtmlPage::getDwlUtil() const
{
    return this->dwlutil;
}

void THtmlPage::setDepth(int depth)
{
    this->Depth = depth;
}

int THtmlPage::getDepth() const
{
    return this->Depth;
}

//void THtmlPage::setNumber(int n)
//{
//    this->Number = n;
//}

//int THtmlPage::getNumber() const
//{
//    return this->Number;
//}

void THtmlPage::setDownloadQueue(QQueue<QString> &dq)
{
    this->DownloadQueue = dq;
}

QQueue<QString> THtmlPage::getDownloadQueue() const
{
    return this->DownloadQueue;
}

void THtmlPage::setAddress(QString adrs)
{
    this->Address = adrs;
}

QString THtmlPage::getAddress() const
{
    return this->Address;
}

void THtmlPage::setHtmlFile(QByteArray *hf)
{
    this->HtmlFile = hf;
}

QByteArray *THtmlPage::getHtmlFile() const
{
    return this->HtmlFile;
}

QList<QString> THtmlPage::getLinks(QString rootaddress)
{
    QString pattern = "href([*]|\n)*?=([*]|\n)*?";
    QString p = "(.*?)";
    QList<QString> li;
    //    int i = 0;

    p.prepend('"');
    p.append('"');
    pattern.append(p);
    QRegularExpression reg(pattern);

    //          testing             //
    //    if(this->HtmlFile->isEmpty())
    //    {
    //        cout << endl;
    //        cout << "Warning: file isn't downloaded..." << endl;
    //        cout << "The address of current page is: " << this->Address.toStdString() << endl;
    //        exit(0);
    //    }
    //          =======             //

    QRegularExpressionMatchIterator itr = reg.globalMatch(*HtmlFile);

    while(itr.hasNext())
    {
        QRegularExpressionMatch m = itr.next();

        if(m.hasMatch())
        {
            QString ns = m.captured(3);

            if(!ns.contains("https:") && !ns.contains("http:"))
            {
                ns.prepend(rootaddress);
            }
            //            ns.prepend(rootaddress + '/');
            li.push_back(ns);
            //            li.push_back(m.captured(3));
        }
    }

    //    QRegularExpressionMatch matched;

    //    matched = reg.match(*HtmlFile);

    //    while(matched.hasMatch())
    //    {
    //        li.push_back(matched.captured(i));
    //        i++;
    //    }

    return li;
}

void THtmlPage::ExtractLinksToDownloadQueue(QString rtad)
{
    QList<QString> links = this->getLinks(rtad);

    for(QString l : links)
    {
        this->DownloadQueue.push_back(l);
    }
}

void THtmlPage::DownLoadFile(QNetworkAccessManager *manager)
{
    QNetworkRequest rq;
    QUrl url(this->Address);

    url.setScheme("https");

//    if(.contains("https"))
//    {
//        url.setScheme("https");
//    }
//    else if(this->Address.contains("http"))
//    {
//        url.setScheme("http");
//    }

//    rq.setUrl(QUrl(this->Address));
    rq.setUrl(url);
    rq.setRawHeader("User-Agent","MyOwnBrowser 1.0");

//    this->connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(AfterDownload(QNetworkReply*)));
    this->dwlutil = manager->get(rq);

    //      under testing part          //
//    QSslConfiguration conf = QSslConfiguration ::defaultConfiguration();

//    conf.setProtocol(QSsl ::TlsV1_0);
//    this->dwlutil->setSslConfiguration(conf);
    //      -------------------         //

    this->connect(dwlutil,SIGNAL(readyRead()),this,SLOT(NewFound()));
    this->connect(dwlutil,SIGNAL(finished()),this,SLOT(ReplyFinished()));
    this->connect(dwlutil,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(NetworkErrorOccured()));
    this->connect(dwlutil,SIGNAL(sslErrors(QList<QSslError>)),this,SLOT(SslErrorOccured()));

}

void THtmlPage::PrintHtmlCode()
{
    QTextStream t(stdout);

    for(int i = 0 ; i < this->HtmlFile->size() ; i++)
    {
        t << this->HtmlFile->at(i) ;
    }
    t << endl;
}

void THtmlPage::DisconnectPage()
{
    this->disconnect(this->dwlutil,SIGNAL(readyRead()),this,SLOT(NewFound()));
    this->disconnect(this->dwlutil,SIGNAL(finished()),this,SLOT(ReplyFinished()));
}

void THtmlPage::NewFound()
{
    cout << "New file for download is available..." << endl;

    QByteArray *bit = new QByteArray();

    //      inserting downloaded data in page.      //
    *bit = this->dwlutil->readAll();

    if(this->HtmlFile == nullptr)
    {
        this->HtmlFile = bit;
    }
    else
    {
        this->HtmlFile->append(*bit);
    }
}

void THtmlPage::NetworkErrorOccured()
{
    cout << endl;
    cout << "Network error occured" << endl;
    cout << dwlutil->errorString().toStdString() << endl;
//    cout << "check your internet connection...!" << endl;
    cout << endl;

    //          under testing part      //
//    this->connect(dwlutil,SIGNAL(readyRead()),this,SLOT(NewFound()));

}

void THtmlPage::SslErrorOccured()
{
    cout << "SslError occured..." << endl;
    cout << this->dwlutil->errorString().toStdString() << endl;
}

void THtmlPage::AfterDownload(QNetworkReply * reply)
{
//    QByteArray * b = new QByteArray();

    cout << "Download finished..." << endl;

    // inserting downloaded data in page    //
//    *b = reply->readAll();
//    this->HtmlFile->append(*b);

    //          testing         //
//    QTextStream q(stdout);

//    for(int i = 0 ; i < this->HtmlFile->size(); i++)
//    {
//        q << this->HtmlFile->at(i);
//    }
//    exit(0);
    //          --------        //

    emit ProcessDownloadedFile(this);

//    dwlutil->deleteLater();
}

void THtmlPage::ReplyFinished()
{
    QByteArray *b = new QByteArray();

    cout << "Reply finished..." << endl;

    //          testing         //
    cout <<"page: " << this->getAddress().toStdString() << endl;
    cout << "Number: " << this->getNumber() << endl;
    //          --------        //


    *b = this->dwlutil->readAll();
    this->HtmlFile->append(*b);


    //          testing         //
//    QTextStream q(stdout);

//    if(this->HtmlFile == nullptr)
//    {
//        cout << "file isn't downloaded..." << endl;
//        exit(0);
//    }

//    for(int i = 0 ; i < this->HtmlFile->size() ; i++)
//    {
//        q << this->HtmlFile->at(i);
//    }
//    q << endl;
//    exit(0);
    //          ---------           //

    //      under testing part      //
    this->ProcessDownloadedFile(this);
}

QTextStream &operator<<(QTextStream &sout, THtmlPage &p)
{
    sout << "Depth = " << p.getDepth() << endl;
    sout << "Address = " << p.getAddress() << endl;
    sout << "HtmlCode = " << p.getHtmlFile() <<  endl ;
    //    p.PrintHtmlCode();

    return sout;
}
