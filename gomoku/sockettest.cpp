#include "sockettest.h"

sockettest::sockettest(QObject *parent) : QObject(parent)
{

}

void sockettest::Connect(QString ip,int port){
    //connect
    socket = new QTcpSocket(this);
    //connect(socket,SIGNAL(connected()),this,SLOT(readdata()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readdata()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(discon()));
    socket->connectToHost(ip,port);
    if(socket->waitForConnected(3000)){
        emit clientbuild();
        qDebug() << "Connected to server!!";
        socket->write("new");
        socket->flush();
    }else{
        qDebug() << "connect fail";
    }
}

void sockettest::readdata(){
    qDebug() << "client ready read";
    QByteArray data = socket->readAll();
    if(QString(data).contains("server")){
        qDebug() << data;
        emit display_message(QString(data));
    }
    else if(data == QByteArray("new")){
        emit newgame();
        qDebug() << "client new game";
    }else{
        QString tostr = QString(data);
        qDebug() << data;
        QStringList list = tostr.split(",");
        qDebug() << "x = " << list[0] << "y = " << list[1] << "player = " << list[2];
        if(list[2] == "0"){
            QString x_position = list[0];
            QString y_position = list[1];
            QString player = list[2];
            emit player0_down(x_position.toInt(),y_position.toInt(),player.toInt());
            qDebug() << "emit player0_down";
        }
    }
}

void sockettest::discon(){
    qDebug() << "client disconnected";
    emit disconnection();
}

void sockettest::send_data(int x,int y,int player){
    qDebug() << "emit send_data_client";
    QString data = QString::number(x) + "," + QString::number(y) + "," + QString::number(player);
    socket->write(data.toLatin1());
    socket->flush();
}

void sockettest::chat_message(QString message){
    socket->write(("<client>->"+message).toLatin1());
    socket->flush();
    emit display_message("<client>->"+message);
}
