#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QHBoxLayout>
#include "board.h"
#include <QTcpServer>
#include <QNetworkRequest>
#include <QNetworkReply>

//#include "tcp_client.h"
//#include "tcp_server.h"

#include "server_tcp.h"
#include "sockettest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /*QHBoxLayout *l = new QHBoxLayout();
    Board *a = new Board();
    l->addWidget(a);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(l);*/

    connect(ui->board,&Board::press,this,&MainWindow::sent);
    connect(this,&MainWindow::newgame,ui->board,&Board::newgame);
    connect(this,&MainWindow::set_turn,ui->board,&Board::set_turn);
    who = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this,"server","已啟用服務端端口");
    int server_use_port = ui->lineEdit->text().toInt();
    ui->label_5->setText("端口已開啟，等待連線");

    //server_tcp *s = new server_tcp;
    who = 0;

    server = new server_tcp;
    server->port = server_use_port;
    server->build();
    connect(server,&server_tcp::connectionbuild,this,&MainWindow::ready);
    connect(server,&server_tcp::newgame,this,&MainWindow::new_game_server);
    ui->board->now = 0;
    ui->board->ai = false;
    connect(server,&server_tcp::player1_down,this,&MainWindow::client_down);//
    connect(this,&MainWindow::force_update,ui->board,&Board::force_update);//
    connect(server,&server_tcp::display_message,this,&MainWindow::display_chat);
}

void MainWindow::ready(){
    qDebug() << "connect ready";
    ui->label_5->setText("連線建立，請先手");
    connect(this,&MainWindow::sent_data,server,&server_tcp::send_data);
    connect(this,&MainWindow::chat_message_server,server,&server_tcp::chat_message);
    connect(server,&server_tcp::disconnecttion,this,&MainWindow::disconnection);
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"client","連線至服務端");
    int server_port = ui->lineEdit_3->text().toInt();
    QString server_ip = ui->lineEdit_2->text();
    who = 1;

    sk = new sockettest;
    connect(sk,&sockettest::clientbuild,this,&MainWindow::clientok);
    sk->Connect(server_ip,server_port);
    connect(sk,&sockettest::newgame,this,&MainWindow::new_game_client);
    ui->board->now = 1;
    ui->board->ai = false;
    connect(sk,&sockettest::player0_down,this,&MainWindow::server_down);//
    connect(this,&MainWindow::force_update,ui->board,&Board::force_update);//
    connect(this,&MainWindow::sent_data_2,sk,&sockettest::send_data);//
    connect(sk,&sockettest::display_message,this,&MainWindow::display_chat);
    connect(this,&MainWindow::chat_message_client,sk,&sockettest::chat_message);
}

void MainWindow::clientok(){
    //connect(this,&MainWindow::sent_data_2,sk,&sockettest::send_data);
    ui->label_5->setText("已連線，等待對方出手");
    connect(sk,&sockettest::disconnection,this,&MainWindow::disconnection);
}

void MainWindow::sent(int x, int y, int player){
    if(player == 0 && ui->board->ai==false){
        emit sent_data(x,y,player);
        ui->label_5->setText("等待對方出手");
        turn = 1;
        emit set_turn(turn);
    }else if(ui->board->ai==false){
        emit sent_data_2(x,y,player);
        ui->label_5->setText("等待對方出手");
        turn = 0;
        emit set_turn(turn);
    }else{
        ui->board->pdown(x,y);
    }

    qDebug() << "emit sent_data";
}

void MainWindow::new_game_client(){
    turn = 0;
    emit newgame();
}

void MainWindow::new_game_server(){
    turn = 0;
    emit newgame();
}

void MainWindow::client_down(int x, int y, int p){
    ui->label_5->setText("輪到你出手");
    qDebug() << "client down";
    ui->board->board_status[x][y] = p + 1;
    emit force_update();
    if(ui->board->checkWin(ui->board->board_status,x,y,p+1)){
       QMessageBox::information(this,"End","You lose");
       ui->board->newgame();
       ui->label_5->setText("對方獲勝，換你先手");
    }
}

void MainWindow::server_down(int x, int y, int p){
    ui->label_5->setText("輪到你出手");
    qDebug() << "server down";
    ui->board->board_status[x][y] = p + 1;
    emit force_update();
    if(ui->board->checkWin(ui->board->board_status,x,y,p+1)){
       QMessageBox::information(this,"End","You lose");
       ui->board->newgame();
       ui->label_5->setText("對方獲勝，換你先手");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!(ui->lineEdit_4->text().isEmpty())){
        if(who==0){
            emit chat_message_server(ui->lineEdit_4->text());
        }else if(who==1){
            emit chat_message_client(ui->lineEdit_4->text());
        }else{
            QMessageBox::information(this,"error","no connection");
        }
        ui->lineEdit_4->clear();
    }
}

void MainWindow::display_chat(QString message){
    ui->textEdit->append(message);
}

void MainWindow::disconnection(){
    ui->label_5->setText("連線中斷");
    who = -1;
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"AI對弈已啟動","AI擲黑子，您擲白子");
    ui->board->newgame();
    ui->board->ai = true;
    ui->board->aistart();
    ui->board->now = 1;
}
