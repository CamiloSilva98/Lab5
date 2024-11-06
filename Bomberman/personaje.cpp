#include "personaje.h"

// Constructor que carga todos los sprites
Personaje::Personaje()
{
    quieto = QPixmap("PersonajeQ.png");
    abajo1 = QPixmap("PersonajeD.png");
    abajo2 = QPixmap("PersonajeDD.png");
    izquierda1 = QPixmap("PersonajeL.png");
    izquierda2 = QPixmap("PersonajeLL.png");
    derecha1 = QPixmap("PersonajeR.png");
    derecha2 = QPixmap("PersonajeRR.png");
    arriba1 = QPixmap("PersonajeU.png");
    arriba2 = QPixmap("PersonajeUU.png");

    // Verificar que las imágenes se cargaron correctamente
    if (quieto.isNull() || abajo1.isNull() || abajo2.isNull() || izquierda1.isNull() || izquierda2.isNull()
        || derecha1.isNull() || derecha2.isNull() || arriba1.isNull() || arriba2.isNull()) {
        qDebug() << "Error: No se pudo cargar una o más imágenes del personaje";
    }

    // Configuración inicial
    setPixmap(quieto);  // Comienza con el sprite quieto
    usandoSprite1 = true;

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

QRectF Personaje::boundingRect() const
{
    return QRectF(1, 1, pixmap().width() - 2, pixmap().height() - 2);
}

// Cambia el sprite del personaje dependiendo de la dirección
void Personaje::cambiarSprite(const QString& direccion)
{
    if (direccion == "abajo") {
        setPixmap(usandoSprite1 ? abajo1 : abajo2);
    } else if (direccion == "arriba") {
        setPixmap(usandoSprite1 ? arriba1 : arriba2);
    } else if (direccion == "izquierda") {
        setPixmap(usandoSprite1 ? izquierda1 : izquierda2);
    } else if (direccion == "derecha") {
        setPixmap(usandoSprite1 ? derecha1 : derecha2);
    } else {
        setPixmap(quieto);  // Sprite en estado quieto si no hay movimiento
    }
    usandoSprite1 = !usandoSprite1;
}

void Personaje::keyPressEvent(QKeyEvent* event)
{
    int stepSize = 4;  // Tamaño del paso en píxeles
    QPointF pos_original = pos();  // Guardar la posición original
    QPointF nuevaPos = pos_original;  // Nueva posición a la que intentará moverse
    QString direccion;

    // Determinar la dirección y calcular la nueva posición
    switch (event->key()) {
    case Qt::Key_Left:
        nuevaPos.setX(nuevaPos.x() - stepSize);
        direccion = "izquierda";
        break;
    case Qt::Key_Right:
        nuevaPos.setX(nuevaPos.x() + stepSize);
        direccion = "derecha";
        break;
    case Qt::Key_Up:
        nuevaPos.setY(nuevaPos.y() - stepSize);
        direccion = "arriba";
        break;
    case Qt::Key_Down:
        nuevaPos.setY(nuevaPos.y() + stepSize);
        direccion = "abajo";
        break;
    case Qt::Key_Escape:
        QApplication::quit();
        return;
    default:
        direccion = "";  // No hay dirección si no es una tecla de movimiento
        return;
    }

    // Mueve temporalmente el personaje a la nueva posición
    setPos(nuevaPos);

    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    bool colisionConPared = false;

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "pared") {
            colisionConPared = true;
            break;
        }
    }

    // Si hay colisión, revertir al original
    if (colisionConPared) {
        setPos(pos_original);  // Vuelve a la posición original si hay colisión
    } else {
        // Si el movimiento fue exitoso, cambia el sprite en función de la dirección
        cambiarSprite(direccion);
    }
}
