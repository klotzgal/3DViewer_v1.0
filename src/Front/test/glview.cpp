#include "glview.h"


//data d = {8,
//          {0.0, 0.0, 0.0,
//           1.0, 0.0, 0.0,
//           1.0, 1.0, 0.0,
//           0.0, 1.0, 0.0,

//           0.0, 0.0, 1.0,
//           1.0, 0.0, 1.0,
//           1.0, 1.0, 1.0,
//           0.0, 1.0, 1.0,},

//          24, {1, 2,
//               2, 3,
//               3, 8,
//               1, 8,
//               2, 6,
//               3, 7,
//               6, 7,
//               5, 6,
//               4, 8,
//               4, 5,
//               1, 5,
//               4, 7
//          }};

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{

//    setGeometry(400, 200, 800, 600);
    z = 0;
    tmr.start(100);
    connect(&tmr, SIGNAL(timeout()), this, SLOT(changeZ()));

    d = {8,
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
              }}; // типа структура из парсера
    Rx = 0;
    Ry = 0;
    Rz = 0;
    line_size = 5;
    point_size = 6;
    scale = 0.5;
    projectionOrtho = true;
}

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
    if (projectionOrtho) {
        glOrtho(-1, 1, -1, 1, -2, 2);
    } else {
        glFrustum(-1, 1, -1, 1, 12, 2);
        glTranslatef(0, 0, -11);
    }




//    glRotatef(90, 0, 0, z);

    glRotatef(Rx, 1, 0, 0); // поворот на Rx по x
    glRotatef(Ry, 0, 1, 0); // поворот на Ry по y
    glRotatef(Rz, 0, 0, 1); // поворот на Rz по z
    glScalef(scale * 0.5, scale * 0.5, scale * 0.5); // размер

    glPointSize(point_size);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, d.vertexes);

    glColor3f(0, 1, 0);
    glDrawArrays(GL_POINTS, 0, d.vert_count); // точки

    glColor3f(1, 0, 0);
    glLineWidth(line_size);
    glDrawElements(GL_LINES, d.surf_count, GL_UNSIGNED_INT, d.surfaces); // грани
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
