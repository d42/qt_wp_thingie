#include <QTextStream>
#include <QFile>
#include "logger_types.hpp"





class logger {

    file_type *output_file;
    public:
        logger();
        void log(const string_type &line);



};

