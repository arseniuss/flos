/**
 *   Builtin library for cell language
 *   Copyright (C) 2017 - 2019 Armands Arseniuss Skolmeisters
 *
 *   This library is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this library  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __CELL__SLICE_H__
#    define __CELL__SLICE_H__

#    include <cell/type.h>
#    include <cell/error.h>

// module builtin.slice

#    define cell_array_sliceof(__arr, __start, __end, __name) \
    typedef __arr##_type __name##_type; \
    typedef struct { __arr##_type* buf; cell_size cap; cell_size len; } __name##_slice_type; \
    __name##_slice_type __name = { .buf = &__arr.buf[__start], .cap = __arr.len - __start, .len = __end - __start + 1  };

#    define coounter(x) x##__COUNTER__

#    define cell_slice_append(__slice, __value, __ret) \
    typeof(__value) ptr##__COUNTER__ = __value; \
    __cell_slice_append(\
        (cell_slice_type *)&(__slice), \
        sizeof(__slice##_type), \
        (void *)&ptr##__COUNTER__, \
        (cell_slice_type *)&(__ret)\
    );


#    define cell_slice_for(__e, __name) \
    cell_size __name##_it = 0; \
    for(__name##_type __e = __name.buf[0]; __name##_it != __name.len;__e = __name.buf[++__name##_it])

#    define cell_slice_for3(__i, __e, __name) \
    cell_size __i = 0; \
    for(__name##_type __e = __name.buf[0]; __i != __name.len;__e = __name.buf[++__i])

typedef struct {
    cell_byte *buf;
    cell_size cap;
    cell_size len;
} cell_slice_type;

cell_error __cell_slice_append(cell_slice_type * s, cell_size elem_size, void *value, cell_slice_type * ret);

#endif /* !__CELL__BUILTIN_SLICE_H__ */
