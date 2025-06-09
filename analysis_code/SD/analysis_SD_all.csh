#!/bin/csh

root4star -b -q analysis_code/SD/all/Calc_systematic_getAN_6ptE.C
root -b -q analysis_code/SD/all/draw_smallBBCEast_sys_compare_run15.C
root -b -q analysis_code/SD/all/draw_largeBBCEast_sys_compare_run15.C
root -b -q analysis_code/SD/all/draw_ROFEast_sys_compare_run15.C
root -b -q analysis_code/SD/all/Calc_systematic_All_5ptE.C
root -b -q analysis_code/SD/Calc_bkg_frac_east.C

