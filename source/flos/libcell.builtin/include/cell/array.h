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

#ifndef __CELL__ARRAY_H__
#    define __CELL__ARRAY_H__

#    include <cell/type.h>

// module builtin.array

#    define cell_array(_type) \
    typeof(struct{_type* buf; cell_size len;})

#    define cell_array_make(__name, __len, __type) \
    typedef __type __name##_type; \
    typedef struct { __type* buf;  cell_size len; } __name##_array_type; \
    __name##_array_type __name = { .len = __len, .buf = cell_mem_salloc(__len * sizeof(__type)) }; \
    __builtin_memset((void *)__name.buf, 0, __len);


typedef cell_array(cell_byte) cell_array_byte;

#    define cell_array_byte_make(__name, __len) \
    cell_array_byte __name = { .len = __len, .buf = cell_mem_salloc(__len * sizeof(cell_byte)) };

#endif /* __CELL__ARRAY_H__ */
