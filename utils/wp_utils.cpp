#include "wp_utils.hpp"

namespace utils
{

WpPrepare::WpPrepare(const settings::WpSettings &wp_settings):settings(&wp_settings)
{
    this->choose_js_parser();
    connect(this, SIGNAL(captcha_typed_in()),
            this, SLOT(get_html()));

    connect(this, SIGNAL(params_to_dictionary_finished()),
            this, SLOT(get_ticket()));


    this->get_captcha();

}
WpPrepare::~WpPrepare()
{
    delete js_parser;
}

void
WpPrepare::get_html()
{
    url_type params_post;

    params_post.addQueryItem("i","1");
    params_post.addQueryItem("regulamin","tak");
    params_post.addQueryItem("auth",(settings->get_auth()? "tak":"nie"));
    params_post.addQueryItem("nick", settings->get_nick());
    params_post.addQueryItem("simg", this->session_variables["captcha"]);
    params_post.addQueryItem("x","52");
    params_post.addQueryItem("y","12");

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

    reply  = qobject_cast<network_reply_type *> (sender());
    string_type html_string(reply->readAll());


    //disregard DOM, acquire JS
    int start = html_string.indexOf("function _");
    if(start == -1)
    {
        this->get_captcha();
    }
    else
    {
    int end = html_string.indexOf(";//",start) - 21;
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
    connect(reply, SIGNAL(finished()),
            this, SLOT(get_captcha_finished()));

}



void
WpPrepare::get_captcha_finished()
{
        reply  = qobject_cast<network_reply_type *> (sender());
    
        url_type redirect_url(reply->attribute ( QNetworkRequest::RedirectionTargetAttribute ).toUrl());

        url_type new_url=reply->url();
        session_variables["ticaid"] = redirect_url.encodedQueryItemValue("ticaid");
        new_url.addQueryItem("ticaid", session_variables["ticaid"]);

        if(!redirect_url.isEmpty())
        { this->get_captcha(new_url); }
        else
        {
            this->captcha.loadFromData(reply->readAll());
            if(this->captcha.size().isEmpty())
            { throw captcha_is_empty_exception();}
            this->captcha_resolve();
        }
}

void
WpPrepare::captcha_resolve() //TODO: less retarded
{

    static bool setup = false;
    if(!setup)
    {
        Ui_captcha_form ui;
        ui.setupUi(&captcha_widget);

        connect(ui.captcha_text, SIGNAL(returnPressed()),this, SLOT(captcha_input()));

        ui.captcha_image->setPixmap(captcha);
        captcha_widget.show();
        setup = true;
    }
    else
    {
        captcha_widget.show();

    }

}
void
WpPrepare::captcha_input()
{
    line_edit_type *captcha = qobject_cast<line_edit_type*>(sender());
    this->session_variables["captcha"] = captcha->text();
    captcha->parentWidget()->hide();

    emit captcha_typed_in();
}



void
WpPrepare::choose_js_parser()
{
    if(file_type(node_path).exists())
    {
        js_parser = new node_js_parser(this);
    }
    else
    {
        throw no_js_parser_avail_exception();
    }
}

void
WpPrepare::js_parser_finished()
{
    process_type *p = qobject_cast<process_type *>(sender());
    this->params_to_dictionary(p->readAllStandardOutput());
}

void
WpPrepare::params_to_dictionary(const string_type &params)
{

    regexp_type re;

    //TODO: less retarded
    for(auto x:{"magic","nickFull"})
    {
        regexp_type re(param_regexp.arg(x));
        re.setMinimal(true);
        re.indexIn(params);
        this->session_variables[re.cap(1)] = re.cap(2);
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
        { wpdticket = x.value(); break;}
    }

    string_type query_nick;
    network_request_type request;

    if(settings->get_auth())
        {}
    else
        {query_nick = string_type("~%1").arg(settings->get_nick());}

    params_get.addQueryItem("nick", query_nick);
    params_get.addQueryItem("wpdticket", wpdticket);
    params_get.addQueryItem("i","0");

    request.setUrl( params_get );
    request.setRawHeader("user-Agent", java_user_agent);
    
    reply = network_manager.get(request);
    connect(reply, SIGNAL(finished()),
            this,  SLOT(get_ticket_finished()));
}

void 
WpPrepare::get_ticket_finished()
{
    bytes_type r = reply->readAll().trimmed();
    this->session_variables["ticket"] = r;
    emit finished();
}

    string_type pol_chars = string_type::fromUtf8("ęóąśłżźćń.:;!@#$%^&*()");
                            string_type int_chars("eoaslzxcnkdf1234567890");

string_type
nick_to_wp(const string_type &nick, bool auth)
{

    unsigned len = (1 + nick.length()/2);
    len = (len % 2 ? len+1 : len);
    string_type cap_letters;
    string_type pol_letters;
    cap_letters.reserve(len/2); // len is kind of a half already, so /4
    pol_letters.reserve(len/2); // because Fh = 1111b
    string_type formatted_nick;
    formatted_nick.reserve(len+nick.length()+1);
    if(!auth)
        {formatted_nick.append("a");}
    for(auto &x_p: nick)
    {
        char_type x(x_p); //TODO: is this t
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
    pol_letters = string_type::number(pol_letters.toInt(&ok, 2),16).rightJustified(len/2,'0');
    cap_letters = string_type::number(cap_letters.toInt(&ok, 2),16).rightJustified(len/2,'0');
    return string_type("%1|%2%3").arg(formatted_nick).arg(pol_letters).arg(cap_letters);


}


string_type
nick_from_wp(const string_type &nickname)
{
    if(!nickname.contains('|'))
        {return nickname;}

    string_list nick_list = nickname.split('|');
    string_type nick = nick_list[0].mid(1);
    string_type &nick2= nick_list[1];
    unsigned len = nick.length()/2;

    if(len%2)
        {len += 1;}
    unsigned caps = nick2.left(len/2).toUInt(0,16);
    unsigned pols = nick2.right(len/2).toUInt(0,16);

    unsigned christian_magic =  (len*2 + ((len*2)%4)-1);
    unsigned mask = 1;
    mask <<= christian_magic;


    for (unsigned i = 0; i < len*2; i++)
    {
        if((pols & mask))
        {
            nick[i] = pol_chars[int_chars.indexOf(nick[i])];
        }
        if((caps & mask)) 
        {
            nick[i] = nick[i].toUpper();

        }
        mask >>= 1;
    }
    string_type bitfield = string_type::number(nick2.toLongLong(0, 16), 2);
    return nick;
}

string_type
WpPrepare::get_magic()const
{
    return this->session_variables["magic"];
}

//void
//set_magic(const string_type &magic)
//{
    //this->session_variables["magic"] = magic;
//}
string_type
WpPrepare::get_ticket()const
{
    return this->session_variables["ticket"];
}

}
