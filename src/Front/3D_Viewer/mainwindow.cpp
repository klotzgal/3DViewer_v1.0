#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("3D Viewer");
    ui->horizontalSlider_rotateX->setValue(ui->Viewer->Rx);
    ui->horizontalSlider_rotateY->setValue(ui->Viewer->Ry);
    ui->horizontalSlider_rotateZ->setValue(ui->Viewer->Rz);
    ui->horizontalSlider_moveX->setValue(ui->Viewer->X);
    ui->horizontalSlider_moveY->setValue(ui->Viewer->Z);
    ui->horizontalSlider_moveZ->setValue(ui->Viewer->Z);
    ui->horizontalSlider_scale->setValue(ui->Viewer->scale);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_rotateX_valueChanged(int angle)
{
//    std::cout << "Rx = ";
//    std::cout << angle - ui->Viewer->Rx << std::endl;
    rotate_X(&ui->Viewer->d, (angle - ui->Viewer->Rx) );
    ui->Viewer->Rx = angle;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_rotateY_valueChanged(int angle)
{
//    std::cout << "Ry = ";
//    std::cout << angle - ui->Viewer->Ry << std::endl;
    rotate_Y(&ui->Viewer->d, (angle - ui->Viewer->Ry));
    ui->Viewer->Ry = angle;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_rotateZ_valueChanged(int angle)
{
//    std::cout << "Rz = ";
//    std::cout << angle - ui->Viewer->Rz << std::endl;
    rotate_Z(&ui->Viewer->d, (angle - ui->Viewer->Rz));
    ui->Viewer->Rz = angle;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_scale_valueChanged(int value)
{
    GLdouble s =  (double)value / ui->Viewer->scale;
    std::cout << s << std::endl;

    scale(&ui->Viewer->d, s);
    ui->Viewer->scale = value;
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


void MainWindow::on_horizontalSlider_moveX_valueChanged(int value)
{
    move_X(&ui->Viewer->d, (value - ui->Viewer->X) * ui->Viewer->max_vert / 100) ;
    ui->Viewer->X = value;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_moveY_valueChanged(int value)
{
    move_Y(&ui->Viewer->d, (value - ui->Viewer->Y) * ui->Viewer->max_vert / 100);
    ui->Viewer->Y = value;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_moveZ_valueChanged(int value)
{
    move_Z(&ui->Viewer->d, (value - ui->Viewer->Z) * ui->Viewer->max_vert / 100);
    ui->Viewer->Z = value;
    ui->Viewer->update();
}

