#include "wp_irc.hpp"


namespace irc
{

WpIRC::WpIRC(const settings::WpSettings &wp_settings, utils::WpPrepare *parent):WpIRCBase(wp_settings, parent)
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

void ncm(string_type &nick, string_type &channel, string_type &mesg, const map_list_type &parsed_line)
{

    nick = utils::nick_from_wp(parsed_line["prefix"][0].split('!')[0]);
    channel = parsed_line["params"][0];
    mesg = parsed_line["args"].join(" ");
}

void
WpIRC::IRC_on_notice(const map_list_type &parsed_line)
{
    string_type line("::%1");
    //qDebug() << parsed_line;

    wp_logger.log_line(line.arg(parsed_line["args"].join(" ")));
}



//TODO refactorize me plx
void
WpIRC::IRC_on_quit(const map_list_type &parsed_line)
{
    string_type line("<-- %1 ( %2 )");
    string_type nick = utils::nick_from_wp(parsed_line["prefix"][0].split('!')[0]);
    string_type reason = parsed_line["params"].join(" ");
    wp_logger.log_line(line.arg(nick).arg(reason));
}


void
WpIRC::IRC_on_privmsg(const map_list_type &parsed_line)
{
    string_type line("%1:%2");

    string_type nick,mesg,channel;
    ncm(nick, channel, mesg, parsed_line);

    wp_logger.log_line(line.arg(nick).arg(mesg), channel);
}

void
WpIRC::IRC_on_part(const map_list_type &parsed_line)
{
    string_type line("<-- %1 ( %2 )");

    string_type nick,mesg,channel;
    ncm(nick, channel, mesg, parsed_line);

    wp_logger.log_line(line.arg(nick).arg(mesg), channel);

}


void
WpIRC::IRC_on_join(const map_list_type &parsed_line)
{
    string_type line("--> %1 ");
    string_type nick = utils::nick_from_wp(parsed_line["prefix"][0].split('!')[0]);
    string_type channel = parsed_line["params"][0];
    wp_logger.log_line(line.arg(nick), channel);

}



}
