#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "bomb.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QApplication>
#include <QTimer>
#include <QObject>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Personaje();  // Constructor
    void colocarBomba();  // Método para colocar una bomba
    QRectF boundingRect() const override;
public slots:
    void manejarExplosion();  // Slot para manejar la explosión de la bomba
    void animarMuerte();  // Slot para la animación de muerte

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    void cambiarSprite(const QString& direccion);
    void morir();

    // Sprites para el personaje
    QPixmap quieto, abajo1, abajo2, izquierda1, izquierda2, derecha1, derecha2, arriba1, arriba2;
    QPixmap muerte1, muerte2, muerte3, muerte4, muerte5, muerte6, muerte7;

    bool usandoSprite1;
    int indiceMuerte;

    Bomb* bombaActual;
};

#endif // PERSONAJE_H
