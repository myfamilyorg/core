PUBLIC u64 strlen(const u8 *X) {
	const u8 *Y;
	if (X == NULL) return 0;
	Y = X;
	while (*X) X++;
	return X - Y;
}

