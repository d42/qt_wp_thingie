#pragma once
#include <QString>
#include <QChar>
#include <QStringList>
#include <QProcess>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QRegExp>
#include <QObject>
#include <QMap>
#include <QLineEdit>
#include <QProcess>
#include <iostream>
#include "wp_utils_types.hpp"
#include "wp_utils_exceptions.hpp"
#include "ui_captcha.h"
#include "wp_js_parser.hpp"
#include "wp_settings.hpp"


namespace utils
{


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

static string_type param_regexp = 
    "name=\"(%1)\" value=\"(.+)\"";


class WpPrepare:public QObject
{
    Q_OBJECT



    const settings::WpSettings *settings;
    map_string_type session_variables;
    widget_type captcha_widget;
    image_type captcha;

    network_manager_type network_manager;
    network_reply_type *reply;


    abstract_js_parser *js_parser;
    void get_captcha(const url_type& captcha_url=captcha_url);
    void choose_js_parser();
    void params_to_dictionary(const string_type &params);

    signals:
    void captcha_typed_in();
    void params_to_dictionary_finished();
    void finished();



    public:
    WpPrepare(const settings::WpSettings &wp_settings);
    ~WpPrepare();

    string_type get_magic()const;
    string_type get_ticket()const;
    private slots:
    void get_html();
    void get_ticket();
    void get_html_finished();
    void get_captcha_finished();
    void js_parser_finished();
    void get_ticket_finished();
    void captcha_resolve();
    void captcha_input();
};

string_type nick_to_wp(const string_type &nick, bool auth=false);
string_type nick_from_wp(const string_type &nick);


}
