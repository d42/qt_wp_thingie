// =====================================================================================
// 
//       Filename:  wp_main.cpp
// 
//    Description:  d
// 
//        Version:  1.0
//        Created:  05/12/2013 04:42:00 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  DaZ (), daz.root@gmail.com
//        Company:  
// 
// =======================================================================================
#include "wp_main.hpp"


WpMain::WpMain()
{


    wp_prepare = new WpPrepare(wp_settings);
    wp_irc = new WpIRC(wp_settings, wp_prepare);
    
    connect(wp_prepare, SIGNAL(finished()),
            this, SLOT(connect_to_server()));
}

WpMain::~WpMain()
{

}

void
WpMain::connect_to_server()
{
    this->wp_irc->connect();
}

void
WpMain::make_connection()
{

}

