#include "personaje.h"
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsItem>
Personaje::Personaje()
{
    sprite1 = QPixmap("PersonajeQ.png");
    abajo1 = QPixmap("PersonajeD.png");
    abajo2 = QPixmap("PersonajeDD.png");
    izquierda1 = QPixmap("PersonajeL.png");
    izquierda2= QPixmap("PersonajeLL.png");
    derecha1= QPixmap("PersonajeR.png");
    derecha2 = QPixmap("PersonajeRR.png");
    arriba1 = QPixmap("PersonajeU.png");
    arriba2 = QPixmap("PersonajeUU.png");
    // Si las imágenes no se cargan correctamente, imprime un mensaje de error
    if (sprite1.isNull() || abajo1.isNull())
    {
        qDebug() << "Error: No se pudo cargar una o ambas imágenes del personaje";
    }
    // Inicialmente mostrar la primera imagen
    setPixmap(sprite1);
    usandoSprite1 = true;  // Empieza usando la primera imagen
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    // Hacer que el personaje pueda recibir eventos de teclado
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}
QRectF Personaje::boundingRect() const
{
    return QRectF(1, 1, pixmap().width() - 2, pixmap().height() - 2);
}
void Personaje::cambiarSprite()
    {
    // Alternar entre las dos imágenes para simular el movimiento
    if (usandoSprite1) {
        setPixmap(abajo1);
    } else {
        setPixmap(sprite1);
    }
    usandoSprite1 = !usandoSprite1;  // Alternar el estado
}

void Personaje::keyPressEvent(QKeyEvent* event)
{
    int stepSize = 4;  // Tamaño del paso en píxeles
    // Guardar la posición actual del personaje
    QPointF nuevaPos = pos();
    QPointF pos_original = nuevaPos;

    // Verificar qué tecla se presionó y calcular la nueva posición
    switch (event->key())
    {
    case Qt::Key_Left:
        nuevaPos.setX(nuevaPos.x() - stepSize);
        break;
    case Qt::Key_Right:
        nuevaPos.setX(nuevaPos.x() + stepSize);
        break;
    case Qt::Key_Up:
        nuevaPos.setY(nuevaPos.y() - stepSize);
        break;
    case Qt::Key_Down:
        nuevaPos.setY(nuevaPos.y() + stepSize);
        break;
    case Qt::Key_Escape:
        qDebug() << "Se presionó ESC. Cerrando la aplicación...";
        QApplication::quit();
        return;
    default:
        return;
    }

    // Mover temporalmente el personaje a la nueva posición para verificar colisiones
    setPos(nuevaPos);

    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    bool colisionConPared = false;

    for (QGraphicsItem* item : colisiones)
    {
        if (item->data(0).toString() == "pared")
        {
            colisionConPared = true;
            break;
        }
    }

    // Si colisiona con una pared, revertir el movimiento
    if (colisionConPared)
    {
        qDebug() << "Colisión detectada con una pared";
        setPos(pos_original);  // Revertir el movimiento

    }
    else
    {
        // No hay colisión, permitir el movimiento
        cambiarSprite();
    }
}
