#include "bomb.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
Bomb::Bomb() : explosionIndex(0)
{
    // Cargar la imagen de la bomba
    if (!QPixmap("bomb.png").isNull()) {
        setPixmap(QPixmap("bomb.png"));
        qDebug() << "Bomba: Imagen cargada correctamente.";
    } else {
        qDebug() << "Error: No se pudo cargar la imagen de la bomba.";
    }

    // Configurar el temporizador para la explosión
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bomb::detonar);

    // Temporizador de 3 segundos antes de la explosión
    timer->start(3000);
    explosionSprites = {
        QPixmap("explosion1.png"),
        QPixmap("explosion2.png"),
        QPixmap("explosion3.png"),
        QPixmap("explosion4.png"),
    };
    explosionTimer = new QTimer(this);
    connect(explosionTimer, &QTimer::timeout, this, &Bomb::animarExplosion);
}

void Bomb::detonar() {
    // Emitir la señal de explosión
    emit explotar();

    explosionIndex = 0;  // Reiniciar el índice
    explosionTimer->start(100);

}
void Bomb::animarExplosion() {
    if (explosionIndex < explosionSprites.size()) {
        // Cambiar al siguiente sprite de explosión
        setPixmap(explosionSprites[explosionIndex]);
        explosionIndex++;
    } else {
        // Detener la animación y eliminar la bomba de la escena
        explosionTimer->stop();
        if (scene()) {
            scene()->removeItem(this);
        }
        // Eliminar la bomba de la escena
        if (scene())
        {
            scene()->removeItem(this);
        }
        delete this;
    }
}
