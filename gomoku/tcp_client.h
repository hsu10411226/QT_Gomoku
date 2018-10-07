#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QDialog>
#include <QHostAddress>
#include <QTcpSocket>

class Tcp_client : public QObject{

    Q_OBJECT
public:
    void setHostAddressAndPort(QString hostAddress, quint16 port);

    QByteArray IntToArray(qint32 source);
public slots:
    void senddata();
    void start();
    void closeConnection();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QHostAddress hostAddress;
    quint16 hostPort;
    QTcpSocket client;
    QByteArray data = "i am client";
};
#endif // TCP_CLIENT_H
