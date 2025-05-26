// Filename: DiffJetAnaTreeQaRun15New.cxx
// Description: 

#include "RootInclude.h"
#include "StRootInclude.h"
#include "BrJetMaker/TStJetCandidate.h"
#include "BrJetMaker/TStJetEvent.h"
#include "BrJetMaker/TStJetSkimEvent.h"
#include "BrContainers/TStRpsTrackData.h"
#include "BrContainers/TStEventData.h"
#include <iostream>

using namespace std;

//Use wildcat in the file name to combine many files.
void DiffJetAnaTreeQaRun15New(TString inFileName, TString outName, TString process , TString det)
{
    TChain *ch = new TChain("T");
    ch->Add(inFileName);
    
    TStJetEvent *jetEvent = 0;
    TStJetSkimEvent *skimEvent;
    TStJetCandidate *jet;
    TStJetTower *tower;
    TStJetParticle *particle;
    TStRpsTrackData *rpsTrack =0;    
    TStEventData *event;

    TClonesArray *rpsArr = new TClonesArray("TStRpsTrackData");

    ch->SetBranchAddress("jetEvents", &jetEvent);
    ch->SetBranchAddress("rpTrack",&rpsArr);

    TString triggerNames_fms[9] = {"FMS-JP0", "FMS-JP1", "FMS-JP2", "FMS-sm-bs1", "FMS-sm-bs2", "FMS-sm-bs3", "FMS-lg-bs1", "FMS-lg-bs2", "FMS-lg-bs3"};
    TString triggerNames_eemc[9] = {"EHT0","JP1","JP2","EHT0*EJP1*L2Egamma","JP2*J2JetHigh","BHT1*VPDMB30","BHT0*BBCMB","BHT1*BBCMB","BHT2*BBCMB"};
    
    TFile *outFile = new TFile(outName, "recreate");
    TH1D *h1nJets_all = new TH1D("h1nJets_all", "Number of Jets from All [TPC/BEMC + EEMC + FMS]", 10, 0, 10);
    TH1D *h1nJets  = new TH1D("h1nJets ", "Number of Jets [FMS or EEMC]", 10, 0, 10);
    TH1I *h1trigId = new TH1I("h1trigId","Trigger ID [480XXX]",100,790,889);
    TH1I *h1_NPosVertex  = new TH1I("h1_NPosVertex", "Number of good vertex (ranking > 0)", 10, 0, 10);
    TH1D *h1spinB = new TH1D("h1spinB", "Blue beam spin; Blue beam spin", 5, -2, 2);
    TH1D *h1spinY = new TH1D("h1spinY", "Yellow beam spin; Yellow beam spin", 5, -2, 2);
    TH1D *h1UnixTime = new TH1D("h1UnixTime", "Event Unix Time; Event Unix Time", 1000000, 1426e6, 1427e6);

    TH1D *h1_nRPEvent_run = new TH1D("h1_nRPEvent_run", "number of events with RP responses per run", 675, 0 ,675);

    TH1D *h1_ZDCE = new TH1D("h1_ZDCE","ZDC east ; ZDC east",200,0.,200.);
    TH1D *h1_smallBBCsumEast = new TH1D("h1_smallBBCsumEast","small BBC ADC sum for east side BBC",250,0,1000);
    TH1D *h1_largeBBCsumEast = new TH1D("h1_largeBBCsumEast","large BBC ADC sum for east side BBC",250,0,1000);
    TH1D *h1_smallBBCsumWest = new TH1D("h1_smallBBCsumWest","small BBC ADC sum for west side BBC",250,0,1000);
    TH1D *h1_largeBBCsumWest = new TH1D("h1_largeBBCsumWest","large BBC ADC sum for west side BBC",250,0,1000);
    TH1D *h1_smallBBCsumEast_RPcut = new TH1D("h1_smallBBCsumEast_RPcut","small BBC ADC sum for east side BBC (after RP cuts)",150,0,150);
    TH1D *h1_smallBBCsumWest_RPcut = new TH1D("h1_smallBBCsumWest_RPcut","small BBC ADC sum for west side BBC (after RP cuts)",150,0,150);
    TH1D *h1_smallBBCsumWest_eRPcut = new TH1D("h1_smallBBCsumWest_eRPcut","small BBC ADC sum for west side BBC (after East RP cuts)",150,0,150);
    TH1D *h1_largeBBCsumEast_RPcut = new TH1D("h1_largeBBCsumEast_RPcut","large BBC ADC sum for east side BBC (after RP cuts)",150,0,150);
    TH1D *h1_largeBBCsumWest_RPcut = new TH1D("h1_largeBBCsumWest_RPcut","large BBC ADC sum for west side BBC (after RP cuts)",150,0,150);
    TH1D *h1_largeBBCsumWest_eRPcut = new TH1D("h1_largeBBCsumWest_eRPcut","large BBC ADC sum for west side BBC (after East RP cuts)",150,0,150);

    TH1D *h1TrigType = new TH1D("h1TrigType", "Trigger Type; Trigger Type", 9, 0, 9);


    TH1D *h1TowerEta = new TH1D("h1TowerEta", "Tower Eta", 100, 1.0, 4.5);
    TH1D *h1TowerPhi = new TH1D("h1TowerPhi", "Tower Phi", 100, -3.2, 3.2);
    TH1D *h1TowerE = new TH1D("h1TowerE", "Tower E", 100, 0, 100);

    TH1D *h1Eta = new TH1D ("h1Eta", "EM Jet #eta; EN Jet #eta", 100, 0.5, 5.0);
    TH1D *h1Phi = new TH1D ("h1Phi", "EM Jet #phi; EM Jet #phi [rad]", 100, -3.3, 3.3);
    TH1D *h1E = new TH1D ("h1E", "EM Jet E; EM Jet E [GeV]", 100, 0.0, 100.0);
    TH1D *h1E_corr = new TH1D ("h1E_corr", "EM Jet E (corrected); EM Jet E [GeV]", 200, 0.0, 100.0);
    TH1D *h1E_corr_12np = new TH1D ("h1E_corr_12np", "EM Jet E (corrected , n photon <= 2); EM Jet E [GeV]", 100, 0.0, 100.0);
    TH1D *h1E_corr_NowRP = new TH1D ("h1E_corr_NowRP", "EM Jet E (corrected); EM Jet E [GeV]", 100, 0.0, 100.0);
    TH1D *h1E_JP1 = new TH1D ("h1E_JP1", "EM Jet E (JP1); Jet E [GeV]", 100, 0.0, 100.0);
    TH1D *h1E_JP2 = new TH1D ("h1E_JP2", "EM Jet E (JP2); Jet E [GeV]", 100, 0.0, 100.0);
    TH1D *h1JetE_s = new TH1D ("h1JetE_s", "EM Jet E [small cells]; Jet E [GeV]", 100, 0.0, 85.0);
    TH1D *h1JetE_l = new TH1D ("h1JetE_l", "EM Jet E [large cells]; Jet E [GeV]", 100, 0.0, 70.0);    
    TH1D *h1Pt = new TH1D ("h1Pt", "EM Jet Pt; Jet Pt [GeV/c]", 100, 0.0, 50.0);
    TH1D *h1UE = new TH1D ("h1UE", "EM Jet energy after UE correction; EM Jet E [GeV]", 100, 0.0, 100.0);
    TH1D *h1dUE = new TH1D ("h1dUE", "UE EM Jet #Delta E; |#Delta(E)| [GeV/c]", 150, 0.0, 50.0);
    TH1D *h1dUE_corr = new TH1D ("h1dUE_corr", "EM Jet dUE; EM Jet dUE [GeV]", 100, 0.0, 20.0);
    TH1D *h1UE_corr = new TH1D ("h1UE_corr", "EM Jet E with corrected from UE; EM Jet E [GeV]", 100, 0.0, 70.0);
    TH1D *h1Pt_JP1 = new TH1D ("h1Pt_JP1", "EM Jet Pt (JP1); Jet Pt [GeV/c]", 100, 0.0, 10.0);
    TH1D *h1Pt_JP2 = new TH1D ("h1Pt_JP2", "EM Jet Pt (JP2); Jet Pt [GeV/c]", 100, 0.0, 10.0);
    TH1D *h1nPhotons = new TH1D("h1nPhotons", "number of photons in EM jets; Number of Photons", 20, 0, 20);
    TH1D *h1vtxZ = new TH1D("h1vtxZ", "Jet vetrex z; Jet vertex z [cm]", 100, -200, 200);
    TH1D *h1_nRpTracks = new TH1D("h1_nRpTracks", "Number of RP tracks", 20, 0, 20);     
    TH1D *h1_nRpTracksEastNocut = new TH1D("h1_nRpTracksEastNocut", "Number of east RP tracks ", 20, 0, 20);     
    TH1D *h1_nRpTracksWestNocut = new TH1D("h1_nRpTracksWestNocut", "Number of west RP tracks ", 20, 0, 20);     
    TH1D *h1_wRpPt = new TH1D("h1_trkPtWest", "West RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 10);
    TH1D *h1_eRpPt = new TH1D("h1_trkPtEast", "East RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 10);    
    TH1D *h1_wRpP = new TH1D("h1_trkPWest", "West RP trk P; RP track P [GeV/c]", 120, 0., 120.);
    TH1D *h1_wRpP_passcut = new TH1D("h1_wRpP_passcut", "West RP trk P (passing RP cuts); RP track P [GeV/c]", 160, 40., 120.);
    TH1D *h1_wRpP_nojets = new TH1D("h1_trkPWest_nojets", "West RP trk P; RP track P [GeV/c]", 120, 0., 120.);
    TH1D *h1_eRpP = new TH1D("h1_trkPEast", "East RP trk P; RP track P [GeV/c]", 120, 0., 120.);
    TH1D *h1_eRpP_passcut = new TH1D("h1_eRpP_passcut", "East RP trk P (passing RP cuts); RP track P [GeV/c]", 160, 40., 120.);
    TH1D *h1_eRpEta = new TH1D("h1_eRpEta","East Roman Pot #eta ; #eta",80,-9,-4);
    TH1D *h1_eRpPhi = new TH1D ("h1_eRpPhi", "East Roman Pot #phi;  #phi [rad]", 50, -3.14, 3.14);
    TH1D *h1_wRpEta = new TH1D("h1_wRpEta","West Roman Pot #eta ; #eta",80,4,9);
    TH1D *h1_wRpPhi = new TH1D ("h1_wRpPhi", "West Roman Pot #phi;  #phi [rad]", 50, -3.14, 3.14);
    TH1D *h1_wRPXi = new TH1D("h1_wRPXi","west RP #xi; #xi",100,0,1.0);
    TH1D *h1_RpThetaX = new TH1D("h1_RpThetaX","Roman Pot #theta_{X};#theta_{X} [mrad]",60,-15,15);
    TH1D *h1_RpThetaY = new TH1D("h1_RpThetaY","Roman Pot #theta_{Y};#theta_{Y} [mrad]",60,-15,15);
    TH2D *h2_RpThetaXY = new TH2D ("h2_RpThetaXY","Roman Pot trk #theta_{y} vs #theta_{x};#theta_{x} [mrad];#theta_{y} [mrad]",60,-15,15,60,-15,15);
    TH2D *h2_RpPyP = new TH2D("h2_RpPyP","Roman Pot track P_{y} vs P;P [GeV/c];P_{y} [GeV/c]",100,20.0,120.0,100,-2.0,2.0);
    TH2D *h2_RpPyPx = new TH2D("h2_RpPyPx","Roman Pot track P_{y} vs P_{x};p_{x} [GeV/c];P_{y} [GeV/c]",100,-2.0,2.0,100,-2.0,2.0);
    TH2D *h2_wRpPyPx_Xi0005 = new TH2D("h2_wRpPyPx_Xi0005","West Roman Pot track P_{y} vs P_{x} (0 < #xi < 0.05);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi0520 = new TH2D("h2_wRpPyPx_Xi0520","West Roman Pot track P_{y} vs P_{x} (0.05 < #xi < 0.20);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-2.0,2.0);
    TH2D *h2_wRpPyPx_Xi2050 = new TH2D("h2_wRpPyPx_Xi2050","West Roman Pot track P_{y} vs P_{x} (#xi > 0.2);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-2.0,2.0);
    TH2D *h2_wRpPyPx_Xi0510 = new TH2D("h2_wRpPyPx_Xi0510","West Roman Pot track P_{y} vs P_{x} (0.05 < #xi < 0.10);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi1015 = new TH2D("h2_wRpPyPx_Xi1015","West Roman Pot track P_{y} vs P_{x} (0.10 < #xi < 0.15);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi1520 = new TH2D("h2_wRpPyPx_Xi1520","West Roman Pot track P_{y} vs P_{x} (0.15 < #xi < 0.20);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi2025 = new TH2D("h2_wRpPyPx_Xi2025","West Roman Pot track P_{y} vs P_{x} (0.20 < #xi < 0.25);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi2530 = new TH2D("h2_wRpPyPx_Xi2530","West Roman Pot track P_{y} vs P_{x} (0.25 < #xi < 0.30);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi3035 = new TH2D("h2_wRpPyPx_Xi3035","West Roman Pot track P_{y} vs P_{x} (0.30 < #xi < 0.35);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi3540 = new TH2D("h2_wRpPyPx_Xi3540","West Roman Pot track P_{y} vs P_{x} (0.35 < #xi < 0.40);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi4045 = new TH2D("h2_wRpPyPx_Xi4045","West Roman Pot track P_{y} vs P_{x} (0.40 < #xi < 0.45);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi4550 = new TH2D("h2_wRpPyPx_Xi4550","West Roman Pot track P_{y} vs P_{x} (0.45 < #xi < 0.50);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi2550 = new TH2D("h2_wRpPyPx_Xi2550","West Roman Pot track P_{y} vs P_{x} (0.25 < #xi < 0.50);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpPyPx_Xi3050 = new TH2D("h2_wRpPyPx_Xi3050","West Roman Pot track P_{y} vs P_{x} (0.30 < #xi < 0.50);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_wRpThetaXY_Xi0005 = new TH2D ("h2_wRpThetaXY_Xi0005","West Roman Pot trk #theta_{y} vs #theta_{x} (0 < #xi < 0.05);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi0510 = new TH2D ("h2_wRpThetaXY_Xi0510","West Roman Pot trk #theta_{y} vs #theta_{x} (0.05 < #xi < 0.10);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi0520 = new TH2D ("h2_wRpThetaXY_Xi0520","West Roman Pot trk #theta_{y} vs #theta_{x} (0.05 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi2050 = new TH2D ("h2_wRpThetaXY_Xi2050","West Roman Pot trk #theta_{y} vs #theta_{x} (#xi > 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi1015 = new TH2D ("h2_wRpThetaXY_Xi1015","West Roman Pot trk #theta_{y} vs #theta_{x} (0.10 < #xi < 0.15);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi1520 = new TH2D ("h2_wRpThetaXY_Xi1520","West Roman Pot trk #theta_{y} vs #theta_{x} (0.15 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi2025 = new TH2D ("h2_wRpThetaXY_Xi2025","West Roman Pot trk #theta_{y} vs #theta_{x} (0.20 < #xi < 0.25);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi2530 = new TH2D ("h2_wRpThetaXY_Xi2530","West Roman Pot trk #theta_{y} vs #theta_{x} (0.25 < #xi < 0.30);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi3035 = new TH2D ("h2_wRpThetaXY_Xi3035","West Roman Pot trk #theta_{y} vs #theta_{x} (0.30 < #xi < 0.35);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi3540 = new TH2D ("h2_wRpThetaXY_Xi3540","West Roman Pot trk #theta_{y} vs #theta_{x} (0.35 < #xi < 0.40);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi4045 = new TH2D ("h2_wRpThetaXY_Xi4045","West Roman Pot trk #theta_{y} vs #theta_{x} (0.40 < #xi < 0.45);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi4550 = new TH2D ("h2_wRpThetaXY_Xi4550","West Roman Pot trk #theta_{y} vs #theta_{x} (0.45 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi2550 = new TH2D ("h2_wRpThetaXY_Xi2550","West Roman Pot trk #theta_{y} vs #theta_{x} (0.25 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_Xi3050 = new TH2D ("h2_wRpThetaXY_Xi3050","West Roman Pot trk #theta_{y} vs #theta_{x} (0.30 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH1D *h1_wRpThetaY_Xi0005 = new TH1D("h1_wRpThetaY_Xi0005","West Roman Pot #theta_{Y} (0 < #xi < 0.05);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi0520 = new TH1D("h1_wRpThetaY_Xi0520","West Roman Pot #theta_{Y} (0.05 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi2050 = new TH1D("h1_wRpThetaY_Xi2050","West Roman Pot #theta_{Y} (0.20 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi0510 = new TH1D("h1_wRpThetaY_Xi0510","West Roman Pot #theta_{Y} (0.05 < #xi < 0.10);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi1015 = new TH1D("h1_wRpThetaY_Xi1015","West Roman Pot #theta_{Y} (0.10 < #xi < 0.15);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi1520 = new TH1D("h1_wRpThetaY_Xi1520","West Roman Pot #theta_{Y} (0.15 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi2025 = new TH1D("h1_wRpThetaY_Xi2025","West Roman Pot #theta_{Y} (0.20 < #xi < 0.25);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi2530 = new TH1D("h1_wRpThetaY_Xi2530","West Roman Pot #theta_{Y} (0.25 < #xi < 0.30);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi3035 = new TH1D("h1_wRpThetaY_Xi3035","West Roman Pot #theta_{Y} (0.30 < #xi < 0.35);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi3540 = new TH1D("h1_wRpThetaY_Xi3540","West Roman Pot #theta_{Y} (0.35 < #xi < 0.40);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi4045 = new TH1D("h1_wRpThetaY_Xi4045","West Roman Pot #theta_{Y} (0.40 < #xi < 0.45);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi4550 = new TH1D("h1_wRpThetaY_Xi4550","West Roman Pot #theta_{Y} (0.45 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi2550 = new TH1D("h1_wRpThetaY_Xi2550","West Roman Pot #theta_{Y} (0.25 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_Xi3050 = new TH1D("h1_wRpThetaY_Xi3050","West Roman Pot #theta_{Y} (0.30 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH2D *h2_wRpThetaXY_rough_Xi0005 = new TH2D ("h2_wRpThetaXY_rough_Xi0005","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0 < #xi < 0.05);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi0510 = new TH2D ("h2_wRpThetaXY_rough_Xi0510","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.05 < #xi < 0.10);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi0520 = new TH2D ("h2_wRpThetaXY_rough_Xi0520","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.05 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi2050 = new TH2D ("h2_wRpThetaXY_rough_Xi2050","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (#xi > 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi1015 = new TH2D ("h2_wRpThetaXY_rough_Xi1015","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.10 < #xi < 0.15);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi1520 = new TH2D ("h2_wRpThetaXY_rough_Xi1520","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.15 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi2025 = new TH2D ("h2_wRpThetaXY_rough_Xi2025","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.20 < #xi < 0.25);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi2530 = new TH2D ("h2_wRpThetaXY_rough_Xi2530","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.25 < #xi < 0.30);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi3035 = new TH2D ("h2_wRpThetaXY_rough_Xi3035","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.30 < #xi < 0.35);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi3540 = new TH2D ("h2_wRpThetaXY_rough_Xi3540","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.35 < #xi < 0.40);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi4045 = new TH2D ("h2_wRpThetaXY_rough_Xi4045","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.40 < #xi < 0.45);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi4550 = new TH2D ("h2_wRpThetaXY_rough_Xi4550","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.45 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi2550 = new TH2D ("h2_wRpThetaXY_rough_Xi2550","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.25 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_wRpThetaXY_rough_Xi3050 = new TH2D ("h2_wRpThetaXY_rough_Xi3050","West Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.30 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH1D *h1_wRpThetaY_rough_Xi0005 = new TH1D("h1_wRpThetaY_rough_Xi0005","West Roman Pot #theta_{Y} with rough cuts (0 < #xi < 0.05);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi0520 = new TH1D("h1_wRpThetaY_rough_Xi0520","West Roman Pot #theta_{Y} with rough cuts (0.05 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi2050 = new TH1D("h1_wRpThetaY_rough_Xi2050","West Roman Pot #theta_{Y} with rough cuts (0.20 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi0510 = new TH1D("h1_wRpThetaY_rough_Xi0510","West Roman Pot #theta_{Y} with rough cuts (0.05 < #xi < 0.10);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi1015 = new TH1D("h1_wRpThetaY_rough_Xi1015","West Roman Pot #theta_{Y} with rough cuts (0.10 < #xi < 0.15);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi1520 = new TH1D("h1_wRpThetaY_rough_Xi1520","West Roman Pot #theta_{Y} with rough cuts (0.15 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi2025 = new TH1D("h1_wRpThetaY_rough_Xi2025","West Roman Pot #theta_{Y} with rough cuts (0.20 < #xi < 0.25);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi2530 = new TH1D("h1_wRpThetaY_rough_Xi2530","West Roman Pot #theta_{Y} with rough cuts (0.25 < #xi < 0.30);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi3035 = new TH1D("h1_wRpThetaY_rough_Xi3035","West Roman Pot #theta_{Y} with rough cuts (0.30 < #xi < 0.35);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi3540 = new TH1D("h1_wRpThetaY_rough_Xi3540","West Roman Pot #theta_{Y} with rough cuts (0.35 < #xi < 0.40);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi4045 = new TH1D("h1_wRpThetaY_rough_Xi4045","West Roman Pot #theta_{Y} with rough cuts (0.40 < #xi < 0.45);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi4550 = new TH1D("h1_wRpThetaY_rough_Xi4550","West Roman Pot #theta_{Y} with rough cuts (0.45 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi2550 = new TH1D("h1_wRpThetaY_rough_Xi2550","West Roman Pot #theta_{Y} with rough cuts (0.25 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_wRpThetaY_rough_Xi3050 = new TH1D("h1_wRpThetaY_rough_Xi3050","West Roman Pot #theta_{Y} with rough cuts (0.30 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);

    TH2D *h2_RpPyPx_sig = new TH2D("h2_RpPyPx_sig","Roman Pot track P_{y} vs P_{x};p_{x} [GeV/c];P_{y} [GeV/c]",100,-2.0,2.0,100,-2.0,2.0);
    TH2D *h2_RpPyPx_bkg = new TH2D("h2_RpPyPx_bkg","Roman Pot track P_{y} vs P_{x};p_{x} [GeV/c];P_{y} [GeV/c]",100,-2.0,2.0,100,-2.0,2.0);
    TH2D *h2_RpPyPx_elastic = new TH2D("h2_RpPyPx_elastic","Roman Pot track P_{y} vs P_{x} (elastic);p_{x} [GeV/c];P_{y} [GeV/c]",100,-2.0,2.0,100,-2.0,2.0);
    TH2D *h2_RpPyPx_nonelastic = new TH2D("h2_RpPyPx_nonelastic","Roman Pot track P_{y} vs P_{x} (non-elastic);p_{x} [GeV/c];P_{y} [GeV/c]",100,-2.0,2.0,100,-2.0,2.0);
    TH1D *h1_RpNPlanes = new TH1D("h1_RpNPlanes","Number of RP planes;N Planes",9,0,9);
    TH1D *h1_sumEwest = new TH1D("h1_sumEwest","sum of west side RP track energy and EM Jet energy;sum E [GeV]",140,180,320);
    TH2D *h2_wRpPxXi = new TH2D("h2_wRPPxXi","west RP p_{X} vs #xi; #xi ; p_{X} [GeV/c]", 25,0.,0.5,100,-1.0,1.0); 
    TH2D *h2_wRpPyXi = new TH2D("h2_wRPPyXi","west RP p_{Y} vs #xi; #xi ; p_{Y} [GeV/c]", 25,0.,0.5,100,-1.0,1.0); 
    TH2D *h2_wRpThetaXXi = new TH2D("h2_wRPThetaXXi","west RP #theta_{X} vs #xi; #xi ; #theta_{X} [mrad]", 25,0.,0.5,100,-1.0,1.0); 
    TH2D *h2_wRpThetaYXi = new TH2D("h2_wRPThetaYXi","west RP #theta_{Y} vs #xi; #xi ; #theta_{Y} [mrad]", 25,0.,0.5,100,-1.0,1.0); 
    TH1D *h1_eRPXi = new TH1D("h1_eRPXi","east RP #xi; #xi",100,0,1.0);
    TH2D *h2_eRpPyPx_Xi0005 = new TH2D("h2_eRpPyPx_Xi0005","East Roman Pot track P_{y} vs P_{x} (0 < #xi < 0.05);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi0520 = new TH2D("h2_eRpPyPx_Xi0520","East Roman Pot track P_{y} vs P_{x} (0.05 < #xi < 0.20);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-2.0,2.0);
    TH2D *h2_eRpPyPx_Xi2050 = new TH2D("h2_eRpPyPx_Xi2050","East Roman Pot track P_{y} vs P_{x} (#xi > 0.2);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-2.0,2.0);
    TH2D *h2_eRpPyPx_Xi0510 = new TH2D("h2_eRpPyPx_Xi0510","East Roman Pot track P_{y} vs P_{x} (0.05 < #xi < 0.10);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi1015 = new TH2D("h2_eRpPyPx_Xi1015","East Roman Pot track P_{y} vs P_{x} (0.10 < #xi < 0.15);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi1520 = new TH2D("h2_eRpPyPx_Xi1520","East Roman Pot track P_{y} vs P_{x} (0.15 < #xi < 0.20);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi2025 = new TH2D("h2_eRpPyPx_Xi2025","East Roman Pot track P_{y} vs P_{x} (0.20 < #xi < 0.25);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi2530 = new TH2D("h2_eRpPyPx_Xi2530","East Roman Pot track P_{y} vs P_{x} (0.25 < #xi < 0.30);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi3035 = new TH2D("h2_eRpPyPx_Xi3035","East Roman Pot track P_{y} vs P_{x} (0.30 < #xi < 0.35);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi3540 = new TH2D("h2_eRpPyPx_Xi3540","East Roman Pot track P_{y} vs P_{x} (0.35 < #xi < 0.40);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi4045 = new TH2D("h2_eRpPyPx_Xi4045","East Roman Pot track P_{y} vs P_{x} (0.40 < #xi < 0.45);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi2550 = new TH2D("h2_eRpPyPx_Xi2550","East Roman Pot track P_{y} vs P_{x} (0.25 < #xi < 0.50);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpPyPx_Xi3050 = new TH2D("h2_eRpPyPx_Xi3050","East Roman Pot track P_{y} vs P_{x} (0.30 < #xi < 0.50);p_{x} [GeV/c];P_{y} [GeV/c]",100,-1.0,1.0,100,-1.0,1.0);
    TH2D *h2_eRpThetaXXi = new TH2D("h2_eRPThetaXXi","east RP #theta_{X} vs #xi; #xi ; #theta_{X} [mrad]", 25,0.,0.5,100,-1.0,1.0); 
    TH2D *h2_eRpThetaYXi = new TH2D("h2_eRPThetaYXi","east RP #theta_{Y} vs #xi; #xi ; #theta_{Y} [mrad]", 25,0.,0.5,100,-1.0,1.0); 
    TH1D *h1_eRpThetaY_Xi0005 = new TH1D("h1_eRpThetaY_Xi0005","East Roman Pot #theta_{Y} (0 < #xi < 0.05);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi0520 = new TH1D("h1_eRpThetaY_Xi0520","East Roman Pot #theta_{Y} (0.05 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi2050 = new TH1D("h1_eRpThetaY_Xi2050","East Roman Pot #theta_{Y} (0.20 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi0510 = new TH1D("h1_eRpThetaY_Xi0510","East Roman Pot #theta_{Y} (0.05 < #xi < 0.10);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi1015 = new TH1D("h1_eRpThetaY_Xi1015","East Roman Pot #theta_{Y} (0.10 < #xi < 0.15);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi1520 = new TH1D("h1_eRpThetaY_Xi1520","East Roman Pot #theta_{Y} (0.15 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi2025 = new TH1D("h1_eRpThetaY_Xi2025","East Roman Pot #theta_{Y} (0.20 < #xi < 0.25);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi2530 = new TH1D("h1_eRpThetaY_Xi2530","East Roman Pot #theta_{Y} (0.25 < #xi < 0.30);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi3035 = new TH1D("h1_eRpThetaY_Xi3035","East Roman Pot #theta_{Y} (0.30 < #xi < 0.35);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi3540 = new TH1D("h1_eRpThetaY_Xi3540","East Roman Pot #theta_{Y} (0.35 < #xi < 0.40);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi4045 = new TH1D("h1_eRpThetaY_Xi4045","East Roman Pot #theta_{Y} (0.40 < #xi < 0.45);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi2550 = new TH1D("h1_eRpThetaY_Xi2550","East Roman Pot #theta_{Y} (0.25 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_Xi3050 = new TH1D("h1_eRpThetaY_Xi3050","East Roman Pot #theta_{Y} (0.30 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH2D *h2_eRpThetaXY_Xi0005 = new TH2D ("h2_eRpThetaXY_Xi0005","East Roman Pot trk #theta_{y} vs #theta_{x} (0 < #xi < 0.05);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi0520 = new TH2D ("h2_eRpThetaXY_Xi0520","East Roman Pot trk #theta_{y} vs #theta_{x} (0.05 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi2050 = new TH2D ("h2_eRpThetaXY_Xi2050","East Roman Pot trk #theta_{y} vs #theta_{x} (#xi > 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi0510 = new TH2D ("h2_eRpThetaXY_Xi0510","East Roman Pot trk #theta_{y} vs #theta_{x} (0.05 < #xi < 0.10);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi1015 = new TH2D ("h2_eRpThetaXY_Xi1015","East Roman Pot trk #theta_{y} vs #theta_{x} (0.10 < #xi < 0.15);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi1520 = new TH2D ("h2_eRpThetaXY_Xi1520","East Roman Pot trk #theta_{y} vs #theta_{x} (0.15 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi2025 = new TH2D ("h2_eRpThetaXY_Xi2025","East Roman Pot trk #theta_{y} vs #theta_{x} (0.20 < #xi < 0.25);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi2530 = new TH2D ("h2_eRpThetaXY_Xi2530","East Roman Pot trk #theta_{y} vs #theta_{x} (0.25 < #xi < 0.30);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi3035 = new TH2D ("h2_eRpThetaXY_Xi3035","East Roman Pot trk #theta_{y} vs #theta_{x} (0.30 < #xi < 0.35);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi3540 = new TH2D ("h2_eRpThetaXY_Xi3540","East Roman Pot trk #theta_{y} vs #theta_{x} (0.35 < #xi < 0.40);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi4045 = new TH2D ("h2_eRpThetaXY_Xi4045","East Roman Pot trk #theta_{y} vs #theta_{x} (0.40 < #xi < 0.45);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi2550 = new TH2D ("h2_eRpThetaXY_Xi2550","East Roman Pot trk #theta_{y} vs #theta_{x} (0.25 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_Xi3050 = new TH2D ("h2_eRpThetaXY_Xi3050","East Roman Pot trk #theta_{y} vs #theta_{x} (0.30 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH1D *h1_eRpThetaY_rough_Xi0005 = new TH1D("h1_eRpThetaY_rough_Xi0005","East Roman Pot #theta_{Y} with rough cuts (0 < #xi < 0.05);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi0520 = new TH1D("h1_eRpThetaY_rough_Xi0520","East Roman Pot #theta_{Y} with rough cuts (0.05 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi2050 = new TH1D("h1_eRpThetaY_rough_Xi2050","East Roman Pot #theta_{Y} with rough cuts (0.20 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi0510 = new TH1D("h1_eRpThetaY_rough_Xi0510","East Roman Pot #theta_{Y} with rough cuts (0.05 < #xi < 0.10);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi1015 = new TH1D("h1_eRpThetaY_rough_Xi1015","East Roman Pot #theta_{Y} with rough cuts (0.10 < #xi < 0.15);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi1520 = new TH1D("h1_eRpThetaY_rough_Xi1520","East Roman Pot #theta_{Y} with rough cuts (0.15 < #xi < 0.20);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi2025 = new TH1D("h1_eRpThetaY_rough_Xi2025","East Roman Pot #theta_{Y} with rough cuts (0.20 < #xi < 0.25);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi2530 = new TH1D("h1_eRpThetaY_rough_Xi2530","East Roman Pot #theta_{Y} with rough cuts (0.25 < #xi < 0.30);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi3035 = new TH1D("h1_eRpThetaY_rough_Xi3035","East Roman Pot #theta_{Y} with rough cuts (0.30 < #xi < 0.35);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi3540 = new TH1D("h1_eRpThetaY_rough_Xi3540","East Roman Pot #theta_{Y} with rough cuts (0.35 < #xi < 0.40);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi4045 = new TH1D("h1_eRpThetaY_rough_Xi4045","East Roman Pot #theta_{Y} with rough cuts (0.40 < #xi < 0.45);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi2550 = new TH1D("h1_eRpThetaY_rough_Xi2550","East Roman Pot #theta_{Y} with rough cuts (0.25 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH1D *h1_eRpThetaY_rough_Xi3050 = new TH1D("h1_eRpThetaY_rough_Xi3050","East Roman Pot #theta_{Y} with rough cuts (0.30 < #xi < 0.50);#theta_{Y} [mrad]",60,-15,15);
    TH2D *h2_eRpThetaXY_rough_Xi0005 = new TH2D ("h2_eRpThetaXY_rough_Xi0005","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0 < #xi < 0.05);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi0520 = new TH2D ("h2_eRpThetaXY_rough_Xi0520","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.05 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi2050 = new TH2D ("h2_eRpThetaXY_rough_Xi2050","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (#xi > 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi0510 = new TH2D ("h2_eRpThetaXY_rough_Xi0510","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.05 < #xi < 0.10);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi1015 = new TH2D ("h2_eRpThetaXY_rough_Xi1015","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.10 < #xi < 0.15);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi1520 = new TH2D ("h2_eRpThetaXY_rough_Xi1520","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.15 < #xi < 0.20);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi2025 = new TH2D ("h2_eRpThetaXY_rough_Xi2025","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.20 < #xi < 0.25);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi2530 = new TH2D ("h2_eRpThetaXY_rough_Xi2530","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.25 < #xi < 0.30);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi3035 = new TH2D ("h2_eRpThetaXY_rough_Xi3035","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.30 < #xi < 0.35);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi3540 = new TH2D ("h2_eRpThetaXY_rough_Xi3540","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.35 < #xi < 0.40);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi4045 = new TH2D ("h2_eRpThetaXY_rough_Xi4045","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.40 < #xi < 0.45);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi2550 = new TH2D ("h2_eRpThetaXY_rough_Xi2550","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.25 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);
    TH2D *h2_eRpThetaXY_rough_Xi3050 = new TH2D ("h2_eRpThetaXY_rough_Xi3050","East Roman Pot trk #theta_{y} vs #theta_{x} with rough cuts (0.30 < #xi < 0.50);#theta_{x} [mrad];#theta_{y} [mrad]",60,-10,10,60,-10,10);


    TH1I *h1_goodEvents = new TH1I("h1_goodEvents","Good Events;",6,0,6);
    TH1I *h1_goodEvents_zerobias = new TH1I("h1_goodEvents_zerobias","Good Events (Zerobias);",6,0,6);

    TH2D *h2EvsPt = new TH2D("h2EvsPt", "Eng vs Pt; Pt [GeV/C]; E [GeV]", 100, 0, 100, 100, 0, 200);
    TH2D *h2PtvsE = new TH2D("h2PtvsE", "EM-jet P_{T} vs E; E [GeV]; P_{T} [GeV/c]", 100,  0., 100., 100, 0., 10.);
    TH2D *h2nPhVsEng = new TH2D("h2nPhVsEng", "Number of photons vs Eng; E [Gev]; No. of Photons", 100, 0, 200, 20, 0, 20);
    TH2D *h2xy_fms = new TH2D ("h2xy_fms", "EM Jet Position [FMS];EM Jet X [cm];EM Jet Y [cm]", 100, -100., 100., 100, -100., 100.);
    TH2D *h2xy_eemc = new TH2D ("h2xy_eemc", "EM Jet Position [EEMC];EM Jet X [cm];EM Jet Y [cm]", 100, -100, 100, 100, -100, 100);
    TH2D *h2EtaPhi_fms = new TH2D ("h2EtaPhi_fms", "EM Jet Eta Phi [FMS];EM Jet #eta; EM Jet #phi [rad]", 100, 2.5, 4.5, 100, -3.5, 3.5);
    TH2D *h2EtaPhi_eemc = new TH2D ("h2EtaPhi_eemc", "EM Jet Eta Phi [EEMC];EM Jet #eta;EM Jet #phi [rad]", 100, 0.8, 2.5, 100, -3.5, 3.5);
    TH2D *h2_sumEwest_vs_smallBBCsumWest = new TH2D("h2_sumEwest_vs_smallBBCsumWest","sum west side energy vs small BBC ADC sum for west side BBC;small BBC sum;energy[GeV]",200,0,10000,140,180,320);

    Double_t etaMin;
    Double_t etaMax;
    Double_t detZ; //For FMS
    Double_t pTcut = 2.0;
	Double_t FMSTrigThresP1[9]={1.84,2.76,3.68,1.26,1.84,2.53,1.26,1.84,2.76};
	Double_t FMSTrigThresP2[9]={1.84,2.76,3.68,1.15,1.84,2.18,1.15,1.84,2.76};
    TF1 *f1 = new TF1("f1","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x+[6]*x*x*x*x*x*x");
    f1->SetParameter(0,8.934910e0);
    f1->SetParameter(1,-6.63987e-1);
    f1->SetParameter(2,1.51376e-1);
    f1->SetParameter(3,-6.65678e-3);
    f1->SetParameter(4,1.56144e-4);
    f1->SetParameter(5,-1.84953e-6);
    f1->SetParameter(6,8.65440e-9);
    	TF1 *f4 = new TF1("f4","[0]+[1]*x+[2]*x*x");
    	f4->SetParameter(0,1.75278);
    	f4->SetParameter(1,1.01717);
    	f4->SetParameter(2,1.14455e-03);
    TF1 *f2 = new TF1("f2","[0]+[1]*x");
    f2->SetParameter(0,1.12965);
    f2->SetParameter(1,1.07394);
    TF1 *f2a = new TF1("f2a","[0]+[1]*x");
    f2a->SetParameter(0,1.45191e+00);
    f2a->SetParameter(1,9.99575e-01);
    if(det == "fms")
    {
	etaMin = 2.0;
	etaMax = 4.5;
	detZ = 735.; //For FMS

	h1TrigType->GetXaxis()->SetBinLabel(1,"FMS JP0");
	h1TrigType->GetXaxis()->SetBinLabel(2,"FMS JP1");
	h1TrigType->GetXaxis()->SetBinLabel(3,"FMS JP2");
	h1TrigType->GetXaxis()->SetBinLabel(4,"Small BS1");
	h1TrigType->GetXaxis()->SetBinLabel(5,"Small BS2");
	h1TrigType->GetXaxis()->SetBinLabel(6,"Small BS3");
	h1TrigType->GetXaxis()->SetBinLabel(7,"Large BS1");
	h1TrigType->GetXaxis()->SetBinLabel(8,"Large BS2");
	h1TrigType->GetXaxis()->SetBinLabel(9,"Large BS3");	
    }
    else if(det == "eemc")
    {
	etaMin = 1.0;
	etaMax = 2.0;
	detZ = kEEmcZSMD; //For EEMC

	h1TrigType->GetXaxis()->SetBinLabel(1,"EHT0");
	h1TrigType->GetXaxis()->SetBinLabel(2,"JP1");
	h1TrigType->GetXaxis()->SetBinLabel(3,"JP2");
	h1TrigType->GetXaxis()->SetBinLabel(4,"EHT0*EJP1*L2Egamma");
	h1TrigType->GetXaxis()->SetBinLabel(5,"JP2*L2JetHigh");
	h1TrigType->GetXaxis()->SetBinLabel(6,"BHT1*VPDMB-30");
	h1TrigType->GetXaxis()->SetBinLabel(7,"BHT0*BBCMB");
	h1TrigType->GetXaxis()->SetBinLabel(8,"BHT1*BBCMB");
	h1TrigType->GetXaxis()->SetBinLabel(9,"BHT2*BBCMB");		
    }
    else
    {
	cout << "Invalid detector" <<endl;
	return;
    }
    
    
    Double_t jetX, jetY, eta, phi, theta, vtxZ, eng, pt, dUE, UE, RpPx, RpPy , WestRpPx, WestRpPy, EastRpP, WestRpP , eng_corr , WestRpXi, EastRpPx, EastRpPy, EastRpXi , WestRpThetaX , WestRpThetaY, EastRpThetaX, EastRpThetaY;
    Int_t nJets = 0;
    int runit,goodrunit;
    int thisFillNum, thisRunNum;
    std::vector<int>::iterator it;


    struct run
    {
	
	int runindex;
	long runnum;
    } runFMS[675];

    vector<int> RunNumber;
    //std::vector<int>::iterator it, it2;

    ifstream runfile;
    runfile.open("run15fmsrunnumber.txt");
    for (int i=0; i<675; ++i)
    {

	runFMS[i].runindex = i;
	runfile >> runFMS[i].runnum;
	RunNumber.push_back(runFMS[i].runnum);

    }
    
    cout << "Total Entries to be processed: "<< ch->GetEntries() <<endl;

    for(Int_t evt = 0; evt < ch->GetEntries(); ++evt)
    {
	ch->GetEntry(evt);

	if(evt % 1000 == 0)
	    cout << "Events Processed: "<< evt <<endl;
	
	skimEvent = jetEvent->GetEvent();
	h1_goodEvents->Fill(0);
	h1_goodEvents_zerobias->Fill(0);
	h1_NPosVertex->Fill(skimEvent->GetNPosVertex());

	//cout<<"Trigger ID:"<<skimEvent->GetTrigFlag(5)<<endl;	
	//h1trigId->Fill(skimEvent->GetTrigId() % 1000);
	h1UnixTime->Fill(skimEvent->GetUnixTime());
	//cout << "Unix time:" << skimEvent->GetUnixTime() << endl;
	h1spinB->Fill(skimEvent->GetSpinB());
	h1spinY->Fill(skimEvent->GetSpinY());
	h1_smallBBCsumEast->Fill(skimEvent->GetBbcSumSmall(0));
	h1_largeBBCsumEast->Fill(skimEvent->GetBbcSumLarge(0));
	h1_smallBBCsumWest->Fill(skimEvent->GetBbcSumSmall(1));
	h1_largeBBCsumWest->Fill(skimEvent->GetBbcSumLarge(1));
	h1_ZDCE->Fill(skimEvent->GetZdcSum(0));
	h1nJets_all->Fill(jetEvent->GetNumberOfJets());
	vtxZ = skimEvent->GetVertexZ();
	h1vtxZ->Fill(vtxZ);

		thisRunNum = skimEvent->GetRunNumber();
	it = std::find (RunNumber.begin(), RunNumber.end(), thisRunNum);
	runit = it - RunNumber.begin();
	//if (it == RunNumber.end()) {continue;}
	if (runit == 675) {continue;}
	
	 for(Int_t t = 0; t < 9; ++t) //Moved to the end of envet loop
	 {
	     if(skimEvent->GetTrigFlag(t))
	 	h1TrigType->Fill(t);
	 }

	nJets = 0;	
	    	Int_t nRpsTracks = rpsArr->GetEntriesFast();
		if (nRpsTracks > 0) {h1_nRPEvent_run->Fill(runit);}
		//if (skimEvent->GetRPMult() > 0) cout << "nRp track:"<<skimEvent->GetRPMult()<<endl;
		if (nRpsTracks > 0) h1_goodEvents->Fill(1);
		if (nRpsTracks > 0) h1_goodEvents_zerobias->Fill(1);
	//if (skimEvent->GetFmsPointMult()>0) h1_goodEvents->Fill(2);
		if (jetEvent->GetNumberOfJets() > 0) h1_goodEvents->Fill(2);
	for(Int_t j = 0; j <  jetEvent->GetNumberOfJets(); ++j)
	{
	    jet = jetEvent->GetJet(j);
	    eng_corr = -1;
	   	    
	    eta = jet->GetEta();
	    phi = jet->GetPhi();
	    theta =  2 * atan( exp(-eta) );

//	    if(eta < etaMin || eta > etaMax) //Conside only EEMC and FMS coverage
//		continue;

	    eng = jet->GetE();
	    pt = jet->GetPt();
	    dUE = jet->GetUedPt();
	    UE = eng + dUE;
	    
	    if (pt < pTcut) continue;

	    h1nPhotons->Fill(jet->GetNumberOfTowers());
	    h1Eta->Fill(eta);
	    h1Phi->Fill(phi);
	    h1Pt->Fill(pt);
	    h1E->Fill(eng);
	    h1dUE->Fill(fabs(dUE));
	    h1UE->Fill(UE);
	    if ((eng > 5)&&(eng < 10)) {eng_corr = f1->Eval(eng);} 
		else {if ((eng > 10)&&(eng < 60)) {eng_corr = f2->Eval(eng);} else {eng_corr = eng;}}

	    h1E_corr->Fill(eng_corr);
	    if ((jet->GetNumberOfTowers() <=2)&&(jet->GetNumberOfTowers()>0)) {h1E_corr_12np->Fill(eng_corr);}

	    bool good_emjet_pt = false;
	    for(Int_t t = 0; t < 9; ++t) 
	    {
	        if(skimEvent->GetTrigFlag(t))
		{

			if (thisRunNum < 16069039) {if ((pt > pTcut)&&(FMSTrigThresP1[t] < pt)) {good_emjet_pt = true;break;}}
			else {if ((pt > pTcut)&&(FMSTrigThresP2[t] < pt)) {good_emjet_pt = true;break;}}
		}
	    }
	    if (!good_emjet_pt) continue;
	    ++nJets;

	    h2EvsPt->Fill(pt, eng);
	    h2PtvsE->Fill(eng, pt);
	    h2nPhVsEng->Fill(eng, jet->GetNumberOfTowers());

	    jetX = (detZ - vtxZ) * tan(theta) * cos(phi);
	    jetY = (detZ - vtxZ) * tan(theta) * sin(phi);
	    
	    if(det == "fms")  //actual range 2.65 - 3.9
	    {	
		h2xy_fms->Fill(jetX, jetY);
		h2EtaPhi_fms->Fill(eta, phi);

		if(eta > 2.0 && eta < 3.15) //FMS large cells
		    h1JetE_l->Fill(eng); 
		if(eta > 3.15 && eta < 4.0)  //FMS small cells
		    h1JetE_s->Fill(eng);		
	    }
	    
	    if(det == "eemc")   // actual range 1.086 - 2.0
	    {
		h2xy_eemc->Fill(jetX, jetY);
		h2EtaPhi_eemc->Fill(eta, phi);
		if (skimEvent->GetTrigFlag(1)) {h1Pt_JP1->Fill(pt);h1E_JP1->Fill(eng);}
		if (skimEvent->GetTrigFlag(2)) {h1Pt_JP2->Fill(pt);h1E_JP2->Fill(eng);h1E_JP1->Fill(eng);}
	    }
	    
	    for(Int_t k = 0; k < jet->GetNumberOfTowers(); ++k)
	    {
		tower = jet->GetTower(k);
	
		h1TowerEta->Fill(tower->GetEta());
		h1TowerPhi->Fill(tower->GetPhi());
		h1TowerE->Fill(tower->GetEnergy());
	    }
	}
	h1nJets->Fill(nJets);

		//rp tracks
		int nRpsTracksEast=0;	
		int nRpsTracksWest=0;	
		int nRpsTracksEastNocut=0;	
		int nRpsTracksWestNocut=0;	
		Double_t sumEwest=0;
		Double_t xy2;
	    	//Int_t nRpsTracks = rpsArr->GetEntriesFast();
		h1_nRpTracks->Fill(nRpsTracks);
		bool goodwRP = false;
		bool goodeRP = false;
		bool PassRoughThetaXYEastCut = false;
		bool PassRoughThetaXYWestCut = false;

		//if ((skimEvent->GetBbcSumSmall(1) > 250)||(skimEvent->GetBbcSumSmall(0) < 150)) continue;
		//if ((skimEvent->GetBbcSumSmall(1) > 90)) continue;
		//if ((skimEvent->GetBbcSumSmall(0) > 90)) continue;

		for (Int_t rpTrk=0; rpTrk<nRpsTracks;++rpTrk)
		{
		
			rpsTrack = (TStRpsTrackData*)rpsArr->At(rpTrk);

			h1_RpNPlanes->Fill(rpsTrack->GetNplanes());
			if (rpsTrack->GetBranch() == 2 || rpsTrack->GetBranch() == 3) {++nRpsTracksWestNocut;}
			if (rpsTrack->GetBranch() == 0 || rpsTrack->GetBranch() == 1) {++nRpsTracksEastNocut;}
			//if ((rpsTrack->GetNplanes() < 7)) {h2_RpPyPx_bkg->Fill(rpsTrack->GetPx(),rpsTrack->GetPy());continue;}
			//else {h2_RpPyPx_sig->Fill(rpsTrack->GetPx(),rpsTrack->GetPy());}
			if (rpsTrack->GetNplanes() < 7) continue;

			RpPx = rpsTrack->GetPx();
			RpPy = rpsTrack->GetPy();
			//if (!((RpPx < 0.3)&&(RpPx > -0.5)&&(((RpPy < 0.4)&&(RpPy > 0.25)) || ((RpPy < -0.25)&&(RpPy > -0.4))))) {continue;}
			//if (!((RpPx < 0.3)&&(RpPx > -0.25)&&(((RpPy < 0.55)&&(RpPy > 0.3)) || ((RpPy < -0.4)&&(RpPy > -0.6))))) {continue;}
			if((rpsTrack->GetBranch() == 2) || (rpsTrack->GetBranch() == 3) && (process == "SE")) //West RP :: 2 West Up RP, 3: East Down RP
            		{
				if ((skimEvent->GetBbcSumSmall(1) > 150)) continue;
				++nRpsTracksWest;
				WestRpP = rpsTrack->GetP();
				WestRpPx = rpsTrack->GetPx();
				WestRpPy = rpsTrack->GetPy();
				WestRpThetaX = rpsTrack->GetThetaX();
				WestRpThetaY = rpsTrack->GetThetaY();
				WestRpXi = 1.0 * (100. - WestRpP) / 100.0;
                		h1_wRpP->Fill(rpsTrack->GetP());
                		h1_wRpPt->Fill(rpsTrack->GetPt());
				h1_wRpEta->Fill(rpsTrack->GetEta());
				h1_wRpPhi->Fill(rpsTrack->GetPhi());
				sumEwest = rpsTrack->GetP();
				h1_wRPXi->Fill(WestRpXi);
				h2_wRpThetaXXi->Fill(WestRpXi,WestRpThetaX);
				h2_wRpThetaYXi->Fill(WestRpXi,WestRpThetaY);

				if ((WestRpXi > 0.20)) {h1_wRpThetaY_rough_Xi2050->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi2050->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.25)) {h1_wRpThetaY_rough_Xi2550->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi2550->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.30)) {h1_wRpThetaY_rough_Xi3050->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi3050->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi < 0.05)&&(WestRpXi > 0.00)) {h1_wRpThetaY_rough_Xi0005->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi0005->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.05)&&(WestRpXi < 0.20)) {h1_wRpThetaY_rough_Xi0520->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi0520->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.00)&&(WestRpXi < 0.05)) {h1_wRpThetaY_rough_Xi0005->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi0005->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.05)&&(WestRpXi < 0.10)) {h1_wRpThetaY_rough_Xi0510->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi0510->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.10)&&(WestRpXi < 0.15)) {h1_wRpThetaY_rough_Xi1015->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi1015->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.15)&&(WestRpXi < 0.20)) {h1_wRpThetaY_rough_Xi1520->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi1520->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.20)&&(WestRpXi < 0.25)) {h1_wRpThetaY_rough_Xi2025->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi2025->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.25)&&(WestRpXi < 0.30)) {h1_wRpThetaY_rough_Xi2530->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi2530->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.30)&&(WestRpXi < 0.35)) {h1_wRpThetaY_rough_Xi3035->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi3035->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.35)&&(WestRpXi < 0.40)) {h1_wRpThetaY_rough_Xi3540->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi3540->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.40)&&(WestRpXi < 0.45)) {h1_wRpThetaY_rough_Xi4045->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi4045->Fill(WestRpThetaX,WestRpThetaY); }
				if ((WestRpXi > 0.45)&&(WestRpXi < 0.50)) {h1_wRpThetaY_rough_Xi4550->Fill(WestRpThetaY); h2_wRpThetaXY_rough_Xi4550->Fill(WestRpThetaX,WestRpThetaY); }


				if ((skimEvent->GetBbcSumSmall(1) <=80)&&(skimEvent->GetBbcSumLarge(1) <=60)) 
				{
					if ((WestRpXi > 0.20)) {h1_wRpThetaY_Xi2050->Fill(WestRpThetaY); h2_wRpThetaXY_Xi2050->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.25)) {h1_wRpThetaY_Xi2550->Fill(WestRpThetaY); h2_wRpThetaXY_Xi2550->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.30)) {h1_wRpThetaY_Xi3050->Fill(WestRpThetaY); h2_wRpThetaXY_Xi3050->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.05)&&(WestRpXi < 0.20)) {h1_wRpThetaY_Xi0520->Fill(WestRpThetaY); h2_wRpThetaXY_Xi0520->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.00)&&(WestRpXi < 0.05)) {h1_wRpThetaY_Xi0005->Fill(WestRpThetaY); h2_wRpThetaXY_Xi0005->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.05)&&(WestRpXi < 0.10)) {h1_wRpThetaY_Xi0510->Fill(WestRpThetaY); h2_wRpThetaXY_Xi0510->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.10)&&(WestRpXi < 0.15)) {h1_wRpThetaY_Xi1015->Fill(WestRpThetaY); h2_wRpThetaXY_Xi1015->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.15)&&(WestRpXi < 0.20)) {h1_wRpThetaY_Xi1520->Fill(WestRpThetaY); h2_wRpThetaXY_Xi1520->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.20)&&(WestRpXi < 0.25)) {h1_wRpThetaY_Xi2025->Fill(WestRpThetaY); h2_wRpThetaXY_Xi2025->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.25)&&(WestRpXi < 0.30)) {h1_wRpThetaY_Xi2530->Fill(WestRpThetaY); h2_wRpThetaXY_Xi2530->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.30)&&(WestRpXi < 0.35)) {h1_wRpThetaY_Xi3035->Fill(WestRpThetaY); h2_wRpThetaXY_Xi3035->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.35)&&(WestRpXi < 0.40)) {h1_wRpThetaY_Xi3540->Fill(WestRpThetaY); h2_wRpThetaXY_Xi3540->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.40)&&(WestRpXi < 0.45)) {h1_wRpThetaY_Xi4045->Fill(WestRpThetaY); h2_wRpThetaXY_Xi4045->Fill(WestRpThetaX,WestRpThetaY); }
					if ((WestRpXi > 0.45)&&(WestRpXi < 0.50)) {h1_wRpThetaY_Xi4550->Fill(WestRpThetaY); h2_wRpThetaXY_Xi4550->Fill(WestRpThetaX,WestRpThetaY); }
				}


				if ((fabs(WestRpThetaY) > 4) || (fabs(WestRpThetaY) < 1.5)) continue;
				if ((WestRpXi > 0.00) && (WestRpXi < 0.05) && ((WestRpThetaX > 1.75) || (WestRpThetaX < -1))) continue; 
				if ((WestRpXi > 0.05) && (WestRpXi < 0.10) && ((WestRpThetaX > 1.50) || (WestRpThetaX < -1.5))) continue; 
				if ((WestRpXi > 0.10) && (WestRpXi < 0.15) && ((WestRpThetaX > 1.25) || (WestRpThetaX < -1.75))) continue; 
				if ((WestRpXi > 0.15) && (WestRpXi < 0.20) && ((WestRpThetaX > 1) || (WestRpThetaX < -2))) continue; 
				if ((WestRpXi > 0.20) && (WestRpXi < 0.25) && ((WestRpThetaX > 0.5) || (WestRpThetaX < -2.75))) continue; 
				if ((WestRpXi > 0.25) && (WestRpXi < 0.30) && ((WestRpThetaX > 0.50) || (WestRpThetaX < -3.25))) continue; 
				if ((WestRpXi > 0.30) && (WestRpXi < 0.35) && ((WestRpThetaX > 0.00) || (WestRpThetaX < -3.75))) continue; 
				if ((WestRpXi > 0.35) && (WestRpXi < 0.40) && ((WestRpThetaX > -0.5) || (WestRpThetaX < -4.5))) continue; 
				if ((WestRpXi > 0.40) && (WestRpXi < 0.45) && ((WestRpThetaX > -1.25) || (WestRpThetaX < -5.5))) continue; 
				//if ((WestRpXi > 0.45) && (WestRpXi < 0.50) && ((WestRpThetaX > -2.0) || (WestRpThetaX < -6))) continue;
				PassRoughThetaXYWestCut = true;
				if ((skimEvent->GetBbcSumSmall(1) > 80)||(skimEvent->GetBbcSumLarge(1) > 60)) continue;

				//if ((WestRpXi > 0.3) && (WestRpXi < 0.5) && ((rpsTrack->GetThetaX() > -0.5) || (rpsTrack->GetThetaX() < -5))) continue; 
				if ((WestRpXi > 0.05)&&(WestRpXi < 0.2)) {h2_wRpPyPx_Xi0520->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.2)) {h2_wRpPyPx_Xi2050->Fill(WestRpPx,WestRpPy);  }
				if ((WestRpXi > 0.00)&&(WestRpXi < 0.05)) {h2_wRpPyPx_Xi0005->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.05)&&(WestRpXi < 0.10)) {h2_wRpPyPx_Xi0510->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.10)&&(WestRpXi < 0.15)) {h2_wRpPyPx_Xi1015->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.15)&&(WestRpXi < 0.20)) {h2_wRpPyPx_Xi1520->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.20)&&(WestRpXi < 0.25)) {h2_wRpPyPx_Xi2025->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.25)&&(WestRpXi < 0.30)) {h2_wRpPyPx_Xi2530->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.30)&&(WestRpXi < 0.35)) {h2_wRpPyPx_Xi3035->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.35)&&(WestRpXi < 0.40)) {h2_wRpPyPx_Xi3540->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.40)&&(WestRpXi < 0.45)) {h2_wRpPyPx_Xi4045->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.45)&&(WestRpXi < 0.50)) {h2_wRpPyPx_Xi4550->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.25)) {h2_wRpPyPx_Xi2550->Fill(WestRpPx,WestRpPy); }
				if ((WestRpXi > 0.30)) {h2_wRpPyPx_Xi3050->Fill(WestRpPx,WestRpPy); }

				if ((WestRpXi > 0.0)&&(WestRpXi < 0.05))
				{

					xy2 = sqrt(pow((WestRpPx - 0.03),2) + pow((fabs(WestRpPy) - 0.18),2));
					if ((xy2 > 0.14)||(fabs(WestRpPy) < 0.18)) continue;

				}
				if ((WestRpXi > 0.05)&&(WestRpXi < 0.10))
				{

					xy2 = sqrt(pow((WestRpPx - 0.01),2) + pow((fabs(WestRpPy) - 0.18),2));
					if ((xy2 > 0.14)||(fabs(WestRpPy) < 0.18)) continue;

				}
				if ((WestRpXi > 0.10)&&(WestRpXi < 0.15))
				{

					xy2 = sqrt(pow((WestRpPx + 0.02),2) + pow((fabs(WestRpPy) - 0.16),2));
					if ((xy2 > 0.14)||(fabs(WestRpPy) < 0.16)) continue;

				}
				if ((WestRpXi > 0.15)&&(WestRpXi < 0.20))
				{

					xy2 = sqrt(pow((WestRpPx + 0.04),2) + pow((fabs(WestRpPy) - 0.16),2));
					if ((xy2 > 0.12)||(fabs(WestRpPy) < 0.16)) continue;

				}
				if ((WestRpXi > 0.20)&&(WestRpXi < 0.25))
				{

					xy2 = sqrt(pow((WestRpPx + 0.06),2) + pow((fabs(WestRpPy) - 0.14),2));
					if ((xy2 > 0.12)||(fabs(WestRpPy) < 0.14)) continue;

				}
				if ((WestRpXi > 0.25)&&(WestRpXi < 0.30))
				{

					xy2 = sqrt(pow((WestRpPx + 0.10),2) + pow((fabs(WestRpPy) - 0.14),2));
					if ((xy2 > 0.12)||(fabs(WestRpPy) < 0.14)) continue;

				}
				if ((WestRpXi > 0.30)&&(WestRpXi < 0.35))
				{

					xy2 = sqrt(pow((WestRpPx + 0.11),2) + pow((fabs(WestRpPy) - 0.12),2));
					if ((xy2 > 0.12)||(fabs(WestRpPy) < 0.12)) continue;

				}
				if ((WestRpXi > 0.35)&&(WestRpXi < 0.40))
				{

					xy2 = sqrt(pow((WestRpPx + 0.14),2) + pow((fabs(WestRpPy) - 0.12),2));
					if ((xy2 > 0.11)||(fabs(WestRpPy) < 0.12)) continue;

				}
				if ((WestRpXi > 0.40)&&(WestRpXi < 0.45))
				{

					xy2 = sqrt(pow((WestRpPx + 0.17),2) + pow((fabs(WestRpPy) - 0.12),2));
					if ((xy2 > 0.10)||(fabs(WestRpPy) < 0.12)) continue;

				}
				//if ((WestRpXi > 0.45)&&(WestRpXi < 0.5))
				//{

				//	xy2 = sqrt(pow((WestRpPx + 0.19),2) + pow((fabs(WestRpPy) - 0.1),2));
				//	if ((xy2 > 0.11)||(fabs(WestRpPy) < 0.11)||(WestRpPx > -0.12)) continue;

				//}

				if ((WestRpXi > 0.00) && (WestRpXi < 0.45)) {goodwRP = true;}
				//if ((WestRpXi > 0.1) && (WestRpXi < 0.2) && ((WestRpPx > -0.3) && (WestRpPx < 0.2)) && (((WestRpPy > -0.6) && (WestRpPy < -0.35)) || ((WestRpPy > 0.3) && (WestRpPy < 0.55)))) {goodwRP = true;}
				//if ((WestRpXi > 0.2) && (WestRpXi < 0.3) && ((WestRpPx > -0.3) && (WestRpPx < 0.15)) && (((WestRpPy > -0.5) && (WestRpPy < -0.3)) || ((WestRpPy > 0.3) && (WestRpPy < 0.5)))) {goodwRP = true;}
				//if ((WestRpXi > 0.3) && (WestRpXi < 0.5) && ((WestRpPx > -0.6) && (WestRpPx < 0)) && (((WestRpPy > -0.5) && (WestRpPy < -0.3)) || ((WestRpPy > 0.2) && (WestRpPy < 0.5)))) {goodwRP = true;}
			}

			if ((process == "SD") && ((rpsTrack->GetBranch() == 0 || rpsTrack->GetBranch() == 1))) //East RP :: O East Up RP, 1: East Down RP
                        {
				++nRpsTracksEast;
				if ((skimEvent->GetBbcSumSmall(0) > 150)) continue;
				EastRpP = rpsTrack->GetP();
				EastRpPx = rpsTrack->GetPx();
				EastRpPy = rpsTrack->GetPy();
				EastRpThetaX = rpsTrack->GetThetaX();
				EastRpThetaY = rpsTrack->GetThetaY();
				EastRpXi = 1.0 * (100. - EastRpP) / 100.0;
				h1_eRpP->Fill(EastRpP);
				h1_eRpPt->Fill(rpsTrack->GetPt());
				h1_eRpEta->Fill(rpsTrack->GetEta());
				h1_eRpPhi->Fill(rpsTrack->GetPhi());
				h1_eRPXi->Fill(EastRpXi);
				h2_eRpThetaXXi->Fill(EastRpXi,EastRpThetaX);
				h2_eRpThetaYXi->Fill(EastRpXi,EastRpThetaY);
				if (EastRpXi > 0.20) {h1_eRpThetaY_rough_Xi2050->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi2050->Fill(EastRpThetaX,EastRpThetaY); }
				if (EastRpXi > 0.25) {h1_eRpThetaY_rough_Xi2550->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi2550->Fill(EastRpThetaX,EastRpThetaY); }
				if (EastRpXi > 0.30) {h1_eRpThetaY_rough_Xi3050->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi3050->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.00)&&(EastRpXi < 0.05)) {h1_eRpThetaY_rough_Xi0005->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi0005->Fill(EastRpThetaX,EastRpThetaY);}
				if ((EastRpXi > 0.05)&&(EastRpXi < 0.20)) {h1_eRpThetaY_rough_Xi0520->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi0520->Fill(EastRpThetaX,EastRpThetaY);}
				if ((EastRpXi > 0.05)&&(EastRpXi < 0.10)) {h1_eRpThetaY_rough_Xi0510->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi0510->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.10)&&(EastRpXi < 0.15)) {h1_eRpThetaY_rough_Xi1015->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi1015->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.15)&&(EastRpXi < 0.20)) {h1_eRpThetaY_rough_Xi1520->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi1520->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.20)&&(EastRpXi < 0.25)) {h1_eRpThetaY_rough_Xi2025->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi2025->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.25)&&(EastRpXi < 0.30)) {h1_eRpThetaY_rough_Xi2530->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi2530->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.30)&&(EastRpXi < 0.35)) {h1_eRpThetaY_rough_Xi3035->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi3035->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.35)&&(EastRpXi < 0.40)) {h1_eRpThetaY_rough_Xi3540->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi3540->Fill(EastRpThetaX,EastRpThetaY); }
				if ((EastRpXi > 0.40)&&(EastRpXi < 0.45)) {h1_eRpThetaY_rough_Xi4045->Fill(EastRpThetaY); h2_eRpThetaXY_rough_Xi4045->Fill(EastRpThetaX,EastRpThetaY); }

				if ((skimEvent->GetBbcSumSmall(0) <= 90)&&(skimEvent->GetBbcSumLarge(0) <= 80))
				{
					if (EastRpXi > 0.20) {h1_eRpThetaY_Xi2050->Fill(EastRpThetaY); h2_eRpThetaXY_Xi2050->Fill(EastRpThetaX,EastRpThetaY); }
					if (EastRpXi > 0.25) {h1_eRpThetaY_Xi2550->Fill(EastRpThetaY); h2_eRpThetaXY_Xi2550->Fill(EastRpThetaX,EastRpThetaY); }
					if (EastRpXi > 0.30) {h1_eRpThetaY_Xi3050->Fill(EastRpThetaY); h2_eRpThetaXY_Xi3050->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.00)&&(EastRpXi < 0.05)) {h1_eRpThetaY_Xi0005->Fill(EastRpThetaY); h2_eRpThetaXY_Xi0005->Fill(EastRpThetaX,EastRpThetaY);}
					if ((EastRpXi > 0.05)&&(EastRpXi < 0.20)) {h1_eRpThetaY_Xi0520->Fill(EastRpThetaY); h2_eRpThetaXY_Xi0520->Fill(EastRpThetaX,EastRpThetaY);}
					if ((EastRpXi > 0.05)&&(EastRpXi < 0.10)) {h1_eRpThetaY_Xi0510->Fill(EastRpThetaY); h2_eRpThetaXY_Xi0510->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.10)&&(EastRpXi < 0.15)) {h1_eRpThetaY_Xi1015->Fill(EastRpThetaY); h2_eRpThetaXY_Xi1015->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.15)&&(EastRpXi < 0.20)) {h1_eRpThetaY_Xi1520->Fill(EastRpThetaY); h2_eRpThetaXY_Xi1520->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.20)&&(EastRpXi < 0.25)) {h1_eRpThetaY_Xi2025->Fill(EastRpThetaY); h2_eRpThetaXY_Xi2025->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.25)&&(EastRpXi < 0.30)) {h1_eRpThetaY_Xi2530->Fill(EastRpThetaY); h2_eRpThetaXY_Xi2530->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.30)&&(EastRpXi < 0.35)) {h1_eRpThetaY_Xi3035->Fill(EastRpThetaY); h2_eRpThetaXY_Xi3035->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.35)&&(EastRpXi < 0.40)) {h1_eRpThetaY_Xi3540->Fill(EastRpThetaY); h2_eRpThetaXY_Xi3540->Fill(EastRpThetaX,EastRpThetaY); }
					if ((EastRpXi > 0.40)&&(EastRpXi < 0.45)) {h1_eRpThetaY_Xi4045->Fill(EastRpThetaY); h2_eRpThetaXY_Xi4045->Fill(EastRpThetaX,EastRpThetaY); }


					if ((EastRpXi < 0.05)) {h2_eRpPyPx_Xi0005->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.20)) {h2_eRpPyPx_Xi2050->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.25)) {h2_eRpPyPx_Xi2550->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.30)) {h2_eRpPyPx_Xi3050->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.05)&&(EastRpXi < 0.20)) {h2_eRpPyPx_Xi0520->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.05)&&(EastRpXi < 0.10)) {h2_eRpPyPx_Xi0510->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.10)&&(EastRpXi < 0.15)) {h2_eRpPyPx_Xi1015->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.15)&&(EastRpXi < 0.20)) {h2_eRpPyPx_Xi1520->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.20)&&(EastRpXi < 0.25)) {h2_eRpPyPx_Xi2025->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.25)&&(EastRpXi < 0.30)) {h2_eRpPyPx_Xi2530->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.30)&&(EastRpXi < 0.35)) {h2_eRpPyPx_Xi3035->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.35)&&(EastRpXi < 0.40)) {h2_eRpPyPx_Xi3540->Fill(EastRpPx,EastRpPy); }
					if ((EastRpXi > 0.40)&&(EastRpXi < 0.45)) {h2_eRpPyPx_Xi4045->Fill(EastRpPx,EastRpPy); }

				}

				if ((fabs(EastRpThetaY) > 4) || (fabs(EastRpThetaY) < 2)) continue;
				if ((EastRpXi > 0.00) && (EastRpXi < 0.05) && ((EastRpThetaX > 1.50) || (EastRpThetaX < -1))) continue; 
				if ((EastRpXi > 0.05) && (EastRpXi < 0.10) && ((EastRpThetaX > 1.25) || (EastRpThetaX < -1.25))) continue; 
				if ((EastRpXi > 0.10) && (EastRpXi < 0.15) && ((EastRpThetaX > 1.25) || (EastRpThetaX < -1.5))) continue; 
				//if ((EastRpXi > 0.15) && (EastRpXi < 0.20) && ((EastRpThetaX > 0.75) || (EastRpThetaX < -2))) continue; 
				//if ((EastRpXi > 0.20) && (EastRpXi < 0.25) && ((EastRpThetaX > 0.75) || (EastRpThetaX < -2.5))) continue; 
				//if ((EastRpXi > 0.25) && (EastRpXi < 0.30) && ((EastRpThetaX > 0.50) || (EastRpThetaX < -3))) continue; 
				//if ((EastRpXi > 0.30) && (EastRpXi < 0.35) && ((EastRpThetaX > 0.25) || (EastRpThetaX < -3.5))) continue; 
				//if ((EastRpXi > 0.35) && (EastRpXi < 0.40) && ((EastRpThetaX >-0.25) || (EastRpThetaX < -4.5))) continue; 
				//if ((EastRpXi > 0.40) && (EastRpXi < 0.45) && ((EastRpThetaX > -0.5) || (EastRpThetaX < -5))) continue; 
				PassRoughThetaXYEastCut = true;
				//if ((EastRpXi > 0.3) && (EastRpXi < 0.5) && ((rpsTrack->GetThetaX() > -0.25) || (rpsTrack->GetThetaX() < -5))) continue; 


				if ((EastRpXi > 0.00)&&(EastRpXi < 0.05))
				{

					xy2 = sqrt(pow((EastRpPx + 0.02),2) + pow((fabs(EastRpPy) - 0.20),2));
					if (!(((xy2 < 0.15)||((EastRpPx < -0.02)&&(EastRpPx > -0.08)))&&((fabs(EastRpPy) > 0.20)&&(fabs(EastRpPy) < 0.35)))) continue;

				}
				if ((EastRpXi > 0.05)&&(EastRpXi < 0.10))
				{

					xy2 = sqrt(pow((EastRpPx + 0.02),2) + pow((fabs(EastRpPy) - 0.20),2));
					if (!(((xy2 < 0.13)||((EastRpPx < -0.02)&&(EastRpPx > -0.10)))&&((fabs(EastRpPy) > 0.20)&&(fabs(EastRpPy) < 0.33)))) continue;

				}
				if ((EastRpXi > 0.10)&&(EastRpXi < 0.15))
				{

					xy2 = sqrt(pow((EastRpPx + 0.02),2) + pow((fabs(EastRpPy) - 0.18),2));
					if (!(((xy2 < 0.13)||((EastRpPx < -0.02)&&(EastRpPx > -0.12)))&&((fabs(EastRpPy) > 0.18)&&(fabs(EastRpPy) < 0.31)))) continue;

				}
				//if ((EastRpXi > 0.15)&&(EastRpXi < 0.20))
				//{

				//	xy2 = sqrt(pow((EastRpPx + 0.06),2) + pow((fabs(EastRpPy) - 0.18),2));
				//	if (!(((xy2 < 0.13)||((EastRpPx < -0.05)&&(EastRpPx > -0.16)))&&((fabs(EastRpPy) > 0.18)&&(fabs(EastRpPy) < 0.31)))) continue;

				//}
				//if ((EastRpXi > 0.20)&&(EastRpXi < 0.25))
				//{

				//	xy2 = sqrt(pow((EastRpPx + 0.06),2) + pow((fabs(EastRpPy) - 0.16),2));
				//	if (!(((xy2 < 0.12)||((EastRpPx < -0.06)&&(EastRpPx > -0.18)))&&((fabs(EastRpPy) > 0.16)&&(fabs(EastRpPy) < 0.28)))) continue;

				//}
				//if ((EastRpXi > 0.25)&&(EastRpXi < 0.30))
				//{

				//	xy2 = sqrt(pow((EastRpPx + 0.10),2) + pow((fabs(EastRpPy) - 0.16),2));
				//	if (!(((xy2 < 0.12)||((EastRpPx < -0.10)&&(EastRpPx > -0.20)))&&((fabs(EastRpPy) > 0.16)&&(fabs(EastRpPy) < 0.28)))) continue;

				//}
				//if ((EastRpXi > 0.30)&&(EastRpXi < 0.35))
				//{

				//	xy2 = sqrt(pow((EastRpPx + 0.10),2) + pow((fabs(EastRpPy) - 0.14),2));
				//	if (!(((xy2 < 0.12)||((EastRpPx < -0.10)&&(EastRpPx > -0.22)))&&((fabs(EastRpPy) > 0.14)&&(fabs(EastRpPy) < 0.26)))) continue;

				//}
				//if ((EastRpXi > 0.35)&&(EastRpXi < 0.40))
				//{

				//	xy2 = sqrt(pow((EastRpPx + 0.13),2) + pow((fabs(EastRpPy) - 0.13),2));
				//	if (!(((xy2 < 0.11)||((EastRpPx < -0.13)&&(EastRpPx > -0.26)))&&((fabs(EastRpPy) > 0.13)&&(fabs(EastRpPy) < 0.24)))) continue;

				//}
				//if ((EastRpXi > 0.40)&&(EastRpXi < 0.45))
				//{

				//	xy2 = sqrt(pow((EastRpPx + 0.15),2) + pow((fabs(EastRpPy) - 0.12),2));
				//	if (!(((xy2 < 0.10)||((EastRpPx < -0.15)&&(EastRpPx > -0.28)))&&((fabs(EastRpPy) > 0.12)&&(fabs(EastRpPy) < 0.22)))) continue;

				//}
				if ((EastRpXi > 0.00) && (EastRpXi < 0.15)) {goodeRP = true;}


				//if ((EastRpXi > 0.1) && (EastRpXi < 0.2) && ((EastRpPx > -0.3) && (EastRpPx < 0.2)) && (((EastRpPy > -0.6) && (EastRpPy < -0.35)) || ((EastRpPy > 0.3) && (EastRpPy < 0.55)))) {goodeRP = true;}
				//if ((EastRpXi > 0.2) && (EastRpXi < 0.3) && ((EastRpPx > -0.3) && (EastRpPx < 0.15)) && (((EastRpPy > -0.55) && (EastRpPy < -0.35)) || ((EastRpPy > 0.3) && (EastRpPy < 0.5)))) {goodeRP = true;}
				//if ((EastRpXi > 0.3) && (EastRpXi < 0.5) && ((EastRpPx > -0.5) && (EastRpPx < 0)) && (((EastRpPy > -0.5) && (EastRpPy < -0.35)) || ((EastRpPy > 0.25) && (EastRpPy < 0.4)))) {goodeRP = true;}

			}
			h1_RpThetaX->Fill(rpsTrack->GetThetaX());
			h1_RpThetaY->Fill(rpsTrack->GetThetaY());	
			h2_RpThetaXY->Fill(rpsTrack->GetThetaX(),rpsTrack->GetThetaY());
			h2_RpPyPx->Fill(rpsTrack->GetPx(),rpsTrack->GetPy());
			h2_RpPyP->Fill(rpsTrack->GetP(),rpsTrack->GetPy());

		}
		//if ((skimEvent->GetBbcSumSmall(1) > 90)||(skimEvent->GetBbcSumLarge(1) > 60)) continue;
		if ((jetEvent->GetNumberOfJets() > 0) && (nRpsTracksWestNocut == 1) && (nRpsTracksEastNocut <= 1)) h1_goodEvents->Fill(3);
		if ((jetEvent->GetNumberOfJets() > 0) && (nRpsTracksWestNocut == 1) && (nRpsTracksEastNocut <= 1) && goodwRP) h1_goodEvents->Fill(4);
		if ((jetEvent->GetNumberOfJets() > 0) && (nRpsTracksEastNocut == 1) && (nRpsTracksWestNocut <= 1) && goodeRP) h1_goodEvents->Fill(5);
		if ((nRpsTracksWestNocut == 1) && (goodwRP)) h1_goodEvents_zerobias->Fill(3);
		if ((nRpsTracksEastNocut == 1) && (goodeRP)) h1_goodEvents_zerobias->Fill(4);
		if ((nRpsTracksEastNocut == 1) && (nRpsTracksWestNocut == 1) && goodeRP && goodwRP) h1_goodEvents_zerobias->Fill(5);
		//if ((jetEvent->GetNumberOfJets() > 0) && (nRpsTracksWestNocut == 1) && (nRpsTracksEastNocut <= 1) && (skimEvent->GetBbcSumSmall(1) < 80) && (skimEvent->GetBbcSumSmall(0) < 80)) h1_goodEvents->Fill(5);

		h1_nRpTracksEastNocut->Fill(nRpsTracksEastNocut);
		h1_nRpTracksWestNocut->Fill(nRpsTracksWestNocut);
		//if ((nRpsTracksWestNocut == 1) && (PassRoughThetaXYWestCut)) {h1_smallBBCsumWest_RPcut->Fill(skimEvent->GetBbcSumSmall(1)); h1_largeBBCsumWest_RPcut->Fill(skimEvent->GetBbcSumLarge(1));}
		if ((PassRoughThetaXYWestCut)) {h1_smallBBCsumWest_RPcut->Fill(skimEvent->GetBbcSumSmall(1)); h1_largeBBCsumWest_RPcut->Fill(skimEvent->GetBbcSumLarge(1));}
		if ((nRpsTracksWestNocut == 1) && (goodwRP)) {h1_wRpP_passcut->Fill(WestRpP);}
		if ((nRpsTracksEastNocut == 1) && (goodeRP)) {h1_eRpP_passcut->Fill(EastRpP);}
		if ((PassRoughThetaXYEastCut)) {h1_smallBBCsumEast_RPcut->Fill(skimEvent->GetBbcSumSmall(0)); h1_largeBBCsumEast_RPcut->Fill(skimEvent->GetBbcSumLarge(0));}
		//if ((nRpsTracksEastNocut == 1) && (PassRoughThetaXYEastCut)) {h1_smallBBCsumEast_RPcut->Fill(skimEvent->GetBbcSumSmall(0)); h1_largeBBCsumEast_RPcut->Fill(skimEvent->GetBbcSumLarge(0));}

		if ((jetEvent->GetNumberOfJets()==0)&&(nRpsTracksWestNocut == 1)) {h1_wRpP_nojets->Fill(WestRpP);}
		if ((nRpsTracksWestNocut == 0)&&(jetEvent->GetNumberOfJets()==1))
		{
			
			
			for(Int_t j = 0; j <  jetEvent->GetNumberOfJets(); ++j)
			{
			    jet = jetEvent->GetJet(j);
			    eng_corr = -1;
	    			eng = jet->GetE();
	    			pt = jet->GetPt();
	    			dUE = jet->GetUedPt();
	    			UE = eng + dUE;
	    			
	    			if (pt < pTcut) continue;
	    			if ((eng > 7)&&(eng < 40)) {eng_corr = f2->Eval(eng);} 
	    			    else {if ((eng > 40)&&(eng < 90)) {eng_corr = f2a->Eval(eng);} else {eng_corr = eng;}}
	    			h1E_corr_NowRP->Fill(eng_corr);

	
			}
		}

		if ((nRpsTracks > 2)||(nRpsTracks == 0)||(process == "SD")) continue;



		if ((nRpsTracksEastNocut == 1) && (nRpsTracksWestNocut == 1) && (fabs(EastRpP - WestRpP) < 5)) {h2_RpPyPx_elastic->Fill(WestRpPx,WestRpPy);}
		//else
			//if ((EastRpP < 240)&&(WestRpP < 240)) {h2_RpPyPx_nonelastic->Fill(WestRpPx,WestRpPy);}

		if ((sumEwest > 0) && (nRpsTracksWestNocut == 1))
		{

			for(Int_t j = 0; j <  jetEvent->GetNumberOfJets(); ++j)
			{

	    			eng = jet->GetE();
	    			dUE = jet->GetUedPt();
	    			UE = eng + dUE;
				sumEwest = sumEwest + UE;


			}

			h1_sumEwest->Fill(sumEwest);
			h2_sumEwest_vs_smallBBCsumWest->Fill(skimEvent->GetBbcSumSmall(1) , sumEwest);		

		}


	    //Particle Branch is for simulated data only
	    // for(Int_t k = 0; k < jet->GetNumberOfParticles(); ++k)
	    // {
	    // 	particle = jet->GetParticle(k);
	
	    // }	    

	if(nJets > 0)
	{
	    for(Int_t t = 0; t < 9; ++t)
	    {
		if(skimEvent->GetTrigFlag(t))
		    h1TrigType->Fill(t);
	    }
	}
    }



    outFile->Write();
    outFile->Close();
    delete ch;
}
