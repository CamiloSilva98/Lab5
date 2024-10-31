#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Personaje : public QGraphicsPixmapItem {
public:
    Personaje();  // Constructor para cargar las imágenes del personaje

    // Método para cambiar el sprite (imagen) del personaje
    void cambiarSprite();

    // Método para manejar el movimiento del personaje
    void keyPressEvent(QKeyEvent* event);

private:
    QPixmap sprite1;  // Primera imagen del personaje
    QPixmap sprite2;  // Segunda imagen del personaje
    bool usandoSprite1;  // Controla cuál sprite está usando el personaje
};

#endif // PERSONAJE_H
