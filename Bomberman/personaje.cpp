#include "personaje.h"
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsItem>
Personaje::Personaje()
{
    //: usandoSprite1(true)
    // Cargar las dos imágenes del personaje
    sprite1 = QPixmap("PersonajeQ.png");  // Ruta a la primera imagen
    sprite2 = QPixmap("PersonajeD.png");  // Ruta a la segunda imagen

    // Si las imágenes no se cargan correctamente, imprime un mensaje de error
    if (sprite1.isNull() || sprite2.isNull())
    {
        qDebug() << "Error: No se pudo cargar una o ambas imágenes del personaje";
    }
    // Inicialmente mostrar la primera imagen
    setPixmap(sprite1);
    usandoSprite1 = true;  // Empieza usando la primera imagen

    // Hacer que el personaje pueda recibir eventos de teclado
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Personaje::cambiarSprite() {
    // Alternar entre las dos imágenes para simular el movimiento
    if (usandoSprite1) {
        setPixmap(sprite2);
    } else {
        setPixmap(sprite1);
    }
    usandoSprite1 = !usandoSprite1;  // Alternar el estado
}

// Funcion movimiento
// void Personaje::keyPressEvent(QKeyEvent* event) {
//     // Mover el personaje dependiendo de la tecla presionada
//     switch (event->key()) {
//     case Qt::Key_Left:
//         setPos(x() - 10, y());
//         cambiarSprite();  // Cambiar el sprite al moverse
//         break;
//     case Qt::Key_Right:
//         setPos(x() + 10, y());
//         cambiarSprite();  // Cambiar el sprite al moverse
//         break;
//     case Qt::Key_Up:
//         setPos(x(), y() - 10);
//         cambiarSprite();  // Cambiar el sprite al moverse
//         break;
//     case Qt::Key_Down:
//         setPos(x(), y() + 10);
//         cambiarSprite();  // Cambiar el sprite al moverse
//         break;
//     case Qt::Key_Escape:
//         qDebug() << "Se presionó ESC. Cerrando la aplicación...";
//         QApplication::quit();  // Cerrar la aplicación
//     default:
//         break;
//     }
// }

// Funcion para que no se salga de delimitadores.
void Personaje::keyPressEvent(QKeyEvent* event)
{
    int stepSize = 8;  // Tamaño del paso en píxeles, ajustado al tamaño de los bloques

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
            item->setOpacity(1.0); // se hacen visibles las pareced
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
