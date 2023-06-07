#ifndef _3DVIEWER_V1_SRC_LIBS_LIB_H_
#define _3DVIEWER_V1_SRC_LIBS_LIB_H_

#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR 1

typedef struct {
  int vert_count;
  double vertexes[100];
  int surf_count;
  int surfaces[100];
} data;

int parser();

#endif  // _3DVIEWER_V1_SRC_LIBS_LIB_H_