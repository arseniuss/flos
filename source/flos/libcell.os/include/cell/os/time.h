/**
 *  OS layer library
 *  Copyright (C) 2019 Armands Arseniuss Skolmeisters
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

#ifndef __CELL__OS_TIME_H__
#    define __CELL__OS_TIME_H__

#    include <cell/builtin.h>
#    include <cell/error.h>

/**
 * 
 * @param milisecs
 */
// func sleep(milisecs uint64) error
cell_error cell_os_sleep(cell_uint64 milisecs);

#endif /* !__CELL__OS_TIME_H__ */
