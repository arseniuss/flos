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

#ifndef F
#    define F(x, y, z)
#endif


F(CELL_LINUX_EPERM, 1, "Operation not permitted")
    F(CELL_LINUX_ENOENT, 2, "No such file or directory")
    F(CELL_LINUX_ESRCH, 3, "No such process")
    F(CELL_LINUX_EINTR, 4, "Interrupted system call")
    F(CELL_LINUX_EIO, 5, "I/O error")
    F(CELL_LINUX_ENXIO, 6, "No such device or address")
    F(CELL_LINUX_E2BIG, 7, "Argument list too long")
    F(CELL_LINUX_ENOEXEC, 8, "Exec format error")
    F(CELL_LINUX_EBADF, 9, "Bad file number")
    F(CELL_LINUX_ECHILD, 10, "No child processes")
    F(CELL_LINUX_EAGAIN, 11, "Try again")
    F(CELL_LINUX_ENOMEM, 12, "Out of memory")
    F(CELL_LINUX_EACCES, 13, "Permission denied")
    F(CELL_LINUX_EFAULT, 14, "Bad address")
    F(CELL_LINUX_ENOTBLK, 15, "Block device required")
    F(CELL_LINUX_EBUSY, 16, "Device or resource busy")
    F(CELL_LINUX_EEXIST, 17, "File exists")
    F(CELL_LINUX_EXDEV, 18, "Cross-device link")
    F(CELL_LINUX_ENODEV, 19, "No such device")
    F(CELL_LINUX_ENOTDIR, 20, "Not a directory")
    F(CELL_LINUX_EISDIR, 21, "Is a directory")
    F(CELL_LINUX_EINVAL, 22, "Invalid argument")
    F(CELL_LINUX_ENFILE, 23, "File table overflow")
    F(CELL_LINUX_EMFILE, 24, "Too many open files")
    F(CELL_LINUX_ENOTTY, 25, "Not a typewriter")
    F(CELL_LINUX_ETXTBSY, 26, "Text file busy")
    F(CELL_LINUX_EFBIG, 27, "File too large")
    F(CELL_LINUX_ENOSPC, 28, "No space left on device")
    F(CELL_LINUX_ESPIPE, 29, "Illegal seek")
    F(CELL_LINUX_EROFS, 30, "Read-only file system")
    F(CELL_LINUX_EMLINK, 31, "Too many links")
    F(CELL_LINUX_EPIPE, 32, "Broken pipe")
    F(CELL_LINUX_EDOM, 33, "Math argument out of domain of func")
    F(CELL_LINUX_ERANGE, 34, "Math result not representable")
    F(CELL_LINUX_EDEADLK, 35, "Resource deadlock would occur")
    F(CELL_LINUX_ENAMETOOLONG, 36, "File name too long")
    F(CELL_LINUX_ENOLCK, 37, "No record locks available")
    F(CELL_LINUX_ENOSYS, 38, "Function not implemented")
    F(CELL_LINUX_ENOTEMPTY, 39, "Directory not empty")
    F(CELL_LINUX_ELOOP, 40, "Too many symbolic links encountered")
#ifndef UNIQUE
    F(CELL_LINUX_EWOULDBLOCK, 11, "Operation would block")
#else
    F(CELL_LINUX_EWOULDBLOCK, 41, "(Invalid) Operation would block")
#endif
    F(CELL_LINUX_ENOMSG, 42, "No message of desired type")
    F(CELL_LINUX_EIDRM, 43, "Identifier removed")
    F(CELL_LINUX_ECHRNG, 44, "Channel number out of range")
    F(CELL_LINUX_EL2NSYNC, 45, "Level 2 not synchronized")
    F(CELL_LINUX_EL3HLT, 46, "Level 3 halted")
    F(CELL_LINUX_EL3RST, 47, "Level 3 reset")
    F(CELL_LINUX_ELNRNG, 48, "Link number out of range")
    F(CELL_LINUX_EUNATCH, 49, "Protocol driver not attached")
    F(CELL_LINUX_ENOCSI, 50, "No CSI structure available")
    F(CELL_LINUX_EL2HLT, 51, "Level 2 halted")
    F(CELL_LINUX_EBADE, 52, "Invalid exchange")
    F(CELL_LINUX_EBADR, 53, "Invalid request descriptor")
    F(CELL_LINUX_EXFULL, 54, "Exchange full")
    F(CELL_LINUX_ENOANO, 55, "No anode")
    F(CELL_LINUX_EBADRQC, 56, "Invalid request code")
    F(CELL_LINUX_EBADSLT, 57, "Invalid slot")
#ifndef UNIQUE
    F(CELL_LINUX_EDEADLOCK, 35, "Deadlock")
#else
    F(CELL_LINUX_EDEADLOCK, 58, "(Invalid) Deadlock")
#endif
    F(CELL_LINUX_EBFONT, 59, "Bad font file format")
    F(CELL_LINUX_ENOSTR, 60, "Device not a stream")
    F(CELL_LINUX_ENODATA, 61, "No data available")
    F(CELL_LINUX_ETIME, 62, "Timer expired")
    F(CELL_LINUX_ENOSR, 63, "Out of streams resources")
    F(CELL_LINUX_ENONET, 64, "Machine is not on the network")
    F(CELL_LINUX_ENOPKG, 65, "Package not installed")
    F(CELL_LINUX_EREMOTE, 66, "Object is remote")
    F(CELL_LINUX_ENOLINK, 67, "Link has been severed")
    F(CELL_LINUX_EADV, 68, "Advertise error")
    F(CELL_LINUX_ESRMNT, 69, "Srmount error")
    F(CELL_LINUX_ECOMM, 70, "Communication error on send")
    F(CELL_LINUX_EPROTO, 71, "Protocol error")
    F(CELL_LINUX_EMULTIHOP, 72, "Multihop attempted")
    F(CELL_LINUX_EDOTDOT, 73, "RFS specific error")
    F(CELL_LINUX_EBADMSG, 74, "Not a data message")
    F(CELL_LINUX_EOVERFLOW, 75, "Value too large for defined data type")
    F(CELL_LINUX_ENOTUNIQ, 76, "Name not unique on network")
    F(CELL_LINUX_EBADFD, 77, "File descriptor in bad state")
    F(CELL_LINUX_EREMCHG, 78, "Remote address changed")
    F(CELL_LINUX_ELIBACC, 79, "Can not access a needed shared library")
    F(CELL_LINUX_ELIBBAD, 80, "Accessing a corrupted shared library")
    F(CELL_LINUX_ELIBSCN, 81, ".lib section in a.out corrupted")
    F(CELL_LINUX_ELIBMAX, 82, "Attempting to link in too many shared libraries")
    F(CELL_LINUX_ELIBEXEC, 83, "Cannot exec a shared library directly")
    F(CELL_LINUX_EILSEQ, 84, "Illegal byte sequence")
    F(CELL_LINUX_ERESTART, 85, "Interrupted system call should be restarted")
    F(CELL_LINUX_ESTRPIPE, 86, "Streams pipe error")
    F(CELL_LINUX_EUSERS, 87, "Too many users")
    F(CELL_LINUX_ENOTSOCK, 88, "Socket operation on non-socket")
    F(CELL_LINUX_EDESTADDRREQ, 89, "Destination address required")
    F(CELL_LINUX_EMSGSIZE, 90, "Message too long")
    F(CELL_LINUX_EPROTOTYPE, 91, "Protocol wrong type for socket")
    F(CELL_LINUX_ENOPROTOOPT, 92, "Protocol not available")
    F(CELL_LINUX_EPROTONOSUPPORT, 93, "Protocol not supported")
    F(CELL_LINUX_ESOCKTNOSUPPORT, 94, "Socket type not supported")
    F(CELL_LINUX_EOPNOTSUPP, 95, "Operation not supported on transport endpoint")
    F(CELL_LINUX_EPFNOSUPPORT, 96, "Protocol family not supported")
    F(CELL_LINUX_EAFNOSUPPORT, 97, "Address family not supported by protocol")
    F(CELL_LINUX_EADDRINUSE, 98, "Address already in use")
    F(CELL_LINUX_EADDRNOTAVAIL, 99, "Cannot assign requested address")
    F(CELL_LINUX_ENETDOWN, 100, "Network is down")
    F(CELL_LINUX_ENETUNREACH, 101, "Network is unreachable")
    F(CELL_LINUX_ENETRESET, 102, "Network dropped connection because of reset")
    F(CELL_LINUX_ECONNABORTED, 103, "Software caused connection abort")
    F(CELL_LINUX_ECONNRESET, 104, "Connection reset by peer")
    F(CELL_LINUX_ENOBUFS, 105, "No buffer space available")
    F(CELL_LINUX_EISCONN, 106, "Transport endpoint is already connected")
    F(CELL_LINUX_ENOTCONN, 107, "Transport endpoint is not connected")
    F(CELL_LINUX_ESHUTDOWN, 108, "Cannot send after transport endpoint shutdown")
    F(CELL_LINUX_ETOOMANYREFS, 109, "Too many references: cannot splice")
    F(CELL_LINUX_ETIMEDOUT, 110, "Connection timed out")
    F(CELL_LINUX_ECONNREFUSED, 111, "Connection refused")
    F(CELL_LINUX_EHOSTDOWN, 112, "Host is down")
    F(CELL_LINUX_EHOSTUNREACH, 113, "No route to host")
    F(CELL_LINUX_EALREADY, 114, "Operation already in progress")
    F(CELL_LINUX_EINPROGRESS, 115, "Operation now in progress")
    F(CELL_LINUX_ESTALE, 116, "Stale NFS file handle")
    F(CELL_LINUX_EUCLEAN, 117, "Structure needs cleaning")
    F(CELL_LINUX_ENOTNAM, 118, "Not a XENIX named type file")
    F(CELL_LINUX_ENAVAIL, 119, "No XENIX semaphores available")
    F(CELL_LINUX_EISNAM, 120, "Is a named type file")
    F(CELL_LINUX_EREMOTEIO, 121, "Remote I/O error")
    F(CELL_LINUX_EDQUOT, 122, "Quota exceeded")
    F(CELL_LINUX_ENOMEDIUM, 123, "No medium found")
    F(CELL_LINUX_EMEDIUMTYPE, 124, "Wrong medium type")
    F(CELL_LINUX_ECANCELED, 125, "Operation Canceled")
    F(CELL_LINUX_ENOKEY, 126, "Required key not available")
    F(CELL_LINUX_EKEYEXPIRED, 127, "Key has expired")
    F(CELL_LINUX_EKEYREVOKED, 128, "Key has been revoked")
    F(CELL_LINUX_EKEYREJECTED, 129, "Key was rejected by service")
    F(CELL_LINUX_EOWNERDEAD, 130, "Owner died")
    F(CELL_LINUX_ENOTRECOVERABLE, 131, "State not recoverable")
