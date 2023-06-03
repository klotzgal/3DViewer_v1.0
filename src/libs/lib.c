#include "lib.h"

int parser(char *file) {
  int res = OK;
  if (!file) {
    return ERR;
  }

  int vertexes[100][3] = 0;
  FILE *f = fopen(file, 'r');
  char line[100] = 0;
  while (fscanf(f, "%100s", line)) {
    if (line[0] == 'v') {
    }
  }

  printf("ну парсер\n");
  return res;
}