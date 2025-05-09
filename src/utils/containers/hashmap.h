/* 
Notes:
* If collision algorithm changes to quadratic probing, then change reallocation size strategy
* Update to use optional types to implement functions
*/

#ifndef _GENERIC_HASHMAP_H_
#define _GENERIC_HASHMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_HASHMAP_CAP 32

#define DECL_HASHMAP(NAME, K, V)                                                                                \
    typedef struct {                                                                                            \
        K key;                                                                                                  \
        V val;                                                                                                  \
        bool is_used;                                                                                           \
    } NAME##_entry_t;                                                                                           \
                                                                                                                \
    typedef struct {                                                                                            \
        NAME##_entry_t *entries;                                                                                \
        size_t entries_len, entries_cap;                                                                        \
    } NAME;                                                                                                     \
                                                                                                                \
    bool new_##NAME(NAME *);                                                                                    \
    bool NAME##_reserve(NAME *, size_t);                                                                        \
    bool NAME##_resize(NAME *);                                                                                 \
    bool NAME##_insert(NAME *, K, V);                                                                           \
    bool NAME##_get(const NAME *, K, V *);                                                                      \
    bool NAME##_get_entry(const NAME *, K, NAME##_entry_t **);                                                  \
    bool NAME##_update(NAME *, K, V);                                                                           \
    bool NAME##_delete(NAME *, K);                                                                              \
    bool destroy_##NAME(NAME *);                                                                                \


#define DEFINE_HASHMAP(NAME, K, V, HASH, IS_EQUAL, FREE_KEY, FREE_VAL)                                          \
    bool new_##NAME(NAME *hashmap) {                                                                            \
        if(!hashmap) {                                                                                          \
            fprintf(stderr, "[in new_%s()]: Failure to allocate new hashmap, invalid hashmap state!\n", #NAME); \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        NAME##_entry_t *entries = malloc(DEFAULT_HASHMAP_CAP * sizeof(*entries));                               \
        if(!entries) {                                                                                          \
            fprintf(stderr, "[in new_%s()]: Failure to allocate space for entries / buckets!\n", #NAME);        \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        *hashmap = (NAME) {                                                                                     \
            .entries = entries,                                                                                 \
            .entries_len = 0,                                                                                   \
            .entries_cap = DEFAULT_HASHMAP_CAP                                                                  \
        };                                                                                                      \
                                                                                                                \
        return true;                                                                                            \
    }                                                                                                           \
                                                                                                                \
    bool NAME##_reserve(NAME *hashmap, size_t cap) {                                                            \
        if(!hashmap) {                                                                                          \
            fprintf(stderr, "[in new_%s()]: Failure to allocate new hashmap, invalid hashmap state!\n", #NAME); \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        if(!cap ||hashmap->entries_cap >= cap) {                                                                \
            return true;                                                                                        \
        }                                                                                                       \
                                                                                                                \
        NAME##_entry_t *entries = malloc(cap * sizeof(*entries));                                               \
        if(!entries) {                                                                                          \
            fprintf(stderr, "[in new_%s()]: Failure to allocate space for entries / buckets!\n", #NAME);        \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        *hashmap = (NAME) {                                                                                     \
            .entries = entries,                                                                                 \
            .entries_len = 0,                                                                                   \
            .entries_cap = cap                                                                                  \
        };                                                                                                      \
                                                                                                                \
        return true;                                                                                            \
    }                                                                                                           \
                                                                                                                \
    bool NAME##_resize(NAME *hashmap) {                                                                         \
        if(!hashmap || !hashmap->entries) {                                                                     \
            fprintf(stderr, "[in %s_resize()]: Failed to resize, invalid hashmap state!\n", #NAME);             \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        size_t prev_cap = hashmap->entries_cap;                                                                 \
        NAME##_entry_t *prev_entries = hashmap->entries;                                                        \
                                                                                                                \
       hashmap->entries_cap *= 2;                                                                               \
       hashmap->entries = malloc(hashmap->entries_cap * sizeof(*hashmap->entries));                             \
        if(!hashmap->entries) {                                                                                 \
            fprintf(stderr, "[in %s_resize()]: Failure to dynamically resize, malloc failure!\n", #NAME);       \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        hashmap->entries_len = 0;                                                                               \
        for(size_t i = 0; i < prev_cap; ++i) {                                                                  \
            if(prev_entries[i].is_used) {                                                                       \
                NAME##_insert(hashmap, prev_entries[i].key, prev_entries[i].val);                               \
            }                                                                                                   \
        }                                                                                                       \
                                                                                                                \
        free(prev_entries);                                                                                     \
        return true;                                                                                            \
    }                                                                                                           \
                                                                                                                \
    bool NAME##_insert(NAME *hashmap, K key, V val) {                                                           \
        if(!hashmap || !hashmap->entries) {                                                                     \
            fprintf(stderr, "[in %s_insert()]: Failure to insert, invalid hashmap state!\n", #NAME);            \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        if(hashmap->entries_len == hashmap->entries_cap) {                                                      \
            if(!NAME##_resize(hashmap)) {                                                                       \
                fprintf(stderr, "[in %s_insert()]: Failure to resize hashmap!\n", #NAME);                       \
                return false;                                                                                   \
            }                                                                                                   \
        }                                                                                                       \
                                                                                                                \
        size_t entry_idx = HASH(key) % hashmap->entries_cap;                                                    \
        while(hashmap->entries[entry_idx].is_used) {                                                            \
            entry_idx = (entry_idx + 1) % hashmap->entries_cap;                                                 \
        }                                                                                                       \
                                                                                                                \
        hashmap->entries[entry_idx] = (NAME##_entry_t) {                                                        \
            .key   = key,                                                                                       \
            .val   = val,                                                                                       \
            .is_used = true                                                                                     \
        };                                                                                                      \
        hashmap->entries_len += 1;                                                                              \
                                                                                                                \
        return true;                                                                                            \
    }                                                                                                           \
                                                                                                                \
    bool NAME##_get_entry(const NAME *hashmap, K key, NAME##_entry_t **found_entry) {                           \
        if(!hashmap || !hashmap->entries) {                                                                     \
            fprintf(stderr, "[in %s_get_entry()]: Invalid hashmap state", #NAME);                               \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        size_t entry_idx = HASH(key) % hashmap->entries_cap;                                                    \
        while(hashmap->entries[entry_idx].is_used) {                                                            \
            if(is_equal(key, hashmap->entries[entry_idx].key)) {                                                \
                *found_entry = &hashmap->entries[entry_idx];                                                    \
                return true;                                                                                    \
            }                                                                                                   \
                                                                                                                \
            entry_idx = (entry_idx + 1) % hashmap->entries_cap;                                                 \
        }                                                                                                       \
                                                                                                                \
        return false;                                                                                           \
    }                                                                                                           \
                                                                                                                \
    bool NAME##_get(const NAME *hashmap, K key, V *found_val) {                                                 \
        if(!hashmap || !hashmap->entries) {                                                                     \
            fprintf(stderr, "[in %s_get()]: Invalid hashmap state!\n", #NAME);                                  \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        NAME##_entry_t *found_entry = NULL;                                                                     \
        bool has_entry = NAME##_get_entry(hashmap, key, &found_entry);                                          \
        if(!has_entry) {                                                                                        \
            return false;                                                                                       \
        }                                                                                                       \
        *found_val = found_entry->val;                                                                          \
                                                                                                                \
        return true;                                                                                            \
    }                                                                                                           \
                                                                                                                \
    bool NAME##_update(NAME *hashmap, K key, V new_val) {                                                       \
        if(!hashmap || !hashmap->entries) {                                                                     \
            fprintf(stderr, "[in %s_update()]: Invalid hashmap state!\n", #NAME);                               \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        NAME##_entry_t *found_entry = NULL;                                                                     \
        bool has_entry = NAME##_get_entry(hashmap, key, &found_entry);                                          \
        if(!has_entry) {                                                                                        \
            return false;                                                                                       \
        }                                                                                                       \
        found_entry->val = new_val;                                                                             \
                                                                                                                \
        return true;                                                                                            \
    }                                                                                                           \
                                                                                                                \
    bool NAME##_delete(NAME *hashmap, K key)  {                                                                 \
        if(!hashmap || !hashmap->entries) {                                                                     \
            fprintf(stderr, "[in %s_delete()]: Invalid hashmap state!\n", #NAME);                               \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        NAME##_entry_t *found_entry = NULL;                                                                     \
        bool has_entry = NAME##_get_entry(hashmap, key, &found_entry);                                          \
        if(!has_entry) {                                                                                        \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        FREE_KEY(found_entry->key);                                                                             \
        FREE_VAL(found_entry->val);                                                                             \
                                                                                                                \
        found_entry->key = (K){0};                                                                              \
        found_entry->val = (V){0};                                                                              \
        found_entry->is_used = false;                                                                           \
        hashmap->entries_len -= 1;                                                                              \
                                                                                                                \
        return true;                                                                                            \
    }                                                                                                           \
                                                                                                                \
    bool destroy_##NAME(NAME *hashmap) {                                                                        \
        if(!hashmap || !hashmap->entries) {                                                                     \
            fprintf(stderr, "[in destroy_%s()]: Failure to destroy, invalid hashmap state!\n", #NAME);          \
            return false;                                                                                       \
        }                                                                                                       \
                                                                                                                \
        for(size_t i = 0; i < hashmap->entries_cap; ++i) {                                                      \
            if(hashmap->entries[i].is_used) {                                                                   \
                FREE_KEY(hashmap->entries[i].key);                                                              \
                FREE_VAL(hashmap->entries[i].val);                                                              \
            }                                                                                                   \
        }                                                                                                       \
                                                                                                                \
        free(hashmap->entries);                                                                                 \
                                                                                                                \
        return true;                                                                                            \
    }                                                                                                           \

#endif

