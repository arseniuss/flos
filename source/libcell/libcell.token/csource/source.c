/* 
 * Cell language token library
 * Copyright (c) 2019 Armands Arseniuss Skolmeisters
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

#include <cell/builtin.h>
#include <cell/lang/source.h>
#include <cell/std/memory.h>

#include "internal.h"

cell_lang_source *cell_lang_source_file(cell_string str) {
    cell_lang_source *src = mem_alloc(sizeof(cell_lang_source));

    return src;
}
