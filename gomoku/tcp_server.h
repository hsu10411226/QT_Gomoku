#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QTcpServer>

class QTcpSocket;

class Tcp_server : public QObject{

    Q_OBJECT
public:
    void listen(quint16 port);
    void dataReceived(QByteArray);
public slots:
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpServer server;
    QTcpSocket *clientConnection;
    QHash<QTcpSocket*, QByteArray*> buffers;
    QHash<QTcpSocket*, qint32*> sizes;
};
#endif // TCP_SERVER_H
