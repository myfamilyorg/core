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

PUBLIC u64 strlen(const u8 *X) {
	const u8 *Y;
	if (X == NULL) return 0;
	Y = X;
	while (*X) X++;
	return X - Y;
}

PUBLIC u8 *strcpy(u8 *dest, const u8 *src) {
	u8 *ptr = dest;
	while ((*ptr++ = *src++));
	return dest;
}

PUBLIC u8 *strchr(const u8 *s, i32 c) {
	while (*s) {
		if (*s == c) return (u8 *)s;
		s++;
	}
	return (*s == c) ? (u8 *)s : 0;
}

PUBLIC i32 strcmp(const u8 *X, const u8 *Y) {
	if (X == NULL || Y == NULL) {
		if (X == Y) return 0;
		return X == NULL ? -1 : 1;
	}
	while (*X == *Y && *X) {
		X++;
		Y++;
	}
	if ((u8)*X > (u8)*Y) return 1;
	if ((u8)*Y > (u8)*X) return -1;
	return 0;
}

PUBLIC u8 *substr(const u8 *s, const u8 *sub) {
	if (s == NULL || sub == NULL) return NULL;
	for (; *s; s++) {
		const u8 *tmps = s, *tmpsub = sub;
		while (*(u8 *)tmps == *(u8 *)tmpsub && *tmps) {
			tmps++;
			tmpsub++;
		}
		if (*tmpsub == '\0') return (u8 *)s;
	}
	return NULL;
}

PUBLIC void *memcpy(void *dest, const void *src, u64 n) {
	u8 *d = (u8 *)dest;
	const u8 *s = (u8 *)src;
	u64 i;

	if (dest == NULL || src == NULL || n == 0) {
		return dest;
	}

	for (i = 0; i < n; i++) {
		d[i] = s[i];
	}
	return dest;
}

PUBLIC void *memorymove(void *dest, const void *src, u64 n) {
	u8 *d = (u8 *)dest;
	const u8 *s = (u8 *)src;
	u64 i;

	if (dest == NULL || src == NULL || n == 0) return dest;
	if (d <= s || d >= s + n) {
		for (i = 0; i < n; i++) d[i] = s[i];
	} else {
		for (i = n; i > 0; i--) d[i - 1] = s[i - 1];
	}

	return dest;
}

PUBLIC void *memset(void *dest, i32 c, u64 n) {
	u8 *s = (u8 *)dest;
	u64 i;

	if (dest == NULL || n == 0) {
		return dest;
	}

	for (i = 0; i < n; i++) {
		s[i] = (u8)c;
	}
	return dest;
}

u128 string_to_uint128(const u8 *buf, u64 len) {
	u128 result;
	u64 i;
	u8 c;

	/* Input validation */
	if (!buf || len == 0) {
		errno = EINVAL;
		return (u128)0;
	}

	result = (u128)0;
	i = 0;

	/* Skip leading whitespace */
	while (i < len && (buf[i] == ' ' || buf[i] == '\t')) {
		i++;
	}

	if (i == len) {
		errno = EINVAL;
		return (u128)0;
	}

	/* Process digits */
	while (i < len) {
		c = buf[i];
		if (c < '0' || c > '9') {
			errno = EINVAL;
			return (u128)0;
		}

		/* Check for overflow */
		if (result > U128_MAX / 10) {
			errno = EINVAL;
			return (u128)0;
		}

		result = result * 10 + (c - '0');
		i++;
	}

	return result;
}

PUBLIC u64 u128_to_string_impl(u8 *buf, u128 v, bool hex, bool upper) {
	u8 temp[64] = {0};
	i32 i = 0, j = 0;
	u16 hex_mod = hex ? 16 : 10;
	const u8 *hex_code = upper ? "0123456789ABCDEF" : "0123456789abcdef";

	if (hex) {
		j = 2;
		buf[0] = '0';
		buf[1] = 'x';
	}
	if (v == 0) {
		buf[j++] = '0';
		buf[j] = '\0';
		return j;
	}

	while (v > 0) {
		temp[i++] = hex_code[(v % hex_mod)];
		if (hex_mod == 16)
			v /= 16;
		else
			v /= 10;
	}

	for (; i > 0; j++) {
		buf[j] = temp[--i];
	}
	buf[j] = '\0';
	return j;
}

u128 __udivti3(u128 a, u128 b) {
	u64 b_lo;
	u64 a_hi;
	u64 a_lo;
	u128 quotient;
	u128 remainder;
	i32 shift;

	/* Handle division by zero */
	if (b == 0) __builtin_trap();

	/* Early return if a < b */
	if (a < b) {
		return 0;
	}

	/* If b fits in 64 bits, optimize */
	if ((b >> 64) == 0) {
		b_lo = (u64)b;
		if (b_lo == 0) __builtin_trap();

		a_hi = (u64)(a >> 64);
		a_lo = (u64)a;

		if (a_hi == 0) {
			return (u128)(a_lo / b_lo);
		}

		/* Compute quotient for a_hi != 0 */
		quotient = (u128)a_hi / b_lo;
		quotient <<= 32;
		quotient |= (u128)(a_lo >> 32) / b_lo;
		quotient <<= 32;
		quotient |= (u128)(a_lo & 0xffffffff) / b_lo;
		return quotient;
	}

	/* General 128-bit case */
	quotient = 0;
	remainder = a;

	/* Align b with remainder's MSB */
	shift = 0;
	while ((b << shift) <= remainder && shift < 128) {
		shift++;
	}
	if (shift > 0) {
		shift--; /* Adjust to highest valid shift */
		b <<= shift;
	}

	/* Division loop */
	while (shift >= 0) {
		if (remainder >= b) {
			remainder -= b;
			quotient |= ((u128)1) << shift;
		}
		b >>= 1;
		shift--;
	}

	return quotient;
}

u128 __umodti3(u128 a, u128 b) {
	u64 b_lo;
	u64 a_hi;
	u64 a_lo;
	u128 remainder;
	i32 shift;

	/* Handle division by zero */
	if (b == 0) __builtin_trap();

	/* Early return if a < b */
	if (a < b) {
		return a;
	}

	/* If b fits in 64 bits, optimize */
	if ((b >> 64) == 0) {
		b_lo = (u64)b;
		if (b_lo == 0) __builtin_trap();

		a_hi = (u64)(a >> 64);
		a_lo = (u64)a;

		if (a_hi == 0) {
			return (u128)(a_lo % b_lo);
		}

		/* Compute remainder for a_hi != 0 */
		remainder = a_hi % b_lo;
		remainder = (remainder << 32) | (a_lo >> 32);
		remainder = remainder % b_lo;
		remainder = (remainder << 32) | (a_lo & 0xffffffff);
		remainder = remainder % b_lo;
		return remainder;
	}

	/* General 128-bit case */
	remainder = a;

	/* Align b with remainder's MSB */
	shift = 0;
	while ((b << shift) <= remainder && shift < 128) {
		shift++;
	}
	if (shift > 0) {
		shift--;
		b <<= shift;
	}

	/* Division loop */
	while (shift >= 0) {
		if (remainder >= b) {
			remainder -= b;
		}
		b >>= 1;
		shift--;
	}

	return remainder;
}

u64 i128_to_string_impl(u8 *buf, i128 v, bool hex, bool upper) {
	u64 len;
	const i128 int128_min = I128_MIN;
	const u128 int128_min_abs = (u128)0x8000000000000000UL << 64;

	i32 is_negative = v < 0;
	u128 abs_v;

	if (is_negative) {
		*buf = '-';
		buf++;
		abs_v = v == int128_min ? int128_min_abs : (u128)(-v);
	} else {
		abs_v = (u128)v;
	}

	len = u128_to_string_impl(buf, abs_v, hex, upper);
	return is_negative ? len + 1 : len;
}

PUBLIC u64 double_to_string(u8 *buf, double v, i32 max_decimals) {
	u8 temp[41];
	u64 pos = 0;
	u64 len;
	i32 i;
	i32 is_negative;
	u64 int_part;
	double frac_part;
	i32 int_start;

	/* Handle special cases: NaN, infinity */
	if (v != v) {
		temp[0] = 'n';
		temp[1] = 'a';
		temp[2] = 'n';
		len = 3;
		memcpy(buf, temp, len);
		buf[len] = '\0';
		return len;
	}
	if (v > 1.7976931348623157e308 || v < -1.7976931348623157e308) {
		if (v < 0) {
			buf[pos++] = '-';
		}
		temp[0] = 'i';
		temp[1] = 'n';
		temp[2] = 'f';
		len = 3;
		memcpy(buf + pos, temp, len);
		len += pos;
		buf[len] = '\0';
		return len;
	}

	/* Handle sign */
	is_negative = v < 0;
	if (is_negative) {
		buf[pos++] = '-';
		v = -v;
	}

	/* Handle zero */
	if (v == 0.0) {
		buf[pos++] = '0';
		buf[pos] = '\0';
		return pos;
	}

	/* Check for overflow in integer part */
	if (v >= 18446744073709551616.0) { /* 2^64 */
		if (is_negative) buf[pos++] = '-';
		temp[0] = 'i';
		temp[1] = 'n';
		temp[2] = 'f';
		len = 3;
		memcpy(buf + pos, temp, len);
		len += pos;
		buf[len] = '\0';
		return len;
	}

	/* Clamp max_decimals (0–17 for double precision) */
	if (max_decimals < 0) max_decimals = 0;
	if (max_decimals > 17) max_decimals = 17;

	/* Integer part */
	int_part = (u64)v;
	frac_part = v - (double)int_part;
	int_start = pos;

	/* Round to max_decimals and handle carry-over */
	if (max_decimals > 0) {
		double rounding = 0.5;
		for (i = 0; i < max_decimals; i++) rounding /= 10.0;
		v += rounding;
		int_part = (u64)v;
		frac_part = v - (double)int_part;
	}

	if (int_part == 0) {
		buf[pos++] = '0';
	} else {
		while (int_part > 0) {
			temp[pos++ - int_start] = '0' + (int_part % 10);
			int_part /= 10;
		}
		for (i = 0; i < (i32)(pos - int_start); i++) {
			buf[int_start + i] = temp[pos - int_start - 1 - i];
		}
	}

	/* Decimal point and fractional part */
	if (frac_part > 0 && max_decimals > 0) {
		i32 digits = 0;
		u64 frac_start;

		buf[pos++] = '.';
		frac_start = pos;
		while (digits < max_decimals) { /* Stop at max_decimals */
			i32 digit;
			frac_part *= 10;
			digit = (i32)frac_part;
			if (digit > 9) digit = 9; /* Cap digit */
			buf[pos++] = '0' + digit;
			frac_part -= digit;
			digits++;
		}
		/* Trim trailing zeros */
		while (pos > frac_start && buf[pos - 1] == '0') {
			pos--;
		}
		/* Remove decimal point if no fractional digits remain */
		if (pos == frac_start) {
			pos--;
		}
	}

	buf[pos] = '\0';
	return pos;
}
