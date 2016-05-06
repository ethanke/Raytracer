#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "image.h"

class Material
{
    public:
        Material();
        Material(const int id, const Color color, const float reflect, const float bump, const Image &texture);

        int		id;
        Color	*color;
        float	reflect;
        float	bump;
        Image	*texture;
};

#endif // MATERIAL_H
