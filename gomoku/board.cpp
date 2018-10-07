#include "board.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

// define game state value //
const double FIVE_IN_A_ROW = std::numeric_limits<double>::infinity();
const double STRAIGHT_FOUR_POINTS = 1000;
const double FOURS_POINTS = 500;
const double THREES_POINTS = 100;
const double TWOS_POINTS = 5;
const double ONES_POINTS = 1;
const bool stopSearch = false;
// end define game state value //

Board::Board(QWidget *parent):QWidget(parent){
    this->setMouseTracking(true);
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            board_status[i][j] = 0;
        }
    }
}
Board::~Board(){

}
void Board::paintEvent(QPaintEvent *){
    int x = 20, y= 20;

    paint = new QPainter;
    paint->begin(this);

    QPen pen(Qt::black);
    pen.setWidth(2);
    pen.setJoinStyle(Qt::MiterJoin);
    paint->setPen(pen);
    paint->setBrush(QColor(255, 255, 170));
    paint->drawRect(20,20,700,700);

    paint->setPen(QPen(Qt::black,1,Qt::SolidLine));
    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));

    for(int i=0;i<15;i++){
        paint->drawLine(20,y+50*i,720,y+50*i);
    }

    for(int i=0;i<15;i++){
        paint->drawLine(x+50*i,20,x+50*i,720);
    }


    for(int i=0;i<15;i++){ // load the board status and draw it
        for(int j=0;j<15;j++){
            if(board_status[i][j] != 0){
                if(board_status[i][j] == 1)
                    paint->setBrush(QBrush(Qt::black,Qt::SolidPattern));
                else
                    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));
                paint->drawEllipse(i*50,j*50,45,45);
            }
        }
    }
    paint->end();




    if(!(((m_pos.x()<10) || (m_pos.y()<10)) || ((m_pos.x()>730) || (m_pos.y()>730)))){
        if(board_status[m_pos.x()/50][m_pos.y()/50] == 0){
            if((clicked)&&(now == turn)){
                paint->begin(this);
                if(now == 0){
                    paint->setBrush(QBrush(Qt::black,Qt::SolidPattern));
                    board_status[m_pos.x()/50][m_pos.y()/50] = 1;
                }
                else{
                    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));
                    board_status[m_pos.x()/50][m_pos.y()/50] = 2;
                }
                paint->drawEllipse((m_pos.x()/50)*50,(m_pos.y()/50)*50,45,45);
                clicked = false;
                paint->end();
                emit press(m_pos.x()/50,m_pos.y()/50,now);
                qDebug() << "emit press" << m_pos.x()/50 << m_pos.y()/50 << now;
                if(checkWin(board_status,m_pos.x()/50,m_pos.y()/50,now+1)){
                    qDebug() << "win" << endl;
                    newgame();
                    QMessageBox::information(this,"End","You Win turn opponent first");
                }
                //now = now==0?1:0;
            }
            else if(now == turn || ai == true){
                paint->begin(this);
                auto r2 = QRect{QPoint(0, 0), QSize(45, 45)};
                int g1 = 20 + (m_pos.x()/50)*50;
                int g2 = 20 + (m_pos.y()/50)*50;

                r2.moveCenter(QPoint(g1,g2));
                QColor color = now==0?(Qt::black):(Qt::white);
                color.setAlpha(150);
                paint->setBrush(QBrush(color,Qt::SolidPattern));
                paint->drawEllipse(r2);
                paint->end();
            }
        }
    }
}

void Board::mouseMoveEvent(QMouseEvent *event){
    m_pos = event->pos();
    //qDebug() << m_pos.x()/50 << m_pos.y()/50 << endl;
    update();
    clicked = false;
}

void Board::mousePressEvent(QMouseEvent *event){
    if(!(((m_pos.x()<10) || (m_pos.y()<10)) || ((m_pos.x()>730) || (m_pos.y()>730)))){
        clicked = true;
        update();
        aigo();
    }
}

bool Board::checkWin(int status[][15],int position_x,int position_y,int player)
{
    for (int i = 0, j; i <= 14; i = j + 1)
    {
        for (j = i; j <= 14 && status[j][position_y] == player; j++);
        if (j - i >= 5) return true;
    }
    for (int i = 0, j; i <= 14; i = j + 1)
    {
        for (j = i; j <= 14 && status[position_x][j] == player; j++);
        if (j - i >= 5) return true;
    }
    for (int i = 0, j, k; i <= 14; i = j + 1)
    {
        for (j = i; k = j - position_x + position_y, 0 <= k && k <= 14 && status[j][k] == player; j++);
        if (j - i >= 5) return true;
    }
    for (int i = 0, j, k; i <= 14; i = j + 1)
    {
        for (j = i; k = position_x + position_y - j, 0 <= k && k <= 14 && status[j][k] == player; j++);
        if (j - i >= 5) return true;
    }
    return false;
}

void Board::newgame(){
    qDebug() << "board new game";
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            board_status[i][j] = 0;
        }
    }
    update();
}

void Board::set_turn(int a){
    turn = a;
}

void Board::force_update(){
    update();
    if(turn == 0){
        turn = 1;
    }else{
        turn = 0;
    }
}

void Board::ai_choosemove(int b_status[][15], int player){
    lastbestmove = miniMax(b_status,player);
    qDebug() << "lastbestmove is" << lastbestmove.x_position << lastbestmove.y_position;
}

Move Board::miniMax(int board_status[][15], int player){
    currentdepth = 0;
    Move bestmove;
    double bestmovevalue = -std::numeric_limits<double>::infinity();
    double movevalue;
    QList<Move> pmove = generatemove(board_status);
    //qDebug() << "generatemove pmove length is " << pmove.length();

    for(int depth = 1; depth <= 2; depth++){
        for(int i=0; i<pmove.length(); i++){
            //qDebug() << "use pmove[" << i << "]";
            int theBoard[15][15] = {0};
            std::copy(&board_status[0][0],&board_status[0][0]+225,&theBoard[0][0]);
            //qDebug() << "run usemove";
            usemove(&theBoard[0][0], player, pmove[i]);
            qDebug() << "finish usemove" << pmove[i].x_position << pmove[i].y_position;
            movevalue = min_move(theBoard, player==1?2:1, depth, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
            //qDebug() << "finish min move";
            qDebug() << pmove[i].x_position << pmove[i].y_position << "value = " << movevalue;
            if(movevalue > bestmovevalue){
                this->lastbestmove = pmove[i];
                bestmove = pmove[i];
                bestmovevalue = movevalue;
                //qDebug() << "bestmove is :" << pmove[i].x_position << pmove[i].y_position << movevalue;
            }
        }
        currentdepth = depth;
    }
    qDebug() << "bestmovevalue = " << bestmovevalue;
    return bestmove;
}

QList<Move> Board::generatemove(int board_status[][15]){
    QList<Move> moves;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_status[i][j] == 0) {
                moves.append(Move(i,j,0));
                //qDebug() << "move append" << i << j;
            }
        }
    }
    return moves;
}

void Board::usemove(int *board_status, int player, Move move){
    int x = move.x_position;
    int y = move.y_position;
    board_status[x*15+y] = player;
}

double Board::min_move(int board_status[][15], int player, int depth, double alpha, double beta){
    //qDebug() << "run min_move" << "now depth : " << depth;
    double currentvalue = getstatevalue(board_status, player);
    //qDebug() << "min_move getstatevalue finished" << depth;
    //qDebug() << "min_move currentvalue: " << currentvalue;

    if(currentvalue == FIVE_IN_A_ROW || depth == 0 || stopSearch){
        return currentvalue;
    }else{
        double bestMovevalue = std::numeric_limits<double>::infinity(), movevalue;
        QList<Move> moves = generateusefulmove(board_status);

        int boards[moves.length()][15][15] = {0};
        for(int i = 0; i < moves.length(); i++)
            std::copy(&board_status[0][0],&board_status[0][0]+225,&boards[i][0][0]);
        generateBoards(&boards[0][0][0], player==1?2:1, moves);
        //qDebug() << "finished generateboards";

        for(int i = 0; i < moves.length();i++){
            movevalue = max_move(boards[i], player==1?2:1, depth-1, alpha, beta);
            if(movevalue < bestMovevalue) bestMovevalue = movevalue;
            if(movevalue <= alpha) return movevalue;
            if(movevalue < beta) beta = movevalue;
        }

        return bestMovevalue;
    }
}

double Board::max_move(int board_status[][15], int player, int depth, double alpha, double beta){
    //qDebug() << "run max_move";
    double currentvalue = getstatevalue(board_status, player);
    //qDebug() << "run max getstatevalue finish";
    //qDebug() << "max_move currentvalue:" << currentvalue;

    if(currentvalue == FIVE_IN_A_ROW  || depth == 0 || stopSearch){
        return currentvalue;
    }else{
        double bestMovevalue = -std::numeric_limits<double>::infinity(), movevalue;
        QList<Move> moves = generateusefulmove(board_status);

        int boards[moves.length()][15][15] = {0};
        for(int i = 0; i < moves.length(); i++)
            std::copy(&board_status[0][0],&board_status[0][0]+225,&boards[i][0][0]);
        generateBoards(&boards[0][0][0], player, moves);
        //qDebug() << "max finish generateboards";

        for(int i = 0; i < moves.length();i++){
            movevalue = min_move(boards[i], player==1?2:1, depth-1, alpha, beta);
            if(movevalue > bestMovevalue) bestMovevalue = movevalue;
            if(movevalue >= beta) return movevalue;
            if(movevalue > alpha) alpha = movevalue;
        }

        return bestMovevalue;
    }
}

QList<Move> Board::generateusefulmove(int board_status[][15]){
    QList<Move> moves;
    QList<QString> history;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_status[i][j] == 1 || board_status[i][j] == 2) { //find
                for(int x=1; x <=6; x++){
                    if(i+x < 15){//down
                        if(board_status[i+x][j] == 0){
                            if(!history.contains(QString::number(i+x)+","+QString::number(j))){
                                moves.append(Move(i+x,j,0));
                                history.append(QString::number(i+x)+","+QString::number(j));
                                //qDebug() << "moves append down" << i+x << j;
                            }
                        }
                    }
                    if(i-x >= 0){//up
                        if(board_status[i-x][j] == 0){
                            if(!history.contains(QString::number(i-x)+","+QString::number(j))){
                                moves.append(Move(i-x,j,0));
                                history.append(QString::number(i-x)+","+QString::number(j));
                                //qDebug() << "moves append up" << i-x << j;
                            }
                        }
                    }
                    if(j+x < 15){//right
                        if(board_status[i][j+x] == 0){
                            if(!history.contains(QString::number(i)+","+QString::number(j+x))){
                                moves.append(Move(i,j+x,0));
                                history.append(QString::number(i)+","+QString::number(j+x));
                                //qDebug() << "moves append right" << i << j+x;
                            }
                        }
                    }
                    if(j-x >= 0){//left
                        if(board_status[i][j-x] == 0){
                            if(!history.contains(QString::number(i)+","+QString::number(j-x))){
                                moves.append(Move(i,j-x,0));
                                history.append(QString::number(i)+","+QString::number(j-x));
                                //qDebug() << "moves append left" << i << j-x;
                            }
                        }
                    }
                    if(i-x >= 0){//top-left
                        if(j-x >= 0){
                            if(board_status[i-x][j-x] == 0){
                                if(!history.contains(QString::number(i-x)+","+QString::number(j-x))){
                                    moves.append(Move(i-x,j-x,0));
                                    history.append(QString::number(i-x)+","+QString::number(j-x));
                                    //qDebug() << "moves append top-left" << i-x << j-x;
                                }
                            }
                        }
                    }
                    if(i+x < 15){//bottom-left
                        if(j-x >=0){
                            if(board_status[i+x][j-x] == 0){
                                if(!history.contains(QString::number(i+x)+","+QString::number(j-x))){
                                    moves.append(Move(i+x,j-x,0));
                                    history.append(QString::number(i+x)+","+QString::number(j-x));
                                    //qDebug() << "moves append bottom-left" << i+x << j-x;
                                }
                            }
                        }
                    }
                    if(i-x >= 0){//top-right
                        if(j+x < 15){
                            if(board_status[i-x][j+x] == 0){
                                if(!history.contains(QString::number(i-x)+","+QString::number(j+x))){
                                    moves.append(Move(i-x,j+x,0));
                                    history.append(QString::number(i-x)+","+QString::number(j+x));
                                    //qDebug() << "moves append top-right" << i-x << j+x;
                                }
                            }
                        }
                    }
                    if(i+x < 15 && j+x < 15 && board_status[i+x][j+x] == 0){//bottom-right
                        if(j+x  < 15){
                            if(board_status[i+x][j+x] == 0){
                                if(!history.contains(QString::number(i+x)+","+QString::number(j+x))){
                                    moves.append(Move(i+x,j+x,0));
                                    history.append(QString::number(i+x)+","+QString::number(j+x));
                                    //qDebug() << "moves append bottom-right" << i+x << j+x;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //qDebug() << "finish usefulgenerate";
    return moves;
}

//QList<int [][15]> Board::generateBoards(int *possible,int board_status[][15], int player, QList<Move> move){
void Board::generateBoards(int *possible, int player, QList<Move> move){
    for(int i = 0; i<move.length(); i++){
        usemove(&possible[225*i],player,move[i]);
    }
        //possible.append(usemove(board_status,player,move[i]));
    //return possible
}

double Board::getstatevalue(int board_status[][15], int player){
    double maxvalue[15][15] = {{0}};
    int enemy = player==1?2:1;
    double evaluation = 0.0;
    int boardLength = 15;
    int count;
    int lastEnemyEncounteredCol, lastEnemyEncounteredRow;
    int encounteredEnemy, encounteredEnemyY;

    for (int row = 0; row < boardLength; row++) {
        lastEnemyEncounteredCol = -1;
        lastEnemyEncounteredRow = -1;
        for (int col = 0; col < boardLength; col++) {

            if (board_status[row][col] == enemy) {
                lastEnemyEncounteredCol = col;//keep track of the last encountered enemy
                lastEnemyEncounteredRow = row;
            }


            //If we find the string contains the player
            if (board_status[row][col] == player) {
                encounteredEnemy = -1;
                //====================CHECK TO THE RIGHT====================
                if (col <= boardLength - 5) {//to be sure there can actually be a 5-in-a-row to this direction

                    count = 1; //Sum of how many of our players we encounter in the next 4 spaces
                    for (int x = col + 1; x < col + 5; x++) {
                        if (board_status[row][x] == player) {
                            count++;
                        }
                        else if (board_status[row][x] == enemy) {
                            encounteredEnemy = x;
                            break;
                        }
                    }

                    if (count < 3 || count == 5) {
                        evaluation += getPointsToAdd(count);
                        qDebug() << "eveluation +=" << getPointsToAdd(count) << "x:" << row << "y:" << col;
                    }
                    else if (count == 3) {
                        if (encounteredEnemy == -1) {
                            evaluation += THREES_POINTS;
                            qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (lastEnemyEncounteredCol > -1) {//we encountered an enemy before seeing our player
                            if (col - 1 >= 0 && encounteredEnemy == col + 4) {//we have enough room to make a 4, check to the left one to see if we can make a 5 (-O-X-XXO--)
                                if (board_status[row][col - 1] != enemy) {
                                    evaluation += THREES_POINTS;
                                    qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                                }
                            }
                            else if (col - 2 >= 0 && encounteredEnemy == col + 3) {//we are stuck on 3, check to the left 2 to see if we can make it a 5
                                evaluation += THREES_POINTS;
                                qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }
                    else if (count == 4 && col - 1 < 0 && encounteredEnemy == -1) {//havent encountered an enemy before seeing our player
                        evaluation += FOURS_POINTS;
                        qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                    }
                    else if (encounteredEnemy > -1 && (col + 5 >= boardLength || col - 1 < 0)) {
                        //enemy is blocking us at the edge of the board (OXXXX)
                    }
                    else { //check for the straight four
                        //String rowString = new String(board_status[row], col - 1, 6); //Create string representation to check for straight 4
                        if (isStraightFour(convertstring(board_status,row,0,1), player)) {//If it is a straight 4
                            evaluation += STRAIGHT_FOUR_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (encounteredEnemy == -1) {//If it is possible to have a straight 4, and we have not encountered an enemy while searching
                            evaluation += FOURS_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else { //If it is possible to have a straight 4, but we have encountered an enemy while searching, check if there is room on left
                            if (board_status[row][col - 1] != enemy) {
                                evaluation += FOURS_POINTS;
                                qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }

                }//FINISH CHECKING TO THE RIGHT
                maxvalue[row][col] = evaluation;
                evaluation = 0;


                encounteredEnemy = -1;
                //====================CHECK BELOW====================
                if (row <= boardLength - 5) {//to be sure there can actually be a 5-in-a-row to this direction

                    count = 1; //Sum of how many of our players we encounter in the next 4 spaces
                    for (int x = row + 1; x < row + 5; x++) {
                        if (board_status[x][col] == player) {
                            count++;
                        }
                        else if (board_status[x][col] == enemy) {
                            encounteredEnemy = x;
                            break;
                        }
                    }

                    if (count < 3 || count == 5) {
                        evaluation += getPointsToAdd(count);
                        qDebug() << "eveluation +=" << getPointsToAdd(count) << "x:" << row << "y:" << col;
                    }
                    else if (count == 3) {
                        if (encounteredEnemy == -1) {
                            evaluation += THREES_POINTS;
                            qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (lastEnemyEncounteredRow > -1) {//we encountered an enemy before seeing our player
                            if (row - 1 >= 0 && encounteredEnemy == row + 4) {//we have enough room to make a 4, check above to see if we can make a 5 (-O-X-XXO--)
                                if (board_status[row - 1][col] != enemy) {
                                    evaluation += THREES_POINTS;
                                    qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                                }
                            }
                            else if (row - 2 >= 0 && encounteredEnemy == row + 3) {//we are stuck on 3, check to the left 2 to see if we can make it a 5
                                evaluation += THREES_POINTS;
                                qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }
                    else if (count == 4 && row - 1 < 0 && encounteredEnemy == -1) {//havent encountered an enemy before seeing our player
                        evaluation += FOURS_POINTS;
                        qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                    }
                    else if (encounteredEnemy > -1 && (row + 5 >= boardLength || row - 1 < 0)) {
                        //enemy is blocking us at the edge of the board (OXXXX)
                    }
                    else { //check for the straight four
                        /*char[] newChars = new char[6];

                        for (int b = row - 1, i = 0; b < boardLength && b < row + 5; b++, i++) {
                            newChars[i] = board_status[b][col];
                        }
                        String rowString = new String(newChars);*/
                        QString newChars = "";
                        for(int b = row - 1, i = 0; b < boardLength && b < row + 5; b++, i++){
                            newChars += QString::number(board_status[b][col]);
                        }

                        //if (isStraightFour(convertstring(board_status,col,0,0), player)) {//If it is a straight 4
                        if (isStraightFour(newChars, player)) {//If it is a straight 4
                            evaluation += STRAIGHT_FOUR_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (encounteredEnemy == -1) {//If it is possible to have a straight 4, and we have not encountered an enemy while searching
                            evaluation += FOURS_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else { //If it is possible to have a straight 4, but we have encountered an enemy while searching, check if there is room on left
                            if (board_status[row - 1][col] != enemy) {
                                evaluation += FOURS_POINTS;
                                qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }

                }//FINISH CHECKING BELOW

                if(evaluation > maxvalue[row][col]){
                    maxvalue[row][col] = evaluation;
                }
                evaluation = 0;

                encounteredEnemy = -1;
                //====================CHECK ABOVE====================
                if (row >= 4) {//to be sure there can actually be a 5-in-a-row to this direction
                    count = 1; //Sum of how many of our players we encounter in the next 4 spaces
                    for (int x = row - 1; x > row - 5; x--) {
                        if (board_status[x][col] == player) {
                            count++;
                        }
                        else if (board_status[x][col] == enemy) {
                            encounteredEnemy = x;
                            break;
                        }
                    }

                    if (count < 3 || count == 5) {
                        evaluation += getPointsToAdd(count);
                        qDebug() << "eveluation +=" << getPointsToAdd(count) << "x:" << row << "y:" << col;
                    }
                    else if (count == 3) {
                        if (encounteredEnemy == -1) {
                            evaluation += THREES_POINTS;
                            qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (lastEnemyEncounteredRow > -1) {//we encountered an enemy before seeing our player
                            if (row + 1 < boardLength && encounteredEnemy == row - 4) {//we have enough room to make a 4, check upwards to see if we can make a 5 (-O-X-XXO--)
                                if (board_status[row + 1][col] != enemy) {
                                    evaluation += THREES_POINTS;
                                    qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                                }
                            }
                            else if (row + 2 < boardLength && encounteredEnemy == row - 3) {//we are stuck on 3, check upwards 2 to see if we can make it a 5
                                evaluation += THREES_POINTS;
                                qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }
                    else if (count == 4 && row + 1 >= boardLength && encounteredEnemy == -1) {//havent encountered an enemy before seeing our player
                        evaluation += FOURS_POINTS;
                        qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                    }
                    else if (encounteredEnemy > -1 && (row - 5 < 0 || row + 1 >= boardLength)) {
                        //enemy is blocking us at the edge of the board (OXXXX)
                    }
                    else { //check for the straight four
                        /*char[] newChars = new char[6];

                        for (int b = row + 1, i = 0; b >= 0 && b > row - 5; b--, i++) {
                            newChars[i] = board_status[b][col];
                        }
                        String rowString = new String(newChars);*/

                        QString newChars = "";
                        for(int b = row + 1, i = 0; b >= 0 && b > row - 5; b--, i++){
                            newChars += QString::number(board_status[b][col]);
                        }

                        //if (isStraightFour(convertstring(board_status,col,0,0), player)) {//If it is a straight 4
                        if (isStraightFour(newChars, player)) {//If it is a straight 4
                            evaluation += STRAIGHT_FOUR_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (encounteredEnemy == -1) {//If it is possible to have a straight 4, and we have not encountered an enemy while searching
                            evaluation += FOURS_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else { //If it is possible to have a straight 4, but we have encountered an enemy while searching, check if there is room on left
                            if (board_status[row + 1][col] != enemy) {
                                evaluation += FOURS_POINTS;
                                qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }

                }//FINISH CHECKING ABOVE

                if(evaluation > maxvalue[row][col]){
                    maxvalue[row][col] = evaluation;
                }
                evaluation = 0;

                encounteredEnemy = -1;
                encounteredEnemyY = -1;
                //====================CHECK BOTTOM-RIGHT DIAGONALLY====================
                if (col + 4 < boardLength && row + 4 < boardLength) {//to be sure there can actually be a 5-in-a-row to this direction
                    count = 1; //Sum of how many of our players we encounter in the next 4 spaces
                    for (int x = row + 1, y = col + 1; x < row + 5 && y < col + 5; x++, y++) {
                        if (board_status[x][y] == player) {
                            count++;
                        }
                        else if (board_status[x][y] == enemy) {
                            encounteredEnemy = x;
                            encounteredEnemyY = y;
                            break;
                        }
                    }

                    if (count < 3 || count == 5) {
                        evaluation += getPointsToAdd(count);
                        qDebug() << "eveluation +=" << getPointsToAdd(count) << "x:" << row << "y:" << col;
                    }
                    else if (count == 3) {
                        if (encounteredEnemy == -1) {
                            evaluation += THREES_POINTS;
                            qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (lastEnemyEncounteredRow > -1) {//we encountered an enemy before seeing our player
                            if ((row + 1 < boardLength && col - 1 >= 0) && (encounteredEnemy == row + 4 && encounteredEnemyY == col + 4)) {//we have enough room to make a 4, check upwards to see if we can make a 5 (-O-X-XXO--)
                                if (board_status[row + 1][col - 1] != enemy) {
                                    evaluation += THREES_POINTS;
                                    qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                                }
                            }
                            else if (row - 2 >= 0 && col - 2 >= 0 && (encounteredEnemy == row + 3 && encounteredEnemyY == col + 3)) {//we are stuck on 3, check upwards 2 to see if we can make it a 5
                                evaluation += THREES_POINTS;
                                qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }
                    else if (count == 4 && (col - 1 < 0 && row - 1 < 0) && encounteredEnemy == -1) {//havent encountered an enemy before seeing our player
                        evaluation += FOURS_POINTS;
                        qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                    }
                    else if (encounteredEnemy > -1 && (row + 5 >= boardLength || row - 1 < 0) && (col + 5 >= boardLength || col - 1 < 0)) {
                        //enemy is blocking us at the edge of the board (OXXXX)
                    }
                    else { //check for the straight four
                        /*char[] newChars = new char[6];

                        for (int b = row - 1, c = col - 1, i = 0; b < boardLength && b < row + 5 && b >= 0 && c >= 0; b++, c++, i++) {
                            newChars[i] = board_status[b][c];
                        }
                        String rowString = new String(newChars);*/

                        QString newChars = "";
                        for(int b = row - 1, c = col - 1, i = 0; b < boardLength && b < row + 5 && b >= 0 && c >= 0; b++, c++, i++){
                            newChars += QString::number(board_status[b][c]);
                        }

                        //if (isStraightFour(convertstring(board_status,col,row,2), player)) {//If it is a straight 4
                        if (isStraightFour(newChars, player)) {//If it is a straight 4
                            evaluation += STRAIGHT_FOUR_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (encounteredEnemy == -1) {//If it is possible to have a straight 4, and we have not encountered an enemy while searching
                            evaluation += FOURS_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else { //If it is possible to have a straight 4, but we have encountered an enemy while searching, check if there is room on left
                            if (row-1 >= 0 && col-1 >= 0 && board_status[row - 1][col - 1] != enemy) {
                                evaluation += FOURS_POINTS;
                                qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }

                }//FINISH BOTTOM RIGHT DIAGONAL

                if(evaluation > maxvalue[row][col]){
                    maxvalue[row][col] = evaluation;
                }
                evaluation = 0;

                encounteredEnemy = -1;
                encounteredEnemyY = -1;
                //====================CHECK TOP-RIGHT DIAGONALLY====================
                if (col + 4 < boardLength && row - 4 >= 0) {//to be sure there can actually be a 5-in-a-row to this direction
                    count = 1; //Sum of how many of our players we encounter in the next 4 spaces
                    for (int x = row - 1, y = col + 1; x > row - 5 && y < col + 5; x--, y++) {
                        if (board_status[x][y] == player) {
                            count++;
                        }
                        else if (board_status[x][y] == enemy) {
                            encounteredEnemy = x;
                            encounteredEnemyY = y;
                            break;
                        }
                    }

                    if (count < 3 || count == 5) {
                        evaluation += getPointsToAdd(count);
                        qDebug() << "eveluation +=" << getPointsToAdd(count) << "x:" << row << "y:" << col;
                    }
                    else if (count == 3) {
                        if (encounteredEnemy == -1) {
                            evaluation += THREES_POINTS;
                            qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (lastEnemyEncounteredRow > -1) {//we encountered an enemy before seeing our player
                            if ((row - 1 >= 0 && col - 1 >= 0) && (encounteredEnemy == row - 4 && encounteredEnemyY == col + 4)) {//we have enough room to make a 4, check upwards to see if we can make a 5 (-O-X-XXO--)
                                if (board_status[row - 1][col - 1] != enemy) {
                                    evaluation += THREES_POINTS;
                                    qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                                }
                            }
                            else if (row + 2 < boardLength && col - 2 >= 0 && (encounteredEnemy == row - 3 && encounteredEnemyY == col + 3)) {//we are stuck on 3, check upwards 2 to see if we can make it a 5
                                evaluation += THREES_POINTS;
                                qDebug() << "eveluation +=" << THREES_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }
                    else if (count == 4 && (col - 1 < 0 && row + 1 >= boardLength) && encounteredEnemy == -1) {//havent encountered an enemy before seeing our player
                        evaluation += FOURS_POINTS;
                        qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                    }
                    else if (encounteredEnemy > -1 && (row - 5 < 0 || row + 1 >= boardLength) && (col + 5 >= boardLength || col - 1 < 0)) {
                        //enemy is blocking us at the edge of the board (OXXXX)
                    }
                    else { //check for the straight four
                        /*char[] newChars = new char[6];

                        for (int b = row + 1, c = col - 1, i = 0; b < boardLength && b > row - 5 && c >= 0; b--, c++, i++) {
                            newChars[i] = board_status[b][c];
                        }
                        String rowString = new String(newChars);*/

                        QString newChars = "";
                        for(int b = row + 1, c = col - 1, i = 0; b < boardLength && b > row - 5 && c >= 0; b--, c++, i++){
                            newChars += QString::number(board_status[b][c]);
                        }

                        //if (isStraightFour(convertstring(board_status,col,row,3), player)) {//If it is a straight 4
                        if (isStraightFour(newChars, player)) {//If it is a straight 4
                            evaluation += STRAIGHT_FOUR_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else if (encounteredEnemy == -1) {//If it is possible to have a straight 4, and we have not encountered an enemy while searching
                            evaluation += FOURS_POINTS;
                            qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                        }
                        else { //If it is possible to have a straight 4, but we have encountered an enemy while searching, check if there is room on left

                            if (board_status[row + 1][col - 1] != enemy) {
                                evaluation += FOURS_POINTS;
                                qDebug() << "eveluation +=" << FOURS_POINTS << "x:" << row << "y:" << col;
                            }
                        }
                    }
                }//FINISH TOP-RIGHT DIAGONAL SEARCH

                if(evaluation > maxvalue[row][col]){
                    maxvalue[row][col] = evaluation;
                }
            }
        }//inner (column) loop
    }//outer (row) loop

    for(int i=0; i<15; i++){
        for(int j =0; j<15; j++){
            evaluation += maxvalue[i][j];
        }
    }

    return evaluation;
}

double Board::getPointsToAdd(int val){
    switch (val) {
        case 1:
            return ONES_POINTS;
        case 2:
            return TWOS_POINTS;
        case 3:
            return THREES_POINTS;
        case 4:
            return FOURS_POINTS;
        case 5:
            return FIVE_IN_A_ROW;
        default:
            return 0;
    }
}

bool Board::isStraightFour(QString in, int player){
    QString straightFour = "0" + QString::number(player) + QString::number(player) + QString::number(player) + QString::number(player) + "0";
    return in.contains(straightFour);
}

QString Board::convertstring(int board_status[][15], int col, int row, int which){
    QString result;
    if(which==0){ // ----
        for(int i = 0; i < 15; i++)
            result.append(QString::number(board_status[i][col]));
    }else if(which==1){ // |||
        for(int i = 0; i < 15; i++)
            result.append(QString::number(board_status[col][i]));
    }else if(which==2){
        for(int c=col,r=row; c<15 && r<15; c++,r++)
            result.append(QString::number(board_status[c][r]));
    }else if(which==3){
        for(int c=col,r=row; c < 15 && r>0; c++,r--)
            result.append(QString::number(board_status[c][r]));
    }
    return result;
}

void Board::aistart(){
    count = 0;

    for(int i = 0;i < 15; i++){
        for(int j = 0; j < 11; j++){
            for(int k = 0; k < 5; k++){
                wins[i][j+k][count] = true;
            }
            count++;
        }
    }

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 11; j++){
            for(int k = 0; k < 5; k++){
                wins[j+k][i][count] = true;
            }
            count++;
        }
    }

    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            for(int k = 0; k < 5; k++){
                wins[i+k][j+k][count] = true;
            }
            count++;
        }
    }

    for(int i = 0; i < 11; i++){
        for(int j = 14; j > 3; j--){
            for(int k = 0; k < 5; k++){
                wins[i+k][j-k][count] = true;
            }
            count++;
        }
    }

    for(int i = 0; i < count; i++){
        myWin[i] = 0;
        airingWin[i] = 0;
    }
    board_status[7][7] = 1;
    update();
}

void Board::pdown(int x, int y){
    if(board_status[x][y] == 0){
        board_status[x][y] = 2;

        for(int k = 0; k < count; k++){
            if(wins[x][y][k]){
                myWin[k] = myWin[k] + 1;
                airingWin[k] = 6;
                if(myWin[k] == 5){
                    ai = false;
                    now = 0;
                    QMessageBox::information(this,"Game Over","You Win");
                    newgame();
                }
                else if(checkWin(board_status,x,y,2)){
                    ai = false;
                    now = 0;
                    QMessageBox::information(this,"Game Over","You Win");
                    newgame();
                }
            }
        }
        airingGo();
        qDebug() << "call";
    }

}

void Board::airingGo(){
    int u = 0;
    int v = 0;
    int myScore[15][15] = {0};
    int airingScore[15][15] ={0};
    int max = 0;

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(board_status[i][j] == 0){
                for(int k = 0; k < count; k++){
                    if(wins[i][j][k]){
                        if(myWin[k] == 1){
                            myScore[i][j] += 200;
                        }
                        else if(myWin[k] == 2){
                            myScore[i][j] += 400;
                        }
                        else if(myWin[k] == 3){
                            myScore[i][j] += 2000;
                        }
                        else if(myWin[k] == 4){
                            myScore[i][j] += 10000;

                        }if(airingWin[k] == 1){
                            airingScore[i][j] += 220;
                        }
                        else if(airingWin[k] == 2){
                            airingScore[i][j] += 420;
                        }
                        else if(airingWin[k] == 3){
                            airingScore[i][j] += 2100;
                        }
                        else if(airingWin[k] == 4){
                            airingScore[i][j] += 20000;
                        }

                    }
                }

                if(myScore[i][j] > max){
                    max = myScore[i][j];
                    u = i;
                    v = j;
                }
                else if(myScore[i][j] == max){
                    if(airingScore[i][j] > airingScore[u][v]){
                        u = i;
                        v = j;
                    }
                }

                if(airingScore[i][j] > max){
                    max = airingScore[i][j];
                    u = i;
                    v = j;
                }
                else if(airingScore[i][j] == max){
                    if(myScore[i][j] > myScore[u][v]){
                        u = i;
                        v = j;
                    }
                }
            }
        }
    }
    qDebug() << "down " << u << v << max;
    board_status[u][v] = 1;

    for(int k = 0; k < count; k++){
        if(wins[u][v][k]){
            airingWin[k] = airingWin[k] + 1;
            myWin[k] = 6;
            if(airingWin[k] == 5){
                ai = false;
                now = 3;
                QMessageBox::information(this,"Game Over","You lose");
                newgame();
            }
            else if(checkWin(board_status,u,v,1)){
                ai = false;
                now = 3;
                QMessageBox::information(this,"Game Over","You lose");
                newgame();
            }
        }
    }

    update();
}

void Board::aigo(){
    if(ai == true)
        emit press(m_pos.x()/50,m_pos.y()/50,now);
}
