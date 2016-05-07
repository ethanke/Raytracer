#include "color.h"

Color::Color()
{
    this->r = 0.0;
    this->g = 0.0;
    this->b = 0.0;
}


Color::Color(const float r, const float g, const float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::clamp_color()
{
    float   max = 1.0;

    if (this->r > max)
        max = this->r;
    if (this->g > max)
        max = this->g;
    if (this->b > max)
        max = this->b;
    this->r /= max;
    this->g /= max;
    this->b /= max;
}
