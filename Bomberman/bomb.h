#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Bomb : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bomb();  // Constructor

signals:
    void explotar();  // Señal para la explosión

private slots:
    void detonar();  // Función para detonar la bomba
    void animarExplosion();

private:
    QTimer *timer;  // Temporizador para la explosión
    QTimer *explosionTimer;  // Temporizador para animar la explosión
    QVector<QPixmap> explosionSprites;  // Sprites de la explosión
    int explosionIndex;
};

#endif // BOMB_H

