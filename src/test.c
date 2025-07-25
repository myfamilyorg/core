Test(core1) {
	ASSERT_EQ(1, 1, "1=1");
	void *tmp = alloc(1);
	ASSERT(tmp, "tmp");
	release(tmp);
	ASSERT_BYTES(0);
}
