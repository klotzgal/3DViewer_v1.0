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
    enum colorise { Line, Point, Back };

private slots:
    void on_horizontalSlider_rotateX_valueChanged(int angle);

    void on_horizontalSlider_rotateY_valueChanged(int angle);

    void on_horizontalSlider_rotateZ_valueChanged(int angle);

    void on_horizontalSlider_scale_valueChanged(int value);

    void on_comboBox_projection_currentIndexChanged(int index);

    void on_horizontalSlider_point_size_valueChanged(int value);

    void on_horizontalSlider_line_size_valueChanged(int value);

    void on_horizontalSlider_moveX_valueChanged(int value);

    void on_horizontalSlider_moveY_valueChanged(int value);

    void on_horizontalSlider_moveZ_valueChanged(int value);

    void on_comboBox_pointType_currentIndexChanged(int index);

    void on_comboBox_lineType_currentIndexChanged(int index);

    void on_horizontalSlider_colorR_valueChanged(int value);

    void on_horizontalSlider_colorG_valueChanged(int value);

    void on_horizontalSlider_colorB_valueChanged(int value);

    void on_pushButton_foto_clicked();

    void on_pushButton_gif_clicked();



    void on_radioButton_line_color_clicked();

    void on_radioButton_point_color_clicked();

    void on_radioButton_back_color_clicked();

    void on_pushButton_open_obj_clicked();

private:
    Ui::MainWindow *ui;
    glView *vi;

};
#endif // MAINWINDOW_H
