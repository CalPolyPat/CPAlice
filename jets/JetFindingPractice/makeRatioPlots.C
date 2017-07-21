void makeRatioPlots(){
    TFile* f = TFile::Open("AnalysisResults.root");

    TString dirName = TString("AliAnalysisTaskPatJet_tracks_caloClusters_emcalCells_histos");

    TList *list = f->Get(dirName.Data());

    if(!list){cout<<"Can't get list"<<'\n'<<;}

    TString histoName[6];
    histoName[0] = TString("Area");
    histoName[1] = TString("Pt");
    histoName[2] = TString("E");
    histoName[3] = TString("Nch");
    histoName[4] = TString("M");
    histoName[5] = TString("MaxChPt");

    THashList *hlist0 = list->At(0);
    THashList *hlist1 = list->At(1);
    THashList *hlist2 = list->At(2);
   TCanvas *c = new TCanvas("c", "canvas", 800, 800);
      TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
        pad1->SetGridx();
    pad1->Draw();

    for(Int_t i=0;i<6;i++){



        TH1F* histE = (TH1F*)(hlist0->FindObject(TString::Format("%s", histoName[i].Data())));
        TH1F* histH = (TH1F*)(hlist1->FindObject(TString::Format("%s", histoName[i].Data())));
        
        Double_t normE = histE->GetEntries();
        Double_t normH = histH->GetEntries();
        
        histE->Scale(1/normE);
        histH->Scale(1/normH);
        histE->Draw();
        histH->Draw("same");

        TH1F* histRat = new TH1F(*histE);
        //histE->Copy(*histRat);

        histRat->Divide(histH);

        TH1F* histIF = (TH1F*)hlist2->FindObject(TString::Format("%s", histoName[i].Data()));

        histIF = histRat;
        
        histIF->SetMaximum(1.2);
        histIF->SetOption("P");
        histIF->SetMarkerStyle(kFullCircle);
        histIF->Draw();

    }

}