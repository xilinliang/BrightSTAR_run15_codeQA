

#ifdef __CINT__


//Run the NanoDst from MuDst files
#pragma link C++ function RunDiffJetTreeMaker;                 // Nano Tree Maker for fms stream
#pragma link C++ function RunDiffJetTreeMaker_FMS;                 // Nano Tree Maker for fms stream
#pragma link C++ function RunDiffJetTreeMaker_zerobias;                 // Nano Tree Maker for zerobias data
#pragma link C++ class TStRunList;				// Get Run Number from file name
#pragma link C++ class TStFmsHotChDB;				// Get FMS Hot/Bad Channel list

//Analysis code for studying data 
#pragma link C++ function DiffJetAnaTreeQaRun15New;                 // QA for the NanoDst (fms stream) , study the cuts for both cases
#pragma link C++ function DiffJetXFCalc_EastRPnew;                 // Analysis for the Single Diffractive Process and Rapidity gap process (fms stream) 
#pragma link C++ function DiffJetXFCalc_WestRPnew;                 // Analysis for the Semi-exclusive Process (fms stream) 
#pragma link C++ function DiffJetXFCalc_Inc;                 // Analysis for the inclusive process  (fms stream) cross section fraction study only!
#pragma link C++ function DiffJetXFANCalc_6pt_East;                 // Calculate the AN for the Single Diffractive Process (fms stream) 
#pragma link C++ function DiffJetXFANCalc_6pt_RG;                 // Calculate the AN for the Rapidity Gap events (fms stream) 
#pragma link C++ function DiffJetXFANCalc_6pt_SE;                 // Calculate the AN for the Semi-exclusive events (fms stream) 
#pragma link C++ function DiffJetXFANCalc_6pt_East_getChi2AndConst;                 // Calculate the Chi2 and constant term for fitting AN for the Single Diffractive Process and rapidity gap events (fms stream) 


