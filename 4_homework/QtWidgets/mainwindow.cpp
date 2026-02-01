#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pb_progress->setMaximum(100);
    ui->pb_progress->setMinimum(0);
    ui->pb_progress->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_updateBar_clicked()
{
    int progress = ui->pb_progress->value();

    if(progress >= 100){
        ui->pb_progress->setValue(0);
    }

    progress += 10;
    ui->pb_progress->setValue(progress);
}

