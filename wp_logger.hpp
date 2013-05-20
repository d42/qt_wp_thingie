#pragma once
#include <QTextStream>
#include <QFile>
#include "logger_types.hpp"
#include "wp_settings.hpp"





class logger {

    public:
        logger(const WpSettings &wp_settings);
        void log_irc(const string_type &line);



};

