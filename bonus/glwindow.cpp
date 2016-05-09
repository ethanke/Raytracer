#include "glwindow.h"

GlWindow::GlWindow(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->scene = NULL;
}

GlWindow::~GlWindow()
{

}

void GlWindow::initializeGL()
{
    glViewport(0, 0, this->size().width(), this->size().height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, this->size().width(), this->size().height(), 0.0, -1, 1);
    this->pixel = new Color[this->size().height() * this->size().width()];
    for (int i = 0; i < this->size().height() * this->size().width() - 10; i++)
    {
        this->pixel[i] = Color();
    }
    this->thread = new RaytraceThread(&this->mutex, this);
}

void GlWindow::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, this->size().width(), this->size().height(), 0.0, -1, 1);
}

void GlWindow::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Vector2 pos;
    for (pos.y = 0; pos.y < this->size().height(); pos.y++)
    {
        for (pos.x = 0; pos.x < this->size().width(); pos.x++)
        {
            setPixelOnScreen(pos, this->pixel[pos.x + pos.y * this->size().width()]);
        }
    }
    glFlush();
}

void GlWindow::raytrace_button()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, global_scene->camera->win_size.x, global_scene->camera->win_size.y, 0.0, -1, 1);
    this->thread->start();
}

void GlWindow::setPixel(const Vector2 pixel_pos, const Color color)
{
    this->pixel[pixel_pos.x + pixel_pos.y * this->size().width()].r = color.r;
    this->pixel[pixel_pos.x + pixel_pos.y * this->size().width()].g = color.g;
    this->pixel[pixel_pos.x + pixel_pos.y * this->size().width()].b = color.b;
}

void GlWindow::setPixelOnScreen(const Vector2 pixel_pos, Color color)
{
    // Draw a Red 1x1 Square
    float   ratio_x = (float)this->size().width()  / (global_scene == NULL ? (float)this->size().width()  : (float)global_scene->camera->win_size.x) + 0.35;
    float   ratio_y = (float)this->size().height() / (global_scene == NULL ? (float)this->size().height() : (float)global_scene->camera->win_size.y) + 0.35;
    float   size_x  = 0.5 * ratio_x;
    float   size_y  = 0.5 * ratio_y;
    glBegin(GL_QUADS);
        glColor3f(std::min(color.r * 255.0, 255.0), std::min(color.g * 255.0, 255.0), std::min(color.b * 255.0, 255.0));
        glVertex2f(pixel_pos.x - size_x, pixel_pos.y - size_y);
        glVertex2f(pixel_pos.x - size_x, pixel_pos.y + size_y);
        glVertex2f(pixel_pos.x + size_x, pixel_pos.y - size_y);
        glVertex2f(pixel_pos.x + size_x, pixel_pos.y + size_y);
    glEnd();
}

