void savScripWeak(){
    TFile *file = new TFile("./AnalysisResults_0000.root");
    //TList *PID = (TList*)file->Get("PIDqa");
    TList *MB = (TList*)file->Get("Min-Bias_Weak_NoSS");
    TList *EMC7 = (TList*)file->Get("EMCal7_Weak_NoSS");
    TList *EMCJet = (TList*)file->Get("EMCalJet_Weak_NoSS");
    
    TCanvas *c1 = new TCanvas();
    c1->cd(1);
    
    Double_t purity_MB[5];
    Double_t purity_EMC7[5];
    Double_t purity_EMCJet[5];
    
    //Some variables to hold number of electrons
    Int_t NElec_MB[3]={0,0,0};
    Int_t NElec_EMC7[3]={0,0,0};
    Int_t NElec_EMCJet[3]={0,0,0};
    
    TH1* fHistEne;//Make histos for overlays
    TH1* fHistEneTag;
    
    TH1* fHistInvMassLike;
    TH1* fHistInvMassUnlike;
    
    TH1* fHistOpAngLike;
    TH1* fHistOpAngUnlike;
    
    TH1* fHistTPCSig;
    TH1* fHistTPCSigCut;
    
    TH1D* histProj;    
   /* TList *TPC = (TList*)PID->FindObject("TPC");
    TList *TPCBasic = (TList*)TPC->FindObject("TPCBasic");
    TH2F *TPCnSig = (TH2F*)TPCBasic->FindObject("hNsigmaP_TPC_Basic_electron");
    TPCnSig->Draw("colz");
    c1->Update();
    c1->SaveAs("./plotsKlayWeak/TPCnSigmaRaw.png");
    
    //TList *TRD = (TList*)PID->FindObject("TRD");
    //TList *TRDLikelihood = (TList*)TRD->FindObject("TRDLikelihood");
    //TH2F *TRDLike = (TH2F*)TRD->FindObject("hLikeP_TRD_5tls_electron");
    //TRDLike->Draw("colz");
    //c1->Update();
    //c1->SaveAs("./plotsKlayWeak/TRDelecLikeRaw.png");

    TList *TOF = (TList*)PID->FindObject("TOF");
    TH2F *TOFnSig = (TH2F*)TOF->FindObject("hNsigmaP_TOF_electron");
    TOFnSig->Draw("colz");
    c1->Update();
    c1->SaveAs("./plotsKlayWeak/TOFnSigmaRaw.png");

    TList *EMC = (TList*)PID->FindObject("EMCAL");
    TH2F *EMCnSig = (TH2F*)EMC->FindObject("hNsigmaPt_EMCAL_electron");
    EMCnSig->Draw("colz");
    c1->Update();
    c1->SaveAs("./plotsKlayWeak/EMCnSigmaRaw.png");*/

    
    for(Int_t i=0; i<=MB->LastIndex();i++){
        TH1 *hist = (TH1*)MB->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistDPhi18Spe_MB")==0){
            hist->GetYaxis()->SetBinLabel(1,"Unknown");
            hist->GetYaxis()->SetBinLabel(2,"Electron");
            hist->GetYaxis()->SetBinLabel(3,"Muon");
            hist->GetYaxis()->SetBinLabel(4,"Pion");
            hist->GetYaxis()->SetBinLabel(5,"Kaon");
            hist->GetYaxis()->SetBinLabel(6,"Proton");
            hist->GetYaxis()->SetBinLabel(7,"Deuteron");
        }
        if(strcmp(hist->GetName(),"fHistImpPar_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistImpParTag_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistPtSum_MB")==0){
            fHistEne = hist;
        }
        if(strcmp(hist->GetName(),"fHistPtSumTag_MB")==0){
            fHistEneTag = hist;
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecLike_MB")==0){
            fHistInvMassLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecUnLike_MB")==0){
            fHistInvMassUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecLike_MB")==0){
            fHistOpAngLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecUnLike_MB")==0){
            fHistOpAngUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSig_MB")==0){
            fHistTPCSig = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSigCut_MB")==0){
            fHistTPCSigCut = hist;
        }
        if(strcmp(hist->GetName(),"fHistPIDRejection")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistPtSum_MB")==0){
            gPad->SetLogy();
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistNElecPerEvent")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistEtaPhiTag_MB")==0){
            gPad->SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistPtSumTag_MB")==0){
            gPad->SetLogy();
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistITSNClus_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_MB")==0){
            gPad->SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultAway_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMin_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMax_MB")==0){
            gPad->SetLogy();
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='C'&&hist->GetName()[8]=='_'){
            TLine *sigBot = new TLine(0, -2, 10, -2);
            TLine *sigTop = new TLine(0, 2, 10, 2);
            sigBot->SetLineColor(kRed);
            sigTop->SetLineColor(kRed);
            sigBot->SetLineWidth(2);
            sigTop->SetLineWidth(2);
            sigBot->Draw();
            sigTop->Draw();
            cout<<hist->GetName()<<'\n';
            TH2F *hist2d = (TH2F*)MB->At(i);
            TH1D *histProj = hist2d->ProjectionY(Form("%s_py", hist->GetName()));
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            TLine *sigTRD = new TLine(0, .9, 10, .9);
            sigTRD->SetLineColor(kRed);
            sigTRD->SetLineWidth(2);
            sigTRD->Draw();
        }
        if(hist->GetName()[5]=='M'&&hist->GetName()[6]=='0'&&hist->GetName()[7]=='2'){
            TLine *sigM02 = new TLine(0.5, 0, 0.5, 2);
            sigM02->SetLineColor(kRed);
            sigM02->SetLineWidth(1);
            sigM02->Draw();
        }
        if(hist->GetName()[5]=='M'&&hist->GetName()[6]=='2'&&hist->GetName()[7]=='0'){
            TLine *sigM20 = new TLine(0.3, 0, 0.3, 2);
            sigM20->SetLineColor(kRed);
            sigM20->SetLineWidth(1);
            sigM20->Draw();
        }
        if(hist->GetName()[5]=='E'&&hist->GetName()[6]=='M'&&hist->GetName()[7]=='C'){
            if(hist->GetName()[-4]=='6'){
                TLine *sigEBot = new TLine(.95, 0, .95, hist->GetMaximum());
                TLine *sigETop = new TLine(1.25, 0, 1.25, hist->GetMaximum());
                sigEBot->SetLineColor(kRed);
                sigETop->SetLineColor(kRed);
                sigEBot->SetLineWidth(2);
                sigETop->SetLineWidth(2);
                sigEBot->Draw();
                sigETop->Draw();
            }
            else{
                TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
                TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
                sigEBot->SetLineColor(kRed);
                sigETop->SetLineColor(kRed);
                sigEBot->SetLineWidth(2);
                sigETop->SetLineWidth(2);
                sigEBot->Draw();
                sigETop->Draw();
            }
            
            c1->Update();
            TPaveStats *ps = (TPaveStats*)hist->FindObject("stats");
            ps->SetX1NDC(.1);
            ps->SetX2NDC(.4);
            
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'){            
            TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
            TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);
            
            if(hist->GetName()[19]=='1'){
                TF1* hadFit = new TF1("hadFit", "gaus", 0.2, 0.8);
                TF1* totalFit = new TF1("totalFit", "gaus(0)+gaus(3)+pol0(6)", 0.2, 1.2);
            }
            
            totalFit->SetParName(0,"Scale_elecFit");
            totalFit->SetParName(1,"Mean_elecFit");
            totalFit->SetParName(2,"Sigma_elecFit");
            totalFit->SetParName(3,"Pedestal_hadCont");
            
            if(hist->GetName()[19]=='1'){
                totalFit->SetParName(3,"Scale_hadFit");
                totalFit->SetParName(4,"Mean_hadFit");
                totalFit->SetParName(5,"Sigma_hadFit");
                totalFit->SetParName(6,"Pedestal_hadCont");
            }
            
            totalFit->SetParameter(0,10);
            totalFit->SetParameter(1,1);
            totalFit->SetParameter(2,.4);
            totalFit->SetParLimits(3, 0, 1000000);
            totalFit->SetParLimits(0, 0, 10000);
                
            if(hist->GetName()[19]=='1'){
                totalFit->SetParameter(3,10);
                totalFit->SetParameter(4,.6);
                totalFit->SetParameter(5,.6);
                totalFit->SetParLimits(3, 0, 1000000);
                totalFit->SetParLimits(0, 0, 1000000);
                totalFit->SetParLimits(6, 0, 1000000);
            }
                
            
            hist->Fit(totalFit, "BLL");
            elecFit->SetParameters(totalFit->GetParameters());
            Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
            cout<<purity<<"\n"<<hist->GetName()[19]<<"\n";
            switch(hist->GetName()[19]){
                case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_MB[0]=purity;
                    NElec_MB[0]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_MB[1]=purity;
                    NElec_MB[1]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_MB[2]=purity;
                    NElec_MB[1]=NElec_MB[1]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_MB[3]=purity;
                    NElec_MB[2]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_MB[4]=purity;
                    NElec_MB[2]=NElec_MB[2]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
            }
            }
            if(hist->GetName()[9]=='H'){
                TF1* hadFit = new TF1("hadFit", "landau", 0.2, 1);
                hadFit->SetParameter(0, 8);
                hadFit->SetParameter(1, .8);
                hadFit->SetParameter(2, .1);
                hist->Fit(hadFit, "B");
            }
        }
        if(hist->GetName()[5]=='D'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='h'){
            switch(hist->GetName()[15]){
            case '1':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%d trigger electrons",NElec_MB[0]));
                pt->Draw();
                break;
            case '2':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%d trigger electrons",NElec_MB[1]));
                pt->Draw();
                break;
            case '4':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%d trigger electrons",NElec_MB[2]));
                pt->Draw();
                break;
            }
        }
        if(hist->GetName()[5]=='N'&&hist->GetName()[6]=='e'&&hist->GetName()[7]=='v'){
            gPad->SetLogy();
        }
        if(hist->GetName()[5]=='I'&&hist->GetName()[6]=='T'&&hist->GetName()[7]=='S'){
            TLine *ITScut = new TLine(4, 0, 4, hist->GetMaximum());
            ITScut->SetLineColor(kRed);
            ITScut->SetLineWidth(2);
            ITScut->Draw();
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='C'&&hist->GetName()[8]=='N'){
            TLine *TPCcut = new TLine(120, 0, 120, hist->GetMaximum());
            TPCcut->SetLineColor(kRed);
            TPCcut->SetLineWidth(2);
            TPCcut->Draw();
        }
        gStyle->SetOptFit(2);
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakSS/%s.png", hist->GetName()));
        
        if(!histProj){continue;}
        histProj->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakSS/%s.png", histProj->GetName()));
    }
    
    //Draw overlays
    fHistEne->SetStats(0);
    fHistEneTag->SetStats(0);
    fHistInvMassLike->SetStats(0);
    fHistInvMassUnlike->SetStats(0);
    fHistOpAngLike->SetStats(0);
    fHistOpAngUnlike->SetStats(0);
    fHistTPCSig->SetStats(0);
    fHistTPCSigCut->SetStats(0);
    
    fHistEne->SetFillStyle(3004);
    fHistEne->SetFillColor(kBlack);
    fHistEne->Draw();
    fHistEneTag->SetFillStyle(3005);
    fHistEneTag->SetFillColor(kBlack);
    fHistEneTag->SetLineColor(kRed);
    fHistEneTag->Draw("same");
    leg = new TLegend(.3,0.7,0.6,0.9);
    leg->AddEntry(fHistEne,"Energy per event for all events","f");
    leg->AddEntry(fHistEneTag,"Energy per event for events with an electron","f");
    leg->Draw();
    gPad->SetLogy();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/EnergyOverlay_MB.png"));
    
    fHistInvMassUnlike->SetFillStyle(3004);
    fHistInvMassUnlike->SetFillColor(kBlack);
    fHistInvMassUnlike->Draw();
    fHistInvMassLike->SetFillStyle(3005);
    fHistInvMassLike->SetFillColor(kBlack);
    fHistInvMassLike->SetLineColor(kRed);
    fHistInvMassLike->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistInvMassLike,"Invariant mass for like-signed electron pairs","f");
    leg->AddEntry(fHistInvMassUnlike,"Invariant mass for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/InvMassOverlay_MB.png"));
    
    fHistOpAngUnlike->SetFillStyle(3004);
    fHistOpAngUnlike->SetFillColor(kBlack);
    fHistOpAngUnlike->Draw();
    fHistOpAngLike->SetFillStyle(3005);
    fHistOpAngLike->SetFillColor(kBlack);
    fHistOpAngLike->SetLineColor(kRed);
    fHistOpAngLike->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistOpAngLike,"Opening angle for like-signed electron pairs","f");
    leg->AddEntry(fHistOpAngUnlike,"Opening angle for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/OpAngOverlay_MB.png"));
    
    fHistTPCSig->SetFillStyle(3004);
    fHistTPCSig->SetFillColor(kBlack);
    fHistTPCSig->Draw();
    fHistTPCSigCut->SetFillStyle(3005);
    fHistTPCSigCut->SetFillColor(kBlack);
    fHistTPCSigCut->SetLineColor(kRed);
    fHistTPCSigCut->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistTPCSig,"TPC dE/dx resolution for all tracks","f");
    leg->AddEntry(fHistTPCSigCut,"TPC dE/dx resolution for tracks that pass HFE track cuts","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/TPCSigOverlay_MB.png"));
    
    gStyle->SetOptStat(1);               
               
    for(Int_t i=0; i<=EMC7->LastIndex();i++){
        TH1 *hist = (TH1*)EMC7->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistDPhi18Spe_EMC7")==0){
            hist->GetYaxis()->SetBinLabel(1,"Unknown");
            hist->GetYaxis()->SetBinLabel(2,"Electron");
            hist->GetYaxis()->SetBinLabel(3,"Muon");
            hist->GetYaxis()->SetBinLabel(4,"Pion");
            hist->GetYaxis()->SetBinLabel(5,"Kaon");
            hist->GetYaxis()->SetBinLabel(6,"Proton");
            hist->GetYaxis()->SetBinLabel(7,"Deuteron");
        }
        if(strcmp(hist->GetName(),"fHistImpPar_EMC7")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistImpParTag_EMC7")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistPtSum_EMC7")==0){
            fHistEne = hist;
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistPtSumTag_EMC7")==0){
            fHistEneTag = hist;
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecLike_EMC7")==0){
            fHistInvMassLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecUnLike_EMC7")==0){
            fHistInvMassUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecLike_EMC7")==0){
            fHistOpAngLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecUnLike_EMC7")==0){
            fHistOpAngUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSig_EMC7")==0){
            fHistTPCSig = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSigCut_EMC7")==0){
            fHistTPCSigCut = hist;
        }
        if(strcmp(hist->GetName(),"fHistITSNClus_EMC7")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_EMC7")==0){
            gPad-> SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistEtaPhiTag_EMC7")==0){
            gPad->SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultAway_EMC7")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMin_EMC7")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMax_EMC7")==0){
            gPad-> SetLogy();
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='C'&&hist->GetName()[8]=='_'){
            TLine *sigBot = new TLine(0, -2, 10, -2);
            TLine *sigTop = new TLine(0, 2, 10, 2);
            sigBot->SetLineColor(kRed);
            sigTop->SetLineColor(kRed);
            sigBot->SetLineWidth(2);
            sigTop->SetLineWidth(2);
            sigBot->Draw();
            sigTop->Draw();
            TH2F* hist2d = (TH2F*)EMC7->At(i);
            TH1D *histProj = hist2d->ProjectionY(Form("%s_py", hist->GetName()));
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            TLine *sigTRD = new TLine(0, .9, 10, .9);
            sigTRD->SetLineColor(kRed);
            sigTRD->SetLineWidth(2);
            sigTRD->Draw();
        }
        if(hist->GetName()[5]=='M'&&hist->GetName()[6]=='0'&&hist->GetName()[7]=='2'){
            TLine *sigM02 = new TLine(0.5, 0, 0.5, 2);
            sigM02->SetLineColor(kRed);
            sigM02->SetLineWidth(1);
            sigM02->Draw();
        }
        if(hist->GetName()[5]=='M'&&hist->GetName()[6]=='2'&&hist->GetName()[7]=='0'){
            TLine *sigM20 = new TLine(0.3, 0, 0.3, 2);
            sigM20->SetLineColor(kRed);
            sigM20->SetLineWidth(1);
            sigM20->Draw();
        }
        if(hist->GetName()[5]=='E'&&hist->GetName()[6]=='M'&&hist->GetName()[7]=='C'){
           if(hist->GetName()[-4]=='6'){
                TLine *sigEBot = new TLine(.95, 0, .95, hist->GetMaximum());
                TLine *sigETop = new TLine(1.25, 0, 1.25, hist->GetMaximum());
                sigEBot->SetLineColor(kRed);
                sigETop->SetLineColor(kRed);
                sigEBot->SetLineWidth(2);
                sigETop->SetLineWidth(2);
                sigEBot->Draw();
                sigETop->Draw();
            }
            else{
                TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
                TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
                sigEBot->SetLineColor(kRed);
                sigETop->SetLineColor(kRed);
                sigEBot->SetLineWidth(2);
                sigETop->SetLineWidth(2);
                sigEBot->Draw();
                sigETop->Draw();
            }
            
            c1->Update();
            TPaveStats *ps = (TPaveStats*)hist->FindObject("stats");
            ps->SetX1NDC(.1);
            ps->SetX2NDC(.4);
            
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'){
            TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
            TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);
            
            if(hist->GetName()[21]=='1'){
                TF1* hadFit = new TF1("hadFit", "gaus", 0.2, 0.8);
                TF1* totalFit = new TF1("totalFit", "gaus(0)+gaus(3)+pol0(6)", 0.2, 1.2);
            }
            
            totalFit->SetParName(0,"Scale_elecFit");
            totalFit->SetParName(1,"Mean_elecFit");
            totalFit->SetParName(2,"Sigma_elecFit");
            totalFit->SetParName(3,"Pedestal_hadCont");
            
            if(hist->GetName()[21]=='1'){
                totalFit->SetParName(3,"Scale_hadFit");
                totalFit->SetParName(4,"Mean_hadFit");
                totalFit->SetParName(5,"Sigma_hadFit");
                totalFit->SetParName(6,"Pedestal_hadCont");
            }
            
            totalFit->SetParameter(0,10);
            totalFit->SetParameter(1,1);
            totalFit->SetParameter(2,.4);
            totalFit->SetParLimits(3, 0, 1000000);
            totalFit->SetParLimits(0, 0, 10000);
                
            if(hist->GetName()[21]=='1'){
                totalFit->SetParameter(3,30);
                totalFit->SetParameter(4,.4);
                totalFit->SetParameter(5,.8);
                totalFit->SetParLimits(3, 0, 100);
                totalFit->SetParLimits(4, 0, .7);
                totalFit->SetParLimits(0, 0, 1000);
                totalFit->SetParLimits(6, 0, 1000000);
            }
                
            hist->Fit(totalFit, "B");
            elecFit->SetParameters(totalFit->GetParameters());
            Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
            cout<<purity<<"\n";
            switch(hist->GetName()[21]){
                case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_EMC7[0]=purity;
                    NElec_EMC7[0]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_EMC7[1]=purity;
                    NElec_EMC7[1]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_EMC7[2]=purity;
                    NElec_EMC7[1]=NElec_EMC7[1]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_EMC7[3]=purity;
                    NElec_EMC7[2]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_EMC7[4]=purity;
                    NElec_EMC7[2]=NElec_EMC7[2]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
            }
            }
        }
        if(hist->GetName()[5]=='D'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='h'){
            switch(hist->GetName()[15]){
            case '1':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%d trigger electrons",NElec_EMC7[0]));
                pt->Draw();
                break;
            case '2':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%d trigger electrons",NElec_EMC7[1]));
                pt->Draw();
                break;
            case '4':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%d trigger electrons",NElec_EMC7[2]));
                pt->Draw();
                break;
            }
        }
        if(hist->GetName()[5]=='N'&&hist->GetName()[6]=='e'&&hist->GetName()[7]=='v'){
            gPad->SetLogy();
        }
        if(hist->GetName()[5]=='I'&&hist->GetName()[6]=='T'&&hist->GetName()[7]=='S'){
            TLine *ITScut = new TLine(4, 0, 4, hist->GetMaximum());
            ITScut->SetLineColor(kRed);
            ITScut->SetLineWidth(2);
            ITScut->Draw();
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='C'&&hist->GetName()[8]=='N'){
            TLine *TPCcut = new TLine(120, 0, 120, hist->GetMaximum());
            TPCcut->SetLineColor(kRed);
            TPCcut->SetLineWidth(2);
            TPCcut->Draw();
        }
        gStyle->SetOptFit(2);
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakSS/%s.png", hist->GetName()));
       
        if(!histProj){continue;}
        histProj->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakSS/%s.png", histProj->GetName()));
    }
               
    fHistEne->SetStats(0);
    fHistEneTag->SetStats(0);
    fHistInvMassLike->SetStats(0);
    fHistInvMassUnlike->SetStats(0);
    fHistOpAngLike->SetStats(0);
    fHistOpAngUnlike->SetStats(0);
    fHistTPCSig->SetStats(0);
    fHistTPCSigCut->SetStats(0);
    //Draw overlays
    fHistEne->SetFillStyle(3004);
    fHistEne->SetFillColor(kBlack);
    fHistEne->Draw();
    fHistEneTag->SetFillStyle(3005);
    fHistEneTag->SetFillColor(kBlack);
    fHistEneTag->SetLineColor(kRed);
    fHistEneTag->Draw("same");
    leg = new TLegend(.3,0.7,0.6,0.9);
    leg->AddEntry(fHistEne,"Energy per event for all events","f");
    leg->AddEntry(fHistEneTag,"Energy per event for events with an electron","f");
    leg->Draw();
    gPad->SetLogy();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/EnergyOverlay_EMC7.png"));
    
    fHistInvMassUnlike->SetFillStyle(3004);
    fHistInvMassUnlike->SetFillColor(kBlack);
    fHistInvMassUnlike->Draw();
    fHistInvMassLike->SetFillStyle(3005);
    fHistInvMassLike->SetFillColor(kBlack);
    fHistInvMassLike->SetLineColor(kRed);
    fHistInvMassLike->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistInvMassLike,"Invariant mass for like-signed electron pairs","f");
    leg->AddEntry(fHistInvMassUnlike,"Invariant mass for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/InvMassOverlay_EMC7.png"));
    
    fHistOpAngUnlike->SetFillStyle(3004);
    fHistOpAngUnlike->SetFillColor(kBlack);
    fHistOpAngUnlike->Draw();
    fHistOpAngLike->SetFillStyle(3005);
    fHistOpAngLike->SetFillColor(kBlack);
    fHistOpAngLike->SetLineColor(kRed);
    fHistOpAngLike->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistOpAngLike,"Opening angle for like-signed electron pairs","f");
    leg->AddEntry(fHistOpAngUnlike,"Opening angle for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/OpAngOverlay_EMC7.png"));
    
    fHistTPCSig->SetFillStyle(3004);
    fHistTPCSig->SetFillColor(kBlack);
    fHistTPCSig->Draw();
    fHistTPCSigCut->SetFillStyle(3005);
    fHistTPCSigCut->SetFillColor(kBlack);
    fHistTPCSigCut->SetLineColor(kRed);
    fHistTPCSigCut->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistTPCSig,"TPC dE/dx resolution for all tracks","f");
    leg->AddEntry(fHistTPCSigCut,"TPC dE/dx resolution for tracks that pass HFE track cuts","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/TPCSigOverlay_EMC7.png"));
    
    gStyle->SetOptStat(1);  
    
    for(Int_t i=0; i<=EMCJet->LastIndex();i++){
        TH1 *hist = (TH1*)EMCJet->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistDPhi18Spe_EMCJet")==0){
            hist->GetYaxis()->SetBinLabel(1,"Unknown");
            hist->GetYaxis()->SetBinLabel(2,"Electron");
            hist->GetYaxis()->SetBinLabel(3,"Muon");
            hist->GetYaxis()->SetBinLabel(4,"Pion");
            hist->GetYaxis()->SetBinLabel(5,"Kaon");
            hist->GetYaxis()->SetBinLabel(6,"Proton");
            hist->GetYaxis()->SetBinLabel(7,"Deuteron");
        }
        if(strcmp(hist->GetName(),"fHistImpPar_EMCJet")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistImpParTag_EMCJet")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistPtSum_EMCJet")==0){
            fHistEne = hist;
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistPtSumTag_EMCJet")==0){
            fHistEneTag = hist;
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecLike_EMCJet")==0){
            fHistInvMassLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecUnLike_EMCJet")==0){
            fHistInvMassUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecLike_EMCJet")==0){
            fHistOpAngLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecUnLike_EMCJet")==0){
            fHistOpAngUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSig_EMCJet")==0){
            fHistTPCSig = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSigCut_EMCJet")==0){
            fHistTPCSigCut = hist;
        }
        if(strcmp(hist->GetName(),"fHistITSNClus_EMCJet")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_EMCJet")==0){
            gPad-> SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistEtaPhiTag_EMCJet")==0){
            gPad->SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultAway_EMCJet")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMin_EMCJet")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMax_EMCJet")==0){
            gPad-> SetLogy();
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='C'&&hist->GetName()[8]=='_'){
            TLine *sigBot = new TLine(0, -2, 10, -2);
            TLine *sigTop = new TLine(0, 2, 10, 2);
            sigBot->SetLineColor(kRed);
            sigTop->SetLineColor(kRed);
            sigBot->SetLineWidth(2);
            sigTop->SetLineWidth(2);
            sigBot->Draw();
            sigTop->Draw();
            TH2F* hist2d = (TH2F*)EMCJet->At(i);
            TH1D *histProj = hist2d->ProjectionY(Form("%s_py", hist->GetName()));
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            TLine *sigTRD = new TLine(0, .9, 10, .9);
            sigTRD->SetLineColor(kRed);
            sigTRD->SetLineWidth(2);
            sigTRD->Draw();
        }
        if(hist->GetName()[5]=='M'&&hist->GetName()[6]=='0'&&hist->GetName()[7]=='2'){
            TLine *sigM02 = new TLine(0.5, 0, 0.5, 2);
            sigM02->SetLineColor(kRed);
            sigM02->SetLineWidth(1);
            sigM02->Draw();
        }
        if(hist->GetName()[5]=='M'&&hist->GetName()[6]=='2'&&hist->GetName()[7]=='0'){
            TLine *sigM20 = new TLine(0.3, 0, 0.3, 2);
            sigM20->SetLineColor(kRed);
            sigM20->SetLineWidth(1);
            sigM20->Draw();
        }
        if(hist->GetName()[5]=='E'&&hist->GetName()[6]=='M'&&hist->GetName()[7]=='C'){
            if(hist->GetName()[-4]=='6'){
                TLine *sigEBot = new TLine(.95, 0, .95, hist->GetMaximum());
                TLine *sigETop = new TLine(1.25, 0, 1.25, hist->GetMaximum());
                sigEBot->SetLineColor(kRed);
                sigETop->SetLineColor(kRed);
                sigEBot->SetLineWidth(2);
                sigETop->SetLineWidth(2);
                sigEBot->Draw();
                sigETop->Draw();
            }
            else{
                TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
                TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
                sigEBot->SetLineColor(kRed);
                sigETop->SetLineColor(kRed);
                sigEBot->SetLineWidth(2);
                sigETop->SetLineWidth(2);
                sigEBot->Draw();
                sigETop->Draw();
            }
            
            c1->Update();
            TPaveStats *ps = (TPaveStats*)hist->FindObject("stats");
            ps->SetX1NDC(.1);
            ps->SetX2NDC(.4);
            
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'){
            TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
            TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);
            totalFit->SetParName(0,"Scale");
            totalFit->SetParName(1,"Mean");
            totalFit->SetParName(2,"Sigma");
            totalFit->SetParName(3,"Pedestal");
            totalFit->SetParameter(0,8);
            totalFit->SetParameter(1,1);
            totalFit->SetParameter(2,.4);
            totalFit->SetParLimits(3, 0, 1000000);
            totalFit->SetParLimits(0, 0, 10000);
            hist->Fit(totalFit, "BLL");
            elecFit->SetParameters(totalFit->GetParameters());
            Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
            cout<<purity<<"\n";
            switch(hist->GetName()[23]){
                case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_EMCJet[0]=purity;
                    NElec_EMCJet[0]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_EMCJet[1]=purity;
                    NElec_EMCJet[1]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_EMCJet[2]=purity;
                    NElec_EMCJet[1]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_EMCJet[3]=purity;
                    NElec_EMCJet[2]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_EMCJet[4]=purity;
                    NElec_EMCJet[2]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
            }
            }
        }
        if(hist->GetName()[5]=='N'&&hist->GetName()[6]=='e'&&hist->GetName()[7]=='v'){
            gPad->SetLogy();
        }
        if(hist->GetName()[5]=='I'&&hist->GetName()[6]=='T'&&hist->GetName()[7]=='S'){
            TLine *ITScut = new TLine(4, 0, 4, hist->GetMaximum());
            ITScut->SetLineColor(kRed);
            ITScut->SetLineWidth(2);
            ITScut->Draw();
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='C'&&hist->GetName()[8]=='N'){
            TLine *TPCcut = new TLine(120, 0, 120, hist->GetMaximum());
            TPCcut->SetLineColor(kRed);
            TPCcut->SetLineWidth(2);
            TPCcut->Draw();
        }
        gStyle->SetOptFit(2);
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakSS/%s.png", hist->GetName()));
        
	if(!histProj){continue;}        
        histProj->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakSS/%s.png", histProj->GetName()));
    }
    
    fHistEne->SetStats(0);
    fHistEneTag->SetStats(0);
    fHistInvMassLike->SetStats(0);
    fHistInvMassUnlike->SetStats(0);
    fHistOpAngLike->SetStats(0);
    fHistOpAngUnlike->SetStats(0);
    fHistTPCSig->SetStats(0);
    fHistTPCSigCut->SetStats(0);
    //Draw overlays
    fHistEne->SetFillStyle(3004);
    fHistEne->SetFillColor(kBlack);
    fHistEne->Draw();
    fHistEneTag->SetFillStyle(3005);
    fHistEneTag->SetFillColor(kBlack);
    fHistEneTag->SetLineColor(kRed);
    fHistEneTag->Draw("same");
    leg = new TLegend(.3,0.7,0.6,0.9);
    leg->AddEntry(fHistEne,"Energy per event for all events","f");
    leg->AddEntry(fHistEneTag,"Energy per event for events with an electron","f");
    leg->Draw();
    gPad->SetLogy();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/EnergyOverlay_EMCJet.png"));
    
    fHistInvMassUnlike->SetFillStyle(3004);
    fHistInvMassUnlike->SetFillColor(kBlack);
    fHistInvMassUnlike->Draw();
    fHistInvMassLike->SetFillStyle(3005);
    fHistInvMassLike->SetFillColor(kBlack);
    fHistInvMassLike->SetLineColor(kRed);
    fHistInvMassLike->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistInvMassLike,"Invariant mass for like-signed electron pairs","f");
    leg->AddEntry(fHistInvMassUnlike,"Invariant mass for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/InvMassOverlay_EMCJet.png"));
    
    fHistOpAngUnlike->SetFillStyle(3004);
    fHistOpAngUnlike->SetFillColor(kBlack);
    fHistOpAngUnlike->Draw();
    fHistOpAngLike->SetFillStyle(3005);
    fHistOpAngLike->SetFillColor(kBlack);
    fHistOpAngLike->SetLineColor(kRed);
    fHistOpAngLike->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistOpAngLike,"Opening angle for like-signed electron pairs","f");
    leg->AddEntry(fHistOpAngUnlike,"Opening angle for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/OpAngOverlay_EMCJet.png"));
    
    fHistTPCSig->SetFillStyle(3004);
    fHistTPCSig->SetFillColor(kBlack);
    fHistTPCSig->Draw();
    fHistTPCSigCut->SetFillStyle(3005);
    fHistTPCSigCut->SetFillColor(kBlack);
    fHistTPCSigCut->SetLineColor(kRed);
    fHistTPCSigCut->Draw("same");
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistTPCSig,"TPC dE/dx resolution for all tracks","f");
    leg->AddEntry(fHistTPCSigCut,"TPC dE/dx resolution for tracks that pass HFE track cuts","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakSS/TPCSigOverlay_EMCJet.png"));
    
    gStyle->SetOptStat(1);
    
    Double_t x[5]={1.5, 2.5, 3.5, 4.5, 5.5};
    
    for(Int_t i=0; i<5; i++){
        cout<<i<<","<<x[i]<<","<<purity_EMC7[i];
    }
    
    TGraph* purityGraph_MB = new TGraph(5, x, purity_MB);
    TGraph* purityGraph_EMC7 = new TGraph(5, x, purity_EMC7);
    TGraph* purityGraph_EMCJet = new TGraph(5, x, purity_EMCJet);
    
    cout<<"is the issue here?";
    gPad->SetLogy(0);
    c1->SetGrid();
    purityGraph_MB->GetXaxis()->SetTitle("Pt");
    purityGraph_MB->GetYaxis()->SetTitle("Electron purity");
    purityGraph_MB->SetTitle("MB Electron Purity after TPC, TRD, EMC cuts");
    purityGraph_MB->SetMinimum(0);
    purityGraph_MB->SetMaximum(1);
    purityGraph_MB->Draw("A*");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakSS/ElecPurity_MB.png");

    c1->SetGrid();
    purityGraph_EMC7->GetXaxis()->SetTitle("Pt");
    purityGraph_EMC7->GetYaxis()->SetTitle("Electron purity");
    purityGraph_EMC7->SetTitle("EMC7 Electron Purity after TPC, TRD, EMC cuts");
    purityGraph_EMC7->SetMinimum(0);
    purityGraph_EMC7->SetMaximum(1);
    purityGraph_EMC7->Draw("A*");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakSS/ElecPurity_EMC7.png");
    
    c1->SetGrid();
    purityGraph_EMCJet->Draw("A*");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakSS/ElecPurity_EMCJet.png");
    return;
}
