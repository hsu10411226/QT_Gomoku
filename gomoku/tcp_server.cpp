#include <QApplication>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>

using namespace std;

#include "tcp_server.h"

void Tcp_server::listen(quint16 port){
    server.listen(QHostAddress::Any,port);
    qDebug() << "listen";
    emit acceptConnection();
}

void Tcp_server::acceptConnection(){
    qDebug() << "accept";
    //clientConnection = server.nextPendingConnection();
    while(server.hasPendingConnections()){
        QTcpSocket *socket = server.nextPendingConnection();
        QByteArray *buffer = new QByteArray();
        qint32 *s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);
        qDebug() << buffers;
        qDebug() << sizes;
    }
    server.close();
}

void Tcp_server::displayError(QAbstractSocket::SocketError socketError){
    //QMessageBox::information(this,"error",socketError);
}
