#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glview.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_rotateX_valueChanged(int angle);

    void on_horizontalSlider_rotateY_valueChanged(int angle);

    void on_horizontalSlider_rotateZ_valueChanged(int angle);

    void on_horizontalSlider_scale_valueChanged(int value);

    void on_radioButton_ortho_clicked();

    void on_radioButton_frustum_clicked();

    void on_horizontalSlider_point_size_valueChanged(int value);

    void on_horizontalSlider_line_size_valueChanged(int value);

    void on_horizontalSlider_moveX_valueChanged(int value);

    void on_horizontalSlider_moveY_valueChanged(int value);

    void on_horizontalSlider_moveZ_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
