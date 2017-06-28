/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */
/* AliAnalysisTaskEventChar.h
 *
 * Template task producing a P_t spectrum and pseudorapidity distribution.
 * Includes explanations of physics and primary track selections
 *
 * Based on tutorial example from offline pages
 * Edited by Arvinder Palaha
 */
#ifndef ALIANALYSISTASKEVENTCHAR_H
#define ALIANALYSISTASKEVENTCHAR_H

#ifndef ALIANALYSISTASKSE_H
#include <AliAnalysisTaskSE.h>
#endif

class AliAnalysisTaskEventChar : public AliAnalysisTaskSE {
 public:
    AliAnalysisTaskEventChar();
    AliAnalysisTaskEventChar(const char *name);
    virtual ~AliAnalysisTaskEventChar();
    
    virtual void     UserCreateOutputObjects();
    virtual void     ConnectInputData(Option_t *);
    virtual void     UserExec(Option_t *option);
    virtual void     Terminate(Option_t *);
    
 private:
    TList           *feIDexchange; //! 
    TList           *fOutputMB; //!
    TList           *fOutputEMC1; //!
    TList           *fOutputEMC7; //!
    TList           *fOutputEMC8; //!
    TList           *fOutputEMCJet; //!
    
    //Tag-Side Histos
    
    //Track Multiplicity Histos
    TH1F            *fHistTrkMultTag_MB[4];
    TH1F            *fHistTrkMultTag_EMC1[4];
    TH1F            *fHistTrkMultTag_EMC7[4];
    TH1F            *fHistTrkMultTag_EMC8[4];
    TH1F            *fHistTrkMultTag_EMCJet[4];
    
    //Pt Distribution Histos
    TH1F            *fHistTrkPtTag_MB[4];
    TH1F            *fHistTrkPtTag_EMC1[4];
    TH1F            *fHistTrkPtTag_EMC7[4];
    TH1F            *fHistTrkPtTag_EMC8[4];
    TH1F            *fHistTrkPtTag_EMCJet[4];
    
    //dEdx by Pt Histos
    TH2F            *fHistDeDxPtTag_MB[4];
    TH2F            *fHistDeDxPtTag_EMC1[4];
    TH2F            *fHistDeDxPtTag_EMC7[4];
    TH2F            *fHistDeDxPtTag_EMC8[4];
    TH2F            *fHistDeDxPtTag_EMCJet[4];
    
    //Away-Side Histos
    
    //Track Multiplicity Histos
    TH1F            *fHistTrkMultAway_MB[4];
    TH1F            *fHistTrkMultAway_EMC1[4];
    TH1F            *fHistTrkMultAway_EMC7[4];
    TH1F            *fHistTrkMultAway_EMC8[4];
    TH1F            *fHistTrkMultAway_EMCJet[4];
    
    //Pt Distribution Histos
    TH1F            *fHistTrkPtAway_MB[4];
    TH1F            *fHistTrkPtAway_EMC1[4];
    TH1F            *fHistTrkPtAway_EMC7[4];
    TH1F            *fHistTrkPtAway_EMC8[4];
    TH1F            *fHistTrkPtAway_EMCJet[4];
    
    //dEdx by Pt Histos
    TH2F            *fHistDeDxPtAway_MB[4];
    TH2F            *fHistDeDxPtAway_EMC1[4];
    TH2F            *fHistDeDxPtAway_EMC7[4];
    TH2F            *fHistDeDxPtAway_EMC8[4];
    TH2F            *fHistDeDxPtAway_EMCJet[4];
    
    //Left-Side Histos
    
    //Track Multiplicity Histos
    TH1F            *fHistTrkMultLeft_MB[4];
    TH1F            *fHistTrkMultLeft_EMC1[4];
    TH1F            *fHistTrkMultLeft_EMC7[4];
    TH1F            *fHistTrkMultLeft_EMC8[4];
    TH1F            *fHistTrkMultLeft_EMCJet[4];
    
    //Pt Distribution Histos
    TH1F            *fHistTrkPtLeft_MB[4];
    TH1F            *fHistTrkPtLeft_EMC1[4];
    TH1F            *fHistTrkPtLeft_EMC7[4];
    TH1F            *fHistTrkPtLeft_EMC8[4];
    TH1F            *fHistTrkPtLeft_EMCJet[4];
    
    //dEdx by Pt Histos
    TH2F            *fHistDeDxPtLeft_MB[4];
    TH2F            *fHistDeDxPtLeft_EMC1[4];
    TH2F            *fHistDeDxPtLeft_EMC7[4];
    TH2F            *fHistDeDxPtLeft_EMC8[4];
    TH2F            *fHistDeDxPtLeft_EMCJet[4];
    
    //Right-Side Histos
    
    //Track Multiplicity Histos
    TH1F            *fHistTrkMultRight_MB[4];
    TH1F            *fHistTrkMultRight_EMC1[4];
    TH1F            *fHistTrkMultRight_EMC7[4];
    TH1F            *fHistTrkMultRight_EMC8[4];
    TH1F            *fHistTrkMultRight_EMCJet[4];
    
    //Pt Distribution Histos
    TH1F            *fHistTrkPtRight_MB[4];
    TH1F            *fHistTrkPtRight_EMC1[4];
    TH1F            *fHistTrkPtRight_EMC7[4];
    TH1F            *fHistTrkPtRight_EMC8[4];
    TH1F            *fHistTrkPtRight_EMCJet[4];
    
    //dEdx by Pt Histos
    TH2F            *fHistDeDxPtRight_MB[4];
    TH2F            *fHistDeDxPtRight_EMC1[4];
    TH2F            *fHistDeDxPtRight_EMC7[4];
    TH2F            *fHistDeDxPtRight_EMC8[4];
    TH2F            *fHistDeDxPtRight_EMCJet[4];
       
    
    AliAnalysisTaskEventChar(const AliAnalysisTaskEventChar&); // not implemented
    AliAnalysisTaskEventChar& operator=(const AliAnalysisTaskEventChar&); // not implemented
    
    ClassDef(AliAnalysisTaskEventChar, 1); // example of analysis
};

#endif

