#ifndef PARTICLE_H
#define PARTICLE_H


#include <QGraphicsItem> //crear y manejar 2D
#include <QRectF> //Rectángulo que limita
#include <QPainter> //Pintar o renderizar formas
#include <QKeyEvent> // Librería para monitorear el teclado.

class Particle : public QGraphicsItem
{
    /*Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)*/
public:
    // const m_color;
    void setColor(const QColor &color);
    Particle(qreal initialX, qreal initialY);
    // rectangulo para limpiar
    QRectF boundingRect() const;
    // Función para pintar
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    // Funciones para el movimiento.
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void change_color();

protected:
    void keyPressEvent(QKeyEvent* event); //permite a las clases derivadas que la anulen y manejen eventos de teclado de manera personalizada

private:
    // Atributos privamos sobre velocidad. Y Rectangulo delimitador.
    qreal velocity;
    qreal minX;
    qreal maxX;
    qreal minY;
    qreal maxY;
    QColor m_color;
};

#endif // PARTICLE_H
