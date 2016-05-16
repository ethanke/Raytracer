#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include "vector2.h"
#include "color.h"

class Image
{
    public:
        Image(const QString file_path);
        Image(const QString file_path, const Vector2 size, const Color *pixel);

        QString     file_path;
        Vector2		size;
        Color		pixel[];
};

#endif // IMAGE_H
