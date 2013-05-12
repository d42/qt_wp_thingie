#include <QApplication>
#include <QWidget>
#include <QtGlobal>
#include <QDebug>
#include "logger.hpp"
#include "wp_main.hpp"

int main(int argc, char *argv[])
{
    //QApplication::setOrganizationName("DaZ soft zią!");
    //QApplication::setApplicationName("wp-bott");
    QApplication app(argc, argv);

    qDebug() << "foobarfoo";
    WpMain foo;

    qDebug() << "why";
    return app.exec();
}
