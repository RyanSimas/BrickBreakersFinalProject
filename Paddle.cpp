#include "Paddle.h"
#include <QBrush>

Paddle::Paddle(QGraphicsItem *parent){ //ignore it saying its unused
    //Draw rect for paddle
    setRect(0,0,100,15);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}

double Paddle::getCenterX(){
    return x()+rect().width()/2;
}

void Paddle::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    //Follow mouse's x position / used mouse for moving paddle instead of the arrow keys might change this
    double mouseX = mapToScene(event->pos()).x();
    setPos(mouseX,y());
}
