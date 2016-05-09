#include "material.h"

Material::Material()
{
    this->id = -1;
    this->color = new Color();
    this->reflect = 0.0;
    this->transparency = 0.0;
    this->bump = 0.0;
    this->texture = new Image("NULL");
}

Material::Material(const int id, const Color color, const float reflect, const float bump, Image *texture)
{
    this->id = id;
    this->color = new Color(color.r, color.g, color.b);
    this->reflect = reflect;

    // A CHANGER
    this->transparency = 0.0;

    this->bump = bump;
    this->texture = texture;
}
