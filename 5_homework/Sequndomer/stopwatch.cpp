#include "stopwatch.h"
#include <QDebug>

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{}

void Stopwatch::SendSignal()
{
    emit sig_SendSimpleSignal( );
}

void Stopwatch::SendSignalWithString(const QString &str)
{
    emit sig_SendSignal(str);
    qDebug() << "Отправлен сигнал со строкой:" << str;
}

Stopwatch::~Stopwatch()
{
    qDebug() << "del Stopwatch";
}
