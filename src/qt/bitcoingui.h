// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOINGUI_H
#define BITCOINGUI_H

#include "amount.h"

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QMenu>
#include <QPoint>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <stdint.h>

class TransactionTableModel;
class ClientModel;
class NetworkStyle;
class Notificator;
class TransactionView;
class OptionsModel;
class BlockExplorer;
class RPCConsole;
class OverviewPage;
class AddressBookPage;
class SendCoinsDialog;
class SignVerifyMessageDialog;
class UnitDisplayStatusBarControl;
class WalletFrame;
class WalletModel;
class ChatPage;

class CWallet;

QT_BEGIN_NAMESPACE
class QLabel;
class QModelIndex;
class QAction;
class QProgressBar;
class QProgressDialog;
class QStackedWidget;
QT_END_NAMESPACE

/**
  Bitcoin GUI main class. This class represents the main window of the Bitcoin UI. It communicates with both the client and
  wallet models to give the user an up-to-date view of the current core state.
*/
class BitcoinGUI : public QMainWindow
{
    Q_OBJECT

public:
    static const QString DEFAULT_WALLET;

    explicit BitcoinGUI(const NetworkStyle* networkStyle, QWidget* parent = 0);
    ~BitcoinGUI();

    /** Set the client model.
        The client model represents the part of the core that communicates with the P2P network, and is wallet-agnostic.
    */
    void setClientModel(ClientModel *clientModel);
    
#ifdef ENABLE_WALLET    
    /** Set the wallet model.
        The wallet model represents a bitcoin wallet, and offers access to the list of transactions, address book and sending
        functionality.
    */
    bool addWallet(const QString& name, WalletModel* walletModel);
    bool setCurrentWallet(const QString& name);
    void removeAllWallets();
#endif // ENABLE_WALLET
    bool enableWallet;
    bool fMultiSend = false;

protected:
    void changeEvent(QEvent* e);
    void closeEvent(QCloseEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    bool eventFilter(QObject* object, QEvent* event);

private:
    ClientModel* clientModel;
    WalletModel* walletModel;

    UnitDisplayStatusBarControl* unitDisplayControl;
    QToolBar* toolbar;
    QLabel* labelStakingIcon;
    QLabel* labelEncryptionIcon;
    QLabel* labelConnectionsIcon;
    QLabel* labelBlocksIcon;
    QLabel* progressBarLabel;
    QProgressBar* progressBar;
    QStackedWidget* centralStackedWidget;
    
    OverviewPage* overviewPage;
    QMenuBar* appMenuBar;
    QAction* overviewAction;
    QAction* historyAction;
    QAction* quitAction;
    QAction* sendCoinsAction;
    QAction* usedSendingAddressesAction;
    QAction* usedReceivingAddressesAction;
    QAction* addressBookAction;
    QAction* signMessageAction;
    QAction* verifyMessageAction;
    QAction* aboutAction;
    QAction* receiveCoinsAction;
    QAction* optionsAction;
    QAction* toggleHideAction;
    QAction* exportAction;
    QAction* encryptWalletAction;
    QAction* backupWalletAction;
    QAction* changePassphraseAction;
    QAction* unlockWalletAction;
    QAction* lockWalletAction;
    QAction* aboutQtAction;
    QAction* openRPCConsoleAction;
    QAction* blockExplorerAction;
    QAction* showBackupsAction;
    QAction* openAction;
    QAction* websiteAction;
    QAction* facebookAction;
    QAction* chatPageAction;
    QAction* multiSendAction;

    QSystemTrayIcon* trayIcon;
    Notificator* notificator;
    TransactionView* transactionView;
    RPCConsole* rpcConsole;
    
    QWidget* transactionsPage;
    AddressBookPage* addressBookPage;
    AddressBookPage* receiveCoinsPage;
    SendCoinsDialog* sendCoinsPage;
    SignVerifyMessageDialog* signVerifyMessageDialog;

    QMovie* syncIconMovie;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    Notificator* notificator;
    RPCConsole* rpcConsole;
    BlockExplorer* explorerWindow;
    
    /** Keep track of previous number of blocks, to detect progress */
    int prevBlocks;
    int spinnerFrame;

    /** Create the main UI actions. */
    void createActions();
    /** Create the menu bar and sub-menus. */
    void createMenuBar();
    /** Create the toolbars */
    void createToolBars();
    /** Create system tray (notification) icon */
    void createTrayIcon();
    
    /** Enable or disable all wallet-related actions */
    void setWalletActionsEnabled(bool enabled);

    /** Connect core signals to GUI client */
    void subscribeToCoreSignals();
    /** Disconnect core signals from GUI client */
    void unsubscribeFromCoreSignals();

signals:
    /** Signal raised when a URI was entered or dragged to the GUI */
    void receivedURI(const QString& uri);
    /** Restart handling */
    void requestedRestart(QStringList args);

public slots:
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count);
     /** Get restart command-line parameters and request restart */
    void handleRestart(QStringList args);

    /** Notify the user of an event from the core network or transaction handling code.
       @param[in] title     the message box / notification title
       @param[in] message   the displayed text
       @param[in] modal     true to use a message box, false to use a notification
       @param[in] style     modality and style definitions (icon and used buttons - buttons only for message boxes)
                            @see CClientUIInterface::MessageBoxFlags
       @param[in] ret       pointer to a bool that will be modified to whether Ok was clicked (modal only)                     
    */
    void message(const QString &title, const QString &message, bool modal, unsigned int style, bool* ret = NULL);
    
    void setStakingStatus();
    
#ifdef ENABLE_WALLET
    /** Set the encryption status as shown in the UI.
       @param[in] status            current encryption status
       @see WalletModel::EncryptionStatus
    */
    void setEncryptionStatus(int status);
    
    bool handlePaymentRequest(const SendCoinsRecipient& recipient);
    
    /** Show incoming transaction notification for new transactions. */
    void incomingTransaction(const QString& date, int unit, const CAmount& amount, const QString& type, const QString& address);
    void handleURI(QString strURI);
    void askFee(qint64 nFeeRequired, bool *payFee);
    /** Asks the user whether to pay the transaction fee or to cancel the transaction.
       It is currently not possible to pass a return value to another thread through
       BlockingQueuedConnection, so an indirected pointer is used.
       https://bugreports.qt-project.org/browse/QTBUG-10440

      @param[in] nFeeRequired       the required fee
      @param[out] payFee            true to pay the fee, false to not pay the fee
    */
#endif // ENABLE_WALLET 

private slots:
#ifdef ENABLE_WALLET
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
    /** Switch to address book page */
    void gotoAddressBookPage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");
    
    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");
    void gotoMultiSendDialog();
    
    /** Show open dialog */
    void openClicked();
    
#endif // ENABLE_WALLET    
    /** Show configuration dialog */
    void optionsClicked();
    /** Show about dialog */
    void aboutClicked();
    /** Show help message dialog */
    void openBlockExplorer();
    void openWebsite();
    void openFacebook();
    /** Switch to IRC Chat Page */
    void gotoChatPage();
    void showHelpMessageClicked();
#ifndef Q_OS_MAC
    /** Handle tray icon clicked */
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
#endif

   /** Show window if hidden, unminimize when minimized, rise when obscured or show if hidden and fToggleHidden is true */
    void showNormalIfMinimized(bool fToggleHidden = false);
    /** Simply calls showNormalIfMinimized(true) for use in SLOT() macro */
    void toggleHidden();

    /** called by a timer to check if fRequestShutdown has been set **/
    void detectShutdown();

    /** Show progress dialog e.g. for verifychain */
    void showProgress(const QString& title, int nProgress);
};

class UnitDisplayStatusBarControl : public QLabel
{
    Q_OBJECT

public:
    explicit UnitDisplayStatusBarControl();
    /** Lets the control know about the Options Model (and its signals) */
    void setOptionsModel(OptionsModel* optionsModel);

protected:
    /** So that it responds to left-button clicks */
    void mousePressEvent(QMouseEvent* event);

private:
    OptionsModel* optionsModel;
    QMenu* menu;

    /** Shows context menu with Display Unit options by the mouse coordinates */
    void onDisplayUnitsClicked(const QPoint& point);
    /** Creates context menu, its actions, and wires up all the relevant signals for mouse events. */
    void createContextMenu();

private slots:
    /** When Display Units are changed on OptionsModel it will refresh the display text of the control on the status bar */
    void updateDisplayUnit(int newUnits);
    /** Tells underlying optionsModel to update its current display unit. */
    void onMenuSelection(QAction* action);
};

    void incomingTransaction(const QModelIndex & parent, int start, int end);
    /** Encrypt the wallet */
    void encryptWallet();
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
    void unlockWallet();
    void lockWallet();
    void updateWeight();
    void updateStakingIcon();
};

#endif // BITCOIN_QT_BITCOINGUI_H
