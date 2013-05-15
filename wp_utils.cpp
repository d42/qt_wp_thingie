#include "wp_utils.hpp"
//static bytes_type user_agent =
    //"Mozilla/5.0 (Windows NT 6.1; rv:16.0) Gecko/20100101 Firefox/16.0";
//static bytes_type java_user_agent =
    //"User-Agent':'User-Agent: Mozilla/4.0 (Windows 7 6.1) Java/1.7.0_09";
////url_type captcha_url =
    ////string_type("http://si.wp.pl/obrazek?width=200&height=60&fSize=27&sn=czat");
//static url_type html_applet_url("http://czat.wp.pl/i,1,chat.html");
//static url_type html_ticket_url("http://czati1.wp.pl/getticket.html");


WpPrepare::WpPrepare(const WpSettings &wp_settings):settings(&wp_settings)
{
    //this->settings["nick"] = "ania12lat";
    this->choose_js_parser();
    connect(this, SIGNAL(captcha_typed_in()),
            this, SLOT(get_html()));

    connect(this, SIGNAL(params_to_dictionary_finished()),
            this, SLOT(get_ticket()));

    this->network_manager.setCookieJar(new cookiejar_type);


    this->get_captcha();

}
WpPrepare::~WpPrepare()
{
    delete js_parser;
}

void
WpPrepare::get_html()
{
    qDebug()  << "get_html";
    url_type params_post;

    encode_query<string_type>(params_post, 
            "i","1",
            "regulamin","tak",
            "auth","nie", //TODO: handle registered nicknames.
            "nick", settings->get_nick(), //TODO: load nickname from settings file
            "simg", this->session_variables["captcha"],
            "x","52",
            "y","12"
            );

    network_request_type request;
    request.setUrl(html_applet_url);
    request.setRawHeader("User-Agent", user_agent);
    request.setRawHeader("content-type", "application/x-www-form-urlencoded");

    network_reply_type *reply = network_manager.post(request, params_post.encodedQuery());
    connect(reply, SIGNAL(finished()),
            this, SLOT(get_html_finished()));


}

void
WpPrepare::get_html_finished()
{
    qDebug() << "get_html_finished";

    reply  = qobject_cast<network_reply_type *> (sender());
    string_type html_string(reply->readAll());


    //disregard DOM, acquire JS
    int start = html_string.indexOf("function _");
    int end = html_string.indexOf(";//",start) - 21;
    if(start == -1)
    {
        qDebug() << "bad captcha code";
        qApp->quit();
        //FIXME:

    }
    else
    {
        html_string = html_string.mid(start, (end-start) );
        this->js_parser->parse(html_string);
    }
}

void
WpPrepare::get_captcha(const url_type &captcha_url /*=captcha_url */)
{
    network_request_type request;

    request.setUrl(captcha_url);
    request.setRawHeader("User-Agent", user_agent);

    reply = network_manager.get(request);
    QObject::connect(reply, SIGNAL(finished()),
            this, SLOT(get_captcha_finished()));

}



void
WpPrepare::get_captcha_finished()
{
    //FIXME: error handling
        reply  = qobject_cast<network_reply_type *> (sender());
    
        url_type redirect_url(reply->attribute ( QNetworkRequest::RedirectionTargetAttribute ).toUrl());

        url_type new_url=reply->url();
        session_variables["ticaid"] = redirect_url.encodedQueryItemValue("ticaid");
        new_url.addQueryItem("ticaid", session_variables["ticaid"]);

        if(!redirect_url.isEmpty())
        {
            this->get_captcha(new_url);
        }
        else
        {
        this->captcha.loadFromData(reply->readAll());

        if(this->captcha.size().isEmpty())
        {
            qDebug() << "zomfg, something went wrong!";
        }
        this->captcha_resolve();
        }
}

void
WpPrepare::captcha_resolve() //TODO: different resolver support
{

    Ui_captcha_form ui;
    ui.setupUi(&captcha_widget);
    QObject::connect(ui.captcha_text, SIGNAL(returnPressed()),this, SLOT(captcha_input()));
    ui.captcha_image->setPixmap(captcha);
    captcha_widget.show();

}
void
WpPrepare::captcha_input()
{
    qDebug() << "captcha_input ";
    line_edit_type *captcha = qobject_cast<line_edit_type*>(sender());
    this->session_variables["captcha"] = captcha->text();
    captcha->parentWidget()->hide();

    emit captcha_typed_in();
}



void
WpPrepare::choose_js_parser()
{
    qDebug() <<"choose_js_parser";

    if(file_type(node_path).exists())
    {
        js_parser = new node_js_parser(this);
    }
    else
    {
        qDebug() << "zomfgfail";

    }



}

void
WpPrepare::js_parser_finished()
{
    qDebug() << "js_parser_finished";
    process_type *p = qobject_cast<process_type *>(sender());
    this->params_to_dictionary(p->readAllStandardOutput());
}

void
WpPrepare::params_to_dictionary(const string_type &params)
{

    qDebug() << "params_to_dictionary";

    regexp_type re;

    //TODO:
    for(auto x:{"magic","nickFull"})
    {
        regexp_type re(param_regexp.arg(x));
        re.setMinimal(true);
        re.indexIn(params);
        this->session_variables[re.cap(1)] = re.cap(2);
        //qDebug() << re.cap(1);
        //qDebug() << re.cap(2);
    }
    emit params_to_dictionary_finished();

}
void
WpPrepare::get_ticket()
{
    url_type params_get(html_ticket_url);
    string_type wpdticket;

    for (auto &x:network_manager.cookieJar()->cookiesForUrl(captcha_url))
    {
        if(x.name() == "wpdticket")
        {
            wpdticket = x.value();
        }
    }

    string_type query_nick;
    network_request_type request;

    if(settings->get_auth())
    {//TODO

    }
    else
    {
        query_nick = string_type("~%1").arg(settings->get_nick());
    }

    params_get.addQueryItem("nick", query_nick);
    params_get.addQueryItem("wpdticket", wpdticket);
    params_get.addQueryItem("i","0");

    qDebug() << params_get;

    request.setUrl( params_get );
    request.setRawHeader("user-Agent", java_user_agent);

    
    reply = network_manager.get(request);
    connect(reply, SIGNAL(finished()),
            this,  SLOT(get_ticket_finished()));
    
    //qDebug() << params_get;


}

void 
WpPrepare::get_ticket_finished()
{
    bytes_type r = reply->readAll().trimmed();
    qDebug() << r.toPercentEncoding();
    this->session_variables["ticket"] = r;

    emit finished();
}

string_type nick_to_wp(const string_type &nick, bool auth)
{
    string_type pol_chars = string_type::fromUtf8("ęóąśłżźćń.:;!@#$%^&*()");
    string_type int_chars("eoaslzxcnkdf1234567890");


    //TODO: make it do weird stuff
    unsigned len = (1 + nick.length()/2); //TODO: more testing
    len = (len % 2 ? len+1 : len);
    string_type cap_letters;
    string_type pol_letters;
    cap_letters.reserve(len/2);
    pol_letters.reserve(len/2);
    string_type formatted_nick;
    formatted_nick.reserve(len+nick.length()+1);
    if(!auth)
    {
        formatted_nick.append("a");
    }
    for(auto &x_p: nick)
    {
        char_type x(x_p); //TODO: find a better way to lose const.
        if(x.isUpper())
        {
            cap_letters.append("1");
            x = x.toLower();
        }
        else
        {
            cap_letters.append("0");
        }
        if(int pos = pol_chars.indexOf(x) != -1)
        {
            x = int_chars.at(pos);
            pol_letters.append("1");
        }
        else
        {
            pol_letters.append("0");

        }
        formatted_nick.append(x);
    }
    bool ok = false;
    pol_letters = string_type::number(pol_letters.toInt(&ok, 2),16).leftJustified(len/2,'0');
    cap_letters = string_type::number(cap_letters.toInt(&ok, 2),16).leftJustified(len/2,'0');
    return string_type("%1|%2%3").arg(formatted_nick).arg(pol_letters).arg(cap_letters);


}


string_type
WpPrepare::get_magic()const
{
    return this->session_variables["magic"];


}
string_type
WpPrepare::get_ticket()const
{
    return this->session_variables["ticket"];
}

