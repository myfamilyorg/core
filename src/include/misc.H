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

#ifndef _MISC_H
#define _MISC_H

u64 strlen(const u8 *S);
u8 *strcpy(u8 *dest, const u8 *src);
void *memcpy(void *dst, const void *src, u64 n);
u64 u128_to_string_impl(u8 *buf, u128 v, bool hex, bool upper);
u64 i128_to_string_impl(u8 *buf, i128 v, bool hex, bool upper);
u128 string_to_uint128(const u8 *buf, u64 len);
i128 string_to_int128(const u8 *buf, u64 len);
void *memset(void *ptr, i32 x, u64 n);
u8 *substr(const u8 *s, const u8 *sub);
u8 *strchr(const u8 *s, i32 c);
void *memorymove(void *dest, const void *src, u64 n);

#endif /* _MISC_H */
