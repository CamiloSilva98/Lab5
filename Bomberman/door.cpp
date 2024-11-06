#include "door.h"

Door::Door()
{
    // Cargar la imagen de la puerta
    QPixmap doorPixmap("puerta.png");
    setPixmap(doorPixmap);
}

