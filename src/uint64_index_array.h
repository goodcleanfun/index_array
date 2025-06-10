#ifndef INDEX_ARRAY_UINT64_H
#define INDEX_ARRAY_UINT64_H

#include <stdlib.h>
#include <stdint.h>

#define ARRAY_NAME uint64_index_array
#define ARRAY_TYPE uint64_t
#include "aligned_array/aligned_array.h"
#include "array/sort.h"
#undef ARRAY_NAME
#undef ARRAY_TYPE

#endif
