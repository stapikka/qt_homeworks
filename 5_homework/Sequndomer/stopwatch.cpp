#include "stopwatch.h"
#include <QDebug>

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}, running(false), lapCount(0)
{
    timer = new QTimer(this);

    timer->setInterval(100);

    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTimer);

    qDebug() << "STOPWATCH CREATED";
}



void Stopwatch::start()
{
    if (!running) {
        // время старта
        startTime = QTime::currentTime();

        // Запускаем таймер
        timer->start();

        running = true;
        emit sig_stateChanged(true);

        qDebug() << "Секундомер запущен";
    }
}

void Stopwatch::stop()
{
    if (running) {  // Если работает
        // Останавливаем таймер
        timer->stop();

        // Добавляем прошедшее время к общему
        int ms = startTime.msecsTo(QTime::currentTime());
        elapsedTime = elapsedTime.addMSecs(ms);

        running = false;
        emit sig_stateChanged(false);

        qDebug() << "Секундомер остановлен";
    }
}

void Stopwatch::reset()
{
    // Останавливаем, если работает
    if (running) {
        timer->stop();
    }

    // Сбрасываем все
    running = false;
    elapsedTime = QTime(0, 0, 0, 0);
    lastLapTime = QTime(0, 0, 0, 0);
    lapCount = 0;

    // Отправляем сигнал о изменении состояния
    emit sig_stateChanged(false);
    // Отправляем сигнал с обнуленным временем
    emit sig_timeUpdated("00:00.000");

    qDebug() << "Секундомер сброшен";
}

void Stopwatch::lap()
{
    if (running) {  // Только если работает
        // Вычисляем время текущего круга
        QTime current = getCurrentTime();

        // Вычисляем время именно этого круга
        QTime lapTime;
        if (lastLapTime.isValid()) {
            // Разница между текущим временем и временем последнего круга
            int ms = lastLapTime.msecsTo(current);
            lapTime = QTime(0, 0, 0, 0).addMSecs(ms);
        } else {
            // Первый круг - просто текущее время
            lapTime = current;
        }

        // Сохраняем время текущего круга для следующего вычисления
        lastLapTime = current;

        // Увеличиваем счетчик кругов
        lapCount++;

        // Форматируем строку с информацией о круге
        QString lapInfo = QString("Круг %1: %2 (Общее: %3)")
                              .arg(lapCount)
                              .arg(lapTime.toString("mm:ss.zzz"))
                              .arg(current.toString("mm:ss.zzz"));

        // Отправляем сигнал с информацией о круге
        emit sig_lapTimeAdded(lapInfo);

        qDebug() << "Зафиксирован круг:" << lapInfo;
    }
}

QString Stopwatch::getTimeString() const
{
    return getCurrentTime().toString("mm:ss.zzz");
}

QString Stopwatch::getLastLapTime() const
{
    return lastLapTime.toString("mm:ss.zzz");
}

bool Stopwatch::isRunning() const
{
    return running;
}

void Stopwatch::updateTimer()
{
    if (running) {
        // Получаем текущее время
        QString timeStr = getTimeString();

        // Отправляем сигнал с обновленным временем
        emit sig_timeUpdated(timeStr);
    }
}

QTime Stopwatch::getCurrentTime() const
{
    if (running) {
        // Текущее время = накопленное время + время с момента последнего старта
        int ms = startTime.msecsTo(QTime::currentTime());
        return elapsedTime.addMSecs(ms);
    } else {
        // Если не работает - возвращаем накопленное время
        return elapsedTime;
    }
}
Stopwatch::~Stopwatch()
{
    qDebug() << "del Stopwatch";
}

