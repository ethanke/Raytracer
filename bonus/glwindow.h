#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QObject>
#include <QGLWidget>
#include <QtOpenGL>
#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <GLUT/glut.h>
        #include <OpenGL/OpenGL.h>
    #endif
#elif defined _WIN32 || defined _WIN64
    #include <GL/glut.h>
#endif

#include "color.h"
#include "vector2.h"
#include "vector3.h"
#include "raytracethread.h"

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

    private slots:
        void raytrace_button();

    private:
        Color *pixel;
        RaytraceThread *thread;
        void setPixel(const Vector2 pixel_pos, const Color color);
};

#endif // GLWINDOW_H
