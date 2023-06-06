#include "glview.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("TheGame");
    setGeometry(400, 200, 800, 600);
    z = 0;
    connect(&tmr, SIGNAL(timeout()), this, SLOT(changeZ()));
    tmr.start(10);
}



//void initializeGL() override;
//void resizeGL(int w, int h) override;
//void paintGL() override;

void glView::initializeGL() {
      initializeOpenGLFunctions();
      glEnable(GL_DEPTH_TEST);
      glLoadIdentity();
//      glMatrixMode(GL_PROJECTION);
//      resize(700, 700);

}

void glView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-1, 1, -1, 1, 0, 2);
    glFrustum(-1, 1, -1, 1, 1, 2);
}

void glView::paintGL() {
    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(90, 0, 0, 1);
    glTranslatef(0, 0, z);
    glBegin(GL_TRIANGLES);
    glColor3d(1, 0, 0);
//        glVertex2d(0, 0);
//        glVertex2d(1, 0);
//        glVertex2d(0, 1);
        glVertex3d(0, 0, -1.5);
        glVertex3d(1, 0, -1.5);
        glVertex3d(0, 1, -1.5);
    glEnd();
}

void glView::changeZ() {
    z += 0.01;
    update();
}
