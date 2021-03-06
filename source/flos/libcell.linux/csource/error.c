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

#define F(def, num, text)       cell_error_def(def, text)

#include <cell/linux/errors.h>

#undef F

cell_error cell_linux_errno[] = {
#define UNIQUE
#define F(def, num, text)   [num] = &CELL_ERROR_NAME_S(def),

#include <cell/linux/errors.h>

#undef F
#undef UNIQUE
};


cell_error *cell_os_error = &cell_linux_errno[0];
