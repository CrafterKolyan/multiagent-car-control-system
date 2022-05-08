#include "car.h"

#include <QDebug>

Car::Car()
{
    this->setCheckable(1);
    this->setText("Car");
    check = 0;
    connect(this,SIGNAL(clicked(bool)),this,SLOT(changeCheckState(bool)));
}

Car::Car(unsigned short number)
{
    this->setCheckable(1);
    this->setText("Car " + QString::number(number));

    check = 0;
    connect(this,SIGNAL(clicked(bool)),this,SLOT(changeCheckState(bool)));
}

void Car::setCheckState(bool a){
    check = a;
}

bool Car::isChecked(){
    return check;
}

void Car::changeCheckState(bool checkState){
    check = checkState;
}

Car::~Car(){
    check = 0;
}
