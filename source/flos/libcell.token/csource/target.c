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

#include <cell/fmt.h>
#include <cell/lang/target.h>
#include <cell/mem.h>
#include <cell/mem/string.h>
#include <cell/slice.h>
#include <cell/string.h>
#include <cell/os/file.h>

struct cell_lang_target_s {
    cell_string filename;
    cell_os_file file;
};

cell_error cell_lang_target_file(cell_string str, cell_lang_target * trg) {
    if(!trg)
        return __default_error;

    cell_error err;

    if((err = cell_mem_alloc(sizeof(struct cell_lang_target_s), (void **)trg)) != CELL_NULL) {
        return err;
    }

    cell_slice_make_generic(s, 256);

    cell_fmt_format(&s, cell_string_c("%S.ll"), str);

    if((err = cell_string_copy(&(*trg)->filename, &s, s.len)) != CELL_NULL) {
        cell_mem_free(*trg);
        return err;
    }

    if((err = cell_os_create((*trg)->filename, &((*trg)->file))) != CELL_NULL) {
        cell_mem_free((*trg)->filename.buffer);
        cell_mem_free(*trg);
        return err;
    }

    return CELL_NULL;
}

cell_error cell_lang_target_name(const cell_lang_target trg, cell_string * name) {
    return cell_string_copy_s(name, &trg->filename);
}

cell_error cell_lang_target_write(cell_lang_target trg, const cell_string str) {
    cell_error err;

    if((err = cell_os_write(trg->file, str)) != CELL_NULL) {
        return err;
    }

    return CELL_NULL;
}
