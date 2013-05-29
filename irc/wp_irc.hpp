#include <QString>
#include <QStringList>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include "wp_utils.hpp"
#include "wp_irc_types.hpp"
#include "wp_settings.hpp"
#include "wp_hasher.hpp"
#include "wp_irc_basic.hpp"

namespace irc
{


class WpIRC:public WpIRCBase
{

    Q_OBJECT

    //const WpPrepare *parent;
    //const WpSettings *wp_settings;
    //tcp_socket_type irc_connection;
    //map_list_type parse_msg(string_type line)const;
    //void handle_command(const map_list_type &parsed_line);

    public:
        WpIRC(const WpSettings &wp_settings, WpPrepare *parent = 0);
        ~WpIRC();
        //void join_channels();
        //void set_nick(const string_type &nick);
        //void set_realname(const string_type );
        //void send_nick(const string_type &nick); //TODO: separate non-const send 
        //void send_user(const string_type &username, const string_type &realname, const string_type &hostname);
        //void send_pass(const string_type &pass);
        //void send_magic(const string_type &magic, const string_type &salt);
        //void send_join(const string_type &channel);
        //void send_quit(const string_type &message);
        //void send_pong(const string_type &server);
        //void send_raw(const string_type &message);
        //void send_privmsg(const string_type &target, const string_type &message);
        //void connect();
    
    private:
        void send_data(const string_type &line);

        //void IRC_on_magic(const map_list_type &parsed_line);
        //void IRC_on_ping(const map_list_type &parsed_line);
        //void IRC_on_mode(const map_list_type &parsed_line);
        //void IRC_on_484(const map_list_type &parsed_line); //logged in
        //void IRC_on_433(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_quit(const map_list_type &parsed_line);
        virtual void IRC_on_privmsg(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_notice(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_part(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_join(const map_list_type &parsed_line); //nickname in use
        //void IRC_on_(const map_list_type &parsed_line);

    //private slots:


        //void on_connect();
        //void on_incoming_data();


};



}
