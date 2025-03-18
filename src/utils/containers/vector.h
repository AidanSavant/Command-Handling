#ifndef GENERIC_VEC_H_
#define GENERIC_VEC_H_

#define DEFAULT_VEC_CAP 32
 
#define DECL_VEC(T, NAME)                                                                                   \
    typedef struct {                                                                                        \
       T *vec_data;                                                                                         \
       size_t vec_len, vec_cap;                                                                             \
    } NAME;                                                                                                 \
                                                                                                            \
    bool new_##NAME(NAME *);                                                                                \
    bool new_##NAME##_with(NAME *, size_t);                                                                 \
    bool NAME##_insert(NAME *, T);                                                                          \
    size_t NAME##_get(const NAME *, T, bool (*)(T, T));                                                     \
    void NAME##_printer(const NAME *vec, void (*)(T));                                                      \
    bool delete_##NAME(NAME *);                                                                             \

#define DEFINE_VEC(T, NAME)                                                                                 \
    bool new_##NAME(NAME *vec) {                                                                            \
        if(!vec) {                                                                                          \
            fprintf(stderr, "[in new_%s()]: invalid vector state!\n", #NAME);                               \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        T *vec_data = malloc(DEFAULT_VEC_CAP * sizeof(*vec_data));                                          \
        if(!vec_data) {                                                                                     \
            fprintf(stderr, "[in new_%s()]: failure to allocate internal array!\n", #NAME);                 \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        *vec = (NAME) {                                                                                     \
            .vec_data = vec_data,                                                                           \
            .vec_len = 0,                                                                                   \
            .vec_cap = DEFAULT_VEC_CAP                                                                      \
        };                                                                                                  \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \
                                                                                                            \
    bool new_##NAME##_with(NAME *vec, size_t cap) {                                                         \
        if(!vec) {                                                                                          \
            fprintf(stderr, "[in %s_reserve()]: invalid vec state!\n", #NAME);                              \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        T *vec_data = malloc(cap * sizeof(*vec_data));                                                      \
        if(!vec_data) {                                                                                     \
            fprintf(stderr, "[in %s_reserve()]: failure to allocate internal array!\n", #NAME);             \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        *vec = (NAME) {                                                                                     \
            .vec_data = vec_data,                                                                           \
            .vec_len = 0,                                                                                   \
            .vec_cap = cap                                                                                  \
        };                                                                                                  \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \
                                                                                                            \
    bool NAME##_insert(NAME *vec, T data) {                                                                 \
        if(!vec || !vec->vec_data) {                                                                        \
           fprintf(stderr, "[in %s_insert()]: invalid vector state!\n", #NAME);                             \
           return false;                                                                                    \
        }                                                                                                   \
                                                                                                            \
        if(vec->vec_len == vec->vec_cap) {                                                                  \
            vec->vec_cap *= 2;                                                                              \
            vec->vec_data = realloc(vec->vec_data, vec->vec_cap * sizeof(T));                               \
                                                                                                            \
            if(!vec->vec_data) {                                                                            \
                fprintf(stderr, "[in %s_insert()]: failure to resize internal array in vector!\n", #NAME);  \
                return false;                                                                               \
           }                                                                                                \
        }                                                                                                   \
                                                                                                            \
        vec->vec_data[vec->vec_len] = data;                                                                 \
        vec->vec_len += 1;                                                                                  \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \
                                                                                                            \
    size_t NAME##_get(const NAME *vec, T data, bool (*cmper)(T, T)) {                                       \
        if(!vec->vec_data || !vec->vec_cap) {                                                               \
            fprintf(stderr, "[in %s_get()]: invalid vector state!\n", #NAME);                               \
            return -1;                                                                                      \
        }                                                                                                   \
                                                                                                            \
        for(size_t i = 0; i < vec->vec_len; ++i) {                                                          \
            if(cmper(vec->vec_data[i], data)) {                                                             \
                return i;                                                                                   \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        return -1;                                                                                          \
    }                                                                                                       \
                                                                                                            \
    void NAME##_printer(const NAME *vec, void (*printer)(T)) {                                              \
      for(size_t i = 0; i < vec->vec_len; ++i) {                                                            \
          printer(vec->vec_data[i]);                                                                        \
      }                                                                                                     \
    }                                                                                                       \
                                                                                                            \
    bool delete_##NAME(NAME *vec) {                                                                         \
        if(!vec || !vec->vec_data) {                                                                        \
            fprintf(stderr, "[in delete_%s()]: Invalid vector state!\n", #NAME);                            \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        free(vec->vec_data);                                                                                \
        vec->vec_data = NULL;                                                                               \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \

#endif

