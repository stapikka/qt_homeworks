#include "udpworker.h"
#include <QDataStream>

UDPworker::UDPworker(QObject *parent)
    : QObject(parent)
{
}

/*!
 * @brief Инициализация UDP серверов
 */
void UDPworker::InitSocket()
{
    // ===== UDP для времени =====
    timeUdpSocket = new QUdpSocket(this);
    timeUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT_TIME);

    connect(timeUdpSocket, &QUdpSocket::readyRead,
            this, &UDPworker::readPendingTimeDatagrams);

    // ===== UDP для текста ===== //
    textUdpSocket = new QUdpSocket(this);
    textUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT_TEXT);

    connect(textUdpSocket, &QUdpSocket::readyRead,
            this, &UDPworker::readPendingTextDatagrams);
}

/*!
 * @brief Обработка датаграммы времени
 */
void UDPworker::ReadTimeDatagram(QNetworkDatagram datagram)
{
    QByteArray data = datagram.data();

    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;
    inStr >> dateTime;

    emit sig_sendTimeToGUI(dateTime);
}

/*!
 * @brief Отправка датаграммы времени
 */
void UDPworker::SendTimeDatagram(QByteArray data)
{
    timeUdpSocket->writeDatagram(
        data,
        QHostAddress::LocalHost,
        BIND_PORT_TIME
        );
}

/*!
 * @brief Отправка текстовой датаграммы
 */
void UDPworker::SendTextDatagram(const QByteArray& data)
{
    textUdpSocket->writeDatagram(
        data,
        QHostAddress::LocalHost,
        BIND_PORT_TEXT
        );
}

/*!
 * @brief Чтение датаграмм времени
 */
void UDPworker::readPendingTimeDatagrams(void)
{
    while (timeUdpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = timeUdpSocket->receiveDatagram();
        ReadTimeDatagram(datagram);
    }
}

/*!
 * @brief Чтение текстовых датаграмм
 */
void UDPworker::readPendingTextDatagrams(void)
{
    while (textUdpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = textUdpSocket->receiveDatagram();

        QByteArray data = datagram.data();

        QString message = QString(
                              "Принято сообщение от %1, размер сообщения(байт) %2"
                              )
                              .arg(datagram.senderAddress().toString())
                              .arg(data.size());

        emit sig_sendTextToGUI(message);
    }
}
