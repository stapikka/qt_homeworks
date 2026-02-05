#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sec = new Stopwatch(this);


    // Когда секундомер обновляет время -> обновляем label
    connect(sec, &Stopwatch::sig_timeUpdated, this, &MainWindow::onTimeUpdated);

    // Когда добавляется круг -> добавляем в текстовый браузер
    connect(sec, &Stopwatch::sig_lapTimeAdded,this, &MainWindow::onLapTimeAdded);

    // Когда меняется состояние -> обновляем кнопки
    connect(sec, &Stopwatch::sig_stateChanged,this, &MainWindow::onStateChanged);

    // Начальное состояние
    ui->lb_time->setText("00:00.000");
    ui->pb_lap->setEnabled(false);
    ui->pb_start->setText("Старт");

    qDebug() << "MainWindow CREATED";

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_start_clicked()
{
    if (sec->isRunning()) {

        sec->stop();
    } else {
        sec->start();
    }
}

void MainWindow::on_pb_lap_clicked()
{
    sec->reset();
    ui->tb_info->clear();
}


void MainWindow::on_pb_clear_clicked()
{
    sec->lap();
}

void MainWindow::onTimeUpdated(const QString &time)
{
    ui->lb_time->setText(time);
}

void MainWindow::onLapTimeAdded(const QString &lapTime)
{
    ui->tb_info->append(lapTime);
}

void MainWindow::onStateChanged(bool running)
{
    if(running) {
        ui->pb_start->setText("Стоп");
        ui->pb_lap->setEnabled(true);
    } else {
        ui->pb_start->setText("Старт");
        ui->pb_lap->setEnabled(false);
    }
}

