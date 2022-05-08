#ifndef MAP_H
#define MAP_H

#include "constants.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QObject>

#include <vector>

struct MaskaPoint{
    unsigned long long x;
    unsigned long long y;
    MaskaPoint(){
        x = 0;
        y = 0;
    }
    MaskaPoint(unsigned long long Y,unsigned long long X){
        y = Y;
        x = X;
    }
    bool operator==(MaskaPoint a){
        return (a.x = x) && (a.y = y);
    }
};

class Map : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Map();
    ~Map();
    unsigned long long currentCar();
    void deleteCar(unsigned short number);
    bool isLockedMap();
    void moveCar(unsigned long long number, MaskaPoint pointNew);
    MaskaPoint nextTurn(unsigned long long number);
    void setCurrentCar(unsigned long long number);
    void setMap(std::vector<std::vector<mapType> > NewMap);
    void updateMap();

signals:

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setLockMap(bool a);
    bool setDestination(unsigned long long number, MaskaPoint destination, bool newDest = 0);
    void nextTurn();

private slots:
    QGraphicsRectItem* createNewCell(unsigned long long y,unsigned long long x);

private:
    std::vector<std::vector<mapType> > *map;
    std::vector<QGraphicsRectItem*> *cells;
    std::vector<QGraphicsTextItem*> *cars;
    std::vector<MaskaPoint> *destinations;
    std::vector<QGraphicsTextItem*> *destinationsText;
    unsigned short curCar;
    bool lockMap;
};

#endif // MAP_H
