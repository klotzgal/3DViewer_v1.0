#include "glview.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    filename = "/Users/klotzgal/Desktop/kl/3DViewer_v1.0/src/tmp/skull.obj";
    parse_obj(filename);
    settings = new QSettings("XXX", "3D_Viewer", this);
    load_settings();
    Rx = 360;
    Ry = 360;
    Rz = 360;
    X = 50;
    Y = 50;
    Z = 50;
    scale = 20;
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
    colorOf = Line;
//    projectionOrtho = true;
//    pointType = Square;
//    lineType = Solid;

}

glView::~glView() {
    std::cout << "destructor test\n";
    save_settings();
    delete settings;
    if (d.vertex_indices_arr) free(d.vertex_indices_arr);
    if (d.vertices_arr) free(d.vertices_arr);
}


void glView::parse_obj(QString fileName)
{
    filename = fileName;
    QByteArray array = fileName.toLocal8Bit();
    char* file_name = array.data();

    if (d.vertex_indices_arr) free(d.vertex_indices_arr);
    if (d.vertices_arr) free(d.vertices_arr);
    this->d.vertex_indices_count = 0;
    this->d.vertices_count = 0;
    parse_obj_file(file_name, &this->d);
    // определение модуля максимальной координаты для задания размера
    max_vert = -9;
    for (size_t i = 0; i < d.vertices_count * 3; i++) if (abs(d.vertices_arr[i]) > max_vert) max_vert = abs(d.vertices_arr[i]);
    update();
}

void glView::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    resize(this->width(), this->height());
}

void glView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void glView::paintGL() {
    resize(this->width(), this->height());
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

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, d.vertices_arr);
    if (pointType != None) {
        printPoints();
    }
    printLines();
    glDisableClientState(GL_VERTEX_ARRAY);
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
        glLineStipple(3, 0x00FF);
    }
    glLineWidth(line_size);
    glColor3f(lineR * 0.01, lineG * 0.01, lineB * 0.01);
    glDrawElements(GL_LINES, d.vertex_indices_count * 2, GL_UNSIGNED_INT, d.vertex_indices_arr); // грани
    if (lineType == Dotted) glDisable(GL_LINE_STIPPLE);
}


void glView::mousePressEvent(QMouseEvent *mo)
{
    mPos = mo->pos();
}

void glView::mouseMoveEvent(QMouseEvent *mo)
{
    xRot = 2 / M_PI * (mPos.y() - mo->pos().y());
    yRot = 2 / M_PI * (mo->pos().x() - mPos.x());

    rotate_X(&d, xRot);
    rotate_Y(&d, yRot);
    mPos = mo->pos();
    update();
}



void glView::save_picture() {
    QImage image = QOpenGLWidget::grabFramebuffer();
    filename = QFileDialog::getSaveFileName(this, tr("Screenshot JPEG"), QDir::home().path(),
                                            tr("JPEG files (*.jpeg)"));
    image.save(filename, "jpeg");
}


void glView::init_gif() {
    gif = new QGifImage();
    gif->setDefaultDelay(100);
    time = 0;
    timer = new QTimer(this);
    timer->start(100);
    connect(timer, &QTimer::timeout, this, &glView::make_gif);
}


void glView::make_gif() {
    if (time < 50) {
        //добавление фрейма
        QImage image = QOpenGLWidget::grabFramebuffer();
        gif->addFrame(image, -1);
        time++;
    } else {
        // сохранение
        timer->stop();
        filename = QFileDialog::getSaveFileName(this, tr("Save GIF"), QDir::home().path(),
                                                tr("GIF files (*.gif)"));
        gif->save(filename);
        delete timer;
        delete gif;
    }
}


void glView::save_settings()
{
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
    point_size = settings->value("point_size", 6.0f).toFloat();
    settings->endGroup();
    settings->beginGroup("Other");
    colorOf = settings->value("colorOf", Line).toInt();
    projectionOrtho = settings->value("projectionOrtho", true).toInt();
    pointType = settings->value("pointType", Square).toInt();
    lineType = settings->value("lineType", Solid).toInt();
    settings->endGroup();
}


















