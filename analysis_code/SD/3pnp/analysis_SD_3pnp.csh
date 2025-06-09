#!/bin/csh

root4star -b -q analysis_code/SD/3pnp/Calc_systematic_getAN_6ptE_3pnp.C
root -b -q analysis_code/SD/3pnp/draw_3pnp_smallBBCEast_sys_compare_run15.C
root -b -q analysis_code/SD/3pnp/draw_3pnp_largeBBCEast_sys_compare_run15.C
root -b -q analysis_code/SD/3pnp/draw_3pnp_ROFEast_sys_compare_run15.C
root -b -q analysis_code/SD/3pnp/Calc_3pnp_systematic_All_5ptE.C
