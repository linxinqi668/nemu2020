#include "cpu/exec/template-start.h"

#define instr idiv

static void do_execute() {
	int64_t a;
	int32_t b = (DATA_TYPE_S)op_src->val;
#if DATA_BYTE == 1
	a = (int16_t)reg_w(R_EAX);
#else
	a = ((int64_t)REG(R_EDX) << (DATA_BYTE * 8)) | (int64_t)REG(R_EAX);
#endif
	REG(R_EAX) = a / b;
	REG(R_EDX) = a % b;

	long long int res = a / b;
	if (cpu.eip == 0x10016a) {
		printf("两个数字分别是: %x, %x\n", (int32_t)a, (int32_t)b);
		printf("结果是: %lld\n\n", (long long)res);
	}

	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
