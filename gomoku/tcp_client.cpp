#include <QApplication>
#include <QMessageBox>
#include <QDebug>

using namespace  std;

#include "tcp_client.h"

void Tcp_client::setHostAddressAndPort(QString address, quint16 port){
    hostAddress.setAddress(address);
    this->hostPort = port;
    emit start();
    connect(&client, SIGNAL(connected()), this, SLOT(senddata()));
}

void Tcp_client::start(){
    client.connectToHost(hostAddress, hostPort);
    qDebug() << "connection start" << hostAddress << hostPort;
    if(client.waitForConnected(5000)){
        qDebug() << "connect success";
        //QMessageBox::information(this,"connect","success");
        //emit senddata(data);
    }else{
        qDebug() << "connect error";
    }

}

void Tcp_client::senddata(){
    qDebug() << "connect success";
    QByteArray send_data = "i am client";
    client.write(IntToArray(send_data.size()));
    client.write("i am client");
    if(client.waitForBytesWritten()){
        qDebug() << "sned data success";
        emit closeConnection();
    }
}

void Tcp_client::closeConnection(){
    client.close();
    qDebug() << "connection close";
}

void Tcp_client::displayError(QAbstractSocket::SocketError socketError){
    //QMessageBox::information(this,"error",socketError);
}

QByteArray Tcp_client::IntToArray(qint32 source){
    QByteArray temp;
    QDataStream data(&temp,QIODevice::ReadWrite);
    data << source;
    return temp;
}
