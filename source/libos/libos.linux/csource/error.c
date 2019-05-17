#include <cell/error.h>

#define ERROR_FUNC(errno) __error_##errno

#define ERROR_FUNC_DEF(errno, text) \
    cell_string __error_##errno##_str(void); \
    cell_error __error_##errno  = { .string = &__error_##errno##_str }; \
    cell_string __error_##errno##_str(void) { \
        return cell_string_c(text); \
    }

#define F(def, num, text)       ERROR_FUNC_DEF(def, text)

#include <cell/os/linux/errors.h>

#undef F

cell_error *os_linux_errno[] = {
#define UNIQUE
#define F(def, num, text)   [num] = &__error_##def,

#include <cell/os/linux/errors.h>

#undef F
#undef UNIQUE
};


cell_error **os_error = os_linux_errno;
