#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QKeyEvent>

#include "Particle.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crear la ventana
    QGraphicsView view;
    view.setRenderHint(QPainter::Antialiasing);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Crear una escena para manejar elementos gráficos
    QGraphicsScene scene;
    view.setScene(&scene);


    Particle particle(100,100);
    //Particle particle("C:/Users/Jaime Vergara Tejada/Documents/p5-1/rf.png");
    scene.addItem(&particle);

    // Set the main window properties
    view.setWindowTitle("Movimiento por teclado");
    view.setRenderHint(QPainter::Antialiasing);
    view.show();

    return app.exec();
}
