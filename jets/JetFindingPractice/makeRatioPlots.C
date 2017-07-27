void makeRatioPlots(){
    TFile* f = TFile::Open("AnalysisResults.root");

    TString dirName = TString("AliAnalysisTaskPatJet_tracks_caloClusters_emcalCells_histos");

    TList *list = f->Get(dirName.Data());

    if(!list){cout<<"Can't get list"<<'\n'<<;}

    TString radName[3] = {"R02", "R04", "R07"};

    TString histoName[12];
    histoName[0] = TString("Area");
    histoName[1] = TString("Pt");
    histoName[2] = TString("E");
    histoName[3] = TString("Nch");
    histoName[4] = TString("M");
    histoName[5] = TString("MaxChPt");
    histoName[6] = TString("Girth");
    histoName[7] = TString("QMoment");
    histoName[8] = TString("CMoment");
    histoName[9] = TString("Angularity");
    histoName[10] = TString("AngularityDeriv");
    histoName[11] = TString("LeadingPtFraction");

    THashList *hlist0[3] = {((THashList*)list->At(0))->At(0), ((THashList*)list->At(0))->At(1), ((THashList*)list->At(0))->At(2)};
    THashList *hlist1[3] = {((THashList*)list->At(1))->At(0), ((THashList*)list->At(1))->At(1), ((THashList*)list->At(1))->At(2)};
    THashList *hlist2[3] = {((THashList*)list->At(2))->At(0), ((THashList*)list->At(2))->At(1), ((THashList*)list->At(2))->At(2)};
    
    
    TCanvas *c = new TCanvas("c", "canvas", 800, 800);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetGridx();
    pad1->Draw();

    for(Int_t j=0;j<3;j++){
        for(Int_t i=0;i<12;i++){

            TH1* histE = (TH1*)(hlist0[j]->FindObject(TString::Format("%s", histoName[i].Data())));
            TH1* histH = (TH1*)(hlist1[j]->FindObject(TString::Format("%s", histoName[i].Data())));

            Double_t normE = histE->GetEntries();
            Double_t normH = histH->GetEntries();
            
            if(normE==0||normH==0){continue;}

            histE->Scale(1/normE);
            histH->Scale(1/normH);
            histE->Draw("colz");
            histH->Draw("same");

            TH1* histRat = (TH1*)histH->Clone(histH->GetName());
            //histE->Copy(*histRat);

            histRat->Divide(histE);
            TH1* histIF = (TH1*)hlist2[j]->FindObject(TString::Format("%s", histoName[i].Data()));

            histIF = histRat;

            histIF->SetMaximum(2.5);
            histIF->SetOption("P");
            histIF->SetStats(0);
            histIF->SetMarkerStyle(kFullCircle);
            TLine* line = new TLine(0,1,100, 1);
            
            TLine* cf = new TLine(0,4./9.,100, 4./9.);
            
            histIF->Draw("plcolz");
            line->Draw();
            cf->Draw();
            c->SaveAs(TString::Format("./ratio_plots/%s/%s.png", radName[j].Data(), histIF->GetName()));

        }
    }

}