#pragma once
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QMap>
#include <QTextCodec>
#include "logger_types.hpp"
#include "wp_settings.hpp"


namespace logger
{


class WpLogger {


    bool enabled;
    file_list_type fl;
    const WpSettings *wp_settings;

    void check();

    public:
        WpLogger(const WpSettings &wp_settings);
        ~WpLogger();
        void log_line( const string_type &line, string_type location="");
        void add_channel(string_type channel);
        void rem_channel(string_type channel);



};

}
