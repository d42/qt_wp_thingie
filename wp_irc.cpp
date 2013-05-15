#include "wp_irc.hpp"


WpIRC::WpIRC(const WpSettings &wp_settings, WpPrepare *parent):parent(parent),wp_settings(&wp_settings)
{
}
WpIRC::~WpIRC()
{

}

void
WpIRC::connect()
{
    irc_connection = new tcp_socket_type(this);
    irc_connection->connectToHost(
            this->wp_settings->get_server(),
            this->wp_settings->get_port()
            );

    object_type::connect(irc_connection, SIGNAL(connected()),
            this, SLOT(on_connect()));
    object_type::connect(irc_connection, SIGNAL(readyRead()),
            this, SLOT(on_incoming_data()));


}

void
WpIRC::on_connect()
{
    qDebug() << "connected!";
    this->send_nick(
            nick_to_wp(
                wp_settings->get_nick(), 
                wp_settings->get_auth())
            );
    this->send_pass(
            parent->get_ticket());

}

void
WpIRC::on_incoming_data()
{
    qDebug() << "on_incoming_data";
    string_type line;
    line = irc_connection->readLine();
    map_list_type parsed_line(this->parse_msg(line));


    if(parsed_line["command"][0] == "MAGIC" )
    {
        qDebug() << "zomfg it's full of magic";
        this->IRC_on_magic(parsed_line);

    }
    //qDebug() << line;

    if(irc_connection->canReadLine())
    {
        on_incoming_data();
    }
}

void
WpIRC::send_nick(const string_type &nick)
{
    qDebug() << "send_nick";
    string_type send_line = string_type("NICK %1").arg(nick);

    this->send_data(send_line);
}
map_list_type
WpIRC::parse_msg(string_type line)const
{
    qDebug() << line;
    map_list_type return_map;
    //:<prefix> <command> <params> :<trailing>

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
        //qDebug() << " no : ";

    }


    return return_map;

}

void
WpIRC::send_data(const string_type &line)
{
    qDebug() << line;

    string_type newline("%1\r\n");

    this->irc_connection->write(newline.arg(line).toAscii());

}
void
WpIRC::IRC_on_magic(const map_list_type &parsed_line)
{
    qDebug() << "IRC_on_magic";
    this->send_magic(parent->get_magic(), parsed_line["args"][0]);

}
void 
WpIRC::send_magic(const string_type &magic, const string_type &salt)
{

    string_type line("USER 192.128.1.2 8 %1 :Czat-Applet");
    string_type hash(hasher(magic, salt));
    this->send_data(line.arg(hash));
}
void
WpIRC::send_pass(const string_type &pass)
{
string_type line("PASS %1");
    this->send_data(line.arg(string_type(pass.toAscii().toPercentEncoding())));

}
