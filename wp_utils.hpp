#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QObject>
#include "wp_utils_types.hpp"

static bytes_type user_agent =
    "Mozilla/5.0 (Windows NT 6.1; rv:16.0) Gecko/20100101 Firefox/16.0";
static bytes_type java_user_agent =
    "User-Agent':'User-Agent: Mozilla/4.0 (Windows 7 6.1) Java/1.7.0_09";
static url_type 
    html_applet_url("http://czat.wp.pl/i,1,chat.html");
static url_type 
    html_ticket_url("http://czati1.wp.pl/getticket.html");
static url_type 
    captcha_url("http://si.wp.pl/obrazek?width=200&height=60&fSize=27&sn=czat");

class wp_prepare:public QObject
{
    Q_OBJECT

    image_type captcha;
    network_manager_type network_manager;
    void get_captcha(const url_type& captcha_url=captcha_url);

    public:
    wp_prepare();
    //label_type captcha_window;
    public slots:
    void show_captcha();
    void resolve_captcha();
};
