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

#ifndef _SYSCALL_H
#define _SYSCALL_H

i64 write(i32 fd, const void *buf, u64 count);
void exit(i32 status);
i32 setitimer(i32 which, const struct itimerval *new_value,
	      struct itimerval *old_value);
i32 rt_sigaction(i32 signum, const struct rt_sigaction *act,
		 struct rt_sigaction *oldact, u64 sigsetsize);
void restorer(void);
i32 gettimeofday(struct timeval *tv, void *tz);
i32 munmap(void *addr, u64 len);
void *mmap(void *addr, u64 length, i32 prot, i32 flags, i32 fd, i64 offset);

#endif /* _SYSCALL_H */
