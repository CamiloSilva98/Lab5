#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QObject>
class Personaje : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    Personaje();  // Constructor para cargar las imágenes del personaje

    // Método para cambiar el sprite (imagen) del personaje
    void cambiarSprite(const QString& direccion);

    // Método para manejar el movimiento del personaje
    void keyPressEvent(QKeyEvent* event);
    QRectF boundingRect() const override;
    void morir();
    void animarMuerte();
    void colocarBomba();
    void manejarExplosion();
private:
    QPixmap quieto, arriba1, arriba2, abajo1, abajo2, derecha1, derecha2, izquierda1, izquierda2, muerte1,
        muerte2, muerte3, muerte4, muerte5, muerte6, muerte7;
    bool usandoSprite1;
    int indiceMuerte;
    Bomb *bombaActual;
};

#endif // PERSONAJE_H
