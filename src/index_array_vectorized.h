#ifndef INDEX_MATH_H
#define INDEX_MATH_H

#include <stdbool.h>
#include <stdlib.h>

#endif

#ifndef INDEX_VECTOR_NAME
#error "Must define INDEX_VECTOR_NAME"
#endif

#ifndef INDEX_VECTOR_TYPE
#error "Must define INDEX_VECTOR_TYPE"
#endif

#ifndef OMP_PARALLEL_MIN_SIZE
#define OMP_PARALLEL_MIN_SIZE_DEFINED
#define OMP_PARALLEL_MIN_SIZE 1000
#endif

#define INDEX_VECTOR_CONCAT_(a, b) a ## b
#define INDEX_VECTOR_CONCAT(a, b) INDEX_VECTOR_CONCAT_(a, b)
#define INDEX_VECTOR_FUNC(name) INDEX_VECTOR_CONCAT(INDEX_VECTOR_NAME, _##name)

static inline void INDEX_VECTOR_FUNC(zero)(INDEX_VECTOR_TYPE *array, size_t n) {
    memset(array, 0, n * sizeof(INDEX_VECTOR_TYPE));
}

static inline void INDEX_VECTOR_FUNC(copy)(INDEX_VECTOR_TYPE * restrict dst, const INDEX_VECTOR_TYPE * restrict src, size_t n) {
    memcpy(dst, src, n * sizeof(INDEX_VECTOR_TYPE));
}

static inline void INDEX_VECTOR_FUNC(set)(INDEX_VECTOR_TYPE *array, INDEX_VECTOR_TYPE value, size_t n) {
    #pragma omp parallel for simd if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 0; i < n; i++) {
        array[i] = value;
    }
}

static inline INDEX_VECTOR_TYPE INDEX_VECTOR_FUNC(max)(INDEX_VECTOR_TYPE *array, size_t n) {
    if (n < 1) return (INDEX_VECTOR_TYPE) 0;
    INDEX_VECTOR_TYPE val = array[0];
    INDEX_VECTOR_TYPE max_val = val;
    #pragma omp parallel for simd reduction(max:max_val) if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 1; i < n; i++) {
        val = array[i];
        if (val > max_val) max_val = val;
    }
    return max_val;
}

static inline INDEX_VECTOR_TYPE INDEX_VECTOR_FUNC(min)(INDEX_VECTOR_TYPE *array, size_t n) {
    if (n < 1) return (INDEX_VECTOR_TYPE) 0;
    INDEX_VECTOR_TYPE val = array[0];
    INDEX_VECTOR_TYPE min_val = val;
    #pragma omp parallel for simd reduction(min:min_val) if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 1; i < n; i++) {
        val = array[i];
        if (val < min_val) min_val = val;
    }
    return min_val;
}

static inline int64_t INDEX_VECTOR_FUNC(argmax)(INDEX_VECTOR_TYPE *array, size_t n) {
    if (n < 1) return -1;
    INDEX_VECTOR_TYPE val = array[0];
    INDEX_VECTOR_TYPE max_val = val;
    int64_t argmax = 0;
    for (size_t i = 0; i < n; i++) {
        val = array[i];
        if (val > max_val) {
            max_val = val;
            argmax = i;
        }
    }
    return argmax;
}

static inline int64_t INDEX_VECTOR_FUNC(argmin)(INDEX_VECTOR_TYPE *array, size_t n) {
    if (n < 1) return (INDEX_VECTOR_TYPE) -1;
    INDEX_VECTOR_TYPE val = array[0];
    INDEX_VECTOR_TYPE min_val = val;
    int64_t argmin = 0;
    for (size_t i = 1; i < n; i++) {
        val = array[i];
        if (val < min_val) {
            min_val = val;
            argmin = i;
        }
    }
    return argmin;
}

static inline void INDEX_VECTOR_FUNC(add)(INDEX_VECTOR_TYPE *array, INDEX_VECTOR_TYPE c, size_t n) {
    #pragma omp parallel for simd if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 0; i < n; i++) {
        array[i] += c;
    }
}

static inline void INDEX_VECTOR_FUNC(sub)(INDEX_VECTOR_TYPE *array, INDEX_VECTOR_TYPE c, size_t n) {
    #pragma omp parallel for simd if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 0; i < n; i++) {
        array[i] -= c;
    }
}

static inline void INDEX_VECTOR_FUNC(add_vector)(INDEX_VECTOR_TYPE *a1, const INDEX_VECTOR_TYPE *a2, size_t n) {
    #pragma omp parallel for simd if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 0; i < n; i++) {
        a1[i] += a2[i];
    }
}

static inline void INDEX_VECTOR_FUNC(add_vector_scaled)(INDEX_VECTOR_TYPE *a1, const INDEX_VECTOR_TYPE *a2, double v, size_t n) {
    #pragma omp parallel for simd if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 0; i < n; i++) {
        a1[i] += a2[i] * v;
    }
}

static inline void INDEX_VECTOR_FUNC(sub_vector)(INDEX_VECTOR_TYPE *a1, const INDEX_VECTOR_TYPE *a2, size_t n) {
    #pragma omp parallel for simd if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 0; i < n; i++) {
        a1[i] -= a2[i];
    }
}


static inline void INDEX_VECTOR_FUNC(sub_vector_scaled)(INDEX_VECTOR_TYPE *a1, const INDEX_VECTOR_TYPE *a2, double v, size_t n) {
    #pragma omp parallel for simd if (n > OMP_PARALLEL_MIN_SIZE)
    for (size_t i = 0; i < n; i++) {
        a1[i] -= a2[i] * v;
    }
}

#undef INDEX_VECTOR_FUNC
#undef INDEX_VECTOR_CONCAT_
#undef INDEX_VECTOR_CONCAT

#ifdef OMP_PARALLEL_MIN_SIZE_DEFINED
#undef OMP_PARALLEL_MIN_SIZE
#undef OMP_PARALLEL_MIN_SIZE_DEFINED
#endif