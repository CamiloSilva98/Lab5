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
    void cambiarSprite();

    // Método para manejar el movimiento del personaje
    void keyPressEvent(QKeyEvent* event);
    QRectF boundingRect() const override;

private:
    QPixmap sprite1;
    QPixmap arriba1;
    QPixmap arriba2;
    QPixmap abajo1;
    QPixmap abajo2;
    QPixmap derecha1;
    QPixmap derecha2;
    QPixmap izquierda1;
    QPixmap izquierda2;
    bool usandoSprite1;  // Controla cuál sprite está usando el personaje
};

#endif // PERSONAJE_H
