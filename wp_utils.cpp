#include "wp_utils.hpp"
//static bytes_type user_agent =
    //"Mozilla/5.0 (Windows NT 6.1; rv:16.0) Gecko/20100101 Firefox/16.0";
//static bytes_type java_user_agent =
    //"User-Agent':'User-Agent: Mozilla/4.0 (Windows 7 6.1) Java/1.7.0_09";
////url_type captcha_url =
    ////string_type("http://si.wp.pl/obrazek?width=200&height=60&fSize=27&sn=czat");
//static url_type html_applet_url("http://czat.wp.pl/i,1,chat.html");
//static url_type html_ticket_url("http://czati1.wp.pl/getticket.html");


wp_prepare::wp_prepare()
{
    qDebug() << "foobar";

    this->network_manager.setCookieJar(new cookiejar_type);
    this->get_captcha();
    //this->resolve_captcha();

}


void
wp_prepare::get_captcha(const url_type &captcha_url /*=captcha_url */)
{
    url_type url("http://czat.wp.pl/i,1,chat.html");
    network_request_type request;
    request.setUrl(captcha_url);
    request.setRawHeader("User-Agent", user_agent);
    network_reply_type *reply = network_manager.get(request);

    qDebug() << "showing mah captcha";
    QObject::connect(reply, SIGNAL(finished()),
            this, SLOT(show_captcha()));


}



void
wp_prepare::show_captcha()
{
    network_reply_type *reply  = qobject_cast<network_reply_type *> (sender());
    qDebug() << "showing mah captchaas a butto";
    qDebug() << reply->url();
    
        url_type redirect_url(reply->attribute ( QNetworkRequest::RedirectionTargetAttribute ).toUrl());

        url_type new_url=reply->url();
        new_url.addQueryItem("ticaid", redirect_url.encodedQueryItemValue("ticaid"));
        //url_type redirect_url(rVxeply->attribute ( QNetworkRequest::RedirectionTargetAttribute ).toUrl());
        if(!redirect_url.isEmpty())
        {
            this->get_captcha(new_url);

        }
        else
        {
        this->captcha.loadFromData(reply->readAll());
        this->resolve_captcha();
        }
}

void
wp_prepare::resolve_captcha()
{
    qDebug() <<"resolve_captcha much";
    label_type captcha_window;
    captcha_window.setPixmap(captcha);
    //captcha_window.show();
    //qDebug() <<"resolve_captcha much";


}
