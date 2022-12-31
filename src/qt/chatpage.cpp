#include "chatpage.h"
#include "ui_chatpage.h"

//#include "clientmodel.h"
#include "walletmodel.h"
#include "guiutil.h"
#include "util.h"
#include "cookiejar.h"
#include "webview.h"

using namespace GUIUtiL;

// Setup header and styles
//    if (fNoHeaders)
//        GUIUtil::header(this, QString(""));
//    else if (fSmallHeaders)
//        GUIUtil::header(this, QString(":images/headerChatSmall"));
//    else
//        GUIUtil::header(this, QString(":images/headerChat"));
//    this->layout()->setContentsMargins(0, HEADER_HEIGHT, 0, 0); 

ChatPage::ChatPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage),
    walletModel(0)
{
    ui->setupUi(this);
    
    CookieJar *chatJar = new CookieJar;
    ui->webView->page()->networkAccessManager()->setCookieJar(chatJar);

    ui->webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAsNeeded);
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);  
    connect(ui->webView->page()->networkAccessManager(), SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )), ui->webView, SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> & )));
    connect(ui->webView->page(), SIGNAL(linkClicked(QUrl)), ui->webView, SLOT(myOpenUrl(QUrl)));

}   

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::setModel(WalletModel *model)
{
    this->walletModel = model;

    ui->webView->load(QUrl("https://web.libera.chat/#litedoge"));
    //    QUrl url(QString(walletUrl).append("wallet/chat.php?v=").append(FormatVersion(CLIENT_VERSION).c_str()));
    //    ui->webView->myOpenUrl(url);
}
