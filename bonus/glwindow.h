#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>

#include "color.h"
#include "vector2.h"
#include "vector3.h"

class GlWindow : public QGLWidget
{
    Q_OBJECT

    public:
        explicit GlWindow(QWidget *parent = 0);
       ~GlWindow();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);

    private:
        void setPixel(const Vector2 pixel_pos, const Color color);
};

#endif // GLWINDOW_H
