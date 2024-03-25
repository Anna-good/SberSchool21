#include "tests.h"

#ifndef S21_EPS
#define S21_EPS 1e-5
#endif

// Move cube test
START_TEST(move_cube) {
  obj3d *obj = NULL;
  obj = parse_obj_file("data-samples/cube.obj");
  scaleObjBeforeDraw(0.5f, obj);
  move_coordinate(0.5, obj, X_CORD);
  move_coordinate(-0.5, obj, Y_CORD);
  move_coordinate(1, obj, Z_CORD);
  ck_assert_float_eq_tol(obj->vertexes[9], 0.0, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[10], -1.0, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[11], 0.5, S21_EPS);
  obj_destroy(obj);
  obj = NULL;
}

// Rotate cube standart case
START_TEST(rotate_cube_y) {
  obj3d *obj = NULL;
  obj = parse_obj_file("data-samples/cube.obj");
  scaleObjBeforeDraw(0.5f, obj);
  rotate_object(1, obj, Y_CORD);
  ck_assert_float_eq_tol(obj->vertexes[6], 0.15058433, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[7], -0.5, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[8], 0.69088664, S21_EPS);
  obj_destroy(obj);
  obj = NULL;
}

START_TEST(rotate_cube_x) {
  obj3d *obj = NULL;
  obj = parse_obj_file("data-samples/cube.obj");
  scaleObjBeforeDraw(0.5f, obj);
  rotate_object(1, obj, X_CORD);
  ck_assert_float_eq_tol(obj->vertexes[6], -0.5, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[7], -0.69088664, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[8], -0.15058433, S21_EPS);
  obj_destroy(obj);
  obj = NULL;
}

START_TEST(rotate_cube_z) {
  obj3d *obj = NULL;
  obj = parse_obj_file("data-samples/cube.obj");
  scaleObjBeforeDraw(0.5f, obj);
  rotate_object(1, obj, Z_CORD);
  ck_assert_float_eq_tol(obj->vertexes[6], 0.15058433, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[7], -0.69088664, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[8], 0.5, S21_EPS);
  obj_destroy(obj);
  obj = NULL;
}

// Rotate cube errors
START_TEST(rotate_cube_zero) {
  obj3d *obj = NULL;
  obj = parse_obj_file("data-samples/cube.obj");
  scaleObjBeforeDraw(0.5f, obj);
  rotate_object(0, obj, Z_CORD);
  rotate_object(0, obj, X_CORD);
  rotate_object(0, obj, Y_CORD);
  ck_assert_float_eq_tol(obj->vertexes[0], 0.5, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[1], -0.5, S21_EPS);
  ck_assert_float_eq_tol(obj->vertexes[2], -0.5, S21_EPS);
  obj_destroy(obj);
  obj = NULL;
}

Suite *test_affine(void) {
  Suite *s = suite_create("\033[45m-=S21_AFFINE=-\033[0m");
  TCase *tc = tcase_create("test_affine_tc");

  tcase_add_test(tc, move_cube);
  tcase_add_test(tc, rotate_cube_y);
  tcase_add_test(tc, rotate_cube_x);
  tcase_add_test(tc, rotate_cube_z);
  tcase_add_test(tc, rotate_cube_zero);
  suite_add_tcase(s, tc);

  return s;
}
