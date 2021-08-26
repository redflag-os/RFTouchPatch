/*
 * main.cpp: mainwindow file
 * Copyright (C) 2021, Red Flag Software Co., Ltd
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(600,450); // 禁止改变窗口大小。
    ui->setupUi(this);
    init_step1();
    init_step2();
    setWindowIcon(QIcon("RFTouchPatch.ico"));
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("\n===========================注意=============================\n");
    ui->textEdit->insertPlainText("如果[ 硬件名称 ] 中包含特殊字符 系统无法成功校准 需要手动输入设备名 。\n如设备名[Weida Hi-Tech CoolTouch® System] 中包含® 需要手动输入设备名 [ Weida Hi-Tech ] 即可\n");
}
static int buttontime = 0;
void MainWindow::init_step1()
{
    QProcess *proc = new QProcess;
    proc->start("xinput");
    proc->waitForFinished();
    QString strResult = proc->readAllStandardOutput();
    delete  proc;

    char *tmp_path = getenv("HOME");
    QString hardname_path = "/hardname.txt";
    hardname_path = tmp_path + hardname_path;
    ofstream  ofhard;
    ofhard.open(hardname_path.toLatin1().data());

    int pos = strResult.toStdString().find("\u21b3");
    string tmpstrResult = strResult.toStdString();
    while (pos != -1)
     {
      tmpstrResult = tmpstrResult.replace(pos, 4 , "#");
      pos = tmpstrResult.find("\u21b3");
     }
    pos = tmpstrResult.find("\u239c");
    while (pos != -1)
     {
      tmpstrResult = tmpstrResult.replace(pos, 4 , "#");
      pos = tmpstrResult.find("\u239c");
     }

    ofhard << tmpstrResult << endl;
    ofhard.close();

    QStringList strList;
    combox_hardname(hardname_path, strList);
    ui->comboBox_hardname->addItems(strList);

    QString command2 = "rm " + hardname_path;
    QProcess ::execute(command2);
}


void MainWindow::init_step2()
{
    char *tmp_path = getenv("HOME");
    QString interface_path = "/interface.txt";
    interface_path = tmp_path + interface_path;

    QProcess *proc = new QProcess;
    proc->start("xrandr");
    proc->waitForFinished();
    QString strResult = proc->readAllStandardOutput();
    delete  proc;

    ofstream  ofhard;
    ofhard.open(interface_path.toLatin1().data());
    ofhard << strResult.toStdString() << endl;
    ofhard.close();


    QStringList strList;
    combox_interface(interface_path, strList);
    ui->comboBox_interface->addItems(strList);

    QString command = "rm " + interface_path;
    QProcess ::execute(command);

}

void combox_interface(QString filename, QStringList &strlist)
{
    ifstream  ofhard;
    ofhard.open(filename.toLatin1().data());
    string interfacename = "";
    while(getline(ofhard, interfacename))
    {
        int pos = interfacename.find("connected");
        if(interfacename.find("dis") != interfacename.npos) continue;;
        if(pos != (int)interfacename.npos)
        {
            interfacename = interfacename.substr(0,pos);
            strlist<<interfacename.c_str();
            interfacename = "";
        }
    }
}

void combox_hardname(QString filename, QStringList &strlist)
{
    ifstream  ofhard;
    ofhard.open(filename.toLatin1().data());
    string hardname = "";
    while(getline(ofhard, hardname))
    {
        int pos = hardname.find("#  #");
        if(pos >= 0)
        {
            hardname = hardname.substr(pos + 4);
            pos = hardname.find("id=");
            hardname = hardname.substr(0,pos);
            hardname = hardname.substr(0, hardname.length() - 1);
            hardname.erase(hardname.find_last_not_of(" ") + 1);
            hardname = hardname.substr(0,pos);
            strlist<<hardname.c_str();
            hardname = "";
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_test_clicked() //校准测试
{
    QString hardnaem = ui->comboBox_hardname->currentText();
    QString interfacenaem = ui->comboBox_interface->currentText();
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("\n========================================================\n开始校准\n");

    QString harddivice = "devid=`xinput |grep \"" + hardnaem + "\" |awk -Fid= '{print $2}'|cut -c 1-2|head -1`";
    QString harddivice1 = "devid=`xinput |grep \"" + hardnaem + "\" |awk -Fid= '{print $2}'|cut -c 1-2|tail -1`";
    QString order = "/usr/bin/xinput map-to-output  \"$devid\" " + interfacenaem ;
    QString deleteenter = "devid=`echo $devid |tr -d '\\n\\r'`";
    QString path = "/jiaozhuntest_tmp.sh";
    char *tmp_path = getenv("HOME");
    path = tmp_path + path;

    ofstream  outfile;
    outfile.open(path.toLatin1().data(), ios::app);
    outfile << "#!/bin/sh" << endl;
    outfile << harddivice.toLatin1().data() << endl;
    outfile << deleteenter.toLatin1().data() << endl;
    outfile << order.toLatin1().data() << endl;
    outfile << harddivice1.toLatin1().data() << endl;
    outfile << deleteenter.toLatin1().data() << endl;
    outfile << order.toLatin1().data() << endl;
    outfile.close();
    QString chmodpath = "chmod a+x " + path;
    QProcess ::execute(chmodpath);
    QString command1 = "sh " + path;
    QProcess ::execute(command1);
    QString command2 = "rm " + path;
    QProcess ::execute(command2);

    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText( "校准完成 ");
    buttontime++;
}


void MainWindow::on_pushButton_confirm_clicked() //校准确认
{
    if (buttontime <= 0)
    {
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->textEdit->insertPlainText("\n========================================================\n请先进行[ 校准测试 ]\n");
        return;
    }
    QString hardnaem = ui->comboBox_hardname->currentText();
    QString interfacenaem = ui->comboBox_interface->currentText();
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("\n========================================================\n开始写入\n");


    QString harddivice = "devid=`xinput |grep \""   +hardnaem +  "\" |awk -Fid= '{print $2}'|cut -c 1-2|head -1`";
    QString harddivice2 = "devid=`xinput |grep \""   +hardnaem +  "\" |awk -Fid= '{print $2}'|cut -c 1-2|tail -1`";

    QString deleteenter = "devid=`echo $devid |tr -d '\\n\\r'`";

    QString order = "/usr/bin/xinput map-to-output  \"$devid\" " + interfacenaem ;

    QString path = "/etc/xdg/autostart/jiaozhun.sh";
    ofstream  outfile;
    outfile.open(path.toLatin1().data(), ios::app);
    if(!(findstr(path.toStdString(), "#!/bin/sh")))
    {
        outfile << "#!/bin/sh" << endl;
        outfile << "sleep 2" << endl;
    }
    int is_exist = findstr(path.toStdString(), interfacenaem.toStdString());
    if(!is_exist)
    {

        outfile << harddivice.toLatin1().data() << endl;
        outfile << deleteenter.toLatin1().data() << endl;
        outfile << order.toLatin1().data() << endl;
        outfile << harddivice2.toLatin1().data() << endl;
        outfile << deleteenter.toLatin1().data() << endl;
        outfile << order.toLatin1().data() << endl;
        outfile.close();

        ui->textEdit->moveCursor(QTextCursor::End);
        ui->textEdit->insertPlainText( "完成写入 ");
     }
    else
    {
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->textEdit->insertPlainText( "\n当前接口已绑定 请进行清空后 重新绑定\n ");
    }
    if(!(is_FileEmpty("/etc/xdg/autostart/jiaozhun.desktop")))
    {
        QString desktop_Entry = "[Desktop Entry]";
        QString type = "Type=Application";
        QString name_Files = "Name=Files";
        path = "Exec=" + path;

        ofstream  outfile1;
        QString tmpfile = "/etc/xdg/autostart/jiaozhun.desktop";
        outfile1.open(tmpfile.toLatin1().data());
        outfile1 << desktop_Entry.toLatin1().data() << endl;
        outfile1 << type.toLatin1().data() << endl;
        outfile1 << name_Files.toLatin1().data() << endl;
        outfile1 << path.toLatin1().data() << endl;
        ui->textEdit->moveCursor(QTextCursor::End);
        outfile1.close();
    }
}




void MainWindow::on_pushButton_cancle_clicked() //清空配置
{
    QMessageBox mb( "注意",
            "注意.\n"
            "确认要清空校准配置?",
            QMessageBox::Information,
            QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::No,
            QMessageBox::Cancel | QMessageBox::Escape );
    mb.setButtonText( QMessageBox::Yes, "是" );
    mb.setButtonText( QMessageBox::No, "否" );
    mb.setButtonText( QMessageBox::Cancel, "取消" );
    switch( mb.exec() ) {
        case QMessageBox::Yes:
            {
                FILE *file;
                file = fopen("/etc/xdg/autostart/jiaozhun.sh","w");
                fclose( file );
                file = fopen("/etc/xdg/autostart/jiaozhun.desktop","w");
                fclose( file );
                ui->textEdit->moveCursor(QTextCursor::End);
                ui->textEdit->insertPlainText("\n========================================================\n清空完成\n");
            }
        case QMessageBox::No:
            break;
        case QMessageBox::Cancel:
            break;
    }
}


void MainWindow::on_textEdit_textChanged()
{
    ui->textEdit->moveCursor(QTextCursor::End);
}

