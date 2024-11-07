#include "bomb.h"
#include <QPixmap>
#include <QGraphicsScene>
Bomb::Bomb()
{
    // Cargar la imagen de la bomba
    setPixmap(QPixmap("bomb.png"));

    // Configurar el temporizador para la explosión
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bomb::detonar);

    // Temporizador de 3 segundos antes de la explosión
    timer->start(3000);
}

void Bomb::detonar() {
    // Emitir la señal de explosión
    emit explotar();

    // Eliminar la bomba de la escena
    if (scene())
    {
        scene()->removeItem(this);
    }
    delete this;
}
