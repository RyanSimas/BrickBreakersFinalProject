#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Paddle: public QGraphicsRectItem{
public:
    //Constructors
    Paddle(QGraphicsItem* parent=NULL);

    //Public methods
    double getCenterX();

    //Events
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif
