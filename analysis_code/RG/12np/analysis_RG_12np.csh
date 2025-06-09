#!/bin/csh

root4star -b -q analysis_code/RG/12np/Calc_systematic_getAN_6ptRG_12np.C
root -b -q analysis_code/RG/12np/draw_12np_smallBBCRG_sys_compare_run15.C
root -b -q analysis_code/RG/12np/draw_12np_largeBBCRG_sys_compare_run15.C
root -b -q analysis_code/RG/12np/draw_12np_ROFRG_sys_compare_run15.C
root -b -q analysis_code/RG/12np/Calc_12np_systematic_All_6ptRG.C
