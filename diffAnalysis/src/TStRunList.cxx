// Filename: TStRunList.cxx
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Wed May 29 00:24:18 2019 (-0400)
// URL: jlab.org/~latif

#include <iostream>
#include <fstream>
#include <string>

#include "json.h"
#include "TStRunList.h"
#include "TString.h"
#include "TSystem.h"

using namespace std;
using json = nlohmann::json;

ClassImp(TStRunList)

TStRunList::TStRunList()
{
    runList = new TEntryList();
    missingRunList = new TEntryList();
}

TStRunList::~TStRunList()
{
    delete runList;
}

//_________________________________________________________________________
Int_t TStRunList::GetRunFromFileName(string fileName, const string prefix)
{
    TString inFile = fileName;
    if(inFile.Contains(".list"))
    {
	ifstream inFileList(inFile); //Use absolute path. No ~ for home directory.
	if(!inFileList)
	{
	    cout << "Unable to read run number from file list" <<endl;
	    return -1;
	}
	getline(inFileList, fileName);
	inFileList.close();
	cout << "\n------->Note: Setting trigger ID based on first run number only: "<< fileName <<"<-----\n"<<endl;
    }
    
    TString fName = fileName;
    fName.ReplaceAll("adc_", "");
    string mFileName = (string)fName;
    const string startDelim = prefix; //Read this from configuration file
    const string stopDelim = "_raw_";
    unsigned firstDelimPos;
    unsigned endPosOfFirstDelim;
    unsigned lastDelimPos;
    string runNumberStr;
    
    firstDelimPos = mFileName.find(startDelim);
    endPosOfFirstDelim = firstDelimPos + startDelim.length();
    lastDelimPos = mFileName.find_first_of(stopDelim, endPosOfFirstDelim);
    runNumberStr = mFileName.substr(endPosOfFirstDelim+1,8);
	cout << firstDelimPos << " " << endPosOfFirstDelim << " " << lastDelimPos << endl;
    cout << runNumberStr <<endl;

    return atoi(runNumberStr.c_str());
}

