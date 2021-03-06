/* 
 * Manual memory management library for cell language
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CELL__MEM_H__
#    define __CELL__MEM_H__

#    include <cell/assert.h>
#    include <cell/builtin.h>
#    include <cell/error.h>

// func alloc(sz size) (*, error)
cell_error cell_mem_alloc(cell_size sz, void **ptr);

cell_error cell_mem_realloc(cell_size sz, void **ptr);

// func (* ptr) free() error
cell_error cell_mem_free(void *ptr);

#    define CELL_MEM_COPY(x, y) \
        { \
            cell_assert(__builtin_types_compatible_p(typeof(x), typeof(y))); \
            __builtin_memcpy(&(y), &(x), sizeof(typeof(x))); \
        }

#endif /* __CELL__MEM_H__ */
