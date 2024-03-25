#include "tests.h"

int main(void) {
  int failed = 0;
  int i = 0;
  Suite *s21_3d_viewer_back_test[] = {test_obj_file(), test_affine(), NULL};

  for (; s21_3d_viewer_back_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_3d_viewer_back_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("== MODULES CHECKED: %2d ======\n", i);
  printf("=========== FAILED: %2d ======\n", failed);

  return 0;
}
