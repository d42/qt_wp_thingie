#pragma once
#include <QString>
//#include <QStringList>
#include <QProcess>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QProcess>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QRegExp>
#include <QObject>
#include <QMap>
#include <QLineEdit>
#include <iostream>
#include "wp_utils_types.hpp"
#include "ui_captcha.h"
#include "wp_js_parser.hpp"
#include "wp_settings.hpp"



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
    //"name=\"(.+)\" value=\"(.+)\"";
    "name=\"(%1)\" value=\"(.+)\"";
    //static string_type param_regexp = 
    //"name=\"(.*)\" value=\"(.*)\"";
    //
    //static string_type param_regexp =
    //"name";


class WpPrepare:public QObject
{
    Q_OBJECT


    //process_type js_parser;

    const WpSettings *settings;
    map_string_type session_variables;
    //map_string_type settings;
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
    WpPrepare(const WpSettings &wp_settings);
    label_type captcha_window;
    public slots:
    void get_html();
    void get_ticket();
    void get_html_finished();
    void get_captcha_finished();
    void js_parser_finished();
    void get_ticket_finished();
    void captcha_resolve();
    void captcha_input();
};




//TODO: not in the damn headers
template<typename s, typename... Args>
url_type&
encode_query(url_type &url,  const s &key, const s &value, Args... args )
{
    encode_query(url, key, value);
    return encode_query<s>(url, args...);
}
template<typename s>
url_type&
encode_query(url_type &url,  const s &key, const s &value)
{
    url.addQueryItem(key, value);
    return url;
}

//string_type
//Hasher(const list_type &magic, const list_type &salt)
//{

//}
