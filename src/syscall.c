bool _debug_no_write = false;

#define SYS_write 64

#define SET_ERR_VALUE         \
	if (ret < 0) {        \
		errno = -ret; \
		return -1;    \
	}

#define SET_ERR       \
	SET_ERR_VALUE \
	return ret;

static __inline__ i64 raw_syscall(i64 sysno, i64 a0, i64 a1, i64 a2, i64 a3,
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

static __inline__ i64 syscall_write(i32 fd, const void *buf, u64 count) {
	return raw_syscall(SYS_write, (i64)fd, (i64)buf, (i64)count, 0, 0, 0);
}

PUBLIC i64 write(i32 fd, const void *buf, u64 count) {
	i64 ret;
	if ((fd == 1 || fd == 2) && _debug_no_write) return count;
	ret = raw_syscall(SYS_write, (i64)fd, (i64)buf, (i64)count, 0, 0, 0);
	SET_ERR
}

