#ifndef _3DVIEWER_V1_SRC_LIBS_LIB_H_
#define _3DVIEWER_V1_SRC_LIBS_LIB_H_

#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR 1

typedef struct data {
  size_t vertices_count;
  double vertices_arr[100];
  size_t vertex_indices_count;
  int vertex_indices_arr[100];
} obj_data;

int parser();

#endif  // _3DVIEWER_V1_SRC_LIBS_LIB_H_