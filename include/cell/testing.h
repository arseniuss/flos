/* 
 * Builtin library of cell language
 * Copyright (c) 2017, 2018 Armands Arseniuss Skolmeisters
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

#ifndef __CELL__TEST_H__
#    define __CELL__TEST_H__

#    include <cell/type.h>

#    if CONFIG==TEST


#        define assert(cond)            do { \
                                    assert_info("%20s:%4d %-80s ... ", \
                                        __FILE__,__LINE__,\
                                        # cond); \
                                    if(!(cond)) { \
                                        assert_fail(#cond); \
                                    } else assert_info("OK\n"); \
                                } while(0)

#        define __TEST_NAME(n1, n2)     n1 ## _test_ ## n2
#        define TEST_NAME(n1, n2)       __TEST_NAME(n1, n2)
#        define TEST(name)              \
                                __attribute__((used, constructor)) \
                                void TEST_NAME(name, __COUNTER__)(void)

extern void assert_log(const c_char * file, int line, const c_char * cond);
extern void assert_fail(const c_char * cond);
extern void assert_info(const char *fmt, ...);

#    else
#        define assert(x)               (void)(x)
#    endif
       /*
        * CONFIG==TEST 
        */

#endif /* __CELL__TEST_H__ */
