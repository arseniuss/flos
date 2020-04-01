/**
 *   Builtin library for cell language
 *   Copyright (C) 2017-2020 Armands Arseniuss Skolmeisters
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

#ifndef __CELL__GOTO_H__
#    define __CELL__GOTO_H__

#    include <cell/type.h>

typedef struct {
    cell_intptr buf[5];
} cell_label;


// func (lbl label) init() bool
#    define cell_label_init(lbl) __builtin_setjmp((void**)&(lbl)) != 0

#    define cell_label_goto(lbl) __builtin_longjmp((void **)&(lbl), 1)

#endif /* !__CELL__GOTO_H__ */
