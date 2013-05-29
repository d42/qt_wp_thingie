#include "wp_main.hpp"


WpMain::WpMain():wp_prepare(wp_settings),wp_irc(wp_settings,&wp_prepare)
{

    connect(&wp_prepare, SIGNAL(finished()),
            this, SLOT(connect_to_server()));
}

WpMain::~WpMain()
{

}

void
WpMain::connect_to_server()
{
    this->wp_irc.connect();
}
