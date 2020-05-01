#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>

class Ball: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    //Constructors
    Ball(QGraphicsItem* parent=NULL);

    //Public methods
    double getCenterX();

public slots:
    //Public slots
    void move();

private:
    //Private attributes
    double xVelocity;
    double yVelocity;

    //Private methods
    void reverseVelocityIfOutOfBounds();
    void handlePaddleCollision();
    void handleBlockCollision();
};

#endif
