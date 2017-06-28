void savScrip(){
    TFile *file = new TFile("./phistos.root");
    TList *PID = (TList*)file->Get("PIDqa");
    TList *MB = (TList*)file->Get("Min-Bias");
    TList *EMC7 = (TList*)file->Get("EMCal7");
    TList *EMC8 = (TList*)file->Get("EMCal8");
    TList *EMCJet = (TList*)file->Get("EMCalJet");
    
    TCanvas *c1 = new TCanvas();

    TList *TPC = (TList*)PID->FindObject("TPC");
    TList *TPCBasic = (TList*)TPC->FindObject("TPCBasic");
    TH2F *TPCnSig = (TH2F*)TPCBasic->FindObject("hNsigmaP_TPC_Basic_electron");
    TPCnSig->Draw();
    c1->Update();
    c1->SaveAs("./plotsKlay/TPCnSigmaRaw.png");
    
    TList *TRD = (TList*)PID->FindObject("TRD");
    TH2F *TRDLike = (TH2F*)TRD->FindObject("hLikeP_TRD_5tls_electron");
    TRDLike->Draw();
    c1->Update();
    c1->SaveAs("./plotsKlay/TRDelecLikeRaw.png");

    TList *TOF = (TList*)PID->FindObject("TOF");
    TH2F *TOFnSig = (TH2F*)TOF->FindObject("hNsigmaP_TOF_electron");
    TOFnSig->Draw();
    c1->Update();
    c1->SaveAs("./plotsKlay/TOFnSigmaRaw.png");

    TList *EMC = (TList*)PID->FindObject("EMCAL");
    TH2F *EMCnSig = (TH2F*)EMC->FindObject("hNsigmaPt_EMCAL_electron");
    EMCnSig->Draw();
    c1->Update();
    c1->SaveAs("./plotsKlay/EMCnSigmaRaw.png");

    
    for(Int_t i=0; i<=MB->LastIndex();i++){
        TH1 *hist = (TH1*)MB->At(i);
        hist->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));

    }
    
    for(Int_t i=0; i<=EMC7->LastIndex();i++){
        TH1 *hist = (TH1*)EMC7->At(i);
        hist->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));
    }
    
    for(Int_t i=0; i<=EMC8->LastIndex();i++){
        TH1 *hist = (TH1*)EMC8->At(i);
        hist->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));
    }
    
    for(Int_t i=0; i<=EMCJet->LastIndex();i++){
        TH1 *hist = (TH1*)EMCJet->At(i);
        hist->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));
    }       
}