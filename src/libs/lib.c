#include "lib.h"

int parser(char *file, double vertexes[40][4]) {
  int res = OK;
  // if (!file) {
  //   return ERR;
  // }

  // FILE *f = fopen(file, "r");
  // char line[100] = "";
  // int i = 0;
  // // fscanf(f, "%99s\n", line)

  // while (fgets(line, 99, f)) {
  //   if (line[0] == 'v') {
  //     // printf("%s", line);
  //     int result = sscanf(line, "v %lf %lf %lf", &vertexes[i][0],
  //                         &vertexes[i][1], &vertexes[i][2]);
  //     vertexes[i][3] = result;
  //     if (result) i++;
  //   }
  // }

  // printf("ну парсер %d\n", i);
  return res;
}
