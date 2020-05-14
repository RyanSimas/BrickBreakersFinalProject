#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView{
public:
    //Constructors
    Game(QWidget* parent=NULL);

    //Public methods
    void start();
    void createBlockCol(double x);
    void creatBlockGrid();

    //Public attributes
    QGraphicsScene* scene;

};

#endif
