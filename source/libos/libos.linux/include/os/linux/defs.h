#pragma once

#define XCONCAT(x, y)    x ## y
#define CONCAT(x, y)    XCONCAT(x, y)

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#else
#error __SIZE_TYPE__ is not defined!
#endif

#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __PTRDIFF_TYPE__ ssize_t;
#else
#error __PTRDIFF_TYPE__ is not defined!
#endif

typedef int pid_t;
struct pt_regs {
    long reg[8];
};
