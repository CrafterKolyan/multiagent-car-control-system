#include "map.h"

#include <QDebug>
#include <QGraphicsTextItem>
#include <QQueue>

#include <math.h>

Map::Map()
{
    map = new std::vector<std::vector<mapType> > (mapSizeY,std::vector<mapType> (mapSizeX,0));
    cells = new std::vector<QGraphicsRectItem*>;
    cars = new std::vector<QGraphicsTextItem*>;
    destinations = new std::vector<MaskaPoint>;
    destinationsText = new std::vector<QGraphicsTextItem*>;
    curCar = 0;
    for(unsigned long long y=0;y<mapSizeY;y++){
        for(unsigned long long x=0;x<mapSizeX;x++){
            cells->push_back(createNewCell(y,x));
            this->addItem(cells->at(y*mapSizeX+x));
        }
    }
    lockMap = 1;
}

Map::~Map(){
    curCar = 0;
    delete map;
    for(unsigned long long i=0;i<cells->size();i++)
        delete cells->at(i);
    delete cells;
    for(unsigned short i=0;i<cars->size();i++)
        delete cars->at(i);
    delete cars;
    delete destinations;
    for(unsigned short i=0;i<cars->size();i++)
        delete destinationsText->at(i);
    delete destinationsText;
}

unsigned long long Map::currentCar(){
    return curCar;
}

void Map::setMap(std::vector<std::vector<mapType> > NewMap){
    *map = NewMap;
    updateMap();
}

void Map::setCurrentCar(unsigned long long number){
    if(curCar <= cars->size() && curCar){
        QGraphicsTextItem *car = cars->at(curCar-1);
//        if(car != 0)
//            cells->at(car->y()/cellSizeY*mapSizeX+car->x()/cellSizeX)->setBrush(QBrush(MaskaRoadColor));
    }

    curCar = number;
    if(curCar <= cars->size() && curCar){
        QGraphicsTextItem *car = cars->at(curCar-1);
        if(car != 0 && car->isVisible()){
//            cells->at(car->y()/cellSizeY*mapSizeX+car->x()/cellSizeX)->setBrush(QBrush(MaskaSelectedCarColor));
            if(curCar <= CarColorSIZE)
                cells->at(car->y()/cellSizeY*mapSizeX+car->x()/cellSizeX)->setBrush(QBrush(CarColor[curCar-1]));
        }
    }
}

QGraphicsRectItem* Map::createNewCell(unsigned long long y, unsigned long long x){
    QGraphicsRectItem *a = new QGraphicsRectItem(x*cellSizeX,y*cellSizeY,cellSizeX,cellSizeY);
    a->setBrush(QBrush(MaskaSpaceColor));
    return a;
}

void Map::setLockMap(bool a){
    lockMap = a;
}

bool Map::isLockedMap(){
    return lockMap;
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *event){
    long long y = event->scenePos().y(),
              x = event->scenePos().x();
    y = floor(y/cellSizeY);
    x = floor(x/cellSizeX);
    qDebug() << "Clicked on" << y << x;

    if(y <= 0 || x <= 0 || y >= mapSizeY-1 || x >= mapSizeX-1)
        return;
    if(curCar == 0){ // if no car selected
        if(lockMap) // if map change is locked
            return;
        if(map->at(y).at(x) == 0){
            map->at(y).at(x) = 1;
            cells->at(y*mapSizeX+x)->setBrush(QBrush(MaskaRoadColor));
        }else if(map->at(y).at(x) == 1){
            map->at(y).at(x) = 0;
            cells->at(y*mapSizeX+x)->setBrush(QBrush(MaskaSpaceColor));
        }
    }else if(map->at(y).at(x) == 1){ // if map[y][x] is road
        if(curCar > cars->size()){
            cars->resize(curCar);
            destinations->resize(curCar);
            destinationsText->resize(curCar);
        }
        if(cars->at(curCar-1) == 0){
            QGraphicsTextItem *addTextItem = new QGraphicsTextItem(QString::number(curCar));
            cars->at(curCar-1) = addTextItem;
            addTextItem->setFont(QFont(addTextItem->font().family(),16));
            addTextItem->setVisible(0);
            this->addItem(addTextItem);

            destinations->at(curCar-1) = MaskaPoint(0,0);

            QGraphicsTextItem *addDestinationTextItem = new QGraphicsTextItem(QString::number(curCar));
            destinationsText->at(curCar-1) = addDestinationTextItem;
            addDestinationTextItem->setFont(QFont(addDestinationTextItem->font().family(),10));
            addDestinationTextItem->setVisible(0);
            this->addItem(addDestinationTextItem);
        }
        unsigned short yPrev = floor(cars->at(curCar-1)->pos().y()/cellSizeY),
                       xPrev = floor(cars->at(curCar-1)->pos().x()/cellSizeX);
        if(yPrev == 0 && xPrev == 0){ // if Car was not set
//            map->at(y).at(x) = curCar+1;
//            cells->at(y*mapSizeX+x)->setBrush(QBrush(MaskaSelectedCarColor));
            for(unsigned long long i=0;i<cars->size();i++){
                if(cars->at(i) == 0)
                    continue;
                else if(cars->at(i)->y() == y*cellSizeY && cars->at(i)->x() == x*cellSizeX)
                    return;
            }
            if(curCar <= CarColorSIZE)
                cells->at(y*mapSizeX+x)->setBrush(QBrush(CarColor[curCar-1]));
            cars->at(curCar-1)->setPos(x*cellSizeX,y*cellSizeY);
            cars->at(curCar-1)->setVisible(1);
        }else{ // if Car was set
            if(destinations->at(curCar-1).x != 0){
                MaskaPoint prev = destinations->at(curCar-1);
                cells->at(prev.y*mapSizeX+prev.x)->setBrush(QBrush(MaskaRoadColor));
                for(unsigned long long i=0;i<cars->size() && i < CarColorSIZE;i++){
                    if(cars->at(i) == 0)
                        continue;
                    else if(cars->at(i)->y() == prev.y*cellSizeY && cars->at(i)->x() == prev.x*cellSizeX)
                        cells->at(prev.y*mapSizeX+prev.x)->setBrush(QBrush(CarColor[i]));
                }
//                map->at(prev.y).at(prev.x) = 1;
            }
            destinations->at(curCar-1).x = x;
            destinations->at(curCar-1).y = y;
            destinationsText->at(curCar-1)->setPos(x*cellSizeX,y*cellSizeY);
            destinationsText->at(curCar-1)->setVisible(1);
        }
    }
}

void Map::deleteCar(unsigned short number){
    if(curCar == number)
        curCar = 0;
    if(number > cars->size())
        return;
    if(cars->at(number-1) == 0)
        return;
    QGraphicsTextItem *car = cars->at(number-1);
//    map->at(car->y() / cellSizeY).at(car->x() / cellSizeX) = 1;
    destinationsText->at(number-1)->setVisible(0);
    delete car;
    cars->erase(cars->begin()+number-1);
}

void Map::updateMap(){
    unsigned long long i = 0;
    short value;
    for(unsigned short y=0;y<mapSizeY;y++){
        for(unsigned short x=0;x<mapSizeX;x++,i++){
            value = map->at(y).at(x);
            if(value == 0)
                cells->at(i)->setBrush(QBrush(MaskaSpaceColor));
            else if(value == 1)
                cells->at(i)->setBrush(QBrush(MaskaRoadColor));
            else{
                qDebug() << "Updating" << y << x << "with value" << map->at(y).at(x);
                QGraphicsTextItem *car = cars->at(value - 2);
                car->setPos(x*cellSizeX, y*cellSizeY);
                car->setVisible(1);
            }
        }
    }
    for(unsigned short i=0;i<mapSizeX;i++){
        cells->at(i)->setVisible(0);
        cells->at(mapSizeX*mapSizeY-i-1)->setVisible(0);
    }
    for(unsigned short i=0;i<mapSizeY;i++){
        cells->at(mapSizeX*i)->setVisible(0);
        cells->at(mapSizeX*i+mapSizeX-1)->setVisible(0);
    }
    for(unsigned short i=0;i<cars->size();i++){
        if(cars->at(i) == 0)
            continue;
        unsigned long long x = cars->at(i)->x()/cellSizeX,
                           y = cars->at(i)->y()/cellSizeY;
        if(i < CarColorSIZE)
            cells->at(y*mapSizeX+x)->setBrush(QBrush(CarColor[i]));
        if(cars->at(i)->x() == destinationsText->at(i)->x() && cars->at(i)->y() == destinationsText->at(i)->y()){
            destinations->at(i).x = 0;
            destinations->at(i).y = 0;
            destinationsText->at(i)->setVisible(0);
        }
    }
}

void Map::moveCar(unsigned long long number, MaskaPoint pointNew){
//    map->at(pointNew.y).at(pointNew.x) = number+1;
//    map->at(pointPrev.y).at(pointPrev.x) = 1;
    MaskaPoint pointPrev(cars->at(number-1)->y()/cellSizeY,cars->at(number-1)->x()/cellSizeX);
    cars->at(number-1)->setPos(pointNew.x*cellSizeX,pointNew.y*cellSizeY);
//    if(pointNew == destinations->at(number-1)){
//        cells->at(pointNew.y*mapSizeX+pointNew.x)->setBrush(QBrush(MaskaRoadColor));
//    }
//    if(number == curCar){
//        cells->at(pointPrev.y*mapSizeX+pointPrev.x)->setBrush(QBrush(MaskaRoadColor));
//        cells->at(pointNew.y*mapSizeX+pointNew.x)->setBrush(QBrush(MaskaSelectedCarColor));
//    }
    cells->at(pointPrev.y*mapSizeX+pointPrev.x)->setBrush(QBrush(MaskaRoadColor));
    if(number <= CarColorSIZE)
        cells->at(pointNew.y*mapSizeX+pointNew.x)->setBrush(QBrush(CarColor[number-1]));
}

static mapType MaskaFindCell(std::vector<std::vector<mapType> > &mapTemp, MaskaPoint point){
    return mapTemp.at(point.y).at(point.x);
}

void Map::nextTurn(){
    std::vector<std::vector<mapType> > *mapTemp = new std::vector<std::vector<mapType> >;
    std::vector<std::vector<MaskaPoint> > steps(cars->size(),std::vector<MaskaPoint> (depth,MaskaPoint(0,0)));
    std::vector<MaskaPoint> carPointBegin(cars->size());
    std::vector<unsigned int> carPointEnd(cars->size(),depth-1);
    std::vector<MaskaPoint> *destinationsTemp = new std::vector<MaskaPoint>;
    *destinationsTemp = *destinations;
    for(unsigned short step = 0;step < depth;step++){
        for(unsigned short iCurCar = 1;iCurCar <= cars->size();iCurCar++){
            if(cars->at(iCurCar-1) == 0)
                continue;
            unsigned int yCar = cars->at(iCurCar-1)->y()/cellSizeY, xCar = cars->at(iCurCar-1)->x()/cellSizeX;
            MaskaPoint carPoint(yCar,xCar);

            if(step == 0){
                carPointBegin[iCurCar-1] = carPoint;
            }
            if(destinations->at(iCurCar-1).x == 0)
                continue;
#if DEBUG
            qDebug() << iCurCar << yCar << xCar << destinations->at(iCurCar-1).y << destinations->at(iCurCar-1).x;
#endif
            *mapTemp = *map;
//            for(unsigned short y=1;y<mapSizeY-1;y++){
//                for(unsigned short x=1;x<mapSizeX-1;x++){
//                    if(mapTemp->at(y).at(x) > 1){
//                        if(mapTemp->at(y).at(x) == iCurCar+1)
//                            mapTemp->at(y).at(x) = 1;
//                        else
//                            mapTemp->at(y).at(x) = 0;
//                    }
//                }
//            }
            for(unsigned short i=0;i<cars->size();i++){
                if(cars->at(i) == 0)
                    continue;
                if(i == iCurCar-1){
                    mapTemp->at(cars->at(i)->y() / cellSizeY).at(cars->at(i)->x() / cellSizeX) = 1;
                }else{
                    mapTemp->at(cars->at(i)->y() / cellSizeY).at(cars->at(i)->x() / cellSizeX) = 0;
                }
            }
            QQueue<MaskaPoint> PointsToCheck;
            PointsToCheck.enqueue(destinations->at(iCurCar-1));
            unsigned long long turn = 2;
            bool failed = 0;
            while(MaskaFindCell(*mapTemp,carPoint) == 1){
                unsigned long long size = PointsToCheck.size();
                if(size == 0){
#if DEBUG
                    qDebug() << "WARNING!!! IMPOSSIBLE TO FIND ROUTE!!!";
#endif
                    failed = 1;
                    break;
                }
                for(unsigned long long i=0;i<size;i++){
                    MaskaPoint curCell = PointsToCheck.dequeue();
                    MaskaPoint Up(curCell.y-1,curCell.x),
                               Down(curCell.y+1,curCell.x),
                               Left(curCell.y,curCell.x-1),
                               Right(curCell.y,curCell.x+1);
                    if(MaskaFindCell(*mapTemp,Up) == 1){
                       mapTemp->at(Up.y).at(Up.x) = turn;
                       PointsToCheck.enqueue(Up);
                    }
                    if(MaskaFindCell(*mapTemp,Down) == 1){
                        mapTemp->at(Down.y).at(Down.x) = turn;
                        PointsToCheck.enqueue(Down);
                    }
                    if(MaskaFindCell(*mapTemp,Left) == 1){
                        mapTemp->at(Left.y).at(Left.x) = turn;
                        PointsToCheck.enqueue(Left);
                    }
                    if(MaskaFindCell(*mapTemp,Right) == 1){
                        mapTemp->at(Right.y).at(Right.x) = turn;
                        PointsToCheck.enqueue(Right);
                    }
                }
                turn++;
            }
            if(failed)
                continue;

            MaskaPoint Up(yCar-1,xCar),
                       Down(yCar+1,xCar),
                       Left(yCar,xCar-1),
                       Right(yCar,xCar+1);
            if(MaskaFindCell(*mapTemp,carPoint) == 2 && MaskaFindCell(*mapTemp,destinations->at(iCurCar-1))){
                moveCar(iCurCar,destinations->at(iCurCar-1));
                steps[iCurCar-1][step] = destinations->at(iCurCar-1);
                carPointEnd[iCurCar-1] = step;
                destinations->at(iCurCar-1).x = 0;
                destinations->at(iCurCar-1).y = 0;
            }else if(MaskaFindCell(*mapTemp,Up) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
               qDebug() << iCurCar << "car goes UP";
#endif
               steps[iCurCar-1][step] = Up;
               moveCar(iCurCar,Up);
            }else if(MaskaFindCell(*mapTemp,Down) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
                qDebug() << iCurCar << "car goes DOWN";
#endif
                steps[iCurCar-1][step] = Down;
                moveCar(iCurCar,Down);
            }else if(MaskaFindCell(*mapTemp,Left) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
                qDebug() << iCurCar << "car goes LEFT";
#endif
                steps[iCurCar-1][step] = Left;
                moveCar(iCurCar,Left);
            }else if(MaskaFindCell(*mapTemp,Right) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
                qDebug() << iCurCar << "car goes RIGHT";
#endif
                steps[iCurCar-1][step] = Right;
                moveCar(iCurCar,Right);
            }
            // Check for CRASH
            for(unsigned short i=1;i<=cars->size();i++){
                if(cars->at(i-1) == 0)
                    continue;
                if(cars->at(i-1)->pos().x() == cars->at(iCurCar-1)->pos().x() && cars->at(i-1)->pos().y() == cars->at(iCurCar-1)->pos().y() && i != iCurCar){
                    qDebug() << "FAILURE!!! CRASH OCCURED!!!" << i << iCurCar;
                    cells->at(0)->setBrush(QBrush(Qt::red));
                    return;
                }
            }
        }
    }
#if DEBUG
    qDebug() << "Fine turn" << endl;
#endif
    std::vector<unsigned long long> RightSteps(cars->size(),0);
    std::vector<bool> go(cars->size(),0);
    for(unsigned long long iCurCar = 1;iCurCar <= cars->size();iCurCar++){
        if(cars->at(iCurCar-1) == 0)
            continue;
        for(unsigned long long i=0;i<depth;i++){
#if DEBUG
            qDebug() << "Step "<< i << ": " << steps[iCurCar-1][i].y << steps[iCurCar-1][i].x;
#endif
            if(steps[iCurCar-1][i].x == carPointBegin[iCurCar-1].x && steps[iCurCar-1][i].y == carPointBegin[iCurCar-1].y || steps[iCurCar-1][RightSteps[iCurCar-1]].x == 0){
                bool changeRightStep = 1;
                for(unsigned int j=0;j<iCurCar-1;j++){
                    if(steps[j][RightSteps[j]].x == carPointBegin[iCurCar-1].x && steps[j][RightSteps[j]].y == carPointBegin[iCurCar-1].y){
                        if(steps[iCurCar-1][i+1].x == carPointBegin[j].x && steps[iCurCar-1][i+1].y == carPointBegin[j].y)
                            changeRightStep = 0;
                    }
                }
                if(changeRightStep)
                    RightSteps[iCurCar-1] = i+1;
#if DEBUG
                qDebug() << "Found Right Step: " << steps[iCurCar-1][RightSteps[iCurCar-1]-1].y << steps[iCurCar-1][RightSteps[iCurCar-1]-1].x;
#endif
            }
        }
#if DEBUG
        qDebug() << iCurCar << "car. Right step:" << RightSteps[iCurCar-1];
        qDebug() << carPointBegin[iCurCar-1].y << carPointBegin[iCurCar-1].x;
        qDebug() << steps[iCurCar-1][RightSteps[iCurCar-1]].y << steps[iCurCar-1][RightSteps[iCurCar-1]].x;
        qDebug() << carPointEnd[iCurCar-1];
#endif
        if(destinationsTemp->at(iCurCar-1).x && RightSteps.at(iCurCar-1) < depth){
            go[iCurCar-1] = 1;
            if(abs(int(steps[iCurCar-1][RightSteps[iCurCar-1]].y) - int(carPointBegin[iCurCar-1].y)) + abs(int(steps[iCurCar-1][RightSteps[iCurCar-1]].x) - int(carPointBegin[iCurCar-1].x)) > 1){
                go[iCurCar-1] = 0;
            }
            for(unsigned short i=0;i<iCurCar-1;i++){
                if(steps[iCurCar-1][RightSteps[iCurCar-1]].x == steps[i][RightSteps[i]].x && steps[iCurCar-1][RightSteps[iCurCar-1]].y == steps[i][RightSteps[i]].y){
                    go[iCurCar-1] = 0;
                }
                if(steps[iCurCar-1][RightSteps[iCurCar-1]].x == carPointBegin[i].x && steps[iCurCar-1][RightSteps[iCurCar-1]].y == carPointBegin[i].y){
                    if(steps[i][RightSteps[i]].x == carPointBegin[iCurCar-1].x && steps[i][RightSteps[i]].y == carPointBegin[iCurCar-1].y){
                        go[iCurCar-1] = 0;
                        moveCar(i+1,carPointBegin[i]);
                    }
                    if(go[i] == 0){
                        go[iCurCar-1] = 0;
                        moveCar(iCurCar,carPointBegin[iCurCar-1]);
                    }
                }
            }
            if(go[iCurCar-1] == 0){
                for(unsigned short i=0;i<iCurCar-1;i++){
                    if(steps[i][RightSteps[i]].x == carPointBegin[iCurCar-1].x && steps[i][RightSteps[i]].y == carPointBegin[iCurCar-1].y){
                        if(go[i]){
                            go[i] = 0;
                            QQueue<long long> delGo;
                            delGo.enqueue(i);
                            while(delGo.size()){
                                for(unsigned short j=0;j<iCurCar-1;j++){
                                    if(steps[j][RightSteps[j]].x == carPointBegin[delGo[0]].x && steps[j][RightSteps[j]].y == carPointBegin[delGo[0]].y){
                                        if(go[j]){
                                            go[j] = 0;
                                            moveCar(j+1,carPointBegin[j]);
                                            delGo.enqueue(j);
                                        }
                                    }
                                }
                                delGo.pop_front();
                            }
                            moveCar(i+1,carPointBegin[i]);
                        }
                    }
                }
            }

            destinations->at(iCurCar-1) = destinationsTemp->at(iCurCar-1);
            if(go[iCurCar-1]){
                moveCar(iCurCar,steps[iCurCar-1][RightSteps[iCurCar-1]]);
                if(steps[iCurCar-1][RightSteps[iCurCar-1]].x == destinations->at(iCurCar-1).x && steps[iCurCar-1][RightSteps[iCurCar-1]].y == destinations->at(iCurCar-1).y){
                    destinations->at(iCurCar-1).x = 0;
                    destinations->at(iCurCar-1).y = 0;
                    destinationsText->at(iCurCar-1)->setVisible(0);
                    // Fun  code
                    if(iCurCar > points.size()){
                        points.resize(iCurCar);
                    }
                    points[iCurCar-1]++;
                    // End of Fun code
                }
            }else{
                moveCar(iCurCar,carPointBegin[iCurCar-1]);
                for(unsigned long long i=0;i<iCurCar;i++){
                    if(cars->at(i) == 0)
                        continue;
                    if(cars->at(i)->x() == cars->at(iCurCar-1)->x() && cars->at(i)->y() == cars->at(iCurCar-1)->y()){
                        moveCar(i+1,carPointBegin[i]);
                    }
                }
            }
        }else{
            moveCar(iCurCar,carPointBegin[iCurCar-1]);
            for(unsigned short i=0;i<iCurCar-1;i++){
                if(steps[i][RightSteps[i]].x == carPointBegin[iCurCar-1].x && steps[i][RightSteps[i]].y == carPointBegin[iCurCar-1].y){
                    if(go[i]){
                        go[i] = 0;
                        QQueue<long long> delGo;
                        delGo.enqueue(i);
                        while(delGo.size()){
                            for(unsigned short j=0;j<iCurCar-1;j++){
                                if(steps[j][RightSteps[j]].x == carPointBegin[delGo[0]].x && steps[j][RightSteps[j]].y == carPointBegin[delGo[0]].y){
                                    if(go[j]){
                                        go[j] = 0;
                                        moveCar(j+1,carPointBegin[j]);
                                        delGo.enqueue(j);
                                    }
                                }
                            }
                            delGo.pop_front();
                        }
                        moveCar(i+1,carPointBegin[i]);

                    }
                }
            }
        }
    }
#if DEBUG
    qDebug() << "go[] START";
    for(unsigned short i=0;i<cars->size();i++){
        qDebug() << i+1 << go[i] << carPointBegin[i].y << carPointBegin[i].x << steps[i][RightSteps[i]].y << steps[i][RightSteps[i]].x;
    }
    qDebug() << "go[] END";
#endif
    int positionChanged = 0;
    for(unsigned short i=0;i<cars->size();i++){
        positionChanged += go[i];
    }
    if(!positionChanged){
        for(unsigned short i=0;i<cars->size();i++){
            nextTurn(i+1);
        }
    }
    /*
    for(unsigned short y=0;y<mapSizeY;y++){
        for(unsigned short x=0;x<mapSizeX;x++){
            if(map->at(y).at(x))
                map->at(y).at(x) = 1;
        }
    }
    for(unsigned short i=0;i<cars->size();i++){
        map->at(cars->at(i)->y()/cellSizeY).at(cars->at(i)->x()/cellSizeX) = i+2;
    }*/
//    if(!positionChanged){
//        qDebug() << "PANIC!!! I DON'T KNOW WHAT TO DO! SYSTEM ERROR!";
//        std::vector<std::vector<std::vector<mapType> > > waveMaps(cars->size(),(std::vector<std::vector<mapType> > (mapSizeY,std::vector<mapType> (mapSizeX,0))));
//        std::vector<std::vector<MaskaPoint> > route(cars->size(),(std::vector<MaskaPoint> (0)));
//        waveMaps[0] = *map;
//        for(unsigned short i = 0;i<cars->size();i++){
//            if(destinations->at(i).x == 0)
//                waveMaps[i][cars->at(i)->y()/cellSizeY][cars->at(i)->x()/cellSizeX] = 0;
//        }
//        for(unsigned short i = 1;i<cars->size();i++)
//            waveMaps[i] = waveMaps[i-1];
//        for(unsigned short iCurCar = 1;iCurCar <= cars->size();iCurCar++){
//            if(destinations->at(iCurCar-1).x == 0)
//                continue;
//            unsigned int yCar = cars->at(iCurCar-1)->y()/cellSizeY, xCar = cars->at(iCurCar-1)->x()/cellSizeX;
//            MaskaPoint carPoint(yCar,xCar);

//            QQueue<MaskaPoint> PointsToCheck;
//            PointsToCheck.enqueue(destinations->at(iCurCar-1));
//            unsigned long long turn = 2;
//            bool failed = 0;
//            while(MaskaFindCell(waveMaps[iCurCar-1],carPoint) == 1){
//                unsigned long long size = PointsToCheck.size();
//                if(size == 0){
//                    failed = 1;
//                    break;
//                }
//                for(unsigned long long i=0;i<size;i++){
//                    MaskaPoint curCell = PointsToCheck.dequeue();
//                    MaskaPoint Up(curCell.y-1,curCell.x),
//                               Down(curCell.y+1,curCell.x),
//                               Left(curCell.y,curCell.x-1),
//                               Right(curCell.y,curCell.x+1);
//                    if(MaskaFindCell(waveMaps[iCurCar-1],Up) == 1){
//                       waveMaps[iCurCar-1].at(Up.y).at(Up.x) = turn;
//                       PointsToCheck.enqueue(Up);
//                    }
//                    if(MaskaFindCell(waveMaps[iCurCar-1],Down) == 1){
//                        waveMaps[iCurCar-1].at(Down.y).at(Down.x) = turn;
//                        PointsToCheck.enqueue(Down);
//                    }
//                    if(MaskaFindCell(waveMaps[iCurCar-1],Left) == 1){
//                        waveMaps[iCurCar-1].at(Left.y).at(Left.x) = turn;
//                        PointsToCheck.enqueue(Left);
//                    }
//                    if(MaskaFindCell(waveMaps[iCurCar-1],Right) == 1){
//                        waveMaps[iCurCar-1].at(Right.y).at(Right.x) = turn;
//                        PointsToCheck.enqueue(Right);
//                    }
//                }
//                turn++;
//            }
//            if(failed)
//                continue;
//            while(true){
//                yCar = carPoint.y;
//                xCar = carPoint.x;
//                MaskaPoint Up(yCar-1,xCar),
//                           Down(yCar+1,xCar),
//                           Left(yCar,xCar-1),
//                           Right(yCar,xCar+1);

//                if(MaskaFindCell(waveMaps[iCurCar-1],carPoint) == 2 && MaskaFindCell(waveMaps[iCurCar-1],destinations->at(iCurCar-1))){
//                    route[iCurCar-1].push_back(destinations->at(iCurCar-1));
//                    break;
//                }else if(MaskaFindCell(waveMaps[iCurCar-1],Up) == MaskaFindCell(waveMaps[iCurCar-1],carPoint)-1){
//                   route[iCurCar-1].push_back(Up);
//                }else if(MaskaFindCell(waveMaps[iCurCar-1],Down) == MaskaFindCell(waveMaps[iCurCar-1],carPoint)-1){
//                    route[iCurCar-1].push_back(Down);
//                }else if(MaskaFindCell(waveMaps[iCurCar-1],Left) == MaskaFindCell(waveMaps[iCurCar-1],carPoint)-1){
//                    route[iCurCar-1].push_back(Left);
//                }else if(MaskaFindCell(waveMaps[iCurCar-1],Right) == MaskaFindCell(waveMaps[iCurCar-1],carPoint)-1){
//                    route[iCurCar-1].push_back(Right);
//                }
//                carPoint.y = route[iCurCar-1][route[iCurCar-1].size()-1].y;
//                carPoint.x = route[iCurCar-1][route[iCurCar-1].size()-1].x;
//            }
//        }
//        for(unsigned short i = 0;i<cars->size();i++){
//            waveMaps[i] = *map;
//            for(unsigned short j = 0;j<cars->size();j++){
//                if(i != j)
//                    waveMaps[i][cars->at(j)->y()/cellSizeY][cars->at(j)->x()/cellSizeX] = 0;
//            }
//        }
//        for(unsigned short iCurCar0 = 0;iCurCar0 < cars->size();iCurCar0++){
//            for(unsigned short step = 0;step < route[iCurCar0].size();step++){
//                for(unsigned short i=0;i<cars->size();i++){
//                    if(i != iCurCar0){
//                        if(cars->at(i)->x()/cellSizeX == route[iCurCar0][step].x && cars->at(i)->y()/cellSizeY == route[iCurCar0][step].y){
//                            QQueue<MaskaPoint> PointsToCheck;
//                            PointsToCheck.enqueue(MaskaPoint(route[iCurCar0][step].y,route[iCurCar0][step].x));
//                            unsigned long long turn = 2;
//                            bool failed = 0;
//                            while(true){
//                                unsigned long long size = PointsToCheck.size();
//                                if(size == 0){
//                                    failed = 1;
//                                    break;
//                                }
//                                for(unsigned long long currentPoint=0;currentPoint<size;currentPoint++){
//                                    MaskaPoint curCell = PointsToCheck.dequeue();
//                                    MaskaPoint Up(curCell.y-1,curCell.x),
//                                               Down(curCell.y+1,curCell.x),
//                                               Left(curCell.y,curCell.x-1),
//                                               Right(curCell.y,curCell.x+1);
//                                    bool ok = 1;
//                                    if(MaskaFindCell(waveMaps[i],Up) == 1){
//                                       waveMaps[i].at(Up.y).at(Up.x) = turn;
//                                       for(unsigned short step2 = 0;step2 < route[i].size();step2++){
//                                            if(route[i][step2].x == Up.x && route[i][step2].y == Up.y)
//                                                ok = 0;
//                                       }
//                                       if(ok){
//                                           MaskaPoint curPoint = Up;
//                                           while(MaskaFindCell(waveMaps[i],curPoint) != 2){
//                                               MaskaPoint Up2(curPoint.y-1,curPoint.x),
//                                                          Down2(curPoint.y+1,curPoint.x),
//                                                          Left2(curPoint.y,curPoint.x-1),
//                                                          Right2(curPoint.y,curPoint.x+1);
//                                               if(MaskaFindCell(waveMaps[i],Up2) == MaskaFindCell(waveMaps[i],curPoint)-1){
//                                                    curPoint = Up2;
//                                               }else if(MaskaFindCell(waveMaps[i],Down2) == MaskaFindCell(waveMaps[i],curPoint)-1){
//                                                   curPoint = Down2;
//                                               }else if(MaskaFindCell(waveMaps[i],Left2) == MaskaFindCell(waveMaps[i],curPoint)-1){
//                                                   curPoint = Left2;
//                                               }else if(MaskaFindCell(waveMaps[i],Right2) == MaskaFindCell(waveMaps[i],curPoint)-1){
//                                                   curPoint = Right2;
//                                               }
//                                           }
//                                           moveCar(i+1,curPoint,MaskaPoint(cars->at(iCurCar0)->y()/cellSizeY,cars->at(iCurCar0)->x()/cellSizeX));
//                                           return;
//                                       }
//                                       PointsToCheck.enqueue(Up);
//                                    }
//                                    ok = 1;
//                                    if(MaskaFindCell(waveMaps[iCurCar0],Down) == 1){
//                                        waveMaps[iCurCar0].at(Down.y).at(Down.x) = turn;
//                                        PointsToCheck.enqueue(Down);
//                                    }
//                                    ok = 1;
//                                    if(MaskaFindCell(waveMaps[iCurCar0],Left) == 1){
//                                        waveMaps[iCurCar0].at(Left.y).at(Left.x) = turn;
//                                        PointsToCheck.enqueue(Left);
//                                    }
//                                    ok = 1;
//                                    if(MaskaFindCell(waveMaps[iCurCar0],Right) == 1){
//                                        waveMaps[iCurCar0].at(Right.y).at(Right.x) = turn;
//                                        PointsToCheck.enqueue(Right);
//                                    }
//                                }
//                                turn++;
//                            }
//                            if(failed)
//                                continue;
//                        }
//                    }
//                }
//            }
//        }
//    }
    updateMap();
    delete mapTemp;
    for(unsigned short i=0;i<cars->size();i++){
        if(cars->at(i) == 0)
            continue;
        else if(abs(int(cars->at(i)->y()/cellSizeY) - int(carPointBegin[i].y)) + abs(int(cars->at(i)->x()/cellSizeX) - int(carPointBegin[i].x)) > 1){
            qDebug() << "KOLYAN TI LOCH!!! RAKALISHE!!! UBRAT BAG NE MOSHESH!!!";
        }
    }
}

MaskaPoint Map::nextTurn(unsigned long long number){
    if(number > cars->size())
        return MaskaPoint(0,0);
    if(cars->at(number-1) == 0)
        return MaskaPoint(0,0);
    if(destinations->at(number-1).x == 0)
        return MaskaPoint(0,0);
    std::vector<std::vector<mapType> > *mapTemp = new std::vector<std::vector<mapType> >;
    std::vector<std::vector<MaskaPoint> > steps(cars->size(),std::vector<MaskaPoint> (depth,MaskaPoint(0,0)));
    std::vector<MaskaPoint> carPointBegin(cars->size());
    std::vector<unsigned int> carPointEnd(cars->size(),depth-1);
    std::vector<MaskaPoint> *destinationsTemp = new std::vector<MaskaPoint>;
    *destinationsTemp = *destinations;
    for(unsigned short step = 0;step < depth;step++){
        for(unsigned short iCurCar = 1;iCurCar <= cars->size();iCurCar++){
            if(cars->at(iCurCar-1) == 0)
                continue;
            unsigned int yCar = cars->at(iCurCar-1)->y()/cellSizeY, xCar = cars->at(iCurCar-1)->x()/cellSizeX;
            MaskaPoint carPoint(yCar,xCar);

            if(step == 0){
                carPointBegin[iCurCar-1] = carPoint;
            }
            if(destinations->at(iCurCar-1).x == 0)
                continue;
#if DEBUG
            qDebug() << iCurCar << yCar << xCar << destinations->at(iCurCar-1).y << destinations->at(iCurCar-1).x;
#endif
            *mapTemp = *map;
//            for(unsigned short y=1;y<mapSizeY-1;y++){
//                for(unsigned short x=1;x<mapSizeX-1;x++){
//                    if(mapTemp->at(y).at(x) > 1){
//                        if(mapTemp->at(y).at(x) == iCurCar+1)
//                            mapTemp->at(y).at(x) = 1;
//                        else
//                            mapTemp->at(y).at(x) = 0;
//                    }
//                }
//            }
            for(unsigned short i=0;i<cars->size();i++){
                if(cars->at(i) == 0)
                    continue;
                else if(i == iCurCar-1){
                    mapTemp->at(cars->at(i)->y() / cellSizeY).at(cars->at(i)->x() / cellSizeX) = 1;
                }else{
                    mapTemp->at(cars->at(i)->y() / cellSizeY).at(cars->at(i)->x() / cellSizeX) = 0;
                }
            }
            QQueue<MaskaPoint> PointsToCheck;
            PointsToCheck.enqueue(destinations->at(iCurCar-1));
            unsigned long long turn = 2;
            bool failed = 0;
            while(MaskaFindCell(*mapTemp,carPoint) == 1){
                unsigned long long size = PointsToCheck.size();
                if(size == 0){
#if DEBUG
                    qDebug() << "WARNING!!! IMPOSSIBLE TO FIND ROUTE!!!";
#endif
                    failed = 1;
                    break;
                }
                for(unsigned long long i=0;i<size;i++){
                    MaskaPoint curCell = PointsToCheck.dequeue();
                    MaskaPoint Up(curCell.y-1,curCell.x),
                               Down(curCell.y+1,curCell.x),
                               Left(curCell.y,curCell.x-1),
                               Right(curCell.y,curCell.x+1);
                    if(MaskaFindCell(*mapTemp,Up) == 1){
                       mapTemp->at(Up.y).at(Up.x) = turn;
                       PointsToCheck.enqueue(Up);
                    }
                    if(MaskaFindCell(*mapTemp,Down) == 1){
                        mapTemp->at(Down.y).at(Down.x) = turn;
                        PointsToCheck.enqueue(Down);
                    }
                    if(MaskaFindCell(*mapTemp,Left) == 1){
                        mapTemp->at(Left.y).at(Left.x) = turn;
                        PointsToCheck.enqueue(Left);
                    }
                    if(MaskaFindCell(*mapTemp,Right) == 1){
                        mapTemp->at(Right.y).at(Right.x) = turn;
                        PointsToCheck.enqueue(Right);
                    }
                }
                turn++;
            }
            if(failed)
                continue;
            MaskaPoint Up(yCar-1,xCar),
                       Down(yCar+1,xCar),
                       Left(yCar,xCar-1),
                       Right(yCar,xCar+1);
            if(MaskaFindCell(*mapTemp,carPoint) == 2 && MaskaFindCell(*mapTemp,destinations->at(iCurCar-1))){
                moveCar(iCurCar,destinations->at(iCurCar-1));
                steps[iCurCar-1][step] = destinations->at(iCurCar-1);
                carPointEnd[iCurCar-1] = step;
                destinations->at(iCurCar-1).x = 0;
                destinations->at(iCurCar-1).y = 0;
            }else if(MaskaFindCell(*mapTemp,Up) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
               qDebug() << iCurCar << "car goes UP";
#endif
               steps[iCurCar-1][step] = Up;
               moveCar(iCurCar,Up);
            }else if(MaskaFindCell(*mapTemp,Down) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
                qDebug() << iCurCar << "car goes DOWN";
#endif
                steps[iCurCar-1][step] = Down;
                moveCar(iCurCar,Down);
            }else if(MaskaFindCell(*mapTemp,Left) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
                qDebug() << iCurCar << "car goes LEFT";
#endif
                steps[iCurCar-1][step] = Left;
                moveCar(iCurCar,Left);
            }else if(MaskaFindCell(*mapTemp,Right) == MaskaFindCell(*mapTemp,carPoint)-1){
#if DEBUG
                qDebug() << iCurCar << "car goes RIGHT";
#endif
                steps[iCurCar-1][step] = Right;
                moveCar(iCurCar,Right);
            }
            // Check for CRASH
            for(unsigned short i=1;i<=cars->size();i++){
                if(cars->at(i-1) == 0)
                    continue;
                if(cars->at(i-1)->pos().x() == cars->at(iCurCar-1)->pos().x() && cars->at(i-1)->pos().y() == cars->at(iCurCar-1)->pos().y() && i != iCurCar){
                    qDebug() << "FAILURE!!! CRASH OCCURED!!!";
                    cells->at(0)->setBrush(QBrush(Qt::red));
                    return MaskaPoint(0,0);
                }
            }
        }
    }
#if DEBUG
    qDebug() << "Fine turn" << endl;
#endif
    unsigned long long RightStep = 0;
    for(unsigned long long i=0;i<depth;i++){
#if DEBUG
        qDebug() << "Step "<< i << ": " << steps[number-1][i].y << steps[number-1][i].x;
#endif
        if(steps[number-1][i].x == carPointBegin[number-1].x && steps[number-1][i].y == carPointBegin[number-1].y){
            bool changeRightStep = 1;
            for(unsigned int carNumber0=0;carNumber0<cars->size();carNumber0++){
                if(carNumber0+1 == number)
                    continue;
                if(steps[carNumber0][RightStep].x == carPointBegin[number-1].x && steps[carNumber0][RightStep].y == carPointBegin[number-1].y){
                    if(steps[number-1][i+1].x == carPointBegin[carNumber0].x && steps[number-1][i+1].y == carPointBegin[carNumber0].y)
                        changeRightStep = 0;
                }
            }
            if(changeRightStep)
                RightStep = i+1;
#if DEBUG
            qDebug() << "Found Right Step: " << steps[number-1][RightStep].y << steps[number-1][RightStep].x;
#endif
        }
    }
#if DEBUG
    qDebug() << number << "car. Right step:" << RightStep;
    qDebug() << carPointBegin[number-1].y << carPointBegin[number-1].x;
    qDebug() << steps[number-1][RightStep].y << steps[number-1][RightStep].x;
    qDebug() << carPointEnd[number-1];
#endif
    if(destinationsTemp->at(number-1).x && RightStep < depth){
        bool go = steps[number-1][RightStep].x;
        for(unsigned short j=0;j<cars->size();j++){
            if(steps[number-1][RightStep].x == carPointBegin[j].x && steps[number-1][RightStep].y == carPointBegin[j].y)
                go = 0;
        }

        destinations->at(number-1) = destinationsTemp->at(number-1);
        if(go){
            moveCar(number,steps[number-1][RightStep]);
            if(steps[number-1][RightStep].x == destinations->at(number-1).x && steps[number-1][RightStep].y == destinations->at(number-1).y){
                qDebug() << "End of Destination";
                destinations->at(number-1).x = 0;
                destinations->at(number-1).y = 0;
                destinationsText->at(number-1)->setVisible(0);
            }
        }else{
            moveCar(number,carPointBegin[number-1]);
        }
    }
    for(unsigned long long i=0;i<cars->size();i++){
        if(i+1 != number){
            if(steps[i][carPointEnd[i]].x != 0)
                moveCar(i+1,carPointBegin[i]);
            destinations->at(i) = destinationsTemp->at(i);
        }
    }
    updateMap();
    return steps[number-1][RightStep];
}

bool Map::setDestination(unsigned long long number, MaskaPoint destination, bool newDest){
    if(number > cars->size() || cars->at(number-1) == 0)
        return 0;
    if(destinations->at(number-1).x && newDest == 0)
        return 0;
    unsigned long long x = destination.x,
                       y = destination.y;
    for(unsigned short i=0;i<cars->size();i++){
        if(destinations->at(i).x == x && destinations->at(i).y == y)
            return 1;
    }

    if(map->at(y).at(x) == 1){
        destinations->at(number-1).x = x;
        destinations->at(number-1).y = y;
        destinationsText->at(number-1)->setPos(x*cellSizeX,y*cellSizeY);
        destinationsText->at(number-1)->setVisible(1);
        return 0;
    }
    return 1;
}
