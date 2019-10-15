/**
 *   Builtin library for cell language
 *   Copyright (C) 2019 Armands Arseniuss Skolmeisters
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

#include <cell/array.h>
#include <cell/defs.h>
#include <cell/type.h>

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_array
#include <cell/namespace.h>

size_t func(type_size) (type_t ptr) {
    if(efunc(cell_type, class) (ptr) != TYPE_ARRAY)
        return 0;

    struct array_desc *at = (struct array_desc *)efunc(cell_type, desc) (ptr);

    return efunc(cell_type, size) (at->of_type) * at->count;
}
