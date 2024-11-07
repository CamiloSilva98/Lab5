#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "breakwall.h"
#include "personaje.h"
#include "door.h"
#include "enemigo.h"
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QColor>
#include <cstdlib>
#include <ctime>
#include <QRandomGenerator>

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
void MainWindow::crearEnemigos(int cantidadEnemigos)
{
    int distanciaSegura = 3 * wallSize;  // Distancia mínima desde el jugador
    QPointF posicionJugador = {wallSize + 1, wallSize + 1};  // Posición inicial del jugador

    int enemigosCreados = 0;

    while (enemigosCreados < cantidadEnemigos) {
        // Genera posiciones aleatorias dentro del mapa
        int fila = QRandomGenerator::global()->bounded(1, rows - 1);
        int columna = QRandomGenerator::global()->bounded(1, cols - 1);
        QPointF posicionEnemigo(columna * wallSize, fila * wallSize);

        // Verifica que la posición esté libre de muros y lejos del jugador
        bool posicionValida = true;

        // Revisa si hay colisiones con muros
        QList<QGraphicsItem*> itemsEnPosicion = scene->items(posicionEnemigo);
        for (QGraphicsItem* item : itemsEnPosicion) {
            if (item->data(0).toString() == "pared") {
                posicionValida = false;
                break;
            }
        }

        // Verifica la distancia con el jugador
        if (posicionValida && QLineF(posicionEnemigo, posicionJugador).length() >= distanciaSegura) {
            // Si la posición es válida, crea y agrega el enemigo
            Enemigo *enemigo = new Enemigo();
            enemigo->setPos(posicionEnemigo);
            enemigo->setData(0, "daño");
            scene->addItem(enemigo);
            enemigosCreados++;

            qDebug() << "Enemigo creado en la posición:" << enemigo->pos();
        }
    }
}

void MainWindow::crearMurosRompibles()
{
    QPixmap breakWallTexture("pared.png");

    int doorRow, doorCol;
    bool posicionValida = false;
    while (!posicionValida) {
        doorRow = QRandomGenerator::global()->bounded(1, rows - 1);
        doorCol = QRandomGenerator::global()->bounded(1, cols - 1);

        // La posición debe estar fuera de las casillas de inicio y en una ubicación donde pueda haber muros rompibles
        if ((doorRow > 2 || doorCol > 2) && (doorRow % 2 != 0 || doorCol % 2 != 0)) {
            posicionValida = true;
        }
    }


    QPointF posicionPuerta(doorCol * wallSize, doorRow * wallSize);
    Door* puerta = new Door();
    puerta->setPos(posicionPuerta);
    scene->addItem(puerta);

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            if (i <= 2 && j <= 2) {
                continue;
            }

            // Coloca un muro rompible solo en posiciones válidas
            if ((i % 2 != 0 || j % 2 != 0)) {
                QPointF position(j * wallSize, i * wallSize);

                // Si esta posición es la misma que la de la puerta, coloca un muro rompible sobre ella
                if (position == posicionPuerta) {
                    BreakWall* muroRompiblePuerta = new BreakWall(breakWallTexture);
                    muroRompiblePuerta->setPos(position);
                    muroRompiblePuerta->setData(0, "pared");
                    muroRompiblePuerta->setData(1, "rompible");
                    //muroRompiblePuerta->setOpacity(0);
                    scene->addItem(muroRompiblePuerta);
                }
                // Para las demás posiciones, agregar muros rompibles de forma aleatoria
                else if (rand() % 4 == 0)
                {
                    BreakWall* breakWall = new BreakWall(breakWallTexture);
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
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            if (i % 2 == 0 && j % 2 == 0) {
                QGraphicsPixmapItem *wall = new QGraphicsPixmapItem(wallTexture);
                wall->setPos(j * wallSize, i * wallSize);
                wall->setData(0, "pared");
                scene->addItem(wall);
            }
        }
    }
    crearMurosRompibles();
    Personaje* personaje = new Personaje();
    personaje->setPos(wallSize + 1, wallSize + 1);
    scene->addItem(personaje);
    crearEnemigos(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}
