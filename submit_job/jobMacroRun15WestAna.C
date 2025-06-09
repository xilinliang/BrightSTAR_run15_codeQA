void jobMacroRun15WestAna(TString fileList, TString outName, TString mode)
{
    gROOT->Macro("rootlogon.C");
    DiffJetXFCalc_WestRPnew(fileList, outName,mode,"fms");
}
