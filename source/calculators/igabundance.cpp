//
//  igabundance.cpp
//  Mothur
//
//  Created by Sarah Westcott on 4/3/19.
//  Copyright © 2019 Schloss Lab. All rights reserved.
//

#include "igabundance.hpp"

/***********************************************************************/
IGAbundance::IGAbundance() : DiversityCalculator(true) {}
/***********************************************************************/

vector<double> IGAbundance::getValues(int maxRank, vector<mcmcSample>& sampling) {
    try {
        maxRank = floor(pow(2.0,ceil(log((double) maxRank)/log(2.0)) + 2.0) + 1.0e-7); //nMax
        
        results.resize(maxRank, 0.0);
        int nSamples = sampling.size();
        
        if (nSamples == 0) {  return results; }
        
#ifdef USE_GSL
        
        DiversityUtils dutils("igabund");
        
        for(int i = 0; i < sampling.size(); i++) {
            
            if (m->getControl_pressed()) { break; }
            
            for (int j = 1; j <= maxRank; j++) {
                int nA = j;
                double dLog = 0.0, dP = 0.0;
                
                dLog = dutils.logLikelihood(nA, sampling[i].alpha, sampling[i].beta);
                
                dP = exp(dLog);
                
                results[j - 1] += dP*sampling[i].ns;
            }
            
        }
        
        for (int i = 1; i<=maxRank; i++) {
            results[i-1] /= (double)nSamples;
            
            if (isnan(results[i-1]) || isinf(results[i-1])) { results[i-1] = 0.0; }
        }
        
#endif
        
        return results;
    }
    catch(exception& e) {
        m->errorOut(e, "IGAbundance", "getValues");
        exit(1);
    }
}
/***********************************************************************/


