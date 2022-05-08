#ifndef CAR_H
#define CAR_H

#include <QWidget>
#include <QPushButton>
#include <QObject>

class Car : public QPushButton
{
    Q_OBJECT
public:
    explicit Car();
    ~Car();
    Car(unsigned short number);
    bool isChecked();
    void setCheckState(bool);

signals:

public slots:

private slots:
    void changeCheckState(bool);

private:
    bool check;
};

#endif // CAR_H
