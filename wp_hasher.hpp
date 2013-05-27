// =====================================================================================
// 
//       Filename:  hasher.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/27/2013 08:41:54 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  DaZ (), daz.root@gmail.com
//        Company:  
// 
// =====================================================================================
#pragma once
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QChar>
#include <QList>

typedef QString string_type;
typedef QChar char_type;
typedef QDateTime time_type;
typedef QList<qint8> time_list;

string_type hasher(const string_type &magic, const string_type &salt);



