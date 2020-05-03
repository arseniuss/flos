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

#include <cell/args.h>
#include <cell/ascii.h>
#include <cell/error.h>
#include <cell/fmt.h>
#include <cell/utf8.h>
#include <cell/slice.h>

cell_error_def(BUFCAP, "buffer cap limit");
cell_error_def(INVPAR, "invalid parameter");
cell_error_def(INVFMT, "invalid format");

const cell_uint32 cell_fmt_width = 1;
const cell_uint32 cell_fmt_left = cell_fmt_width << 1;
const cell_uint32 cell_fmt_show_sign = cell_fmt_left << 1;
const cell_uint32 cell_fmt_blank = cell_fmt_show_sign << 1;
const cell_uint32 cell_fmt_alter = cell_fmt_blank << 1;
const cell_uint32 cell_fmt_zeros = cell_fmt_alter << 1;
const cell_uint32 cell_fmt_signed = cell_fmt_zeros << 1;
const cell_uint32 cell_fmt_w16 = cell_fmt_signed << 1;
const cell_uint32 cell_fmt_w32 = cell_fmt_w16 << 1;
const cell_uint32 cell_fmt_w64 = cell_fmt_w32 << 1;
const cell_uint32 cell_fmt_capital = cell_fmt_w64 << 1;

static inline cell_error __emit_in_buffer(void *p, cell_byte ch) {
    cell_slice_type *buffer = (cell_slice_type *) p;

    if(buffer == CELL_NULL)
        return CELL_ERROR_NAME(INVPAR);

    if(buffer->len < buffer->cap) {
        buffer->buf[buffer->len++] = ch;
        return CELL_NULL;
    }

    return CELL_ERROR_NAME(BUFCAP);
}

cell_size cell_c_strlen(const char *);

cell_error __do_format(fmt_format_args * args, cell_va_list list, void *p, cell_error(*emit) (void *, cell_byte)) {
    cell_uint16 radix;
    cell_int64 num;
    cell_size width = 0;
    cell_byte *ptr;
    cell_error err = CELL_NULL;
    cell_byte tmp[130];

    switch (args->ch) {
        case 'X':
            args->flags |= cell_fmt_capital;
        case 'x':
        case 'p':
        case 'n':
            radix = 16;
            goto DO_NUM;
        case 'd':
        case 'i':
            args->flags |= cell_fmt_signed;
        case 'u':
            radix = 10;
            goto DO_NUM;
        case 'b':
            radix = 2;
            goto DO_NUM;
        case 'o':
            radix = 8;
            goto DO_NUM;

          DO_NUM:
            {
                cell_byte *no = &tmp[129];


                *no = '\0';

                if(args->flags & cell_fmt_w16) {
                    if(args->flags & cell_fmt_signed) {
                        num = (cell_int16) cell_va_arg(list, int);
                    } else {
                        num = (cell_uint16) cell_va_arg(list, int);
                    }
                } else if(args->flags & cell_fmt_w64) {
                    if(args->flags & cell_fmt_signed) {
                        num = (cell_int32) cell_va_arg(list, cell_int64);
                    } else {
                        num = (cell_uint32) cell_va_arg(list, cell_uint64);
                    }
                } else {
                    if(args->flags & cell_fmt_signed) {
                        num = (cell_int32) cell_va_arg(list, cell_int32);
                    } else {
                        num = (cell_uint32) cell_va_arg(list, cell_uint32);
                    }
                }

                cell_uint64 n;

                if(args->flags & cell_fmt_signed) {
                    n = num < 0 ? -num : num;
                } else {
                    n = num;
                }

                do {
                    cell_uint64 temp;

                    no--;
                    temp = (cell_uint64) n % radix;
                    if(temp < 10) {
                        *no = temp + '0';
                    } else if(args->flags & cell_fmt_capital) {
                        *no = temp - 10 + 'A';
                    } else {
                        *no = temp - 10 + 'a';
                    }
                    width++;
                    n = (cell_uint64) n / radix;
                }
                while(n != 0);

                if(args->flags & cell_fmt_signed) {
                    if(num < 0) {
                        num = -num;
                        *(--no) = '-';
                        width++;
                    } else if(args->flags & cell_fmt_show_sign) {
                        *(--no) = '+';
                        width++;
                    }
                }

                if(args->flags & cell_fmt_alter) {
                    switch (radix) {
                        case 16:
                            *(width++, --no) = 'x';
                            *(width++, --no) = '0';
                            break;
                        case 8:
                            *(width++, --no) = '0';
                            break;
                        case 2:
                            *(width++, --no) = 'b';
                            *(width++, --no) = '0';
                    }
                }

                ptr = no;

                goto DO_STRING;
            }
        case 'c':
            // ASCII char

            if((err = emit(p, (cell_byte) cell_va_arg(list, int))) != CELL_NULL)
                  return err;

            break;
        case 'C':
            num = cell_va_arg(list, cell_uint32);

            if((width = cell_utf8_fromchar((cell_char) num, tmp, sizeof(tmp))) == 0) {
                return CELL_ERROR_NAME(INVPAR);
            }

            tmp[width] = '\0';
            ptr = &tmp[0];
            goto DO_STRING;
        case 's':
            ptr = (cell_byte *) cell_va_arg(list, void *);
            width = cell_c_strlen(ptr);
            if(args->width != 0 && width > args->width) 
                width = args->width;
            goto DO_STRING;
        case 'S':
        {
            cell_string str;

            str = (cell_string) cell_va_arg(list, cell_string);

            ptr = str.buffer;
            width = str.len;

            goto DO_STRING;
        }

          DO_STRING:
            if(!(args->flags & cell_fmt_left)) {
                while(args->width > width) {
                    emit(p, args->flags & cell_fmt_zeros ? '0' : ' ');
                    args->width--;
                }
            }

            while(*ptr != '\0' && width > 0) {
                emit(p, *ptr++);
                width--;
            }

            if(args->flags & cell_fmt_left) {
                while(args->width > width) {
                    emit(p, args->flags & cell_fmt_zeros ? '0' : ' ');
                    args->width--;
                }
            }

    }

    return CELL_NULL;
}

cell_error __do_custom_format(fmt_format_args * args, cell_va_list list, void *p, cell_error(*emit) (void *, cell_byte)) {
    return CELL_ERROR_NAME(INVFMT);
}

cell_error cell_fmt_format(cell_slice_type * buffer, cell_string format, ...) {
    cell_va_list list;

    cell_va_start(list, format);

    cell_error err = cell_fmt_format_list(buffer, format, list);

    cell_va_end(list);

    return err;
}

cell_error cell_fmt_format_list(cell_slice_type * buffer, cell_string format, cell_va_list list) {
    cell_error ret = CELL_NULL;
    fmt_format_args args;

    for(cell_size i = 0; i < format.len; i++) {

        if(format.buffer[i] == '%') {
            if(++i >= format.len)
                return CELL_ERROR_NAME(INVFMT);

            if(format.buffer[i] == '%') {
                if((ret = __emit_in_buffer(buffer, '%')) != CELL_NULL)
                    return ret;
                continue;
            }

            args.begin = &format.buffer[i];
            args.width = 0;
            args.precision = 6;
            args.flags = 0;

            while(1) {

                switch (format.buffer[i]) {
                    case '-':
                    /** Left justify */
                        args.flags |= cell_fmt_left;
                        break;
                    case '+':
                    /** Print sign */
                        args.flags |= cell_fmt_show_sign;
                        break;
                    case ' ':
                    /** Print blank */
                        args.flags |= cell_fmt_blank;
                        break;
                    case '#':
                    /** Alternate foram */
                        args.flags |= cell_fmt_alter;
                        break;
                    case '0':
                    /** Preceed zeros */
                        args.flags |= cell_fmt_zeros;
                        break;
                    default:
                        goto FLAGS_DONE;
                }
                if(++i >= format.len)
                    return CELL_ERROR_NAME(INVFMT);
            }

          FLAGS_DONE:
            if(format.buffer[i] == '*') {
                args.width = cell_va_arg(list, int);
                if(++i >= format.len)
                    return CELL_ERROR_NAME(INVFMT);
            } else {
                while(cell_ascii_isdigit(format.buffer[i])) {
                    args.width = args.width * 10 + (format.buffer[i] - '0');
                    if(++i >= format.len)
                        return CELL_ERROR_NAME(INVFMT);
                }
            }

            if(format.buffer[i] == '.') {
                if(++i >= format.len)
                    return CELL_ERROR_NAME(INVFMT);
                if(format.buffer[i] == '*') {
                    args.precision = cell_va_arg(list, int);
                    if(++i >= format.len)
                        return CELL_ERROR_NAME(INVFMT);
                } else {
                    args.precision = 0;
                    while(cell_ascii_isdigit(format.buffer[i])) {
                        args.precision = args.precision * 10 + (format.buffer[i] - '0');
                        if(++i >= format.len)
                            return CELL_ERROR_NAME(INVFMT);
                    }
                }
            }

            switch (format.buffer[i]) {
                case 'h':
                    args.flags |= cell_fmt_w16;
                    if(++i >= format.len)
                        return CELL_ERROR_NAME(INVFMT);
                    break;
                case 'l':
                    if(++i >= format.len)
                        return CELL_ERROR_NAME(INVFMT);
                    if(format.buffer[i] == 'l') {
                        args.flags |= cell_fmt_w64;
                        if(++i >= format.len)
                            return CELL_ERROR_NAME(INVFMT);
                    } else {
                        args.flags |= cell_fmt_w32;
                    }
                    break;
            }

            int chlen;

            if((chlen = cell_utf8_tochar(&args.ch, &format.buffer[i], format.len - i)) > 0) {
                i += chlen - 1;
                switch (args.ch) {
                    case 'u':
                    case 'd':
                    case 'i':
                    case 'x':
                    case 'X':
                    case 'b':
                    case 'o':
                    case 'c':
                    case 's':
                    case 'S':
                    case 'C':
                        __do_format(&args, list, buffer, &__emit_in_buffer);
                        break;
                    default:
                        if((ret = __do_custom_format(&args, list, buffer, &__emit_in_buffer)) != CELL_NULL)
                            return ret;
                        break;
                }

            }
        } else {
            if((ret = __emit_in_buffer(buffer, format.buffer[i])) != CELL_NULL)
                return ret;
        }
    }

    return ret;
}
