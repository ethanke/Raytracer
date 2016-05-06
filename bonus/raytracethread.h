#ifndef RAYTRACETHREAD_H
#define RAYTRACETHREAD_H

#include <QThread>
#include <QMutex>
#include "vector2.h"
#include "color.h"

class RaytraceThread : public QThread
{
    protected:
        void run();
};

#endif // RAYTRACETHREAD_H
