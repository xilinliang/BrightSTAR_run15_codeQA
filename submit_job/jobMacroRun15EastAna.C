void jobMacroRun15EastAna(TString fileList, TString outName, TString mode, TString process)
{
    gROOT->Macro("rootlogon.C");
    DiffJetXFCalc_EastRPnew(fileList, outName,mode,process,"fms");
}
