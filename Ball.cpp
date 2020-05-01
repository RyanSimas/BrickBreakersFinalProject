#include "Ball.h"
#include <QTimer>
#include <QBrush>
#include "Game.h"
#include "Paddle.h"
#include "Block.h"

extern Game* game;

/*
 * IF WE USE A FILLED BALL FOR BALL INSTEAD OF OMELLETE, READ BELOW
 * IF NOT, IGNORE INFO BELOW
 * So this actually needs to use QPainter to draw an eclipse which is a circle in QT I beleive
 * Essentially it would look something like this:

   void Widget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p(this);
    int w = m_mousPos.x() < width()/2 ? (width()/2 -m_mousPos.x())*2 : (m_mousPos.x()- width()/2)*2;
    int h = m_mousPos.y() < height()/2 ? (height()/2 -m_mousPos.y())*2 : (m_mousPos.y()-height()/2)*2;
    QRect r(0,0,w, h);
    r.moveCenter(QPoint(width()/2,height()/2));

    p.drawEllipse(r);
}

 * Not sure if the above code is right but this idea needs to be implemented on Ball (line 32)
 * QT docs are pretty good for QPaint as well
 */

Ball::Ball(QGraphicsItem *parent): QGraphicsRectItem(parent), QObject(){ //Ignore this warning
    //Draw a rect instead of using designer and image of something
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);

    //Move the ball up right initially
    xVelocity = 0;
    yVelocity = -5;

    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(15);
}

double Ball::getCenterX(){
    return x() + rect().width()/2;
}

void Ball::move(){
    //If ball is out of bounds reverse the velocity
    reverseVelocityIfOutOfBounds();

    //If the ball collides with paddle reverse yVelocite and add xVelocity
    handlePaddleCollision();

    //This handles collisions with blocks (destroying blocks and reversing ball velocity)
    handleBlockCollision();

    moveBy(xVelocity,yVelocity);
}

void Ball::reverseVelocityIfOutOfBounds(){
    //Check if ball is out of bounds and if it is reverse to the proper velocity
    double screenW = game->width();
    double screenH = game->height(); //Ignore the error of unesed variable qt is weird

    //Left edge of screen
    if (mapToScene(rect().topLeft()).x() <= 0){
        xVelocity = -1 * xVelocity;
    }

    //Right edge of screen
    if (mapToScene(rect().topRight()).x() >= screenW){
        xVelocity = -1 * xVelocity;
    }

    //Top edge of screen
    if (mapToScene(rect().topLeft()).y() <= 0){
        yVelocity = -1 * yVelocity;
    }
}

//For handelling paddle collision with paddle
void Ball::handlePaddleCollision(){
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        Paddle* paddle = dynamic_cast<Paddle*>(cItems[i]);
        if (paddle){
            //Reverse the y velocity
            yVelocity = -1 * yVelocity;

            //Add to x velocity depending on where it hits the paddle
            double ballX = getCenterX();
            double paddleX = paddle->getCenterX();
            double dvx = ballX - paddleX;
            xVelocity = (xVelocity + dvx)/15;

            return; //might remove this return not sure if its needed
        }
    }
}

void Ball::handleBlockCollision(){
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        Block* block = dynamic_cast<Block*>(cItems[i]);
        //For colliding with block and for some reason it removes 2 blocks at a time we need to fix this
        if (block){
            double yPad = 15;
            double xPad = 15;
            double ballx = pos().x();
            double bally = pos().y();
            double blockx = block->pos().x();
            double blocky = block->pos().y();

            //If ball collides from bottom
            if (bally > blocky + yPad && yVelocity < 0){
                yVelocity = -1 * yVelocity;
            }

            //If ball collides from top
            if (blocky > bally + yPad && yVelocity > 0 ){
                yVelocity = -1 * yVelocity;
            }

            //If ball collides from right
            if (ballx > blockx + xPad && xVelocity < 0){
                xVelocity = -1 * xVelocity;
            }

            //If ball collides from left
            if (blockx > ballx + xPad && xVelocity > 0){
                xVelocity = -1 * xVelocity;
            }

            //If ball deletes a block
            game->scene->removeItem(block); //This right here might be why 2 blocks are deleted instead of 1 we need to fix this
            delete block;
        }
    }
}
