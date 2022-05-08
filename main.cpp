#include "maska.h"

#include <QApplication>
#include <QObject>
#include <QDebug>

#include <fstream>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(0));
    std::ifstream inputMap("map.maska");
    if(inputMap.is_open()){
        qDebug() << "Uploading from file map.maska";
        inputMap >> mapSizeY >> mapSizeX;
        mapSizeY += 2;
        mapSizeX += 2;
    }else{
        qDebug() << "Can't find map.maska";
        qDebug() << "Starting with standard constants";
    }
    QApplication a(argc, argv);
    Maska w;
    if(inputMap.is_open()){
        std::vector<std::vector<mapType> > map(mapSizeY,std::vector<mapType> (mapSizeX,0));
        char inputChar;
        for(unsigned long long y=1;y<mapSizeY-1;y++){
            for(unsigned long long x=1;x<mapSizeX-1;x++){
               inputMap >> inputChar;
               if(inputChar == '1'){
                   map[y][x] = 1;
               }
            }
        }
        w.setMap(map);
    }
    w.showFullScreen();

    return a.exec();

}
