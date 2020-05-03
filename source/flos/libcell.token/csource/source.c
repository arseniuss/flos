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
#include <cell/utf8.h>

#include "internal.h"

cell_error_def(FULLBUF, "buffer is full");
cell_error_def(INVCHR, "invalid unicode character");
cell_error_def(cell_lang_source_eof, "end of file");

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

cell_error __source_file_read(const cell_lang_source src, cell_char * _ch, cell_slice_type * buf) {
    cell_error err = CELL_NULL;
    struct __source_file_s *f = (struct __source_file_s *)src->data;

    if(buf->len >= buf->cap)
        return __FULLBUF_error;

    cell_size cap = buf->cap;
    cell_size start = buf->len;

    cell_char ch;
    cell_size ch_len = 0;

    do {
        if(buf->len >= cap + 1) {
            err = __FULLBUF_error;
            goto RETURN;
        }

        buf->cap = buf->len + 1;       // read just one byte

        if((err = cell_os_read(f->file, buf)) != CELL_NULL) {
            goto RETURN;
        }

        if(buf->len == 0) {
            err = __cell_lang_source_eof_error;
            goto RETURN;
        }

        ch_len = cell_utf8_tochar(&ch, &buf->buf[start], buf->len - start);
    } while(ch == cell_utf8_error && ch_len < buf->len - start);

    if(ch == cell_utf8_error) {
        err = __INVCHR_error;
        buf->len = start;
        goto RETURN;
    }

    *_ch = ch;
    buf->len = start + ch_len;


  RETURN:
    buf->cap = cap;

    return err;
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

    // TODO

    return CELL_NULL;
}

cell_error __source_str_read(const cell_lang_source src, cell_char * _ch, cell_slice_type * buf) {
    struct __source_str_s *s = (struct __source_str_s *)src->data;

    if(buf->len >= buf->cap)
        return __FULLBUF_error;

    cell_char ch;
    cell_size ch_len = cell_utf8_tochar(&ch, s->ptr, s->str.buffer + s->str.len - s->ptr);

    if(ch == cell_utf8_error) {
        return __INVCHR_error;
    }

    if(buf->len + ch_len > buf->cap)
        return __FULLBUF_error;

    __builtin_memcpy(&buf->buf[buf->len], s->ptr, ch_len);
    buf->len += ch_len;
    s->ptr += ch_len;
    *_ch = ch;

    return CELL_NULL;
}
