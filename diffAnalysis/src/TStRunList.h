// Filename: TStRunList.h
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Wed May 29 00:26:00 2019 (-0400)
// URL: jlab.org/~latif

#ifndef TSTRUNLIST_H
#define TSTRUNLIST_H

#include <TObject.h>
#include <TEntryList.h>
#include <string>
using namespace std;

class TStRunList: public TObject
{
    TEntryList *runList;
    TEntryList *missingRunList;
public:
    
    TStRunList();
    virtual ~TStRunList();

    static Int_t GetRunFromFileName(string fileName, const string prefix);
    ClassDef(TStRunList,1)
};
#endif
