
#include "TChain.h"
#include "TTree.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TColor.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"

#include "AliESDEvent.h"
#include "AliESDInputHandler.h"
#include "AliESDTZERO.h"
#include "AliESDInputHandlerRP.h"
#include "AliESDtrack.h"
#include "AliTOFcluster.h"
#include "AliCluster.h"
#include "AliTOFGeometry.h"

#include "AliAnalysisTaskSanity.h"

// example of an analysis task creating a p_t spectrum
// Authors: Panos Cristakoglou, Jan Fiete Grosse-Oetringhaus, Christian Klein-Boesing
// Reviewed: A.Gheata (19/02/10)

ClassImp(AliAnalysisTaskSanity)

//________________________________________________________________________
AliAnalysisTaskSanity::AliAnalysisTaskSanity(const char *name) 
: AliAnalysisTaskSE(name), fESD(0), fOutputList(0),fHistTrackTOFId(0),fHistTrackEMId(0), fHistEMClus(0), fHistTOFClus(0)
{
  // Constructor
  

  // Define input and output slots here
  // Input slot #0 works with a TChain
  DefineInput(0, TChain::Class());
  // Output slot #0 id reserved by the base class for AOD
  // Output slot #1 writes into a TH1 container
  DefineOutput(1, TList::Class());
}


//________________________________________________________________________
AliAnalysisTaskSanity::AliAnalysisTaskSanity() 
  : AliAnalysisTaskSE(), fESD(0), fOutputList(0),fHistTrackTOFId(0),fHistTrackEMId(0), fHistEMClus(0), fHistTOFClus(0)
{
  // Default Constructor

  
}

//________________________________________________________________________
void AliAnalysisTaskSanity::UserCreateOutputObjects()
{
  // Create histograms
  // Called once

  fOutputList = new TList();
  fOutputList->SetOwner(); // otherwise it produces leaks in merging
  
  fHistTrackTOFId = new TH1F("fHistTrackTOFId", "TOF Ids associated with all tracks",1000,-1,999);
  fHistTrackTOFId->GetXaxis()->SetTitle("ID");
  fHistTrackTOFId->GetYaxis()->SetTitle("Count");

  fHistTrackEMId = new TH1F("fHistTrackEMId", "EMCal Ids associated with all tracks", 1000,-1,999);
  fHistTrackEMId->GetXaxis()->SetTitle("ID");
  fHistTrackEMId->GetYaxis()->SetTitle("Count");

  fHistEMClus = new TH1F("fHistEMClus", "Energy distribution for matched tracks", 100, 0,10);
  fHistEMClus->GetXaxis()->SetTitle("Energy");
  fHistEMClus->GetYaxis()->SetTitle("Counts");
  
  fHistTOFClus = new TH2F("fHistTOFClus", "R-Phi distribution of matched TOF clusters", 100, 0,2*3.14159, 100, -9,9);
  fHistTOFClus->GetXaxis()->SetTitle("Phi");
  fHistTOFClus->GetYaxis()->SetTitle("R");
  
  fOutputList->Add(fHistTrackEMId);
  fOutputList->Add(fHistTrackTOFId);
  fOutputList->Add(fHistTOFClus);
  fOutputList->Add(fHistEMClus);

  
  PostData(1,fOutputList); // important for merging
}

//________________________________________________________________________
void AliAnalysisTaskSanity::UserExec(Option_t *) 
{
  // Main loop
  // Called for each event

  if (!fInputEvent) {
    printf("ERROR: Input event not available\n");
    return;
  }
  // Get rec points
  AliESDInputHandlerRP *handler = 
    dynamic_cast<AliESDInputHandlerRP*>(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
  if (!handler) { printf("No RP handler\n"); return; }
  AliESDEvent *esd  = handler->GetEvent();
  if (!esd) { printf("No AliESDEvent\n"); return; }
  
  TTree* tofClusterTree = handler->GetTreeR("TOF");
  TTree* Tree = handler->GetTreeR("TOF");
  if (!tofClusterTree) {printf("<WARN>No TOF clusters!\n");return;}
  
  TBranch* tofClusterBranch = tofClusterTree->GetBranch("TOF");
  if (!tofClusterBranch) {printf("Can't get the branch with the TOF digits !\n"); return;}
  
  TClonesArray dummy("AliESDTOFCluster",1000), * tofClusters = &dummy; tofClusterBranch->SetAddress(&tofClusters);
  TRefArray* emClusters = new TRefArray; 
  esd->GetEMCALClusters(emClusters);
  
  
  Int_t nClusters = tofClusters->GetEntriesFast();
  
  tofClusterTree->GetEvent(0);
  
  Int_t nesdtracks = esd->GetNumberOfTracks();
  
  for(int i=0;i<nesdtracks;i++){
  AliESDtrack* esdtrk = (AliESDtrack*)esd->GetTrack(i);
  fHistTrackEMId->Fill(esdtrk->GetEMCALcluster());
  fHistTrackTOFId->Fill(esdtrk->GetTOFcluster());
  AliESDCaloCluster* emclus = new AliESDCaloCluster();
  emclus->SetID(esdtrk->GetEMCALcluster());
  fHistEMClus->Fill(emclus->E());
  }
  
  for(int i=0;i<nClusters;i++){
  AliESDTOFCluster* tofclus = (AliESDTOFCluster*)tofClusters->At(i);
  fHistTOFClus->Fill(tofclus->GetPhi(), tofclus->GetR());
  }
  
  
  PostData(1, fOutputList);
  
}

//________________________________________________________________________
void AliAnalysisTaskSanity::Terminate(Option_t *) 
{
  // Draw result to the screen
  // Called once at the end of the query
  printf("is it here?");
  fOutputList = dynamic_cast<TList*> (GetOutputData(1));
  if (!fOutputList) {printf("ERROR: Output list not available\n");return;}
  
}
