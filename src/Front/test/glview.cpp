#include "glview.h"

//data d = {8,
//          {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
//           1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0},
//          12,
//          {1, 7, 5, 1, 3, 7, 1, 4, 3, 1, 2, 4, 3, 8, 7, 3, 4, 8,
//           5, 7, 8, 5, 8, 6, 1, 5, 6, 1, 6, 2, 2, 6, 8, 2, 8, 4}};
data d = {8,
          {0.0, 0.0, 0.0,
           1.0, 0.0, 0.0,
           1.0, 1.0, 0.0,
           0.0, 1.0, 0.0,

           0.0, 0.0, 1.0,
           1.0, 0.0, 1.0,
           1.0, 1.0, 1.0,
           0.0, 1.0, 1.0,},

          24, {1, 2,
               2, 3,
               3, 8,
               1, 8,
               2, 6,
               3, 7,
               6, 7,
               5, 6,
               4, 8,
               4, 5,
               1, 5,
               4, 7
//          1, 6, 1, 7, 1, 8, 1, 9
          }};

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("TheGame");
    setGeometry(400, 200, 800, 600);
    z = 0;
    tmr.start(100);
    connect(&tmr, SIGNAL(timeout()), this, SLOT(changeZ()));

}



//void initializeGL() override;
//void resizeGL(int w, int h) override;
//void paintGL() override;

void glView::initializeGL() {
      initializeOpenGLFunctions();
      glEnable(GL_DEPTH_TEST);
      resize(500, 500);
}

void glView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void glView::paintGL() {
    resize(500, 500);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-1, 1, -1, 1, 2, 1);
    glOrtho(-2, 2, -2, 2, -2, 1);

//    glTranslatef(1, 0, 1);


    glRotatef(90, 0, 0, z);
   glRotatef(-45, 1, 0, 0);
   glRotatef(-45, 0, 1, 0);

    glPointSize(6);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, d.vertexes);

    glColor3f(0, 1, 0);
    glDrawArrays(GL_POINTS, 0, d.vert_count);
    glColor3f(1, 0, 0);

//    glEnable(GL_LINE_STIPPLE);
    glLineWidth(5);
    glDrawElements(GL_LINES, d.surf_count, GL_UNSIGNED_INT, d.surfaces);
    glDisableClientState(GL_VERTEX_ARRAY);

//    glBegin(GL_TRIANGLES);
////        glVertex2d(0, 0);
////        glVertex2d(1, 0);
////        glVertex2d(0, 1);
//        glColor3f(1, 0, 0); glVertex3f(0.8f, 0.0f, 0.0f);
//        glColor3f(0, 1, 0); glVertex3f(0.0f, 0.8f, 0.0f);
//        glColor3f(0, 0, 1); glVertex3f(0.0f, 0.0f, 0.8f);
//    glEnd();
}

void glView::changeZ() {
    z += 0.01;
    update();
}
