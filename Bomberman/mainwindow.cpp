#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "breakwall.h"
#include <QPixmap>
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(winX + 50, winY + 50);

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

    QGraphicsRectItem *bottomWall = new QGraphicsRectItem(0, winY - wallSize, winX, wallSize);
    bottomWall->setBrush(wallBrush);
    scene->addItem(bottomWall);

    QGraphicsRectItem *leftWall = new QGraphicsRectItem(0, 0, wallSize, winY);
    leftWall->setBrush(wallBrush);
    scene->addItem(leftWall);

    QGraphicsRectItem *rightWall = new QGraphicsRectItem(winX - wallSize, 0, wallSize, winY);
    rightWall->setBrush(wallBrush);
    scene->addItem(rightWall);

    // Generar muros internos en patrón alternado
    for (int i = 1; i < rows - 1; ++i)
    {   // Evitar las filas de los bordes
        for (int j = 1; j < cols - 1; ++j)
        {   // Evitar las columnas de los bordes
            if ((i % 2 == 0) && (j % 2 == 0))
            {   // Patrón alternado
                QGraphicsPixmapItem *wall = new QGraphicsPixmapItem(wallTexture);
                wall->setPos(j * wallSize, i * wallSize);
                scene->addItem(wall);
            }
        }
    }

    // Inicializar la semilla para la aleatoriedad
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generar muros rompibles aleatorios
    QPixmap breakWallTexture("pared.png");
    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {
            if (!(i <= 1 && j <= 2) && (rand() % 4 == 0))
            {   // Evitar las primeras 3 casillas y agregar aleatoriamente
                BreakWall *breakWall = new BreakWall(breakWallTexture);
                breakWall->setPos(j * wallSize, i * wallSize);
                scene->addItem(breakWall);
            }
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
