//#include <stdio.h>
#ifdef TOET
#ifdef __arm__
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <sys/stat.h>

#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#ifdef __STM32
#ifdef STM32F0XX
#include <stm32f0xx.h>
#else
#include <stm32f10x.h>
#endif
#endif
//#include "system.h"
#include "Sys.h"

#ifdef __cplusplus
extern "C" {
#endif
int errno;
/**
 new operator. Redefined not to throw exceptions.
 */
void *operator new(size_t size) {
//	return malloc(size);
	return malloc(size);
}

void *operator new[](size_t size) {
//	return malloc(size);
	while(1);
	return (void*)0;
}

/**
 delete operator. Redefined not to throw exceptions.
 */
void operator delete(void *p) {
//	free(p);
	while(1);
}

void operator delete[](void *p) {
//	free(p);
	while(1);
}

extern "C" void __cxa_pure_virtual() {while (1);};
extern "C" void _init() {};

namespace __gnu_cxx {

	/**
	 Replaces the default verbose terminate handler.
	 Avoids the inclusion of code to demangle C++ names.
	 */
	void __verbose_terminate_handler() {
//	abort();
		while(1);
	}
} //namespace __gnu_cxx

int __register_exitproc( int type , void (*fn) (void) , void *arg , void *d){
	return 0;
}

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/**
 Required by C++ standard library.
 See http://lists.debian.org/debian-gcc/2003/07/msg00057.html
 */
void *__dso_handle=(void*) &__dso_handle;
/**
 _exit, restarts the system
 */

/**
 __malloc_lock, no need to lock malloc
 */
void __malloc_lock() {
	//Do nothing
}

/**
 __malloc_unlock, no need to lock malloc
 */
void __malloc_unlock() {
	//Do nothing
}

#undef errno
extern int errno;

int close(int file) {
	return -1;
}

//void abort(){};

/*
 link
 Establish a new name for an existing file. Minimal implementation:
 */

/*
 lseek
 Set position in a file. Minimal implementation:
 */
off_t lseek(int file, off_t ptr, int dir) {
	return 0;
}
off_t _lseek_r(_reent* ree,int file, off_t ptr, int dir) {
	return 0;
}

//void free(void *a){};

/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */
void *sbrk_r(ptrdiff_t incr) {
	return sbrk(incr);
}
static char *heap_end;
void *sbrk(ptrdiff_t incr) {

	extern char _ebss; // Defined by the linker
	char *prev_heap_end;

	if (heap_end == 0) {
		heap_end = &_ebss;
	}
	prev_heap_end = heap_end;
#ifdef __STM32
	char * stack = (char*) __get_MSP();
#else
	extern char* _stack;
	char *stack=_stack;
#endif
	if (heap_end + incr > stack)
	{
//         _write (STDERR_FILENO, "Heap and stack collision\n", 25);
		errno = ENOMEM;
		while(1);
		return (caddr_t) -1;
		//abort ();
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}

/*
 read
 Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
 Returns -1 on error or blocks until the number of characters have been read.
 */

int read(int file, void *ptr, size_t len) {

	return 0;
}

/*
 stat
 Status of a file (by name). Minimal implementation:
 int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */

int stat(const char *filepath, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

/*
 write
 Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
 Returns -1 on error or number of bytes sent
 */
/*int _write(int file, char *ptr, int len) {
 return 0;
 }*/

int _ctype(char c) {
	return 0;
}

#ifndef STDOUT_USART
#define STDOUT_USART 2
#endif

#ifndef STDERR_USART
#define STDERR_USART 2
#endif

#ifndef STDIN_USART
#define STDIN_USART 2
#endif

#undef errno
extern int errno;

/*
 environ
 A pointer to a list of environment variables and their values.
 For a minimal environment, this empty list is adequate:
 */
char *__env[1] = {0};
char **environ = __env;

int _write(int file, char *ptr, int len);

void _exit(int status) {
	while (1) {
		;
	}
}

int _close(int file) {
	return -1;
}
/*
 execve
 Transfer control to a new process. Minimal implementation (for a system without processes):
 */
int _execve(char *name, char **argv, char **env) {
	errno = ENOMEM;
	return -1;
}
/*
 fork
 Create a new process. Minimal implementation (for a system without processes):
 */

int _fork() {
	errno = EAGAIN;
	return -1;
}
/*
 fstat
 Status of an open file. For consistency with other minimal implementations in these examples,
 all files are regarded as character special devices.
 The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
 */
int _fstat(int file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

/*
 getpid
 Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
 */

int _getpid() {
	return 1;
}

/*
 isatty
 Query whether output stream is a terminal. For consistency with the other minimal implementations,
 */
int _isatty(int file) {
	switch (file) {
		case STDOUT_FILENO:
		case STDERR_FILENO:
		case STDIN_FILENO:
		return 1;
		default:
		//errno = ENOTTY;
		errno = EBADF;
		return 0;
	}
}

/*
 kill
 Send a signal. Minimal implementation:
 */
int _kill(int pid, int sig) {
	errno = EINVAL;
	return (-1);
}

/*
 link
 Establish a new name for an existing file. Minimal implementation:
 */

int _link(char *old, char *nw) {
	errno = EMLINK;
	return -1;
}

/*
 lseek
 Set position in a file. Minimal implementation:
 */
int _lseek(int file, int ptr, int dir) {
	return 0;
}

/* Register name faking - works in collusion with the linker.  */
register char * stack_ptr asm ("sp");
void* _sbrk_r (struct _reent *r, ptrdiff_t incr)
{
	extern char end asm ("end"); /* Defined by the linker.  */
	static char * heap_end;
	char * prev_heap_end;

	if (heap_end == NULL)
	heap_end = & end;

	prev_heap_end = heap_end;

	if (heap_end + incr > stack_ptr)
	{
		/* Some of the libstdc++-v3 tests rely upon detecting
		 out of memory errors, so do not abort here.  */
#if 0
		extern void abort (void);

		_write (1, "_sbrk: Heap and stack collision\n", 32);

		abort ();
#else
		errno = ENOMEM;
		return (caddr_t) -1;
#endif
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */
/*caddr_t _sbrk(int incr) {

 extern char _ebss; // Defined by the linker
 static char *heap_end;
 char *prev_heap_end;

 if (heap_end == 0) {
 heap_end = &_ebss;
 }
 prev_heap_end = heap_end;

 char * stack = (char*) __get_MSP();
 if (heap_end + incr >  stack)
 {
 _write (STDERR_FILENO, "Heap and stack collision\n", 25);
 errno = ENOMEM;
 return  (caddr_t) -1;
 //abort ();
 }

 heap_end += incr;
 return (caddr_t) prev_heap_end;

 }*/

/*
 read
 Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
 Returns -1 on error or blocks until the number of characters have been read.
 */

int _read(int file, char *ptr, int len) {

	errno = EBADF;
	return -1;

}

/*
 stat
 Status of a file (by name). Minimal implementation:
 int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */

int _stat(const char *filepath, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

/*
 times
 Timing information for current process. Minimal implementation:
 */

clock_t _times(struct tms *buf) {
	return -1;
}

/*
 unlink
 Remove a file's directory entry. Minimal implementation:
 */
int _unlink(char *name) {
	errno = ENOENT;
	return -1;
}

/*
 wait
 Wait for a child process. Minimal implementation:
 */
int _wait(int *status) {
	errno = ECHILD;
	return -1;
}

/*
 write
 Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
 Returns -1 on error or number of bytes sent
 */
int _write(int file, char *ptr, int len) {

	errno = EBADF;
	return -1;

}

#ifdef __cplusplus
}
#endif
#endif
#endif
