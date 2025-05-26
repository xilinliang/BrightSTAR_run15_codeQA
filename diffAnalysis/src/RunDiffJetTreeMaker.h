// Filename: RunDiffJetTreeMaker.h
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Fri Apr 10 22:08:43 2020 (-0400)
// URL: jlab.org/~latif

#include "TString.h"
#include <vector>
#include <TObject.h>
#include <string>

void RunDiffJetTreeMaker(TString inFile = "./inFiles_fms.list", TString outFile = "jets.root", Int_t fillNumber=18857, TString det = "fms",  Bool_t isMC = kFALSE);
