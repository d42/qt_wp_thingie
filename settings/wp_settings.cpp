#include "wp_settings.hpp"

static string_type config_name =
    "wpirc.conf";

WpSettings::WpSettings():wp_settings(config_name, settings_type::IniFormat)
{
    set_defaults();

}
string_type
WpSettings::get_nick()const
{
    return this->wp_settings.value("all/nick").toString();
}
bool
WpSettings::get_auth()const
{
    if(wp_settings.value("irc/auth").toBool()) //TODO: authorization
    {
        qDebug() << "authorization unsupported ";
        return false;
    }
    return this->wp_settings.value("all/auth").toBool();
}


bool
WpSettings::get_log_enabled()const
{
    //if(wp_settings.value("log/enabled").toBool()) //TODO: authorization
    return this->wp_settings.value("log/enabled").toBool();
}


string_type
WpSettings::get_server()const
{
    return this->wp_settings.value("irc/server").toString();

}

string_type
WpSettings::get_path()const
{
    return this->wp_settings.value("log/path").toString();
}


string_type
WpSettings::get_timeformat()const
{
    return this->wp_settings.value("log/timeformat").toString();
}

unsigned
WpSettings::get_port()const
{
    return this->wp_settings.value("irc/port").toUInt();
}


list_type
WpSettings::get_channels()const
{
    return this->wp_settings.value("irc/channels").toString().split(",");
}

void
WpSettings::set_defaults()
{
    map_string_type d;
    d.insert("all/nick", "ania12lat");
    d.insert("all/auth", "false");
    d.insert("irc/server", "czati1.wp.pl");
    d.insert("irc/port", "5579");
    d.insert("irc/channels", "#podstawow,#foo");
    d.insert("irc/port", "5579");
    d.insert("log/enabled", "false");
    d.insert("log/path", "foo/");
    d.insert("log/timeformat", "HH:mm:ss");


    for(auto &x: d.uniqueKeys())
    {
        if(!wp_settings.contains(x))
        {
            wp_settings.setValue(x, d[x]);
        }

    }
    wp_settings.sync();
}
