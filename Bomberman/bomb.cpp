#include "bomb.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
Bomb::Bomb()
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
