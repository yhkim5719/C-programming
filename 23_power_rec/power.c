unsigned power_helper (unsigned x, unsigned y) {
	if (y == 0) return 1;
	return x * power_helper (x, y - 1);
	}

unsigned power (unsigned x, unsigned y) {
	return power_helper(x, y);
	}
