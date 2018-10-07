#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server_tcp.h"
#include "sockettest.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sent_data(int x,int y,int player);
    void sent_data_2(int x,int y,int player);
    void newgame();
    void set_turn(int turn);
    void force_update();
    void chat_message_server(QString message);
    void chat_message_client(QString message);

public slots:
    void on_pushButton_clicked();
    void sent(int x,int y,int player);
    void ready();
    void clientok();
    void new_game_client();
    void new_game_server();
    void client_down(int x,int y,int p);
    void server_down(int x,int y,int p);
    void display_chat(QString message);
    void disconnection();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    server_tcp *server;
    sockettest *sk;
    int turn = 0;
    int who;
};

#endif // MAINWINDOW_H
