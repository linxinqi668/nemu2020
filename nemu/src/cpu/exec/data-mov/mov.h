#ifndef __MOV_H__
#define __MOV_H__

make_helper(mov_i2r_b);
make_helper(mov_i2rm_b);
make_helper(mov_r2rm_b);
make_helper(mov_rm2r_b);
make_helper(mov_a2moffs_b);
make_helper(mov_moffs2a_b);

make_helper(mov_i2r_v);
make_helper(mov_i2rm_v);
make_helper(mov_r2rm_v);
make_helper(mov_rm2r_v);
make_helper(mov_a2moffs_v);
make_helper(mov_moffs2a_v);



// myself.
make_helper(movs_l);
make_helper(movs_b);
make_helper(movzbl);
make_helper(movzwl);
make_helper(movsbl);
make_helper(movswl);

make_helper(mov_cr2r);
make_helper(mov_r2cr);
make_helper(mov_sreg2rm);


#endif
