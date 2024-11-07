#include "bomb.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>

Bomb::Bomb() : explosionIndex(0)
{
    // Cargar la imagen de la bomba
    QPixmap bombImage("bomb.png");
    if (!bombImage.isNull()) {
        setPixmap(bombImage);
        qDebug() << "Bomba: Imagen cargada correctamente.";
    } else {
        qDebug() << "Error: No se pudo cargar la imagen de la bomba.";
    }

    // Configurar el temporizador para la explosión
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bomb::detonar);

    // Temporizador de 3 segundos antes de la explosión
    timer->start(2800);

    // Cargar los sprites de la animación de explosión
    explosionSprites = {
        QPixmap("explosion1.png"),
        QPixmap("explosion2.png"),
        QPixmap("explosion3.png"),
        QPixmap("explosion4.png"),
    };

    // Configurar el temporizador para la animación de explosión (sin iniciarlo aún)
    explosionTimer = new QTimer(this);
    connect(explosionTimer, &QTimer::timeout, this, &Bomb::animarExplosion);
}

void Bomb::detonar() {
    // Emitir la señal de explosión
    emit explotar();
    explosionCenter = pos();
    // Ajustar la posición una vez para centrar la animación de explosión
    int offsetX = -16;
    int offsetY = -16;
    setPos(explosionCenter.x() + offsetX, explosionCenter.y() + offsetY);

    // Iniciar la animación de la explosión
    explosionIndex = 0;
    explosionTimer->start(100);  // Cambia de sprite cada 100 ms
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
        delete this;
    }
}
