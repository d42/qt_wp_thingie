#include <QApplication>
#include <QWidget>
#include <QtGlobal>
#include <QDebug>
#include "wp_main.hpp"
#include "wp_irc.hpp"

int main(int argc, char *argv[])
{
    WpIRC a;
    WpIRC b = a;
    QApplication app(argc, argv);
    WpMain foo;
    return app.exec();
}
