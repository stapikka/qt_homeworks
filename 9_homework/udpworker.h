#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>

#define BIND_PORT_TIME 12345
#define BIND_PORT_TEXT 12346

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);

    void InitSocket(void);
    void SendTimeDatagram(QByteArray data);

    void SendTextDatagram(const QByteArray& data);

private slots:
    void readPendingTimeDatagrams(void);
    void readPendingTextDatagrams(void);

private:
    void ReadTimeDatagram(QNetworkDatagram datagram);

    QUdpSocket* timeUdpSocket;
    QUdpSocket* textUdpSocket;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendTextToGUI(QString text);
};

#endif // UDPWORKER_H
