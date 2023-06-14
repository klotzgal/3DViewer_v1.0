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
    ui->horizontalSlider_colorR->setValue(ui->Viewer->lineR);
    ui->horizontalSlider_colorG->setValue(ui->Viewer->lineG);
    ui->horizontalSlider_colorB->setValue(ui->Viewer->lineB);
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




void MainWindow::on_comboBox_pointType_currentIndexChanged(int index)
{
    ui->Viewer->pointType = index;
    ui->Viewer->update();
}


void MainWindow::on_comboBox_lineType_currentIndexChanged(int index)
{
    ui->Viewer->lineType = index;
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_colorR_valueChanged(int value)
{
    if (ui->Viewer->colorOf == Line) {
        ui->Viewer->lineR = value;
    } else if (ui->Viewer->colorOf == Point) {
        ui->Viewer->pointR = value;
    } else if (ui->Viewer->colorOf == Back) {
        ui->Viewer->backR = value;
    }
    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_colorG_valueChanged(int value)
{
    if (ui->Viewer->colorOf == Line) {
        ui->Viewer->lineG = value;
    } else if (ui->Viewer->colorOf == Point) {
       ui->Viewer->pointG = value;
    } else if (ui->Viewer->colorOf == Back) {
        ui->Viewer->backG = value;
     }

    ui->Viewer->update();
}


void MainWindow::on_horizontalSlider_colorB_valueChanged(int value)
{
    if (ui->Viewer->colorOf == Line) {
        ui->Viewer->lineB = value;
    } else if (ui->Viewer->colorOf == Point) {
        ui->Viewer->pointB = value;
    } else if (ui->Viewer->colorOf == Back) {
        ui->Viewer->backB = value;
    }
    ui->Viewer->update();
}


void MainWindow::on_comboBox_Color_currentIndexChanged(int index)
{
    if (index == Line) {
        ui->Viewer->colorOf = Line;
        std::cout << "line color" << std::endl;
        ui->horizontalSlider_colorR->setValue(ui->Viewer->lineR);
        ui->horizontalSlider_colorG->setValue(ui->Viewer->lineG);
        ui->horizontalSlider_colorB->setValue(ui->Viewer->lineB);

    } else if (index == Point) {
        ui->Viewer->colorOf = Point;
        std::cout << "point color" << std::endl;
        ui->horizontalSlider_colorR->setValue(ui->Viewer->pointR);
        ui->horizontalSlider_colorG->setValue(ui->Viewer->pointG);
        ui->horizontalSlider_colorB->setValue(ui->Viewer->pointB);

    } else if (index == Back) {
        ui->Viewer->colorOf = Back;
        std::cout << "back color" << std::endl;
        ui->horizontalSlider_colorR->setValue(ui->Viewer->backR);
        ui->horizontalSlider_colorG->setValue(ui->Viewer->backG);
        ui->horizontalSlider_colorB->setValue(ui->Viewer->backB);

    }

}

