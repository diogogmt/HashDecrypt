# 1 "md5.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "md5.cpp"
# 54 "md5.cpp"
# 1 "md5.h" 1
# 63 "md5.h"
typedef unsigned char md5_byte_t;
typedef unsigned int md5_word_t;


typedef struct md5_state_s {
    md5_word_t count[2];
    md5_word_t abcd[4];
    md5_byte_t buf[64];
} md5_state_t;


extern "C"
{



void md5_init(md5_state_t *pms);


void md5_append(md5_state_t *pms, const md5_byte_t *data, int nbytes);


void md5_finish(md5_state_t *pms, md5_byte_t digest[16]);


}
# 55 "md5.cpp" 2
# 1 "/usr/include/c++/4.2.1/cstring" 1 3
# 48 "/usr/include/c++/4.2.1/cstring" 3
       
# 49 "/usr/include/c++/4.2.1/cstring" 3

# 1 "/usr/include/c++/4.2.1/bits/c++config.h" 1 3
# 41 "/usr/include/c++/4.2.1/bits/c++config.h" 3
# 1 "/usr/include/c++/4.2.1/bits/os_defines.h" 1 3
# 61 "/usr/include/c++/4.2.1/bits/os_defines.h" 3
# 1 "/usr/include/unistd.h" 1 3 4
# 71 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/_types.h" 1 3 4
# 27 "/usr/include/_types.h" 3 4
# 1 "/usr/include/sys/_types.h" 1 3 4
# 32 "/usr/include/sys/_types.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 406 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/sys/_symbol_aliasing.h" 1 3 4
# 407 "/usr/include/sys/cdefs.h" 2 3 4
# 472 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/sys/_posix_availability.h" 1 3 4
# 473 "/usr/include/sys/cdefs.h" 2 3 4
# 33 "/usr/include/sys/_types.h" 2 3 4
# 1 "/usr/include/machine/_types.h" 1 3 4
# 32 "/usr/include/machine/_types.h" 3 4
# 1 "/usr/include/i386/_types.h" 1 3 4
# 37 "/usr/include/i386/_types.h" 3 4
typedef signed char __int8_t;



typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
# 70 "/usr/include/i386/_types.h" 3 4
typedef int __darwin_ct_rune_t;





typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;

typedef __mbstate_t __darwin_mbstate_t;


typedef long int __darwin_ptrdiff_t;





typedef long unsigned int __darwin_size_t;





typedef __builtin_va_list __darwin_va_list;





typedef int __darwin_wchar_t;




typedef __darwin_wchar_t __darwin_rune_t;


typedef int __darwin_wint_t;




typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
# 33 "/usr/include/machine/_types.h" 2 3 4
# 34 "/usr/include/sys/_types.h" 2 3 4
# 58 "/usr/include/sys/_types.h" 3 4
struct __darwin_pthread_handler_rec
{
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};
struct _opaque_pthread_attr_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_cond_t { long __sig; char __opaque[40]; };
struct _opaque_pthread_condattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_mutex_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_mutexattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_once_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_rwlock_t { long __sig; char __opaque[192]; };
struct _opaque_pthread_rwlockattr_t { long __sig; char __opaque[16]; };
struct _opaque_pthread_t { long __sig; struct __darwin_pthread_handler_rec *__cleanup_stack; char __opaque[1168]; };
# 94 "/usr/include/sys/_types.h" 3 4
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;

typedef __darwin_ino64_t __darwin_ino_t;



typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef struct _opaque_pthread_attr_t
   __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t
   __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t
   __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t
   __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t
   __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t
   __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t
   __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t
   __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t
   *__darwin_pthread_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];
# 28 "/usr/include/_types.h" 2 3 4
# 39 "/usr/include/_types.h" 3 4
typedef int __darwin_nl_item;
typedef int __darwin_wctrans_t;

typedef __uint32_t __darwin_wctype_t;
# 72 "/usr/include/unistd.h" 2 3 4
# 1 "/usr/include/sys/unistd.h" 1 3 4
# 138 "/usr/include/sys/unistd.h" 3 4
struct accessx_descriptor {
 unsigned int ad_name_offset;
 int ad_flags;
 int ad_pad[2];
};
# 73 "/usr/include/unistd.h" 2 3 4
# 1 "/usr/include/Availability.h" 1 3 4
# 144 "/usr/include/Availability.h" 3 4
# 1 "/usr/include/AvailabilityInternal.h" 1 3 4
# 145 "/usr/include/Availability.h" 2 3 4
# 74 "/usr/include/unistd.h" 2 3 4



typedef __darwin_gid_t gid_t;




typedef __darwin_intptr_t intptr_t;




typedef __darwin_off_t off_t;




typedef __darwin_pid_t pid_t;






typedef __darwin_size_t size_t;




typedef __darwin_ssize_t ssize_t;




typedef __darwin_uid_t uid_t;




typedef __darwin_useconds_t useconds_t;
# 458 "/usr/include/unistd.h" 3 4
extern "C" {
void _exit(int) __attribute__((noreturn));
int access(const char *, int);
unsigned int
  alarm(unsigned int);
int chdir(const char *);
int chown(const char *, uid_t, gid_t);

int close(int) __asm("_" "close" );

int dup(int);
int dup2(int, int);
int execl(const char *, const char *, ...);
int execle(const char *, const char *, ...);
int execlp(const char *, const char *, ...);
int execv(const char *, char * const *);
int execve(const char *, char * const *, char * const *);
int execvp(const char *, char * const *);
pid_t fork(void);
long fpathconf(int, int);
char *getcwd(char *, size_t);
gid_t getegid(void);
uid_t geteuid(void);
gid_t getgid(void);



int getgroups(int, gid_t []);

char *getlogin(void);
pid_t getpgrp(void);
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
int isatty(int);
int link(const char *, const char *);
off_t lseek(int, off_t, int);
long pathconf(const char *, int);

int pause(void) __asm("_" "pause" );

int pipe(int [2]);

ssize_t read(int, void *, size_t) __asm("_" "read" );

int rmdir(const char *);
int setgid(gid_t);
int setpgid(pid_t, pid_t);
pid_t setsid(void);
int setuid(uid_t);

unsigned int
  sleep(unsigned int) __asm("_" "sleep" );

long sysconf(int);
pid_t tcgetpgrp(int);
int tcsetpgrp(int, pid_t);
char *ttyname(int);


int ttyname_r(int, char *, size_t) __asm("_" "ttyname_r" );




int unlink(const char *);

ssize_t write(int, const void *, size_t) __asm("_" "write" );
}
# 535 "/usr/include/unistd.h" 3 4
extern "C" {
size_t confstr(int, char *, size_t) __asm("_" "confstr" );

int getopt(int, char * const [], const char *) __asm("_" "getopt" );

extern char *optarg;
extern int optind, opterr, optopt;
}
# 560 "/usr/include/unistd.h" 3 4
 extern "C" {




void *brk(const void *);
int chroot(const char *) ;


char *crypt(const char *, const char *);



char *ctermid(char *);


void encrypt(char *, int) __asm("_" "encrypt" );



int fchdir(int);
long gethostid(void);
pid_t getpgid(pid_t);
pid_t getsid(pid_t);



int getdtablesize(void) ;
int getpagesize(void) __attribute__((const)) ;
char *getpass(const char *) ;




char *getwd(char *) ;


int lchown(const char *, uid_t, gid_t) __asm("_" "lchown" );

int lockf(int, int, off_t) __asm("_" "lockf" );

int nice(int) __asm("_" "nice" );

ssize_t pread(int, void *, size_t, off_t) __asm("_" "pread" );

ssize_t pwrite(int, const void *, size_t, off_t) __asm("_" "pwrite" );





void *sbrk(int);



pid_t setpgrp(void) __asm("_" "setpgrp" );




int setregid(gid_t, gid_t) __asm("_" "setregid" );

int setreuid(uid_t, uid_t) __asm("_" "setreuid" );

void swab(const void * , void * , ssize_t);
void sync(void);
int truncate(const char *, off_t);
useconds_t ualarm(useconds_t, useconds_t);
int usleep(useconds_t) __asm("_" "usleep" );
pid_t vfork(void);


int fsync(int) __asm("_" "fsync" );

int ftruncate(int, off_t);
int getlogin_r(char *, size_t);
}
# 647 "/usr/include/unistd.h" 3 4
extern "C" {
int fchown(int, uid_t, gid_t);
int gethostname(char *, size_t);
ssize_t readlink(const char * , char * , size_t);
int setegid(gid_t);
int seteuid(uid_t);
int symlink(const char *, const char *);
}







# 1 "/usr/include/sys/select.h" 1 3 4
# 66 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/sys/appleapiopts.h" 1 3 4
# 67 "/usr/include/sys/select.h" 2 3 4
# 78 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/sys/_structs.h" 1 3 4
# 88 "/usr/include/sys/_structs.h" 3 4
struct timespec
{
 __darwin_time_t tv_sec;
 long tv_nsec;
};







struct timeval
{
 __darwin_time_t tv_sec;
 __darwin_suseconds_t tv_usec;
};
# 183 "/usr/include/sys/_structs.h" 3 4
extern "C" {
typedef struct fd_set {
 __int32_t fds_bits[((((1024) % ((sizeof(__int32_t) * 8))) == 0) ? ((1024) / ((sizeof(__int32_t) * 8))) : (((1024) / ((sizeof(__int32_t) * 8))) + 1))];
} fd_set;
}


static inline int
__darwin_fd_isset(int _n, const struct fd_set *_p)
{
 return (_p->fds_bits[_n/(sizeof(__int32_t) * 8)] & (1<<(_n % (sizeof(__int32_t) * 8))));
}
# 79 "/usr/include/sys/select.h" 2 3 4
# 87 "/usr/include/sys/select.h" 3 4
typedef __darwin_time_t time_t;




typedef __darwin_suseconds_t suseconds_t;




typedef __darwin_sigset_t sigset_t;
# 134 "/usr/include/sys/select.h" 3 4
extern "C" {


int pselect(int, fd_set * , fd_set * ,
  fd_set * , const struct timespec * ,
  const sigset_t * )




  __asm("_" "pselect" "$1050")




  ;


# 1 "/usr/include/sys/_select.h" 1 3 4
# 39 "/usr/include/sys/_select.h" 3 4
int select(int, fd_set * , fd_set * ,
  fd_set * , struct timeval * )




  __asm("_" "select" "$1050")




  ;
# 153 "/usr/include/sys/select.h" 2 3 4

}
# 663 "/usr/include/unistd.h" 2 3 4



typedef __darwin_dev_t dev_t;




typedef __darwin_mode_t mode_t;




typedef __darwin_uuid_t uuid_t;


extern "C" {
void _Exit(int) __attribute__((noreturn));
int accessx_np(const struct accessx_descriptor *, size_t, int *, uid_t);
int acct(const char *);
int add_profil(char *, size_t, unsigned long, unsigned int);
void endusershell(void);
int execvP(const char *, const char *, char * const *);
char *fflagstostr(unsigned long);
int getdomainname(char *, int);
int getgrouplist(const char *, int, int *, int *);
int gethostuuid(uuid_t, const struct timespec *) __attribute__((visibility("default")));
mode_t getmode(const void *, mode_t);
int getpeereid(int, uid_t *, gid_t *);
int getsgroups_np(int *, uuid_t);
char *getusershell(void);
int getwgroups_np(int *, uuid_t);
int initgroups(const char *, int);
int iruserok(unsigned long, int, const char *, const char *);
int iruserok_sa(const void *, int, int, const char *, const char *);
int issetugid(void);
char *mkdtemp(char *);
int mknod(const char *, mode_t, dev_t);
int mkpath_np(const char *path, mode_t omode) __attribute__((visibility("default")));
int mkstemp(char *);
int mkstemps(char *, int);
char *mktemp(char *);
int nfssvc(int, void *);
int profil(char *, size_t, unsigned long, unsigned int);
int pthread_setugid_np(uid_t, gid_t);
int pthread_getugid_np( uid_t *, gid_t *);
int rcmd(char **, int, const char *, const char *, const char *, int *);
int rcmd_af(char **, int, const char *, const char *, const char *, int *,
  int);
int reboot(int);
int revoke(const char *);
int rresvport(int *);
int rresvport_af(int *, int);
int ruserok(const char *, int, const char *, const char *);
int setdomainname(const char *, int);
int setgroups(int, const gid_t *);
void sethostid(long);
int sethostname(const char *, int);

void setkey(const char *) __asm("_" "setkey" );



int setlogin(const char *);
void *setmode(const char *) __asm("_" "setmode" );
int setrgid(gid_t);
int setruid(uid_t);
int setsgroups_np(int, const uuid_t);
void setusershell(void);
int setwgroups_np(int, const uuid_t);
int strtofflags(char **, unsigned long *, unsigned long *);
int swapon(const char *);
int syscall(int, ...);
int ttyslot(void);
int undelete(const char *);
int unwhiteout(const char *);
void *valloc(size_t);

extern char *suboptarg;
int getsubopt(char **, char * const *, char **);



int fgetattrlist(int,void*,void*,size_t,unsigned int) __attribute__((visibility("default")));
int fsetattrlist(int,void*,void*,size_t,unsigned int) __attribute__((visibility("default")));
int getattrlist(const char*,void*,void*,size_t,unsigned int) __asm("_" "getattrlist" );
int setattrlist(const char*,void*,void*,size_t,unsigned int) __asm("_" "setattrlist" );
int exchangedata(const char*,const char*,unsigned int);
int getdirentriesattr(int,void*,void*,size_t,unsigned int*,unsigned int*,unsigned int*,unsigned int);
# 763 "/usr/include/unistd.h" 3 4
struct fssearchblock;
struct searchstate;

int searchfs(const char *, struct fssearchblock *, unsigned long *, unsigned int, unsigned int, struct searchstate *);
int fsctl(const char *,unsigned long,void*,unsigned int);
int ffsctl(int,unsigned long,void*,unsigned int) __attribute__((visibility("default")));




int fsync_volume_np(int, int) __attribute__((visibility("default")));
int sync_volume_np(const char *, int) __attribute__((visibility("default")));

extern int optreset;

}
# 62 "/usr/include/c++/4.2.1/bits/os_defines.h" 2 3





extern "C" {
# 92 "/usr/include/c++/4.2.1/bits/os_defines.h" 3
extern void __dtrace_probe$cxa_runtime$cxa_exception_rethrow$v1(void);
extern int __dtrace_isenabled$cxa_runtime$cxa_exception_rethrow$v1(void);
extern void __dtrace_probe$cxa_runtime$cxa_exception_throw$v1$766f6964202a(void *);
extern int __dtrace_isenabled$cxa_runtime$cxa_exception_throw$v1(void);


}
# 42 "/usr/include/c++/4.2.1/bits/c++config.h" 2 3


# 1 "/usr/include/c++/4.2.1/bits/cpu_defines.h" 1 3
# 45 "/usr/include/c++/4.2.1/bits/c++config.h" 2 3
# 153 "/usr/include/c++/4.2.1/bits/c++config.h" 3
namespace std {
# 165 "/usr/include/c++/4.2.1/bits/c++config.h" 3
}
# 51 "/usr/include/c++/4.2.1/cstring" 2 3
# 1 "/usr/include/c++/4.2.1/cstddef" 1 3
# 48 "/usr/include/c++/4.2.1/cstddef" 3
       
# 49 "/usr/include/c++/4.2.1/cstddef" 3


# 1 "/usr/llvm-gcc-4.2/bin/../lib/gcc/i686-apple-darwin11/4.2.1/include/stddef.h" 1 3 4
# 152 "/usr/llvm-gcc-4.2/bin/../lib/gcc/i686-apple-darwin11/4.2.1/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 52 "/usr/include/c++/4.2.1/cstddef" 2 3

namespace std {

  using ::ptrdiff_t;
  using ::size_t;

}
# 52 "/usr/include/c++/4.2.1/cstring" 2 3
# 1 "/usr/include/string.h" 1 3 4
# 79 "/usr/include/string.h" 3 4
extern "C" {
void *memchr(const void *, int, size_t);
int memcmp(const void *, const void *, size_t);
void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
char *strcat(char *, const char *);
char *strchr(const char *, int);
int strcmp(const char *, const char *);
int strcoll(const char *, const char *);
char *strcpy(char *, const char *);
size_t strcspn(const char *, const char *);
char *strerror(int) __asm("_" "strerror" );
size_t strlen(const char *);
char *strncat(char *, const char *, size_t);
int strncmp(const char *, const char *, size_t);
char *strncpy(char *, const char *, size_t);
char *strpbrk(const char *, const char *);
char *strrchr(const char *, int);
size_t strspn(const char *, const char *);
char *strstr(const char *, const char *);
char *strtok(char *, const char *);
size_t strxfrm(char *, const char *, size_t);
}
# 113 "/usr/include/string.h" 3 4
extern "C" {
char *strtok_r(char *, const char *, char **);
}
# 125 "/usr/include/string.h" 3 4
extern "C" {
int strerror_r(int, char *, size_t);
char *strdup(const char *);
void *memccpy(void *, const void *, int, size_t);
}
# 139 "/usr/include/string.h" 3 4
extern "C" {
char *stpcpy(char *, const char *);
char *stpncpy(char *, const char *, size_t) __attribute__((visibility("default")));
char *strndup(const char *, size_t) __attribute__((visibility("default")));
size_t strnlen(const char *, size_t) __attribute__((visibility("default")));
char *strsignal(int sig);
}
# 158 "/usr/include/string.h" 3 4
extern "C" {
void *memmem(const void *, size_t, const void *, size_t) __attribute__((visibility("default")));
void memset_pattern4(void *, const void *, size_t) __attribute__((visibility("default")));
void memset_pattern8(void *, const void *, size_t) __attribute__((visibility("default")));
void memset_pattern16(void *, const void *, size_t) __attribute__((visibility("default")));

char *strcasestr(const char *, const char *);
char *strnstr(const char *, const char *, size_t);
size_t strlcat(char *, const char *, size_t);
size_t strlcpy(char *, const char *, size_t);
void strmode(int, char *);
char *strsep(char **, const char *);


void swab(const void * , void * , ssize_t);
}






# 1 "/usr/include/strings.h" 1 3 4
# 71 "/usr/include/strings.h" 3 4
extern "C" {


int bcmp(const void *, const void *, size_t) ;
void bcopy(const void *, void *, size_t) ;
void bzero(void *, size_t) ;
char *index(const char *, int) ;
char *rindex(const char *, int) ;


int ffs(int);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);
}



extern "C" {
int ffsl(long) __attribute__((visibility("default")));
int fls(int) __attribute__((visibility("default")));
int flsl(long) __attribute__((visibility("default")));
}

# 1 "/usr/include/string.h" 1 3 4
# 95 "/usr/include/strings.h" 2 3 4
# 181 "/usr/include/string.h" 2 3 4
# 53 "/usr/include/c++/4.2.1/cstring" 2 3
# 78 "/usr/include/c++/4.2.1/cstring" 3
namespace std {

  using ::memcpy;
  using ::memmove;
  using ::strcpy;
  using ::strncpy;
  using ::strcat;
  using ::strncat;
  using ::memcmp;
  using ::strcmp;
  using ::strcoll;
  using ::strncmp;
  using ::strxfrm;
  using ::strcspn;
  using ::strspn;
  using ::strtok;
  using ::memset;
  using ::strerror;
  using ::strlen;

  using ::memchr;

  inline void*
  memchr(void* __p, int __c, size_t __n)
  { return memchr(const_cast<const void*>(__p), __c, __n); }

  using ::strchr;

  inline char*
  strchr(char* __s1, int __n)
  { return __builtin_strchr(const_cast<const char*>(__s1), __n); }

  using ::strpbrk;

  inline char*
  strpbrk(char* __s1, const char* __s2)
  { return __builtin_strpbrk(const_cast<const char*>(__s1), __s2); }

  using ::strrchr;

  inline char*
  strrchr(char* __s1, int __n)
  { return __builtin_strrchr(const_cast<const char*>(__s1), __n); }

  using ::strstr;

  inline char*
  strstr(char* __s1, const char* __s2)
  { return __builtin_strstr(const_cast<const char*>(__s1), __s2); }

}
# 56 "md5.cpp" 2
# 131 "md5.cpp"
static void
md5_process(md5_state_t *pms, const md5_byte_t *data )
{
    md5_word_t
 a = pms->abcd[0], b = pms->abcd[1],
 c = pms->abcd[2], d = pms->abcd[3];
    md5_word_t t;





    md5_word_t xbuf[16];
    const md5_word_t *X;


    {






 static const int w = 1;

 if (*((const md5_byte_t *)&w))


 {




     if (!((data - (const md5_byte_t *)0) & 3)) {

  X = (const md5_word_t *)data;
     } else {

  memcpy(xbuf, data, 64);
  X = xbuf;
     }
 }


 else


 {




     const md5_byte_t *xp = data;
     int i;


     X = xbuf;



     for (i = 0; i < 16; ++i, xp += 4)
  xbuf[i] = xp[0] + (xp[1] << 8) + (xp[2] << 16) + (xp[3] << 24);
 }

    }
# 207 "md5.cpp"
    t = a + (((b) & (c)) | (~(b) & (d))) + X[0] + (((md5_word_t)~0) ^ 0x28955b87); a = (((t) << (7)) | ((t) >> (32 - (7)))) + b;
    t = d + (((a) & (b)) | (~(a) & (c))) + X[1] + (((md5_word_t)~0) ^ 0x173848a9); d = (((t) << (12)) | ((t) >> (32 - (12)))) + a;
    t = c + (((d) & (a)) | (~(d) & (b))) + X[2] + 0x242070db; c = (((t) << (17)) | ((t) >> (32 - (17)))) + d;
    t = b + (((c) & (d)) | (~(c) & (a))) + X[3] + (((md5_word_t)~0) ^ 0x3e423111); b = (((t) << (22)) | ((t) >> (32 - (22)))) + c;
    t = a + (((b) & (c)) | (~(b) & (d))) + X[4] + (((md5_word_t)~0) ^ 0x0a83f050); a = (((t) << (7)) | ((t) >> (32 - (7)))) + b;
    t = d + (((a) & (b)) | (~(a) & (c))) + X[5] + 0x4787c62a; d = (((t) << (12)) | ((t) >> (32 - (12)))) + a;
    t = c + (((d) & (a)) | (~(d) & (b))) + X[6] + (((md5_word_t)~0) ^ 0x57cfb9ec); c = (((t) << (17)) | ((t) >> (32 - (17)))) + d;
    t = b + (((c) & (d)) | (~(c) & (a))) + X[7] + (((md5_word_t)~0) ^ 0x02b96afe); b = (((t) << (22)) | ((t) >> (32 - (22)))) + c;
    t = a + (((b) & (c)) | (~(b) & (d))) + X[8] + 0x698098d8; a = (((t) << (7)) | ((t) >> (32 - (7)))) + b;
    t = d + (((a) & (b)) | (~(a) & (c))) + X[9] + (((md5_word_t)~0) ^ 0x74bb0850); d = (((t) << (12)) | ((t) >> (32 - (12)))) + a;
    t = c + (((d) & (a)) | (~(d) & (b))) + X[10] + (((md5_word_t)~0) ^ 0x0000a44e); c = (((t) << (17)) | ((t) >> (32 - (17)))) + d;
    t = b + (((c) & (d)) | (~(c) & (a))) + X[11] + (((md5_word_t)~0) ^ 0x76a32841); b = (((t) << (22)) | ((t) >> (32 - (22)))) + c;
    t = a + (((b) & (c)) | (~(b) & (d))) + X[12] + 0x6b901122; a = (((t) << (7)) | ((t) >> (32 - (7)))) + b;
    t = d + (((a) & (b)) | (~(a) & (c))) + X[13] + (((md5_word_t)~0) ^ 0x02678e6c); d = (((t) << (12)) | ((t) >> (32 - (12)))) + a;
    t = c + (((d) & (a)) | (~(d) & (b))) + X[14] + (((md5_word_t)~0) ^ 0x5986bc71); c = (((t) << (17)) | ((t) >> (32 - (17)))) + d;
    t = b + (((c) & (d)) | (~(c) & (a))) + X[15] + 0x49b40821; b = (((t) << (22)) | ((t) >> (32 - (22)))) + c;
# 233 "md5.cpp"
    t = a + (((b) & (d)) | ((c) & ~(d))) + X[1] + (((md5_word_t)~0) ^ 0x09e1da9d); a = (((t) << (5)) | ((t) >> (32 - (5)))) + b;
    t = d + (((a) & (c)) | ((b) & ~(c))) + X[6] + (((md5_word_t)~0) ^ 0x3fbf4cbf); d = (((t) << (9)) | ((t) >> (32 - (9)))) + a;
    t = c + (((d) & (b)) | ((a) & ~(b))) + X[11] + 0x265e5a51; c = (((t) << (14)) | ((t) >> (32 - (14)))) + d;
    t = b + (((c) & (a)) | ((d) & ~(a))) + X[0] + (((md5_word_t)~0) ^ 0x16493855); b = (((t) << (20)) | ((t) >> (32 - (20)))) + c;
    t = a + (((b) & (d)) | ((c) & ~(d))) + X[5] + (((md5_word_t)~0) ^ 0x29d0efa2); a = (((t) << (5)) | ((t) >> (32 - (5)))) + b;
    t = d + (((a) & (c)) | ((b) & ~(c))) + X[10] + 0x02441453; d = (((t) << (9)) | ((t) >> (32 - (9)))) + a;
    t = c + (((d) & (b)) | ((a) & ~(b))) + X[15] + (((md5_word_t)~0) ^ 0x275e197e); c = (((t) << (14)) | ((t) >> (32 - (14)))) + d;
    t = b + (((c) & (a)) | ((d) & ~(a))) + X[4] + (((md5_word_t)~0) ^ 0x182c0437); b = (((t) << (20)) | ((t) >> (32 - (20)))) + c;
    t = a + (((b) & (d)) | ((c) & ~(d))) + X[9] + 0x21e1cde6; a = (((t) << (5)) | ((t) >> (32 - (5)))) + b;
    t = d + (((a) & (c)) | ((b) & ~(c))) + X[14] + (((md5_word_t)~0) ^ 0x3cc8f829); d = (((t) << (9)) | ((t) >> (32 - (9)))) + a;
    t = c + (((d) & (b)) | ((a) & ~(b))) + X[3] + (((md5_word_t)~0) ^ 0x0b2af278); c = (((t) << (14)) | ((t) >> (32 - (14)))) + d;
    t = b + (((c) & (a)) | ((d) & ~(a))) + X[8] + 0x455a14ed; b = (((t) << (20)) | ((t) >> (32 - (20)))) + c;
    t = a + (((b) & (d)) | ((c) & ~(d))) + X[13] + (((md5_word_t)~0) ^ 0x561c16fa); a = (((t) << (5)) | ((t) >> (32 - (5)))) + b;
    t = d + (((a) & (c)) | ((b) & ~(c))) + X[2] + (((md5_word_t)~0) ^ 0x03105c07); d = (((t) << (9)) | ((t) >> (32 - (9)))) + a;
    t = c + (((d) & (b)) | ((a) & ~(b))) + X[7] + 0x676f02d9; c = (((t) << (14)) | ((t) >> (32 - (14)))) + d;
    t = b + (((c) & (a)) | ((d) & ~(a))) + X[12] + (((md5_word_t)~0) ^ 0x72d5b375); b = (((t) << (20)) | ((t) >> (32 - (20)))) + c;
# 259 "md5.cpp"
    t = a + ((b) ^ (c) ^ (d)) + X[5] + (((md5_word_t)~0) ^ 0x0005c6bd); a = (((t) << (4)) | ((t) >> (32 - (4)))) + b;
    t = d + ((a) ^ (b) ^ (c)) + X[8] + (((md5_word_t)~0) ^ 0x788e097e); d = (((t) << (11)) | ((t) >> (32 - (11)))) + a;
    t = c + ((d) ^ (a) ^ (b)) + X[11] + 0x6d9d6122; c = (((t) << (16)) | ((t) >> (32 - (16)))) + d;
    t = b + ((c) ^ (d) ^ (a)) + X[14] + (((md5_word_t)~0) ^ 0x021ac7f3); b = (((t) << (23)) | ((t) >> (32 - (23)))) + c;
    t = a + ((b) ^ (c) ^ (d)) + X[1] + (((md5_word_t)~0) ^ 0x5b4115bb); a = (((t) << (4)) | ((t) >> (32 - (4)))) + b;
    t = d + ((a) ^ (b) ^ (c)) + X[4] + 0x4bdecfa9; d = (((t) << (11)) | ((t) >> (32 - (11)))) + a;
    t = c + ((d) ^ (a) ^ (b)) + X[7] + (((md5_word_t)~0) ^ 0x0944b49f); c = (((t) << (16)) | ((t) >> (32 - (16)))) + d;
    t = b + ((c) ^ (d) ^ (a)) + X[10] + (((md5_word_t)~0) ^ 0x4140438f); b = (((t) << (23)) | ((t) >> (32 - (23)))) + c;
    t = a + ((b) ^ (c) ^ (d)) + X[13] + 0x289b7ec6; a = (((t) << (4)) | ((t) >> (32 - (4)))) + b;
    t = d + ((a) ^ (b) ^ (c)) + X[0] + (((md5_word_t)~0) ^ 0x155ed805); d = (((t) << (11)) | ((t) >> (32 - (11)))) + a;
    t = c + ((d) ^ (a) ^ (b)) + X[3] + (((md5_word_t)~0) ^ 0x2b10cf7a); c = (((t) << (16)) | ((t) >> (32 - (16)))) + d;
    t = b + ((c) ^ (d) ^ (a)) + X[6] + 0x04881d05; b = (((t) << (23)) | ((t) >> (32 - (23)))) + c;
    t = a + ((b) ^ (c) ^ (d)) + X[9] + (((md5_word_t)~0) ^ 0x262b2fc6); a = (((t) << (4)) | ((t) >> (32 - (4)))) + b;
    t = d + ((a) ^ (b) ^ (c)) + X[12] + (((md5_word_t)~0) ^ 0x1924661a); d = (((t) << (11)) | ((t) >> (32 - (11)))) + a;
    t = c + ((d) ^ (a) ^ (b)) + X[15] + 0x1fa27cf8; c = (((t) << (16)) | ((t) >> (32 - (16)))) + d;
    t = b + ((c) ^ (d) ^ (a)) + X[2] + (((md5_word_t)~0) ^ 0x3b53a99a); b = (((t) << (23)) | ((t) >> (32 - (23)))) + c;
# 285 "md5.cpp"
    t = a + ((c) ^ ((b) | ~(d))) + X[0] + (((md5_word_t)~0) ^ 0x0bd6ddbb); a = (((t) << (6)) | ((t) >> (32 - (6)))) + b;
    t = d + ((b) ^ ((a) | ~(c))) + X[7] + 0x432aff97; d = (((t) << (10)) | ((t) >> (32 - (10)))) + a;
    t = c + ((a) ^ ((d) | ~(b))) + X[14] + (((md5_word_t)~0) ^ 0x546bdc58); c = (((t) << (15)) | ((t) >> (32 - (15)))) + d;
    t = b + ((d) ^ ((c) | ~(a))) + X[5] + (((md5_word_t)~0) ^ 0x036c5fc6); b = (((t) << (21)) | ((t) >> (32 - (21)))) + c;
    t = a + ((c) ^ ((b) | ~(d))) + X[12] + 0x655b59c3; a = (((t) << (6)) | ((t) >> (32 - (6)))) + b;
    t = d + ((b) ^ ((a) | ~(c))) + X[3] + (((md5_word_t)~0) ^ 0x70f3336d); d = (((t) << (10)) | ((t) >> (32 - (10)))) + a;
    t = c + ((a) ^ ((d) | ~(b))) + X[10] + (((md5_word_t)~0) ^ 0x00100b82); c = (((t) << (15)) | ((t) >> (32 - (15)))) + d;
    t = b + ((d) ^ ((c) | ~(a))) + X[1] + (((md5_word_t)~0) ^ 0x7a7ba22e); b = (((t) << (21)) | ((t) >> (32 - (21)))) + c;
    t = a + ((c) ^ ((b) | ~(d))) + X[8] + 0x6fa87e4f; a = (((t) << (6)) | ((t) >> (32 - (6)))) + b;
    t = d + ((b) ^ ((a) | ~(c))) + X[15] + (((md5_word_t)~0) ^ 0x01d3191f); d = (((t) << (10)) | ((t) >> (32 - (10)))) + a;
    t = c + ((a) ^ ((d) | ~(b))) + X[6] + (((md5_word_t)~0) ^ 0x5cfebceb); c = (((t) << (15)) | ((t) >> (32 - (15)))) + d;
    t = b + ((d) ^ ((c) | ~(a))) + X[13] + 0x4e0811a1; b = (((t) << (21)) | ((t) >> (32 - (21)))) + c;
    t = a + ((c) ^ ((b) | ~(d))) + X[4] + (((md5_word_t)~0) ^ 0x08ac817d); a = (((t) << (6)) | ((t) >> (32 - (6)))) + b;
    t = d + ((b) ^ ((a) | ~(c))) + X[11] + (((md5_word_t)~0) ^ 0x42c50dca); d = (((t) << (10)) | ((t) >> (32 - (10)))) + a;
    t = c + ((a) ^ ((d) | ~(b))) + X[2] + 0x2ad7d2bb; c = (((t) << (15)) | ((t) >> (32 - (15)))) + d;
    t = b + ((d) ^ ((c) | ~(a))) + X[9] + (((md5_word_t)~0) ^ 0x14792c6e); b = (((t) << (21)) | ((t) >> (32 - (21)))) + c;





    pms->abcd[0] += a;
    pms->abcd[1] += b;
    pms->abcd[2] += c;
    pms->abcd[3] += d;
}

void
md5_init(md5_state_t *pms)
{
    pms->count[0] = pms->count[1] = 0;
    pms->abcd[0] = 0x67452301;
    pms->abcd[1] = ((md5_word_t)~0) ^ 0x10325476;
    pms->abcd[2] = ((md5_word_t)~0) ^ 0x67452301;
    pms->abcd[3] = 0x10325476;
}

void
md5_append(md5_state_t *pms, const md5_byte_t *data, int nbytes)
{
    const md5_byte_t *p = data;
    int left = nbytes;
    int offset = (pms->count[0] >> 3) & 63;
    md5_word_t nbits = (md5_word_t)(nbytes << 3);

    if (nbytes <= 0)
 return;


    pms->count[1] += nbytes >> 29;
    pms->count[0] += nbits;
    if (pms->count[0] < nbits)
 pms->count[1]++;


    if (offset) {
 int copy = (offset + nbytes > 64 ? 64 - offset : nbytes);

 memcpy(pms->buf + offset, p, copy);
 if (offset + copy < 64)
     return;
 p += copy;
 left -= copy;
 md5_process(pms, pms->buf);
    }


    for (; left >= 64; p += 64, left -= 64)
 md5_process(pms, p);


    if (left)
 memcpy(pms->buf, p, left);
}

void
md5_finish(md5_state_t *pms, md5_byte_t digest[16])
{
    static const md5_byte_t pad[64] = {
 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    md5_byte_t data[8];
    int i;


    for (i = 0; i < 8; ++i)
 data[i] = (md5_byte_t)(pms->count[i >> 2] >> ((i & 3) << 3));

    md5_append(pms, pad, ((55 - (pms->count[0] >> 3)) & 63) + 1);

    md5_append(pms, data, 8);
    for (i = 0; i < 16; ++i)
 digest[i] = (md5_byte_t)(pms->abcd[i >> 2] >> ((i & 3) << 3));
}
