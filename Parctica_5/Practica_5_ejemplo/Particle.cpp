#include "Particle.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include <QPropertyAnimation>  // Para Animación de Particula.


Particle::Particle(qreal initialX, qreal initialY) : velocity(15.0),minX(0), maxX(800), minY(0), maxY(600),m_color(Qt::blue)
{
    setPos(initialX, initialY);
    setFlag(ItemIsFocusable);//puede recibir inputs de teclado

}

QRectF Particle::boundingRect() const
{
    return QRectF(0, 0, 600, 600); // Ajusta límites visuales
}

void Particle::setColor(const QColor &color) {
    m_color = color;
    update();  // Redibuja la partícula con el nuevo color
}

void Particle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(m_color);
    painter->drawEllipse(10, 10, 20, 20); // Tamaño y ub de la elipse
}

void Particle::moveLeft()
{ // pos()
    setPos(x() - velocity, y());
}

void Particle::moveRight()
{
    setPos(x() + velocity, y());
}

void Particle::moveUp()
{
    setPos(x(), y() - velocity);
}

void Particle::moveDown()
{
    setPos(x(), y() + velocity);
}





void Particle::keyPressEvent(QKeyEvent* event)
{

    setFocus();
    //qreal newX = x();
    //qreal newY = y();
    switch (event->key())
    {
    case Qt::Key_A:
        qDebug() << "Tecla: " << event->key();
        moveLeft();
        break;
    case Qt::Key_D:
        moveRight();

        qDebug() << "Tecla: " << event->key();
        break;
    case Qt::Key_W:
        moveUp();
        setColor(Qt::blue);
        qDebug() << "Tecla: " << event->key();
        break;
    case Qt::Key_S:
        moveDown();
        setColor(Qt::red);
        qDebug() << "Tecla: " << event->key();
        break;

    default:
        break;
    }
    /*if (newX >= minX && newX <= maxX && newY >= minY && newY <= maxY){
        setPos(newX, newY);
        qDebug() << "Current position: " << x() << ", " << y();
        qDebug() << "Boundaries: minX=" << minX << " maxX=" << maxX << " minY=" << minY << " maxY=" << maxY;

    }*/


    scene()->update();

}
