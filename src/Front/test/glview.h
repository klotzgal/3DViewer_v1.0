#ifndef GLVIEW_H
#define GLVIEW_H


//#include <QColorDialog>
//#include <QFileDialog>
//#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>
//#include <QScrollArea>

// Видео
//#include <gl/GL.H>
//#include <gl/GLU.h>
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "GLU32.lib")

extern "C" {
    #include "../../libs/lib.h"
}

class glView : public QOpenGLWidget, protected QOpenGLFunctions
{

private:
    float z;
    QTimer tmr;



public:
    glView(QWidget *parent = nullptr);
    GLfloat Rx;
    GLfloat Ry;
    GLfloat Rz;
    GLfloat line_size;
    GLfloat point_size;
    GLfloat scale;
    bool projectionOrtho;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:
    glView *viewer;
    ::data d = {};

public slots:
    void changeZ();

};


#endif // GLVIEW_H
