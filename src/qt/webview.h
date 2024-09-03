/*
 * MIT License
 *
 * Copyright (c) 2024 Serge Zaitsev
 * Copyright (c) 2024 Steffen André Langnes
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Qt5 webview naviagation
 *
 * Developed by OnsightIT 2014-2015
 * onsightit@gmail.com
 */
#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QApplication>
#include <QApp>
#include <QtWebView>
#include <QIcon>
#include <QString>
#include <Qt::NavigationMode>
#include <QPalette>
#include <QWidgetList>
#include <Qt::LayoutDirection>
#include <QScreen>
#include <qGuiApp>
#include <QSessionManager> 
#include <QObject>
#include <QWindow::isTopLevel>
#include <QWindow::close>
#include <QStyle>
#include <QWebFrame>
#include <QWebHistory>
#include <QStackedWidget>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QPushButton>
#include <QList>
#include <QUrl>

class WebPage;

namespace Ui {
class WebView;
}


class WebView : public QWebView
{
    Q_OBJECT

public:
    explicit WebView(QWidget *parent = 0);
    ~WebView();

    // Receives web nav buttons from parent webview
    void sendButtons(QPushButton *bb, QPushButton *hb, QPushButton *fb);

public slots:
    void myBack();
    void myHome();
    void myForward();
    void myReload();
    void myOpenUrl(QUrl url);
    bool isTrustedUrl(QUrl url);
    void sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist);

private:
    Ui::WebView *ui;
    int m_loadProgress;
    bool fTrustedUrlsSet;
    QPushButton *backButton;
    QPushButton *homeButton;
    QPushButton *forwardButton;

    // Set button enabled/disabled states
    void setButtonStates(bool canGoBack, bool canGoHome, bool canGoForward);

    QList<QString> trustedUrls;
};

#endif
