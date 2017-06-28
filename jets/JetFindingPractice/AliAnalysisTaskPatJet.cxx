#include <TClonesArray.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TList.h>

#include <AliVCluster.h>
#include <AliVParticle.h>
#include <AliLog.h>

#include "AliTLorentzVector.h"
#include "AliEmcalJet.h"
#include "AliJetContainer.h"
#include "AliParticleContainer.h"
#include "AliClusterContainer.h"    

#include "AliAnalysisTaskPatJet.h"
    
ClassImp(AliAnalysisTaskPatJet);
    
AliAnalysisTaskPatJet::AliAnalysisTaskPatJet() : AliAnalysisTaskEmcalJet(),
  fHistManager()
{
}

AliAnalysisTaskPatJet::AliAnalysisTaskPatJet(const char *name) : AliAnalysisTaskEmcalJet(name, kTRUE),
  fHistManager(name)
{
}

AliAnalysisTaskPatJet::~AliAnalysisTaskPatJet()
{
}

void AliAnalysisTaskPatJet::UserCreateOutputObjects()
{
    AliAnalysisTaskEmcalJet::UserCreateOutputObjects();
    
    InitJetHistos();
    InitTrackHistos();
    InitClusterHistos();
    TIter next(fHistManager.GetListOfHistograms());
    TObject* obj = 0;
    while ((obj = next())) {
        fOutput->Add(obj);
    }
  
    PostData(1, fOutput);
}

Bool_t AliAnalysisTaskPatJet::FillHistograms()
{
    FillJetHistos();
    FillTrackHistos();
    FillClusterHistos();
    
    return kTRUE;
}

void AliAnalysisTaskPatJet::ExecOnce()
{
    AliAnalysisTaskEmcalJet::ExecOnce();
}

Bool_t AliAnalysisTaskPatJet::Run()
{
    return kTRUE;
}

void AliAnalysisTaskPatJet::InitJetHistos()
{
    Int_t NBins = 100;
    
    TString histoName;
    TString histoTitle;
    TString groupName;
    
    AliJetContainer* jetCont = 0;
    TIter nextJet(&fJetCollArray);
    
    while((jetCont = static_cast<AliJetContainer*>(nextJet()))){
        groupName = jetCont->GetName();

        fHistManager.CreateHistoGroup(groupName);
        
        histoName = TString::Format("%s/jetPt", groupName.Data());
        histoTitle = TString::Format("Jet Pt Distribution");
        fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 10);
    }
    
}

void AliAnalysisTaskPatJet::InitTrackHistos()
{}

void AliAnalysisTaskPatJet::InitClusterHistos()
{}

void AliAnalysisTaskPatJet::FillJetHistos()
{
    TString histoName;
    TString groupName;
    
    AliJetContainer* jetCont = 0;
    
    TIter nextJet(&fJetCollArray);
    
    while((jetCont = static_cast<AliJetContainer*>(nextJet()))) {
        groupName = jetCont->GetName();
        
        for(auto jet : jetCont->accepted()){
            if(!jet) continue;
            histoName = TString::Format("%s/jetPt", groupName.Data());
            fHistManager.FillTH1(histoName, jet->Pt());
        }  
    }
}

void AliAnalysisTaskPatJet::FillTrackHistos()
{}

void AliAnalysisTaskPatJet::FillClusterHistos()
{}

void AliAnalysisTaskPatJet::Terminate(Option_t *)
{}
