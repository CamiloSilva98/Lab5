#ifndef BREAKWALL_H
#define BREAKWALL_H

#include <QGraphicsPixmapItem>

class BreakWall : public QGraphicsPixmapItem {
public:
    BreakWall(QPixmap &texture, QGraphicsItem *parent = nullptr);
};

#endif // BREAKWALL_H
