#pragma once
#include "wp_utils.hpp"
#include "wp_settings.hpp"
#include "wp_irc.hpp"
class WpMain:public object_type
{
    Q_OBJECT
    WpPrepare *wp_prepare;
    WpIRC *wp_irc;
    WpSettings wp_settings;



    private slots:
        void connect_to_server();
    public:
        WpMain();
        ~WpMain();
        void make_connection();
};
