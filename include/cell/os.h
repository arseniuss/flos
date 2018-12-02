/* 
 * OS library for cell language
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
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

#ifndef __OS__OS_H__
#    define __OS__OS_H__

#    include <cell/builtin.h>
#    include <cell/os/error.h>

#    define func(name, ret, ...)    ret name(__VA_ARGS__);

#    define EOF                     0

#    define R                       1
#    define W                       2
#    define X                       4

#    define RW                      R | W
#    define RX                      R | X
#    define WX                      W | X
#    define RWX                     R | W | X

#    define PERM(o, g, u, mode)     (((o) & 0x7) << 6) | (((g) & 0x7) << 3) | \
                                        ((u) & 0x7) | mode)
/** File descriptor type */
typedef int32_t fd_t;
typedef int32_t pid_t;
typedef int64_t offset_t;

enum {
  /** Open for reading */
    OREAD = 0,
  /** Open for writing */
    OWRITE = (1 << 0),
  /** Open for reading and writing */
    ORDWR = (1 << 1),
  /** Open for executing */
    OEXEC = 3,

  /** Truncate file to zero length before opening */
    OTRUNC = (1 << 4),

  /** Close file before exec call */
    OTILLEXEC,

  /** Close file when all processes stops using it */
    OGC,

  /** Open file for exclusive use */
    OEXCL,
};

enum {
  /** Create mode opton to create a new directory */
    PMDIR = (1 << 8),

  /** Create file for exclusive use */
    PMEXCL = (1 << 9),
  /** Create file to append to */
    PMAPPEND,
};

/** Flags for os_fork function */
enum {
  /** Create a new process or affect current */
    FPROC = (1 << 0),



};

typedef struct {
    pid_t pid;
    uint32_t time[3];
    const byte *msg;
} waitmsg;

/**
 * Change working directory of process. If `dirname` do not start with / or #,
 * then the current working directory is starting point to evulate change.
 * @param dirname directory path
 * @return 
 */
func(os_chdir, int, const byte * dirname);

/**
 * Closes file assicated with file descriptor. If provided file descriptor is 
 * valid open descriptor, it is guanranteed to close. Upon termination of 
 * process files are closed automatically.
 */
func(os_close, error, fd_t fd);

/**
 * Creates new file according to `omode` and returns associated file. If file
 * already exists, it is truncated to zero length.
 * descriptor. 
 * @param file
 * @param omode
 * @param perm
 * @return 
 */
func(os_create, fd_t, const byte * file, byte omode, uint32_t perm);
func(os_open, fd_t, const byte * file, byte omode);
func(os_read, ssize_t, fd_t fd, void *buf, size_t bytes);
func(os_write, ssize_t, fd_t fd, const void *buf, size_t bytes);

/**
 * Sets the offset of file associated with file descriptor.
 * @param fd file descriptor
 * @param n
 * @param type  if type is 0, then offset is set to n bytes
 *              if type is 1, then pointer is set from current position plus n
 *              if type is 2, then pointer is set to the size of file plus n
 * @return new offset
 */
func(os_seek, offset_t, fd_t fd, offset_t n, int type);

func(os_dup, int, fd_t oldfd, fd_t newfd);

func(os_stat, int, const byte * file, void *buf, ssize_t len);
func(os_fstat, int, fd_t fd, void *buf, ssize_t len);
func(os_wstat, int, const byte * file, void *buf, ssize_t len);
func(os_fwstat, int, fd_t fd, void *buf, ssize_t len);

func(os_remove, int, const byte * file);

func(os_fork, int, uint32_t flags);

func(os_exec, int, const byte * name, byte * args[]);
func(os_execl, int, const byte * name, ...);

func(os_exit, int, const byte * msg);
func(os_exits, int, const byte * msg);
func(os_atexit, int, void (*)(void));
func(os_atexitdont, int, void (*)(void));

func(os_sleep, int, uint32_t milisecs);
func(os_alarm, int, uint32_t milisecs);

func(os_wait, waitmsg *, void);
func(os_waitpid, pid_t, void);
func(os_pipe, int, fd_t fd[2]);
func(os_rendezvous, void *, void *tag, void *value);
func(os_brk, int, void *addr);
func(os_sbrk, void *, uint32_t inc);
func(os_notify, int, void (*)(void *, const byte *));
func(os_noted, int, int v);

#    undef func


#endif /* __OS__OS_H__ */
