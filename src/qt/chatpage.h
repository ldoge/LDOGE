#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWebView>
#include <QWidget>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QTimer>
#include <QMap>
#include <QtGui>
#include <QtNetwork>
#include "clientmodel.h"
#include "serveur.h"
#include "serveur.cpp"

namespace Ui {
    class ChatPage;
}
class ClientModel;
class WalletModel;

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Trade page widget */
class ChatPage : public QStackedWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = 0);
    ~ChatPage();

    void setModel(ClientModel *clientModel);
    void setModel(WalletModel *walletModel);
    Server * currentTab();
    signals:
        void changeTab();
public slots:
        void sendCommande();
        void connecte();
        void closeTab();

        void tabChanged(int index);

        void tabJoined();
        void tabJoining();
        void disconnectFromServer();
        void tabClosing(int index);
        
private:
    Ui::ChatPage *ui;
    ClientModel *clientModel;
    WalletModel *walletModel;

private slots:
    Ui::ChatPage *ui;
    ClientModel *model;
    QMap<QString,Server *> servers;
    bool joining;
    void closeEvent(QCloseEvent *event);

};

#endif // CHATPAGE_H
