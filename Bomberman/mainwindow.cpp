#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) // Inicialización de ui
{
    ui->setupUi(this);  // Configuración de la interfaz de usuario

    resize(800, 600);  // Tamaño de la ventana

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 600, 400);  // Tamaño del escenario

    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setFixedSize(620, 420);  // Tamaño de la vista (ligeramente más grande que la escena)
    view->setBackgroundBrush(QBrush(QColor("#009400")));
    setCentralWidget(view);  // Agregar la vista a la ventana principal
}

MainWindow::~MainWindow() {
    delete ui;  // Liberar la memoria de ui
}

