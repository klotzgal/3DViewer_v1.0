#ifndef GLVIEW_H
#define GLVIEW_H


//#include <QColorDialog>
//#include <QFileDialog>
//#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>
#include <iostream>
#include <fstream>
//#include <QScrollArea>
#include <QSettings>



extern "C" {
//    #include "../../libs/lib.h"
    #include "../../modules/affine.h"
    #include "../../modules/model_loading.h"
    #include "../../modules/s21_3dviewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class glView : public QOpenGLWidget, protected QOpenGLFunctions
{

private:
    QTimer tmr;
    ~glView() override;


public:
    glView(QWidget *parent = nullptr);
    GLint Rx;
    GLint Ry;
    GLint Rz;
    GLint X;
    GLint Y;
    GLint Z;
    GLfloat line_size;
    GLfloat point_size;
    GLint lineType;
    GLint lineR;
    GLint lineG;
    GLint lineB;
    GLint pointR;
    GLint pointG;
    GLint pointB;
    GLint backR;
    GLint backG;
    GLint backB;
    GLint colorOf;
    GLint pointType;
    GLfloat max_vert;
    GLint scale;
    bool projectionOrtho;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    ::obj_data d = {};
    void parse_obj();
    void take_picture();
    void save_settings();
    void load_settings();

private:
    glView *viewer;
    Ui::MainWindow *Main;
    void printPoints();
    void printLines();
    enum point_type { None, Round, Square };
    enum line_type { Solid, Dotted };
    enum colorise { Line, Point, Back };

    QSettings* settings;

};


#endif // GLVIEW_H
