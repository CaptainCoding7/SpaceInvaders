#!/bin/bash

x86_64-linux-gnu-g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../SpaceInvaders -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -o spaceinvaders.o ../SpaceInvaders/spaceinvaders.cpp

cd ../build-SpaceInvaders-Desktop-Debug

x86_64-linux-gnu-g++  -o SpaceInvaders components.o main.o mainwindow.o spaceinvaders.o qrc_images.o moc_components.o moc_mainwindow.o moc_spaceinvaders.o   /usr/lib/x86_64-linux-gnu/libQt5Widgets.so /usr/lib/x86_64-linux-gnu/libQt5Gui.so /usr/lib/x86_64-linux-gnu/libQt5Core.so /usr/lib/x86_64-linux-gnu/libGL.so -lpthread

./SpaceInvaders

