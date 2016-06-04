#!/bin/sh
# Bash for creating Qt project on Xcode.
# By Laohyx.
#

if [[ -n $1 ]]; then
    mkdir -p $1;
    cd $1;
fi
echo '// Xcode for Qt project.
// Generated by create_qt_xcode_project.sh, Laohyx.

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QLabel *label = new QLabel("Hello Qt!");
    label->show();
    return app.exec();
}
' >> main.cpp
/Users/meteor/Qt5.2.1/5.2.1/clang_64/bin/qmake -project
/Users/meteor/Qt5.2.1/5.2.1/clang_64/bin/qmake -spec macx-xcode
open `find . -name '*.xcodeproj'|head -n 1`