#ifndef ALIANALYSISTASKPATJET_H
#define ALIANALYSISTASKPATJET_H
    
/*******
 * Header for jet analysis task for the Cal Poly group
 * 
 *
 * Author: Patrick j Steffanic
 */
    
#include "AliAnalysisTaskEmcalJet.h"
#include "THistManager.h"
    
class AliAnalysisTaskPatJet : public AliAnalysisTaskEmcalJet {
    public:
    
    AliAnalysisTaskPatJet();
    AliAnalysisTaskPatJet(const char *name);
    virtual ~AliAnalysisTaskPatJet();
    
    void UserCreateOutputObjects();
    void Terminate(Option_t *option);
    
    protected:
    
    void ExecOnce();
    Bool_t FillHistograms();
    Bool_t Run();
    
    //Add user functions here
    
    void InitJetHistos();
    void InitTrackHistos();
    void InitClusterHistos();
    void FillJetHistos();
    void FillTrackHistos();
    void FillClusterHistos();
    
    THistManager fHistManager;///< Histgram manager
    
    
    private:
    AliAnalysisTaskPatJet(const AliAnalysisTaskPatJet&);
    AliAnalysisTaskPatJet &operator=(const AliAnalysisTaskPatJet&);
    
    ClassDef(AliAnalysisTaskPatJet, 1);
    
};
#endif
    