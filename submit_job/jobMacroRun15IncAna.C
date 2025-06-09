void jobMacroRun15IncAna(TString fileList, TString outName)
{
    gROOT->Macro("rootlogon.C");
    DiffJetXFCalc_Inc(fileList, outName,"fms");
}
