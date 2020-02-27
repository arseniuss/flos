/**
 *  Linux layer library
 *  Copyright (C) 2019  Armands Arseniuss Skolmeisters
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

typedef void (*func_ptr) (void);

extern func_ptr __init_array_start[0], __init_array_end[0];
extern func_ptr __fini_array_start[0], __fini_array_end[0];

void __init(void) __attribute__ ((section("_init")));

void _init(void) {
    for(func_ptr * func = __init_array_start; func != __init_array_end; func++)
        (*func) ();
}

void _fini(void) {
    for(func_ptr * func = __fini_array_start; func != __fini_array_end; func++)
        (*func) ();
}
