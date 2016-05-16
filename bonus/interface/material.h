#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include <QImage>

class Material
{
    public:
        Material();
        Material(const int id, const Color color, const float reflect, const float transparency, const float ior,  const float bump, const int sky, QString path);

        int		id;
        Color	*color;
        float   transparency;
        int     sky;
        float   ior;
        float   eior;
        float	reflect;
        float	bump;
        QImage	*texture;
};

#endif // MATERIAL_H
