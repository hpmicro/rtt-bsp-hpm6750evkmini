/*
 * Copyright (c) 2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-18     Fan YANG     the first version
 */
#ifndef SES_LIBC_STUB_H
#define SES_LIBC_STUB_H



#ifndef ENOTTY
#define ENOTTY           25
#endif

#ifndef ENODATA
#define ENODATA          61
#endif

#ifndef EINTR
#define EINTR            4
#endif
#ifndef EIO
#define EIO              5
#endif

#ifndef O_RDONLY
#define O_RDONLY         0
#endif
#ifndef O_WRONLY
#define O_WRONLY         1
#endif
#ifndef O_RDWR
#define O_RDWR           2
#endif
#ifndef O_NONBLOCK
#define O_NONBLOCK       0x4000
#endif

#ifndef O_APPEND
#define O_APPEND         0x8
#endif

#ifndef O_CREAT
#define O_CREAT          0x200
#endif
#ifndef O_TRUNC
#define O_TRUNC          0x400
#endif
#ifndef O_EXCL
#define O_EXCL           0x800
#endif
#ifndef O_ACCMODE
#define O_ACCMODE        (O_RDONLY|O_WRONLY|O_RDWR)
#endif

#ifndef O_NOFOLLOW
#define O_NOFOLLOW       0x100000
#endif

#ifndef O_DIRECTORY
#define O_DIRECTORY      0x200000
#endif

#ifndef O_EXEC
#define O_EXEC           0x400000
#endif

#ifndef O_TMPFILE
#define O_TMPFILE        0x800000
#endif

#ifndef F_DUPFD
#define F_DUPFD          0
#endif

#ifndef F_GETFD
#define F_GETFD          1
#endif

#ifndef F_SETFD
#define F_SETFD          2
#endif

#ifndef F_GETFL
#define F_GETFL          3
#endif
#ifndef F_SETFL
#define F_SETFL          4
#endif
#ifndef F_GETLK
#define F_GETLK          7
#endif
#ifndef F_SETLK
#define F_SETLK          8
#endif

#ifndef F_SETLKW
#define F_SETLKW         14
#endif

#ifndef EINTR
#define EINTR            4
#endif
#ifndef EIO
#define EIO              5
#endif
#ifndef EBADF
#define EBADF            9
#endif
#ifndef EXDEV
#define EXDEV            18
#endif
#ifndef ENOTDIR
#define ENOTDIR          20
#endif
#ifndef EISDIR
#define EISDIR           21
#endif
#ifndef ENFILE
#define ENFILE           23
#endif
#ifndef EROFS
#define EROFS            30
#endif
#ifndef ENODATA
#define ENODATA          61
#endif
#ifndef EOVERFLOW
#define EOVERFLOW        75
#endif
#ifndef ENOTSOCK
#define ENOTSOCK         88
#endif
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL    99
#endif

#ifndef ENXIO
#define ENXIO            9966
#endif

#ifndef S_ISDIR
#define S_ISDIR(m) (((m)&_IFMT) == _IFDIR)
#endif
#ifndef S_ISLNK
#define S_ISLNK(m) (((m)&_IFMT) == _IFLNK)
#endif

#ifndef S_ISCHR
#define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#endif

#ifndef S_ISBLK
#define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#endif

/* LWIP errno.h stub */
#ifndef EWOULDBLOCK
#define EWOULDBLOCK      11
#endif
#ifndef EMSGSIZE
#define EMSGSIZE         90
#endif
#ifndef ENOPROTOOPT
#define ENOPROTOOPT      92
#endif
#ifndef EOPNOTSUPP
#define EOPNOTSUPP       95
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT     97
#endif
#ifndef EADDRINUSE
#define EADDRINUSE       98
#endif
#ifndef ECONNABORTED
#define ECONNABORTED     103
#endif
#ifndef ECONNRESET
#define ECONNRESET       104
#endif
#ifndef EISCONN
#define EISCONN          106
#endif
#ifndef ENOTCONN
#define ENOTCONN         107
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH     113
#endif
#ifndef EINPROGRESS
#define EINPROGRESS      115
#endif


typedef long _off_t;
typedef signed long _ssize_t ;
struct _reent
{
    int _errno;
};


#endif /* SES_LIBC_STUB_H */
