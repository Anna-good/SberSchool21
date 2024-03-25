#include "tests.h"

#ifndef S21_EPS
#define S21_EPS 1e-20
#endif

static u_int cube_v_count = 8U;
static u_int cube_f_count = 12U;
static u_int cube_ind_count = 36U;
static u_int cube_ind_counts[12] = {3U, 3U, 3U, 3U, 3U, 3U,
                                    3U, 3U, 3U, 3U, 3U, 3U};
static u_int cube_indeces[36] = {
    2U, 3U, 4U, 8U, 7U, 6U, 5U, 6U, 2U, 6U, 7U, 3U, 3U, 7U, 8U, 1U, 4U, 8U,
    1U, 2U, 4U, 5U, 8U, 6U, 1U, 5U, 2U, 2U, 6U, 3U, 4U, 3U, 8U, 5U, 1U, 8U};
static float cube_asw[24] = {
    0.500000f,  -0.500000f, -0.500000f, 0.500000f,  -0.500000f, 0.500000f,
    -0.500000f, -0.500000f, 0.500000f,  -0.500000f, -0.500000f, -0.500000f,
    0.500000f,  0.500000f,  -0.500000f, 0.500000f,  0.500000f,  0.500000f,
    -0.500000f, 0.500000f,  0.500000f,  -0.500000f, 0.500000f,  -0.500000f};
static u_int deer_v_count = 772U;
static u_int deer_f_count = 1508U;
static u_int deer_ind_count = 4524U;

START_TEST(test_open_success_and_parse_correct_cube_1) {
  obj3d *obj = NULL;

  obj = parse_obj_file("data-samples/cube.obj");
  ck_assert_ptr_nonnull(obj);
  // CHECK BASE DATA V/F/INDEXES COUNT
  ck_assert_uint_eq(obj->vertexes_count, cube_v_count);
  ck_assert_uint_eq(obj->faces_count, cube_f_count);
  ck_assert_uint_eq(obj->total_indexes, cube_ind_count);
  // CHECK VERTEXES
  for (u_int i = 0; i < obj->vertexes_count * AX_DIMEN; i++) {
    ck_assert_float_eq_tol(obj->vertexes[i], cube_asw[i], S21_EPS);
  }
  // CHECK BOUNDS
  ck_assert_float_eq_tol(obj->bounds.x_min, -0.5f, 1e-3);
  ck_assert_float_eq_tol(obj->bounds.x_max, 0.5f, 1e-3);
  ck_assert_float_eq_tol(obj->bounds.y_min, -0.5, 1e-5);
  ck_assert_float_eq_tol(obj->bounds.y_max, 0.5, 1e-2);
  ck_assert_float_eq_tol(obj->bounds.z_min, -0.5, 1e-3);
  ck_assert_float_eq_tol(obj->bounds.z_max, 0.5, 1e-3);
  // CHECK THE FACES INDEXES COUNTS
  for (u_int i = 0; i < obj->faces_count; i++) {
    ck_assert_uint_eq((u_int)obj->polygons.indeces_count[i],
                      (u_int)cube_ind_counts[i]);
  }
  // CHECK THE FACES INDEXES
  for (u_int i = 0; i < obj->total_indexes; i++) {
    ck_assert_uint_eq((u_int)obj->polygons.vertexes_ind[i],
                      (u_int)cube_indeces[i]);
  }
  obj_destroy(obj);
  obj = NULL;
  ck_assert_ptr_null(obj);
}
END_TEST

START_TEST(test_open_success_and_parse_correct_deer_2) {
  obj3d *obj = NULL;

  obj = parse_obj_file("data-samples/deer.obj");
  ck_assert_ptr_nonnull(obj);
  // CHECK BASE DATA V/F/INDEXES COUNT
  // printf("\nobj->vertexes_count: %u\n", obj->vertexes_count);
  // printf("\nobj->faces_count: %u\n", obj->faces_count);
  // printf("\nobj->total_indexes: %u (4524)\n", obj->total_indexes);
  ck_assert_uint_eq(obj->vertexes_count, deer_v_count);
  ck_assert_uint_eq(obj->faces_count, deer_f_count);
  ck_assert_uint_eq(obj->total_indexes, deer_ind_count);
  // // CHECK VERTEXES
  // printf("\nCHECK VERTEXES\n");
  // for (u_int i = 3; i < obj->vertexes_count * AX_DIMEN; i += 3) {
  //   printf("%f %f %f\n", obj->vertexes[i - 3], obj->vertexes[i - 2],
  //   obj->vertexes[i - 1]);
  // }
  // for (u_int i = 0; i < obj->vertexes_count * AX_DIMEN; i++) {
  //   ck_assert_float_eq_tol(obj->vertexes[i], cube_asw[i], S21_EPS);
  // }
  // // CHECK BONDS
  // printf("\nCHECK BONDS\n");
  // printf("%f\n", obj->bounds.x_min);
  // printf("%f\n", obj->bounds.x_max);
  // printf("%f\n", obj->bounds.y_min);
  // printf("%f\n", obj->bounds.y_max);
  // printf("%f\n", obj->bounds.z_min);
  // printf("%f\n", obj->bounds.z_max);
  ck_assert_float_eq_tol(obj->bounds.x_min, -662.070007f, 1e-6);
  ck_assert_float_eq_tol(obj->bounds.x_max, 568.287170f, 1e-6);
  ck_assert_float_eq_tol(obj->bounds.y_min, 6.595768f, 1e-6);
  ck_assert_float_eq_tol(obj->bounds.y_max, 1453.478394f, 1e-6);
  ck_assert_float_eq_tol(obj->bounds.z_min, -368.466339f, 1e-6);
  ck_assert_float_eq_tol(obj->bounds.z_max, 369.518066, 1e-6);
  // // CHECK THE FACES INDEXES COUNTS
  // printf("\nCHECK THE FACES INDEXES COUNTS\n");
  // for (u_int i = 0; i < obj->faces_count; i++) {
  //   printf("%u\n", (u_int)obj->polygons.indeces_count[i]);
  // }
  // for (u_int i = 0; i < obj->faces_count; i++) {
  //   ck_assert_uint_eq((u_int)obj->polygons.indeces_count[i],
  //                     (u_int)cube_ind_counts[i]);
  // }
  // // CHECK THE FACES INDEXES
  // printf("\nCHECK THE FACES INDEXES\n");
  // for (u_int i = 3; i < obj->total_indexes; i += 3) {
  //   printf("%u %u %u\n", (u_int)obj->polygons.vertexes_ind[i - 3],
  //                     (u_int)obj->polygons.vertexes_ind[i - 2],
  //                     (u_int)obj->polygons.vertexes_ind[i - 1]);
  // }
  // for (u_int i = 0; i < obj->total_indexes; i++) {
  //   ck_assert_uint_eq((u_int)obj->polygons.vertexes_ind[i],
  //                     (u_int)cube_indeces[i]);
  // }
  obj_destroy(obj);
  obj = NULL;
  ck_assert_ptr_null(obj);
}
END_TEST

START_TEST(test_open_success_and_parse_correct_get_edges_count_cube_3) {
  obj3d *obj = NULL;
  u_int real_edges_count = 18;

  obj = parse_obj_file("data-samples/cube.obj");
  u_int edges_count = get_count_edges(obj);
  ck_assert_uint_eq(edges_count, real_edges_count);
  if (obj) {
    obj_destroy(obj);
  }
}
END_TEST

START_TEST(test_open_success_and_parse_correct_get_edges_count_deer_4) {
  obj3d *obj = NULL;
  u_int real_edges_count = 2271;

  obj = parse_obj_file("data-samples/deer.obj");
  u_int edges_count = get_count_edges(obj);
  ck_assert_uint_eq(edges_count, real_edges_count);
  if (obj) {
    obj_destroy(obj);
  }
}
END_TEST

START_TEST(test_get_edges_count_book_5) {
  obj3d *obj = NULL;
  obj = (obj3d *)malloc(sizeof(obj3d));
  u_int real_edges_count = 7;
  obj->faces_count = 2;
  obj->vertexes_count = 6;
  obj->total_indexes = 8;
  unsigned *indices_counts =
      (unsigned *)malloc(obj->faces_count * sizeof(unsigned));
  unsigned *indices = (unsigned *)malloc(obj->total_indexes * sizeof(unsigned));
  indices_counts[0] = 4;
  indices_counts[1] = 4;
  indices[0] = 1;
  indices[1] = 2;
  indices[2] = 3;
  indices[3] = 4;
  indices[4] = 4;
  indices[5] = 3;
  indices[6] = 5;
  indices[7] = 6;

  obj->polygons.indeces_count = indices_counts;
  obj->polygons.vertexes_ind = indices;
  u_int edges_count = get_count_edges(obj);
  ck_assert_uint_eq(edges_count, real_edges_count);
  if (obj) {
    free(obj->polygons.indeces_count);
    free(obj->polygons.vertexes_ind);
    free(obj);
  }
}
END_TEST

Suite *test_obj_file(void) {
  Suite *s = suite_create("\033[45m-=S21_OBJ_FILE=-\033[0m");
  TCase *tc = tcase_create("test_obj_file_tc");

  tcase_add_test(tc, test_open_success_and_parse_correct_cube_1);
  tcase_add_test(tc, test_open_success_and_parse_correct_deer_2);
  tcase_add_test(tc,
                 test_open_success_and_parse_correct_get_edges_count_cube_3);
  tcase_add_test(tc,
                 test_open_success_and_parse_correct_get_edges_count_deer_4);
  tcase_add_test(tc, test_get_edges_count_book_5);

  suite_add_tcase(s, tc);

  return s;
}
