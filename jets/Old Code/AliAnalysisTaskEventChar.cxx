/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id$ */

/* AliAnalysisTaskEventChar.cxx
 *
 * Task for characterizing events containing a high Pt electron
 * Created by Patrick Steffanic
 */
#include "AliAnalysisTaskEventChar.h"

#include "Riostream.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TList.h"

#include "AliAnalysisTaskSE.h"
#include "AliAnalysisManager.h"
#include "AliStack.h"
#include "AliESDtrackCuts.h"
#include "AliESDEvent.h"
#include "AliESDInputHandler.h"

ClassImp(AliAnalysisTaskEventChar)

//________________________________________________________________________
AliAnalysisTaskEventChar::AliAnalysisTaskEventChar() // All data members should be initialised here
   :AliAnalysisTaskSE(),
    feIDexchange(0),
    fOutputMB(0),
    fOutputEMC1(0),
    fOutputEMC7(0),
    fOutputEMC8(0),
    fOutputEMCJet(0)
{
    for(Int_t i=0;i<4;i++){
        //Tag Side Histos
        fHistTrkMultTag_MB[i]=0;
        fHistTrkMultTag_EMC1[i]=0;
        fHistTrkMultTag_EMC7[i]=0;
        fHistTrkMultTag_EMC8[i]=0;
        fHistTrkMultTag_EMCJet[i]=0;
            
        fHistTrkPtTag_MB[i]=0;
        fHistTrkPtTag_EMC1[i]=0;
        fHistTrkPtTag_EMC7[i]=0;
        fHistTrkPtTag_EMC8[i]=0;
        fHistTrkPtTag_EMCJet[i]=0;
            
        fHistTrkDeDxPtTag_MB[i]=0;
        fHistTrkDeDxPtTag_EMC1[i]=0;
        fHistTrkDeDxPtTag_EMC7[i]=0;
        fHistTrkDeDxPtTag_EMC8[i]=0;
        fHistTrkDeDxPtTag_EMCJet[i]=0;
            
        //Away Side Histos
        fHistTrkMultAway_MB[i]=0;
        fHistTrkMultAway_EMC1[i]=0;
        fHistTrkMultAway_EMC7[i]=0;
        fHistTrkMultAway_EMC8[i]=0;
        fHistTrkMultAway_EMCJet[i]=0;
            
        fHistTrkPtAway_MB[i]=0;
        fHistTrkPtAway_EMC1[i]=0;
        fHistTrkPtAway_EMC7[i]=0;
        fHistTrkPtAway_EMC8[i]=0;
        fHistTrkPtAway_EMCJet[i]=0;
            
        fHistTrkDeDxPtAway_MB[i]=0;
        fHistTrkDeDxPtAway_EMC1[i]=0;
        fHistTrkDeDxPtAway_EMC7[i]=0;
        fHistTrkDeDxPtAway_EMC8[i]=0;
        fHistTrkDeDxPtAway_EMCJet[i]=0;
            
        //Left Side Histos
        fHistTrkMultLeft_MB[i]=0;
        fHistTrkMultLeft_EMC1[i]=0;
        fHistTrkMultLeft_EMC7[i]=0;
        fHistTrkMultLeft_EMC8[i]=0;
        fHistTrkMultLeft_EMCJet[i]=0;
            
        fHistTrkPtLeft_MB[i]=0;
        fHistTrkPtLeft_EMC1[i]=0;
        fHistTrkPtLeft_EMC7[i]=0;
        fHistTrkPtLeft_EMC8[i]=0;
        fHistTrkPtLeft_EMCJet[i]=0;
            
        fHistTrkDeDxPtLeft_MB[i]=0;
        fHistTrkDeDxPtLeft_EMC1[i]=0;
        fHistTrkDeDxPtLeft_EMC7[i]=0;
        fHistTrkDeDxPtLeft_EMC8[i]=0;
        fHistTrkDeDxPtLeft_EMCJet[i]=0;
            
        //Right Side Histos
        fHistTrkMultRight_MB[i]=0;
        fHistTrkMultRight_EMC1[i]=0;
        fHistTrkMultRight_EMC7[i]=0;
        fHistTrkMultRight_EMC8[i]=0;
        fHistTrkMultRight_EMCJet[i]=0;
            
        fHistTrkPtRight_MB[i]=0;
        fHistTrkPtRight_EMC1[i]=0;
        fHistTrkPtRight_EMC7[i]=0;
        fHistTrkPtRight_EMC8[i]=0;
        fHistTrkPtRight_EMCJet[i]=0;
           
        fHistTrkDeDxPtRight_MB[i]=0;
        fHistTrkDeDxPtRight_EMC1[i]=0;
        fHistTrkDeDxPtRight_EMC7[i]=0;
        fHistTrkDeDxPtRight_EMC8[i]=0;
        fHistTrkDeDxPtRight_EMCJet[i]=0;
    }
            
}

//________________________________________________________________________
AliAnalysisTaskEventChar::AliAnalysisTaskEventChar(const char *name) // All data members should be initialised here
   :AliAnalysisTaskSE(name),
    feIDexchange(0),
    fOutputMB(0),
    fOutputEMC1(0),
    fOutputEMC7(0),
    fOutputEMC8(0),
    fOutputEMCJet(0)
{
    for(Int_t i=0;i<4;i++){
        //Tag Side Histos
        fHistTrkMultTag_MB[i]=0;
        fHistTrkMultTag_EMC1[i]=0;
        fHistTrkMultTag_EMC7[i]=0;
        fHistTrkMultTag_EMC8[i]=0;
        fHistTrkMultTag_EMCJet[i]=0;
            
        fHistTrkPtTag_MB[i]=0;
        fHistTrkPtTag_EMC1[i]=0;
        fHistTrkPtTag_EMC7[i]=0;
        fHistTrkPtTag_EMC8[i]=0;
        fHistTrkPtTag_EMCJet[i]=0;
            
        fHistTrkDeDxPtTag_MB[i]=0;
        fHistTrkDeDxPtTag_EMC1[i]=0;
        fHistTrkDeDxPtTag_EMC7[i]=0;
        fHistTrkDeDxPtTag_EMC8[i]=0;
        fHistTrkDeDxPtTag_EMCJet[i]=0;
            
        //Away Side Histos
        fHistTrkMultAway_MB[i]=0;
        fHistTrkMultAway_EMC1[i]=0;
        fHistTrkMultAway_EMC7[i]=0;
        fHistTrkMultAway_EMC8[i]=0;
        fHistTrkMultAway_EMCJet[i]=0;
            
        fHistTrkPtAway_MB[i]=0;
        fHistTrkPtAway_EMC1[i]=0;
        fHistTrkPtAway_EMC7[i]=0;
        fHistTrkPtAway_EMC8[i]=0;
        fHistTrkPtAway_EMCJet[i]=0;
          
        fHistTrkDeDxPtAway_MB[i]=0;
        fHistTrkDeDxPtAway_EMC1[i]=0;
        fHistTrkDeDxPtAway_EMC7[i]=0;
        fHistTrkDeDxPtAway_EMC8[i]=0;
        fHistTrkDeDxPtAway_EMCJet[i]=0;
            
        //Left Side Histos
        fHistTrkMultLeft_MB[i]=0;
        fHistTrkMultLeft_EMC1[i]=0;
        fHistTrkMultLeft_EMC7[i]=0;
        fHistTrkMultLeft_EMC8[i]=0;
        fHistTrkMultLeft_EMCJet[i]=0;
           
        fHistTrkPtLeft_MB[i]=0;
        fHistTrkPtLeft_EMC1[i]=0;
        fHistTrkPtLeft_EMC7[i]=0;
        fHistTrkPtLeft_EMC8[i]=0;
        fHistTrkPtLeft_EMCJet[i]=0;
            
        fHistTrkDeDxPtLeft_MB[i]=0;
        fHistTrkDeDxPtLeft_EMC1[i]=0;
        fHistTrkDeDxPtLeft_EMC7[i]=0;
        fHistTrkDeDxPtLeft_EMC8[i]=0;
        fHistTrkDeDxPtLeft_EMCJet[i]=0;
            
        //Right Side Histos
        fHistTrkMultRight_MB[i]=0;
        fHistTrkMultRight_EMC1[i]=0;
        fHistTrkMultRight_EMC7[i]=0;
        fHistTrkMultRight_EMC8[i]=0;
        fHistTrkMultRight_EMCJet[i]=0;
           
        fHistTrkPtRight_MB[i]=0;
        fHistTrkPtRight_EMC1[i]=0;
        fHistTrkPtRight_EMC7[i]=0;
        fHistTrkPtRight_EMC8[i]=0;
        fHistTrkPtRight_EMCJet[i]=0;
        
        fHistTrkDeDxPtRight_MB[i]=0;
        fHistTrkDeDxPtRight_EMC1[i]=0;
        fHistTrkDeDxPtRight_EMC7[i]=0;
        fHistTrkDeDxPtRight_EMC8[i]=0;
        fHistTrkDeDxPtRight_EMCJet[i]=0;
    }
        
    DefineInput(1, TList::Class());//eIDexchange
    DefineOutput(1, TList::Class());//MB
    DefineOutput(2, TList::Class());//EMC1
    DefineOutput(3, TList::Class());//EMC7
    DefineOutput(4, TList::Class());//EMC8
    DefineOutput(5, TList::Class());//EMCJet
}

//________________________________________________________________________
AliAnalysisTaskEventChar::~AliAnalysisTaskEventChar()
{
    for(Int_t i=0;i<4;i++){
        //Tag Side Histos
        delete fHistTrkMultTag_MB[i];
        delete fHistTrkMultTag_EMC1[i];
        delete fHistTrkMultTag_EMC7[i];
        delete fHistTrkMultTag_EMC8[i];
        delete fHistTrkMultTag_EMCJet[i];
        
        delete fHistTrkPtTag_MB[i];
        delete fHistTrkPtTag_EMC1[i];
        delete fHistTrkPtTag_EMC7[i];
        delete fHistTrkPtTag_EMC8[i];
        delete fHistTrkPtTag_EMCJet[i];
          
        delete fHistTrkDeDxPtTag_MB[i];
        delete fHistTrkDeDxPtTag_EMC1[i];
        delete fHistTrkDeDxPtTag_EMC7[i];
        delete fHistTrkDeDxPtTag_EMC8[i];
        delete fHistTrkDeDxPtTag_EMCJet[i];
          
        //Away Side Histos
        delete fHistTrkMultAway_MB[i];
        delete fHistTrkMultAway_EMC1[i];
        delete fHistTrkMultAway_EMC7[i];
        delete fHistTrkMultAway_EMC8[i];
        delete fHistTrkMultAway_EMCJet[i];
        
        delete fHistTrkPtAway_MB[i];
        delete fHistTrkPtAway_EMC1[i];
        delete fHistTrkPtAway_EMC7[i];
        delete fHistTrkPtAway_EMC8[i];
        delete fHistTrkPtAway_EMCJet[i];
         
        delete fHistTrkDeDxPtAway_MB[i];
        delete fHistTrkDeDxPtAway_EMC1[i];
        delete fHistTrkDeDxPtAway_EMC7[i];
        delete fHistTrkDeDxPtAway_EMC8[i];
        delete fHistTrkDeDxPtAway_EMCJet[i];
            
        //Left Side Histos
        delete fHistTrkMultLeft_MB[i];
        delete fHistTrkMultLeft_EMC1[i];
        delete fHistTrkMultLeft_EMC7[i];
        delete fHistTrkMultLeft_EMC8[i];
        delete fHistTrkMultLeft_EMCJet[i];
        
        delete fHistTrkPtLeft_MB[i];
        delete fHistTrkPtLeft_EMC1[i];
        delete fHistTrkPtLeft_EMC7[i];
        delete fHistTrkPtLeft_EMC8[i];
        delete fHistTrkPtLeft_EMCJet[i];
        
        delete fHistTrkDeDxPtLeft_MB[i];
        delete fHistTrkDeDxPtLeft_EMC1[i];
        delete fHistTrkDeDxPtLeft_EMC7[i];
        delete fHistTrkDeDxPtLeft_EMC8[i];
        delete fHistTrkDeDxPtLeft_EMCJet[i];
        
        //Right Side Histos
        delete fHistTrkMultRight_MB[i];
        delete fHistTrkMultRight_EMC1[i];
        delete fHistTrkMultRight_EMC7[i];
        delete fHistTrkMultRight_EMC8[i];
        delete fHistTrkMultRight_EMCJet[i];
            
        delete fHistTrkPtRight_MB[i];
        delete fHistTrkPtRight_EMC1[i];
        delete fHistTrkPtRight_EMC7[i];
        delete fHistTrkPtRight_EMC8[i];
        delete fHistTrkPtRight_EMCJet[i];
            
        delete fHistTrkDeDxPtRight_MB[i];
        delete fHistTrkDeDxPtRight_EMC1[i];
        delete fHistTrkDeDxPtRight_EMC7[i];
        delete fHistTrkDeDxPtRight_EMC8[i];
        delete fHistTrkDeDxPtRight_EMCJet[i];
    }

}

//________________________________________________________________________
void AliAnalysisTaskEventChar::UserCreateOutputObjects()
{
    // Create histograms
    // Called once (on the worker node)
        
    fOutputMB = new TList();
    OpenFile(1);
    fOutputMB->SetOwner();  // IMPORTANT!
    fOutputEMC1 = new TList();
    OpenFile(2);
    fOutputEMC1->SetOwner();  // IMPORTANT!
    fOutputEMC7 = new TList();
    OpenFile(3);
    fOutputEMC7->SetOwner();  // IMPORTANT!
    fOutputEMC8 = new TList();
    OpenFile(4);
    fOutputEMC8->SetOwner();  // IMPORTANT!
    fOutputEMCJet = new TList();
    OpenFile(5);
    fOutputEMCJet->SetOwner();  // IMPORTANT!
    
    //Some strings for histograms
    TString ptRanges[4] = {"1-2Gev", "2-4Gev", "4-6Gev", ">6Gev"};
    
    
    for(Int_t i=0;i<4;i++){
           
           //Tag Side Histos
       
           //Multiplicity Histos
           fHistTrkMultTag_MB[i] = new TH1F(TString::Format("fHistTrkMultTag_MB_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultTag_MB[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultTag_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultTag_EMC1[i] = new TH1F(TString::Format("fHistTrkMultTag_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultTag_EMC1[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultTag_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultTag_EMC7[i] = new TH1F(TString::Format("fHistTrkMultTag_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultTag_EMC7[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultTag_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultTag_EMC8[i] = new TH1F(TString::Format("fHistTrkMultTag_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultTag_EMC8[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultTag_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultTag_EMCJet[i] = new TH1F(TString::Format("fHistTrkMultTag_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultTag_EMCJet[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultTag_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //Pt Histos
           fHistTrkPtTag_MB[i] = new TH1F(TString::Format("fHistTrkPtTag_MB_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtTag_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtTag_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtTag_EMC1[i] = new TH1F(TString::Format("fHistTrkPtTag_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtTag_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtTag_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtTag_EMC7[i] = new TH1F(TString::Format("fHistTrkPtTag_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtTag_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtTag_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtTag_EMC8[i] = new TH1F(TString::Format("fHistTrkPtTag_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtTag_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtTag_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtTag_EMCJet[i] = new TH1F(TString::Format("fHistTrkPtTag_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtTag_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtTag_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //DeDx by Pt Histos
           fHistTrkDeDxPtTag_MB[i] = new TH2F(TString::Format("fHistTrkDeDxPtTag_MB_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtTag_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtTag_MB[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtTag_EMC1[i] = new TH2F(TString::Format("fHistTrkDeDxPtTag_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtTag_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtTag_EMC1[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtTag_EMC7[i] = new TH2F(TString::Format("fHistTrkDeDxPtTag_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtTag_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtTag_EMC7[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtTag_EMC8[i] = new TH2F(TString::Format("fHistTrkDeDxPtTag_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtTag_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtTag_EMC8[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtTag_EMCJet[i] = new TH2F(TString::Format("fHistTrkDeDxPtTag_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Tag Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtTag_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtTag_EMCJet[i]->GetYaxis()->SetTitle("TPC dE/dx");
        
           //Away Side Histos
       
           //Multiplicity Histos
           fHistTrkMultAway_MB[i] = new TH1F(TString::Format("fHistTrkMultAway_MB_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultAway_MB[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultAway_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultAway_EMC1[i] = new TH1F(TString::Format("fHistTrkMultAway_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultAway_EMC1[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultAway_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultAway_EMC7[i] = new TH1F(TString::Format("fHistTrkMultAway_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultAway_EMC7[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultAway_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultAway_EMC8[i] = new TH1F(TString::Format("fHistTrkMultAway_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultAway_EMC8[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultAway_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultAway_EMCJet[i] = new TH1F(TString::Format("fHistTrkMultAway_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultAway_EMCJet[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultAway_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //Pt Histos
           fHistTrkPtAway_MB[i] = new TH1F(TString::Format("fHistTrkPtAway_MB_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtAway_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtAway_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtAway_EMC1[i] = new TH1F(TString::Format("fHistTrkPtAway_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtAway_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtAway_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtAway_EMC7[i] = new TH1F(TString::Format("fHistTrkPtAway_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtAway_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtAway_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtAway_EMC8[i] = new TH1F(TString::Format("fHistTrkPtAway_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtAway_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtAway_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtAway_EMCJet[i] = new TH1F(TString::Format("fHistTrkPtAway_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtAway_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtAway_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //DeDx by Pt Histos
           fHistTrkDeDxPtAway_MB[i] = new TH2F(TString::Format("fHistTrkDeDxPtAway_MB_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtAway_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtAway_MB[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtAway_EMC1[i] = new TH2F(TString::Format("fHistTrkDeDxPtAway_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtAway_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtAway_EMC1[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtAway_EMC7[i] = new TH2F(TString::Format("fHistTrkDeDxPtAway_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtAway_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtAway_EMC7[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtAway_EMC8[i] = new TH2F(TString::Format("fHistTrkDeDxPtAway_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtAway_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtAway_EMC8[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtAway_EMCJet[i] = new TH2F(TString::Format("fHistTrkDeDxPtAway_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Away Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtAway_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtAway_EMCJet[i]->GetYaxis()->SetTitle("TPC dE/dx");
        
           //Left Side Histos
       
           //Multiplicity Histos
           fHistTrkMultLeft_MB[i] = new TH1F(TString::Format("fHistTrkMultLeft_MB_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultLeft_MB[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultLeft_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultLeft_EMC1[i] = new TH1F(TString::Format("fHistTrkMultLeft_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultLeft_EMC1[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultLeft_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultLeft_EMC7[i] = new TH1F(TString::Format("fHistTrkMultLeft_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultLeft_EMC7[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultLeft_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultLeft_EMC8[i] = new TH1F(TString::Format("fHistTrkMultLeft_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultLeft_EMC8[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultLeft_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultLeft_EMCJet[i] = new TH1F(TString::Format("fHistTrkMultLeft_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultLeft_EMCJet[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultLeft_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //Pt Histos
           fHistTrkPtLeft_MB[i] = new TH1F(TString::Format("fHistTrkPtLeft_MB_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtLeft_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtLeft_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtLeft_EMC1[i] = new TH1F(TString::Format("fHistTrkPtLeft_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtLeft_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtLeft_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtLeft_EMC7[i] = new TH1F(TString::Format("fHistTrkPtLeft_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtLeft_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtLeft_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtLeft_EMC8[i] = new TH1F(TString::Format("fHistTrkPtLeft_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtLeft_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtLeft_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtLeft_EMCJet[i] = new TH1F(TString::Format("fHistTrkPtLeft_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtLeft_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtLeft_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //DeDx by Pt Histos
           fHistTrkDeDxPtLeft_MB[i] = new TH2F(TString::Format("fHistTrkDeDxPtLeft_MB_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtLeft_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtLeft_MB[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtLeft_EMC1[i] = new TH2F(TString::Format("fHistTrkDeDxPtLeft_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtLeft_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtLeft_EMC1[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtLeft_EMC7[i] = new TH2F(TString::Format("fHistTrkDeDxPtLeft_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtLeft_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtLeft_EMC7[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtLeft_EMC8[i] = new TH2F(TString::Format("fHistTrkDeDxPtLeft_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtLeft_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtLeft_EMC8[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtLeft_EMCJet[i] = new TH2F(TString::Format("fHistTrkDeDxPtLeft_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Left Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtLeft_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtLeft_EMCJet[i]->GetYaxis()->SetTitle("TPC dE/dx");
            
           //Right Side Histos
       
           //Multiplicity Histos
           fHistTrkMultRight_MB[i] = new TH1F(TString::Format("fHistTrkMultRight_MB_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultRight_MB[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultRight_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultRight_EMC1[i] = new TH1F(TString::Format("fHistTrkMultRight_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultRight_EMC1[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultRight_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultRight_EMC7[i] = new TH1F(TString::Format("fHistTrkMultRight_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultRight_EMC7[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultRight_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultRight_EMC8[i] = new TH1F(TString::Format("fHistTrkMultRight_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultRight_EMC8[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultRight_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkMultRight_EMCJet[i] = new TH1F(TString::Format("fHistTrkMultRight_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Multiplicity of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 400, 0, 400);
           fHistTrkMultRight_EMCJet[i]->GetXaxis()->SetTitle("Track Multiplicity");
           fHistTrkMultRight_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //Pt Histos
           fHistTrkPtRight_MB[i] = new TH1F(TString::Format("fHistTrkPtRight_MB_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtRight_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtRight_MB[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtRight_EMC1[i] = new TH1F(TString::Format("fHistTrkPtRight_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtRight_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtRight_EMC1[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtRight_EMC7[i] = new TH1F(TString::Format("fHistTrkPtRight_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtRight_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtRight_EMC7[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtRight_EMC8[i] = new TH1F(TString::Format("fHistTrkPtRight_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtRight_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtRight_EMC8[i]->GetYaxis()->SetTitle("Cts");
       
           fHistTrkPtRight_EMCJet[i] = new TH1F(TString::Format("fHistTrkPtRight_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("Pt Distribution of Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8);
           fHistTrkPtRight_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkPtRight_EMCJet[i]->GetYaxis()->SetTitle("Cts");
            
           //DeDx by Pt Histos
           fHistTrkDeDxPtRight_MB[i] = new TH2F(TString::Format("fHistTrkDeDxPtRight_MB_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtRight_MB[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtRight_MB[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtRight_EMC1[i] = new TH2F(TString::Format("fHistTrkDeDxPtRight_EMC1_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtRight_EMC1[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtRight_EMC1[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtRight_EMC7[i] = new TH2F(TString::Format("fHistTrkDeDxPtRight_EMC7_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtRight_EMC7[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtRight_EMC7[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtRight_EMC8[i] = new TH2F(TString::Format("fHistTrkDeDxPtRight_EMC8_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtRight_EMC8[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtRight_EMC8[i]->GetYaxis()->SetTitle("TPC dE/dx");
       
           fHistTrkDeDxPtRight_EMCJet[i] = new TH2F(TString::Format("fHistTrkDeDxPtRight_EMCJet_%s", ptRangesRegion[i].Data()), TString::Format("DeDx by Pt for Tracks on the Right Side of Event with a %s pt electron", ptRangesRegion[i].Data()), 800, 0, 8, 300, -5, 50);
           fHistTrkDeDxPtRight_EMCJet[i]->GetXaxis()->SetTitle("Track Pt");
           fHistTrkDeDxPtRight_EMCJet[i]->GetYaxis()->SetTitle("TPC dE/dx");
    }
    
    for(Int_t i=0;i<4;i++){
        
        //Tag Side Histos
        
        //Multiplicity Histos
        fOutputMB->Add(fHistTrkMultTag_MB[i]);
        fOutputEMC1->Add(fHistTrkMultTag_EMC1[i]);
        fOutputEMC7->Add(fHistTrkMultTag_EMC7[i]);
        fOutputEMC8->Add(fHistTrkMultTag_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkMultTag_EMCJet[i]);
        
        //Pt Histos
        fOutputMB->Add(fHistTrkPtTag_MB[i]);
        fOutputEMC1->Add(fHistTrkPtTag_EMC1[i]);
        fOutputEMC7->Add(fHistTrkPtTag_EMC7[i]);
        fOutputEMC8->Add(fHistTrkPtTag_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkPtTag_EMCJet[i]);
        
        //DeDx by Pt Histos
        fOutputMB->Add(fHistTrkDeDxPTag_MB[i]);
        fOutputEMC1->Add(fHistTrkDeDxPtTag_EMC1[i]);
        fOutputEMC7->Add(fHistTrkDeDxPtTag_EMC7[i]);
        fOutputEMC8->Add(fHistTrkDeDxPtTag_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkDeDxPtTag_EMCJet[i]);
        
        //Away Side Histos
        
        //Multiplicity Histos
        fOutputMB->Add(fHistTrkMultAway_MB[i]);
        fOutputEMC1->Add(fHistTrkMultAway_EMC1[i]);
        fOutputEMC7->Add(fHistTrkMultAway_EMC7[i]);
        fOutputEMC8->Add(fHistTrkMultAway_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkMultAway_EMCJet[i]);
        
        //Pt Histos
        fOutputMB->Add(fHistTrkPtAway_MB[i]);
        fOutputEMC1->Add(fHistTrkPtAway_EMC1[i]);
        fOutputEMC7->Add(fHistTrkPtAway_EMC7[i]);
        fOutputEMC8->Add(fHistTrkPtAway_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkPtAway_EMCJet[i]);
        
        //DeDx by Pt Histos
        fOutputMB->Add(fHistTrkDeDxPAway_MB[i]);
        fOutputEMC1->Add(fHistTrkDeDxPtAway_EMC1[i]);
        fOutputEMC7->Add(fHistTrkDeDxPtAway_EMC7[i]);
        fOutputEMC8->Add(fHistTrkDeDxPtAway_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkDeDxPtAway_EMCJet[i]);
        
        //Left Side Histos
        
        //Multiplicity Histos
        fOutputMB->Add(fHistTrkMultLeft_MB[i]);
        fOutputEMC1->Add(fHistTrkMultLeft_EMC1[i]);
        fOutputEMC7->Add(fHistTrkMultLeft_EMC7[i]);
        fOutputEMC8->Add(fHistTrkMultLeft_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkMultLeft_EMCJet[i]);
        
        //Pt Histos
        fOutputMB->Add(fHistTrkPtLeft_MB[i]);
        fOutputEMC1->Add(fHistTrkPtLeft_EMC1[i]);
        fOutputEMC7->Add(fHistTrkPtLeft_EMC7[i]);
        fOutputEMC8->Add(fHistTrkPtLeft_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkPtLeft_EMCJet[i]);
        
        //DeDx by Pt Histos
        fOutputMB->Add(fHistTrkDeDxPLeft_MB[i]);
        fOutputEMC1->Add(fHistTrkDeDxPtLeft_EMC1[i]);
        fOutputEMC7->Add(fHistTrkDeDxPtLeft_EMC7[i]);
        fOutputEMC8->Add(fHistTrkDeDxPtLeft_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkDeDxPtLeft_EMCJet[i]);
        
        //Right Side Histos
        
        //Multiplicity Histos
        fOutputMB->Add(fHistTrkMultRight_MB[i]);
        fOutputEMC1->Add(fHistTrkMultRight_EMC1[i]);
        fOutputEMC7->Add(fHistTrkMultRight_EMC7[i]);
        fOutputEMC8->Add(fHistTrkMultRight_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkMultRight_EMCJet[i]);
        
        //Pt Histos
        fOutputMB->Add(fHistTrkPtRight_MB[i]);
        fOutputEMC1->Add(fHistTrkPtRight_EMC1[i]);
        fOutputEMC7->Add(fHistTrkPtRight_EMC7[i]);
        fOutputEMC8->Add(fHistTrkPtRight_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkPtRight_EMCJet[i]);
        
        //DeDx by Pt Histos
        fOutputMB->Add(fHistTrkDeDxPRight_MB[i]);
        fOutputEMC1->Add(fHistTrkDeDxPtRight_EMC1[i]);
        fOutputEMC7->Add(fHistTrkDeDxPtRight_EMC7[i]);
        fOutputEMC8->Add(fHistTrkDeDxPtRight_EMC8[i]);
        fOutputEMCJet->Add(fHistTrkDeDxPtRight_EMCJet[i]);
    }
    
    PostData(1, fOutputMB);
    PostData(2, fOutputEMC1);
    PostData(3, fOutputEMC7);
    PostData(4, fOutputEMC8);
    PostData(5, fOutputEMCJet);
}

//________________________________________________________________________
void AliAnalysisTaskEventChar::ConnectInputData()
{
    feIDexchange = dynamic_cast<TList*>(GetInputData(1));
    
    if(!feIDexchange){
        AliError("The exchange container is null, you did something wrong!");
    }      
}

//________________________________________________________________________
void AliAnalysisTaskEventChar::UserExec(Option_t *) 
{
    // Main loop
    // Called for each event
        
    //_______________________________Major event-level stuff____________________________________
    // Create pointer to reconstructed event
    AliVEvent *event = InputEvent();
    if (!event) { Printf("ERROR: Could not retrieve event"); return; }
        
    // create pointer to event
    AliESDEvent* esd = dynamic_cast<AliESDEvent*>(event);
    if (!esd) {
        AliError("Cannot get the ESD event");
        return;
    }  
    
    // input handler
  const AliAnalysisManager* man(AliAnalysisManager::GetAnalysisManager());
  if (NULL == man) {
    AliWarning("AliAnalysisManager is not available");
    return;
  }

  AliESDInputHandler* inputHandler(dynamic_cast<AliESDInputHandler*>(man->GetInputEventHandler()));  
  if (NULL == inputHandler) {
    AliWarning("AliESDInputHandler is not available");
    return;
  }

  UInt_t fSelectMask = inputHandler->IsEventSelected();
  Bool_t isSelected = fSelectMask & (AliVEvent::kEMC7 | AliVEvent::kEMC1 | AliVEvent::kEMCEJE | AliVEvent::kEMC8);
  if(isSelected){
        AliWarning("This is not an EMCal triggered event");
  }
    
  
  Bool_t EMC1trg = fSelectMask & AliVEvent::kEMC1;
  Bool_t EMC7trg = fSelectMask & AliVEvent::kEMC7;
  Bool_t EMC8trg = fSelectMask & AliVEvent::kEMC8;
  Bool_t EMCJettrg = fSelectMask & AliVEvent::kEMCEJE;
  
    
    
  AliPIDResponse* fPIDResponse = inputHandler->GetPIDResponse();
      if(!fPIDResponse){
        AliWarning("NULL PIDResponse");}
    
    //__________________________End major event stuff_____________________________
    
    //__________________Event filtering from previous tasks_______________________
    TList *evtIDs = feIDexchange->At(0);//Get tagged Event IDs
    
    TList *elecTrkIDs = feIDexchange->At(1);//Get tracks tagged as electrons' IDs
    
    if(!evtIDs){
        
        AliError("Cannot retrieve tagged event IDs, returning");
        
        return;
        
    }
    
    if(!elecTrkIDs){
        
        AliError("Cannot retrieve electron track IDs, returning");
        
        return;
        
    }
    
    Bool_t eventTag = kFALSE;
    
    Int_t nEvtIDs = evtIDs->LastIndex();
    
    for(Int_t i=0;i<nEvtIDs;i++){
        
        if(esd->GetEventNumberInFile()!=evtIDs->At(i)){
            
            continue;
            
        }
        
        else{
            
            eventTag=kTRUE;
            
            break;
        
        }
    }
        
    if(!eventTag){
        
        AliError("This is not a tagged event, returning");
        
        return; 
        
    }
    
    
    //___________________________End______________________________________________
    Int_t ntracks = esd->GetNumberOfTracks();
    
    for(Int_t i=0;i<ntracks;i++){
        
        AliESDtrack* esdtrack = esd->GetTrack(i);
        
        AliESDtrack* elecCandTrack = esd->GetTrack(//TODO figure out how to tell not only the ID of electrons but which event they belong to.
    
    
}


//________________________________________________________________________
void AliAnalysisTaskEventChar::Terminate(Option_t *) 
{
    
}