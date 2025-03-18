#include "arg_parsing.h"

/* == Container type definitions == */
DEFINE_VEC(char, Chars)
DEFINE_VEC(Chars, Args)

/* == Public interface == */
Args parse_args(const char *str) {
    if(!str) {
        die("Invalid str!");
    }

    Args args = {0};
    if(!new_Args_with(&args, 3)) {
        die("Failure to construct Args struct!");
    }

    Chars chars = {0};
    if(!new_Chars_with(&chars, 3)) {
        die("Failure to construct Chars struct!");
    }

    for(; *str; ++str) {
        if(isspace(*str) || *str == ' ') {
            if(chars.vec_len > 0) {
                Args_insert(&args, chars);
                reset_chars(&chars);            
            }
        }

        else {
            Chars_insert(&chars, *str);
        }
    }

    if(chars.vec_len > 0) {
        Args_insert(&args, chars);
    }
    
    else {
        free(args.vec_data);
        args.vec_data = NULL;
    }

    return args;
}

char *args_get(const Args args, const size_t idx) {
    const size_t argc = args_len(args);
    if(idx >= argc) {
        LOG_MSG(L_ERROR, "Invalid index of %lu, should be less than %lu\n!", idx, argc);
        exit(1);
    }

    return args.vec_data[idx].vec_data;
}

void delete_args(Args *args) {
    if(!args) {
        die("Invalid args state!\n");
    }
    
    for(size_t i = 0; i < args_len(*args); ++i) {
        if(args->vec_data[i].vec_data) {
            free(args->vec_data[i].vec_data);
            args->vec_data[i].vec_data = NULL;
        }
    }

    free(args->vec_data);
    args->vec_data = NULL;
}

size_t args_len(const Args args) {
    return args.vec_len;
}

/* == Private interface == */
void die(const char *fmt) {
    LOG_MSG(L_ERROR, "%s\n", fmt);
    exit(1);
}

void reset_chars(Chars *chars) {
    if(!chars) {
        die("Invalid chars state!");
    }

    // can't do this, causes a UAF bug
    // if(chars->vec_data) {
    //     // deallocs prev vec_data before new alloc
    //     free(chars->vec_data);
    // }

    chars->vec_data = malloc(3);
    if(!chars->vec_data) {
        die("Failure to allocate space for: chars->vec_data");
    }

    chars->vec_cap = 3;
    chars->vec_len = 0;
}

