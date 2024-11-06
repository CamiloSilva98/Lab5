#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
class Bomb : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bomb();  // Constructor

signals:
    void explotar();  // Señal para la explosión

private slots:
    void detonar();  // Función para detonar la bomba

private:
    QTimer *timer;  // Temporizador para la explosión
};

#endif // BOMB_H

