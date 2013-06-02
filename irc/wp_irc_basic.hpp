#include <QString>
#include <QStringList>
#include <QTcpSocket>
#include <QTextCodec>
#include <QObject>
#include <QtGlobal>
#include <QDebug>
#include "wp_utils.hpp"
#include "wp_logger.hpp"
#include "wp_irc_types.hpp"
#include "wp_settings.hpp"
#include "wp_hasher.hpp"

namespace irc
{

class WpIRCBase:public object_type
{

    Q_OBJECT


    codec_type *codec;
    const utils::WpPrepare *parent;
    const settings::WpSettings *wp_settings;
    tcp_socket_type irc_connection;
    map_list_type parse_msg(string_type line)const;
    void handle_command(const map_list_type &parsed_line);

    WpIRCBase(WpIRCBase &derp);

    public:
        void join_channels();
        void set_nick(const string_type &nick);
        void set_realname(const string_type );
        void send_nick(const string_type &nick); 
        void send_user(const string_type &username, const string_type &realname, const string_type &hostname);
        void send_pass(const string_type &pass);
        void send_magic(const string_type &magic, const string_type &salt);
        void send_join(const string_type &channel);
        void send_quit(const string_type &message);
        void send_pong(const string_type &server);
        void send_raw(const string_type &message);
        void send_privmsg(const string_type &target, const string_type &message);
        void connect();
    
    protected:
        virtual void send_data(const string_type &line);
        WpIRCBase(const settings::WpSettings &wp_settings, utils::WpPrepare *parent = 0);
        ~WpIRCBase();

        logger::WpLogger wp_logger;
        virtual void IRC_on_privmsg(const map_list_type &parsed_line); 
        virtual void IRC_on_magic(const map_list_type &parsed_line);
        virtual void IRC_on_ping(const map_list_type &parsed_line);
        virtual void IRC_on_mode(const map_list_type &parsed_line);
        virtual void IRC_on_part(const map_list_type &parsed_line);
        virtual void IRC_on_join(const map_list_type &parsed_line);
        virtual void IRC_on_quit(const map_list_type &parsed_line);
        virtual void IRC_on_484(const map_list_type &parsed_line); //logged in
        virtual void IRC_on_433(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_notice(const map_list_type &parsed_line); 
        virtual void IRC_on_magicu(const map_list_type &parsed_line); //magic
        //void IRC_on_(const map_list_type &parsed_line);

    private slots:


        void on_connect();
        void on_incoming_data();


};


}
