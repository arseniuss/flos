/**
 *  Linux layer library
 *  Copyright (C) 2018 - 2019  Armands Arseniuss Skolmeisters
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

#ifndef __CELL_LINUX__ERROR_H__
#    define __CELL_LINUX__ERROR_H__

// TODO: POSIX, UNIX
#    define CELL_LINUX_EPERM        1  /* Operation not permitted */
#    define CELL_LINUX_ENOENT       2  /* No such file or directory */
#    define CELL_LINUX_ESRCH        3  /* No such process */
#    define CELL_LINUX_EINTR        4  /* Interrupted system call */
#    define CELL_LINUX_EIO          5  /* I/O error */
#    define CELL_LINUX_ENXIO        6  /* No such device or address */
#    define CELL_LINUX_E2BIG        7  /* Argument list too long */
#    define CELL_LINUX_ENOEXEC      8  /* Exec format error */
#    define CELL_LINUX_EBADF        9  /* Bad file number */
#    define CELL_LINUX_ECHILD      10  /* No child processes */
#    define CELL_LINUX_EAGAIN      11  /* Try again */
#    define CELL_LINUX_ENOMEM      12  /* Out of memory */
#    define CELL_LINUX_EACCES      13  /* Permission denied */
#    define CELL_LINUX_EFAULT      14  /* Bad address */
#    define CELL_LINUX_ENOTBLK     15  /* Block device required */
#    define CELL_LINUX_EBUSY       16  /* Device or resource busy */
#    define CELL_LINUX_EEXIST      17  /* File exists */
#    define CELL_LINUX_EXDEV       18  /* Cross-device link */
#    define CELL_LINUX_ENODEV      19  /* No such device */
#    define CELL_LINUX_ENOTDIR     20  /* Not a directory */
#    define CELL_LINUX_EISDIR      21  /* Is a directory */
#    define CELL_LINUX_EINVAL      22  /* Invalid argument */
#    define CELL_LINUX_ENFILE      23  /* File table overflow */
#    define CELL_LINUX_EMFILE      24  /* Too many open files */
#    define CELL_LINUX_ENOTTY      25  /* Not a typewriter */
#    define CELL_LINUX_ETXTBSY     26  /* Text file busy */
#    define CELL_LINUX_EFBIG       27  /* File too large */
#    define CELL_LINUX_ENOSPC      28  /* No space left on device */
#    define CELL_LINUX_ESPIPE      29  /* Illegal seek */
#    define CELL_LINUX_EROFS       30  /* Read-only file system */
#    define CELL_LINUX_EMLINK      31  /* Too many links */
#    define CELL_LINUX_EPIPE       32  /* Broken pipe */
#    define CELL_LINUX_EDOM        33  /* Math argument out of domain of func */
#    define CELL_LINUX_ERANGE      34  /* Math result not representable */


#    define CELL_LINUX_EDEADLK     35  /* Resource deadlock would occur */
#    define CELL_LINUX_ENAMETOOLONG    36   /* File name too long */
#    define CELL_LINUX_ENOLCK      37  /* No record locks available */
#    define CELL_LINUX_ENOSYS      38  /* Function not implemented */
#    define CELL_LINUX_ENOTEMPTY   39  /* Directory not empty */
#    define CELL_LINUX_ELOOP       40  /* Too many symbolic links encountered */
#    define CELL_LINUX_EWOULDBLOCK EAGAIN   /* Operation would block */
#    define CELL_LINUX_ENOMSG      42  /* No message of desired type */
#    define CELL_LINUX_EIDRM       43  /* Identifier removed */
#    define CELL_LINUX_ECHRNG      44  /* Channel number out of range */
#    define CELL_LINUX_EL2NSYNC    45  /* Level 2 not synchronized */
#    define CELL_LINUX_EL3HLT      46  /* Level 3 halted */
#    define CELL_LINUX_EL3RST      47  /* Level 3 reset */
#    define CELL_LINUX_ELNRNG      48  /* Link number out of range */
#    define CELL_LINUX_EUNATCH     49  /* Protocol driver not attached */
#    define CELL_LINUX_ENOCSI      50  /* No CSI structure available */
#    define CELL_LINUX_EL2HLT      51  /* Level 2 halted */
#    define CELL_LINUX_EBADE       52  /* Invalid exchange */
#    define CELL_LINUX_EBADR       53  /* Invalid request descriptor */
#    define CELL_LINUX_EXFULL      54  /* Exchange full */
#    define CELL_LINUX_ENOANO      55  /* No anode */
#    define CELL_LINUX_EBADRQC     56  /* Invalid request code */
#    define CELL_LINUX_EBADSLT     57  /* Invalid slot */

#    define CELL_LINUX_EDEADLOCK   EDEADLK

#    define CELL_LINUX_EBFONT      59  /* Bad font file format */
#    define CELL_LINUX_ENOSTR      60  /* Device not a stream */
#    define CELL_LINUX_ENODATA     61  /* No data available */
#    define CELL_LINUX_ETIME       62  /* Timer expired */
#    define CELL_LINUX_ENOSR       63  /* Out of streams resources */
#    define CELL_LINUX_ENONET      64  /* Machine is not on the network */
#    define CELL_LINUX_ENOPKG      65  /* Package not installed */
#    define CELL_LINUX_EREMOTE     66  /* Object is remote */
#    define CELL_LINUX_ENOLINK     67  /* Link has been severed */
#    define CELL_LINUX_EADV        68  /* Advertise error */
#    define CELL_LINUX_ESRMNT      69  /* Srmount error */
#    define CELL_LINUX_ECOMM       70  /* Communication error on send */
#    define CELL_LINUX_EPROTO      71  /* Protocol error */
#    define CELL_LINUX_EMULTIHOP   72  /* Multihop attempted */
#    define CELL_LINUX_EDOTDOT     73  /* RFS specific error */
#    define CELL_LINUX_EBADMSG     74  /* Not a data message */
#    define CELL_LINUX_EOVERFLOW   75  /* Value too large for defined data type */
#    define CELL_LINUX_ENOTUNIQ    76  /* Name not unique on network */
#    define CELL_LINUX_EBADFD      77  /* File descriptor in bad state */
#    define CELL_LINUX_EREMCHG     78  /* Remote address changed */
#    define CELL_LINUX_ELIBACC     79  /* Can not access a needed shared library */
#    define CELL_LINUX_ELIBBAD     80  /* Accessing a corrupted shared library */
#    define CELL_LINUX_ELIBSCN     81  /* .lib section in a.out corrupted */
#    define CELL_LINUX_ELIBMAX     82  /* Attempting to link in too many shared libraries */
#    define CELL_LINUX_ELIBEXEC    83  /* Cannot exec a shared library directly */
#    define CELL_LINUX_EILSEQ      84  /* Illegal byte sequence */
#    define CELL_LINUX_ERESTART    85  /* Interrupted system call should be restarted */
#    define CELL_LINUX_ESTRPIPE    86  /* Streams pipe error */
#    define CELL_LINUX_EUSERS      87  /* Too many users */
#    define CELL_LINUX_ENOTSOCK    88  /* Socket operation on non-socket */
#    define CELL_LINUX_EDESTADDRREQ    89   /* Destination address required */
#    define CELL_LINUX_EMSGSIZE    90  /* Message too long */
#    define CELL_LINUX_EPROTOTYPE  91  /* Protocol wrong type for socket */
#    define CELL_LINUX_ENOPROTOOPT 92  /* Protocol not available */
#    define CELL_LINUX_EPROTONOSUPPORT 93   /* Protocol not supported */
#    define CELL_LINUX_ESOCKTNOSUPPORT 94   /* Socket type not supported */
#    define CELL_LINUX_EOPNOTSUPP  95  /* Operation not supported on transport endpoint */
#    define CELL_LINUX_EPFNOSUPPORT    96   /* Protocol family not supported */
#    define CELL_LINUX_EAFNOSUPPORT    97   /* Address family not supported by protocol */
#    define CELL_LINUX_EADDRINUSE  98  /* Address already in use */
#    define CELL_LINUX_EADDRNOTAVAIL   99   /* Cannot assign requested address */
#    define CELL_LINUX_ENETDOWN    100 /* Network is down */
#    define CELL_LINUX_ENETUNREACH 101 /* Network is unreachable */
#    define CELL_LINUX_ENETRESET   102 /* Network dropped connection because of reset */
#    define CELL_LINUX_ECONNABORTED    103  /* Software caused connection abort */
#    define CELL_LINUX_ECONNRESET  104 /* Connection reset by peer */
#    define CELL_LINUX_ENOBUFS     105 /* No buffer space available */
#    define CELL_LINUX_EISCONN     106 /* Transport endpoint is already connected */
#    define CELL_LINUX_ENOTCONN    107 /* Transport endpoint is not connected */
#    define CELL_LINUX_ESHUTDOWN   108 /* Cannot send after transport endpoint shutdown */
#    define CELL_LINUX_ETOOMANYREFS    109  /* Too many references: cannot splice */
#    define CELL_LINUX_ETIMEDOUT   110 /* Connection timed out */
#    define CELL_LINUX_ECONNREFUSED    111  /* Connection refused */
#    define CELL_LINUX_EHOSTDOWN   112 /* Host is down */
#    define CELL_LINUX_EHOSTUNREACH    113  /* No route to host */
#    define CELL_LINUX_EALREADY    114 /* Operation already in progress */
#    define CELL_LINUX_EINPROGRESS 115 /* Operation now in progress */
#    define CELL_LINUX_ESTALE      116 /* Stale NFS file handle */
#    define CELL_LINUX_EUCLEAN     117 /* Structure needs cleaning */
#    define CELL_LINUX_ENOTNAM     118 /* Not a XENIX named type file */
#    define CELL_LINUX_ENAVAIL     119 /* No XENIX semaphores available */
#    define CELL_LINUX_EISNAM      120 /* Is a named type file */
#    define CELL_LINUX_EREMOTEIO   121 /* Remote I/O error */
#    define CELL_LINUX_EDQUOT      122 /* Quota exceeded */

#    define CELL_LINUX_ENOMEDIUM   123 /* No medium found */
#    define CELL_LINUX_EMEDIUMTYPE 124 /* Wrong medium type */
#    define CELL_LINUX_ECANCELED   125 /* Operation Canceled */
#    define CELL_LINUX_ENOKEY      126 /* Required key not available */
#    define CELL_LINUX_EKEYEXPIRED 127 /* Key has expired */
#    define CELL_LINUX_EKEYREVOKED 128 /* Key has been revoked */
#    define CELL_LINUX_EKEYREJECTED    129  /* Key was rejected by service */

/* for robust mutexes */
#    define CELL_LINUX_EOWNERDEAD  130 /* Owner died */
#    define CELL_LINUX_ENOTRECOVERABLE 131  /* State not recoverable */

#endif /* !__CELL_LINUX__ERROR_H__ */
