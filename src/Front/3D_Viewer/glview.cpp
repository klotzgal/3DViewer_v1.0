#include "glview.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    parse_obj();
    settings = new QSettings("XXX", "3D_Viewer", this);
    load_settings();
    Rx = 360;
    Ry = 360;
    Rz = 360;
    X = 50;
    Y = 50;
    Z = 50;

//    line_size = 5;
//    lineR = 100;
//    lineG = 0;
//    lineB = 0;
//    pointR = 0;
//    pointG = 100;
//    pointB = 0;
//    backR = 0;
//    backG = 0;
//    backB = 0;
//    point_size = 6;
    scale = 20;

//    colorOf = Line;
//    projectionOrtho = true;
//    pointType = Square;
//    lineType = Solid;

}

glView::~glView() {
    std::cout << "destructor test" << std::endl;
    save_settings();
    if (d.vertex_indices_arr) free(d.vertex_indices_arr);
    if (d.vertices_arr) free(d.vertices_arr);
    std::ofstream out;
    out.open("settings");
    if (out.is_open()){
        std::cout << out.is_open();
        std::cout << "file open" << std::endl;
        out << Rx << std::endl;
        out << Ry << std::endl;
        out << Rz << std::endl;
        out.close();
    } else {
        std::cout << "Not open" << std::endl;
    }
}

void glView::parse_obj()
{
    char filename[] = "/Users/klotzgal/Desktop/kl/3DViewer_v1.0/src/tmp/skull.obj";
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
    glClearColor(backR * 0.01, backG * 0.01, backB * 0.01, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projectionOrtho) {
        glOrtho(-max_vert * 1.2, max_vert * 1.2, -max_vert * 1.2, max_vert * 1.2, -2.0 * max_vert, 1000 * max_vert);
    } else {
        glFrustum(-max_vert * 1.2, max_vert * 1.2, -max_vert * 1.2, max_vert * 1.2, 120 * max_vert , 1000 * max_vert);
        glTranslatef(0, 0, -124 * max_vert );
    }

//    glRotatef(Rx, 1, 0, 0); // поворот на Rx по x
//    glRotatef(Ry, 0, 1, 0); // поворот на Ry по y
//    glRotatef(Rz, 0, 0, 1); // поворот на Rz по z
//    glScalef( 1/max_vert, 1/max_vert, 1/max_vert); // размер
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, d.vertices_arr);
    if (pointType != None) {
        printPoints();
    }
    printLines();
    glDisableClientState(GL_VERTEX_ARRAY);

//    if (glGetError()) std::cout << glGetError() << std::endl;

}


void glView::printPoints() {
    if (pointType == Round) glEnable(GL_POINT_SMOOTH);
    glPointSize(point_size);
    glColor3f(pointR * 0.01, pointG * 0.01, pointB * 0.01);
    glDrawArrays(GL_POINTS, 0, d.vertices_count); // точки
    if (pointType == Round) glDisable(GL_POINT_SMOOTH);
}

void glView::printLines(){
    if (lineType == Dotted) {
        glEnable(GL_LINE_STIPPLE);
//        glLineStipple(1, 0x3333);
        glLineStipple(3, 0x00FF);
    }

    glLineWidth(line_size);
    glColor3f(lineR * 0.01, lineG * 0.01, lineB * 0.01);
    glDrawElements(GL_LINES, d.vertex_indices_count * 2, GL_UNSIGNED_INT, d.vertex_indices_arr); // грани
    if (lineType == Dotted) glDisable(GL_LINE_STIPPLE);
}


void glView::take_picture() {
    QImage image = QOpenGLWidget::grabFramebuffer();
    image.save("../../../foto", "jpeg");
    std::cout << "picture" << std::endl;
}

void glView::save_settings()
{
//    settings->setValue("lineType", lineType);

    settings->beginGroup("Color");
    settings->setValue("lineR", lineR);
    settings->setValue("lineG", lineG);
    settings->setValue("lineB", lineB);
    settings->setValue("pointR", pointR);
    settings->setValue("pointG", pointG);
    settings->setValue("pointB", pointB);
    settings->setValue("backR", backR);
    settings->setValue("backG", backG);
    settings->setValue("backB", backB);
    settings->endGroup();
    settings->beginGroup("Size");
    settings->setValue("line_size", line_size);
    settings->setValue("point_size", point_size);
//    settings->setValue("scale", scale);
    settings->endGroup();
    settings->beginGroup("Other");
    settings->setValue("colorOf", colorOf);
    settings->setValue("projectionOrtho", projectionOrtho);
    settings->setValue("pointType", pointType);
    settings->setValue("lineType", lineType);
    settings->endGroup();
};

void glView::load_settings()
{
//    std::cout << "lineType settings " << settings->value("lineType", Solid).toInt() << std::endl;
//    lineType = settings->value("lineType", Solid).toInt();

    settings->beginGroup("Color");
    lineR = settings->value("lineR", 100 ).toInt();
    lineG = settings->value("lineG", 0 ).toInt();
    lineB = settings->value("lineB", 0 ).toInt();
    pointR = settings->value("pointR", 0 ).toInt();
    pointG = settings->value("pointG", 100 ).toInt();
    pointB = settings->value("pointB", 0 ).toInt();
    backR = settings->value("backR", 0 ).toInt();
    backG = settings->value("backG", 0 ).toInt();
    backB = settings->value("backB", 0 ).toInt();
    settings->endGroup();
    settings->beginGroup("Size");
    line_size = settings->value("line_size", 5.0f).toFloat();
    point_size = settings->value("line_size", 6.0f).toFloat();
//    scale = settings->value("scale", 50).toFloat();
    settings->endGroup();
    settings->beginGroup("Other");
    colorOf = settings->value("colorOf", Line).toInt();
    projectionOrtho = settings->value("projectionOrtho", true).toInt();
    pointType = settings->value("pointType", Square).toInt();
    lineType = settings->value("lineType", Solid).toInt();
    settings->endGroup();
}


















