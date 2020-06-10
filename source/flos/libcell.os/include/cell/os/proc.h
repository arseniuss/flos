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

#ifndef __OS__PROC_H__
#    define __OS__PROC_H__

#    include <cell/string.h>

#    define cell_os_exit(msg) \
    _Generic((msg), \
        const char*: cell_os_exit_p, \
        char*: cell_os_exit_p, \
        cell_string: cell_os_exit_s \
    )(msg)

void cell_os_exit_s(const cell_string msg);
void cell_os_exit_p(const char *msg);

#endif /* !__OS__PROC_H__ */
