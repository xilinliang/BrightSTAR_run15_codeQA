#!/bin/csh

root4star -b -q analysis_code/SD/12np/Calc_systematic_getAN_6ptE_12np.C
root -b -q analysis_code/SD/12np/draw_12np_smallBBCEast_sys_compare_run15.C
root -b -q analysis_code/SD/12np/draw_12np_largeBBCEast_sys_compare_run15.C
root -b -q analysis_code/SD/12np/draw_12np_ROFEast_sys_compare_run15.C
root -b -q analysis_code/SD/12np/Calc_12np_systematic_All_5ptE.C
