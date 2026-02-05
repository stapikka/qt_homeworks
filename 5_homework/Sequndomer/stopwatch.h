#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTime>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);


    ~Stopwatch();

    void start();
    void stop();
    void reset();
    void lap();

    bool isRunning() const;
    QString getTimeString() const;
    QString getLastLapTime() const;

    QTime getCurrentTime() const;
signals:

    void sig_timeUpdated(const QString& time);
    void sig_lapTimeAdded(const QString& lapTime);
    void sig_stateChanged(bool running);

private slots:
    void updateTimer();

private:
    QTimer *timer;
    QTime startTime;
    QTime elapsedTime;
    QTime lastLapTime;
    bool running;
    int lapCount;

};

#endif // STOPWATCH_H
