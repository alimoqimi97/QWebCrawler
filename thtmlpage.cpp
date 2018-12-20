#include "thtmlpage.h"

THtmlPage::THtmlPage() :dwlutil(nullptr),Number(0),HtmlFile(nullptr)
{
    this->connect(dwlutil,SIGNAL(readyRead()),this,SLOT(NewFound()));
    this->connect(dwlutil,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(SslErrorOccured()));
    this->connect(dwlutil,SIGNAL(sslErrors(QList<QSslError>)),this,SLOT(SslErrorOccured()));
    this->connect(dwlutil,SIGNAL(finished()),this,SLOT(AfterDownload()));
}

THtmlPage::THtmlPage(const THtmlPage &other) :QObject(this)
{
    this->dwlutil = other.getDwlUtil();
    this->Number = other.getNumber();
    this->DownloadQueue = other.getDownloadQueue();
    this->Address = other.getAddress();
    this->HtmlFile = other.getHtmlFile();
}

THtmlPage THtmlPage::operator=(THtmlPage &other)
{
    this->dwlutil = other.getDwlUtil();
    this->Number = other.getNumber();
    this->DownloadQueue = other.getDownloadQueue();
    this->Address = other.getAddress();
    this->HtmlFile = other.getHtmlFile();
}



void THtmlPage::setDwlUtil(QNetworkReply *du)
{
    this->dwlutil = du;
}

QNetworkReply *THtmlPage::getDwlUtil() const
{
    return this->dwlutil;
}

void THtmlPage::setNumber(int n)
{
    this->Number = n;
}

int THtmlPage::getNumber() const
{
    return this->Number;
}

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

QList<QString> THtmlPage::getLinks()
{
    QString pattern = "href([*]|\n)*?=([*]|\n)*?";
    QString p = "(.*)";
    QList<QString> li;
    int i = 0;

    p.prepend('"');
    p.append('"');
    pattern.append(p);
    QRegularExpression reg(pattern);
    QRegularExpressionMatch matched;

    matched = reg.match(*HtmlFile);

    while(matched.hasMatch())
    {
        li.push_back(matched.captured(i));
        i++;
    }

    return li;
}

void THtmlPage::ExtractLinksToDownloadQueue()
{
    QList<QString> links = this->getLinks();

    for(QString l : links)
    {
        this->DownloadQueue.push_back(l);
    }
}

void THtmlPage::DownLoadFile(QNetworkAccessManager &manager)
{
    QNetworkRequest rq;
//    QByteArray * b = new QByteArray();

    rq.setUrl(QUrl(this->Address));
    this->dwlutil = manager.get(rq);

//    *b = dwlutil->readAll();
//    this->HtmlFile = b;
}

void THtmlPage::NewFound()
{
    cout << "New file for download is available..." << endl;
}

void THtmlPage::NetworkErrorOccured()
{
    cout << "Network error occured" << endl;
}

void THtmlPage::SslErrorOccured()
{
    cout << "SslError occured..." << endl;
}

void THtmlPage::AfterDownload()
{
    QByteArray * b = new QByteArray();

    cout << "Download finished..." << endl;
    *b = this->dwlutil->readAll();
    this->HtmlFile = b;
//    dwlutil->deleteLater();
}
