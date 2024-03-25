/**
 * @file s21_affine.c
 * @brief Implementation of affine transformations for changing obj coord
 */

#include "s21_3d_viewer.h"

// ФУНКЦИИ МАСШТАБИРОВАНИЯ ОБЪЕКТА
//  применение масштаба перед рисонованием объекта
/*значение scaleForDraw будем получать из ползунка отвечающего
за масштаб(UI), но оно должно быть в интервале 0..1.
*/
/**
 * @brief scaling object before draw
 * @param[in] scaleForDraw - scale in interval 0..1 from gui
 * @param[in] obj - pointer to obj3d struct
 * @param[out] result of function
 */
int scaleObjBeforeDraw(float scaleForDraw, obj3d* obj) {
  int function_result = FALSE;
  moveToCenter(obj);
  float maxDistance = 0.0, scale_factor = 0.0;
  if (maxDistanceAxies(obj, &maxDistance) == TRUE) {
    scale_factor = (scaleForDraw - (scaleForDraw * (-1))) / maxDistance;
    if (scale_factor > 0) {  // maybe useful  delta = 0.000000001, зависит от
                             // задаваемого значения через UI
      scaleApply(scale_factor, obj);
      function_result = TRUE;
    }
  }
  return function_result;
}

// Поиск максимального расстояния по осям, для того, чтобы отмаштабирать объект,
// чтобы он помещался в куб с максимальным расстоянием не большим 1. "0 < x <=
//  1";
/**
 * @brief scaling object before draw
 * @param[in] scaleForDraw - scale in interval 0..1 from gui
 * @param[in] obj - pointer to obj3d struct
 * @param[out] result of function
 */
int maxDistanceAxies(obj3d* obj, float* result) {
  int function_result = FALSE;
  float dist_x = obj->bounds.x_max - obj->bounds.x_min;
  float dist_y = obj->bounds.y_max - obj->bounds.y_min;
  float dist_z = obj->bounds.z_max - obj->bounds.z_min;
  if (dist_x >= dist_y && dist_x >= dist_z) {
    *result = dist_x;
  } else if (dist_y >= dist_z) {
    *result = dist_y;
  } else {
    *result = dist_z;
  }
  if (*result > 0) {  // maybe useful  delta = 0.000000001
    function_result = TRUE;
  }
  return function_result;
}
/**
 * @brief apply scale for object
 * @param[in] scale - scale from gui
 * @param[in] obj - pointer to obj3d struct
 */
void scaleApply(float scale, obj3d* obj) {
  obj->bounds.x_max *= scale;
  obj->bounds.x_min *= scale;
  obj->bounds.y_max *= scale;
  obj->bounds.y_min *= scale;
  obj->bounds.z_max *= scale;
  obj->bounds.z_min *= scale;
  for (unsigned int i = 0; i < obj->vertexes_count * 3; i += 3) {
    obj->vertexes[i] *= scale;
    obj->vertexes[i + 1] *= scale;
    obj->vertexes[i + 2] *= scale;
  }
}

/**
 * @brief move object to center of cords
 * @param[in] obj - pointer to obj3d struct
 */
void moveToCenter(obj3d* obj) {  // add tests!
  float x_center =
      obj->bounds.x_min + (obj->bounds.x_max - obj->bounds.x_min) / 2.0;
  float y_center =
      obj->bounds.y_min + (obj->bounds.y_max - obj->bounds.y_min) / 2.0;
  float z_center =
      obj->bounds.z_min + (obj->bounds.z_max - obj->bounds.z_min) / 2.0;
  obj->bounds.x_min -= x_center;
  obj->bounds.x_max -= x_center;
  obj->bounds.y_min -= y_center;
  obj->bounds.y_max -= y_center;
  obj->bounds.z_min -= z_center;
  obj->bounds.z_max -= z_center;
  for (u_int i = 0; i < obj->vertexes_count * 3; i += 3) {
    obj->vertexes[i] -= x_center;
    obj->vertexes[i + 1] -= y_center;
    obj->vertexes[i + 2] -= z_center;
  }
}

// ФУНКЦИИ СМЕЩЕНИЯ ОБЪЕКТА ВДОЛЬ ОСЕЙ КООРДИНАТ
// Сдвиг всего объекта по оси, в зависимости от типа координаты
/*Так как мы приводим OpenGL Widget к окну от -1 до 1, то максимально значение
сдвига move_value = 1 - предполагается, что это задается через UI
*/
/**
 * @brief smoving out object for X, Y, Z
 * @param[in] move_value - distance
 * @param[in] obj - pointer to obj3d struct
 * @param[in] type_of_coordinate - type of X, Y, Z
 */
void move_coordinate(float move_value, obj3d* obj, int type_of_coordinate) {
  /*if (type_of_coordinate == X_CORD) {
    obj->bounds.x_min += move_value;
    obj->bounds.x_max += move_value;
  } else if (type_of_coordinate == Y_CORD) {
    obj->bounds.y_min += move_value;
    obj->bounds.y_max += move_value;
  } else {
    obj->bounds.z_min += move_value;
    obj->bounds.z_max += move_value;
  }*/
  for (unsigned int i = 0; i < obj->vertexes_count * 3; i += 3) {
    obj->vertexes[i + type_of_coordinate] += move_value;
  }
}

// ФУНКЦИИ ВРАЩЕНИЯ ОБЪЕКТА
// умножение матрицы линейного оператора 3 на 3 на значения координат
/**
 * @brief multiply matrix of linear operator for coords
 * @param[in] matrix_transform- matrix of linear operator
 * @param[in] obj - pointer to obj3d struct
 * @param[in] x, y, z - pointer to coords
 */
void matrix_vector_multiply(float matrix_transform[3][3], float* x, float* y,
                            float* z) {
  float x_old = *x, y_old = *y, z_old = *z;
  *x = matrix_transform[0][0] * x_old + matrix_transform[0][1] * y_old +
       matrix_transform[0][2] * z_old;
  *y = matrix_transform[1][0] * x_old + matrix_transform[1][1] * y_old +
       matrix_transform[1][2] * z_old;
  *z = matrix_transform[2][0] * x_old + matrix_transform[2][1] * y_old +
       matrix_transform[2][2] * z_old;
}

// функция вращения объекта
/**
 * @brief object rotation
 * @param[in] angle - angle for rotation
 * @param[in] obj - pointer to obj3d struct
 * @param[in] type_of_coordinate - X, Y, Z/
 */
void rotate_object(float angle, obj3d* obj, int type_of_coordinate) {
  float sin_angle = sin(angle);
  float cos_angle = cos(angle);
  float matrixOfLinearOperator[3][3] = {0};
  // Матрица линейного оператора над пространством трехмерных векторов
  if (type_of_coordinate == X_CORD) {
    matrixOfLinearOperator[0][0] = 1;
    matrixOfLinearOperator[1][1] = cos_angle;
    matrixOfLinearOperator[1][2] = -sin_angle;
    matrixOfLinearOperator[2][1] = sin_angle;
    matrixOfLinearOperator[2][2] = cos_angle;
  } else if (type_of_coordinate == Y_CORD) {
    matrixOfLinearOperator[0][0] = cos_angle;
    matrixOfLinearOperator[0][2] = sin_angle;
    matrixOfLinearOperator[1][1] = 1;
    matrixOfLinearOperator[2][0] = -sin_angle;
    matrixOfLinearOperator[2][2] = cos_angle;
  } else {
    matrixOfLinearOperator[0][0] = cos_angle;
    matrixOfLinearOperator[0][1] = -sin_angle;
    matrixOfLinearOperator[1][0] = sin_angle;
    matrixOfLinearOperator[1][1] = cos_angle;
    matrixOfLinearOperator[2][2] = 1;
  }
  /*matrix_vector_multiply(matrixOfLinearOperator, &(obj->bounds.x_max),
                         &(obj->bounds.y_max), &(obj->bounds.z_max));*/
  /*matrix_vector_multiply(matrixOfLinearOperator, &(obj->bounds.x_min),
                         &(obj->bounds.y_min), &(obj->bounds.z_min));*/
  for (unsigned int i = 0; i < obj->vertexes_count * 3; i += 3) {
    matrix_vector_multiply(matrixOfLinearOperator, &(obj->vertexes[i]),
                           &(obj->vertexes[i + 1]), &(obj->vertexes[i + 2]));
  }
}
