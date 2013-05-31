#include <QString>
#include <QProcess>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include "wp_js_parser_types.hpp"



namespace utils
{
static string_type node_path =
    "/usr/bin/node";

static list_type node_params("-e");

class abstract_js_parser:public object_type
{
    Q_OBJECT

    protected:
    object_type *parent;

    public:
        abstract_js_parser(object_type *parent=0);
        virtual void parse(const string_type &js)=0;
};


class node_js_parser:public abstract_js_parser
{
    Q_OBJECT

    process_type p;

    public:
       node_js_parser(object_type *parent=0);
        virtual void parse(const string_type &js);
};
}
