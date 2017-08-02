#include<vector>
    #include <TClonesArray.h>
    #include <TH1F.h>
    #include <TH2F.h>
    #include <TList.h>

    #include <AliVCluster.h>
    #include <AliVParticle.h>
    #include <AliLog.h>
    #include <math.h>


    #include "AliAnalysisTaskPatJet.h"

    #include "AliEmcalJet.h"
    #include "AliJetContainer.h"
    #include "AliParticleContainer.h"
    #include "AliClusterContainer.h"
    #include "AliAODTrack.h"
    #include "AliAODCluster.h"
    #include "AliAnalysisTaskPatJet.h"
    #include "AliPIDResponse.h"
    #include "AliInputEventHandler.h"
    #include "AliAnalysisManager.h"
    #include "AliAODCaloCluster.h"
    #include "AliAODEvent.h"


    /// \cond CLASSIMP
    ClassImp(AliAnalysisTaskPatJet);
/// \endcond

using namespace std;


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

void AliAnalysisTaskPatJet::UserCreateOutputObjects() //overloading
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

Bool_t AliAnalysisTaskPatJet::FillHistograms() //overloading
{

    //get event
    AliAODEvent *aod = (AliAODEvent*)InputEvent();
    if (!aod) { Printf("ERROR: Could not retrieve event");}

    //get manager
    const AliAnalysisManager* man(AliAnalysisManager::GetAnalysisManager());
    AliInputEventHandler* inputHandler = (AliInputEventHandler*)man->GetInputEventHandler();

    //get PID response for HFe check
    AliPIDResponse* fPIDResponse = (AliPIDResponse*)inputHandler->GetPIDResponse();


    FillJetHistos(aod, fPIDResponse);
    FillTrackHistos();
    FillClusterHistos();

    return kTRUE;
}

void AliAnalysisTaskPatJet::ExecOnce() //overloading
{
    AliAnalysisTaskEmcalJet::ExecOnce();
}

Bool_t AliAnalysisTaskPatJet::Run() //overloading
{
    return kTRUE;
}

void AliAnalysisTaskPatJet::InitJetHistos()
{
    Int_t NBins = 40; //placeholder until I can think of appropriate binning

    TString histoName;
    TString histoTitle;
    TString groupName[3];//elec leading and had leading
    TString radName[3];//jet radii

    AliJetContainer* jetCont = 0; 
    TIter nextJet(&fJetCollArray); //Iterate over the jet collections in fjetcollarray

    groupName[0] = TString("AsJet_ElecLeading");
    groupName[1] = TString("AsJet_HadronLeading");//this should technically also be muons
    groupName[2] = TString("Ratios_Ave");//Fill by taking ratios of As_Jet Plots

    radName[0] = TString("R02");
    radName[1] = TString("R04");
    radName[2] = TString("R07");

    Double_t PtTemp[21] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,34,38,44,50,58};

    Double_t MaxChPtTemp[12] = {0,2,4,6,8,10,12,14,16,20,24,30};

    Double_t AreaTemp[40] = {0, 1/40., 2/40., 3/40., 4/40., 5/40., 6/40., 7/40., 8/40., 9/40., 10/40., 11/40., 12/40., 13/40., 14/40., 15/40., 16/40., 17/40., 18/40., 19/40., 20/40., 21/40., 22/40., 23/40., 24/40., 25/40., 26/40., 27/40., 28/40., 29/40., 30/40., 31/40., 32/40., 33/40., 34/40., 35/40., 36/40., 37/40., 38/40., 39/40.};

    Double_t NchTemp[30] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};

    Double_t GQCTemp[40] = {0, .005, .01, .015, .02, .025, .03, .035, .04, .045, .05, .055, .06, .065, .07, .075, .08, .085, .09, .095, .1, .105, .11, .115, .12, .125, .13, .135, .14, .145, .15, .155, .16, .165, .17, .175, .18, .185, .19, .195};

    Double_t LFTemp[40] = {0, 1.3/40., 2.6/40., 3.9/40., 5.2/40., 6.5/40., 7.8/40., 9.1/40., 10.4/40., 11.7/40., 13/40., 14.3/40., 15.6/40., 16.9/40., 18.2/40., 19.5/40., 20.8/40., 22.1/40., 23.4/40., 24.7/40., 26/40., 27.3/40., 28.6/40., 29.9/40., 31.2/40., 32.5/40., 33.8/40., 35.1/40., 36.4/40., 37.7/40., 39/40., 40.3/40., 41.6/40., 42.9/40., 44.2/40., 45.5/40., 46.8/40., 48.1/40., 49.4/40., 50.7/40.};

    TArrayD* PtBins = new TArrayD(21, PtTemp);
    TArrayD* MaxChPtBins = new TArrayD(12, MaxChPtTemp);
    TArrayD* AreaBins = new TArrayD(40, AreaTemp);
    TArrayD* NchBins = new TArrayD(30, NchTemp);
    TArrayD* GBins = new TArrayD(40, GQCTemp);
    TArrayD* CBins= new TArrayD(40, GQCTemp);
    TArrayD* QBins= new TArrayD(40, GQCTemp);
    TArrayD* LeadingFracBins = new TArrayD(40, LFTemp);



    for(Int_t i=0; i<3;i++){

        fHistManager.CreateHistoGroup(groupName[i]); //Make folders foreach group of histos

    }

    //Init plots for away side jets
    for(Int_t i=0;i<3;i++){
        for(Int_t j=0;j<3;j++){

            //jet area
            histoName = TString::Format("%s/%s/Area", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet area for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *AreaBins);

            //jet energy
            histoName = TString::Format("%s/%s/E", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet Energy for away side jets(Calculated using jet mass)");
            fHistManager.CreateTH1(histoName, histoTitle, *PtBins);

            //
            histoName = TString::Format("%s/%s/Pt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet Pt for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *PtBins);

            histoName = TString::Format("%s/%s/Nch", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Charged particle multiplicity for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *NchBins);

            histoName = TString::Format("%s/%s/M", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet mass for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, .01);

            histoName = TString::Format("%s/%s/MaxChPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Pt of leading charged constituent for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *MaxChPtBins);

            histoName = TString::Format("%s/%s/Girth", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Girth or first geometric moment for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *GBins);

            histoName = TString::Format("%s/%s/QMoment", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Quadratic geometric moment for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *QBins);

            histoName = TString::Format("%s/%s/CMoment", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Cubic geometric moment for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *CBins);

            histoName = TString::Format("%s/%s/Angularity", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Angularity vs. parameter a for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, NBins, -2, 2, NBins, 0, 1);

            histoName = TString::Format("%s/%s/AngularityDeriv", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Derivative of angularity vs. parameter a for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, NBins, -2, 2, NBins, 0, 1);

            histoName = TString::Format("%s/%s/LeadingPtFraction", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Leading particle pT fraction for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, *LeadingFracBins);

            histoName = TString::Format("%s/%s/tracks/DCA", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("DCA for tracks in away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, -10, 10);

            histoName = TString::Format("%s/%s/tracks/Length", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Length for tracks in away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 5);

            histoName = TString::Format("%s/%s/tracks/Pt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Pt for tracks in away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 30);

            histoName = TString::Format("%s/%s/tracks/dEdx", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("dEdx by Pt for tracks in away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, NBins*2, 0, 50, NBins, -30, 180);

            //by Pt histos
            //jet area
            histoName = TString::Format("%s/%s/AreaByPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet area vs Jet Pt for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *AreaBins);

            histoName = TString::Format("%s/%s/NchByPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Charged particle multiplicity vs Jet Pt for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *NchBins);

            histoName = TString::Format("%s/%s/MaxChPtByPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Pt of leading charged constituent vs Jet Pt for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *MaxChPtBins);

            histoName = TString::Format("%s/%s/GirthByPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Girth or first geometric moment vs Jet Pt for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *GBins);

            histoName = TString::Format("%s/%s/QMomentByPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Quadratic geometric moment vs Jet Ptfor away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *QBins);

            histoName = TString::Format("%s/%s/CMomentByPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Cubic geometric moment vs Jet Pt for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *CBins);

            histoName = TString::Format("%s/%s/LeadingPtFractionByPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Leading particle pT fraction vs Jet Pt for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *LeadingFracBins);

            //Moments
            for(Int_t n=0;n<11;n++){
                for(Int_t m=0;m<11;m++){
                    histoName = TString::Format("%s/%s/Moments/M%d%d", groupName[i].Data(), radName[j].Data(), n, m);
                    histoTitle = TString::Format("M%d%d", n, m);
                    fHistManager.CreateTH2(histoName, histoTitle, *PtBins, *NchBins);
                }
            }

        }
    }

    for(Int_t j=0;j<3;j++){
        histoName = TString::Format("%s/%s/tracks/LeadingFInvMassLS", groupName[0].Data(), radName[j].Data());
        histoTitle = TString::Format("Invariant mass of leading electron with like-signed constituents for leading full jet");
        fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 30);

        histoName = TString::Format("%s/%s/tracks/LeadingFInvMassULS", groupName[0].Data(), radName[j].Data());
        histoTitle = TString::Format("Invariant mass of leading electron with unlike-signed constituents for leading full jet");
        fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 30);

        histoName = TString::Format("%s/%s/HFERejection", groupName[0].Data(), radName[j].Data());
        histoTitle = TString::Format("Number of leading electrons in leading full jet that would pass HFE cuts");
        fHistManager.CreateTH1(histoName, histoTitle, 2, 0, 2);
        ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(1, "Passed");
        ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(2, "Failed");
    }


    //Histo to demonstrate what the leading particle of the jet in the emcal acceptance is in events with back to back jets

    histoName = TString::Format("B2BEvLeadType");
    histoTitle = TString::Format("PID of leading particle of full jet in back to back events");
    fHistManager.CreateTH1(histoName, histoTitle, 6, 0, 6);
    ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(1, "Electron");
    ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(2, "Muon");
    ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(3, "Pion");
    ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(4, "Kaon");
    ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(5, "Proton");
    ((TH1*)fHistManager.FindObject(histoName))->GetXaxis()->SetBinLabel(6, "Other");



    histoName = TString::Format("JetPt");
    histoTitle = TString::Format("Pt spectrum of all jets");
    fHistManager.CreateTH1(histoName, histoTitle, 50, 0, 100);


    PostData(1, fOutput);

}

void AliAnalysisTaskPatJet::InitTrackHistos()
{}

void AliAnalysisTaskPatJet::InitClusterHistos()
{}

void AliAnalysisTaskPatJet::FillJetHistos(AliAODEvent* aod, AliPIDResponse* fPIDResponse )
{
    TString histoName;
    TString groupName[3];
    TString radName[3];

    AliJetContainer* jetCont = 0;
    AliJetContainer* jetContFull = 0;
    AliJetContainer* jetContCharge = 0;
    AliClusterContainer* clusCont = GetClusterContainer(0);

    UInt_t jetCntFull[3] = {0,0,0};
    UInt_t jetCntCharged[3] = {0,0,0};

    Double_t PhiFull = -99;
    Double_t PhiCharge = -99;

    TIter jetCounter(&fJetCollArray);
    TIter nextJet(&fJetCollArray);

    groupName[0] = TString("AsJet_ElecLeading");
    groupName[1] = TString("AsJet_HadronLeading");//this should technically also be muons
    groupName[2] = TString("Ratios_Ave");//Fill by taking ratios of As_Jet Plots

    radName[0] = TString("R02");
    radName[1] = TString("R04");
    radName[2] = TString("R07");

    std::vector<AliEmcalJet*> leadingB2BC(3, NULL);
    std::vector<AliEmcalJet*> leadingB2BF(3, NULL);

    Double_t a_vals[100];
    for(Int_t ind=0;ind<100;ind++){
        a_vals[ind] = ((Double_t)ind)/25-2;
    }

    //Count the number of charged and full jets
    while((jetCont = static_cast<AliJetContainer*>(jetCounter()))) {


        //R02
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R02")==kTRUE){
            jetContFull = jetCont;
            for(auto jet : jetContFull->accepted()){
                if(!jet) continue;
                jetCntFull[0]++;//keeping track of # of jets in event
            }
        }

        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R02")==kTRUE){
            jetContCharge = jetCont;
            for(auto jet : jetContCharge->accepted()){
                if(!jet) continue;
                jetCntCharged[0]++;//keeping track of # of jets in event
            }
        }


        //R04
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R04")==kTRUE){
            jetContFull = jetCont;
            for(auto jet : jetContFull->accepted()){
                if(!jet) continue;
                jetCntFull[1]++;//keeping track of # of jets in event
            }
        }

        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R04")==kTRUE){
            jetContCharge = jetCont;
            for(auto jet : jetContCharge->accepted()){
                if(!jet) continue;
                jetCntCharged[1]++;//keeping track of # of jets in event
            }
        }


        //R07
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R07")==kTRUE){
            jetContFull = jetCont;
            for(auto jet : jetContFull->accepted()){
                if(!jet) continue;
                jetCntFull[2]++;//keeping track of # of jets in event
            }
        }

        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R07")==kTRUE){
            jetContCharge = jetCont;
            for(auto jet : jetContCharge->accepted()){
                if(!jet) continue;
                jetCntCharged[2]++;//keeping track of # of jets in event
            }
        }
    }

    AliAODTrack* leading1=0;
    AliAODTrack* leading2=0;


    Double_t FJPhi = -99;
    Double_t CJPhi = -99;

    Int_t leadTrkPID = -1;

    Bool_t CJetFill = kFALSE;

    Bool_t B2BEv = kFALSE;


    //start loop over collections
    while((jetCont = static_cast<AliJetContainer*>(nextJet()))) {

        Int_t jetInd = 0;

        Int_t jetCnt = 0;

        //R02
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R02")==kTRUE){
            jetCnt = jetCntFull[0];
        }
        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R02")==kTRUE){
            jetCnt = jetCntCharged[0];
        }

        //R04
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R04")==kTRUE){
            jetCnt = jetCntFull[1];
        }
        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R04")==kTRUE){
            jetCnt = jetCntCharged[1];
        }

        //R07
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R07")==kTRUE){
            jetCnt = jetCntFull[2];
        }
        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R07")==kTRUE){
            jetCnt = jetCntCharged[2];
        }




        for(Int_t y=0;y<3;y++){
            if(TString(jetCont->GetName()).Contains("R02")==kTRUE&&y!=0){
                CJetFill = kFALSE;
                B2BEv = kFALSE;
                cout<<"Not R02\n"; 
                continue;
            }
            if(TString(jetCont->GetName()).Contains("R04")==kTRUE&&y!=1){
                CJetFill = kFALSE;
                B2BEv = kFALSE;
                cout<<"Not R04\n"; 
                continue;
            }
            if(TString(jetCont->GetName()).Contains("R07")==kTRUE&&y!=2){
                CJetFill = kFALSE;
                B2BEv = kFALSE;
                cout<<"Not R07\n"; 
                continue;}

            //start loop over jets
            for(auto jet : jetCont->accepted()){   
                if(!jet) continue;
                jetInd++;
                histoName = TString::Format("JetPt");
                fHistManager.FillTH1(histoName, jet->Pt());

                if(TString(jetCont->GetName()).Contains("R02")==kTRUE){
                    if(jetCntFull[0]==0||jetCntCharged[0]==0){continue;}
                }

                if(TString(jetCont->GetName()).Contains("R04")==kTRUE){
                    if(jetCntFull[1]==0||jetCntCharged[1]==0){
                        cout<<"Is this where we loseit? R04 no jets?\n";
                        continue;}
                }

                if(TString(jetCont->GetName()).Contains("R07")==kTRUE){
                    if(jetCntFull[2]==0||jetCntCharged[2]==0){
                        cout<<"Is this where we loseit? R07 no jets?\n";
                        continue;}
                }

                //==========================================================
                //Past this point we have some full jets and some charged jets
                //==========================================================

                if(!leadingB2BF[y]){cout<<"Leading full jet hasn't been filled.\n";}
                else{

                    FJPhi = leadingB2BF[y]->Phi_0_2pi();

                }

                if(!leadingB2BC[y]){cout<<"Leading charged jet that is 'nearly' back to back with the leading full jet hasn't been filled.\n";}
                else{

                    CJPhi = leadingB2BC[y]->Phi_0_2pi();

                    for(Int_t id=0; id<leadingB2BC[y]->GetNumberOfTracks(); id++){
                        AliAODTrack* track = (AliAODTrack*)leadingB2BC[y]->Track(id);
                        if(!track) continue;
                        if(!leading2 || leading2->Pt()<track->Pt()){
                            leading2=track;
                            cout<<"Leading constituent of away side charged jet loaded! Pt is:"<<leading2->Pt();
                        }
                    }

                }

                Double_t DPhiB2B = -999;

                if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&jet==jetCont->GetLeadingJet("")){
                    leadingB2BF[y] = jet;
                    cout<<"Just filled leading fullfor container"<<y<<"\n";
                    for(Int_t id=0; id<jet->GetNumberOfTracks(); id++){
                        AliAODTrack* track = (AliAODTrack*)jet->Track(id);
                        if(!track) continue;
                        if(!leading1 || leading1->Pt()<track->Pt()){
                            leading1=track;
                            cout<<"Leading constituent of near side full jet loaded! Pt is:"<<leading1->Pt()<<'\n';
                        }
                    }
                }

                if(FJPhi!=-99&&CJPhi!=-99&&!B2BEv){
                    DPhiB2B = (FJPhi-CJPhi > 0) ? FJPhi-CJPhi : CJPhi-FJPhi;


                }

                if(B2BEv){
                    if(leading1 != NULL){
                        leadTrkPID = (leading1->GetMostProbablePID() == AliAODTrack::kElectron) ? 0:(leading1->GetMostProbablePID() == AliAODTrack::kMuon) ? 1: (leading1->GetMostProbablePID() == AliAODTrack::kPion) ? 2: (leading1->GetMostProbablePID() == AliAODTrack::kKaon) ? 3: (leading1->GetMostProbablePID() == AliAODTrack::kProton) ? 4:5 ;

                        cout<<"Filling B2b plot\n";
                        histoName = TString::Format("B2BEvLeadType");
                        fHistManager.FillTH1(histoName, leadTrkPID);

                    }
                }

                if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&leadingB2BF[y]!=NULL){


                    if(TMath::Abs(jet->Phi_0_2pi()-leadingB2BF[y]->Phi_0_2pi())>TMath::Pi()-TMath::Pi()/8&&TMath::Abs(jet->Phi_0_2pi()-leadingB2BF[y]->Phi_0_2pi())<TMath::Pi()+TMath::Pi()/8){

                        if(leadingB2BC[y]==NULL){leadingB2BC[y] = jet; CJetFill = kTRUE;}
                        else{
                            if(leadingB2BC[y]->Pt() < jet->Pt()){
                                leadingB2BC[y] = jet;
                                CJetFill = kTRUE;
                                cout<<"Refilling B2Bc\n";
                            }
                        }
                        cout<<"B2b event\n";

                        B2BEv = kTRUE;
                    }


                    if(!leading1 || !leading2){cout<<"The leading jet constituents are not defined.\n";}

                }

                if(B2BEv&&leading1!=NULL&&CJetFill&&jetInd==jetCnt){

                    Double_t EOP = -1;

                    for(Int_t i=0; i<3; i++){
                        if(i==0&&leading1->GetMostProbablePID()==AliAODTrack::kElectron){

                            AliPIDResponse::EDetPidStatus detOK = AliPIDResponse::kDetPidOk;

                            Double_t elecLikeTRD[1];

                            Double_t nSigmaTPC;
                            nSigmaTPC = fPIDResponse->NumberOfSigmasTPC(leading1,AliPID::kElectron);



                            /*if(leading1->GetEMCALcluster()!=-99999){
                                Int_t clid = leading1->GetEMCALcluster();
                                AliAODCaloCluster* cl = aod->GetCaloCluster(clid);
                                if(cl){
                                    cout<<"FIlling EOP with cluster ID:"<<clid<<"\n";
                                    EOP = cl->E()/leading1->Pt();
                                }
                            }*/

                            if(leading1->IsHybridGlobalConstrainedGlobal()  &&  fPIDResponse->CheckPIDStatus(AliPIDResponse::kTRD, leading1)==detOK  &&  fPIDResponse->CheckPIDStatus(AliPIDResponse::kTPC, leading1)==detOK  &&  fPIDResponse->CheckPIDStatus(AliPIDResponse::kEMCAL, leading1)==detOK  &&  leading1->GetTRDntrackletsPID()<4  &&  fPIDResponse->ComputeTRDProbability(leading1, AliPID::kElectron, elecLikeTRD, AliTRDPIDResponse::kLQ2D) == detOK  &&  nSigmaTPC<2  &&  nSigmaTPC>-2  &&  elecLikeTRD[0]>.9){

                                histoName = TString::Format("%s/%s/HFERejection", groupName[0].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, 0.);
                            }else{
                                histoName = TString::Format("%s/%s/HFERejection", groupName[0].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, 1);
                            }

                            for(Int_t k=0;k<leadingB2BF[y]->GetNumberOfTracks();k++){
                                AliAODTrack* trk = (AliAODTrack*)leadingB2BF[y]->Track(k);
                                if(!trk){continue;}
                                Double_t ElecMass=.000511;

                                if(trk->GetMostProbablePID()==AliAODTrack::kElectron&&trk->Charge()==leading1->Charge()){

                                    Double_t assocE1=TMath::Sqrt(leading1->P()*leading1->P()+ElecMass*ElecMass);
                                    Double_t assocE2=TMath::Sqrt(trk->P()*trk->P()+ElecMass*ElecMass);

                                    TLorentzVector assoc1(leading1->Px(), leading1->Py(), leading1->Pz(), assocE1);
                                    TLorentzVector assoc2(trk->Px(), trk->Py(), trk->Pz(), assocE2);

                                    Double_t InvMass=(assoc1+assoc2).M();

                                    histoName = TString::Format("%s/%s/tracks/LeadingFInvMassLS", groupName[0].Data(), radName[y].Data());
                                    fHistManager.FillTH1(histoName, InvMass);
                                }

                                if(trk->GetMostProbablePID()==AliAODTrack::kElectron&&trk->Charge()!=leading1->Charge()&&trk->Charge()!=0){

                                    Double_t assocE1=TMath::Sqrt(leading1->P()*leading1->P()+ElecMass*ElecMass);
                                    Double_t assocE2=TMath::Sqrt(trk->P()*trk->P()+ElecMass*ElecMass);

                                    TLorentzVector assoc1(leading1->Px(), leading1->Py(), leading1->Pz(), assocE1);
                                    TLorentzVector assoc2(trk->Px(), trk->Py(), trk->Pz(), assocE2);

                                    Double_t InvMass=(assoc1+assoc2).M();

                                    histoName = TString::Format("%s/%s/tracks/LeadingFInvMassULS", groupName[0].Data(), radName[y].Data());
                                    fHistManager.FillTH1(histoName, InvMass);
                                }


                            }

                            histoName = TString::Format("%s/%s/Area", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Area());

                            histoName = TString::Format("%s/%s/AreaByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->Area());

                            histoName = TString::Format("%s/%s/E", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->E());

                            histoName = TString::Format("%s/%s/Pt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt());

                            histoName = TString::Format("%s/%s/Nch", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Nch());

                            histoName = TString::Format("%s/%s/NchByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->Nch());

                            histoName = TString::Format("%s/%s/M", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->M());

                            histoName = TString::Format("%s/%s/MaxChPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->MaxChargedPt());

                            histoName = TString::Format("%s/%s/MaxChPtByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->MaxChargedPt());

                            histoName = TString::Format("%s/%s/LeadingPtFraction", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->MaxChargedPt()/leadingB2BC[y]->Pt());

                            histoName = TString::Format("%s/%s/LeadingPtFractionByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->MaxChargedPt()/leadingB2BC[y]->Pt());

                            Double_t g = 0;
                            Double_t g2 = 0;
                            Double_t g3 = 0;
                            
                            Double_t mom[11][11] = {-1};
                            for(Int_t k=0;k<jet->GetNumberOfTracks();k++){
                                AliAODTrack* trk = (AliAODTrack*)jet->Track(k);
                                if(!trk){continue;}

                                g = g + (trk->Pt()/jet->Pt())*jet->DeltaR(trk);
                                g2 = g2 + ((trk->Pt()*trk->Pt())/jet->Pt())*jet->DeltaR(trk);
                                g3 = g3 + ((trk->Pt()*trk->Pt()*trk->Pt())/jet->Pt())*jet->DeltaR(trk);
                                
                                for(Int_t n=0;n<11;n++){
                                    for(Int_t m=0;m<11;m++){
                                        mom[n][m] += pow((trk->Pt()/jet->Pt()), n)*pow(TMath::Abs(jet->Eta()-trk->Eta()), m);
                                    }
                                }

                                histoName = TString::Format("%s/%s/tracks/DCA", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, trk->DCA());

                                histoName = TString::Format("%s/%s/tracks/Length", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, trk->GetIntegratedLength());

                                histoName = TString::Format("%s/%s/tracks/Pt", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, trk->Pt());

                                histoName = TString::Format("%s/%s/tracks/dEdx", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, trk->Pt(), trk->GetTPCsignal());
                            }
                            
                            

                            for(Int_t ind = 0;ind<100;ind++){
                                Double_t t = 0;
                                Double_t td = 0;
                                for(Int_t k=0;k<jet->GetNumberOfTracks();k++){
                                    AliAODTrack* trk = (AliAODTrack*)jet->Track(k);
                                    if(!trk){continue;}
                                    t = t + trk->Pt()*TMath::Exp(-TMath::Abs(jet->Eta()-trk->Eta())*(1-a_vals[ind]));
                                    td = td + trk->Pt()*TMath::Abs(jet->Eta()-trk->Eta())*TMath::Exp(-TMath::Abs(jet->Eta()-trk->Eta())*(1-a_vals[ind]));
                                }
                                histoName = TString::Format("%s/%s/Angularity", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, a_vals[ind], t/(2*jet->E())); 

                                histoName = TString::Format("%s/%s/AngularityDeriv", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, a_vals[ind], td/(2*jet->E())); 

                            }

                            histoName = TString::Format("%s/%s/Girth", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g);

                            histoName = TString::Format("%s/%s/QMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g2);

                            histoName = TString::Format("%s/%s/CMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g3);

                            histoName = TString::Format("%s/%s/GirthByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), g);

                            histoName = TString::Format("%s/%s/QMomentByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), g2);

                            histoName = TString::Format("%s/%s/CMomentByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), g3);
                            
                            for(Int_t n=0;n<11;n++){
                                for(Int_t m=0;m<11;m++){
                                    histoName = TString::Format("%s/%s/Moments/M%d%d", groupName[i].Data(), radName[y].Data(), n, m);
                                    fHistManager.FillTH2(histoName, leadingB2BC[y]->Pt(), mom[n][m]);
                                }
                            }



                        }

                        if(i==1&&leading1->GetMostProbablePID()!=AliAODTrack::kElectron){
                            histoName = TString::Format("%s/%s/Area", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Area());

                            histoName = TString::Format("%s/%s/AreaByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->Area());

                            histoName = TString::Format("%s/%s/E", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->E());

                            histoName = TString::Format("%s/%s/Pt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt());

                            histoName = TString::Format("%s/%s/Nch", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Nch());

                            histoName = TString::Format("%s/%s/NchByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->Nch());

                            histoName = TString::Format("%s/%s/M", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->M());

                            histoName = TString::Format("%s/%s/MaxChPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->MaxChargedPt());

                            histoName = TString::Format("%s/%s/MaxChPtByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->MaxChargedPt());

                            histoName = TString::Format("%s/%s/LeadingPtFraction", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->MaxChargedPt()/leadingB2BC[y]->Pt());

                            histoName = TString::Format("%s/%s/LeadingPtFractionByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), leadingB2BC[y]->MaxChargedPt()/leadingB2BC[y]->Pt());

                            Double_t g = 0;
                            Double_t g2 = 0;
                            Double_t g3 = 0;
                            for(Int_t k=0;k<jet->GetNumberOfTracks();k++){
                                AliAODTrack* trk = (AliAODTrack*)jet->Track(k);
                                if(!trk){continue;}

                                g = g + (trk->Pt()/jet->Pt())*jet->DeltaR(trk);
                                g2 = g2 + ((trk->Pt()*trk->Pt())/jet->Pt())*jet->DeltaR(trk);
                                g3 = g3 + ((trk->Pt()*trk->Pt()*trk->Pt())/jet->Pt())*jet->DeltaR(trk);

                                histoName = TString::Format("%s/%s/tracks/DCA", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, trk->DCA());

                                histoName = TString::Format("%s/%s/tracks/Length", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, trk->GetIntegratedLength());

                                histoName = TString::Format("%s/%s/tracks/Pt", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH1(histoName, trk->Pt());

                                histoName = TString::Format("%s/%s/tracks/dEdx", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, trk->Pt(), trk->GetTPCsignal());
                            }

                            for(Int_t ind = 0;ind<100;ind++){
                                Double_t t = 0;
                                Double_t td = 0;
                                for(Int_t k=0;k<jet->GetNumberOfTracks();k++){
                                    AliAODTrack* trk = (AliAODTrack*)jet->Track(k);
                                    if(!trk){continue;}
                                    t = t + trk->Pt()*TMath::Exp(-TMath::Abs(jet->Eta()-trk->Eta())*(1-a_vals[ind]));
                                    td = td + trk->Pt()*TMath::Abs(jet->Eta()-trk->Eta())*TMath::Exp(-TMath::Abs(jet->Eta()-trk->Eta())*(1-a_vals[ind]));
                                }
                                histoName = TString::Format("%s/%s/Angularity", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, a_vals[ind], t/(2*jet->E()));     

                                histoName = TString::Format("%s/%s/AngularityDeriv", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, a_vals[ind], td/(2*jet->E())); 
                            }

                            histoName = TString::Format("%s/%s/Girth", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g);

                            histoName = TString::Format("%s/%s/QMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g2);

                            histoName = TString::Format("%s/%s/CMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g3);

                            histoName = TString::Format("%s/%s/GirthByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), g);

                            histoName = TString::Format("%s/%s/QMomentByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), g2);

                            histoName = TString::Format("%s/%s/CMomentByPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt(), g3);
                        }
                    }
                }

            }       
        }
    } 

    PostData(1, fOutput);
}

void AliAnalysisTaskPatJet::FillTrackHistos()
{}

void AliAnalysisTaskPatJet::FillClusterHistos()
{}

void AliAnalysisTaskPatJet::Terminate(Option_t *)
{

}
