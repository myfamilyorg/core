/********************************************************************************
 * MIT License
 *
 * Copyright (c) 2025 Christopher Gilliard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

bool _debug_no_write = false;

#define SET_ERR_VALUE         \
	if (ret < 0) {        \
		errno = -ret; \
		return -1;    \
	}

#define SET_ERR       \
	SET_ERR_VALUE \
	return ret;

#ifdef __aarch64__

#define SYS_write 64
#define SYS_setitimer 103
#define SYS_gettimeofday 169
#define SYS_rt_sigaction 134

#define SYSCALL_EXIT                 \
	__asm__ volatile(            \
	    "mov x8, #93\n"          \
	    "mov x0, %0\n"           \
	    "svc #0\n"               \
	    :                        \
	    : "r"((i64)status)       \
	    : "x8", "x0", "memory"); \
	while (true) {               \
	}

#define SYSCALL_RESTORER     \
	__asm__ volatile(    \
	    "mov x8, #139\n" \
	    "svc #0\n" ::    \
		: "x8", "memory");

STATIC __inline__ i64 raw_syscall(i64 sysno, i64 a0, i64 a1, i64 a2, i64 a3,
				  i64 a4, i64 a5) {
	i64 result;
	__asm__ volatile(
	    "mov x8, %1\n"
	    "mov x0, %2\n"
	    "mov x1, %3\n"
	    "mov x2, %4\n"
	    "mov x3, %5\n"
	    "mov x4, %6\n"
	    "mov x5, %7\n"
	    "svc #0\n"
	    "mov %0, x0\n"
	    : "=r"(result)
	    : "r"(sysno), "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5)
	    : "x0", "x1", "x2", "x3", "x4", "x5", "x8", "memory");
	return result;
}

#endif /* __aarch64__ */

PUBLIC i64 write(i32 fd, const void *buf, u64 count) {
	i64 ret;
	if ((fd == 1 || fd == 2) && _debug_no_write) return count;
	ret = raw_syscall(SYS_write, (i64)fd, (i64)buf, (i64)count, 0, 0, 0);
	SET_ERR
}

i32 setitimer(i32 which, const struct itimerval *new_value,
	      struct itimerval *old_value) {
	i32 ret = (i32)raw_syscall(SYS_setitimer, (i64)which, (i64)new_value,
				   (i64)old_value, 0, 0, 0);
	SET_ERR
}

void restorer(void){SYSCALL_RESTORER}

PUBLIC void exit(i32 status) {
	execute_exits();
	SYSCALL_EXIT
}

i32 gettimeofday(struct timeval *tv, void *tz) {
	i32 ret =
	    (i32)raw_syscall(SYS_gettimeofday, (i64)tv, (i64)tz, 0, 0, 0, 0);
	SET_ERR
}

i32 rt_sigaction(i32 signum, const struct rt_sigaction *act,
		 struct rt_sigaction *oldact, u64 sigsetsize) {
	i32 ret = (i32)raw_syscall(SYS_rt_sigaction, (i64)signum, (i64)act,
				   (i64)oldact, (i64)sigsetsize, 0, 0);
	SET_ERR
}

