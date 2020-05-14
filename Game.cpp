#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

Game::Game(QWidget *parent): QGraphicsView(parent){
    //Initialize the scene
    scene = new QGraphicsScene(0,0,400,600); //Change these values to mess with window size also not sure if this has to be dynamic so this might need changing
    setScene(scene);

    //Set mouse tracking instead of using arrow keys
    setMouseTracking(true);
}

void Game::start(){
    //Create a ball / this needs to be an omellete
    Ball* ball = new Ball();
    ball->setPos(200,500);
    scene->addItem(ball);

    //Create the paddle
    Paddle* paddle = new Paddle();
    paddle->setPos(150,575);
    scene->addItem(paddle);
    paddle->grabMouse();

    //Create the blocks
    creatBlockGrid();
}

void Game::createBlockCol(double x){
    for (size_t i = 0, n = 5; i < n; ++i){
        Block* block = new Block();
        block->setPos(x,i*52); // 2 space b/w blocks (50 height of block)
        scene->addItem(block);
    }
}

void Game::creatBlockGrid(){
    for (size_t i = 0, n = 7; i < n; ++i){
        createBlockCol(i*52);
    }
}
