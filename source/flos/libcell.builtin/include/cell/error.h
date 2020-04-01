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

#ifndef __CELL__ERROR_H__
#    define __CELL__ERROR_H__

#    include <cell/string.h>
#    include <cell/goto.h>

#    define CELL_ERROR_NAME(name)   __##name##_error

#    define CELL_DECL_ERROR(name) \
        extern cell_error CELL_ERROR_NAME(name);

#    define CELL_DEF_ERROR(name, str) \
    cell_string __##name##_error_str(struct cell_error_s* err); \
    cell_error __##name##_error = &(struct cell_error_s){ .string = __##name##_error_str }; \
    cell_string __##name##_error_str(struct cell_error_s* err) { return cell_string_c(str); }

// type error struct {
//      string()
// }

typedef struct cell_error_s {
    cell_string(*string) (struct cell_error_s *);
} *cell_error;

extern cell_error __default_error;
extern cell_error __this_error;
extern cell_error __ret1_error;
extern cell_error __ret2_error;
extern cell_error __ret3_error;
extern cell_error __ret4_error;
extern cell_error __ret5_error;
extern cell_error __ret6_error;

typedef struct {
    cell_label label;
    cell_error err;
} cell_error_label;

#    define cell_error_label_init(lbl) ({ lbl.err = CELL_NULL; cell_label_init(lbl.label); })

#    define cell_error_label_throw(lbl, e) lbl.err = e; cell_label_goto(lbl.label);

#endif /* __CELL__ERROR_H__ */
