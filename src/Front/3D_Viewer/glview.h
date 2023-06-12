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

// Видео
//#include <gl/GL.H>
//#include <gl/GLU.h>
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "GLU32.lib")

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
    GLfloat max_vert;
    GLint scale;
    bool projectionOrtho;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    ::obj_data d = {};
    void parse_obj();






private:
    glView *viewer;
    Ui::MainWindow *Main;

};


#endif // GLVIEW_H
