void savScrip(){
    TFile *file = new TFile("./AnalysisResults.root");
    TList *PID = (TList*)file->Get("PIDqa");
    TList *MB = (TList*)file->Get("Min-Bias");
    TList *EMC7 = (TList*)file->Get("EMCal7");
    TList *EMC8 = (TList*)file->Get("EMCal8");
    TList *EMCJet = (TList*)file->Get("EMCalJet");
    
    TCanvas *c1 = new TCanvas();
    c1->cd(1);
    
    Double_t purity_MB[5];
    Double_t purity_EMC7[5];
    Double_t purity_EMC8[5];
    Double_t purity_EMCJet[5];
    
    TList *TPC = (TList*)PID->FindObject("TPC");
    TList *TPCBasic = (TList*)TPC->FindObject("TPCBasic");
    TH2F *TPCnSig = (TH2F*)TPCBasic->FindObject("hNsigmaP_TPC_Basic_electron");
    TPCnSig->Draw("colz");
    c1->Update();
    c1->SaveAs("./plotsKlay/TPCnSigmaRaw.png");
    
    //TList *TRD = (TList*)PID->FindObject("TRD");
    //TList *TRDLikelihood = (TList*)TRD->FindObject("TRDLikelihood");
    //TH2F *TRDLike = (TH2F*)TRD->FindObject("hLikeP_TRD_5tls_electron");
    //TRDLike->Draw("colz");
    //c1->Update();
    //c1->SaveAs("./plotsKlay/TRDelecLikeRaw.png");

    TList *TOF = (TList*)PID->FindObject("TOF");
    TH2F *TOFnSig = (TH2F*)TOF->FindObject("hNsigmaP_TOF_electron");
    TOFnSig->Draw("colz");
    c1->Update();
    c1->SaveAs("./plotsKlay/TOFnSigmaRaw.png");

    TList *EMC = (TList*)PID->FindObject("EMCAL");
    TH2F *EMCnSig = (TH2F*)EMC->FindObject("hNsigmaPt_EMCAL_electron");
    EMCnSig->Draw("colz");
    c1->Update();
    c1->SaveAs("./plotsKlay/EMCnSigmaRaw.png");

    
    for(Int_t i=0; i<=MB->LastIndex();i++){
        TH1 *hist = (TH1*)MB->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistPIDRejection")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistEng_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistEngTag_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistITSNClus_MB")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_MB")==0){
            gPad-> SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultAway_MB")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMin_MB")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMax_MB")==0){
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
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            TLine *sigTRD = new TLine(0, .9, 10, .9);
            sigTRD->SetLineColor(kRed);
            sigTRD->SetLineWidth(2);
            sigTRD->Draw();
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
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'){
            TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
            TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);
            totalFit->SetParameter(0,8);
            totalFit->SetParameter(1,1);
            totalFit->SetParameter(2,.4);
            totalFit->SetParLimits(3, 0, 1000000);
            totalFit->SetParLimits(0, 0, 10000);
            hist->Fit(totalFit, "BLL");
            elecFit->SetParameters(totalFit->GetParameters());
            Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
            cout<<purity<<"\n"<<hist->GetName()[19]<<"\n";
            switch(hist->GetName()[19]){
                case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_MB[0]=purity;
                    break;
                case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_MB[1]=purity;
                    break;
                case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_MB[2]=purity;
                    break;
                case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_MB[3]=purity;
                    break;
                case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_MB[4]=purity;
                    break;
            }
            }
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'&&hist->GetName()[19]=='1'){
                TF1* hadFit = new TF1("hadFit", "landau", 0.2, 1.2);
                TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
                TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)+landau(4)", 0.2, 1.2);
                Double_t *p;
                Double_t elec_par[3];
                Double_t had_par[3];
                totalFit->SetParameter(0,8);
                totalFit->SetParameter(1,1);
                totalFit->SetParameter(2,.4);
                totalFit->SetParameter(4, 8);
                totalFit->SetParameter(5, .8);
                totalFit->SetParameter(6, .1);
                totalFit->SetParLimits(3, 0, 1000000);
                totalFit->SetParLimits(0, 0, 10000);
                hist->Fit(totalFit, "BLL");
                totalFit->GetParameters(p);
                elec_par = &p[0];
                had_par = &p[4];
                elecFit->SetParameters(elec_par);
                hadFit->SetParameters(had_par);
                Double_t purity = elecFit->Integral(0.8, 1.2)/(totalFit->Integral(0.8, 1.2)-hadFit->Integral(0.8, 1.2));
                cout<<purity<<'\n';
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
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));
    }
    
    for(Int_t i=0; i<=EMC7->LastIndex();i++){
        TH1 *hist = (TH1*)EMC7->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistITSNClus_EMC7")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_EMC7")==0){
            gPad-> SetLogz();
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
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            TLine *sigTRD = new TLine(0, .9, 10, .9);
            sigTRD->SetLineColor(kRed);
            sigTRD->SetLineWidth(2);
            sigTRD->Draw();
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
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'){
            TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
            TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);
            totalFit->SetParameter(0,8);
            totalFit->SetParameter(1,1);
            totalFit->SetParameter(2,.4);
            totalFit->SetParLimits(3, 0, 1000000);
            totalFit->SetParLimits(0, 0, 10000);
            hist->Fit(totalFit, "BLL");
            elecFit->SetParameters(totalFit->GetParameters());
            Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
            cout<<purity<<"\n";
            switch(hist->GetName()[21]){
                case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_EMC7[0]=purity;
                    break;
                case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_EMC7[1]=purity;
                    break;
                case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_EMC7[2]=purity;
                    break;
                case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_EMC7[3]=purity;
                    break;
                case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_EMC7[4]=purity;
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
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));
    }
    
    for(Int_t i=0; i<=EMC8->LastIndex();i++){
        TH1 *hist = (TH1*)EMC8->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistITSNClus_EMC8")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_EMC8")==0){
            gPad-> SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultAway_EMC8")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMin_EMC8")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMax_EMC8")==0){
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
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            TLine *sigTRD = new TLine(0, .9, 10, .9);
            sigTRD->SetLineColor(kRed);
            sigTRD->SetLineWidth(2);
            sigTRD->Draw();
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
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'){
            TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
            TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);
            totalFit->SetParameter(0,8);
            totalFit->SetParameter(1,1);
            totalFit->SetParameter(2,.4);
            totalFit->SetParLimits(3, 0, 1000000);
            totalFit->SetParLimits(0, 0, 10000);
            hist->Fit(totalFit, "BLL");
            elecFit->SetParameters(totalFit->GetParameters());
            Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
            cout<<purity<<"\n";
            switch(hist->GetName()[21]){
                case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_EMC8[0]=purity;
                    break;
                case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_EMC8[1]=purity;
                    break;
                case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_EMC8[2]=purity;
                    break;
                case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_EMC8[3]=purity;
                    break;
                case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_EMC8[4]=purity;
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
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));
    }
    
    for(Int_t i=0; i<=EMCJet->LastIndex();i++){
        TH1 *hist = (TH1*)EMCJet->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistITSNClus_EMCJet")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_EMCJet")==0){
            gPad-> SetLogz();
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
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            TLine *sigTRD = new TLine(0, .9, 10, .9);
            sigTRD->SetLineColor(kRed);
            sigTRD->SetLineWidth(2);
            sigTRD->Draw();
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
            if(hist->GetName()[9]=='T'&&hist->GetName()[10]=='P'&&hist->GetName()[11]=='C'&&hist->GetName()[12]=='T'&&hist->GetName()[13]=='R'){
            TF1* elecFit = new TF1("elecFit", "gaus", 0.8, 1.2);
            TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);
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
                    break;
                case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_EMCJet[1]=purity;
                    break;
                case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_EMCJet[2]=purity;
                    break;
                case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_EMCJet[3]=purity;
                    break;
                case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_EMCJet[4]=purity;
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
        c1->Update();
        c1->SaveAs(Form("./plotsKlay/%s.png", hist->GetName()));
    }
    
    Double_t x[5]={1.5, 2.5, 3.5, 4.5, 5.5};
    
    for(Int_t i=0; i<5; i++){
        cout<<i<<","<<x[i]<<","<<purity_EMC7[i];
    }
    
    TGraph* purityGraph_MB = new TGraph(5, x, purity_MB);
    TGraph* purityGraph_EMC7 = new TGraph(5, x, purity_EMC7);
    TGraph* purityGraph_EMC8 = new TGraph(5, x, purity_EMC8);
    TGraph* purityGraph_EMCJet = new TGraph(5, x, purity_EMCJet);
    
    cout<<"is the issue here?";
    
    purityGraph_MB->Draw("A*");
    c1->SetGrid();
    c1->Update();
    c1->SaveAs("./plotsKlay/ElecPurity_MB.png");
    
    purityGraph_EMC7->Draw("A*");
    c1->SetGrid();
    c1->Update();
    c1->SaveAs("./plotsKlay/ElecPurity_EMC7.png");
    
    purityGraph_EMC8->Draw("A*");
    c1->SetGrid();
    c1->Update();
    c1->SaveAs("./plotsKlay/ElecPurity_EMC8.png");
    
    purityGraph_EMCJet->Draw("A*");
    c1->SetGrid();
    c1->Update();
    c1->SaveAs("./plotsKlay/ElecPurity_EMCJet.png");
    return;
}
