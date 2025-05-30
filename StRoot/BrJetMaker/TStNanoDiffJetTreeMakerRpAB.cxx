// Filename: TStNanoDiffJetTreeMakerRpAB.cxx
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Mon Aug 19 17:37:54 2019 (-0400)
// URL: jlab.org/~latif


#include "TStNanoDiffJetTreeMakerRpAB.h"
#include "StEvent/StEvent.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StSpinPool/StJetEvent/StJetEvent.h"
#include "StSpinPool/StJetSkimEvent/StJetSkimEvent.h"
#include "StSpinPool/StJetEvent/StJetCandidate.h"
#include "StSpinPool/StJetEvent/StJetTower.h"
#include "StSpinPool/StJetEvent/StJetParticle.h"
#include "StSpinPool/StJetEvent/StJetVertex.h"
#include "StSpinPool/StJetEvent/StJetTrack.h"
#include "StJetFinder/StProtoJet.h"
#include "StJetMaker/StJetMaker2015.h"
#include "StJetMaker/StJetSkimEventMaker.h"
#include "StEvent/StTriggerData.h"
#include "StEvent/StTriggerId.h"

#include "TStJetEvent.h"
#include "TStJetSkimEvent.h"
#include "TStJetCandidate.h"

ClassImp(TStNanoDiffJetTreeMakerRpAB)

//_____________________________________________________________________________ 
TStNanoDiffJetTreeMakerRpAB::TStNanoDiffJetTreeMakerRpAB( StMuDstMaker* maker):StMaker("TStNanoDiffJetTreeMakerRpAB")
{
    mOutJetEvent = new TStJetEvent();
    mOutSkimEvent = mOutJetEvent->GetEvent();

    mMuDstMaker      = maker ;
    mAfterburner = new StMuRpsUtil(maker);


    mJetMaker = 0;
    mSkimEventMaker = 0;
    mInJetEvent = 0;
    mInSkimEvent = 0;

    mEtaMax = 6.0;
    mEtaMin = -2.0;
    mZdist = 735.0;


    //RP Buffer
    TStRpsTrackData::Class()->IgnoreTObjectStreamer();
    mRpsArray = new TClonesArray("TStRpsTrackData");    
}

//_____________________________________________________________________________ 
TStNanoDiffJetTreeMakerRpAB::~TStNanoDiffJetTreeMakerRpAB()
{
    //
    delete mOutJetEvent;

    //RP Buffer    
    delete mRpsArray;
}


//_____________________________________________________________________________ 
Int_t TStNanoDiffJetTreeMakerRpAB::Init()
{

    mOutFile = new TFile(mOutName, "recreate");
    mTree = new TTree("T", "EM Jet Analysis Tree");
    TStJetEvent::Class()->IgnoreTObjectStreamer();
    mTree->Branch("jetEvents", &mOutJetEvent, 256000, 99);

    //branch to hold FMS photons (used in FastJet) info from FMS maker
    
    //RP branch
    mTree->Branch("rpTrack", &mRpsArray, 256000, 99);
    
    cout << "Initialized NanoJetMaker!" <<endl;
    return kStOK;
}


//_____________________________________________________________________________
Int_t TStNanoDiffJetTreeMakerRpAB::Make()
{
    mMuDst = (StMuDst*)GetInputDS("MuDst");
    mEvent = (StEvent*)GetInputDS("StEvent");

    // Check if mMuDst or mEvent is valid
    if(!mMuDst)
    {
	LOG_ERROR << "TSt<Template>Maker::Make - No MuDst found" <<endm;
	return kStFatal;
    }
    mMuEvent = mMuDst->event();
    
    mJetMaker = (StJetMaker2015*)GetMaker("StJetMaker2015"); //This did not work --> bug fixed, try again
    mSkimEventMaker = (StJetSkimEventMaker*)GetMaker("StJetSkimEventMaker"); //Did not work --> bug fixed, try again
    if(!mJetMaker || !mSkimEventMaker)
    {
	LOG_ERROR << "TStNanoDiffJetTreeMakerRpAB::Make - No JetMaker or SkimEventMaker found" <<endm;
	return kStFatal;	
    }

    mInJetEvent = mJetMaker->event("AntiKtR070NHits12"); //Set the branch name from a Set function
    mInSkimEvent = mSkimEventMaker->event();
    cout<<"start NanoEvent!"<<endl;

    assert(mInJetEvent && mInSkimEvent);
    assert(mInJetEvent->runId() == mInSkimEvent->runId() && mInJetEvent->eventId() == mInSkimEvent->eventId());

    //intermediate variables
    Int_t spin4Bit;
    Int_t spinB;
    Int_t spinY;
    Int_t nPhotons;
    Double_t eta;
    Double_t phi;
    Double_t eng;
    Double_t pt;
    Double_t vtxZ;
    Double_t jetX;
    Double_t jetY;
    Double_t theta;
    Double_t rt;

    if ((mInSkimEvent->bx7() > 30 && mInSkimEvent->bx7() < 40) || (mInSkimEvent->bx7() > 110 && mInSkimEvent->bx7() < 120))
	    return kStOK;
    
    if(mInJetEvent->numberOfJets() == 0)
	return kStOK;
	
    mInVertex = mInJetEvent->vertex(); //same as mInJetEvent->vertex(0), i.e. highest ranked vertex only
    if (!mInVertex)
	return kStOK;

    mRpsArray->Clear();    
    mOutJetEvent->Reset();


    mTrigFlag = kFALSE;
//    for(Int_t k = 0; k < mMaxTriggers; ++k)
//    {
//	mTrigFlag = mMuEvent->triggerIdCollection().nominal().isTrigger(mTrigIds[k]);
//	if(mTrigFlag)
//	{
//	    mOutSkimEvent->SetTrigFlag(k, 1);
//	    mOutSkimEvent->SetTrigBit(k);
//	}
//    }	

    for(Int_t k = 0; k < 10; ++k)
    {
	int mTrigId = mMuEvent->triggerIdCollection().nominal().triggerId(k);
	

	switch(mTrigId)
	{
	    case 480810 :
		mOutSkimEvent->SetTrigFlag(0, 1);
		break;
	    case 480830 :
		mOutSkimEvent->SetTrigFlag(0, 1);
		break;
	    case 480809 :
		mOutSkimEvent->SetTrigFlag(1, 1);
		break;
	    case 480829 :
		mOutSkimEvent->SetTrigFlag(1, 1);
		break;
	    case 480808 :
		mOutSkimEvent->SetTrigFlag(2, 1);
		break;
	    case 480828 :
		mOutSkimEvent->SetTrigFlag(2, 1);
		break;
	    case 480801 :
		mOutSkimEvent->SetTrigFlag(3, 1);
		break;
	    case 480821 :
		mOutSkimEvent->SetTrigFlag(3, 1);
		break;
	    case 480841 :
		mOutSkimEvent->SetTrigFlag(3, 1);
		break;
	    case 480802 :
		mOutSkimEvent->SetTrigFlag(4, 1);
		break;
	    case 480822 :
		mOutSkimEvent->SetTrigFlag(4, 1);
		break;
	    case 480803 :
		mOutSkimEvent->SetTrigFlag(5, 1);
		break;
	    case 480823 :
		mOutSkimEvent->SetTrigFlag(5, 1);
		break;
	    case 480843 :
		mOutSkimEvent->SetTrigFlag(5, 1);
		break;
	    case 480804 :
		mOutSkimEvent->SetTrigFlag(6, 1);
		break;
	    case 480824 :
		mOutSkimEvent->SetTrigFlag(6, 1);
		break;
	    case 480844 :
		mOutSkimEvent->SetTrigFlag(6, 1);
		break;
	    case 480805 :
		mOutSkimEvent->SetTrigFlag(7, 1);
		break;
	    case 480825 :
		mOutSkimEvent->SetTrigFlag(7, 1);
		break;
	    case 480806 :
		mOutSkimEvent->SetTrigFlag(8, 1);
		break;
	    case 480826 :
		mOutSkimEvent->SetTrigFlag(8, 1);
		break;
	
	    case 480301 :
		mOutSkimEvent->SetTrigFlag(0, 1);
		break;
	    case 480404 :
		mOutSkimEvent->SetTrigFlag(1, 1);
		break;
	    case 480414 :
		mOutSkimEvent->SetTrigFlag(1, 1);
		break;
	    case 480401 :
		mOutSkimEvent->SetTrigFlag(2, 1);
		break;
	    case 480411 :
		mOutSkimEvent->SetTrigFlag(2, 1);
		break;
	    case 480501 :
		mOutSkimEvent->SetTrigFlag(3, 1);
		break;
	    case 480405 :
		mOutSkimEvent->SetTrigFlag(4, 1);
		break;
	    case 480415 :
		mOutSkimEvent->SetTrigFlag(4, 1);
		break;
	    case 480202 :
		mOutSkimEvent->SetTrigFlag(5, 1);
		break;
	    case 480203 :
		mOutSkimEvent->SetTrigFlag(6, 1);
		break;
	    case 480204 :
		mOutSkimEvent->SetTrigFlag(7, 1);
		break;
	    case 480205 :
		mOutSkimEvent->SetTrigFlag(8, 1);
		break;
	}


    }	
    vtxZ = mInVertex->position().z();

    //tof and bbc multiplicity. Needed to minimize FMS ring of fire.
    mOutSkimEvent->SetTofMult(mMuEvent->triggerData()->tofMultiplicity()); 
    mOutSkimEvent->SetTofTrayMult(mMuEvent->btofTrayMultiplicity()); 
    //bbc multiplicity
    Int_t tac, adc;
    Int_t bbcMult = 0;
    Int_t east = 0;
    for(Int_t i = 1; i <= 16; i++)
    {
	tac = mMuEvent->triggerData()->bbcTDC((StBeamDirection)east,i);
	if(tac > 100 && tac < 2400)
	{
	    adc = mMuEvent->triggerData()->bbcADC((StBeamDirection)east, i);
	    if(adc > 50)
		bbcMult++;
	    //bbcEsum += trgd->bbcADC(east,i);
	}
    } 
    mOutSkimEvent->SetBbcMult(bbcMult);
    
    mOutSkimEvent->SetRunNumber(mInJetEvent->runId());
    mOutSkimEvent->SetEventId(mInJetEvent->eventId());
    mOutSkimEvent->SetVertexZ(vtxZ);
    //mOutSkimEvent->SetUnixTime(mInSkimEvent->unixTime()); //skimEvent does not have ET to GEM correction for SL20a
    mOutSkimEvent->SetUnixTime(mInJetEvent->unixTime());
    mOutSkimEvent->SetBbcWestRate(mInSkimEvent->bbcWestRate());
    mOutSkimEvent->SetBbcEastRate(mInSkimEvent->bbcEastRate());
    mOutSkimEvent->SetFillNumber((Int_t)mInSkimEvent->fill());
    mOutSkimEvent->SetBbcSumSmall(0,mMuEvent->bbcTriggerDetector().adcSumEast());
    mOutSkimEvent->SetBbcSumSmall(1,mMuEvent->bbcTriggerDetector().adcSumWest());
    mOutSkimEvent->SetBbcSumLarge(0,mMuEvent->bbcTriggerDetector().adcSumEastLarge());
    mOutSkimEvent->SetBbcSumLarge(1,mMuEvent->bbcTriggerDetector().adcSumWestLarge());
    
    spin4Bit = mInSkimEvent->spin4usingBx48(); 
    /*
      Spin info to be interpreted based on: https://drupal.star.bnl.gov/STAR/blog/oleg/spin-patterns-and-polarization-direction
      spin = 10:  STAR pol B+ Y+
      =  9:  STAR pol B+ Y-
      =  6:  STAR pol B- Y+
      =  5:  STAR pol B- Y-
      (Note: Bunches can also be unpolarized, i.e. other possible values for the 4-spin bits are 1, 2, 4, and 8.)
    */

    switch(spin4Bit) 
    {
    case 5:
    {
	spinB = -1;
	spinY = -1;
	break;
    }
    case 6:
    {
	spinB = -1;
	spinY = +1;
	break;
    }
    case 9:
    {
	spinB = +1;
	spinY = -1;
	break;
    }
    case 10:
    {
	spinB = +1;
	spinY = +1;
	break;
    }
    default: //either one is unpolarized or undefined
	spinB = 0;
	spinY = 0;
    }

    mOutSkimEvent->SetSpinB(spinB);
    mOutSkimEvent->SetSpinY(spinY);
		
    for(Int_t i = 0; i < mInVertex->numberOfJets(); ++i) 
    {	    
	eta = mInVertex->jet(i)->eta();

	if(eta < mEtaMin  || eta > mEtaMax) 
	    continue;
	    
	phi = mInVertex->jet(i)->phi();
	eng = mInVertex->jet(i)->E();
	pt = mInVertex->jet(i)->pt();
	nPhotons = mInVertex->jet(i)->numberOfTowers();
	rt = mInVertex->jet(i)->rt();
	    
	theta =  2 * atan( exp(-eta) );
	jetX = (mZdist - vtxZ) * tan(theta) * cos(phi);
	jetY = (mZdist - vtxZ) * tan(theta) * sin(phi);

	mOutJet = mOutJetEvent->NewJet();	    
	mOutJet->SetNphotons(nPhotons);
	mOutJet->SetEta(eta);
	mOutJet->SetPhi(phi);
	mOutJet->SetE(eng);
	mOutJet->SetPt(pt);
	mOutJet->SetX(jetX);
	mOutJet->SetY(jetY);
	mOutJet->SetRt(rt);
	mOutJet->SetUedPt(mInVertex->jet(i)->ueDensity()["OffAxisConesR070"]*mInVertex->jet(i)->area());
	cout << "Density: "<< mInVertex->jet(i)->ueDensity()["OffAxisConesR070"] <<" Area: "<< mInVertex->jet(i)->area() <<endl;

	//Add Tower info
	for(Int_t j = 0; j < mInVertex->jet(i)->numberOfTowers(); ++j)
	{
	    mInTower = mInVertex->jet(i)->tower(j);
	    mOutTower = mOutJetEvent->NewTower();
	    mOutJetEvent->CopyTower(mInTower, mOutTower);		    
	    mOutJet->AddTower(mOutTower);
	}

	//Add particle info
	for(Int_t j = 0; j < mInVertex->jet(i)->numberOfParticles(); ++j)
	{
	    mInParticle = mInVertex->jet(i)->particle(j);
	    mOutParticle = mOutJetEvent->NewParticle();
	    mOutJetEvent->CopyParticle(mInParticle, mOutParticle);
	    mOutJet->AddParticle(mOutParticle);		
	}

	//Add track info (if needed) in a similar fashion as tower and particles	    
    }
    
    MakeRps();
    mTree->Fill();

        
    return kStOK;
}

//_____________________________________________________________________________
Int_t TStNanoDiffJetTreeMakerRpAB::MakeRps()
{

	StMuEvent* muEvent      =  mMuDstMaker->muDst()->event(); // Get 'event' data


    //------ Using afterburner ----
     if(mUseRpsAfterburner)
     {    
    	mAfterburner->updateVertex(0.000415, 0.000455, 0.0); // specific to run 15 pp200 trans !!! To be set with set method
    	mRpsMuColl = mAfterburner->process(); // executes afterburner
     }
    //------
    
    //mRpsMuColl = mMuDst->RpsCollection();  //No afterburner
    if(!mRpsMuColl)
    {
	cout<<"No RP data for this event"<<endl;
	return kStSkip;
    }
    
    mRpNtracks = mRpsMuColl->numberOfTracks();
    Int_t trkType;
    for(Int_t i = 0; i < mRpNtracks; ++i)
    {	
	mRpsTrackData =  new((*mRpsArray)[i])TStRpsTrackData();	
	mRpsTrk = mRpsMuColl->track(i);
	trkType = (mRpsTrk->type() == StMuRpsTrack::rpsGlobal) ? 1 : 0;
	
	mRpsTrackData->SetType(trkType);
	mRpsTrackData->SetNplanes(mRpsTrk->planesUsed());
	mRpsTrackData->SetBranch(mRpsTrk->branch());	
	mRpsTrackData->SetTheta(1000.0*mRpsTrk->theta());	
	mRpsTrackData->SetThetaX(1000.0*mRpsTrk->theta(0));	
	mRpsTrackData->SetThetaY(1000.0*mRpsTrk->theta(1));	
	mRpsTrackData->SetEta(mRpsTrk->eta());
	mRpsTrackData->SetPhi(mRpsTrk->phi());
	mRpsTrackData->SetPt(mRpsTrk->pt());		
	mRpsTrackData->SetP(mRpsTrk->p());		
	mRpsTrackData->SetPx(mRpsTrk->pVec().x());		
	mRpsTrackData->SetPy(mRpsTrk->pVec().y());		
	mRpsTrackData->SetPz(mRpsTrk->pVec().z());		
	mRpsTrackData->SetXi(mRpsTrk->xi(mBeamMom)); // Beam momentum is approximate		
	mRpsTrackData->SetMt(-1.0*mRpsTrk->t(mBeamMom));	

//	for (Int_t rpPointi=0; rpPointi<mRpsMuColl->numberOfTrackPoints(); ++rpPointi)
	//if (mRpsMuColl->numberOfTrackPoints() > 0)
        //{

	//	mRpsTrkPoint = mRpsMuColl->trackPoint(0);
	//	mRpsTrackData->SetX(mRpsTrkPoint->x());
	//	mRpsTrackData->SetY(mRpsTrkPoint->y());

	//}

    }

    //afterburner
    mAfterburner->clear(); //Critical!!!
    
    return kStOk;    
}


//_____________________________________________________________________________
Int_t TStNanoDiffJetTreeMakerRpAB::Finish()
{
    //Write histograms to root file etc.
    mOutFile->Write();
    return kStOK;
}

//_____________________________________________________________________________
void TStNanoDiffJetTreeMakerRpAB::SetTrigIds(Int_t *trigIds)
{
    for(Int_t i = 0; i < mMaxTriggers; ++i)
	mTrigIds[i] = trigIds[i];
}
