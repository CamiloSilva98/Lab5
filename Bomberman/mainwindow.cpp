#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QColor>
#include <cstdlib>
#include <ctime>

int wallSize = 16;
int rows = 13;
int cols = 31;
int winX = wallSize * cols;
int winY = wallSize * rows;
//srand(static_cast<unsigned int>(time(nullptr)));
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(winX+50, winY+50);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, winX, winY);

    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setFixedSize(winX + 5, winY + 5);
    view->setBackgroundBrush(QBrush(QColor("#009400")));
    setCentralWidget(view);

    QPixmap wallTexture("muros.png");
    QBrush wallBrush(wallTexture);
    wallBrush.setStyle(Qt::TexturePattern);

    // Muros del borde
    QGraphicsRectItem *topWall = new QGraphicsRectItem(0, 0, winX, wallSize);
    topWall->setBrush(wallBrush);
    scene->addItem(topWall);

    QGraphicsRectItem *bottomWall = new QGraphicsRectItem(0, winY-wallSize, winX, wallSize);
    bottomWall->setBrush(wallBrush);
    scene->addItem(bottomWall);

    QGraphicsRectItem *leftWall = new QGraphicsRectItem(0, 0, wallSize, winY);
    leftWall->setBrush(wallBrush);
    scene->addItem(leftWall);

    QGraphicsRectItem *rightWall = new QGraphicsRectItem(winX-wallSize, 0, wallSize, winY);
    rightWall->setBrush(wallBrush);
    scene->addItem(rightWall);

    // Generar muros internos en patrón alternado
    for (int i = 1; i < rows - 1; ++i)
    {       // Evitar las filas de los bordes
        for (int j = 1; j < cols - 1; ++j)
        {   // Evitar las columnas de los bordes
            if ((i % 2 == 0) && (j % 2 == 0))
            {  // Patrón alternado
                QGraphicsPixmapItem *wall = new QGraphicsPixmapItem(wallTexture);
                wall->setPos(j * wallSize, i * wallSize);
                scene->addItem(wall);
            }
        }
    }
}

//QPixmap breakableWallTexture("pared.png");
//
//// Generar muros rompibles aleatoriamente en los espacios libres
//for (int i = 1; i < rows - 1; ++i)
//{
//    for (int j = 1; j < cols - 1; ++j)
//    {
//        // Saltar posiciones con muros sólidos o de inicio del jugador
//        if ((i % 2 == 0) && (j % 2 == 0)) continue;
//        if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0)) continue;
//
//        // Colocar muro rompible con probabilidad de 50%
//        if (rand() % 2 == 0)
//        {  // Cambia el 2 por un número mayor para menos muros
//            QGraphicsPixmapItem *breakableWall = new QGraphicsPixmapItem(breakableWallTexture);
//            breakableWall->setPos(j * wallSize, i * wallSize);
//            scene->addItem(breakableWall);
//        }
//    }
//}
MainWindow::~MainWindow() {
    delete ui;
}
