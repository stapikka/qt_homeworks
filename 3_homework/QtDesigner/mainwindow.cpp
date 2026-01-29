#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myDialog = new Dialog();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myDialog;
}

void MainWindow::on_pb_openDW_clicked()
{
    myDialog->show();
}

