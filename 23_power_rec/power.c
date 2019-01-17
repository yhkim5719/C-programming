unsigned power_helper (unsigned x, unsigned y, unsigned ans) {
	if (y <= 0) return ans;
	return power_helper (x, y - 2, ans * x);
	}

unsigned power (unsigned x, unsigned y) {
	return power_helper(x, y, 1);
	}
