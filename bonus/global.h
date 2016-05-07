#ifndef GLOBAL_H
#define GLOBAL_H

#include "scene.h"

# define 		DTR(ang) 	((ang) / 180.0 * M_PI)
# define		RTD(rad) 	((rad) * (180.0 / M_PI))
# define		invsqrtf(x)	(1.0f / sqrt(x))

extern Scene *global_scene;

#endif // GLOBAL_H
