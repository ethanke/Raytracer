#include "glwindow.h"

GlWindow::GlWindow(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

}

GlWindow::~GlWindow()
{

}

void GlWindow::initializeGL()
{

}

void GlWindow::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1080, 720.0, 0.0, -1, 1);
}

void GlWindow::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

    Vector2 pos;
    for (pos.y = 0; pos.y < this->size().height(); pos.y++)
    {
        for (pos.x = 0; pos.x < this->size().width(); pos.x++)
        {
            setPixel(pos, Color(1.0, 0.0, 0.0));
        }
    }
    glFlush();
}

void GlWindow::setPixel(const Vector2 pixel_pos, const Color color)
{
    // Draw a Red 1x1 Square
    glBegin(GL_QUADS);
        glColor3f(color.r, color.g, color.b);
        glVertex2f(pixel_pos.x + 0, pixel_pos.y + 0);
        glVertex2f(pixel_pos.x + 0, pixel_pos.y + 1);
        glVertex2f(pixel_pos.x + 1, pixel_pos.y + 0);
        glVertex2f(pixel_pos.x + 1, pixel_pos.y + 1);
    glEnd();
}

