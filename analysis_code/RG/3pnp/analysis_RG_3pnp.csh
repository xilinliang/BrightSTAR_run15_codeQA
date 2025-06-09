#!/bin/csh

root4star -b -q analysis_code/RG/3pnp/Calc_systematic_getAN_6ptRG_3pnp.C
root -b -q analysis_code/RG/3pnp/draw_3pnp_smallBBCRG_sys_compare_run15.C
root -b -q analysis_code/RG/3pnp/draw_3pnp_largeBBCRG_sys_compare_run15.C
root -b -q analysis_code/RG/3pnp/draw_3pnp_ROFRG_sys_compare_run15.C
root -b -q analysis_code/RG/3pnp/Calc_3pnp_systematic_All_6ptRG.C
