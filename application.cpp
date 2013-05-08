#include <QApplication>
#include <QWidget>
#include <QtGlobal>
#include <QDebug>
#include "logger.hpp"
#include "wp_utils.hpp"

int main(int argc, char *argv[])
{
    //QApplication::setOrganizationName("DaZ soft zią!");
    //QApplication::setApplicationName("wp-bott");
    QApplication app(argc, argv);

    qDebug() << "foobarfoo";
    wp_prepare foo;
    //foo.show_captcha();
    //foo.captcha_window.show();

    return app.exec();
}
