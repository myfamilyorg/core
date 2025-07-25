PUBLIC i64 micros(void) {
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1) return -1;
	return (i64)tv.tv_sec * 1000000 + tv.tv_usec;
}

