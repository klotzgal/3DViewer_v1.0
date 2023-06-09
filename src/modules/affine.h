#ifndef INC_AFFINE_H
#define INC_AFFINE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "s21_3dviewer.h"

void translate(double x, double y, double z, obj_data* obj) ;
void scale(double new_size, obj_data* obj);
void rotation(double angle, int axis, obj_data* obj);


#endif //INC_AFFINE_H
