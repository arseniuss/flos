#include <cell/error.h>

#define ERROR_FUNC(errno) __error_##errno

#define ERROR_FUNC_DEF(errno, text) \
    string __error_##errno##_str(void); \
    error_s __error_##errno##_s  = { .str = __error_##errno##_str }; \
    error __error_##errno = &__error_##errno##_s; \
    string __error_##errno##_str(void) { \
        return string_c(text); \
    }

#define F(def, num, text)       ERROR_FUNC_DEF(def, text)

#include <cell/os/linux/errors.h>

#undef F

error os_linux_errno[] = {
#define UNIQUE
#define F(def, num, text)   [num] = &__error_##def##_s,

#include <cell/os/linux/errors.h>

#undef F
#undef UNIQUE
};


error *os_error = os_linux_errno;
