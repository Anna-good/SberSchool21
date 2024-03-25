/**
 * @file s21_3d_viewer.h
 * @author Team (TL: victarim@student.21-school.ru)
 * sustaint@student.21-school.ru
 * ventresi@student.21-school.ru
 * @brief s21 3dvewer header
 * @version 0.1
 * @date 2023-09-06
 *cd
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SRC_3D_VIEWERV1_0_BACK_S21_3D_VIEWER_H_
#define SRC_3D_VIEWERV1_0_BACK_S21_3D_VIEWER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief  Collection of boolean values
 */
typedef enum { FALSE, TRUE } BOOLEAN;

/**
 * @brief  Collection of coordinate types
 */
typedef enum { X_CORD, Y_CORD, Z_CORD } TYPE_OF_CORD;

#define AX_DIMEN 3         ///< Axises dimensional for X Y Z
#define BUFFER_SIZE 65536  ///< Size of buffer to reading file into RAM
#define MAX_POWER 20       ///< Max power for float parsing

typedef unsigned int u_int;  ///< alias of type unsigned int

/**
 * @brief Data about indexes for polygons
 *
 */
typedef struct {
  u_int* indeces_count;  ///< counts of vertexes which need to make polygon
  u_int* vertexes_ind;   ///< indexes of vertexes which need use to make polygon
} polygon_t;

/**
 * @brief Data about min and max value of axis x y z, which need to rescale 3D
 * object
 *
 */
typedef struct {
  float x_min;
  float x_max;
  float y_min;
  float y_max;
  float z_min;
  float z_max;
} axises;

/**
 * @brief obj3d struct, contains all important info about 3D object
 *
 */
typedef struct {
  u_int vertexes_count;  ///< count of vertexes
  u_int faces_count;     ///< count of faces
  u_int total_indexes;   ///< total count of indices
  float* vertexes;       ///< 1-dimensional array of vertexes
  polygon_t polygons;    //< obj of polygons_t, contains array of vertex indices
                         // and indices counts
  axises bounds;  //< obj of axises, contains bounds for axises X Y Z to make it
                  // possible to rescale 3D object
} obj3d;

/**
 * @brief parse .obj file and returns a pointer to the 3D object
 *
 * @param[in] path a path to the .obj file
 * @return[out] obj3d*
 */
obj3d* parse_obj_file(const char* path);
/**
 * @brief free memory from the 3D object
 *
 * @param[in] obj a pointer to the 3D object
 */
void obj_destroy(obj3d* obj);

/**
 * @brief count obj3d edges and return it
 *
 * @param[in] obj the 3D object
 * @return[out] u_int
 */
u_int get_count_edges(obj3d* obj);

/*---------------------------affine transformations-----------------*/
/**
 * @brief functions for affine transformations
 */
int scaleObjBeforeDraw(float scaleForDraw, obj3d* obj);
int maxDistanceAxies(obj3d* obj, float* result);
void scaleApply(float scale, obj3d* obj);
void move_coordinate(float move_value, obj3d* obj, int type_of_coordinate);
void matrix_vector_multiply(float matrix_transform[3][3], float* x, float* y,
                            float* z);
void rotate_object(float angle, obj3d* obj, int type_of_coordinate);
void moveToCenter(obj3d* obj);

#ifdef __cplusplus
}
#endif

#endif  // SRC_3D_VIEWERV_1_0_BACK_S21_VIEWER_H_
