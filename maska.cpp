#include "maska.h"
#include "ui_maska.h"

#include <QDebug>
#include <QWindow>
#include <QMenuBar>

#include <ctime>
#include <algorithm>

Maska::Maska(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Maska)
{
    ui->setupUi(this);
    map = new Map;
    mapView = new mapViewer;
    timer = new QTimer;
    messageBox = new QMessageBox;
    timer->setInterval(2048);
    randomType = 1;
    stickyRandom = 0;

 //   ui->gridLayout->addWidget(mapView,0,2,0,1);

    mapView->setScene(map);
    ui->mapViewConst->setScene(map);
    ui->statusBar->showMessage("Timer interval: " + QString::number(timer->interval()) + " ms");

    carPushButtons = new std::vector<Car*>;
    connect(ui->addCar,SIGNAL(clicked()),this,SLOT(addCar()));
    connect(ui->deleteCar,SIGNAL(clicked()),this,SLOT(deleteCar()));
    connect(timer,SIGNAL(timeout()),this,SLOT(nextTurn()));
}

Maska::~Maska()
{
    for(unsigned long long i=0;i<carPushButtons->size();i++)
        delete carPushButtons->at(i);
    delete carPushButtons;
    delete ui;
    delete timer;
}

void Maska::addCar(){
    Car *car = new Car(carPushButtons->size()+1);
    carPushButtons->push_back(car);

    connect(car,SIGNAL(clicked(bool)),this,SLOT(selectCar(bool)));

    ui->gridLayout->addWidget(car,carPushButtons->size()+3,0,1,2);
    ui->gridLayout->addWidget(ui->mapViewConst,0,3,carPushButtons->size()+5,1);
//    ui->gridLayout->addWidget(mapView,0,3,carPushButtons->size()+2,1);
}

void Maska::deleteCar(){
    if(carPushButtons->size() == 0)
        return;
    map->deleteCar(carPushButtons->size());
    delete carPushButtons->at(carPushButtons->size()-1);
    carPushButtons->pop_back();
    map->updateMap();
}

void Maska::selectCar(bool checked){
    if(checked == 0){
        map->setCurrentCar(0);
        return;
    }
    unsigned short size = carPushButtons->size();
    unsigned short newCar = 0;
    for(unsigned short i=0;i<size;i++){
        if(carPushButtons->at(i)->isChecked()){
            if(i+1 == map->currentCar()){
                carPushButtons->at(i)->setChecked(0);
                carPushButtons->at(i)->setCheckState(0);
            }else{
                newCar = i+1;
            }
        }
    }
    map->setCurrentCar(newCar);
}

void Maska::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_0){
        if(carPushButtons->size() > 9)
            carPushButtons->at(9)->click();
    }if(event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9){
        if(carPushButtons->size() > event->key()-Qt::Key_1)
            carPushButtons->at(event->key()-Qt::Key_1)->click();
    }else if(event->key() == Qt::Key_F11){
        qDebug() << "F11 pressed. Updating map...";
        map->updateMap();
        qDebug() << "Update ended.";
    }else if(event->text() == "\f"){ // Ctrl + L
        map->setLockMap(!map->isLockedMap()); // change lockMap
        qDebug() << "lockMap =" << map->isLockedMap();
    }else if(event->key() == Qt::Key_F2){
        if(randomType == 0)
            on_actionRandomALL_triggered();
        else
            on_actionRandom_unset_destinations_triggered();
    }else if(event->text() == "\u0010"){ // Ctrl + P  // This is FUN CODE
        QString a("");
        for(unsigned short i=0;i<points.size();i++)
            a.push_back("Car " + QString::number(i+1) + " : " + QString::number(points[i]) + "\n");
        messageBox->setText(a);
        messageBox->show(); // End of FUN CODE
    }else{
        qDebug() << event->text();
    }
}

void Maska::setMap(std::vector<std::vector<mapType> > NewMap){
    map->setMap(NewMap);
}

void Maska::on_addSpeed_clicked(){
    if(timer->interval() != 1)
        timer->setInterval(timer->interval()/2);
    ui->statusBar->showMessage("Timer interval: " + QString::number(timer->interval()) + " ms");
}

void Maska::on_decSpeed_clicked(){
    if(timer->interval() <= 100000)
        timer->setInterval(timer->interval()*2);
    ui->statusBar->showMessage("Timer interval: " + QString::number(timer->interval()) + " ms");
}

void Maska::on_nextTurn_clicked(){
    map->nextTurn();
}

void Maska::nextTurn(){
    map->nextTurn();
    if(stickyRandom){
        if(randomType == 0)
            on_actionRandomALL_triggered();
        else
            on_actionRandom_unset_destinations_triggered();
    }
}

void Maska::on_autoNextTurn_clicked(bool checked){
    if(checked)
        timer->start();
    else
        timer->stop();
}

void Maska::on_actionRandomALL_triggered(){
    for(unsigned short i=0;i<carPushButtons->size();i++){
        while(map->setDestination(i+1,MaskaPoint(rand()%(mapSizeY-2) + 1,rand()%(mapSizeX-2) + 1),1));
    }
    randomType = 0;
}

void Maska::on_actionRandom_unset_destinations_triggered(){
    for(unsigned short i=0;i<carPushButtons->size();i++){
        while(map->setDestination(i+1,MaskaPoint(rand()%(mapSizeY-2) + 1,rand()%(mapSizeX-2) + 1)));
    }
    randomType = 1;
}

void Maska::on_actionSticky_Random_triggered(bool checked){
    stickyRandom = checked;
}

void Maska::on_reset_clicked(){
    while(carPushButtons->size())
        deleteCar();
    map->updateMap();
}

void Maska::wheelEvent(QWheelEvent *event){
    if(carPushButtons->size() == 0)
        return;
    if(event->delta() < 0){
        carPushButtons->at(map->currentCar()%carPushButtons->size())->click();
    }else if(event->delta() > 0){
        if(map->currentCar() == 1)
            carPushButtons->at(carPushButtons->size()-1)->click();
        else
            carPushButtons->at(map->currentCar()-2)->click();
    }
}
