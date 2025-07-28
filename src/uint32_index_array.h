#ifndef INDEX_ARRAY_UINT32_ALIGNED_H
#define INDEX_ARRAY_UINT32_ALIGNED_H

#include <stdlib.h>
#include <stdint.h>

#define ARRAY_NAME uint32_index_array
#define ARRAY_TYPE uint32_t
#include "aligned_array/aligned_array.h"
#include "array/sort.h"
#undef ARRAY_NAME
#undef ARRAY_TYPE

#define INDEX_VECTOR_NAME uint32_index_vector
#define INDEX_VECTOR_TYPE uint32_t
#include "index_array_vectorized.h"
#undef INDEX_VECTOR_NAME
#undef INDEX_VECTOR_TYPE

#endif
