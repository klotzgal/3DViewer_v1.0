#include <check.h>

#include "../modules/affine.h"
#include "../modules/model_loading.h"

#define EPS 1e-07

START_TEST(parser_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                           0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                           0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  int vertex_indices_arr[] = {0, 6, 4, 4, 6, 0, 2, 6, 6, 2, 0, 3, 2, 2, 3,
                              0, 1, 3, 3, 1, 2, 7, 7, 6, 6, 2, 2, 3, 3, 7,
                              7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7, 5, 5, 4, 0,
                              4, 5, 5, 4, 0, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0};
  int res = parse_obj_file(filename, &d);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq(d.vertices_arr[i], vertices_arr[i]);
    i++;
  }
  i = 0;
  while (i < (int)d.vertex_indices_count * 2) {
    ck_assert_int_eq(d.vertex_indices_arr[i], vertex_indices_arr[i]);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(parser_2) {
  obj_data d = {0};
  char filename[] = "tmp/xxx.obj";
  int res = parse_obj_file(filename, &d);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(parser_3) {
  obj_data d = {0};
  char *filename = NULL;
  int res = parse_obj_file(filename, &d);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(affine_rotate_X_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 0.0000000,  0.0000000, 1.0000000, 1.7320508,
      0.0000000, 1.7320508, -1.0000000, 0.0000000, 2.7320508, 0.7320508,
      2.0000000, 0.0000000, 0.0000000,  2.0000000, 1.0000000, 1.7320508,
      2.0000000, 1.7320508, -1.0000000, 2.0000000, 2.7320508, 0.7320508};
  parse_obj_file(filename, &d);
  rotate_X(&d, 30);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_X_2) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 0.0000000, 0.0000000, -1.0000000, 1.7320508,
      0.0000000, 1.7320508, 1.0000000, 0.0000000, 0.7320508,  2.7320508,
      2.0000000, 0.0000000, 0.0000000, 2.0000000, -1.0000000, 1.7320508,
      2.0000000, 1.7320508, 1.0000000, 2.0000000, 0.7320508,  2.7320508};
  parse_obj_file(filename, &d);
  rotate_X(&d, -30);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);
  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_X_3) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, -0.0000000, 0.0000000, 0.0000000, -0.6840403, -1.8793852,
      0.0000000, -1.8793852, 0.6840403, 0.0000000, -2.5634255, -1.1953450,
      2.0000000, -0.0000000, 0.0000000, 2.0000000, -0.6840403, -1.8793852,
      2.0000000, -1.8793852, 0.6840403, 2.0000000, -2.5634255, -1.1953450};
  parse_obj_file(filename, &d);
  rotate_X(&d, 2000000);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);
  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_Y_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 0.0000000,  1.0000000, 0.0000000, 1.7320508,
      0.0000000, 2.0000000, 0.0000000,  1.0000000, 2.0000000, 1.7320508,
      1.7320508, 0.0000000, -1.0000000, 2.7320508, 0.0000000, 0.7320508,
      1.7320508, 2.0000000, -1.0000000, 2.7320508, 2.0000000, 0.7320508};
  parse_obj_file(filename, &d);
  rotate_Y(&d, 30);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_Y_2) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 0.0000000, -1.0000000, 0.0000000, 1.7320508,
      0.0000000, 2.0000000, 0.0000000, -1.0000000, 2.0000000, 1.7320508,
      1.7320508, 0.0000000, 1.0000000, 0.7320508,  0.0000000, 2.7320508,
      1.7320508, 2.0000000, 1.0000000, 0.7320508,  2.0000000, 2.7320508};
  parse_obj_file(filename, &d);
  rotate_Y(&d, -30);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_Y_3) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      -0.0000000, 0.0000000, 0.0000000, -0.6840403, 0.0000000, -1.8793852,
      -0.0000000, 2.0000000, 0.0000000, -0.6840403, 2.0000000, -1.8793852,
      -1.8793852, 0.0000000, 0.6840403, -2.5634255, 0.0000000, -1.1953450,
      -1.8793852, 2.0000000, 0.6840403, -2.5634255, 2.0000000, -1.1953450};
  parse_obj_file(filename, &d);
  rotate_Y(&d, 2000000);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_Z_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000,  0.0000000, 0.0000000, 0.0000000,  2.0000000,
      1.0000000, 1.7320508,  0.0000000, 1.0000000, 1.7320508,  2.0000000,
      1.7320508, -1.0000000, 0.0000000, 1.7320508, -1.0000000, 2.0000000,
      2.7320508, 0.7320508,  0.0000000, 2.7320508, 0.7320508,  2.0000000};
  parse_obj_file(filename, &d);
  rotate_Z(&d, 30);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_Z_2) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000,  0.0000000, 0.0000000, 0.0000000,  0.0000000, 2.0000000,
      -1.0000000, 1.7320508, 0.0000000, -1.0000000, 1.7320508, 2.0000000,
      1.7320508,  1.0000000, 0.0000000, 1.7320508,  1.0000000, 2.0000000,
      0.7320508,  2.7320508, 0.0000000, 0.7320508,  2.7320508, 2.0000000};
  parse_obj_file(filename, &d);
  rotate_Z(&d, -30);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_rotate_Z_3) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      -0.0000000, 0.0000000,  0.0000000, -0.0000000, 0.0000000,  2.0000000,
      -0.6840403, -1.8793852, 0.0000000, -0.6840403, -1.8793852, 2.0000000,
      -1.8793852, 0.6840403,  0.0000000, -1.8793852, 0.6840403,  2.0000000,
      -2.5634255, -1.1953450, 0.0000000, -2.5634255, -1.1953450, 2.0000000};
  parse_obj_file(filename, &d);
  rotate_Z(&d, 2000000);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_scale_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 6.0000000,
      0.0000000, 6.0000000, 0.0000000, 0.0000000, 6.0000000, 6.0000000,
      6.0000000, 0.0000000, 0.0000000, 6.0000000, 0.0000000, 6.0000000,
      6.0000000, 6.0000000, 0.0000000, 6.0000000, 6.0000000, 6.0000000};
  parse_obj_file(filename, &d);
  scale(&d, 3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_scale_2) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.6000000,
      0.0000000, 0.6000000, 0.0000000, 0.0000000, 0.6000000, 0.6000000,
      0.6000000, 0.0000000, 0.0000000, 0.6000000, 0.0000000, 0.6000000,
      0.6000000, 0.6000000, 0.0000000, 0.6000000, 0.6000000, 0.6000000};
  parse_obj_file(filename, &d);
  scale(&d, 0.3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_scale_3) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000,      0.0000000,      0.0000000,      0.0000000,
      0.0000000,      666666.0000000, 0.0000000,      666666.0000000,
      0.0000000,      0.0000000,      666666.0000000, 666666.0000000,
      666666.0000000, 0.0000000,      0.0000000,      666666.0000000,
      0.0000000,      666666.0000000, 666666.0000000, 666666.0000000,
      0.0000000,      666666.0000000, 666666.0000000, 666666.0000000};
  parse_obj_file(filename, &d);
  scale(&d, 333333);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_X_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      3.0000000, 0.0000000, 0.0000000, 3.0000000, 0.0000000, 2.0000000,
      3.0000000, 2.0000000, 0.0000000, 3.0000000, 2.0000000, 2.0000000,
      5.0000000, 0.0000000, 0.0000000, 5.0000000, 0.0000000, 2.0000000,
      5.0000000, 2.0000000, 0.0000000, 5.0000000, 2.0000000, 2.0000000};
  parse_obj_file(filename, &d);
  move_X(&d, 3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_X_2) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      -3.0000000, 0.0000000, 0.0000000, -3.0000000, 0.0000000, 2.0000000,
      -3.0000000, 2.0000000, 0.0000000, -3.0000000, 2.0000000, 2.0000000,
      -1.0000000, 0.0000000, 0.0000000, -1.0000000, 0.0000000, 2.0000000,
      -1.0000000, 2.0000000, 0.0000000, -1.0000000, 2.0000000, 2.0000000};
  parse_obj_file(filename, &d);
  move_X(&d, -3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_X_3) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      -0.5000000, 0.0000000, 0.0000000, -0.5000000, 0.0000000, 2.0000000,
      -0.5000000, 2.0000000, 0.0000000, -0.5000000, 2.0000000, 2.0000000,
      1.5000000,  0.0000000, 0.0000000, 1.5000000,  0.0000000, 2.0000000,
      1.5000000,  2.0000000, 0.0000000, 1.5000000,  2.0000000, 2.0000000};
  parse_obj_file(filename, &d);
  move_X(&d, -0.5);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_Y_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 3.0000000, 0.0000000, 0.0000000, 3.0000000, 2.0000000,
      0.0000000, 5.0000000, 0.0000000, 0.0000000, 5.0000000, 2.0000000,
      2.0000000, 3.0000000, 0.0000000, 2.0000000, 3.0000000, 2.0000000,
      2.0000000, 5.0000000, 0.0000000, 2.0000000, 5.0000000, 2.0000000};
  parse_obj_file(filename, &d);
  move_Y(&d, 3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_Y_2) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, -3.0000000, 0.0000000, 0.0000000, -3.0000000, 2.0000000,
      0.0000000, -1.0000000, 0.0000000, 0.0000000, -1.0000000, 2.0000000,
      2.0000000, -3.0000000, 0.0000000, 2.0000000, -3.0000000, 2.0000000,
      2.0000000, -1.0000000, 0.0000000, 2.0000000, -1.0000000, 2.0000000};
  parse_obj_file(filename, &d);
  move_Y(&d, -3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_Y_3) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, -0.5000000, 0.0000000, 0.0000000, -0.5000000, 2.0000000,
      0.0000000, 1.5000000,  0.0000000, 0.0000000, 1.5000000,  2.0000000,
      2.0000000, -0.5000000, 0.0000000, 2.0000000, -0.5000000, 2.0000000,
      2.0000000, 1.5000000,  0.0000000, 2.0000000, 1.5000000,  2.0000000};
  parse_obj_file(filename, &d);
  move_Y(&d, -0.5);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_Z_1) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 3.0000000, 0.0000000, 0.0000000, 5.0000000,
      0.0000000, 2.0000000, 3.0000000, 0.0000000, 2.0000000, 5.0000000,
      2.0000000, 0.0000000, 3.0000000, 2.0000000, 0.0000000, 5.0000000,
      2.0000000, 2.0000000, 3.0000000, 2.0000000, 2.0000000, 5.0000000};
  parse_obj_file(filename, &d);
  move_Z(&d, 3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_Z_2) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, -3.0000000, 0.0000000, 0.0000000, -1.0000000,
      0.0000000, 2.0000000, -3.0000000, 0.0000000, 2.0000000, -1.0000000,
      2.0000000, 0.0000000, -3.0000000, 2.0000000, 0.0000000, -1.0000000,
      2.0000000, 2.0000000, -3.0000000, 2.0000000, 2.0000000, -1.0000000};
  parse_obj_file(filename, &d);
  move_Z(&d, -3);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

START_TEST(affine_move_Z_3) {
  obj_data d = {0};
  char filename[] = "tmp/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, -0.5000000, 0.0000000, 0.0000000, 1.5000000,
      0.0000000, 2.0000000, -0.5000000, 0.0000000, 2.0000000, 1.5000000,
      2.0000000, 0.0000000, -0.5000000, 2.0000000, 0.0000000, 1.5000000,
      2.0000000, 2.0000000, -0.5000000, 2.0000000, 2.0000000, 1.5000000};
  parse_obj_file(filename, &d);
  move_Z(&d, -0.5);
  ck_assert_int_eq(d.vertex_indices_count, 30);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  data_destructor(&d);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");
  TCase *tc_parser_1;
  tc_parser_1 = tcase_create("parser_1");
  suite_add_tcase(s, tc_parser_1);
  tcase_add_test(tc_parser_1, parser_1);

  TCase *tc_parser_2;
  tc_parser_2 = tcase_create("parser_2");
  suite_add_tcase(s, tc_parser_2);
  tcase_add_test(tc_parser_2, parser_2);

  TCase *tc_parser_3;
  tc_parser_3 = tcase_create("parser_3");
  suite_add_tcase(s, tc_parser_3);
  tcase_add_test(tc_parser_3, parser_3);

  TCase *tc_affine_rotate_X_1;
  tc_affine_rotate_X_1 = tcase_create("affine_rotate_X_1");
  suite_add_tcase(s, tc_affine_rotate_X_1);
  tcase_add_test(tc_affine_rotate_X_1, affine_rotate_X_1);

  TCase *tc_affine_rotate_X_2;
  tc_affine_rotate_X_2 = tcase_create("affine_rotate_X_2");
  suite_add_tcase(s, tc_affine_rotate_X_2);
  tcase_add_test(tc_affine_rotate_X_2, affine_rotate_X_2);

  TCase *tc_affine_rotate_X_3;
  tc_affine_rotate_X_3 = tcase_create("affine_rotate_X_3");
  suite_add_tcase(s, tc_affine_rotate_X_3);
  tcase_add_test(tc_affine_rotate_X_3, affine_rotate_X_3);

  TCase *tc_affine_rotate_Y_1;
  tc_affine_rotate_Y_1 = tcase_create("affine_rotate_Y_1");
  suite_add_tcase(s, tc_affine_rotate_Y_1);
  tcase_add_test(tc_affine_rotate_Y_1, affine_rotate_Y_1);

  TCase *tc_affine_rotate_Y_2;
  tc_affine_rotate_Y_2 = tcase_create("affine_rotate_Y_2");
  suite_add_tcase(s, tc_affine_rotate_Y_2);
  tcase_add_test(tc_affine_rotate_Y_2, affine_rotate_Y_2);

  TCase *tc_affine_rotate_Y_3;
  tc_affine_rotate_Y_3 = tcase_create("affine_rotate_Y_3");
  suite_add_tcase(s, tc_affine_rotate_Y_3);
  tcase_add_test(tc_affine_rotate_Y_3, affine_rotate_Y_3);

  TCase *tc_affine_rotate_Z_1;
  tc_affine_rotate_Z_1 = tcase_create("affine_rotate_Z_1");
  suite_add_tcase(s, tc_affine_rotate_Z_1);
  tcase_add_test(tc_affine_rotate_Z_1, affine_rotate_Z_1);

  TCase *tc_affine_rotate_Z_2;
  tc_affine_rotate_Z_2 = tcase_create("affine_rotate_Z_2");
  suite_add_tcase(s, tc_affine_rotate_Z_2);
  tcase_add_test(tc_affine_rotate_Z_2, affine_rotate_Z_2);

  TCase *tc_affine_rotate_Z_3;
  tc_affine_rotate_Z_3 = tcase_create("affine_rotate_Z_3");
  suite_add_tcase(s, tc_affine_rotate_Z_3);
  tcase_add_test(tc_affine_rotate_Z_3, affine_rotate_Z_3);

  TCase *tc_affine_scale_1;
  tc_affine_scale_1 = tcase_create("affine_scale_1");
  suite_add_tcase(s, tc_affine_scale_1);
  tcase_add_test(tc_affine_scale_1, affine_scale_1);

  TCase *tc_affine_scale_2;
  tc_affine_scale_2 = tcase_create("affine_scale_2");
  suite_add_tcase(s, tc_affine_scale_2);
  tcase_add_test(tc_affine_scale_2, affine_scale_2);

  TCase *tc_affine_scale_3;
  tc_affine_scale_3 = tcase_create("affine_scale_3");
  suite_add_tcase(s, tc_affine_scale_3);
  tcase_add_test(tc_affine_scale_3, affine_scale_3);

  TCase *tc_affine_move_X_1;
  tc_affine_move_X_1 = tcase_create("affine_move_X_1");
  suite_add_tcase(s, tc_affine_move_X_1);
  tcase_add_test(tc_affine_move_X_1, affine_move_X_1);

  TCase *tc_affine_move_X_2;
  tc_affine_move_X_2 = tcase_create("affine_move_X_2");
  suite_add_tcase(s, tc_affine_move_X_2);
  tcase_add_test(tc_affine_move_X_2, affine_move_X_2);

  TCase *tc_affine_move_X_3;
  tc_affine_move_X_3 = tcase_create("affine_move_X_3");
  suite_add_tcase(s, tc_affine_move_X_3);
  tcase_add_test(tc_affine_move_X_3, affine_move_X_3);

  TCase *tc_affine_move_Y_1;
  tc_affine_move_Y_1 = tcase_create("affine_move_Y_1");
  suite_add_tcase(s, tc_affine_move_Y_1);
  tcase_add_test(tc_affine_move_Y_1, affine_move_Y_1);

  TCase *tc_affine_move_Y_2;
  tc_affine_move_Y_2 = tcase_create("affine_move_Y_2");
  suite_add_tcase(s, tc_affine_move_Y_2);
  tcase_add_test(tc_affine_move_Y_2, affine_move_Y_2);

  TCase *tc_affine_move_Y_3;
  tc_affine_move_Y_3 = tcase_create("affine_move_Y_3");
  suite_add_tcase(s, tc_affine_move_Y_3);
  tcase_add_test(tc_affine_move_Y_3, affine_move_Y_3);

  TCase *tc_affine_move_Z_1;
  tc_affine_move_Z_1 = tcase_create("affine_move_Z_1");
  suite_add_tcase(s, tc_affine_move_Z_1);
  tcase_add_test(tc_affine_move_Z_1, affine_move_Z_1);

  TCase *tc_affine_move_Z_2;
  tc_affine_move_Z_2 = tcase_create("affine_move_Z_2");
  suite_add_tcase(s, tc_affine_move_Z_2);
  tcase_add_test(tc_affine_move_Z_2, affine_move_Z_2);

  TCase *tc_affine_move_Z_3;
  tc_affine_move_Z_3 = tcase_create("affine_move_Z_3");
  suite_add_tcase(s, tc_affine_move_Z_3);
  tcase_add_test(tc_affine_move_Z_3, affine_move_Z_3);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return 0;
}
