// #include "libs/lib.h"
#include "modules/model_loading.h"

int main() {
  obj_data d = {0};
  char file_name[] = "/opt/goinfre/klotzgal/skull.obj";
  // char file_name[] = "/Users/klotzgal/Desktop/kl/3DViewer_v1.0/src/cube.obj";

  parse_obj_file(file_name, &d);
  // FILE* f = fopen(file_name, "r");
  printf("%d, %d, %d, %d\n", d.vertex_indices_arr[0], d.vertex_indices_arr[1],
         d.vertex_indices_arr[2], d.vertex_indices_arr[3]);
  printf("vertices_count = %ld\n", d.vertices_count);
  printf("vertex_indices_count = %ld\n", d.vertex_indices_count);
  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    printf("%lf ", d.vertices_arr[i]);
    i++;
  }
  // printf("%lf, %lf, %lf, %lf\n", d.vertices_arr[3], d.vertices_arr[4],
  //        d.vertices_arr[5], d.vertices_arr[6]);
  return 0;
}