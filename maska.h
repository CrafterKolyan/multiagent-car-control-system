#ifndef MASKA_H
#define MASKA_H

#include "car.h"
#include "map.h"
#include "mapviewer.h"

#include <QMainWindow>
#include <QPushButton>
#include <QKeyEvent>
#include <QObject>
#include <QAction>
#include <QTimer>
#include <QMessageBox>
#include <QWheelEvent>

namespace Ui {
class Maska;
}

class Maska : public QMainWindow
{
    Q_OBJECT

public:
    explicit Maska(QWidget *parent = 0);
    ~Maska();

public slots:
    void addCar();
    void deleteCar();
    void selectCar(bool);
    void setMap(std::vector<std::vector<mapType> > NewMap);
    void wheelEvent(QWheelEvent *);

private slots:
    void keyPressEvent(QKeyEvent *);
    void on_addSpeed_clicked();
    void on_decSpeed_clicked();
    void on_nextTurn_clicked();
    void nextTurn();
    void on_autoNextTurn_clicked(bool checked);
    void on_actionRandomALL_triggered();
    void on_actionRandom_unset_destinations_triggered();
    void on_actionSticky_Random_triggered(bool checked);
    void on_reset_clicked();

private:
    Map *map;
    mapViewer *mapView;
    std::vector<Car*> *carPushButtons;
    Ui::Maska *ui;
    QTimer* timer;
    QMessageBox *messageBox;
    unsigned int randomType;
    bool stickyRandom;
};

#endif // MASKA_H
