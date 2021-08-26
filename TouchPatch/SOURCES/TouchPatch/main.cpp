/*
 * main.cpp: main file
 * Copyright (C) 2021, Red Flag Software Co., Ltd
 *
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
