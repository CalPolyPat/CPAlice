#include <TClonesArray.h>
    #include <TH1F.h>
    #include <TH2F.h>
    #include <TList.h>

    #include <AliVCluster.h>
    #include <AliVParticle.h>
    #include <AliLog.h>


    #include "AliAnalysisTaskPatJet.h"

    #include "AliEmcalJet.h"
    #include "AliJetContainer.h"
    #include "AliParticleContainer.h"
    #include "AliClusterContainer.h"
    #include "AliAODTrack.h"
    #include "AliAODCluster.h"
    #include "AliAnalysisTaskPatJet.h"


    /// \cond CLASSIMP
    ClassImp(AliAnalysisTaskPatJet);
/// \endcond

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
    FillJetHistos();
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
    Int_t NBins = 100; //placeholder until I can think of appropriate binning

    TString histoName;
    TString histoTitle;
    TString groupName[3];
    TString radName[3];

    AliJetContainer* jetCont = 0; 
    TIter nextJet(&fJetCollArray); //Iterate over the jet collections in fjetcollarray

    groupName[0] = TString("AsJet_ElecLeading");
    groupName[1] = TString("AsJet_HadronLeading");//this should technically also be muons
    groupName[2] = TString("Ratios_Ave");//Fill by taking ratios of As_Jet Plots

    radName[0] = TString("R02");
    radName[1] = TString("R04");
    radName[2] = TString("R10");



    for(Int_t i=0; i<3;i++){

        fHistManager.CreateHistoGroup(groupName[i]); //Make folders foreach group of histos

    }

    //Init plots for away side jets
    for(Int_t i=0;i<3;i++){
        for(Int_t j=0;j<3;j++){
            histoName = TString::Format("%s/%s/Area", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet area for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 1);

            histoName = TString::Format("%s/%s/E", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet Energy for away side jets(Calculated using jet mass)");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 80);

            histoName = TString::Format("%s/%s/Pt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet Pt for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 80);

            histoName = TString::Format("%s/%s/Nch", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Charged particle multiplicity for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 30);

            histoName = TString::Format("%s/%s/M", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Jet mass for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 1);

            histoName = TString::Format("%s/%s/MaxChPt", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Pt of leading charged constituent for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 50);

            histoName = TString::Format("%s/%s/Girth", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Girth or first geometric moment for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 1);

            histoName = TString::Format("%s/%s/QMoment", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Quadratic geometric moment for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 1);

            histoName = TString::Format("%s/%s/CMoment", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Cubic geometric moment for away side jets");
            fHistManager.CreateTH1(histoName, histoTitle, NBins, 0, 1);

            histoName = TString::Format("%s/%s/Angularity", groupName[i].Data(), radName[j].Data());
            histoTitle = TString::Format("Angularity vs. parameter a for away side jets");
            fHistManager.CreateTH2(histoName, histoTitle, NBins, -2, 2, NBins, 0, 1);

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
        }
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
    fHistManager.CreateTH1(histoName, histoTitle, 200, 0, 100);


    PostData(1, fOutput);

}

void AliAnalysisTaskPatJet::InitTrackHistos()
{}

void AliAnalysisTaskPatJet::InitClusterHistos()
{}

void AliAnalysisTaskPatJet::FillJetHistos()
{
    TString histoName;
    TString groupName[3];
    TString radName[3];

    AliJetContainer* jetCont = 0;
    AliJetContainer* jetContFull = 0;
    AliJetContainer* jetContCharge = 0;
    AliClusterContainer* clusCont = GetClusterContainer(0);

    UInt_t jetCntFull[3];
    UInt_t jetCntCharged[3];

    Double_t PhiFull = -99;
    Double_t PhiCharge = -99;

    TIter jetCounter(&fJetCollArray);
    TIter nextJet(&fJetCollArray);

    groupName[0] = TString("AsJet_ElecLeading");
    groupName[1] = TString("AsJet_HadronLeading");//this should technically also be muons
    groupName[2] = TString("Ratios_Ave");//Fill by taking ratios of As_Jet Plots

    radName[0] = TString("R02");
    radName[1] = TString("R04");
    radName[2] = TString("R10");

    AliEmcalJet* leadingB2BC[3] = {0, 0, 0};
    AliEmcalJet* leadingB2BF[3] = {0, 0, 0};

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


        //R10
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R10")==kTRUE){
            jetContFull = jetCont;
            for(auto jet : jetContFull->accepted()){
                if(!jet) continue;
                jetCntFull[2]++;//keeping track of # of jets in event
            }
        }

        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R10")==kTRUE){
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



    Bool_t B2BEv = kFALSE;


    //start loop over collections
    while((jetCont = static_cast<AliJetContainer*>(nextJet()))) {

        Int_t jetInd = 0;

        UInt_t jetCnt = 0;

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

        //R10
        if(TString(jetCont->GetName()).Contains("Full")==kTRUE&&TString(jetCont->GetName()).Contains("R10")==kTRUE){
            jetCnt = jetCntFull[2];
        }
        if(TString(jetCont->GetName()).Contains("Charged")==kTRUE&&TString(jetCont->GetName()).Contains("R10")==kTRUE){
            jetCnt = jetCntCharged[2];
        }




        for(Int_t y=0;y<3;y++){
            if(TString(jetCont->GetName()).Contains("R02")==kTRUE&&y!=0) continue;
            if(TString(jetCont->GetName()).Contains("R04")==kTRUE&&y!=1) continue;
            if(TString(jetCont->GetName()).Contains("R10")==kTRUE&&y!=2) continue;

            //start loop over jets
            for(auto jet : jetCont->accepted()){   
                if(!jet) continue;
                histoName = TString::Format("JetPt");
                fHistManager.FillTH1(histoName, jet->Pt());

                if(TString(jetCont->GetName()).Contains("R02")==kTRUE){
                    if(jetCntFull[0]==0||jetCntCharged[0]==0){continue;}
                }

                if(TString(jetCont->GetName()).Contains("R04")==kTRUE){
                    if(jetCntFull[1]==0||jetCntCharged[1]==0){continue;}
                }

                if(TString(jetCont->GetName()).Contains("R10")==kTRUE){
                    if(jetCntFull[2]==0||jetCntCharged[2]==0){continue;}
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
                    cout<<"Just filled leading full\n";
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

                if(TString(jetCont->GetName()).Contains("Charged")==kTRUE){


                    if(TMath::Abs(jet->Phi_0_2pi()-leadingB2BF[y]->Phi_0_2pi())>TMath::Pi()-TMath::Pi()/8&&TMath::Abs(jet->Phi_0_2pi()-leadingB2BF[y]->Phi_0_2pi())<TMath::Pi()+TMath::Pi()/8){

                        if(!leadingB2BC[y]){leadingB2BC[y] = jet;}
                        else{
                            if(leadingB2BC[y]->Pt() < jet->Pt()){
                                leadingB2BC[y] = jet;
                                cout<<"Refilling B2Bc\n";
                            }
                        }
                        cout<<"B2b event\n";

                        B2BEv = kTRUE;
                    }


                    if(!leading1 || !leading2){cout<<"The leading jet constituents are not defined.\n";}

                }

                if(B2BEv&&leading1!=NULL&&jetInd == jetCnt-1){
                    for(Int_t i=0; i<3; i++){
                        if(i==0&&leading1->GetMostProbablePID()==AliAODTrack::kElectron){
                            histoName = TString::Format("%s/%s/Area", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Area());

                            histoName = TString::Format("%s/%s/E", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->E());

                            histoName = TString::Format("%s/%s/Pt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt());

                            histoName = TString::Format("%s/%s/Nch", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Nch());

                            histoName = TString::Format("%s/%s/M", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->M());

                            histoName = TString::Format("%s/%s/MaxChPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->MaxChargedPt());

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
                                for(Int_t k=0;k<jet->GetNumberOfTracks();k++){
                                    AliAODTrack* trk = (AliAODTrack*)jet->Track(k);
                                    if(!trk){continue;}
                                    t = t + trk->Pt()*TMath::Exp(-TMath::Abs(jet->Eta()-trk->Eta())*(1-a_vals[ind]));
                                }
                                histoName = TString::Format("%s/%s/Angularity", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, a_vals[ind], t/(2*jet->E()));      
                            }

                            histoName = TString::Format("%s/%s/Girth", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g);

                            histoName = TString::Format("%s/%s/QMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g2);

                            histoName = TString::Format("%s/%s/CMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g3);

                        }

                        if(i==1&&leading1->GetMostProbablePID()!=AliAODTrack::kElectron){
                            histoName = TString::Format("%s/%s/Area", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Area());

                            histoName = TString::Format("%s/%s/E", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->E());

                            histoName = TString::Format("%s/%s/Pt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Pt());

                            histoName = TString::Format("%s/%s/Nch", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->Nch());

                            histoName = TString::Format("%s/%s/M", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->M());

                            histoName = TString::Format("%s/%s/MaxChPt", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, leadingB2BC[y]->MaxChargedPt());

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
                                for(Int_t k=0;k<jet->GetNumberOfTracks();k++){
                                    AliAODTrack* trk = (AliAODTrack*)jet->Track(k);
                                    if(!trk){continue;}
                                    t = t + trk->Pt()*TMath::Exp(-TMath::Abs(jet->Eta()-trk->Eta())*(1-a_vals[ind]));
                                }
                                histoName = TString::Format("%s/%s/Angularity", groupName[i].Data(), radName[y].Data());
                                fHistManager.FillTH2(histoName, a_vals[ind], t/(2*jet->E()));      
                            }

                            histoName = TString::Format("%s/%s/Girth", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g);

                            histoName = TString::Format("%s/%s/QMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g2);

                            histoName = TString::Format("%s/%s/CMoment", groupName[i].Data(), radName[y].Data());
                            fHistManager.FillTH1(histoName, g3);
                        }
                    }
                }
                jetInd++;
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
