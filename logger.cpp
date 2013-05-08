#include "logger.hpp"
logger::logger()
{
    output_file = new file_type("file");
}

void
logger::log(const string_type &line)
{
    if(output_file->open(file_type::WriteOnly)) {
        text_stream_type out(output_file);
        out << line << endl;
    }

}
