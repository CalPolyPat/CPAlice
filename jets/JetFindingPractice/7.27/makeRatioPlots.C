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

    //indiv rt plots
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

    //double rat plots
    for(Int_t i=0;i<12;i++){

        TH1* histE02 = (TH1*)(hlist0[0]->FindObject(TString::Format("%s", histoName[i].Data())));
        TH1* histH02 = (TH1*)(hlist1[0]->FindObject(TString::Format("%s", histoName[i].Data())));
        TH1* histE04 = (TH1*)(hlist0[1]->FindObject(TString::Format("%s", histoName[i].Data())));
        TH1* histH04 = (TH1*)(hlist1[1]->FindObject(TString::Format("%s", histoName[i].Data())));

        Double_t normE02 = histE02->GetEntries();
        Double_t normH02 = histH02->GetEntries();
        Double_t normE04 = histE04->GetEntries();
        Double_t normH04 = histH04->GetEntries();

        if(normE02==0||normH02==0||normE04==0||normH04==0){continue;}

        histE02->Scale(1/normE02);
        histH02->Scale(1/normH02);
        histE02->Draw("colz");
        histH02->Draw("same");
        
        histE04->Scale(1/normE04);
        histH04->Scale(1/normH04);
        histE04->Draw("colz");
        histH04->Draw("same");

        TH1* histRat02 = (TH1*)histH02->Clone(histH02->GetName());
        TH1* histRat04 = (TH1*)histH04->Clone(histH04->GetName());
        //histE->Copy(*histRat);

        histRat02->Divide(histE02);
        histRat04->Divide(histE04);


        histRat02->SetMaximum(2.5);
        histRat02->SetOption("P");
        histRat02->SetStats(0);
        histRat02->SetMarkerStyle(kFullCircle);
        
        histRat04->SetMaximum(2.5);
        histRat04->SetOption("P");
        histRat04->SetStats(0);
        histRat04->SetMarkerStyle(kFullCircle);
        TLine* line = new TLine(0,1,100, 1);

        TLine* cflow = new TLine(0,4./9.,100, 4./9.);
        TLine* cfhi = new TLine(0,9./4.,100, 9./4.);
        
        hist0204 = (TH1*)histRat02->Clone(histRat02->GetName());
        hist0204->Divide(histRat04);

        hist0204->Draw("plcolz");
        line->Draw();
        cflow->Draw();
        cfhi->Draw();
        c->SaveAs(TString::Format("./ratio_plots/%s/%s.png", "0204", hist0204->GetName()));

    }


}