// Filename: TStFmsHotChDB.cxx
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Fri Apr 10 15:24:42 2020 (-0400)
// URL: jlab.org/~latif

#include <iostream>
#include <fstream>
#include <string>

#include "json.h"
#include "TString.h"

#include "TStFmsHotChDB.h"

using namespace std;
using json = nlohmann::json;

ClassImp(TStFmsHotChDB)

TStFmsHotChDB::TStFmsHotChDB()
{

}

TStFmsHotChDB::~TStFmsHotChDB()
{

}

void TStFmsHotChDB::GetHotChList(Int_t fillNo, Bool_t isHotCh[][571])
{

    if(fillNo == -1)
    {
	cout << "-----------> Unable to get valid fill number <------------" <<endl;
	cout << "Hot Channel List Will be Empty" <<endl;
	return;
    }
    
    TString StarHome = getenv("STARHOME");
    TString FmsHotChFileName = StarHome + "/database/Run15FmsHotChList.json";
    std::ifstream i(FmsHotChFileName);
    json j;
    i >> j;

    Int_t det;
    Int_t ch;
    for(Int_t k = 0; k < j.size(); ++k)
    {
	if(j[k]["fill"] == fillNo)
	{	    
	    for(int r = 0; r < j[k]["hot"].size(); ++r)
	    {
		det = j[k]["hot"][r]["det"];
		ch = j[k]["hot"][r]["ch"];
		if((det - 8) < 4 && (ch - 1) < 571)
		    isHotCh[det - 8][ch - 1] = 1;
	    }

	    for(Int_t r = 0; r < j[k]["bad"].size(); ++r)
	    {
		det = j[k]["bad"][r]["det"];
		ch = j[k]["bad"][r]["ch"];
		if((det - 8) < 4 && (ch - 1) < 571)
		    isHotCh[det - 8][ch - 1] = 1;
	    }
	    break;
	}
    }

    //Masking of beam background / ring of fire channels is done by excluding small-bs3 trigger
    //Other masked channels are as listed here: 
    int roh = j.size() - 1; //Rest of the hot channels
    for(int r = 0; r < j[roh]["hot"].size(); ++r)
    {
    	det = j[roh]["hot"][r]["det"];
    	ch = j[roh]["hot"][r]["ch"];
    	if((det - 8) < 4 && (ch - 1) < 571)
    	    isHotCh[det - 8][ch -1] = 1;
    }
  
    
    i.close();    
 
}


