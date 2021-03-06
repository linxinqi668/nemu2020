#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	// nemu_assert(0);
	long long c = (long long)a * (long long)b;
	return (FLOAT)(c >> 16);
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	/* Dividing two 64-bit integers needs the support of another library
	 * `libgcc', other than newlib. It is a dirty work to port `libgcc'
	 * to NEMU. In fact, it is unnecessary to perform a "64/64" division
	 * here. A "64/32" division is enough.
	 *
	 * To perform a "64/32" division, you can use the x86 instruction
	 * `div' or `idiv' by inline assembly. We provide a template for you
	 * to prevent you from uncessary details.
	 *
	 *     asm volatile ("??? %2" : "=a"(???), "=d"(???) : "r"(???), "a"(???), "d"(???));
	 *
	 * If you want to use the template above, you should fill the "???"
	 * correctly. For more information, please read the i386 manual for
	 * division instructions, and search the Internet about "inline assembly".
	 * It is OK not to use the template above, but you should figure
	 * out another way to perform the division.
	 */
	int sign = 1;
	if (a < 0) 
	{
		sign = -sign;
		a = -a;
	}
	if (b < 0) 
	{
		sign = -sign;
		b = -b;
	}
	int res = a / b;
	a = a % b;
	int i;
	for (i = 0; i < 16; i++) 
	{
		a <<= 1;
		res <<= 1;
		if (a >= b) 
		{
			a -= b;
			res++;
		}
	}
	return res * sign;
}

FLOAT f2F(float a) {

	// float类型的存储方式为:
	// <sign bit> <----- Exponent 8 bit -----> <----- Mantissa 23 bit ----->
	// real number = (-1)^s * 2^(E - 127) * 1.M

	unsigned int temp = *(unsigned int *)&a; // 转成无符号数, 方便移位
	int sign_bit = temp >> 31; // 符号位
	int exp = (temp >> 23) & 0xff; // 指数
	unsigned int mantissa = (temp << 9 >> 9); // 尾数
	unsigned int frac = (0x1 << 23) + mantissa; // 小数部分
	// 现在的frac相当于是原来的浮点数 左移了23位.
	// 指数部分还需要移动 E - 127 位, 转成FLOAT只需要左移16位.
	unsigned int res = 0x0;
	if (exp - 127 < 0) // exp 不可以是unsigned int.
		res = frac >> (127 - exp) >> 7;
	else if (exp - 127 > 0)
		res = frac << (exp - 127) >> 7;
	else
		res = frac >> 7;
	
	if (sign_bit == 1) // 更新符号.
		res = ~res + 1;
	
	return res;
}

FLOAT Fabs(FLOAT a) {
	// nemu_assert(0);
	return a < 0 ? (-a) : a;
}

/* Functions below are already implemented */

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

