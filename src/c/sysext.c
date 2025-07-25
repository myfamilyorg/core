PUBLIC i64 micros(void) {
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1) return -1;
	return (i64)tv.tv_sec * 1000000 + tv.tv_usec;
}

PUBLIC void *map(u64 length) {
	void *v = mmap(NULL, length, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (v == MAP_FAILED) return NULL;
	return v;
}
PUBLIC void *fmap(i32 fd, i64 size, i64 offset) {
	void *v =
	    mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
	if (v == MAP_FAILED) return NULL;
	return v;
}

PUBLIC void *smap(u64 length) {
	void *v = mmap(NULL, length, PROT_READ | PROT_WRITE,
		       MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (v == MAP_FAILED) return NULL;
	return v;
}

