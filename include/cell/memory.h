/* 
 * Builtin library of cell language
 * Copyright (c) 2017, 2018 Armands Arseniuss Skolmeisters
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
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
#ifndef __CELL__MEMORY_H__
#    define __CELL__MEMORY_H__

// module builtin.memory

#    include <cell/type.h>

/** Allocate memory from stack */
// func salloc(s size_t) safe*
#    define memory_salloc(x)       __builtin_alloca(x)

#    ifdef HAS_MEMORY_ALLOC

#    endif

#endif /* __CELL__MEMORY_H__ */
