#include "enemigo.h"
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>
bool D = true;
Enemigo::Enemigo(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    // Establece la imagen del enemigo. Asegúrate de que la ruta sea correcta.
    setPixmap(QPixmap("Globo.png"));

    // Crea el temporizador para el movimiento automático
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemigo::mover);
    timer->start(50); // Cambia el valor para ajustar la frecuencia de movimiento

}
QRectF Enemigo::boundingRect() const
{
    return QRectF(1, 1, pixmap().width() - 2, pixmap().height() - 2);
}

void Enemigo::mover()
{
    // Mueve el enemigo en la dirección definida por dx y dy
    setPos(x() + dx, y() + dy);

    // Verificar colisiones
    QList<QGraphicsItem*> collidingItemsList = collidingItems();

    for (QGraphicsItem* item : collidingItemsList) {
        // Verificar si el enemigo colisiona con un muro
        if (item->data(0) == "pared") {  // La etiqueta "pared" la usaste para los muros
            // Deshacer el movimiento si colisiona con un muro
            setPos(x() - dx, y() - dy);

            // Cambiar la dirección para evitar el muro (ejemplo de cambio horizontal)
            dx = -dx;
            break;  // Salir del bucle si ya encontró un muro
        }
    }
    if (pos().x() + pixmap().width() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}


