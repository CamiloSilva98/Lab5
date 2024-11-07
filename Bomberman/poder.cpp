#include "poder.h"

Poder::Poder()
{
    // Cargar la imagen de la puerta
    QPixmap PoderPixmap("power.png");
    setPixmap(PoderPixmap);
}
