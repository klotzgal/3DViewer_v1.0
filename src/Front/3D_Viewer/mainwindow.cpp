#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("3D Viewer");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_rotateX_valueChanged(int value)
{
    ui->Viewer->Rx = value;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_rotateY_valueChanged(int value)
{
    ui->Viewer->Ry = value;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_rotateZ_valueChanged(int value)
{
    ui->Viewer->Rz = value;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_scale_valueChanged(int value)
{
    ui->Viewer->scale = 0.01 * value;
    ui->Viewer->update();
}


void MainWindow::on_radioButton_ortho_clicked()
{
    ui->Viewer->projectionOrtho = true;
    ui->Viewer->update();
}


void MainWindow::on_radioButton_frustum_clicked()
{
    ui->Viewer->projectionOrtho = false;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_point_size_valueChanged(int value)
{
    ui->Viewer->point_size = value;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_line_size_valueChanged(int value)
{
    ui->Viewer->line_size = value;
    ui->Viewer->update();
}

