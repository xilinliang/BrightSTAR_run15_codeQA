#!/bin/csh

root4star -b -q analysis_code/SE/Calc_systematic_getAN_6pt_12np.C
root -b -q analysis_code/SE/draw_12np_smallBBCWest_sys_compare_run15.C
root -b -q analysis_code/SE/draw_12np_largeBBCWest_sys_compare_run15.C
root -b -q analysis_code/SE/draw_12np_ROFWest_sys_compare_run15.C
root -b -q analysis_code/SE/draw_12np_EsumWest_sys_compare_run15.C
root4star -b -q analysis_code/SE/draw_Esum_bkg.C
root -b -q analysis_code/SE/Calc_12np_systematic_All_5pt.C
