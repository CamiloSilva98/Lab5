#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene> // Paquete para control de scena
#include <QGraphicsView> // paquete para vistas.
#include "bomb.h"
#include <QTimer>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Constructor
    ~MainWindow(); // destructor
    void crearEnemigos(int cantidadEnemigos);
private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;   // La escena que se va a construir.
    void crearEscena();  // Método para configurar la escena y agregar las paredes
    void crearMurosRompibles();
};
#endif // MAINWINDOW_H
