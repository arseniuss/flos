/* 
 * Standard formatting for cell language
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
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

#include <cell/array.h>
#include <cell/error.h>
#include <cell/std/fmt.h>
#include <cell/assert.h>
#include <cell/os.h>

static cell_bool equal(const cell_c_char * result, cell_array buffer) {
    for(cell_uint32 i = 0; *result || buffer.len < buffer.cap; result++, i++) {
        if(*result != buffer.buffer[i])
            return 0;
    }
    return 1;
}

static void format_assert(const cell_c_char * result,
                          const cell_c_char * format, ...) {
    cell_va_list list;

    cell_va_start(list, format);


    if(result != CELL_NULL) {
        // Testing correctness 
        os_write(0, "Testing \"", 9, CELL_NULL);
        os_write(0, format, cell_c_strlen(format), CELL_NULL);
        os_write(0, "\" ... ", 6, CELL_NULL);

        cell_va_list list;

        cell_va_start(list, format);

        cell_array_make(buffer, 0, cell_c_strlen(result));
        cell_error *err = fmt_format_list(&buffer, cell_string_c(format), list);

        os_write(0, "\"", 1, CELL_NULL);
        os_write(0, buffer.buffer, buffer.len, CELL_NULL);
        os_write(0, "\"", 1, CELL_NULL);

        if(err != CELL_NULL || !equal(result, buffer)) {
            os_write(0, " error: ", 8, CELL_NULL);
            if(err != CELL_NULL) {
                os_write(0, err->string().buffer, err->string().len, CELL_NULL);

            }
            os_write(0, "\n", 1, CELL_NULL);
            os_exit(cell_string_c("test failed"));
        } else {
            os_write(0, "\n", 1, CELL_NULL);
        }
    } else {
        cell_array_make(buffer, 0, 1);

        os_write(0, "Testing error format \"", 22, CELL_NULL);
        os_write(0, format, cell_c_strlen(format), CELL_NULL);
        os_write(0, "\" ... ", 6, CELL_NULL);

        cell_error *err = fmt_format_list(&buffer, cell_string_c(format), list);
        if(err == CELL_NULL) {
            os_write(0, "\n", 1, CELL_NULL);
            os_exit(cell_string_c("test failed"));
        } else {
            os_write(0, err->string().buffer, err->string().len, CELL_NULL);
            os_write(0, " OK\n", 4, CELL_NULL);
        }
    }

}

TEST(format_hex) {
    format_assert("TEST", "TEST");
    format_assert("%", "%%");
    format_assert("123", "%d", 123);
    format_assert("+123  ", "%-+6d", 123);
    format_assert("FFE", "%X", 4094);
    format_assert("ffe", "%x", 4094);
    format_assert("-123", "%i", -123);
    format_assert("101", "%b", 5);
    format_assert("173", "%o", 123);
    format_assert("c", "%c", 'c');
    format_assert("\347\247\201", "%C", 0x79C1);
    format_assert("ABC", "%s", "ABC");
    format_assert("123         ", "%-12d", 123);
    format_assert("         123", "%12d", 123);
    format_assert("\n123\n123\n", "\n%d\n%d\n", 123, 123);

    format_assert(CELL_NULL, "%", "invalid format");
    format_assert(CELL_NULL, "%+-", "invalid format");
    format_assert(CELL_NULL, "%*", "invalid format");
    format_assert(CELL_NULL, "%*.*", "invalid format");
    format_assert(CELL_NULL, "%1", "invalid format");
    format_assert(CELL_NULL, "%.1", "invalid format");
    format_assert(CELL_NULL, "%ll", "invalid format");
    format_assert(CELL_NULL, "%w", "invalid format");
}
