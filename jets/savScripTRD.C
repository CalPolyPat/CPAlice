void savScripTRD(){
    TFile *file = new TFile("./phistos.root");
    TList *PID = (TList*)file->Get("PIDqa");
    TList *MB = (TList*)file->Get("Min-Bias");
    TList *EMC7 = (TList*)file->Get("EMCal7");
    TList *EMC8 = (TList*)file->Get("EMCal8");
    TList *EMCJet = (TList*)file->Get("EMCalJet");
    
    TCanvas *c1 = new TCanvas();

    for(Int_t i=0; i<=MB->LastIndex();i++){
        TH2F *hist = (TH2F*)MB->At(i);
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
        hist->GetYaxis()->SetRangeUser(0,1);
        hist->Draw("colz");
        c1->Update();
        c1->SaveAs(Form("./plotsKlayTRD/%s.png", hist->GetName()));
        }
    }
    
    for(Int_t i=0; i<=EMC7->LastIndex();i++){
        TH2F *hist = (TH2F*)EMC7->At(i);
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
        hist->GetYaxis()->SetRangeUser(0,1);
        hist->Draw("colz");
        c1->Update();
        c1->SaveAs(Form("./plotsKlayTRD/%s.png", hist->GetName()));
        }
    }
    
    for(Int_t i=0; i<=EMC8->LastIndex();i++){
        TH2F *hist = (TH2F*)EMC8->At(i);
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
        hist->GetYaxis()->SetRangeUser(0,1);
        hist->Draw("colz");
        c1->Update();
        c1->SaveAs(Form("./plotsKlayTRD/%s.png", hist->GetName()));
        }
    }
    
    for(Int_t i=0; i<=EMCJet->LastIndex();i++){
        TH2F *hist = (TH2F*)EMCJet->At(i);
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
        hist->GetYaxis()->SetRangeUser(0,1);
        hist->Draw("colz");
        c1->Update();
        c1->SaveAs(Form("./plotsKlayTRD/%s.png", hist->GetName()));
        }
    }       
    return;
}