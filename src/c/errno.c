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

i32 __err_value = 0;
PUBLIC i32 *__error(void) { return &__err_value; }
i32 __err_location(void) { &__err_value; }

PUBLIC void perror(const u8 *s) {
	i32 len = 0, v = 2;
	const u8 *err_msg;
	if (s == NULL) return;
	len = strlen(s);
	v = write(2, s, len);
	if (len && v == len) v = write(2, ": ", 2);
	if (v == 2) err_msg = strerror(errno);
	if (v == 2) len = strlen(err_msg);
	if (v == 2) v = write(2, err_msg, len);
	if (v == len) v = write(2, "\n", 1);
}

PUBLIC const u8 *strerror(i32 err_code) {
	switch (err_code) {
		case SUCCESS:
			return "Success";
		case EPERM:
			return "Operation not permitted";
		case ENOENT:
			return "No such file or directory";
		case ESRCH:
			return "No such process";
		case EINTR:
			return "Interrupted system call";
		case EIO:
			return "Input/output error";
		case ENXIO:
			return "No such device or address";
		case E2BIG:
			return "Argument list too long";
		case ENOEXEC:
			return "Exec format error";
		case EBADF:
			return "Bad file descriptor";
		case ECHILD:
			return "No child processes";
		case EAGAIN:
			return "Resource temporarily unavailable";
		case ENOMEM:
			return "Out of memory";
		case EACCES:
			return "Permission denied";
		case EFAULT:
			return "Bad address";
		case ENOTBLK:
			return "Block device required";
		case EBUSY:
			return "Device or resource busy";
		case EEXIST:
			return "File exists";
		case EXDEV:
			return "Invalid cross-device link";
		case ENODEV:
			return "No such device";
		case ENOTDIR:
			return "Not a directory";
		case EISDIR:
			return "Is a directory";
		case EINVAL:
			return "Invalid argument";
		case ENFILE:
			return "File table overflow";
		case EMFILE:
			return "Too many open files";
		case ENOTTY:
			return "Not a typewriter";
		case ETXTBSY:
			return "Text file busy";
		case EFBIG:
			return "File too large";
		case ENOSPC:
			return "No space left on device";
		case ESPIPE:
			return "Illegal seek";
		case EROFS:
			return "Read-only file system";
		case EMLINK:
			return "Too many links";
		case EPIPE:
			return "Broken pipe";
		case EDOM:
			return "Math argument out of domain of func";
		case ERANGE:
			return "Math result not representable";
		case EDEADLK:
			return "Resource deadlock would occur";
		case ENAMETOOLONG:
			return "File name too long";
		case ENOLCK:
			return "No record locks available";
		case ENOSYS:
			return "Invalid system call number";
		case ENOTEMPTY:
			return "Directory not empty";
		case ELOOP:
			return "Too many symbolic links encountered";
		case ENOMSG:
			return "No message of desired type";
		case EIDRM:
			return "Identifier removed";
		case ECHRNG:
			return "Channel number out of range";
		case EL2NSYNC:
			return "Level 2 not synchronized";
		case EL3HLT:
			return "Level 3 halted";
		case EL3RST:
			return "Level 3 reset";
		case ELNRNG:
			return "Link number out of range";
		case EUNATCH:
			return "Protocol driver not attached";
		case ENOCSI:
			return "No CSI structure available";
		case EL2HLT:
			return "Level 2 halted";
		case EBADE:
			return "Invalid exchange";
		case EBADR:
			return "Invalid request descriptor";
		case EXFULL:
			return "Exchange full";
		case ENOANO:
			return "No anode";
		case EBADRQC:
			return "Invalid request code";
		case EBADSLT:
			return "Invalid slot";
		case EBFONT:
			return "Bad font file format";
		case ENOSTR:
			return "Device not a stream";
		case ENODATA:
			return "No data available";
		case ETIME:
			return "Timer expired";
		case ENOSR:
			return "Out of streams resources";
		case ENONET:
			return "Machine is not on the network";
		case ENOPKG:
			return "Package not installed";
		case EREMOTE:
			return "Object is remote";
		case ENOLINK:
			return "Link has been severed";
		case EADV:
			return "Advertise error";
		case ESRMNT:
			return "Srmount error";
		case ECOMM:
			return "Communication error on send";
		case EPROTO:
			return "Protocol error";
		case EMULTIHOP:
			return "Multihop attempted";
		case EDOTDOT:
			return "RFS specific error";
		case EBADMSG:
			return "Not a data message";
		case EOVERFLOW:
			return "Value too large for defined data type";
		case ENOTUNIQ:
			return "Name not unique on network";
		case EBADFD:
			return "File descriptor in bad state";
		case EREMCHG:
			return "Remote address changed";
		case ELIBACC:
			return "Can not access a needed shared library";
		case ELIBBAD:
			return "Accessing a corrupted shared library";
		case ELIBSCN:
			return "lib section in a.out corrupted";
		case ELIBMAX:
			return "Attempting to link in too many shared "
			       "libraries";
		case ELIBEXEC:
			return "Cannot exec a shared library directly";
		case EILSEQ:
			return "Illegal byte sequence";
		case ERESTART:
			return "Interrupted system call should be restarted";
		case ESTRPIPE:
			return "Streams pipe error";
		case EUSERS:
			return "Too many users";
		case ENOTSOCK:
			return "Socket operation on non-socket";
		case EDESTADDRREQ:
			return "Destination address required";
		case EMSGSIZE:
			return "Message too long";
		case EPROTOTYPE:
			return "Protocol wrong type for socket";
		case ENOPROTOOPT:
			return "Protocol not available";
		case EPROTONOSUPPORT:
			return "Protocol not supported";
		case ESOCKTNOSUPPORT:
			return "Socket type not supported";
		case EOPNOTSUPP:
			return "Operation not supported on transport endpoint";
		case EPFNOSUPPORT:
			return "Protocol family not supported";
		case EAFNOSUPPORT:
			return "Address family not supported by protocol";
		case EADDRINUSE:
			return "Address already in use";
		case EADDRNOTAVAIL:
			return "Cannot assign requested address";
		case ENETDOWN:
			return "Network is down";
		case ENETUNREACH:
			return "Network is unreachable";
		case ENETRESET:
			return "Network dropped connection because of reset";
		case ECONNABORTED:
			return "Software caused connection abort";
		case ECONNRESET:
			return "Connection reset by peer";
		case ENOBUFS:
			return "No buffer space available";
		case EISCONN:
			return "Transport endpoint is already connected";
		case ENOTCONN:
			return "Transport endpoint is not connected";
		case ESHUTDOWN:
			return "Cannot send after transport endpoint shutdown";
		case ETOOMANYREFS:
			return "Too many references: cannot splice";
		case ETIMEDOUT:
			return "Connection timed out";
		case ECONNREFUSED:
			return "Connection refused";
		case EHOSTDOWN:
			return "Host is down";
		case EHOSTUNREACH:
			return "No route to host";
		case EALREADY:
			return "Operation already in progress";
		case EINPROGRESS:
			return "Operation now in progress";
		case ESTALE:
			return "Stale file handle";
		case EUCLEAN:
			return "Structure needs cleaning";
		case ENOTNAM:
			return "Not a XENIX named type file";
		case ENAVAIL:
			return "No XENIX semaphores available";
		case EISNAM:
			return "Is a named type file";
		case EREMOTEIO:
			return "Remote I/O error";
		case EDQUOT:
			return "Quota exceeded";
		case ENOMEDIUM:
			return "No medium found";
		case EMEDIUMTYPE:
			return "Wrong medium type";
		case ECANCELED:
			return "Operation canceled";
		case ENOKEY:
			return "Required key not available";
		case EKEYEXPIRED:
			return "Key has expired";
		case EKEYREVOKED:
			return "Key has been revoked";
		case EKEYREJECTED:
			return "Key was rejected by service";
		default:
			return "Unknown error";
	}
}
