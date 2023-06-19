// #include "libs/lib.h"
#include "modules/affine.h"
#include "modules/model_loading.h"

int main() {
  obj_data d = {0};
  // char file_name[] = "/opt/goinfre/klotzgal/skull.obj";
  char file_name[] = "tmp/cube.obj";

  parse_obj_file(file_name, &d);
  // FILE* f = fopen(file_name, "r");
  // printf("%d, %d, %d, %d\n", d.vertex_indices_arr[0],
  // d.vertex_indices_arr[1],
  //        d.vertex_indices_arr[2], d.vertex_indices_arr[3]);
  move_Z(&d, -3);
  printf("vertices_count = %ld\n", d.vertices_count);
  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    printf("%.7lf ,", d.vertices_arr[i]);
    i++;
    if (i % 3 == 0) printf("\n");
  }
  printf("vertex_indices_count = %ld\n", d.vertex_indices_count);
  i = 0;
  while (i < (int)d.vertex_indices_count * 2) {
    printf("%d ", d.vertex_indices_arr[i]);
    i++;
    if (i % 4 == 0) printf("\n");
  }
  // printf("%lf, %lf, %lf, %lf\n", d.vertices_arr[3], d.vertices_arr[4],
  //        d.vertices_arr[5], d.vertices_arr[6]);
  return 0;
}