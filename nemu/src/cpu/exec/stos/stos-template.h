#include "cpu/exec/template-start.h"

make_helper(concat(stos_, SUFFIX)) {
    swaddr_t addr_dest = reg_l(R_EDI);

    MEM_W(addr_dest, REG(R_EAX));

    if (cpu.EFLAGS.DF == 0)
        reg_l(R_EDI) += DATA_BYTE;
    else
        reg_l(R_EDI) -= DATA_BYTE;

    return 1;
}


#include "cpu/exec/template-end.h"