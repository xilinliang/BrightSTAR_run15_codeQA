// Filename: DiffJetRpTreeQa.cxx
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Thu Jun 11 13:08:16 2020 (-0400)
// URL: jlab.org/~latif

#include "DiffJetXFCalc_EastRPnew.h"
#include "RootInclude.h"
#include "StRootInclude.h"
#include "BrJetMaker/TStJetCandidate.h"
#include "BrJetMaker/TStJetEvent.h"
#include "BrJetMaker/TStJetSkimEvent.h"
#include "BrContainers/TStRpsTrackData.h"
#include <iostream>

using namespace std;

//Use wildcat in the file name to combine many files.
void DiffJetXFCalc_EastRPnew(TString inFileName, TString outName, TString mode, TString process, TString det)
{
    TChain *ch = new TChain("T");
    ch->Add(inFileName);
    
    TStJetEvent *jetEvent = 0;
    TStJetSkimEvent *skimEvent;
    TStJetCandidate *jet;
    TStJetTower *tower;
    TStJetParticle *particle;
    TStRpsTrackData *rpsTrack =0;    

    TClonesArray *rpsArr = new TClonesArray("TStRpsTrackData");

    ch->SetBranchAddress("jetEvents", &jetEvent);
    ch->SetBranchAddress("rpTrack",&rpsArr);

	if (mode == "AN") cout << "start analysis physics! Not systematic." << endl;
	if (mode == "Ecorr") cout << "start energy correction systematic" << endl;
	if (mode == "Esum") cout << "start sum energy cut systematic" << endl;
	if (mode == "ROF") cout << "start ROF systematic" << endl;
	if (mode != "ROF") cout << "not doing ROF systematic" << endl;
	if (mode == "smallBBC") cout << "start small BBC systematic" << endl;
	if (mode == "largeBBC") cout << "start large BBC systematic" << endl;

    
    TFile *outFile = new TFile(outName, "recreate");
    TH1I *h1_fill_index = new TH1I("h1_fill_index","fill index",59,0,59);
    TH1I *h1_event_type = new TH1I("h1_event_type","event type",4,0,4);
    TH1I *h1_event_type_withoutEMjet = new TH1I("h1_event_type_withoutEMjet","event type",4,0,4);
    TH1I *h1_event_type_withoutEMjet_zerobias = new TH1I("h1_event_type_withoutEMjet_zerobias","event type",4,0,4);
    TH1I *h1_event_final = new TH1I("h1_event_final","event type",4,0,4);
    TH1D *h1nJets_all = new TH1D("h1nJets_all", "Number of Jets from All [TPC/BEMC + EEMC + FMS]", 10, 0, 10);
    TH1D *h1nJets  = new TH1D("h1nJets ", "Number of  Jets [FMS or EEMC]", 10, 0, 10);
    TH1D *h1spinB = new TH1D("h1spinB", "Blue beam spin; Blue beam spin", 5, -2, 2);
    TH1D *h1spinY = new TH1D("h1spinY", "Yellow beam spin; Yellow beam spin", 5, -2, 2);
    TH1D *h1UnixTime = new TH1D("h1UnixTime", "Event Unix Time; Event Unix Time", 1000000, 1426e6, 1427e6);
    TH1D *h1TrigType = new TH1D("h1TrigType", "Trigger Type; Trigger Type", 10, 0, 10);
    TH1D *h1TrigType_ori = new TH1D("h1TrigType_ori", "Trigger Type (no cuts); Trigger Type", 10, 0, 10);
    TH1D *polBlue_Allfill = new TH1D("polBlue_Allfill","blue beam polarization distribution (all fill)",90,0.4,0.7);
    TH1D *polYellow_Allfill = new TH1D("polYellow_Allfill","yellow beam polarization distribution (all fill)",90,0.4,0.7);
   
    TH1D *h1_pol_uncertainty = new TH1D("h1_pol_uncertainty","pol fill uncertainty by fill index",59,0,59);

    TH1D *h1TowerEta = new TH1D("h1TowerEta", "Tower Eta", 100, 1.0, 4.5);
    TH1D *h1TowerPhi = new TH1D("h1TowerPhi", "Tower Phi", 100, -3.2, 3.2);
    TH1D *h1TowerE = new TH1D("h1TowerE", "Tower E", 100, 0, 100);

    TH1D *h1Eta = new TH1D ("h1Eta", "EM Jet Eta; Jet #eta", 100, 0.5, 5.0);
    TH1D *h1Phi = new TH1D ("h1Phi", "EM Jet Phi; Jet #phi [rad]", 100, -3.3, 3.3);
    TH1D *h1E = new TH1D ("h1E", "EM Jet E; Jet E [GeV]", 100, 0.0, 70.0);
    TH1D *h1E_corr = new TH1D ("h1E_corr", "EM Jet E with corrected from MC; EM Jet E [GeV]", 100, 0.0, 70.0);
    TH1D *h1dUE_corr = new TH1D ("h1dUE_corr", "EM Jet dUE; EM Jet dUE [GeV]", 100, 0.0, 20.0);
    TH1D *h1UE_corr = new TH1D ("h1UE_corr", "EM Jet E with corrected from UE; EM Jet E [GeV]", 100, 0.0, 70.0);
    TH1D *h1JetE_s = new TH1D ("h1JetE_s", "EM Jet E [small cells]; Jet E [GeV]", 100, 0.0, 85.0);
    TH1D *h1JetE_l = new TH1D ("h1JetE_l", "EM Jet E [large cells]; EM Jet E [GeV]", 100, 0.0, 70.0);    
    TH1D *h1Pt = new TH1D ("h1Pt", "EM Jet Pt; EM Jet Pt [GeV/c]", 100, 0.0, 10.0);
    TH1D *h1Pt_nocut = new TH1D ("h1Pt_nocut", "Jet Pt (no cut); Jet Pt [GeV/c]", 100, 0.0, 10.0);
    TH1I *h1nPhotons = new TH1I("h1nPhotons", "number of photons in EM jets; Number of Photons", 20, 0, 20);
    TH1D *h1vtxZ = new TH1D("h1vtxZ", "Jet vetrex z; Jet vertex z [cm]", 100, -200, 200);
    TH1D *h1_ZDCE = new TH1D("h1_ZDCE","ZDC East after cuts;ZDC East",100,0.,100.);
    TH1D *h1_ZDCE_final = new TH1D("h1_ZDCE_final","ZDC East after cuts;ZDC East",100,0.,100.);
    TH1D *h1_TOFmult_final = new TH1D("h1_TOFmult_final","TOF mult after cuts;TOF mult",100,0.,100.);
    TH1D *h1_TOFetaMin_final = new TH1D("h1_TOFetaMin_final","min TOF hit #eta after cuts;#eta",40,-1.,1.);
    TH1D *h1_smallBBCsumEast = new TH1D("h1_smallBBCsumEast","small BBC ADC sum for east side BBC",400,0,2000);
    TH1D *h1_largeBBCsumEast = new TH1D("h1_largeBBCsumEast","large BBC ADC sum for east side BBC",400,0,2000);
    TH1D *h1_smallBBCsumWest = new TH1D("h1_smallBBCsumWest","small BBC ADC sum for west side BBC",400,0,2000);
    TH1D *h1_largeBBCsumWest = new TH1D("h1_largeBBCsumWest","large BBC ADC sum for west side BBC",400,0,2000);
    TH2D *h2_sumEwest_vs_smallBBCsumWest = new TH2D("h2_sumEwest_vs_smallBBCsumWest","sum west side energy vs small BBC ADC sum for west side BBC;small BBC sum;energy[GeV]",200,0,1000,80,60,140);
    TH2D *h2_sumEwest_vs_largeBBCsumWest = new TH2D("h2_sumEwest_vs_largeBBCsumWest","sum west side energy vs large BBC ADC sum for west side BBC;large BBC sum;energy[GeV]",200,0,1000,80,60,140);
    TH2D *h2_sumEwest_vs_smallBBCsumWest_withjets = new TH2D("h2_sumEwest_vs_smallBBCsumWest_withjets","sum west side energy vs small BBC ADC sum for west side BBC (only events with EM-jets);small BBC sum;energy[GeV]",200,0,1000,80,60,140);
    TH2D *h2_sumEwest_vs_largeBBCsumWest_withjets = new TH2D("h2_sumEwest_vs_largeBBCsumWest_withjets","sum west side energy vs large BBC ADC sum for west side BBC (only events with EM-jets);large BBC sum;energy[GeV]",200,0,1000,80,60,140);
    TH2D *h2_sumEwest_vs_smallBBCsumEast = new TH2D("h2_sumEwest_vs_smallBBCsumEast","sum west side energy vs small BBC ADC sum for east side BBC;small BBC sum;energy[GeV]",200,0,1000,80,60,140);
    TH2D *h2_sumEwest_vs_largeBBCsumEast = new TH2D("h2_sumEwest_vs_largeBBCsumEast","sum west side energy vs large BBC ADC sum for east side BBC;large BBC sum;energy[GeV]",200,0,1000,80,60,140);
    TH2D *h2_RPtrkEwest_vs_smallBBCsumWest = new TH2D("h2_RptrkEwest_vs_smallBBCsumWest","west side RP track energy vs small BBC ADC sum for west side BBC;small BBC sum;energy[GeV]",200,0,1000,80,50,130);
    TH2D *h2_RPtrkEwest_vs_largeBBCsumWest = new TH2D("h2_RptrkEwest_vs_largeBBCsumWest","west side RP track energy vs large BBC ADC sum for west side BBC;large BBC sum;energy[GeV]",200,0,1000,80,50,130);
    TH2D *h2_RPtrkEeast_vs_smallBBCsumEast = new TH2D("h2_RptrkEeast_vs_smallBBCsumEast","east side RP track energy vs small BBC ADC sum for east side BBC;small BBC sum;energy[GeV]",200,0,1000,80,50,130);
    TH2D *h2_RPtrkEeast_vs_largeBBCsumEast = new TH2D("h2_RptrkEeast_vs_largeBBCsumEast","east side RP track energy vs large BBC ADC sum for east side BBC;large BBC sum;energy[GeV]",200,0,1000,80,50,130);
    TH2D *h2_RPtrkXieast_vs_RPtrkPteast = new TH2D("h2_RPtrkXieast_vs_RPtrkPteast","East RP #xi vs East RP p_{T}; p_{T} [GeV/c]; #xi",60,0.,3.,30,0.,0.15);

    TH1I *h1_nRpTracks = new TH1I("h1_nRpTracks", "Number of RP tracks", 20, 0, 20);     
    TH1D *h1_wRpPt = new TH1D("h1_trkPtWest", "West RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 20);
    TH1D *h1_eRpPt = new TH1D("h1_trkPtEast", "East RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 20);    
    TH1D *h1_wRpP = new TH1D("h1_trkPWest", "West RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1D *h1_eRpP = new TH1D("h1_trkPEast", "East RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1D *h1_eRpP_aftercut = new TH1D("h1_eRpP_aftercut", "East RP trk P (after cuts); RP track P [GeV/c]", 110, 0, 110);
    TH1D *h1_totalRpP = new TH1D("h1_totalRpP", "total RP trk P;P [GeV/c]", 250, 0, 250);
    TH1D *h1_EastRpP = new TH1D("h1_EastRpP", "East RP trk P;P [GeV/c]", 60, 60, 120);
    TH1D *h1_WestRpP = new TH1D("h1_WestRpP", "West RP trk P;P [GeV/c]", 80, 40, 120);
    TH1D *h1_EastRpP_doublediff = new TH1D("h1_EastRpP_doublediff", "East RP trk P for double diffractive process;P [GeV/c]", 60, 60, 120);
    TH1D *h1_WestRpP_doublediff = new TH1D("h1_WestRpP_doublediff", "West RP trk P for double diffractive process;P [GeV/c]", 80, 40, 120);
    TH1D *h1_WestRpP_singlediff = new TH1D("h1_WestRpP_singlediff", "West RP trk P for single diffractive process;P [GeV/c]", 80, 40, 120);

    TH1D *h1_EastWestRP_Pdiff = new TH1D("h1_EastWestRP_Pdiff", "|P_{West RP track} - P_{East RP track}| ; #Delta P", 80, 0,10); 
    TH1D *h1_EastWestRP_Pxdiff = new TH1D("h1_EastWestRP_Pxdiff", "|Px_{West RP track} - Px_{East RP track}| ; #Delta Px", 80, 0,1); 
    TH1D *h1_EastWestRP_Pydiff = new TH1D("h1_EastWestRP_Pydiff", "|Py_{West RP track} - Py_{East RP track}| ; #Delta Py", 80, 0,1); 
    TH1D *h1_EastWestRP_Pzdiff = new TH1D("h1_EastWestRP_Pzdiff", "|Pz_{West RP track} - Pz_{East RP track}| ; #Delta Pz", 80, 0,5); 
    TH1D *h1_EastRpP_elastic = new TH1D("h1_EastRpP_elastic", "East RP trk P for elastic scattering process;P [GeV/c]", 60, 60, 120);
    TH1D *h1_WestRpP_elastic = new TH1D("h1_WestRpP_elastic", "West RP trk P for elastic scattering process;P [GeV/c]", 60, 60, 120);

    TH1I *h1_RpNPlanes = new TH1I("h1_RpNPlanes","Number of RP planes;N Planes",9,0,9);
    TH1I *h1_RpNPlanes_East = new TH1I("h1_RpNPlanes_East","Number of RP planes in East side;N Planes East",9,0,9);
    TH1I *h1_RpNPlanes_West = new TH1I("h1_RpNPlanes_West","Number of RP planes in West side;N Planes West",9,0,9);
    TH1D *h1_sumEwest = new TH1D("h1_sumEwest","sum of west side RP track energy and EM Jet energy;sum E [GeV]",120,60,180);
    TH1D *h1_sumEwest_XF1015 = new TH1D("h1_sumEwest_XF1015","sum of west side RP track energy and EM Jet energy (0.1 < x_{F} < 0.15) );sum E [GeV]",120,60,180);
    TH1D *h1_sumEwest_XF1520 = new TH1D("h1_sumEwest_XF1520","sum of west side RP track energy and EM Jet energy (0.15 < x_{F} < 0.2 ) );sum E [GeV]",120,60,180);
    TH1D *h1_sumEwest_XF2025 = new TH1D("h1_sumEwest_XF2025","sum of west side RP track energy and EM Jet energy (0.2 < x_{F} < 0.25) );sum E [GeV]",120,60,180);
    TH1D *h1_sumEwest_XF2530 = new TH1D("h1_sumEwest_XF2530","sum of west side RP track energy and EM Jet energy (0.25 < x_{F} < 0.3 ) );sum E [GeV]",120,60,180);
    TH1D *h1_sumEwest_XF30 = new TH1D("h1_sumEwest_XF30","sum of west side RP track energy and EM Jet energy (x_{F} > 0.3 ) );sum E [GeV]",120,60,180);
    TH1D *h1_pT_XF1015 = new TH1D("h1_pT_XF1015","p_{T} for EM jets 0.1 < x_{F} < 0.15 ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1D *h1_pT_XF1520 = new TH1D("h1_pT_XF1520","p_{T} for EM jets 0.15< x_{F} < 0.2  ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1D *h1_pT_XF2025 = new TH1D("h1_pT_XF2025","p_{T} for EM jets 0.2 < x_{F} < 0.25 ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1D *h1_pT_XF2530 = new TH1D("h1_pT_XF2530","p_{T} for EM jets 0.25< x_{F} < 0.3  ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1D *h1_pT_XF3035 = new TH1D("h1_pT_XF3035","p_{T} for EM jets 0.3 < x_{F} < 0.35 ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1D *h1_pT_XF3540 = new TH1D("h1_pT_XF3540","p_{T} for EM jets 0.35< x_{F} < 0.4  ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1D *h1_pT_XF4045 = new TH1D("h1_pT_XF4045","p_{T} for EM jets 0.4 < x_{F} < 0.45 ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1D *h1_pT_XF30 = new TH1D("h1_pT_XF30","p_{T} for EM jets 0.3 < x_{F} < 0.45 ;p_{T} [GeV/c]",50,1.0,6.0);
    TH1I *h1_nPhoton_XF1015 = new TH1I("h1_nPhoton_XF1015","Photon multiplicity for EM jets 0.1 < x_{F} < 0.15 ;Photon multiplicity",5,1.0,6.0);
    TH1I *h1_nPhoton_XF1520 = new TH1I("h1_nPhoton_XF1520","Photon multiplicity for EM jets 0.15< x_{F} < 0.2  ;Photon multiplicity",5,1.0,6.0);
    TH1I *h1_nPhoton_XF2025 = new TH1I("h1_nPhoton_XF2025","Photon multiplicity for EM jets 0.2 < x_{F} < 0.25 ;Photon multiplicity",5,1.0,6.0);
    TH1I *h1_nPhoton_XF2530 = new TH1I("h1_nPhoton_XF2530","Photon multiplicity for EM jets 0.25< x_{F} < 0.3  ;Photon multiplicity",5,1.0,6.0);
    TH1I *h1_nPhoton_XF3035 = new TH1I("h1_nPhoton_XF3035","Photon multiplicity for EM jets 0.3 < x_{F} < 0.35 ;Photon multiplicity",5,1.0,6.0);
    TH1I *h1_nPhoton_XF3540 = new TH1I("h1_nPhoton_XF3540","Photon multiplicity for EM jets 0.35< x_{F} < 0.4  ;Photon multiplicity",5,1.0,6.0);
    TH1I *h1_nPhoton_XF4045 = new TH1I("h1_nPhoton_XF4045","Photon multiplicity for EM jets 0.4 < x_{F} < 0.45 ;Photon multiplicity",5,1.0,6.0);
    TH1I *h1_nPhoton_XF30 = new TH1I("h1_nPhoton_XF30","Photon multiplicity for EM jets 0.3 < x_{F} < 0.45 ;Photon multiplicity",5,1.0,6.0);
    TH1D *h1_sumEwest_beforeBBCcut = new TH1D("h1_sumEwest_beforeBBCcut","sum of west side RP track energy and EM Jet energy before BBC cut;sum E [GeV]",80,60,140);

    TH1D *h1_eRPXi_xF1020 = new TH1D("h1_eRPXi_xF1020", " East RP track #xi distribution for EM jets 0.10 < x_{F} < 0.20 ; #xi",100,0.0,0.5);
    TH1D *h1_eRPXi_xF2025 = new TH1D("h1_eRPXi_xF2025", " East RP track #xi distribution for EM jets 0.20 < x_{F} < 0.25 ; #xi",100,0.0,0.5);
    TH1D *h1_eRPXi_xF2530 = new TH1D("h1_eRPXi_xF2530", " East RP track #xi distribution for EM jets 0.25 < x_{F} < 0.30 ; #xi",100,0.0,0.5);
    TH1D *h1_eRPXi_xF3035 = new TH1D("h1_eRPXi_xF3035", " East RP track #xi distribution for EM jets 0.30 < x_{F} < 0.35 ; #xi",100,0.0,0.5);
    TH1D *h1_eRPXi_xF3540 = new TH1D("h1_eRPXi_xF3540", " East RP track #xi distribution for EM jets 0.35 < x_{F} < 0.40 ; #xi",100,0.0,0.5);
    TH1D *h1_eRPXi_xF4045 = new TH1D("h1_eRPXi_xF4045", " East RP track #xi distribution for EM jets 0.40 < x_{F} < 0.45 ; #xi",100,0.0,0.5);
    TH1D *h1_eRPXi_final = new TH1D("h1_eRPXi_final", " East RP track #xi distribution for events finally taken into AN calc ; #xi",30,0.0,0.3);


    TH1D *h1_nPhoton_count_only1westRP = new TH1D("h1_nPhoton_count_only1westRP","number of photon by only 1 west RP track",5,1.0,6.0);
    TH1D *h1_nPhoton_count_1east1westRP = new TH1D("h1_nPhoton_count_1east1westRP","number of photon by 1 east and 1 west RP track",5,1.0,6.0);
    TH1D *h1_xF_count_only1westRP = new TH1D("h1_xF_count_only1westRP","xF distribution by only 1 west RP track",5,0.1,0.35);
    TH1D *h1_xF_count_1east1westRP = new TH1D("h1_xF_count_1east1westRP","xF distribution by 1 east and 1 west RP track",5,0.1,0.35);
    TH1D *h1_pT_count_only1westRP = new TH1D("h1_pT_count_only1westRP","pT distribution by only 1 west RP track",5,1.0,3.5);
    TH1D *h1_pT_count_1east1westRP = new TH1D("h1_pT_count_1east1westRP","pT distribution by 1 east and 1 west RP track",5,1.0,3.5);
    TH1D *h1_xF_final = new TH1D("h1_xF_final","xF distribution final",7,0.1,0.45);
	

    TH1D *h1_xF_1015 = new TH1D("h1_xF_1015","x_{F} distribution in [0.1,0.15];x_{F}",50,0.1,0.15);
    TH1D *h1_xF_1520 = new TH1D("h1_xF_1520","x_{F} distribution in [0.15,0.2];x_{F}",50,0.15,0.2);
    TH1D *h1_xF_1020 = new TH1D("h1_xF_1020","x_{F} distribution in [0.1,0.2 ];x_{F}",50,0.1,0.20);
    TH1D *h1_xF_2025 = new TH1D("h1_xF_2025","x_{F} distribution in [0.2,0.25];x_{F}",50,0.2,0.25);
    TH1D *h1_xF_2530 = new TH1D("h1_xF_2530","x_{F} distribution in [0.25,0.3];x_{F}",50,0.25,0.3);
    TH1D *h1_xF_3035 = new TH1D("h1_xF_3035","x_{F} distribution in [0.3,0.35];x_{F}",50,0.3,0.35);
    TH1D *h1_xF_3540 = new TH1D("h1_xF_3540","x_{F} distribution in [0.35,0.4];x_{F}",50,0.35,0.4);
    TH1D *h1_xF_4045 = new TH1D("h1_xF_4045","x_{F} distribution in [0.4,0.45];x_{F}",50,0.4,0.45);
    TH1D *h1_xF_3045 = new TH1D("h1_xF_3045","x_{F} distribution in [0.3,0.45];x_{F}",150,0.3,0.45);

    TH1D *h1_xF_1015_Ecorr = new TH1D("h1_xF_1015_Ecorr","x_{F} distribution in [0.1,0.15] (energy correction systematic study);x_{F}",50,0.1,0.15);
    TH1D *h1_xF_1520_Ecorr = new TH1D("h1_xF_1520_Ecorr","x_{F} distribution in [0.15,0.2] (energy correction systematic study);x_{F}",50,0.15,0.2);
    TH1D *h1_xF_1020_Ecorr = new TH1D("h1_xF_1020_Ecorr","x_{F} distribution in [0.1,0.2 ] (energy correction systematic study);x_{F}",50,0.1,0.20);
    TH1D *h1_xF_2025_Ecorr = new TH1D("h1_xF_2025_Ecorr","x_{F} distribution in [0.2,0.25] (energy correction systematic study);x_{F}",50,0.2,0.25);
    TH1D *h1_xF_2530_Ecorr = new TH1D("h1_xF_2530_Ecorr","x_{F} distribution in [0.25,0.3] (energy correction systematic study);x_{F}",50,0.25,0.3);
    TH1D *h1_xF_3035_Ecorr = new TH1D("h1_xF_3035_Ecorr","x_{F} distribution in [0.3,0.45] (energy correction systematic study);x_{F}",50,0.3,0.35);
    TH1D *h1_xF_3540_Ecorr = new TH1D("h1_xF_3540_Ecorr","x_{F} distribution in [0.35,0.4] (energy correction systematic study);x_{F}",50,0.35,0.4);
    TH1D *h1_xF_4045_Ecorr = new TH1D("h1_xF_4045_Ecorr","x_{F} distribution in [0.4,0.45] (energy correction systematic study);x_{F}",50,0.4,0.45);
    TH1D *h1_xF_3045_Ecorr = new TH1D("h1_xF_3045_Ecorr","x_{F} distribution in [0.3,0.45] (energy correction systematic study);x_{F}",150,0.3,0.45);

    TH1D *h1_xF_1020_12np = new TH1D("h1_xF_1020_12np","x_{F} distribution in [0.1,0.2 ] (photon multiplicity =1 or 2);x_{F}",50,0.1,0.20);
    TH1D *h1_xF_2025_12np = new TH1D("h1_xF_2025_12np","x_{F} distribution in [0.2,0.25] (photon multiplicity =1 or 2);x_{F}",50,0.2,0.25);
    TH1D *h1_xF_2530_12np = new TH1D("h1_xF_2530_12np","x_{F} distribution in [0.25,0.3] (photon multiplicity =1 or 2);x_{F}",50,0.25,0.3);
    TH1D *h1_xF_3035_12np = new TH1D("h1_xF_3035_12np","x_{F} distribution in [0.3,0.35] (photon multiplicity =1 or 2);x_{F}",50,0.3,0.35);
    TH1D *h1_xF_3540_12np = new TH1D("h1_xF_3540_12np","x_{F} distribution in [0.35,0.4] (photon multiplicity =1 or 2);x_{F}",50,0.35,0.4);
    TH1D *h1_xF_4045_12np = new TH1D("h1_xF_4045_12np","x_{F} distribution in [0.4,0.45] (photon multiplicity =1 or 2);x_{F}",50,0.4,0.45);

    TH1D *h1_xF_1020_3pnp = new TH1D("h1_xF_1020_3pnp","x_{F} distribution in [0.1,0.2 ] (photon multiplicity =3 or more);x_{F}",50,0.1,0.20);
    TH1D *h1_xF_2025_3pnp = new TH1D("h1_xF_2025_3pnp","x_{F} distribution in [0.2,0.25] (photon multiplicity =3 or more);x_{F}",50,0.2,0.25);
    TH1D *h1_xF_2530_3pnp = new TH1D("h1_xF_2530_3pnp","x_{F} distribution in [0.25,0.3] (photon multiplicity =3 or more);x_{F}",50,0.25,0.3);
    TH1D *h1_xF_3035_3pnp = new TH1D("h1_xF_3035_3pnp","x_{F} distribution in [0.3,0.35] (photon multiplicity =3 or more);x_{F}",50,0.3,0.35);
    TH1D *h1_xF_3540_3pnp = new TH1D("h1_xF_3540_3pnp","x_{F} distribution in [0.35,0.4] (photon multiplicity =3 or more);x_{F}",50,0.35,0.4);
    TH1D *h1_xF_4045_3pnp = new TH1D("h1_xF_4045_3pnp","x_{F} distribution in [0.4,0.45] (photon multiplicity =3 or more);x_{F}",50,0.4,0.45);

    TH1D *h1_xF_1015_noCorr = new TH1D("h1_xF_1015_noCorr","x_{F} distribution in [0.1,0.15] (no correction);x_{F}",50,0.1,0.15);
    TH1D *h1_xF_1520_noCorr = new TH1D("h1_xF_1520_noCorr","x_{F} distribution in [0.15,0.2] (no correction);x_{F}",50,0.15,0.2);
    TH1D *h1_xF_2025_noCorr = new TH1D("h1_xF_2025_noCorr","x_{F} distribution in [0.2,0.25] (no correction);x_{F}",50,0.2,0.25);
    TH1D *h1_xF_2530_noCorr = new TH1D("h1_xF_2530_noCorr","x_{F} distribution in [0.25,0.3] (no correction);x_{F}",50,0.25,0.3);
    TH1D *h1_xF_3045_noCorr = new TH1D("h1_xF_3045_noCorr","x_{F} distribution in [0.3,0.45] (no correction);x_{F}",150,0.3,0.45);

    TH1D *h1_xF_1015_SysDiff = new TH1D("h1_xF_1015_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.1,0.15] ;Difference ",50,0,0.20);
    TH1D *h1_xF_1520_SysDiff = new TH1D("h1_xF_1520_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.15,0.2] ;Difference ",50,0,0.20);
    TH1D *h1_xF_2025_SysDiff = new TH1D("h1_xF_2025_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.2,0.25] ;Difference ",50,0,0.20);
    TH1D *h1_xF_2530_SysDiff = new TH1D("h1_xF_2530_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.25,0.3] ;Difference ",50,0,0.20);
    TH1D *h1_xF_3035_SysDiff = new TH1D("h1_xF_3035_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.3,0.35] ;Difference ",50,0,0.20);
    TH1D *h1_xF_3540_SysDiff = new TH1D("h1_xF_3540_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.35,0.4] ;Difference ",50,0,0.20);
    TH1D *h1_xF_4045_SysDiff = new TH1D("h1_xF_4045_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.4,0.45] ;Difference ",50,0,0.20);
    TH1D *h1_xF_3045_SysDiff = new TH1D("h1_xF_3045_SysDiff","Systematic uncertainty for E correction x_{F} distribution in [0.3,0.45] ;Difference ",50,0,0.20);

    TH2D *h2EvsPt = new TH2D("h2EvsPt", "Eng vs Pt; Pt [GeV/C]; E [GeV]", 100, 0, 20, 100, 0, 100);
    TH2D *h2PtvsE = new TH2D("h2PtvsE", "Pt vs E; E [GeV]; Pt [GeV/c]", 100,  0, 100, 100, 0, 20);
    TH2D *h2nPhVsEng = new TH2D("h2nPhVsEng", "Number of photons vs Eng; E [Gev]; No. of Photons", 100, 0, 100, 20, 0, 20);
    TH2D *h2_EMJetE_vs_ProtonE = new TH2D("h2_EmJetE_vs_ProtonE", "EM Jet sum Energy vs West Proton Energy; West Proton Energy [GeV]; EM Jet sum Energy [GeV]", 60, 50, 110, 50, 5, 55);

    TH2D *h2PtvsXF = new TH2D("h2PtvsXF","EM-jet P_{T} vs x_{F} ; x_{F} ; P_{T} bin ",5,0.1,0.35,20,1.0,5.0);
    TH2D *h2_TOFmult_vs_TOFMinEta = new TH2D("h2_TOFmult_vs_TOFMinEta", "TOF multiplicity vs TOF min #eta; TOF min #eta ; TOF mult",20,-1.0,1.0,50,0.,50.0);

    Int_t Phibin=0;
    if (det == "fms") {Phibin=16;}
    if (det == "eemc"){Phibin=16;}
    TH1D* polFmsBlue[54];
    TH1D* polFmsYellow[54];
    TH1D* polEemcBlue[59];
    TH1D* polEemcYellow[59];
    Int_t XFbin = 20;
    TH2D *h2_BU_xF_vs_phi = new TH2D("h2_BU_xF_vs_phi","Blue beam spin +1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_BD_xF_vs_phi = new TH2D("h2_BD_xF_vs_phi","Blue beam spin -1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_YU_xF_vs_phi = new TH2D("h2_YU_xF_vs_phi","Yellow beam spin +1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_YD_xF_vs_phi = new TH2D("h2_YD_xF_vs_phi","Yellow beam spin -1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_BU_xF_vs_phi_nPhoton12 = new TH2D("h2_BU_xF_vs_phi_nPhoton12","Blue beam spin +1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_BD_xF_vs_phi_nPhoton12 = new TH2D("h2_BD_xF_vs_phi_nPhoton12","Blue beam spin -1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_YU_xF_vs_phi_nPhoton12 = new TH2D("h2_YU_xF_vs_phi_nPhoton12","Yellow beam spin +1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_YD_xF_vs_phi_nPhoton12 = new TH2D("h2_YD_xF_vs_phi_nPhoton12","Yellow beam spin -1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_BU_xF_vs_phi_nPhoton3p = new TH2D("h2_BU_xF_vs_phi_nPhoton3p","Blue beam spin +1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_BD_xF_vs_phi_nPhoton3p = new TH2D("h2_BD_xF_vs_phi_nPhoton3p","Blue beam spin -1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_YU_xF_vs_phi_nPhoton3p = new TH2D("h2_YU_xF_vs_phi_nPhoton3p","Yellow beam spin +1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);
    TH2D *h2_YD_xF_vs_phi_nPhoton3p = new TH2D("h2_YD_xF_vs_phi_nPhoton3p","Yellow beam spin -1 x_{F} vs #phi ; #phi [rad] ; x_{F}",Phibin,-TMath::Pi(),TMath::Pi(),XFbin,0,1);

    TH2D *h2_pT_vs_xF_final = new TH2D("h2_pT_vs_xF_final", "p_{T} vs x_{F} for Em-jets after all cuts; x_{F} ; p_{T} [GeV/c]",7,0.1,0.45,20,1.0,5.0);

    TH2D *h2_bbcmult_vs_sumEwest = new TH2D("h2_bbcmult_vs_sumEwest","BBC mult vs sum of west side track energy;sum energy [GeV];BBC mult",80,60,140,50,0,50);

    TF1 *f1 = new TF1("f1","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x+[6]*x*x*x*x*x*x");
    f1->SetParameter(0,8.934910e0);
    f1->SetParameter(1,-6.63987e-1);
    f1->SetParameter(2,1.51376e-1);
    f1->SetParameter(3,-6.65678e-3);
    f1->SetParameter(4,1.56144e-4);
    f1->SetParameter(5,-1.84953e-6);
    f1->SetParameter(6,8.65440e-9);

    TF1 *f2 = new TF1("f2","[0]+[1]*x");
    f2->SetParameter(0,1.12965);
    f2->SetParameter(1,1.07394);
    	TF1 *f3 = new TF1("f3","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x");
    	TF1 *f4 = new TF1("f4","[0]+[1]*x+[2]*x*x");

    	f3->SetParameter(0,1.11349e+01);
    	f3->SetParameter(1,-1.58394e-01);
    	f3->SetParameter(2,1.58873e-02);
    	f3->SetParameter(3,-6.66110e-03);
    	f3->SetParameter(4,6.85146e-05);
    	f3->SetParameter(5,7.97991e-05);
    	f4->SetParameter(0,1.75278);
    	f4->SetParameter(1,1.01717);
    	f4->SetParameter(2,1.14455e-03);


    Double_t etaMin;
    Double_t etaMax;
    Double_t detZ; //For FMS
    Double_t pTcut = 2.0;
	Double_t FMSTrigThresP1[9]={1.84,2.76,3.68,1.26,1.84,2.53,1.26,1.84,2.76};
	Double_t FMSTrigThresP2[9]={1.84,2.76,3.68,1.15,1.84,2.18,1.15,1.84,2.76};
    if(det == "fms")
    {
	etaMin = 2.8;
	etaMax = 3.8;
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
    else if (det == "zerobias") {}
    else
    {
	cout << "Invalid detector" <<endl;
	return;
    }
    
    
    Double_t jetX, jetY, eta, phi, theta, vtxZ, eng, eng_corr, eng_corr_sys, eng_corr_diff, pt,nEMjets_cut,xF , nPhotons;
    Int_t nJets = 0;
    
    cout << "Total Entries to be processed: "<< ch->GetEntries() <<endl;

    ifstream polfile,runfile;
    Double_t UnixTime,StartTime,P0B,dP0B,dPBdT,ddPBdT,P0Y,dP0Y,dPYdT,ddPYdT , dUnixTime;
    int thisFillNum, thisRunNum;
    int fillit;

    double runStartTime[1000],runEndTime[1000],nRunEvent[1000];
    for (int k=0;k<1000;k=k+1)
    {

	runStartTime[k]=9999999;
	runEndTime[k]=0;
	nRunEvent[k]=0;

    }

    Double_t thisFillEvent=0;
    Double_t ThisFillUncertainty=0;

    struct polPara
    {

	int fillNum;
	long startrun,endrun;
	double StartTime,P0B,dP0B,dPBdT,ddPBdT,P0Y,dP0Y,dPYdT,ddPYdT;

    } polFms[54], polEemc[60];

    vector<int> FillNumber;
    std::vector<int>::iterator it;

    if(det == "fms")
    {
    	polfile.open("polarization_fms.txt");
	runfile.open("run15fmsFill_run.list");
	for (int i=0; i<54; ++i)
	{

	polfile >> polFms[i].fillNum >> polFms[i].StartTime >> polFms[i].P0B >> polFms[i].dP0B >> polFms[i].dPBdT >> polFms[i].ddPBdT >> polFms[i].P0Y >> polFms[i].dP0Y >> polFms[i].dPYdT >> polFms[i].ddPYdT ;	
	runfile >> polFms[i].fillNum >> polFms[i].startrun >> polFms[i].endrun;

	FillNumber.push_back(polFms[i].fillNum);

	//cout<<"fill number: "<<FillNumber[i]<<endl;


	}
  
    }
    else if (det == "zerobias") {}
	else
    {
	cout << "Invalid detector" <<endl;
	return;
    }


    for(Int_t evt = 0; evt < ch->GetEntries(); ++evt)
    {
	ch->GetEntry(evt);

	if(evt % 1000 == 0)
	    cout << "Events Processed: "<< evt <<endl;
	
	skimEvent = jetEvent->GetEvent();
	
	h1UnixTime->Fill(skimEvent->GetUnixTime());
	h1spinB->Fill(skimEvent->GetSpinB());
	h1spinY->Fill(skimEvent->GetSpinY());
	vtxZ = skimEvent->GetVertexZ();
	h1_smallBBCsumEast->Fill(skimEvent->GetBbcSumSmall(0));
	h1_largeBBCsumEast->Fill(skimEvent->GetBbcSumLarge(0));
	h1_smallBBCsumWest->Fill(skimEvent->GetBbcSumSmall(1));
	h1_largeBBCsumWest->Fill(skimEvent->GetBbcSumLarge(1));
	if (fabs(vtxZ) > 80) continue;
		thisFillNum = skimEvent->GetFillNumber();
		thisRunNum = skimEvent->GetRunNumber();

	//cut on BBC ADC sum
	//if (skimEvent->GetBbcSumSmall(1) > 100) continue;
	//if (skimEvent->GetBbcSumLarge(1) >  60) continue;
	//if (skimEvent->GetBbcSumSmall(0) >  60) continue;
	//if (skimEvent->GetBbcSumLarge(0) >  50) continue;
	
	
	 for(Int_t t = 0; t < 9; ++t) //Moved to the end of envet loop
	 {
	     if(skimEvent->GetTrigFlag(t))
	 	h1TrigType_ori->Fill(t);
	 }

	//Exclude FMS small-bs3 trigger that gives ring of fire issue. But this removes most of high energetic jets.
	if((det == "fms") && (mode == "ROF"))
	{
	    if(skimEvent->GetTrigFlag(5))
		continue;
	}
	//Alternative way to reduce ring of fire, require: BBCMult > 2 and TofMult > 2
	
	nJets = jetEvent->GetNumberOfJets();

	//roman pot cut	
	Int_t nRpsTracks = rpsArr->GetEntriesFast();
	h1_nRpTracks->Fill(nRpsTracks);
	//if (nRpsTracks != 1) continue;
	//if ((nRpsTracks > 2)||(nRpsTracks == 0)) continue;
	int nRpsTracksEast=0;	
	int nRpsTracksWest=0;	
	Double_t totalRpP=0;
	Double_t EastRpP=0;
	Double_t EastRpPt=0;
	Double_t EastRpPx=0;
	Double_t EastRpPy=0;
	Double_t EastRpPz=0;
	Double_t EastRpThetaX=0;
	Double_t EastRpThetaY=0;
	Double_t EastRpXi;
	Double_t WestRpP=0;
	Double_t WestRpPx=0;
	Double_t WestRpPy=0;
	Double_t WestRpPz=0;
	Double_t WestRpThetaX=0;
	Double_t WestRpThetaY=0;
	Double_t WestRpXi;
	Int_t TOFmult;
	Double_t TOFMinEta;
	bool final_event_count = false;

	bool goodevent=false;
    	Double_t RpWestPpJetE=0;
	Int_t goodjets=0;
	Double_t xy2;


	for (int iRpTrk=0;iRpTrk < nRpsTracks; ++iRpTrk)
	{	
		rpsTrack = (TStRpsTrackData*)rpsArr->At(iRpTrk);

		h1_RpNPlanes->Fill(rpsTrack->GetNplanes());	
		if(rpsTrack->GetBranch() == 0 || rpsTrack->GetBranch() == 1) //East RP :: O East Up RP, 1: East Down RP
                {
			nRpsTracksEast=nRpsTracksEast+1;
			EastRpP = rpsTrack->GetP();
			EastRpPt = rpsTrack->GetPt();
			EastRpPx = rpsTrack->GetPx();
			EastRpPy = rpsTrack->GetPy();
			EastRpPz = rpsTrack->GetPz();
			EastRpThetaX = rpsTrack->GetThetaX();
			EastRpThetaY = rpsTrack->GetThetaY();
			EastRpXi = 1.0 * (100. - EastRpP) / 100.0;
			if ((EastRpXi < 0.00) || (EastRpXi > 0.15)) {continue;}
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


				//if ((EastRpXi > 0.1) && (EastRpXi < 0.2) && ((EastRpPx > -0.3) && (EastRpPx < 0.2)) && (((EastRpPy > -0.6) && (EastRpPy < -0.35)) || ((EastRpPy > 0.3) && (EastRpPy < 0.55)))) {goodeRP = true;}
				//if ((EastRpXi > 0.2) && (EastRpXi < 0.3) && ((EastRpPx > -0.3) && (EastRpPx < 0.15)) && (((EastRpPy > -0.55) && (EastRpPy < -0.35)) || ((EastRpPy > 0.3) && (EastRpPy < 0.5)))) {goodeRP = true;}
				//if ((EastRpXi > 0.3) && (EastRpXi < 0.5) && ((EastRpPx > -0.5) && (EastRpPx < 0)) && (((EastRpPy > -0.5) && (EastRpPy < -0.35)) || ((EastRpPy > 0.25) && (EastRpPy < 0.4)))) {goodeRP = true;}

			if (rpsTrack->GetNplanes()>=7) {goodevent=true;}
			//continue;
                }
		else 
		{
			if(rpsTrack->GetBranch() == 2 || rpsTrack->GetBranch() == 3) // 2:  West Up RP, 3: West Down RP
                	{
				nRpsTracksWest = nRpsTracksWest+1;
				//WestRpP = rpsTrack->GetP();
				//WestRpPx = rpsTrack->GetPx();
				//WestRpPy = rpsTrack->GetPy();
				//WestRpPz = rpsTrack->GetPz();
				//RpWestPpJetE=rpsTrack->GetP();
				//WestRpXi = 1.0 * (100. - WestRpP) / 100.0;
				//if ((fabs(rpsTrack->GetThetaY()) > 4) || (fabs(rpsTrack->GetThetaY()) < 1.5)) continue;
				//if ((WestRpXi > 0.10) && (WestRpXi < 0.15) && ((rpsTrack->GetThetaX() > 1.5) || (rpsTrack->GetThetaX() < -1.75))) continue; 
				//if ((WestRpXi > 0.15) && (WestRpXi < 0.20) && ((rpsTrack->GetThetaX() > 1.25) || (rpsTrack->GetThetaX() < -2.25))) continue; 
				//if ((WestRpXi > 0.20) && (WestRpXi < 0.25) && ((rpsTrack->GetThetaX() > 1) || (rpsTrack->GetThetaX() < -2.5))) continue; 
				//if ((WestRpXi > 0.25) && (WestRpXi < 0.3) && ((rpsTrack->GetThetaX() > 0.5) || (rpsTrack->GetThetaX() < -3))) continue; 
				//if ((WestRpXi > 0.3) && (WestRpXi < 0.5) && ((rpsTrack->GetThetaX() > -0.5) || (rpsTrack->GetThetaX() < -5))) continue; 
				//if ((WestRpXi > 0.10)&&(WestRpXi < 0.15))
				//{

				//	xy2 = sqrt(pow((WestRpPx + 0.02),2) + pow((fabs(WestRpPy) - 0.15),2));
				//	if ((xy2 > 0.14)||(fabs(WestRpPy) < 0.15)) continue;

				//}
				//if ((WestRpXi > 0.15)&&(WestRpXi < 0.20))
				//{

				//	xy2 = sqrt(pow((WestRpPx + 0.04),2) + pow((fabs(WestRpPy) - 0.15),2));
				//	if ((xy2 > 0.14)||(fabs(WestRpPy) < 0.15)) continue;

				//}
				//if ((WestRpXi > 0.20)&&(WestRpXi < 0.25))
				//{

				//	xy2 = sqrt(pow((WestRpPx + 0.06),2) + pow((fabs(WestRpPy) - 0.15),2));
				//	if ((xy2 > 0.12)||(fabs(WestRpPy) < 0.15)) continue;

				//}
				//if ((WestRpXi > 0.25)&&(WestRpXi < 0.30))
				//{

				//	xy2 = sqrt(pow((WestRpPx + 0.10),2) + pow((fabs(WestRpPy) - 0.15),2));
				//	if ((xy2 > 0.12)||(fabs(WestRpPy) < 0.15)) continue;

				//}
				//if ((WestRpXi > 0.30)&&(WestRpXi < 0.45))
				//{

				//	xy2 = sqrt(pow((WestRpPx + 0.17),2) + pow((fabs(WestRpPy) - 0.10),2));
				//	if ((xy2 > 0.12)||(fabs(WestRpPy) < 0.10)) continue;

				//}
				//if (rpsTrack->GetNplanes()>=7) {goodevent=true;}
				//continue;
                	}
			else continue;
		}	
//		if (rpsTrack->GetThetaX() < -2 || rpsTrack->GetThetaX() > 2) {goodevent=false;continue;}
//		if (fabs(rpsTrack->GetThetaY()) <  1.5 || fabs(rpsTrack->GetThetaY()) > 4.5) {goodevent=false;continue;}


	}
	//if ((nRpsTracksEast==2)||(nRpsTracksWest==2)||(!goodevent)) {continue;}
	if (process == "SD")
	{
		if ((skimEvent->GetBbcSumSmall(0) <= 90)&&(skimEvent->GetBbcSumLarge(0) <= 80)) {h1_event_type_withoutEMjet->Fill(1);}
		if ((!goodevent)) {continue;}
		if ((nRpsTracksEast!=1)) continue;

		if ((skimEvent->GetBbcSumSmall(0) <= 90)&&(skimEvent->GetBbcSumLarge(0) <= 80)) {h1_event_type_withoutEMjet->Fill(2);}
	}
	if (process == "RG")
	{
		if ((skimEvent->GetBbcSumSmall(0) <= 90)&&(skimEvent->GetBbcSumLarge(0) <= 80)) {h1_event_type_withoutEMjet->Fill(2);}
	}

	if (det == "zerobias")
	{
		h1_event_type_withoutEMjet_zerobias->Fill(1);
		if ((skimEvent->GetBbcSumSmall(0) <= 90)&&(skimEvent->GetBbcSumLarge(0) <= 80)) {h1_event_type_withoutEMjet_zerobias->Fill(2);}

		continue;
	}

	h1_totalRpP->Fill(totalRpP);
//	if ((nRpsTracksEast==1)&&((skimEvent->GetBbcSumSmall(0) > 100)||(skimEvent->GetBbcSumLarge(0) > 60))) continue;

	
	//if ((nRpsTracksEast==0)||(nRpsTracksWest==0)) continue;
	//if (fabs(WestRpP - EastRpP) > 5) continue;
	//else
	//{

	//	h1_EastRpP_elastic->Fill(EastRpP);
	//	h1_WestRpP_elastic->Fill(WestRpP);

	//}
	//if ((nRpsTracksWest==1)) continue;
	
	h1nJets_all->Fill(jetEvent->GetNumberOfJets());

	if(nJets > 0)
	{
	    for(Int_t t = 0; t < 9; ++t)
	    {
		if(skimEvent->GetTrigFlag(t))
		    h1TrigType->Fill(t);
	    }
	}
    
	if (nJets != 1) continue;

	for(Int_t j = 0; j <  jetEvent->GetNumberOfJets(); ++j)
	{
	    jet = jetEvent->GetJet(j);
	   	    
	    eta = jet->GetEta();
	    phi = jet->GetPhi();
	    nPhotons = jet->GetNumberOfTowers();
	    theta =  2 * atan( exp(-eta) );

	    if(eta < etaMin || eta > etaMax) //Conside only EEMC and FMS coverage
		continue;

	    eng = jet->GetE();
	    if (jet->GetUedPt() < 0) eng = eng + jet->GetUedPt();
	    if ((eng > 5)&&(eng < 10)) {eng_corr = f1->Eval(eng);} 
		else {if ((eng > 10)&&(eng < 60)) {eng_corr = f2->Eval(eng);} else {eng_corr = eng;}}
	    //cout<<"original EM jet E:"<<eng<<"	corrected EM jet E:"<<eng_corr<<endl;
	    pt = jet->GetPt();
	    //RpWestPpJetE=RpWestPpJetE+eng_corr;
	    
	    if(j == 0)
		h1vtxZ->Fill(vtxZ);
	   

	    //if (eng < 2) continue;
	    //if (pt < 2) continue; 
	 
   
	    h2EvsPt->Fill(pt, eng_corr);
	    h2PtvsE->Fill(eng_corr, pt);
	    h2nPhVsEng->Fill(eng, jet->GetNumberOfTowers());

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
	    
	    for(Int_t k = 0; k < jet->GetNumberOfTowers(); ++k)
	    {
		tower = jet->GetTower(k);
	
		h1TowerEta->Fill(tower->GetEta());
		h1TowerPhi->Fill(tower->GetPhi());
		h1TowerE->Fill(tower->GetEnergy());
	    }
		++goodjets;
	}

	//if (nRpsTracksWest==1) {h1_sumEwest_beforeBBCcut->Fill(RpWestPpJetE);}
	//h2_sumEwest_vs_smallBBCsumWest->Fill(skimEvent->GetBbcSumSmall(1),RpWestPpJetE);
	//h2_sumEwest_vs_largeBBCsumWest->Fill(skimEvent->GetBbcSumLarge(1),RpWestPpJetE);
	//h2_sumEwest_vs_smallBBCsumEast->Fill(skimEvent->GetBbcSumSmall(0),RpWestPpJetE);
	//h2_sumEwest_vs_largeBBCsumEast->Fill(skimEvent->GetBbcSumLarge(0),RpWestPpJetE);

	//if ((nRpsTracksWest==1) && (nRpsTracksEast==1) && (RpWestPpJetE > 108)) 
	//{
	//	h1_EastWestRP_Pdiff->Fill(fabs(WestRpP - EastRpP));
	//	h1_EastWestRP_Pxdiff->Fill(fabs(fabs(WestRpPx) - fabs(EastRpPx)));
	//	h1_EastWestRP_Pydiff->Fill(fabs(fabs(WestRpPy) - fabs(EastRpPy)));
	//	h1_EastWestRP_Pzdiff->Fill(fabs(WestRpPz - fabs(EastRpPz)));
	//
	//}
	if (goodjets == 0) {continue;}
	//h2_sumEwest_vs_smallBBCsumWest_withjets->Fill(skimEvent->GetBbcSumSmall(1),RpWestPpJetE);

	if (nRpsTracksWest==1) {h2_RPtrkEwest_vs_smallBBCsumWest->Fill(skimEvent->GetBbcSumSmall(1),WestRpP);h2_RPtrkEwest_vs_largeBBCsumWest->Fill(skimEvent->GetBbcSumLarge(1),WestRpP);}
	if (nRpsTracksEast==1) {h2_RPtrkEeast_vs_smallBBCsumEast->Fill(skimEvent->GetBbcSumSmall(0),EastRpP);h2_RPtrkEeast_vs_largeBBCsumEast->Fill(skimEvent->GetBbcSumLarge(0),EastRpP);}
	//if ((det=="fms")&&(mode!="largeBBC")&&(mode!="smallBBC")) {if ((nRpsTracksWest==1)&&((skimEvent->GetBbcSumSmall(1) > 100))) {continue;}}
	//if ((det=="fms")&&(mode!="largeBBC")&&(mode!="smallBBC")) {if ((nRpsTracksWest==1)&&((skimEvent->GetBbcSumSmall(1) > 90))) {continue;}}
	//h2_sumEwest_vs_largeBBCsumWest_withjets->Fill(skimEvent->GetBbcSumLarge(1),RpWestPpJetE);
	//if ((det=="fms")&&(mode=="largeBBC")) {if ((nRpsTracksWest==1)&&((skimEvent->GetBbcSumLarge(1) > 63))) {continue;}}
	//if ((det=="fms")&&(mode!="largeBBC")&&(mode!="smallBBC")) {if ((nRpsTracksWest==1)&&((skimEvent->GetBbcSumSmall(1) > 100)||(skimEvent->GetBbcSumLarge(1) > 60))) {continue;}}
	//if ((det=="fms")&&(mode=="smallBBC")) {if ((nRpsTracksWest==1)&&((skimEvent->GetBbcSumSmall(1) > 103)||(skimEvent->GetBbcSumLarge(1) > 60))) {continue;}}
	if ((det=="fms")&&((mode=="AN")||(mode=="ROF")||(mode=="Ecorr"))) {if (((skimEvent->GetBbcSumSmall(0) > 90)||(skimEvent->GetBbcSumLarge(0) > 80))) {continue;}}
	//if ((det=="fms")&&(mode!="largeBBC")&&(mode!="smallBBC")) {if (((skimEvent->GetBbcSumSmall(1) > 70)||(skimEvent->GetBbcSumLarge(1) > 20))) {continue;}}
	//if ((det=="fms")&&(mode!="largeBBC")&&(mode!="smallBBC")) {if ((nRpsTracksWest==1)&&((skimEvent->GetBbcSumSmall(1) > 80)||(skimEvent->GetBbcSumLarge(1) > 60))) {continue;}}
	if ((det=="fms")&&(mode=="smallBBCm20")) {if (((skimEvent->GetBbcSumSmall(0) > 70)||(skimEvent->GetBbcSumLarge(0) > 80))) {continue;}}
	if ((det=="fms")&&(mode=="smallBBCm10")) {if (((skimEvent->GetBbcSumSmall(0) > 80)||(skimEvent->GetBbcSumLarge(0) > 80))) {continue;}}
	if ((det=="fms")&&(mode=="smallBBCp10")) {if (((skimEvent->GetBbcSumSmall(0) >100)||(skimEvent->GetBbcSumLarge(0) > 80))) {continue;}}
	if ((det=="fms")&&(mode=="smallBBCp20")) {if (((skimEvent->GetBbcSumSmall(0) >110)||(skimEvent->GetBbcSumLarge(0) > 80))) {continue;}}

	if ((det=="fms")&&(mode=="largeBBCm20")) {if (((skimEvent->GetBbcSumSmall(0) > 90)||(skimEvent->GetBbcSumLarge(0) > 60))) {continue;}}
	if ((det=="fms")&&(mode=="largeBBCm10")) {if (((skimEvent->GetBbcSumSmall(0) > 90)||(skimEvent->GetBbcSumLarge(0) > 70))) {continue;}}
	if ((det=="fms")&&(mode=="largeBBCp10")) {if (((skimEvent->GetBbcSumSmall(0) > 90)||(skimEvent->GetBbcSumLarge(0) > 90))) {continue;}}
	if ((det=="fms")&&(mode=="largeBBCp20")) {if (((skimEvent->GetBbcSumSmall(0) > 90)||(skimEvent->GetBbcSumLarge(0) >100))) {continue;}}
	//if (nRpsTracksWest==1) {h1_sumEwest->Fill(RpWestPpJetE);h2_EMJetE_vs_ProtonE->Fill(WestRpP, (RpWestPpJetE - WestRpP));}

	//if ((RpWestPpJetE < 102)||(nRpsTracksWest==0))
	//if ((RpWestPpJetE < 108)&&(nRpsTracksWest==1))
	//if ((RpWestPpJetE > 140)&&(RpWestPpJetE < 150)&&(nRpsTracksWest==1))

		if ((nRpsTracksEast == 0) && (nRpsTracksWest == 1)) h1_event_type->Fill(2);
		if ((nRpsTracksEast == 1) && (nRpsTracksWest == 1)) h1_event_type->Fill(3);

		//cout<<"fill number"<<skimEvent->GetFillNumber()<<endl;
		it = std::find (FillNumber.begin(), FillNumber.end(), thisFillNum);
		fillit = it - FillNumber.begin();
	  UnixTime=skimEvent->GetUnixTime();
	  h1_fill_index->Fill(fillit);
	  if (det == "fms")
	  {
	  	Double_t polBlue = polFms[fillit].P0B + (UnixTime - polFms[fillit].StartTime) /3600. * polFms[fillit].dPBdT; 
	  	Double_t polYellow = polFms[fillit].P0Y + (UnixTime - polFms[fillit].StartTime) /3600. * polFms[fillit].dPYdT;
	  	dUnixTime = (UnixTime - polFms[fillit].StartTime);
		thisRunNum = thisRunNum - polFms[fillit].startrun;
		//cout << "this run num diff:"<<thisRunNum<<"	d Unix Time:"<<dUnixTime<<endl;
		if (dUnixTime > runEndTime[thisRunNum]) {runEndTime[thisRunNum] = dUnixTime;}
		if (dUnixTime < runStartTime[thisRunNum]) {runStartTime[thisRunNum] = dUnixTime;}
		nRunEvent[thisRunNum]=nRunEvent[thisRunNum] +1;		

	  	//cout<<"Blue beam pol:"<<polBlue<<endl;
	  	polBlue_Allfill->Fill(polBlue/100.);
	  	polYellow_Allfill->Fill(polYellow/100.);

	  }

	  thisFillEvent=thisFillEvent+1;
//
//	  if (det == "eemc")
//	  {
//	  	Double_t polBlue = polEemc[fillit].P0B + (UnixTime - polEemc[fillit].StartTime) /3600. * polEemc[fillit].dPBdT; 
//	  	Double_t polYellow = polEemc[fillit].P0Y + (UnixTime - polEemc[fillit].StartTime) /3600. * polEemc[fillit].dPYdT;
//	  	polBlue_Allfill->Fill(polBlue/100.);
//	  	polYellow_Allfill->Fill(polYellow/100.);
//		//ThisFillUncertainty = ThisFillUncertainty + pow((polEemc[fillit].ddPBdT*(UnixTime - polEemc[fillit].StartTime)/3600.),2);
//	  }
	  

	  for(Int_t j = 0; j <  jetEvent->GetNumberOfJets(); ++j)
	  {


	    jet = jetEvent->GetJet(j);
	    eta = jet->GetEta();
	    phi = jet->GetPhi();
	    if(eta < etaMin || eta > etaMax) //Conside only EEMC and FMS coverage
		continue;
	    eng = jet->GetE();
	    xF = 0;
 	    if (det == "fms") {xF = eng / 100.;}
	    if (det == "eemc") {xF = eng * tanh(eta) / 100.;}


	    if ((xF > 0.1)&& (xF < 0.15)) {h1_xF_1015_noCorr->Fill(xF);}
	    if ((xF > 0.15)&& (xF < 0.2)) {h1_xF_1520_noCorr->Fill(xF);}
	    if ((xF > 0.2)&& (xF < 0.25)) {h1_xF_2025_noCorr->Fill(xF);}
	    if ((xF > 0.25)&& (xF < 0.3)) {h1_xF_2530_noCorr->Fill(xF);}
	    if ((xF > 0.3)&&(xF < 0.45)) {h1_xF_3045_noCorr->Fill(xF);}
	    if (jet->GetUedPt() < 0) eng = eng + jet->GetUedPt();
	    h1E->Fill(eng);
	    if ((eng > 5)&&(eng < 10)) {eng_corr = f1->Eval(eng);} 
		else {if ((eng > 10)&&(eng < 60)) {eng_corr = f2->Eval(eng);} else {eng_corr = eng;}}
		//eng_corr = f1->Eval(eng);
	    h1E_corr->Fill(eng_corr);
	    pt = jet->GetPt();
	    h1Eta->Fill(eta);
	    h1Phi->Fill(phi);
	    h1Pt->Fill(pt);
	    h1nPhotons->Fill(jet->GetNumberOfTowers());
	    //if (eng > 50) continue;
 	    //if (det == "fms") {xF = eng / 100.;}
	    //if (det == "eemc") {xF = eng * tanh(eta) / 100.;}
	    xF = 0;
 	    if (det == "fms") {xF = eng_corr / 100.;}
	    if (det == "eemc") {xF = eng_corr * tanh(eta) / 100.;}

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


	    if ((xF > 0.1)&& (xF < 0.15)) {h1_xF_1015->Fill(xF);}
	    if ((xF > 0.15)&& (xF < 0.2)) {h1_xF_1520->Fill(xF);}
	    if ((xF > 0.1)&& (xF < 0.2)) {h1_xF_1020->Fill(xF);}
	    if ((xF > 0.2)&& (xF < 0.25)) {h1_xF_2025->Fill(xF);}
	    if ((xF > 0.25)&& (xF < 0.3)) {h1_xF_2530->Fill(xF);}
	    if ((xF > 0.3)&& (xF < 0.35)) {h1_xF_3035->Fill(xF);}
	    if ((xF > 0.35)&& (xF < 0.45)) {h1_xF_3540->Fill(xF);}
	    if ((xF > 0.4)&& (xF < 0.45)) {h1_xF_4045->Fill(xF);}
	    //if ((xF > 0.3)&&(xF < 0.45)) {h1_xF_3045->Fill(xF); xF = 0.32;}
	    if (xF > 0.45) {continue;}
	    if (nPhotons <= 2)
	    {
	    	if ((xF > 0.1)&& (xF < 0.2) ) {h1_xF_1020_12np->Fill(xF);}
	    	if ((xF > 0.2)&& (xF < 0.25)) {h1_xF_2025_12np->Fill(xF);}
	    	if ((xF > 0.25)&& (xF < 0.3)) {h1_xF_2530_12np->Fill(xF);}
	    	if ((xF > 0.3)&& (xF < 0.35)) {h1_xF_3035_12np->Fill(xF);}
	    	if ((xF > 0.35)&& (xF < 0.4)) {h1_xF_3540_12np->Fill(xF);}
	    	if ((xF > 0.4)&& (xF < 0.45)) {h1_xF_4045_12np->Fill(xF);}

	    }
	    if (nPhotons >= 3)
	    {
	    	if ((xF > 0.1)&& (xF < 0.2) ) {h1_xF_1020_3pnp->Fill(xF);}
	    	if ((xF > 0.2)&& (xF < 0.25)) {h1_xF_2025_3pnp->Fill(xF);}
	    	if ((xF > 0.25)&& (xF < 0.3)) {h1_xF_2530_3pnp->Fill(xF);}
	    	if ((xF > 0.3)&& (xF < 0.35)) {h1_xF_3035_3pnp->Fill(xF);}
	    	if ((xF > 0.35)&& (xF < 0.4)) {h1_xF_3540_3pnp->Fill(xF);}
	    	if ((xF > 0.4)&& (xF < 0.45)) {h1_xF_4045_3pnp->Fill(xF);}

	    }

	    //if (mode != "Esum")
	    //{
	    //
	    //            if ((xF<0.2)&&(RpWestPpJetE > 105)) continue;
	    //		if ((xF<0.3)&&(RpWestPpJetE > 110)) continue;
	    //		if ((xF<0.45)&&(RpWestPpJetE > 115)) continue;

	    //}
	    //else
	    //{
	    //
	    //            if ((xF<0.2)&&(RpWestPpJetE > 112)) continue;
	    //		if ((xF<0.3)&&(RpWestPpJetE > 114)) continue;
	    //		if ((xF<0.45)&&(RpWestPpJetE > 120)) continue;

	    //}


	    if ((xF > 0.1)&& (xF < 0.15)) {h1_pT_XF1015->Fill(pt);h1_nPhoton_XF1015->Fill(jet->GetNumberOfTowers());}
	    if ((xF > 0.15)&& (xF < 0.2)) {h1_pT_XF1520->Fill(pt);h1_nPhoton_XF1520->Fill(jet->GetNumberOfTowers());}
	    if ((xF > 0.2)&& (xF < 0.25)) {h1_pT_XF2025->Fill(pt);h1_nPhoton_XF2025->Fill(jet->GetNumberOfTowers());}
	    if ((xF > 0.25)&& (xF < 0.3)) {h1_pT_XF2530->Fill(pt);h1_nPhoton_XF2530->Fill(jet->GetNumberOfTowers());}
	    if ((xF > 0.3)&&(xF < 0.45)) {h1_pT_XF30->Fill(pt);h1_nPhoton_XF30->Fill(jet->GetNumberOfTowers());}


	    if (mode == "Ecorr")
	    {

	    	if ((eng > 5)&&(eng < 10)) {eng_corr = f1->Eval(eng); eng_corr_sys = f3->Eval(eng); eng_corr_diff = 1.0*(fabs(eng_corr - eng_corr_sys)/eng_corr);} 
			else {if ((eng > 10)&&(eng < 60)) {eng_corr = f2->Eval(eng); eng_corr_sys = f4->Eval(eng);eng_corr_diff = 1.0*(fabs(eng_corr - eng_corr_sys)/eng_corr); cout << eng_corr << " "<< eng_corr_sys << " " << eng_corr_diff << endl;} else {eng_corr = eng; eng_corr_diff = -1;}}
			//cout << "eng_corr_diff" << eng_corr_diff << endl;
	    	//if ((xF > 0.1)&& (xF < 0.15) && (eng_corr_diff > 0)) {h1_xF_1015_SysDiff->Fill(eng_corr_diff);}
	    	//if ((xF > 0.15)&& (xF < 0.2) && (eng_corr_diff > 0)) {h1_xF_1520_SysDiff->Fill(eng_corr_diff);}
	    	if ((xF > 0.1)&& (xF < 0.2) && (eng_corr_diff > 0)) {h1_xF_1520_SysDiff->Fill(eng_corr_diff); h1_xF_1020_Ecorr->Fill( eng_corr * 1.0 / 100.);}
	    	if ((xF > 0.2)&& (xF < 0.25) && (eng_corr_diff > 0)) {h1_xF_2025_SysDiff->Fill(eng_corr_diff);h1_xF_2025_Ecorr->Fill( eng_corr * 1.0 / 100.);}
	    	if ((xF > 0.25)&& (xF < 0.3) && (eng_corr_diff > 0)) {h1_xF_2530_SysDiff->Fill(eng_corr_diff);h1_xF_2530_Ecorr->Fill( eng_corr * 1.0 / 100.);}
	    	if ((xF > 0.3)&& (xF < 0.45) && (eng_corr_diff > 0)) {h1_xF_3045_SysDiff->Fill(eng_corr_diff);h1_xF_3045_Ecorr->Fill( eng_corr * 1.0 / 100.);}

	    }

	    h2_pT_vs_xF_final->Fill(xF,pt);

	    Double_t Yphi=0;
	    if (phi > 0) {Yphi = TMath::Pi() - phi;} else {Yphi = -1.0 * TMath::Pi() - phi;}

	    h2_RPtrkXieast_vs_RPtrkPteast->Fill(EastRpPt,EastRpXi);
	    h1_eRPXi_final->Fill(EastRpXi);
	    if ((xF<0.2)&&(xF>0.1)) {xF = 0.175;}
	    h1_eRpP_aftercut->Fill(EastRpP);
	    h1_ZDCE_final->Fill(skimEvent->GetZdcSum(0));
	    TOFmult = skimEvent->GetTofMult();
	    cout << "TOFmult:" << TOFmult << endl;
	    TOFMinEta = skimEvent->GetTofEtaMin();
	    h1_TOFmult_final->Fill(TOFmult);
	    h1_TOFetaMin_final->Fill(TOFMinEta);
	    h2_TOFmult_vs_TOFMinEta->Fill(TOFMinEta,TOFmult);

	    if (skimEvent->GetSpinB() == 1) h2_BU_xF_vs_phi->Fill(phi,xF);
	    if (skimEvent->GetSpinB() == -1) h2_BD_xF_vs_phi->Fill(phi,xF);
	    if (skimEvent->GetSpinY() == 1) h2_YU_xF_vs_phi->Fill(Yphi,xF);
	    if (skimEvent->GetSpinY() == -1) h2_YD_xF_vs_phi->Fill(Yphi,xF);

	    if (nPhotons <= 2)
	    {

	    	if (skimEvent->GetSpinB() == 1) h2_BU_xF_vs_phi_nPhoton12->Fill(phi,xF);
	    	if (skimEvent->GetSpinB() == -1) h2_BD_xF_vs_phi_nPhoton12->Fill(phi,xF);
	    	if (skimEvent->GetSpinY() == 1) h2_YU_xF_vs_phi_nPhoton12->Fill(Yphi,xF);
	    	if (skimEvent->GetSpinY() == -1) h2_YD_xF_vs_phi_nPhoton12->Fill(Yphi,xF);

	    }
	    if (nPhotons >= 3)
	    {

	    	if (skimEvent->GetSpinB() == 1) h2_BU_xF_vs_phi_nPhoton3p->Fill(phi,xF);
	    	if (skimEvent->GetSpinB() == -1) h2_BD_xF_vs_phi_nPhoton3p->Fill(phi,xF);
	    	if (skimEvent->GetSpinY() == 1) h2_YU_xF_vs_phi_nPhoton3p->Fill(Yphi,xF);
	    	if (skimEvent->GetSpinY() == -1) h2_YD_xF_vs_phi_nPhoton3p->Fill(Yphi,xF);

	    }
	    if ((xF > 0.2)&&(xF < 0.45)) {final_event_count = true; h1_xF_final->Fill(xF);}
	    //h1_xF_final->Fill(xF);
	    if ((nRpsTracksEast==1)&&(nRpsTracksWest==1)) 
	    {

		h1_nPhoton_count_1east1westRP->Fill(jet->GetNumberOfTowers());
		h1_pT_count_1east1westRP->Fill(pt);
		h1_xF_count_1east1westRP->Fill(xF);

	    }
	    if ((nRpsTracksEast==0)&&(nRpsTracksWest==1)) 
	    {

		h1_nPhoton_count_only1westRP->Fill(jet->GetNumberOfTowers());
		h1_pT_count_only1westRP->Fill(pt);
		h1_xF_count_only1westRP->Fill(xF);

	    }	
	    if (pt > 2) {h2PtvsXF->Fill(xF , 2.5);} else {h2PtvsXF->Fill(xF , 1.5);}

	    if (nRpsTracksEast==1) {h1_EastRpP->Fill(EastRpP);}
	    if (nRpsTracksWest==1) {h1_WestRpP->Fill(WestRpP);}
	    if ((nRpsTracksEast==1) && (nRpsTracksWest==1)) {h1_EastRpP_doublediff->Fill(EastRpP);h1_WestRpP_doublediff->Fill(WestRpP);}
	    if ((nRpsTracksWest==1) && (nRpsTracksEast==0)) {h1_WestRpP_singlediff->Fill(WestRpP);}

	  }	

	    //Particle Branch is for simulated data only
	    // for(Int_t k = 0; k < jet->GetNumberOfParticles(); ++k)
	    // {
	    // 	particle = jet->GetParticle(k);
	
	    // }	    
	h1nJets->Fill(nJets);
    	if (final_event_count) {h1_event_final->Fill(1);} else {h1_event_final->Fill(2);}


    }
	for (int k=0;k<1000;k=k+1)
	{
		if (nRunEvent[k]>0) 
		{
			cout<<"k:"<<k<<"	n EVents this run:"<<nRunEvent[k]<<"	start time:"<<runStartTime[k]<<"	end time:"<<runEndTime[k]<<endl;
			ThisFillUncertainty = ThisFillUncertainty + (runEndTime[k] + runStartTime[k]) / 7200.0 * nRunEvent[k];
			
		}

	}
    if (thisFillEvent>0) {h1_pol_uncertainty->Fill(fillit,(sqrt(pow(polFms[fillit].dP0B,2) + pow(1.0*ThisFillUncertainty * polFms[fillit].ddPBdT/thisFillEvent , 2))));}

    outFile->Write();
    outFile->Close();
    delete ch;
}
