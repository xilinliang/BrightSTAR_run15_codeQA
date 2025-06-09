#!/bin/csh

root4star -b -q analysis_code/RG/all/Calc_systematic_getAN_6ptRG.C
root -b -q analysis_code/RG/all/draw_smallBBCRG_sys_compare_run15.C
root -b -q analysis_code/RG/all/draw_largeBBCRG_sys_compare_run15.C
root -b -q analysis_code/RG/all/draw_ROFRG_sys_compare_run15.C
root -b -q analysis_code/RG/all/Calc_systematic_All_6ptRG.C
