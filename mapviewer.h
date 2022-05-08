#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QWidget>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QSize>

class mapViewer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit mapViewer(QGraphicsView *parent = 0);

public slots:
    void resizeEvent(QResizeEvent *event);
};

#endif // MAPVIEWER_H
