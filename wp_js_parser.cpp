#include "wp_js_parser.hpp"

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
    //process_type *p_p = &p; //FIXME: why would i do that
    QObject::connect(&p , SIGNAL(finished(int, QProcess::ExitStatus )),
            this->parent, SLOT(js_parser_finished()));

    p.start(node_path,(node_params << js_console ));
}
