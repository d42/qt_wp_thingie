#include "wp_js_parser.hpp"


namespace utils
{

abstract_js_parser::abstract_js_parser(object_type *parent):parent(parent)
{

}

node_js_parser::node_js_parser(object_type *parent):abstract_js_parser(parent)
{

}
void
node_js_parser::parse(const string_type &js)
{
    string_type js_console(js + "console.log(txt());");
    qDebug() << "parse";
    //qDebug() << js;
    process_type *p_p = &p; //FIXME:
    QObject::connect(p_p , SIGNAL(finished(int, QProcess::ExitStatus )),
            this->parent, SLOT(js_parser_finished()));

    p.start(node_path,(node_params << js_console ));
}
}
