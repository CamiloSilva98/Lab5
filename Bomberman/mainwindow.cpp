#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "breakwall.h"
#include "personaje.h"
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

    scene = new QGraphicsScene(this);
    crearEscena();

    scene->setSceneRect(0, 0, winX, winY);

    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setFixedSize(winX + 5, winY + 5);
    view->setBackgroundBrush(QBrush(QColor("#009400")));
    setCentralWidget(view);
}
void MainWindow::crearMurosRompibles()
{
    QPixmap breakWallTexture("pared.png");

    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {
            // Evitar las primeras casillas donde empieza el personaje
            if ((i <= 2 && j <= 2))
            {
                continue;
            }

            // Colocar muro rompible en posiciones que no sean de la malla de muros indestructibles
            if ((i % 2 != 0 || j % 2 != 0))
            {
                // Verificar si ya hay un muro indestructible en esta posición
                QPointF position(j * wallSize, i * wallSize);
                QList<QGraphicsItem*> itemsEnPosicion = scene->items(position);

                bool posicionOcupada = false;
                for (QGraphicsItem* item : itemsEnPosicion)
                {
                    if (item->data(0).toString() == "pared" && item->data(1).toString() == "indestructible") {
                        posicionOcupada = true;
                        break;
                    }
                }

                // Si la posición está libre, agregar un muro rompible
                if (!posicionOcupada && (rand() % 4 == 0))
                {
                    BreakWall *breakWall = new BreakWall(breakWallTexture);
                    breakWall->setPos(position);
                    breakWall->setData(0, "pared");
                    breakWall->setData(1, "rompible");
                    scene->addItem(breakWall);
                }
            }
        }
    }
}

    void MainWindow::crearEscena()
    {
        scene->setSceneRect(0, 0, winX, winY);

        QPixmap wallTexture("muros.png");
        QBrush wallBrush(wallTexture);
        wallBrush.setStyle(Qt::TexturePattern);

        // Muros del borde
        QGraphicsRectItem *topWall = new QGraphicsRectItem(0, 0, winX, wallSize);
        topWall->setData(0, "pared");
        topWall->setBrush(wallBrush);
        scene->addItem(topWall);

        QGraphicsRectItem *bottomWall = new QGraphicsRectItem(0, winY - wallSize, winX, wallSize);
        bottomWall->setData(0, "pared");
        bottomWall->setBrush(wallBrush);
        scene->addItem(bottomWall);

        QGraphicsRectItem *leftWall = new QGraphicsRectItem(0, 0, wallSize, winY);
        leftWall->setData(0, "pared");
        leftWall->setBrush(wallBrush);
        scene->addItem(leftWall);

        QGraphicsRectItem *rightWall = new QGraphicsRectItem(winX - wallSize, 0, wallSize, winY);
        rightWall->setData(0, "pared");
        rightWall->setBrush(wallBrush);
        scene->addItem(rightWall);

        // Generar muros internos en patrón alternado
        for (int i = 1; i < rows - 1; ++i)
        { // Evitar las filas de los bordes
            for (int j = 1; j < cols - 1; ++j)
            { // Evitar las columnas de los bordes
                if ((i % 2 == 0) && (j % 2 == 0))
                { // Patrón alternado
                    QGraphicsPixmapItem *wall = new QGraphicsPixmapItem(wallTexture);
                    wall->setPos(j * wallSize, i * wallSize);
                    wall->setData(0, "pared");
                    scene->addItem(wall);
                }
            }
        }
    //crearMurosRompibles();
    Personaje* personaje = new Personaje();
    personaje->setPos(wallSize+1, wallSize+1 );
    scene->addItem(personaje);
    }

MainWindow::~MainWindow()
{
    delete ui;
}
