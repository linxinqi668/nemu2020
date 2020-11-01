#include "trap.h"
#include "FLOAT.h"

FLOAT f(FLOAT x) { 
	/* f(x) = 1/(1+25x^2) */
	return F_div_F(int2F(1), int2F(1) + F_mul_int(F_mul_F(x, x), 25));
}

// FLOAT computeT(int n, FLOAT a, FLOAT b, FLOAT (*fun)(FLOAT)) {
// 	int k;
// 	FLOAT s,h;
// 	h = F_div_int((b - a), n); // 步长.
// 	s = F_div_int(fun(a) + fun(b), 2 );
// 	for(k = 1; k < n; k ++) {
// 		s += fun(a + F_mul_int(h, k));
// 	}
// 	s = F_mul_F(s, h);
// 	return s;
// }

int main() { 
	// FLOAT a = computeT(10, f2F(-1.0), f2F(1.0), f); // f2F没问题.
	// FLOAT ans = f2F(0.551222);
	// vnemu_assert(Fabs(ans - a) < f2F(100.0))

	FLOAT res = f(f2F(0.1));

	// nemu_assert(Fabs(a - ans) < f2F(1e-2));
	nemu_assert(Fabs(res - f2F(0.8)) < f2F(0.1));

	return 0;
}
