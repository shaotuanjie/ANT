/* Copyright (c) 2017-2020 SKKU ESLAB, and contributors. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ant_ml_native_internal.h"
#include "../../../common/native/ant_common.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void ant_ml_getMaxOfBuffer_internal_uint8(const unsigned char *data_array,
                                          size_t data_array_len,
                                          int *result_max_index,
                                          unsigned char *result_value) {
  unsigned char max_value = 0;
  int max_index = -1;

  int i;
  for (i = 0; i < (int)data_array_len; i++) {
    unsigned char item = data_array[i];
    if (item > max_value) {
      max_value = item;
      max_index = i;
    }
  }
  *result_max_index = max_index;
  *result_value = max_value;
}

void ant_ml_getMaxOfBuffer_internal_int32(const long *data_array,
                                          size_t data_array_len,
                                          int *result_max_index,
                                          long *result_value) {
  long max_value = 0;
  int max_index = -1;

  int i;
  for (i = 0; i < (int)data_array_len; i++) {
    long item = data_array[i];
    if (item > max_value) {
      max_value = item;
      max_index = i;
    }
  }
  *result_max_index = max_index;
  *result_value = max_value;
}

void ant_ml_getMaxOfBuffer_internal_float32(const float *data_array,
                                            size_t data_array_len,
                                            int *result_max_index,
                                            float *result_value) {
  float max_value = 0;
  int max_index = -1;

  int i;
  for (i = 0; i < (int)data_array_len; i++) {
    float item = data_array[i];
    if (item > max_value) {
      max_value = item;
      max_index = i;
    }
  }
  *result_max_index = max_index;
  *result_value = max_value;
}

void initANTML(void) {
  // Empty function
}