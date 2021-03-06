#ifndef Mothur_sequencecountparser_h
#define Mothur_sequencecountparser_h

//
//  sequencecountparser.h
//  Mothur
//
//  Created by Sarah Westcott on 8/7/12.
//  Copyright (c) 2012 Schloss Lab. All rights reserved.
//

#include "mothur.h"
#include "mothurout.h"
#include "sequence.hpp"
#include "counttable.h"
#include "utils.hpp"

/* This class reads a fasta and count file and parses the data by group. The countfile must contain group information.
 
 Note: The sum of all the groups unique sequences will be larger than the original number of unique sequences. 
 This is because when we parse the count file we make a unique for each group instead of 1 unique for all
 groups. 
 
 */

class SequenceCountParser {
	
public:
	
    SequenceCountParser(string, string, vector<string>);			//count, fasta, groups - file mismatches will set m->setControl_pressed(true)
    ~SequenceCountParser();
    
    //general operations
    int getNumGroups();
    vector<string> getNamesOfGroups();
    
    vector<string> getFiles(string);  //returns fasta and count file a specific group.
    map<string, vector<string> > getFiles() { return groupToFiles; } //returns all files groupName - > vector of groups files (fasta, count);
    
private:
    MothurOut* m;
    Utils util;
    
    map<string, vector<string> > groupToFiles;
    vector<string> namesOfGroups; //namesOfGroups in same order as groupToSeqs
    
    
};



#endif
