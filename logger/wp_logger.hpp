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
#include "wp_utils.hpp"
#include <unistd.h>

namespace logger
{


class WpLogger {


    file_list_type fl;
    const settings::WpSettings *wp_settings;

    void check();


    void write( file_type *f, const string_type &s);
    WpLogger(WpLogger &wp_logger);

    public:

        WpLogger(const settings::WpSettings &wp_settings);
        ~WpLogger();
        void log_line( const string_type &line, string_type location="");
        void add_channel(string_type channel);
        void rem_channel(string_type channel);

};

}
