#pragma once
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QChar>
#include <QList>

namespace utils
{

    typedef QString string_type;
    typedef QChar char_type;
    typedef QDateTime time_type;
    typedef QList<qint8> time_list;

    string_type hasher(const string_type &magic, const string_type &salt);

}
