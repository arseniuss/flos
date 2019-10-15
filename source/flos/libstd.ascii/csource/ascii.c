/*
 * Standard ASCII encoding library for cell language
 * Copyright (c) 2019 Armands Arseniuss Skolmeisters
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
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

#include <cell/ascii.h>

cell_bool ascii_isalnum(cell_char c) {
    return ascii_isalpha(c) || ascii_isdigit(c);
}

cell_bool ascii_isalpha(cell_char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

cell_bool ascii_iscntrl(cell_char c) {
    return (c >= 0x00 && c <= 0x1F) || c == 0x7F;
}

cell_bool ascii_isdigit(cell_char c) {
    return (c >= '0' && c <= '9');
}

cell_bool ascii_islower(cell_char c) {
    return (c >= 'a' && c <= 'z');
}

cell_bool ascii_isspace(cell_char c) {
    return c == ' ' || (c >= 0x09 && c <= 0x0D);
}

cell_bool ascii_isupper(cell_char c) {
    return (c >= 'A' && c <= 'Z');
}

cell_char ascii_tolower(cell_char c) {
    if(c >= 'A' && c <= 'Z')
        return 'a' + (c - 'A');
    return c;
}

cell_char ascii_toupper(cell_char c) {
    if(c >= 'a' && c <= 'z')
        return 'A' + (c - 'a');
    return c;
}

cell_bool ascii_isblank(cell_char c) {
    return c == '\t' || c == ' ';
}

cell_bool ascii_isxdigit(cell_char c) {
    return ascii_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

cell_bool ascii_ispunct(cell_char c) {
    return (c >= 0x21 && c <= 0x2F) || (c >= 0x3A && c <= 0x40) ||
        (c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7E);
}

cell_bool ascii_isgraph(cell_char c) {
    return (c >= 0x21 && c <= 0x7E);
}

cell_bool ascii_isprint(cell_char c) {
    return (c >= 0x20 && c <= 0x7E);
}
