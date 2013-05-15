#include <QApplication>
#include <QWidget>
#include <QtGlobal>
#include <QDebug>
#include "wp_main.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WpMain foo;
    return app.exec();
}
