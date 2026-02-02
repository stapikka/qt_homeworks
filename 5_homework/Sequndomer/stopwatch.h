#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);

    void SendSignal();
    void SendSignalWithString(const QString &str);

    ~Stopwatch();

signals:
    void sig_SendSimpleSignal();
    void sig_SendSignal(QString str);

};

#endif // STOPWATCH_H
