#include "wp_utils.hpp"
#include "wp_settings.hpp"
#include "wp_irc.hpp"
class WpMain:public object_type
{
    Q_OBJECT
    settings::WpSettings wp_settings;
    utils::WpPrepare wp_prepare;
    irc::WpIRC wp_irc;
    WpMain(WpMain &w);

    private slots:
        void connect_to_server();
    public:
        WpMain();
        ~WpMain();


};
