QT += network webkit
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    rise.cpp

TARGET = rise
# Please do not modify the following two lines. Required for deployment.
#include(html5applicationviewer/html5applicationviewer.pri)
#qtcAddDeployment()

HEADERS += \
    rise.h
