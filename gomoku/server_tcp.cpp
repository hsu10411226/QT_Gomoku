#include "server_tcp.h"

server_tcp::server_tcp(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);


    connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

void server_tcp::build(){
    if(!server->listen(QHostAddress::Any,port)){
        qDebug() << "Server can't build";
    }else{
        qDebug() << "Server started listen";
    }

    if(server->isListening()){
        qDebug() << "tcp server is listening";
    }else{
        qDebug() << "not listening";
    }
}

void server_tcp::acceptConnection(){
    qDebug() << "client connect in";
    emit connectionbuild();
    socket = server->nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_data()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(close()));
    socket->write("new");
    socket->flush();
    //socket->waitForBytesWritten(3000);
    //socket->close();
}

void server_tcp::close(){
    qDebug() << "server disconnected";
    emit disconnecttion();
}

void server_tcp::send_data(int x, int y, int player){
    qDebug() << "server send_data";
    QString data = QString::number(x) + "," +QString::number(y) + "," + QString::number(player);
    socket->write(data.toLatin1());
    socket->flush();
    //socket->waitForBytesWritten(3000);
}

void server_tcp::read_data(){
    QByteArray message = socket->readAll();
    if(QString(message).contains("client")){
        qDebug() << message;
        emit display_message(QString(message));
    }
    else if(message == QByteArray("new")){
        emit newgame();
        qDebug() << "server new game";
    }else{
        QString tostr = QString(message);
        qDebug() << message;
        QStringList list = tostr.split(",");
        qDebug() << "x = " << list[0] << "y = " << list[1] << "player = " << list[2];
        if(list[2] == "1"){
            QString x_position = list[0];
            QString y_position = list[1];
            QString player = list[2];
            emit player1_down(x_position.toInt(),y_position.toInt(),player.toInt());
            qDebug() << "emit player1_down";
        }
    }
}

void server_tcp::chat_message(QString message){
    socket->write(("<server>->"+message).toLatin1());
    socket->flush();
    emit display_message("<server>->"+message);
}
