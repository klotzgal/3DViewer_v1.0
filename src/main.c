#include "libs/lib.h"

int main() {
  char file[] = "cube.obj";
  double vertexes[40][4] = {{0}};
  parser(file, vertexes);

  for (int k = 0; k < 40; k++) {
    if (!vertexes[k][3]) break;
    printf("v");
    for (int j = 0; j < 4; j++) {
      printf(" %lf", vertexes[k][j]);
    }
    printf("\n");
  }
  return 0;
}