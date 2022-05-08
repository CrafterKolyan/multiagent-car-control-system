#include "mapviewer.h"

#include <QDebug>

static unsigned int firstResize = 1;

mapViewer::mapViewer(QGraphicsView *parent) : QGraphicsView(parent)
{

}

void mapViewer::resizeEvent(QResizeEvent *event){
    if(!firstResize)
        this->scale(double(event->size().width())/event->oldSize().width(),double(event->size().height())/event->oldSize().height());
    else
        firstResize = 0;
}
