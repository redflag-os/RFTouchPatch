/*
 * main.cpp: mainwindow head file
 * Copyright (C) 2021, Red Flag Software Co., Ltd
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <qmessagebox.h>
#include "Tool.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_step1();
    void init_step2();

private slots:
    void on_pushButton_test_clicked();

    void on_pushButton_confirm_clicked();

    void on_pushButton_cancle_clicked();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
};
void combox_hardname(QString filename, QStringList &strlist);
void combox_interface(QString filename, QStringList &strlist);


#endif // MAINWINDOW_H
