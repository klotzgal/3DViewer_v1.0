#include "glview.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    parse_obj();
    Rx = 360;
    Ry = 360;
    Rz = 360;
    X = 50;
    Y = 50;
    Z = 50;

    line_size = 5;
    point_size = 6;
    scale = 50;
    projectionOrtho = true;

}

glView::~glView() {
    std::cout << "destructor test" << std::endl;
    if (d.vertex_indices_arr) free(d.vertex_indices_arr);
    if (d.vertices_arr) free(d.vertices_arr);
    std::ofstream out;
    out.open("settings");
    if (out.is_open()){
        std::cout << "file open" << std::endl;
        out << Rx << std::endl;
        out << Ry << std::endl;
        out << Rz << std::endl;
        out.close();
    } else {std::cout << "Not open" << std::endl;
    }
}

void glView::parse_obj()
{

    char filename[] = "/opt/goinfre/klotzgal/skull.obj";
//    char filename[] = "/Users/klotzgal/Desktop/kl/3DViewer_v1.0/src/tmp/IphoneX.obj";
//    char filename[] = "/Users/klotzgal/Desktop/kl/3DViewer_v1.0/src/tmp/rhino_pose1.obj";
//    char filename[] = "/Users/klotzgal/Desktop/kl/3DViewer_v1.0/src/tmp/katana.obj";
    if (d.vertex_indices_arr) free(d.vertex_indices_arr);
    if (d.vertices_arr) free(d.vertices_arr);
    parse_obj_file(filename, &this->d);
    max_vert = -9;
    for (size_t i = 0; i < d.vertices_count * 3; i++) if (abs(d.vertices_arr[i]) > max_vert) max_vert = abs(d.vertices_arr[i]);
    std::cout << max_vert << std::endl;
    update();

}

void glView::initializeGL() {
      initializeOpenGLFunctions();
      glEnable(GL_DEPTH_TEST);
      resize(800, 800);
}

void glView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void glView::paintGL() {
    resize(800, 800);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projectionOrtho) {
        glOrtho(-max_vert, max_vert, -max_vert, max_vert, -2.0 * max_vert, 1000 * max_vert);
    } else {
        glFrustum(-max_vert, max_vert, -max_vert, max_vert, 120 * max_vert , 1000 * max_vert);
        glTranslatef(0, 0, -124 * max_vert );
    }

//    glRotatef(Rx, 1, 0, 0); // поворот на Rx по x
//    glRotatef(Ry, 0, 1, 0); // поворот на Ry по y
//    glRotatef(Rz, 0, 0, 1); // поворот на Rz по z
//    glScalef( 1/max_vert, 1/max_vert, 1/max_vert); // размер

    glPointSize(point_size);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, d.vertices_arr);

    glColor3f(0, 1, 0);
    glDrawArrays(GL_POINTS, 0, d.vertices_count); // точки

    glColor3f(1, 0, 0);
    glLineWidth(line_size);
    glDrawElements(GL_LINES, d.vertex_indices_count * 2, GL_UNSIGNED_INT, d.vertex_indices_arr); // грани
    glDisableClientState(GL_VERTEX_ARRAY);

    if (glGetError()) std::cout << glGetError() << std::endl;

}


