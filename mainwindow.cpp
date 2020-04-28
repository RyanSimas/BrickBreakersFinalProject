#include "mainwindow.h"
#include "ui_mainwindow.h"

//This is for drawing the UI tried to mess with adding an intro screen here but couldn't figure it out

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

