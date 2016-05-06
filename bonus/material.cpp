#include "material.h"

Material::Material(const int id, const Color color, const float reflect, const float bump, const Image texture)
{
    this->id = id;
    this->color = color;
    this->reflect = reflect;
    this->bump = bump;
    this->texture = new Image(texture.file_path, texture.size, texture.pixel);
}
