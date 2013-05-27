#pragma once
#include <QStringList>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QMap>
#include "wp_settings_types.hpp"


class WpSettings
{
    settings_type wp_settings;
    public:
        WpSettings();
        string_type get_nick()const;
        bool get_auth()const;
        string_type get_server()const;
        unsigned get_port()const;
        void set_defaults();
        list_type get_channels()const;
};
