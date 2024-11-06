// enemigo.h
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Enemigo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Enemigo(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;

public slots:
    void mover();

private:
    int dx = -5;  // Velocidad en el eje x
    int dy = 0;   // Velocidad en el eje y
};

#endif // ENEMIGO_H

