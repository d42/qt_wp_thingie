#include "wp_logger.hpp"

namespace logger
{



WpLogger::WpLogger(const WpSettings &wp_settings):wp_settings(&wp_settings)
{


}


void
WpLogger::check()
{
    dir_type d(wp_settings->get_path());
    if(d.exists() )
    {
    }
    else
    {
    dir_type().mkdir(wp_settings->get_path());

    }
}

WpLogger::~WpLogger()
{

}


void
WpLogger::log_line( const string_type &line, string_type location)
{

    if(!wp_settings->get_log_enabled())
    {
        return;
    }

    location = location.toLower();
    if(location!= "")
    {
        file_type *f = fl[location];
        f->write(time_type::currentDateTime().toString(wp_settings->get_timeformat()).toUtf8());
        f->write(" ");
        f->write(line.toUtf8());
        f->write("\n");
        f->flush();

    }

}

void
WpLogger::add_channel(string_type channel)
{

    if(!wp_settings->get_log_enabled())
    {
        return;
    }
    channel = channel.toLower();
    this->check();
    string_type path("%1/%2");
    file_type *f = new file_type(path
            .arg(wp_settings->get_path())
            .arg(channel)
            );
    f->open(QIODevice::WriteOnly); // write-only

    fl.insert(channel, f);

}
void
WpLogger::rem_channel(string_type channel)
{
    channel = channel.toLower();
        file_type *f = fl[channel];
        delete f;

}


}
