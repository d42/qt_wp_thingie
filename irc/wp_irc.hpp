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

    public:
        WpIRC(const settings::WpSettings &wp_settings, utils::WpPrepare *parent = 0);
        ~WpIRC();
    
    private:
        virtual void IRC_on_quit(const map_list_type &parsed_line);
        virtual void IRC_on_privmsg(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_notice(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_part(const map_list_type &parsed_line); //nickname in use
        virtual void IRC_on_join(const map_list_type &parsed_line); //nickname in use
};



}
