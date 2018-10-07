#ifndef SERVER_TCP_H
#define SERVER_TCP_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class server_tcp : public QObject
{
    Q_OBJECT
public:
    explicit server_tcp(QObject *parent = nullptr);
    QTcpServer *server;
    int port = 23;
    void build();
    QTcpSocket *socket;

signals:
    void connectionbuild();
    void newgame();
    void player1_down(int x,int y,int player);
    void display_message(QString message);
    void disconnecttion();

public slots:
    void acceptConnection();
    void close();
    void send_data(int x,int y,int player);
    void read_data();
    void chat_message(QString message);
private:

};

#endif // SERVER_TCP_H
