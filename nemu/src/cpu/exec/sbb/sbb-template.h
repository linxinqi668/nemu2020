#include "cpu/exec/template-start.h"

#define instr sbb

static void do_execute() {
    // dest - src - CF

    DATA_TYPE_S src;
    if (op_src->type == OP_TYPE_IMM && op_src->size == 1) {
        // extended_src
        int8_t src_ = op_src->val;
        src = src_;
    } else
        src = op_src->val;

    DATA_TYPE_S minus_res = op_dest->val - src - cpu.EFLAGS.CF;

    // write
    OPERAND_W(op_dest, minus_res);

    // set ZF
    cpu.EFLAGS.ZF = (minus_res == 0) ? 1 : 0;

    // set PF
    uint8_t low_byte = minus_res;
    uint32_t count;
    for (count = 0; low_byte; ++count)
        low_byte &= (low_byte - 1); // 不断清除右边的1
    cpu.EFLAGS.PF = (count % 2 == 0) ? 1 : 0;


    // set SF
    cpu.EFLAGS.SF = (DATA_TYPE)minus_res >> (DATA_BYTE * 8 - 1);

    // set OF in subtraction.
    if (
        !(((DATA_TYPE)minus_res >> (DATA_BYTE * 8 - 1)) ^
        ((DATA_TYPE)src >> (DATA_BYTE * 8 - 1))) &&
        (((DATA_TYPE)op_dest->val >> (DATA_BYTE * 8 - 1)) ^
        ((DATA_TYPE)src >> (DATA_BYTE * 8 - 1)))
    )
        cpu.EFLAGS.OF = 1;
    else
        cpu.EFLAGS.OF = 0;

    // set CF in subtraction.
    if ((DATA_TYPE)op_dest->val < (DATA_TYPE)src)
        cpu.EFLAGS.CF = 1;
    else
        cpu.EFLAGS.CF = 0;
}

make_instr_helper(r2rm);



#include "cpu/exec/template-end.h"