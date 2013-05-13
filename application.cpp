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

    WpMain foo;

    //nick_to_wp("dupa");
    //nick_to_wp(QString::fromUtf8("dupaDópa"));

    //qDebug() << "why";
    return app.exec();
}
