#include "model_loading.h"

int parse_obj_file(char *filename, obj_data *data) {
  if (filename == NULL || data == NULL) {
    return ERROR;
  }

  int parse_status = OK;
  FILE *file = fopen(filename, "r");
  if (file) {
    count_vertices_and_indices(file, data);
    parse_status = memory_allocation(data);
    if (parse_status != ERROR) {
      printf("Check status [%d]\n", parse_status);
      fseek(file, 0, SEEK_SET);
      parse_status = parse_vertices_and_indices(file, data);
    }
    fclose(file);
  } else {
    parse_status = ERROR;
  }

  return parse_status;
}

int memory_allocation(obj_data *data) {
  int allocate_status = OK;

  if (data->vertices_count) {
    // x, y, z vertex without [w] => multiply by 3
    data->vertices_arr = calloc(data->vertices_count * 3, sizeof(double));
  }
  if (data->vertex_indices_count) {
    // multiply by two because we will build lines that we will loop
    data->vertex_indices_arr =
        calloc(data->vertex_indices_count * 2, sizeof(int));

  }
  if (data->vertices_arr == NULL || data->vertex_indices_arr == NULL) {
    allocate_status = ERROR;
  }

  return allocate_status;
}

void count_vertices_and_indices(FILE *file, obj_data *data) {
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, file) != EOF) {
    if (strncmp(line, "v ", 2) == 0) {
      data->vertices_count++;
    } else if (strncmp(line, "f ", 2) == 0) {
      char *vertex_index = strtok(line + 2, " ");
      while (vertex_index != NULL) {
        if (atoi(vertex_index)) {
          data->vertex_indices_count++;
        }
        vertex_index = strtok(NULL, " ");
      }
    }
  }

  if (line) {
    free(line);
    line = NULL;
  }
}

void data_destructor(obj_data *data) {
  if (data != NULL) {
    if (data->vertices_arr != NULL) {
      free(data->vertices_arr);
      data->vertices_arr = NULL;
    }
    if (data->vertex_indices_arr != NULL) {
      free(data->vertex_indices_arr);
      data->vertex_indices_arr = NULL;
    }
  }
}

int parse_vertices_and_indices(FILE *file, obj_data *data) {
  int parse_status = OK;
  char *line = NULL;
  size_t len = 0;
  size_t i = 0;
  size_t vertex_counter = 0;
  size_t vertex_indices_counter = 0;

  while (getline(&line, &len, file) != EOF) {
    if (strncmp(line, "v ", 2) == 0) {
      vertex_counter++;
      double x, y, z;
      sscanf(line, "%lf %lf %lf", &x, &y, &z);
      data->vertices_arr[i++] = x;
      data->vertices_arr[i++] = y;
      data->vertices_arr[i++] = z;
    } else if (strncmp(line, "f ", 2) == 0) {
      int first_index = 0;
      char *vertex_index = strtok(line + 2, " ");
      while (vertex_index != NULL) {
        int index_val = atoi(vertex_index);
        if (index_val) {
          // If an index is negative then it relatively refers to the end
          // of the vertex list, -1 referring to the last element.
          if (index_val < 0) {
            index_val += vertex_counter + 1;
          }
          data->vertex_indices_arr[vertex_indices_counter] = index_val - 1;
          if (!first_index) {
            first_index = index_val - 1;
          } else {
            data->vertex_indices_arr[++vertex_indices_counter] = index_val - 1;
          }
          vertex_indices_counter++;
        }
        vertex_index = strtok(NULL, " ");
      }
      // loop lines
      data->vertex_indices_arr[vertex_indices_counter] = first_index;
      vertex_indices_counter++;
    }
  }

  if (line) {
    free(line);
    line = NULL;
  }

  // TO DO: CHECK VALIDATOR
//  if (!data->vertices_arr[data->vertices_count * 3] ||
//      !data->vertex_indices_arr[data->vertex_indices_count * 2]) {
//    parse_status = ERROR;
//  }

  return parse_status;
}
