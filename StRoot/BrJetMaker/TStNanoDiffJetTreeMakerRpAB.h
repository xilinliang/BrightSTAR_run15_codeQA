// Filename: TStNanoDiffJetTreeMakerRpAB.h
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Mon Aug 19 17:38:04 2019 (-0400)
// URL: jlab.org/~latif

#ifndef TSTNANODIFFJETTREEMAKERRpAB_H
#define TSTNANODIFFJETTREEMAKERRpAB_H

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "StMaker.h"

#include "StMuDSTMaker/COMMON/StMuRpsCollection.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrack.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrackPoint.h"
#include "BrContainers/TStRpsTrackData.h"
#include "StMuRpsUtil/StMuRpsUtil.h"
#include "StMuRpsUtil/StMuRpsCollection2.h"

class StEvent;
class StMuDst;
class StMuEvent;
class StJetMaker2015;
class StJetEvent;
class StJetTower;
class StJetParticle;
class StJetVertex;
class StJetSkimEvent;
class StJetSkimTrig;
class StJetSkimEventMaker;

class TStJetEvent;
class TStJetSkimEvent;
class TStJetCandidate;
class TStJetTower;
class TStJetParticle;
class StMuRpsUtil;
class StMuDstMaker;

class TStNanoDiffJetTreeMakerRpAB : public StMaker
{
private:
    StMuDst *mMuDst;  
    StEvent* mEvent;
    StMuEvent *mMuEvent;

    StMuDstMaker* mMuDstMaker ;                      //  Make MuDst pointer available to member functions

    StJetMaker2015 *mJetMaker;
    StJetSkimEventMaker *mSkimEventMaker;
    StJetEvent* mInJetEvent;
    StJetSkimEvent* mInSkimEvent;
    StJetParticle *mInParticle;
    StJetTower *mInTower;
    StJetVertex *mInVertex;
   
 
    TFile *mOutFile;
    TTree *mTree;
    TString mOutName = "NanoJetTree.root";
    TStJetEvent *mOutJetEvent;    
    TStJetSkimEvent *mOutSkimEvent;    
    TStJetCandidate *mOutJet;
    TStJetParticle *mOutParticle;
    TStJetTower *mOutTower;

    static const Int_t mMaxTriggers = 9;
    StJetSkimTrig* mJetTrig[mMaxTriggers];
    Int_t mTrigIds[mMaxTriggers];
    Double_t mEtaMax;
    Double_t mEtaMin;
    Double_t mZdist;
    Bool_t mTrigFlag;

    //--- RP ---
    //StMuRpsCollection *mRpsMuColl;
    StMuRpsCollection2 *mRpsMuColl; //Use after burner
    StMuRpsUtil* mAfterburner;
    StMuRpsTrack *mRpsTrk;
    Double_t mBeamMom;
    StMuRpsTrackPoint *mRpsTrkPoint;

    Int_t mUseRpsAfterburner=1;    
    Int_t mRpNtracks;
    TClonesArray  *mRpsArray;
    TStRpsTrackData *mRpsTrackData;
    
public: 
    TStNanoDiffJetTreeMakerRpAB(StMuDstMaker* maker);
    virtual ~TStNanoDiffJetTreeMakerRpAB();
    virtual Int_t Init();
    virtual Int_t Make();
    virtual Int_t Finish();
    void SetOutFileName(TString fileName){mOutName = fileName;}
    // virtual Int_t InitRun  (int runumber){return 0;}; // Overload empty StMaker::InitRun 
    // virtual Int_t FinishRun(int runumber){return 0;}; // Overload empty StMaker::FinishRun 
    void SetEtaMax(Double_t etaMax){mEtaMax = etaMax;}
    void SetEtaMin(Double_t etaMin){mEtaMin = etaMin;}
    void SetDetZdist(Double_t z){mZdist = z;}
    void SetTrigIds(Int_t *trigIds);
    Int_t MakeRps();
    
    ClassDef(TStNanoDiffJetTreeMakerRpAB,1) 
};

#endif

