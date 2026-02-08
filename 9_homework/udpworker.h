#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QDateTime>
#include <qt6/QtNetwork/QUdpSocket>
#include<qt6/QtNetwork/QNetworkDatagram>


#define BIND_PORT 12345

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data );


private slots:
    void readPendingDatagrams(void);

private:
    QUdpSocket* serviceUdpSocket;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendTextToGUI(QString text);

};

#endif // UDPWORKER_H
