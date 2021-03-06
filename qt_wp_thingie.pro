######################################################################
# Automatically generated by qmake (2.01a) Wed May 29 17:00:35 2013
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . irc logger settings utils utils/parser
INCLUDEPATH += . utils utils/parser settings irc logger
QT += network
QMAKE_CXXFLAGS += -std=c++11 -g -O0

# Input
HEADERS += wp_main.hpp \
           wp_main_types.hpp \
           irc/wp_irc.hpp \
           irc/wp_irc_basic.hpp \
           irc/wp_irc_types.hpp \
           logger/logger_types.hpp \
           logger/wp_logger.hpp \
           settings/wp_settings.hpp \
           settings/wp_settings_types.hpp \
           utils/wp_hasher.hpp \
           utils/wp_utils.hpp \
           utils/wp_utils_exceptions.hpp \
           utils/wp_utils_types.hpp \
           utils/parser/wp_js_parser.hpp \
           utils/parser/wp_js_parser_types.hpp
FORMS += captcha.ui
SOURCES += application.cpp \
           wp_main.cpp \
           irc/wp_irc.cpp \
           irc/wp_irc_basic.cpp \
           logger/wp_logger.cpp \
           settings/wp_settings.cpp \
           utils/wp_hasher.cpp \
           utils/wp_utils.cpp \
           utils/parser/wp_js_parser.cpp
