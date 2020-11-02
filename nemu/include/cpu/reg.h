#ifndef __REG_H__
#define __REG_H__

#include "common.h"

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

/* TODO: Re-organize the `CPU_state' structure to match the register
 * encoding scheme in i386 instruction format. For example, if we
 * access cpu.gpr[3]._16, we will get the `bx' register; if we access
 * cpu.gpr[1]._8[1], we will get the 'ch' register. Hint: Use `union'.
 * For more details about the register encoding scheme, see i386 manual.
 */

typedef struct {

	union {
		union {
			uint32_t _32;
			uint16_t _16;
			uint8_t _8[2];
		} gpr[8];

		struct {
			uint32_t eax;
			uint32_t ecx;
			uint32_t edx;
			uint32_t ebx;
			uint32_t esp;
			uint32_t ebp;
			uint32_t esi;
			uint32_t edi;
		};
	};

	// Eflags used in nemu.
	union {
		// bit filed
		struct {
			uint8_t CF:1; // 1 bit
			uint8_t One_1:1;
			uint8_t PF:1;
			uint8_t Zero_1:1;
			uint8_t AF_unused:1;
			uint8_t Zero_2:1;
			uint8_t ZF:1;
			uint8_t SF:1;
			uint8_t TF_unused:1;
			uint8_t IF:1;
			uint8_t DF:1;
			uint8_t OF:1;
			uint8_t OL_unused:1;
			uint8_t IP_unused:1;
			uint8_t NT_unused:1;
			uint8_t Zero_3:1;
			uint8_t RF_unused:1;
			uint8_t VM_unused:1;
			uint16_t unused:14; // 没用的高位.
		};

		// init value of Eflags.
		uint32_t init_val;
	} EFLAGS;
	


	/* Do NOT change the order of the GPRs' definitions. */

	swaddr_t eip;

} CPU_state;

extern CPU_state cpu;

static inline int check_reg_index(int index) {
	assert(index >= 0 && index < 8);
	return index;
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index) & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
