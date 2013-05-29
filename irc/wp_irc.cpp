#include "wp_irc.hpp"


namespace irc
{

WpIRC::WpIRC(const WpSettings &wp_settings, WpPrepare *parent):WpIRCBase(wp_settings, parent)
{
}
WpIRC::~WpIRC()
{

}

//void
//WpIRC::IRC_on_ping(const map_list_type &parsed_line)
//{

    //this->send_pong("dupa");
//}


//void
//WpIRC::IRC_on_484(const map_list_type &parsed_line)
//{
    //this->join_channels();

//}

//void
//WpIRC::IRC_on_433(const map_list_type &parsed_line)
//{
//qDebug() << "oops";
//}


void
WpIRC::IRC_on_notice(const map_list_type &parsed_line)
{
    string_type line("::");
    qDebug() << parsed_line;
}



//TODO refactorize me plx
void
WpIRC::IRC_on_quit(const map_list_type &parsed_line)
{
    string_type line("<-- %1 ( %2 )");
    string_type nick = nick_from_wp(parsed_line["prefix"][0].split('!')[0]);
    string_type reason = parsed_line["params"].join(" ");
    wp_logger.log_line(line.arg(nick).arg(reason));
}


void
WpIRC::IRC_on_privmsg(const map_list_type &parsed_line)
{
    //nick:message
    string_type line("%1:%2");
    string_type nick = nick_from_wp(parsed_line["prefix"][0].split('!')[0]);
    string_type channel = parsed_line["params"][0];
    string_type mesg = parsed_line["args"].join(" ");
    wp_logger.log_line(line.arg(nick).arg(mesg), channel);
}

void
WpIRC::IRC_on_part(const map_list_type &parsed_line)
{
    string_type line("<-- %1 ( %2 )");
    string_type nick = nick_from_wp(parsed_line["prefix"][0].split('!')[0]);
    string_type mesg = parsed_line["args"].join(" ");
    string_type channel = parsed_line["params"][0];
    wp_logger.log_line(line.arg(nick).arg(mesg), channel);

}


void
WpIRC::IRC_on_join(const map_list_type &parsed_line)
{
    string_type line("--> %1 ");
    string_type nick = nick_from_wp(parsed_line["prefix"][0].split('!')[0]);
    //string_type mesg = parsed_line["args"].join(" ");
    string_type channel = parsed_line["params"][0];
    wp_logger.log_line(line.arg(nick), channel);

}



}
