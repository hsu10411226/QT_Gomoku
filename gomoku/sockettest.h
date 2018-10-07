#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class sockettest : public QObject
{
    Q_OBJECT
public:
    explicit sockettest(QObject *parent = nullptr);

    void Connect(QString ip,int port);
    QTcpSocket *socket;

signals:
    void clientbuild();
    void newgame();
    void player0_down(int x,int y,int player);
    void display_message(QString message);
    void disconnection();

public slots:
    void readdata();
    void discon();
    void send_data(int x,int y,int player);
    void chat_message(QString message);

private:

};

#endif // SOCKETTEST_H
