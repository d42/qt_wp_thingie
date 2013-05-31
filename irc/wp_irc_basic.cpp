// =====================================================================================
// 
//       Filename:  wp_irc.basic.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/27/2013 10:08:44 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  DaZ (), daz.root@gmail.com
//        Company:  
// 
// =====================================================================================
#include "wp_irc_basic.hpp"

namespace irc
{

string_type realname("USER 192.128.1.2 8 %1 :Czat-Applet");

WpIRCBase::WpIRCBase(const settings::WpSettings &wp_settings, utils::WpPrepare *parent):parent(parent),wp_settings(&wp_settings),wp_logger(wp_settings)
{
    codec = codec_type::codecForName("ISO 8859-2");
}
WpIRCBase::~WpIRCBase()
{
}

void
WpIRCBase::connect()
{
    irc_connection.connectToHost(
            this->wp_settings->get_server(),
            this->wp_settings->get_port()
            );

    object_type::connect(&irc_connection, SIGNAL(connected()),
            this, SLOT(on_connect()));
    object_type::connect(&irc_connection, SIGNAL(readyRead()),
            this, SLOT(on_incoming_data()));


}

void
WpIRCBase::on_connect()
{
    this->send_nick(
            utils::nick_to_wp(
                wp_settings->get_nick(), 
                wp_settings->get_auth())
            );
    this->send_pass(
            parent->get_ticket());

}


void
WpIRCBase::handle_command(const map_list_type &parsed_line)
{
    string_type command = parsed_line["command"][0];
    if(command == "MAGIC" )
    {
        IRC_on_magic(parsed_line);
    }
    else if(command == "PRIVMSG")
    {
        IRC_on_privmsg(parsed_line);
    }
    else if(command == "QUIT")
    {
        IRC_on_quit(parsed_line);
    }
    else if(command == "PING")
    {
        IRC_on_ping(parsed_line);
    }
    else if(command == "PART")
    {
        IRC_on_part(parsed_line);
    }
    else if(command == "WPJOIN")
    {
        IRC_on_join(parsed_line);
    }
    else if(command == "484")
    {
        IRC_on_484(parsed_line);
    }
    else if(command == "433")
    {
        IRC_on_433(parsed_line);
    }
    else if(command == "NOTICE")
    {
        IRC_on_notice(parsed_line);
    }

    else if(command == "UMAGIC")
    {
        IRC_on_umagic(parsed_line);
    }
}

void
WpIRCBase::on_incoming_data()
{
    string_type line;
    //line = irc_connection.readLine();
    line = codec->toUnicode(
            irc_connection.readLine()
            );

    qDebug() << line;

    map_list_type parsed_line(this->parse_msg(line));
    this->handle_command(parsed_line);

    if(irc_connection.canReadLine()){on_incoming_data();}
}

void
WpIRCBase::send_nick(const string_type &nick)
{
    string_type send_line = string_type("NICK %1").arg(nick);

    this->send_data(send_line);
}
map_list_type
WpIRCBase::parse_msg(string_type line)const
{
    map_list_type return_map;
    //:<prefix> <command> <params> :<trailing>
    //PING :<server>
    //MAGICU 88fc209d1da5b734f7e674624c319505
    //:wpserv@czati1a.wp.pl MODE #seks -v bpi-colo|de00 
    if(!line.contains(':'))
    {

    }

    if(line.at(0) == ':')
    {
        line = line.mid(1);

        return_map["prefix"] << line.section(' ',0,0);
        line                 = line.section(' ',1).trimmed();
    }
    else 
    {
        line = line.trimmed();
    }

    
    if( line.contains(":"))
    {

        return_map["command"] << line.section(' ',0,0).split(' ');
        line                  = line.section(' ', 1);

        return_map["params"] << line.section(" :",0,0).split(' ');
        return_map["args"]  << line.section(':',1).split(' ');
    }
    else 
    {
    }

    return return_map;

}

void
WpIRCBase::send_data(const string_type &line)
{
    string_type newline("%1\r\n");
    this->irc_connection.write(newline.arg(line).toAscii());
}

void
WpIRCBase::IRC_on_magic(const map_list_type &parsed_line)
{
    qDebug() << "IRC_on_magic";
    this->send_magic(parent->get_magic(), parsed_line["args"][0]);

}
void 
WpIRCBase::send_magic(const string_type &magic, const string_type &salt)
{

    string_type line(realname);
    string_type hash(utils::hasher(magic, salt));
    this->send_data(line.arg(hash));
}
void
WpIRCBase::send_pass(const string_type &pass)
{
string_type line("PASS %1");
    this->send_data(line.arg(string_type(pass.toAscii().toPercentEncoding())));
}

void
WpIRCBase::IRC_on_ping(const map_list_type &parsed_line)
{

    qDebug() << parsed_line;
    this->send_pong(parsed_line["params"][0]);
}
void
WpIRCBase::send_pong(const string_type &server)
{
    string_type line(":PONG %1");

    this->send_data(line.arg(server));

}


void
WpIRCBase::IRC_on_484(const map_list_type &parsed_line)
{
    this->join_channels();

}

void
WpIRCBase::IRC_on_433(const map_list_type &parsed_line)
{
    qDebug() << "this nickname is already taken"; 
    // there's no way to change it on the fly, unfortunately :c


}


void
WpIRCBase::IRC_on_notice(const map_list_type &parsed_line)
{
    //qDebug() << "notice";
}

void
WpIRCBase::join_channels()
{
    for(auto &x: wp_settings->get_channels())
    {
        this->send_join(x);

    }

}
void
WpIRCBase::send_join(const string_type &channel)
{
    string_type line("WPJOIN %1");
    this->send_data(line.arg(channel));
    //TODO: some fancy way to figure out whether we've actually joined the channel.
    wp_logger.add_channel(channel);

}
void
WpIRCBase::IRC_on_mode(const map_list_type &parsed_line)
{
}


void
WpIRCBase::IRC_on_quit(const map_list_type &parsed_line)
{
}

void
WpIRCBase::IRC_on_privmsg(const map_list_type &parsed_line)
{
}


void
WpIRCBase::IRC_on_join(const map_list_type &parsed_line)
{
}


void
WpIRCBase::IRC_on_part(const map_list_type &parsed_line)
{
}


void
WpIRCBase::IRC_on_umagic(const map_list_type &parsed_line)
{
}


}
