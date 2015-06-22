#include "chatpage.h"
#include "ui_chatpage.h"

//#include "clientmodel.h"
#include "walletmodel.h"
#include "guiutil.h"
#include "util.h"
#include "cookiejar.h"
#include "webview.h"

using namespace GUIUtil;

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

    ui->webView->load(QUrl("https://kiwiirc.com/client/irc.freenode.net/#litedoge"));
}
