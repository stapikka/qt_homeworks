#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sec = new Stopwatch(this);

    connect(sec, &Stopwatch::sig_SendSimpleSignal, this, &MainWindow::ReceiveSimpleSignal);

    connect(sec, &Stopwatch::sig_SendSignal, this, &MainWindow::ReceiveSignal);

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_start_clicked()
{
    sec->SendSignal();
}

void MainWindow::ReceiveSimpleSignal()
{
    ui->tb_info->append(QString("Принят простой сигнал"));
    qDebug() << "Принят простой сигнал";
}

void MainWindow::ReceiveSignal(QString str)
{
    ui->tb_info->append(QString("Принят сигнал со строкой: '%1'").arg(str));
    qDebug() << "Принят сигнал со строкой:" << str;
}


void MainWindow::on_pb_lap_clicked()
{
    ui->tb_info->clear();
}


void MainWindow::on_pb_clear_clicked()
{
    sec->SendSignalWithString(ui->lb_time->text());
}

