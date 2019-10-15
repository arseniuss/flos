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

#include <cell/error.h>

#define ERROR_FUNC(errno) __error_##errno

#define ERROR_FUNC_DEF(errno, text) \
    cell_string __error_##errno##_str(void); \
    cell_error __error_##errno  = { .string = &__error_##errno##_str }; \
    cell_string __error_##errno##_str(void) { \
        return cell_string_c(text); \
    }

#define F(def, num, text)       ERROR_FUNC_DEF(def, text)

#include <cell/os/linux/errors.h>

#undef F

cell_error *os_linux_errno[] = {
#define UNIQUE
#define F(def, num, text)   [num] = &__error_##def,

#include <cell/os/linux/errors.h>

#undef F
#undef UNIQUE
};


cell_error **os_error = os_linux_errno;
