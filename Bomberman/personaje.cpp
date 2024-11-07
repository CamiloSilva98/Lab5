#include "personaje.h"
#include "bomb.h"
#include <QGraphicsScene>
#include <QObject>
#include <QDebug>
// Constructor que carga todos los sprites
Personaje::Personaje() : bombaActual(nullptr)
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

    muerte1 = QPixmap("Muerte1.png");
    muerte2 = QPixmap("Muerte2.png");
    muerte3 = QPixmap("Muerte3.png");
    muerte4 = QPixmap("Muerte4.png");
    muerte5 = QPixmap("Muerte5.png");
    muerte6 = QPixmap("Muerte6.png");
    muerte7 = QPixmap("Muerte7.png");

    // Verificar que las imágenes se cargaron correctamente
    if (quieto.isNull() || abajo1.isNull() || abajo2.isNull() || izquierda1.isNull() || izquierda2.isNull()
        || derecha1.isNull() || derecha2.isNull() || arriba1.isNull() || arriba2.isNull() || muerte1.isNull() || muerte2.isNull()
        ||muerte3.isNull() || muerte4.isNull() || muerte5.isNull() || muerte6.isNull() || muerte7.isNull())
    {
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
void Personaje::colocarBomba()
{
    // Asegurarse de que no haya una bomba activa
    if (bombaActual != nullptr) return;

    bombaActual = new Bomb();
    bombaActual->setPos(this->pos()); // Colocar bomba en la posición actual del personaje
    //bombaActual->setData(0, "pared");
    if (scene())
    {
        scene()->addItem(bombaActual);  // Agrega la bomba a la escena
        qDebug() << "Bomba creada en la posición:" << bombaActual->pos();
        connect(bombaActual, &Bomb::explotar, this, &Personaje::manejarExplosion);
    }
    else
    {
        qDebug() << "Error: La escena es nula, no se puede añadir la bomba.";
    }

    // Conectar la señal de explosión de la bomba a manejarExplosion en Personaje
    connect(bombaActual, &Bomb::explotar, this, &Personaje::manejarExplosion);

    qDebug() << "Bomba creada en la posición:" << bombaActual->pos();
}
void Personaje::manejarExplosion()
{
    if (bombaActual == nullptr) return;  // Asegurarse de que la bomba exista

    QPointF bombaPos = bombaActual->pos();
    int explosionRadius = 48; // Radio de explosión

    // Destruir muros rompibles en el área de explosión
    QList<QGraphicsItem*> items = scene()->items();
    for (QGraphicsItem* item : items) {
        // Verificar si el item está en el radio de la explosión
        if (item->data(1).toString() == "rompible" &&
            qAbs(item->x() - bombaPos.x()) <= explosionRadius &&
            qAbs(item->y() - bombaPos.y()) <= explosionRadius)
        {
            morir();
            scene()->removeItem(item);
            delete item;
            bombaActual = nullptr;
        }
    }
}
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
    switch (event->key())
    {
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
    case Qt::Key_X:
        colocarBomba();
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

    // Verificar si colisiona con algún objeto etiquetado como "pared" o "enemigo"
    QList<QGraphicsItem*> colisiones = collidingItems();
    bool colisionConPared = false;

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "pared")
        {
            colisionConPared = true;
            break;
        }
        // Verificar si colisiona con un enemigo
        if (item->data(0).toString() == "daño")
        {
            morir();  // Llama a la función morir si hay colisión con un enemigo
            return;
        }
    }

    // Si hay colisión con una pared, revertir al original
    if (colisionConPared) {
        setPos(pos_original);  // Vuelve a la posición original si hay colisión con una pared
    } else {
        // Si el movimiento fue exitoso, cambia el sprite en función de la dirección
        cambiarSprite(direccion);
    }
}

// Función para manejar la "muerte" del personaje
void Personaje::morir()
{
    // Desactivar las interacciones del personaje
    setEnabled(false);

    // Reiniciar el índice de la animación de muerte
    indiceMuerte = 0;

    // Crear un temporizador para controlar la animación de muerte
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Personaje::animarMuerte);
    timer->start(300); // Cambia el sprite cada 100 ms (ajusta según la velocidad deseada)
}
void Personaje::animarMuerte()
{
    switch (indiceMuerte)
    {
    case 0:
        setPixmap(muerte1);
        break;
    case 1:
        setPixmap(muerte2);
        break;
    case 2:
        setPixmap(muerte3);
        break;
    case 3:
        setPixmap(muerte4);
        break;
    case 4:
        setPixmap(muerte5);
        break;
    case 5:
        setPixmap(muerte6);
        break;
    case 6:
        setPixmap(muerte7);
        break;
    default:
        // Cuando termine la animación, eliminar al personaje de la escena
        scene()->removeItem(this);

        if (QTimer* timer = qobject_cast<QTimer*>(sender())) {
            timer->stop();
            timer->deleteLater();
        }

        // Mostrar un mensaje de "Game Over" o implementar tu lógica de fin de juego
        qDebug() << "Game Over: El personaje ha sido eliminado por un enemigo";
        return;
    }

    // Incrementar el índice para el próximo sprite
    indiceMuerte++;
}
