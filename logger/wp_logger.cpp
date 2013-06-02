#include "wp_logger.hpp"

namespace logger
{
    string_type server_channel("server");


WpLogger::WpLogger(const settings::WpSettings &wp_settings):wp_settings(&wp_settings)
{
    enabled = wp_settings.get_log_enabled();
    check(); 
    add_channel(server_channel);

}

void 
WpLogger::write(file_type *f, const string_type &line)
{

            f->write(time_type::currentDateTime().toString(wp_settings->get_timeformat()).toUtf8());
            f->write(" ");
            f->write(line.toUtf8());
            f->write("\n");
            f->flush();

}

void
WpLogger::check()
{
    dir_type d(wp_settings->get_path());
    if(d.exists())
    {
    }
    else
    {
    dir_type().mkdir(wp_settings->get_path());

    }
}

WpLogger::~WpLogger()
{
    for(auto &x: fl)
    {
        delete x;
    }

}


void
WpLogger::log_line( const string_type &line, string_type location)
{

    if(!enabled)
    {
        return;
    }
    location = location.toLower();
        qDebug() << location << line;

    if(location!= "")
    {
        if(location[0] == '#')
        {
            file_type *f = fl[location];
            this->write(f,line);
        }
        else // it's an actual privmsg!
        {
                location = utils::nick_from_wp(location);

                if(fl.contains(location))
            {
                file_type *f = fl[location];
                this->write(f,line);
            }

            else
            {
                this->add_channel(location);
                file_type *f = fl[location];
                this->write(f,line);
            }
        }

    }
    else
    {
                file_type *f = fl[server_channel];
                this->write(f,line);

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
    string_type path("%1/%2");
    file_type *f = new file_type(path
            .arg(wp_settings->get_path())
            .arg(channel)
            );
    f->open(QIODevice::Append); // write-only

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
