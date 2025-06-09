void jobMacroRun15WestQa_zerobias(TString fileList, TString outName, TString process)
{
    gROOT->Macro("rootlogon.C");
    DiffJetAnaTreeQaRun15New(fileList, outName,process);
}
