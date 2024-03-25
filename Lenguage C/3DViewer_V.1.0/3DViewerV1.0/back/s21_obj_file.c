/**
 * @file s21_obj_file.c
 * @brief Implementation of reading and working with .obj
* @details
* МАССИВЫ ОСНОВНЫЕ ПОНЯТИЯ МЕХАНИЗМА:
*
* 0) Введение:
* ======================================================
* Вся основная информация о массиве хранится в заголовке.
* Заголовок массива - первые два элемента массива
*
* Пример создания умного массива с помощью макроса array_push() наглядно:
* char arr = realloc(arr, 1 * 10)
*
* Представление в виде последовательности адрессов
*
* 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10
*
* arr == 0x0

* *arr // size == 0
*
* arr += 1; // меняем индексацию
*
* arr == 0x1 // эта ячейка теперь имеет индекс 0
*
* *arr // capacity == (10 - 2) == 8
*
* arr += 1; // аналогично меняем индексацию
*
* Измененная индексация массива
*
* arr == 0x2 // текущая ячейка массива индексирует другие начиная с себя от 0
*
* до 7 arr // текущее лженачало массива
*
* !!! Для того, чтобы пользователь мог спокойно получать данные, а не
* информацию о массиве, не сдвигаясь каждый раз на 2 ячейки вперед, мы храним в
* указателе адрес на элемент с адресом 2, то есть, при обращении к массиву с
* инструкцией сдвига на 0 ячеек и разыменования указателя, мы получим значение
* текущей ячейки 2
*
* array_push(arr, 2); // вызывает также изменение размера на 1
*
* Теперь при попытке сдвига на 0 ячеек результат будет равен значению элемента
* с индексом 2 arr[0] == 2
*
* 1) Задача умного массива сохранять основную информацию о себе:
* ======================================================
* - размер - текущее количество элементов заполненных значащими данными, а не
* мусором
* - вместимость - текущее количество элементов, которое может хранить массив,
* не включающее в себя два первых элемента (заголовок массива)
*
* 2) !!!Задача умного массива ограничить количество вызовов функции
* ======================================================
* перевыделения памяти, то есть зная размер и емкость, мы можем не выделять
* ======================================================
* память для массива с размером меньше его емкости (наполненности/вместимости)
* ======================================================
* 3) Задача умного массива упростить работу с массивом
* ======================================================
* 4) Недостатки - большее потребление памяти, чем для обычного из-за выделения
* ======================================================
* памяти всегда минимум на 18 ячеек и с размером 2 по 2 байта и остальных 8
* ======================================================
* байт
* ======================================================
* 5) Преимущества - легкость в использовании и доступность информации о
* ======================================================
* массиве
* ======================================================
 */

#include "s21_3d_viewer.h"

#define _array_header(_arr) \
  ((u_int *)(_arr)-2)  ///< перемещает указатель массива на  его подлинное
                       ///< начало
#define _array_size(_arr) \
  (_array_header(         \
      _arr)[0])  ///< помещает в качестве значения текущий размер массива
// он может быть меньше емкости или равно {пример: size 2 cap 7 arr = [1, 1, 0,
//  0, 0, 0, 0]}
#define _array_cap(_arr) (_array_header(_arr)[1])  ///<
// помещает в качестве значения текущую вместимость массива
// она может быть больше размера или равно {пример: size 2 cap 7 arr = [1, 1, 0,
// 0, 0, 0, 0]}
#define array_size(_arr) ((_arr) ? _array_size(_arr) : 0)  ///<
// помещает в качестве значения текущий размер массива, если его указатель null,
// то помещает 0 он может быть меньше емкости или равно {пример: size 2 cap 7
// arr = [1, 1, 0, 0, 0, 0, 0]}
#define array_cap(_arr)      \
  ((_arr) ? _array_cap(_arr) \
          : 0)  ///< помещает в качестве значения текущую вместимость массива,
                ///< если его указатель
// null, помещает 0 она может быть больше размера или равно
// {пример: size 2 cap 5 arr = [1, 1, 0, 0, 0, 0, 0]}
#define array_empty(_arr) (array_size(_arr) == 0)  ///<
// проверка массива на пустоту при 0 использованных ячеек или указателе с
// значением null помещает 1 иначе 0 {1 - true 0 - false}
#define _array_grow(_arr, _n) \
  (*((void **)&(_arr)) = array_realloc(_arr, _n, sizeof(*(_arr))))  ///<
// увеличивает вместимость текущего массива
// явное приведение параметра _arr к типу void ** и использование адреса
// указателя позволяет изменить значение указателя _arr внутри макроса
#define _array_ngrow(_arr, _n) \
  ((_arr) == 0 || (_array_size(_arr) + (_n) >= _array_cap(_arr)))  ///<
// проверка на возможность увеличения размера массива без перевыделения
// дополнительной памяти если возможно, то 0, иначе 1
// {0 - success, 1 - failure, _n - возможное кол-во новых данных}
#define _array_mgrow(_arr, _n) \
  (_array_ngrow(_arr, _n) ? (_array_grow(_arr, _n) != 0) : 1)  ///<
// увеличивем количество элементов массива - вместимость с учетом нового размера
// если возможно увеличить или вместимость превосходит возможный размер, то 1,
// иначе, если увеличить нельзя, то 0
#define array_clean(_arr) \
  ((_arr) ? mem_dealloc(_array_header(_arr)), 0 : 0)  ///<
// чистим массив начиная с загловка массива - первого адреса на ячейку памяти с
// индексом 0 в случае наличия не пустого указателя вызывается функция очистки
// памяти и возвращается результат 0, благодаря прописанию дополнительного
// действия ", 0", иначе 0 {0 - success}
#define array_push(_arr, _val)                                         \
  (_array_mgrow(_arr, 1)                                               \
       ? ((_arr)[_array_size(_arr)++] = (_val), _array_size(_arr) - 1) \
       : 0)  ///<
// добавляем новый элемент массива, если вместимость не позволяет или
// присваеваем новый элемент следующий после не мусорных элементов, если можно
// добавить новый элемент, то нет ответа, иначе 0 {0 - false, _val - добавляемое
// значение в следующий элемент после значащего в последовательности }

/** Эпсилоны для чисел типа float больше 0 в научной E и e нотациях, так как мы
 * ограничиваем максимальную степень до 20 */
static const double POWER_10_POS[MAX_POWER] = {
    1.0e0,  1.0e1,  1.0e2,  1.0e3,  1.0e4,  1.0e5,  1.0e6,
    1.0e7,  1.0e8,  1.0e9,  1.0e10, 1.0e11, 1.0e12, 1.0e13,
    1.0e14, 1.0e15, 1.0e16, 1.0e17, 1.0e18, 1.0e19,
};
/** Эпсилоны для чисел типа float меньше 0 в научной E и e нотациях, так как мы
 * ограничиваем максимальную степень до 20 */
static const double POWER_10_NEG[MAX_POWER] = {
    1.0e0,   1.0e-1,  1.0e-2,  1.0e-3,  1.0e-4,  1.0e-5,  1.0e-6,
    1.0e-7,  1.0e-8,  1.0e-9,  1.0e-10, 1.0e-11, 1.0e-12, 1.0e-13,
    1.0e-14, 1.0e-15, 1.0e-16, 1.0e-17, 1.0e-18, 1.0e-19,
};

static int incorrect_file = 0;

static void *mem_realloc(void *ptr, size_t bytes) {
  return realloc(ptr, bytes);
}

static void mem_dealloc(void *ptr) { free(ptr); }

static void *array_realloc(void *ptr, u_int n, u_int b) {
  // берем размер массива
  // считаем его новый размер
  // берем текущую вместимость
  // вычисляем новую вместимость {текущая * 1,5}
  u_int sz = array_size(ptr);
  u_int new_sz = sz + n;
  u_int cap = array_cap(ptr);
  u_int ncap = cap + cap / 2;
  u_int *res = NULL;

  // удостоверимся, что новой емкости для последующих расчетов хватит
  // {случаи использования, когда вместимости хватает мы не рассматриваем, так
  // как их нельзя реализовать пользователю данной библиотеки из-за ограничения
  // области видимости пользовательского интерфейса с помощью ключевого слова
  // static} иначе присвоим вместимости новый размер
  if (ncap < new_sz) ncap = new_sz;
  // выделям еще больше, чтобы не тратить временные ресурсы на последующее
  // выделение памяти {например, ncap 3 new_sz 3 ncap = (0..11 + 0..1111) &
  // ~0..1111 = 0..10010 & 1..11110000 = 32}
  // Минимальную вместимость выдает равную 16
  ncap = (ncap + 15) & ~15u;
  // перевыделяем память для проверочного указателя, если он равен null, то
  // память не выделилась или не может выделиться в полном объеме
  // выдаем количество памяти равное фактической вместимости
  // фактическая вместимость = вместимость * размер для данных + 2 * размер
  // информации о массиве
  res = (u_int *)(mem_realloc(ptr ? _array_header(ptr) : 0,
                              (size_t)b * ncap + 2 * sizeof(u_int)));
  if (!res) return 0;

  // заполняем заголовок массива текущий размер и вместимость
  // после возвращаем указатель на адрес 2 ячейки
  res[0] = sz;
  res[1] = ncap;

  return (res + 2);
}

/**
 * @brief init bounds of axis of the 3D object
 *
 * @param obj a pointer to the 3D object
 */
static void init_bounds_obj3d(obj3d *obj) {
  obj->bounds.x_min = 0;
  obj->bounds.x_max = 0;
  obj->bounds.y_min = 0;
  obj->bounds.y_max = 0;
  obj->bounds.z_min = 0;
  obj->bounds.z_max = 0;
}

/**
 * @brief init the 3D object
 *
 * @param obj a pointer to the 3D object
 */
static void init_obj3d(obj3d *obj) {
  obj->vertexes_count = 0;
  obj->faces_count = 0;
  obj->total_indexes = 0;
  obj->vertexes = 0;
  init_bounds_obj3d(obj);
  obj->polygons.indeces_count = 0;
  obj->polygons.vertexes_ind = 0;
}

/**
 * @brief set main data about object to the 3D object
 *
 * @param obj a pointer to the 3D object
 */
static void set_main_data_obj3d(obj3d *obj) {
  obj->vertexes_count = array_size(obj->vertexes) / 3;
  obj->faces_count = array_size(obj->polygons.indeces_count);
  obj->total_indexes = array_size(obj->polygons.vertexes_ind);
}

// printf("\nopened file: %s - ptr: %p\n", file_name, *file);
// fprintf(stderr, "\ncan't open file: %s\n", file_name);
// open obj file and print messeges
static void *open_obj_file(const char *file_name) {
  return fopen(file_name, "rb");
}

// close obj file and set ptr to file null
static void close_obj_file(FILE *file) {
  if (file) {
    fclose(file);
    file = NULL;
  }
}

static size_t read_obj_file(void *file, void *dst, size_t bytes) {
  FILE *f = NULL;

  f = (FILE *)(file);

  return fread(dst, 1, bytes, f);
}

static int is_whitespace(char c) {
  return (c == ' ' || c == '\t' || c == '\r');
}

static int is_newline(char c) { return (c == '\n'); }

static int is_digit(char c) { return (c >= '0' && c <= '9'); }

static int is_exponent(char c) { return (c == 'e' || c == 'E'); }

static const char *skip_whitespace(const char *ptr) {
  while (is_whitespace(*ptr)) {
    ptr++;
  }

  return ptr;
}

static const char *skip_line(const char *ptr) {
  while (!is_newline(*ptr++))
    ;

  return ptr;
}

/**
 * @brief compare and change bounds of axis in the 3D object
 *
 * @param data a pointer to the 3D object
 * @param x a value of new x coordinate
 * @param y a value of new y coordinate
 * @param z a value of new z coordinate
 */
static void compare_and_update_bounds(obj3d *data, float x, float y, float z) {
  if (data->bounds.x_min > x) {
    data->bounds.x_min = x;
  }
  if (data->bounds.x_max < x) {
    data->bounds.x_max = x;
  }
  if (data->bounds.y_min > y) {
    data->bounds.y_min = y;
  }
  if (data->bounds.y_max < y) {
    data->bounds.y_max = y;
  }
  if (data->bounds.z_min > z) {
    data->bounds.z_min = z;
  }
  if (data->bounds.z_max < z) {
    data->bounds.z_max = z;
  }
}

/**
 * @brief update values of the axises bounds in the 3D object
 *
 * @param data a pointer to the 3D object
 */
static void update_bounds(obj3d *data) {
  u_int sz = array_size(data->vertexes);
  float x = data->vertexes[sz - AX_DIMEN];
  float y = data->vertexes[sz - AX_DIMEN + 1];
  float z = data->vertexes[sz - AX_DIMEN + 2];

  if (sz > AX_DIMEN) {
    compare_and_update_bounds(data, x, y, z);
  } else {
    data->bounds.x_min = x;
    data->bounds.x_max = x;
    data->bounds.y_min = y;
    data->bounds.y_max = y;
    data->bounds.z_min = z;
    data->bounds.z_max = z;
  }
}

static const char *parse_int(const char *ptr, int *val) {
  int sign = 0;
  int num = 0;

  if (*ptr == '-') {
    sign = -1;
    ptr++;
  } else {
    sign = +1;
  }

  if (val != NULL) {
    num = 0;
    while (is_digit(*ptr)) {
      num = 10 * num + (*ptr++ - '0');
    }
    *val = sign * num;
  } else {
    while (is_digit(*ptr)) {
      ptr++;
    }
  }

  return ptr;
}

static double get_sign_and_skip_explic_sgn_fl(const char **ptr) {
  double sign = 0.0;

  switch (**ptr) {
    case '+':
      sign = 1.0;
      (*ptr)++;
      break;

    case '-':
      sign = -1.0;
      (*ptr)++;
      break;

    default:
      sign = 1.0;
      break;
  }

  return sign;
}

static const char *parse_fl_int_part(const char *ptr, double *num) {
  while (is_digit(*ptr)) {
    *num = 10.0 * *num + (double)(*ptr++ - '0');
  }

  return ptr;
}

static const char *parse_fl_fra_part(const char *ptr, double *num) {
  double fra = 0.0;
  double div = 1.0;

  while (is_digit(*ptr)) {
    fra = 10.0 * fra + (double)(*ptr++ - '0');
    div *= 10.0;
  }

  *num += fra / div;

  return ptr;
}

static int is_neg_e_skip_neg_sign_fl(const char **ptr) {
  int res = FALSE;
  (*ptr)++;
  switch (*(*ptr)) {
    case '+':
      (*ptr)++;
      break;

    case '-':
      res = TRUE;
      (*ptr)++;
      break;

    default:
      break;
  }

  return res;
}

static const char *parse_float(const char *ptr, float *val) {
  double sign = 0.0, num = 0.0;
  u_int eval = 0;
  const double *powers = NULL;

  ptr = skip_whitespace(ptr);

  sign = get_sign_and_skip_explic_sgn_fl(&ptr);
  ptr = parse_fl_int_part(ptr, &num);

  if (*ptr == '.') {
    ptr++;
  }

  ptr = parse_fl_fra_part(ptr, &num);

  if (is_exponent(*ptr)) {
    if (is_neg_e_skip_neg_sign_fl(&ptr)) {
      powers = POWER_10_POS;
    } else {
      powers = POWER_10_NEG;
    }

    while (is_digit(*ptr)) eval = 10 * eval + (*ptr++ - '0');

    num *= (eval >= MAX_POWER) ? 0.0 : powers[eval];
  }

  *val = (float)(sign * num);

  return ptr;
}

static const char *parse_vertex(obj3d *data, const char *ptr) {
  u_int i = 0;
  float v = 0.0;

  for (i = 0; i < AX_DIMEN; i++) {
    ptr = parse_float(ptr, &v);
    array_push(data->vertexes, v);
  }
  update_bounds(data);

  return ptr;
}

static const char *parse_face(obj3d *data, const char *ptr) {
  u_int v_ind_count = 0;
  u_int v_index = 0;
  int v = 0;

  ptr = skip_whitespace(ptr);
  while (!is_newline(*ptr)) {
    v = 0;
    ptr = parse_int(ptr, &v);
    if (*ptr == '/') {
      ptr++;
      if (*ptr != '/') ptr = parse_int(ptr, NULL);
      if (*ptr == '/') {
        ptr++;
        ptr = parse_int(ptr, NULL);
      }
    }

    // add vertexe index to array of indeces
    if (v < 0) {
      v_index = (array_size(data->vertexes) / 3) - (u_int)(-v);
    } else if (v == 0) {
      incorrect_file = 1;
      break;
    } else {
      v_index = (u_int)(v);
    }

    array_push(data->polygons.vertexes_ind, v_index);
    v_ind_count++;

    ptr = skip_whitespace(ptr);
  }
  array_push(data->polygons.indeces_count, v_ind_count);

  return ptr;
}

static const char *check_v_after_parse_vertex(obj3d *data, const char *ptr) {
  ptr++;
  switch (*ptr++) {
    case ' ':
    case '\t':
      ptr = parse_vertex(data, ptr);
      break;

    case 't':
      break;
    case 'n':
      break;

    default:
      ptr--; /* roll p++ back in case *p was a newline */
  }

  return ptr;
}

static const char *check_f_after_parse_face(obj3d *data, const char *ptr) {
  ptr++;
  switch (*ptr++) {
    case ' ':
    case '\t':
      ptr = parse_face(data, ptr);
      break;

    default:
      ptr--; /* roll p++ back in case *p was a newline */
  }

  return ptr;
}

static void parse_buffer(obj3d *data, const char *ptr, const char *end) {
  const char *p = NULL;

  p = ptr;

  while (p != end) {
    p = skip_whitespace(p);
    switch (*p) {
      case 'v':
        p = check_v_after_parse_vertex(data, p);
        break;

      case 'f':
        p = check_f_after_parse_face(data, p);
        break;

      case 'o':
        break;
      case 'g':
        break;
      case 'm':
        break;
      case 'u':
        break;
      case '#':
        break;
    }

    p = skip_line(p);
  }
}

static void copy_overflow_to_next_buffer(char **buffer, char **last,
                                         u_int *bytes, char **start,
                                         char **end) {
  *bytes = (u_int)(*end - *last);
  memmove(*buffer, *last, *bytes);
  *start = *buffer + *bytes;
}

obj3d *parse_obj_file(const char *path) {
  obj3d *obj = NULL;
  void *file = NULL;
  char *buffer = NULL;  // буфер
  char *start = NULL;   // начало буфера
  char *end = NULL;     // конец буфера
  char *last = NULL;
  u_int read = 0;
  u_int bytes = 0;

  // Открытие файла
  file = open_obj_file(path);
  if (!file) return 0;
  // Создание пустого 3d объекта
  obj = (obj3d *)(mem_realloc(0, sizeof(obj3d)));
  if (!obj) return 0;
  // Зануление данных
  init_obj3d(obj);
  // Создание буфера для чтения данных
  buffer = (char *)(mem_realloc(NULL, 2 * BUFFER_SIZE * sizeof(char)));
  if (!buffer) return 0;
  start = buffer;
  while (1) {
    // Считываем количество байт из файла (медленно обращаемся к диску)
    read = (u_int)(read_obj_file(file, start, BUFFER_SIZE));
    // проверка на пустоту
    if (read == 0 && start == buffer) break;
    // Обеспечиваем окончание буфера на символ новой строки '\n'
    if (read < BUFFER_SIZE) {
      if (read == 0 || start[read - 1] != '\n') start[read++] = '\n';
    }
    // Находим конец буфера
    end = start + read;
    if (end == buffer) break;
    // Ищем последнюю новую строку
    last = end;
    while (last > buffer) {
      last--;
      if (*last == '\n') break;
    }
    // Проверяем имеется ли там новая строка
    if (*last != '\n') break;
    last++;
    // Использование буфера для парсинга
    parse_buffer(obj, buffer, last);
    // Копируем переполненные ячейки для следующего буфера
    copy_overflow_to_next_buffer(&buffer, &last, &bytes, &start, &end);
  }
  // Вычисляем основные данные о количестве вершин/фейсов/всех индексов
  set_main_data_obj3d(obj);
  // Удаляем буфер из RAM
  mem_dealloc(buffer);
  // Закрываем файл
  close_obj_file(file);

  return obj;
}

static void set_first_lesser_and_second_greater(u_int *first, u_int *second) {
  if (*first > *second) {
    u_int temp = *first;
    *first = *second;
    *second = temp;
  }
}

static u_int get_one_if_new_edge(u_int index1, u_int index2,
                                 u_int ***unique_edges) {
  int is_have_in_set = 0;

  if ((*unique_edges)[index1 - 1] != NULL) {
    for (u_int v = 0; v < array_size((*unique_edges)[index1 - 1]); v++) {
      if ((*unique_edges)[index1 - 1][v] == index2) {
        is_have_in_set = 1;
        v = array_size((*unique_edges)[index1 - 1]);
      }
    }
    if (!is_have_in_set) {
      array_push((*unique_edges)[index1 - 1], index2);
    }
  } else {
    array_push((*unique_edges)[index1 - 1], index2);
  }
  return !is_have_in_set ? 1 : 0;
}

u_int get_count_edges(obj3d *obj) {
  u_int edges_count = 0;
  if (!obj || incorrect_file) {
    incorrect_file = 0;
    return edges_count;
  }
  u_int faces_count = obj->faces_count;
  u_int vertexes_count = obj->vertexes_count;
  u_int *indices_counts = obj->polygons.indeces_count;
  u_int *copy_indices = obj->polygons.vertexes_ind;
  int first_and_last = 1;

  // matrix (not smart 2 dimensional array of smart arrays)
  u_int **unique_edges = (u_int **)malloc(vertexes_count * sizeof(u_int *));
  if (!unique_edges) return edges_count;

  for (u_int i = 0; i < vertexes_count; i++) unique_edges[i] = 0;
  // main range
  for (u_int i = 0; i < faces_count; i++) {
    // face cross
    for (u_int j = 0; j < indices_counts[i]; j++) {
      if (first_and_last) {
        u_int ind1 = *copy_indices;
        u_int ind2 = *((copy_indices += indices_counts[i] - 1));
        set_first_lesser_and_second_greater(&ind1, &ind2);
        edges_count += get_one_if_new_edge(ind1, ind2, &unique_edges);
        first_and_last = 0;
        copy_indices -= indices_counts[i] - 1;
      } else {
        u_int ind1 = *copy_indices, ind2 = *(++copy_indices);
        set_first_lesser_and_second_greater(&ind1, &ind2);
        edges_count += get_one_if_new_edge(ind1, ind2, &unique_edges);
      }
    }
    first_and_last = 1;
    ++copy_indices;
  }
  for (u_int i = 0; i < vertexes_count; i++) array_clean(unique_edges[i]);
  free(unique_edges);

  return edges_count;
}

void obj_destroy(obj3d *obj) {
  array_clean(obj->vertexes);
  array_clean(obj->polygons.vertexes_ind);
  array_clean(obj->polygons.indeces_count);

  mem_dealloc(obj);
}
