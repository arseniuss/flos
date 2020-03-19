/**
 *  Cell language token library
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

#include <cell/array.h>
#include <cell/assert.h>
#include <cell/builtin.h>
#include <cell/error.h>
#include <cell/lang/source.h>
#include <cell/mem.h>
#include <cell/os/file.h>

#include "internal.h"

// func new(filepath string) (error, source)

cell_error cell_lang_source_new(cell_string filepath, cell_lang_source * src) {
    if(!src)
        return __default_error;

    cell_error err;
    struct __source_file_s *s;

    if((err = cell_mem_alloc(sizeof(struct cell_lang_source_s), (void **)src)) != CELL_NULL) {
        return err;
    }

    if((err = cell_mem_alloc(sizeof(struct __source_file_s), (void **)&s)) != CELL_NULL) {
        cell_mem_free(*src);
        return err;
    }

    if((err = cell_os_open(filepath, &s->file)) != CELL_NULL) {
        cell_mem_free(s);
        return err;
    }


    (*src)->read = &__source_file_read;
    (*src)->data = s;

    return CELL_NULL;
}

cell_error __source_file_read(const cell_lang_source src, cell_array * buffer) {
    struct __source_file_s *f = (struct __source_file_s *)src->data;
    cell_error err;

    cell_size cap = buffer->cap;
    buffer->cap = 1;

    if((err = cell_os_read(f->file, buffer)) != CELL_NULL) {
        buffer->cap = cap;
        return err;
    }

    buffer->cap = cap;

    return CELL_NULL;
}

cell_error cell_lang_source_string(cell_string str, cell_lang_source * src) {
    if(!src)
        return __default_error;

    cell_error err;
    struct __source_str_s *s;

    if((err = cell_mem_alloc(sizeof(struct cell_lang_source_s), (void **)src)) != CELL_NULL) {
        return err;
    }

    if((err = cell_mem_alloc(sizeof(struct __source_str_s), (void **)&s)) != CELL_NULL) {
        cell_mem_free(*src);
        return err;
    }

    (*src)->read = &__source_str_read;
    (*src)->data = s;

    return CELL_NULL;
}

cell_error __source_str_read(const cell_lang_source src, cell_array * buffer) {
    struct __source_str_s *s = (struct __source_str_s *)src->data;

    if(s->ptr >= s->str.buffer + s->str.len) {
        buffer->len = 0;
    } else if(buffer->cap < 1) {
        return __default_error;
    } else {
        buffer->len = 1;
        buffer->buffer[0] = *s->ptr;
        s->ptr++;
    }

    return CELL_NULL;
}
