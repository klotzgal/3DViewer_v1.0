#include "glview.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{

//    setGeometry(400, 200, 800, 600);

////    d = {8,
////              {0.0, 0.0, 0.0,
////               1.0, 0.0, 0.0,
////               1.0, 1.0, 0.0,
////               0.0, 1.0, 0.0,

////               0.0, 0.0, 1.0,
////               1.0, 0.0, 1.0,
////               1.0, 1.0, 1.0,
////               0.0, 1.0, 1.0,},

////              24, {1, 2,
////                   2, 3,
////                   3, 8,
////                   1, 8,
////                   2, 6,
////                   3, 7,
////                   6, 7,
////                   5, 6,
////                   4, 8,
////                   4, 5,
////                   1, 5,
////                   4, 7
////              }}; // типа структура из парсера
//    d = {8,
//              {0.0, 0.0, 0.0,
//               0.0, 0.0, 1.0,
//               0.0, 1.0, 0.0,
//               0.0, 1.0, 1.0,
//               1.0, 0.0, 1.0,
//               1.0, 0.0, 1.0,
//               1.0, 1.0, 0.0,
//               1.0, 1.0, 1.0,},

//              36, {1, 7, 5,
//                   1, 3, 7,
//                   1, 4, 3,
//                   1, 2, 4,
//                   3, 8, 7,
//                   3, 4, 8,
//                   5, 7, 8,
//                   5, 8, 6,
//                   1, 5, 6,
//                   1, 6, 2,
//                   2, 6, 8,
//                   2, 8, 4
//              }};
    char file_name[] = "/opt/goinfre/*/skull.obj";
    parse_obj_file(file_name, &d);
    std::cout << d.vertices_arr << std::endl;
    Rx = 0;
    Ry = 0;
    Rz = 0;
    line_size = 5;
    point_size = 6;
    scale = 0.5;
    projectionOrtho = true;
}

glView::~glView() {
    std::cout << "destructor test" << std::endl;
    if (d.vertex_indices_arr) free(d.vertex_indices_arr);
    if (d.vertices_arr) free(d.vertices_arr);
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






    glRotatef(Rx, 1, 0, 0); // поворот на Rx по x
    glRotatef(Ry, 0, 1, 0); // поворот на Ry по y
    glRotatef(Rz, 0, 0, 1); // поворот на Rz по z
    glScalef(scale * 0.5, scale * 0.5, scale * 0.5); // размер

    glPointSize(point_size);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, d.vertices_arr);

    glColor3f(0, 1, 0);
    glDrawArrays(GL_POINTS, 0, d.vertices_count); // точки

    glColor3f(1, 0, 0);
    glLineWidth(line_size);
    glDrawElements(GL_LINES, d.vertex_indices_count, GL_UNSIGNED_INT, d.vertex_indices_arr); // грани
    glDisableClientState(GL_VERTEX_ARRAY);

    if (glGetError()){
        std::cout << glGetError() << std::endl;
    }
}


