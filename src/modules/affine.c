#include "affine.h"

void translate(double x, double y, double z, obj_data*obj) {
  for (int i = 0; i < (int)obj->vertices_count * 3; i += 3) {
    obj->vertices_arr[i] += x;
  }
  for (int i = 1; i < (int)obj->vertices_count * 3; i += 3) {
    obj->vertices_arr[i] += y;
  }
  for (int i = 2; i < (int)obj->vertices_count * 3; i += 3) {
    obj->vertices_arr[i] += z;
  }
}

void scale(double new_size, obj_data*obj) {
  for (int i = 0; i < (int)obj->vertices_count * 3; i += 3) {
    obj->vertices_arr[i] *= new_size;
  }
  for (int i = 1; i < (int)obj->vertices_count * 3; i += 3) {
    obj->vertices_arr[i] *= new_size;
  }
  for (int i = 2; i < (int)obj->vertices_count * 3; i += 3) {
    obj->vertices_arr[i] *= new_size;
  }
}

void rotation(double angle, int axis, obj_data*obj) {
  double new_angle = angle * M_PI / 180;
  for (int i = 0; i < (int)obj->vertices_count * 3; i += 3) {
    double x = obj->vertices_arr[i];
    double y = obj->vertices_arr[i + 1];
    double z = obj->vertices_arr[i + 2];
    // Поворот по X
    if (axis == 0) {
      obj->vertices_arr[i + 1] = y * cos(new_angle) - z * sin(new_angle);
      obj->vertices_arr[i + 2] = y * sin(new_angle) + z * cos(new_angle);
      // Поворот по Y
    } else if (axis == 1) {
      obj->vertices_arr[i] = x * cos(new_angle) + z * sin(new_angle);
      obj->vertices_arr[i + 2] = -x * sin(new_angle) + z * cos(new_angle);
      // Поворот по Z
    } else if (axis == 2) {
      obj->vertices_arr[i] = x * cos(new_angle) - y * sin(new_angle);
      obj->vertices_arr[i + 1] = x * sin(new_angle) + y * cos(new_angle);
    }
  }
}
