// =====================================================================================
// 
//       Filename:  wp_js_parser.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/10/2013 05:07:01 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  DaZ (), daz.root@gmail.com
//        Company:  
// 
// =====================================================================================
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
    qDebug() << "parse";
    //qDebug() << js;
    process_type *p_p = &p; //FIXME:
    QObject::connect(p_p , SIGNAL(finished(int, QProcess::ExitStatus )),
            this->parent, SLOT(js_parser_finished()));

    p.start(node_path,(node_params << js_console ));
}
