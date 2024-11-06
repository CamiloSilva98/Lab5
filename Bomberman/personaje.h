#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>

class Personaje : public QGraphicsPixmapItem {
public:
    Personaje();  // Constructor para cargar las imágenes del personaje

    // Método para cambiar el sprite (imagen) del personaje
    void cambiarSprite(const QString& direccion);

    // Método para manejar el movimiento del personaje
    void keyPressEvent(QKeyEvent* event);
    QRectF boundingRect() const override;

private:
    QPixmap quieto, arriba1, arriba2, abajo1, abajo2, derecha1, derecha2, izquierda1, izquierda2;
    bool usandoSprite1;
};

#endif // PERSONAJE_H
