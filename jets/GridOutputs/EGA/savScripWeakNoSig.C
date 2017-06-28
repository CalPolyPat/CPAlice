void savScripWeakNoSig(){
    TFile *file = new TFile("./AnalysisResults.root");
    //TList *PID = (TList*)file->Get("PIDqa");
    TList *MB = (TList*)file->Get("Min-Bias_Weak_NoSS_NoSig");
    TList *EMC7 = (TList*)file->Get("EMCal7_Weak_NoSS_NoSig");
    TList *EMCEGA = (TList*)file->Get("EMCalEGA_Weak_NoSS_NoSig");
    TList *EMCJet = (TList*)file->Get("EMCalJet_Weak_NoSS_NoSig");

    TCanvas *c1 = new TCanvas();
    c1->cd(1);

    Double_t purity_MB[5];
    Double_t purity_EMC7[5];
    Double_t purity_EMCEGA[5];
    Double_t purity_EMCJet[5];

    //Some variables to hold number of electrons
    Double_t NElec_MB[3]={0,0,0};
    Double_t NElec_EMC7[3]={0,0,0};
    Double_t NElec_EMCEGA[3]={0,0,0};
    Double_t NElec_EMCJet[3]={0,0,0};

    Double_t NTot_MB[5]={0,0,0,0,0};
    Double_t NSig_MB[5]={0,0,0,0,0};
    Double_t NTot_EMC7[5]={0,0,0,0,0};
    Double_t NSig_EMC7[5]={0,0,0,0,0};
    Double_t NTot_EMCEGA[5]={0,0,0,0,0};
    Double_t NSig_EMCEGA[5]={0,0,0,0,0};
    Double_t NTot_EMCJet[5]={0,0,0,0,0};
    Double_t NSig_EMCJet[5]={0,0,0,0,0};

    TH1* fHistEne;//Make histos for overlays
    TH1* fHistEneTag;

    TH1* fHistInvMassLike;
    TH1* fHistInvMassUnlike;

    TH1* fHistOpAngLike;
    TH1* fHistOpAngUnlike;

    TH1* fHistTPCSig;
    TH1* fHistTPCSigCut;
    

    //histos for combining pt bins
    TH1* fHistTPC_1;
    TH1* fHistTPC_2;
    TH1* fHistTPC_3;
    TH1* fHistTPC_4;
    TH1* fHistTPC_5;
    TH1* fHistTPC_6;

    TH1* fHistTRD_1;
    TH1* fHistTRD_2;
    TH1* fHistTRD_3;
    TH1* fHistTRD_4;
    TH1* fHistTRD_5;
    TH1* fHistTRD_6;

    TH1* fHistEMC_1;
    TH1* fHistEMC_2;
    TH1* fHistEMC_3;
    TH1* fHistEMC_4;
    TH1* fHistEMC_5;
    TH1* fHistEMC_6;

    TH1* fHistDPhi[150];
    TH1* fHistDPhiMix[150];
    Int_t ind=0;
    Int_t indMix=0;

    Double_t MB_mis=0;
    Double_t EMC7_mis=0;
    Double_t EMCEGA_mis=0;
    Double_t EMCJet_mis=0;

    Int_t NElec6_MB=0;
    Int_t NElec6_EMC7=0;
    Int_t NElec6_EMCEGA=0;
    Int_t NElec6_EMCJet=0;

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

    gStyle->SetTextFont(132);
    for(Int_t i=0; i<=MB->LastIndex();i++){
        TH1 *hist = (TH1*)MB->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistPhotoMismatch_MB")==0){
            MB_mis = hist->GetEntries();
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
            switch(hist->GetName()[19]){
                case '1':
                fHistTPC_1=hist;
                break;
                case '2':
                fHistTPC_2=hist;
                break;
                case '3':
                fHistTPC_3=hist;
                break;
                case '4':
                fHistTPC_4=hist;
                break;
                case '5':
                fHistTPC_5=hist;
                break;
                case '>':
                fHistTPC_6=hist;
                break;
            }
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
            switch(hist->GetName()[19]){
                case '1':
                fHistTRD_1=hist;
                break;
                case '2':
                fHistTRD_2=hist;
                break;
                case '3':
                fHistTRD_3=hist;
                break;
                case '4':
                fHistTRD_4=hist;
                break;
                case '5':
                fHistTRD_5=hist;
                break;
                case '>':
                fHistTRD_6=hist;
                break;
            }
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
            switch(hist->GetName()[19]){
                case '1':
                fHistEMC_1= (TH1*)hist->Clone();
                break;
                case '2':
                fHistEMC_2= (TH1*)hist->Clone();
                break;
                case '3':
                fHistEMC_3= (TH1*)hist->Clone();
                break;
                case '4':
                fHistEMC_4= (TH1*)hist->Clone();
                break;
                case '5':
                fHistEMC_5= (TH1*)hist->Clone();
                break;
                case '>':
                fHistEMC_6= (TH1*)hist->Clone();
                break;
            }
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
                TF1* elecFit = new TF1("elecFit", "gaus", 0.2, 1.2);
                TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.2, 1.2);

                if(hist->GetName()[19]=='1'){
                    TF1* hadFit = new TF1("hadFit", "gaus", 0.2, 1.2);
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
                if(hist->GetName()[19]=='1'){
                    Double_t* par= new Double_t[];
                    par=totalFit->GetParameters();
                    hadFit->SetParameters(&par[3]);
                }
                Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
                cout<<purity<<"\n"<<hist->GetName()[19]<<"\n";
                elecFit->Draw("same");
                switch(hist->GetName()[19]){
                    case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_MB[0]=purity;
                    NElec_MB[0]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_MB[0]=totalFit->Integral(0.8, 1.2);
                    NSig_MB[0]=elecFit->Integral(0.8, 1.2);
                    hadFit->Draw("same");
                    break;
                    case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_MB[1]=purity;
                    NElec_MB[1]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_MB[1]=totalFit->Integral(0.8, 1.2);
                    NSig_MB[1]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_MB[2]=purity;
                    NElec_MB[1]=NElec_MB[1]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_MB[2]=totalFit->Integral(0.8, 1.2);
                    NSig_MB[2]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_MB[3]=purity;
                    NElec_MB[2]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_MB[3]=totalFit->Integral(0.8, 1.2);
                    NSig_MB[3]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_MB[4]=purity;
                    NElec_MB[2]=NElec_MB[2]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_MB[4]=totalFit->Integral(0.8, 1.2);
                    NSig_MB[4]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '>':
                    NElec6_MB = hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
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
            if(hist->GetName()[9]=='_'){
                fHistDPhi[ind]=hist;
                ind++;
            }
            cout<<hist->GetName()[12]<<'\n';
            if(hist->GetName()[12]=='_'){
                fHistDPhiMix[indMix]=hist;
                indMix++;
            }
            switch(hist->GetName()[15]){
                case '1':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_MB[0]));
                pt->Draw();
                hist->Scale(1/NElec_MB[0]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
                break;
                case '2':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_MB[1]));
                pt->Draw();
                hist->Scale(1/NElec_MB[1]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
                break;
                case '4':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_MB[2]));
                pt->Draw();
                hist->Scale(1/NElec_MB[2]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
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
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", hist->GetName()));

        if(!histProj){continue;}
        histProj->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", histProj->GetName()));
    }

    gStyle->SetOptStat(0);

    THStack* stackTPC=new THStack("st", "TPC nSigma after TRD and EMC cuts");
    fHistTPC_1->SetStats(0);
    fHistTPC_2->SetStats(0);
    fHistTPC_3->SetStats(0);
    fHistTPC_4->SetStats(0);
    fHistTPC_5->SetStats(0);
    fHistTPC_6->SetStats(0);
    stackTPC->Add(fHistTPC_1);
    stackTPC->Add(fHistTPC_2);
    stackTPC->Add(fHistTPC_3);
    stackTPC->Add(fHistTPC_4);
    stackTPC->Add(fHistTPC_5);
    stackTPC->Add(fHistTPC_6);
    stackTPC->Draw("nostackcol");
    stackTPC->GetXaxis()->SetTitle("Pt");
    stackTPC->GetYaxis()->SetTitle("nSigma");
    TLine *sigBot = new TLine(0, -2, 10, -2);
    TLine *sigTop = new TLine(0, 2, 10, 2);
    sigBot->SetLineColor(kRed);
    sigTop->SetLineColor(kRed);
    sigBot->SetLineWidth(2);
    sigTop->SetLineWidth(2);
    sigBot->Draw();
    sigTop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCFull_MB.png"));
    c1->Clear();

    THStack* stackTRD=new THStack("strd", "TRD electron liklihood after TPC and EMC cuts");
    fHistTRD_1->SetStats(0);
    fHistTRD_2->SetStats(0);
    fHistTRD_3->SetStats(0);
    fHistTRD_4->SetStats(0);
    fHistTRD_5->SetStats(0);
    fHistTRD_6->SetStats(0);
    stackTRD->Add(fHistTRD_1);
    stackTRD->Add(fHistTRD_2);
    stackTRD->Add(fHistTRD_3);
    stackTRD->Add(fHistTRD_4);
    stackTRD->Add(fHistTRD_5);
    stackTRD->Add(fHistTRD_6);
    stackTRD->Draw("nostackcol");
    stackTRD->GetXaxis()->SetTitle("Pt");
    stackTRD->GetYaxis()->SetTitle("Electron Liklihood");
    TLine *sigTRD = new TLine(0, .8, 10, .8);
    sigTRD->SetLineColor(kRed);
    sigTRD->SetLineWidth(2);
    sigTRD->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TRDFull_MB.png"));

    c1->Clear();

    c1->Divide(3,2);
    c1->cd(1);
    fHistEMC_1->SetTitle(";E/p[c^2];Cts");
    fHistEMC_1->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_1->GetMaximum()*1.1, "1-2Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_1->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_1->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(2);
    fHistEMC_2->SetTitle(";E/p[c^2];Cts");
    fHistEMC_2->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_2->GetMaximum()*1.1, "2-3Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_2->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_2->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(3);
    fHistEMC_3->SetTitle(";E/p[c^2];Cts");
    fHistEMC_3->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_3->GetMaximum()*1.1, "3-4Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_3->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_3->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(4);
    fHistEMC_4->SetTitle(";E/p[c^2];Cts");
    fHistEMC_4->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_4->GetMaximum()*1.1, "4-5Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_4->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_4->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(5);
    fHistEMC_5->SetTitle(";E/p[c^2];Cts");
    fHistEMC_5->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_5->GetMaximum()*1.1, "5-6Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_5->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_5->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(6);
    fHistEMC_6->SetTitle(";E/p[c^2];Cts");
    fHistEMC_6->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_6->GetMaximum()*1.1, ">6Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.95, 0, .95, fHistEMC_6->GetMaximum());
    TLine *sigETop = new TLine(1.25, 0, 1.25, fHistEMC_6->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EMCFull_MB.png"));

    c1=new TCanvas();

    gStyle->SetTextFont(132);
    //Draw overlays
    fHistEne->SetStats(0);
    fHistEneTag->SetStats(0);
    fHistInvMassLike->SetStats(0);
    fHistInvMassUnlike->SetStats(0);
    fHistOpAngLike->SetStats(0);
    fHistOpAngUnlike->SetStats(0);
    fHistTPCSig->SetStats(0);
    fHistTPCSigCut->SetStats(0);
    fHistInvMassLike->SetTitle(";Invariant Mass[Gev/c];Cts");
    fHistInvMassUnlike->SetTitle(";Invariant Mass[Gev/c];Cts");
    fHistOpAngLike->SetTitle(";Opening Angle[rad];Cts");
    fHistOpAngUnlike->SetTitle(";Opening Angle[rad];Cts");

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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EnergyOverlay_MB.png"));

    fHistInvMassUnlike->SetFillStyle(3004);
    fHistInvMassUnlike->SetFillColor(kBlack);
    fHistInvMassUnlike->Draw();
    fHistInvMassLike->SetFillStyle(3005);
    fHistInvMassLike->SetFillColor(kBlack);
    fHistInvMassLike->SetLineColor(kRed);
    fHistInvMassLike->Draw("same");
    TLine* InvCut = new TLine(.1, 0, .1, fHistInvMassUnlike->GetMaximum());
    InvCut->SetLineColor(kBlack);
    InvCut->SetLineWidth(2);
    InvCut->Draw();
    TLatex* titl = new TLatex(0.1, fHistInvMassUnlike->GetMaximum()*2.5, "Invariant Mass for electron pairs");
    titl->SetTextSize(0.05);
    titl->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/InvMassOverlay_MB.png"));

    fHistOpAngUnlike->SetFillStyle(3004);
    fHistOpAngUnlike->SetFillColor(kBlack);
    fHistOpAngUnlike->Draw();
    fHistOpAngLike->SetFillStyle(3005);
    fHistOpAngLike->SetFillColor(kBlack);
    fHistOpAngLike->SetLineColor(kRed);
    fHistOpAngLike->Draw("same");
    TLine* OpCut = new TLine(.1, 0, .1, fHistOpAngUnlike->GetMaximum());
    OpCut->SetLineColor(kBlack);
    OpCut->SetLineWidth(2);
    OpCut->Draw();
    leg = new TLegend(0.3,0.7,0.6,0.89);
    leg->AddEntry(fHistOpAngLike,"Like-signed electron pairs","p");
    leg->AddEntry(fHistOpAngUnlike,"Unlike-signed electron pairs","p");
    leg->SetTextSize(0.05);
    leg->SetBorderSize(0);
    leg->Draw();
    TLatex* titl = new TLatex(0.75, fHistOpAngUnlike->GetMaximum()*2.5, "Opening angle for electron pairs");
    titl->SetTextSize(0.05);
    titl->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/OpAngOverlay_MB.png"));

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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCSigOverlay_MB.png"));

    gStyle->SetOptStat(1);               

    for(Int_t i=0; i<=EMC7->LastIndex();i++){
        TH1 *hist = (TH1*)EMC7->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistPhotoMismatch_EMC7")==0){
            EMC7_mis = hist->GetEntries();
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
            switch(hist->GetName()[21]){
                case '1':
                fHistTPC_1=hist;
                break;
                case '2':
                fHistTPC_2=hist;
                break;
                case '3':
                fHistTPC_3=hist;
                break;
                case '4':
                fHistTPC_4=hist;
                break;
                case '5':
                fHistTPC_5=hist;
                break;
                case '>':
                fHistTPC_6=hist;
                break;
            }
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
            switch(hist->GetName()[21]){
                case '1':
                fHistTRD_1=hist;
                break;
                case '2':
                fHistTRD_2=hist;
                break;
                case '3':
                fHistTRD_3=hist;
                break;
                case '4':
                fHistTRD_4=hist;
                break;
                case '5':
                fHistTRD_5=hist;
                break;
                case '>':
                fHistTRD_6=hist;
                break;
            }
            TLine *sigTRD = new TLine(0, .8, 10, .8);
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
            switch(hist->GetName()[21]){
                case '1':
                fHistEMC_1=(TH1*)hist->Clone();
                break;
                case '2':
                fHistEMC_2=(TH1*)hist->Clone();
                break;
                case '3':
                fHistEMC_3=(TH1*)hist->Clone();
                break;
                case '4':
                fHistEMC_4=(TH1*)hist->Clone();
                break;
                case '5':
                fHistEMC_5=(TH1*)hist->Clone();
                break;
                case '>':
                fHistEMC_6=(TH1*)hist->Clone();
                break;
            }
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
                TF1* elecFit = new TF1("elecFit", "gaus", 0.2, 1.2);
                TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);

                if(hist->GetName()[21]=='1'){
                    TF1* hadFit = new TF1("hadFit", "gaus", 0.2, 1.2);
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
                if(hist->GetName()[21]=='1'){
                    Double_t* par= new Double_t[];
                    par=totalFit->GetParameters();
                    hadFit->SetParameters(&par[3]);
                }
                Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
                cout<<purity<<"\n";
                elecFit->Draw("same");
                switch(hist->GetName()[21]){
                    case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_EMC7[0]=purity;
                    NElec_EMC7[0]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMC7[0]=totalFit->Integral(0.8, 1.2);
                    NSig_EMC7[0]=elecFit->Integral(0.8, 1.2);
                    hadFit->Draw("same");
                    break;
                    case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_EMC7[1]=purity;
                    NElec_EMC7[1]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMC7[1]=totalFit->Integral(0.8, 1.2);
                    NSig_EMC7[1]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_EMC7[2]=purity;
                    NElec_EMC7[1]=NElec_EMC7[1]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMC7[2]=totalFit->Integral(0.8, 1.2);
                    NSig_EMC7[2]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_EMC7[3]=purity;
                    NElec_EMC7[2]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMC7[3]=totalFit->Integral(0.8, 1.2);
                    NSig_EMC7[3]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_EMC7[4]=purity;
                    NElec_EMC7[2]=NElec_EMC7[2]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMC7[4]=totalFit->Integral(0.8, 1.2);
                    NSig_EMC7[4]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '>':
                    NElec6_EMC7 = hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                }
            }
        }
        if(hist->GetName()[5]=='D'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='h'){
            if(hist->GetName()[9]=='_'){
                fHistDPhi[ind]=hist;
                ind++;
            }
            if(hist->GetName()[12]=='_'){
                fHistDPhiMix[indMix]=hist;
                indMix++;
            }
            switch(hist->GetName()[15]){
                case '1':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_EMC7[0]));
                pt->Draw();
                hist->Scale(1/NElec_EMC7[0]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
                break;
                case '2':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_EMC7[1]));
                pt->Draw();
                hist->Scale(1/NElec_EMC7[1]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
                break;
                case '4':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_EMC7[2]));
                pt->Draw();
                hist->Scale(1/NElec_EMC7[2]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
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
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", hist->GetName()));

        if(!histProj){continue;}
        histProj->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", histProj->GetName()));
    }

    c1=new TCanvas();

    gStyle->SetOptStat(0);


    THStack* stackTPC1=new THStack("st1", "TPC electron nSigma after TRD and EMC PID cuts");
    fHistTPC_1->SetStats(0);
    fHistTPC_2->SetStats(0);
    fHistTPC_3->SetStats(0);
    fHistTPC_4->SetStats(0);
    fHistTPC_5->SetStats(0);
    fHistTPC_6->SetStats(0);
    stackTPC1->Add(fHistTPC_1);
    stackTPC1->Add(fHistTPC_2);
    stackTPC1->Add(fHistTPC_3);
    stackTPC1->Add(fHistTPC_4);
    stackTPC1->Add(fHistTPC_5);
    stackTPC1->Add(fHistTPC_6);
    stackTPC1->Draw("nostackcol");
    stackTPC1->GetXaxis()->SetTitle("Pt");
    stackTPC1->GetYaxis()->SetTitle("nSigma");
    TLine *sigBot = new TLine(0, -2, 10, -2);
    TLine *sigTop = new TLine(0, 2, 10, 2);
    sigBot->SetLineColor(kRed);
    sigTop->SetLineColor(kRed);
    sigBot->SetLineWidth(2);
    sigTop->SetLineWidth(2);
    sigBot->Draw();
    sigTop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCFull_EMC7.png"));

    c1->Clear();

    THStack* stackTRD1=new THStack("strd1", "TRD electron liklihood after TPC and EMC cuts");
    fHistTRD_1->SetStats(0);
    fHistTRD_2->SetStats(0);
    fHistTRD_3->SetStats(0);
    fHistTRD_4->SetStats(0);
    fHistTRD_5->SetStats(0);
    fHistTRD_6->SetStats(0);
    stackTRD1->Add(fHistTRD_1);
    stackTRD1->Add(fHistTRD_2);
    stackTRD1->Add(fHistTRD_3);
    stackTRD1->Add(fHistTRD_4);
    stackTRD1->Add(fHistTRD_5);
    stackTRD1->Add(fHistTRD_6);
    stackTRD1->Draw("nostackcol");
    stackTRD1->GetXaxis()->SetTitle("Pt");
    stackTRD1->GetYaxis()->SetTitle("Electron Liklihood");
    TLine *sigTRD = new TLine(0, .8, 10, .8);
    sigTRD->SetLineColor(kRed);
    sigTRD->SetLineWidth(2);
    sigTRD->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TRDFull_EMC7.png"));

    c1->Clear();

    c1->Divide(3,2);
    c1->cd(1);
    fHistEMC_1->SetTitle(";E/p[c^2];Cts");
    fHistEMC_1->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_1->GetMaximum()*1.1, "1-2Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_1->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_1->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(2);
    fHistEMC_2->SetTitle(";E/p[c^2];Cts");
    fHistEMC_2->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_2->GetMaximum()*1.1, "2-3Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_2->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_2->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(3);
    fHistEMC_3->SetTitle(";E/p[c^2];Cts");
    fHistEMC_3->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_3->GetMaximum()*1.1, "3-4Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_3->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_3->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(4);
    fHistEMC_4->SetTitle(";E/p[c^2];Cts");
    fHistEMC_4->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_4->GetMaximum()*1.1, "4-5Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_4->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_4->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(5);
    fHistEMC_5->SetTitle(";E/p[c^2];Cts");
    fHistEMC_5->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_5->GetMaximum()*1.1, "5-6Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_5->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_5->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(6);
    fHistEMC_6->SetTitle(";E/p[c^2];Cts");
    fHistEMC_6->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_6->GetMaximum()*1.1, ">6Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.95, 0, .95, fHistEMC_6->GetMaximum());
    TLine *sigETop = new TLine(1.25, 0, 1.25, fHistEMC_6->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EMCFull_EMC7.png"));

    c1=new TCanvas();


    fHistEne->SetStats(0);
    fHistEneTag->SetStats(0);
    fHistInvMassLike->SetStats(0);
    fHistInvMassUnlike->SetStats(0);
    fHistOpAngLike->SetStats(0);
    fHistOpAngUnlike->SetStats(0);
    fHistTPCSig->SetStats(0);
    fHistTPCSigCut->SetStats(0);
    fHistInvMassLike->SetTitle(";Invariant Mass[Gev/c];Cts");
    fHistInvMassUnlike->SetTitle(";Invariant Mass[Gev/c];Cts");
    fHistOpAngLike->SetTitle(";Opening Angle[rad];Cts");
    fHistOpAngUnlike->SetTitle(";Opening Angle[rad];Cts");
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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EnergyOverlay_EMC7.png"));

    fHistInvMassUnlike->SetFillStyle(3004);
    fHistInvMassUnlike->SetFillColor(kBlack);
    fHistInvMassUnlike->Draw();
    fHistInvMassLike->SetFillStyle(3005);
    fHistInvMassLike->SetFillColor(kBlack);
    fHistInvMassLike->SetLineColor(kRed);
    fHistInvMassLike->Draw("same");
    TLine* InvCut = new TLine(.1, 0, .1, fHistInvMassUnlike->GetMaximum());
    InvCut->SetLineColor(kBlack);
    InvCut->SetLineWidth(2);
    InvCut->Draw();
    TLatex* titl = new TLatex(0.1, fHistInvMassUnlike->GetMaximum()*2.5, "Invariant Mass for electron pairs");
    titl->SetTextSize(0.05);
    titl->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/InvMassOverlay_EMC7.png"));

    fHistOpAngUnlike->SetFillStyle(3004);
    fHistOpAngUnlike->SetFillColor(kBlack);
    fHistOpAngUnlike->Draw();
    fHistOpAngLike->SetFillStyle(3005);
    fHistOpAngLike->SetFillColor(kBlack);
    fHistOpAngLike->SetLineColor(kRed);
    fHistOpAngLike->Draw("same");
    TLine* OpCut = new TLine(.1, 0, .1, fHistOpAngUnlike->GetMaximum());
    OpCut->SetLineColor(kBlack);
    OpCut->SetLineWidth(2);
    OpCut->Draw();
    TLatex* titl = new TLatex(.75, fHistOpAngUnlike->GetMaximum()*2.5, "Opening angle for electron pairs");
    titl->SetTextSize(0.05);
    titl->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/OpAngOverlay_EMC7.png"));

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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCSigOverlay_EMC7.png"));
    
    gStyle->SetOptStat(1);               

    for(Int_t i=0; i<=EMCEGA->LastIndex();i++){
        TH1 *hist = (TH1*)EMCEGA->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistPhotoMismatch_EMCEGA")==0){
            EMCEGA_mis = hist->GetEntries();
        }
        if(strcmp(hist->GetName(),"fHistImpPar_EMCEGA")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistImpParTag_EMCEGA")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistPtSum_EMCEGA")==0){
            fHistEne = hist;
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistPtSumTag_EMCEGA")==0){
            fHistEneTag = hist;
            hist->Scale(1/hist->GetEntries());
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecLike_EMCEGA")==0){
            fHistInvMassLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistInvMassElecUnLike_EMCEGA")==0){
            fHistInvMassUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecLike_EMCEGA")==0){
            fHistOpAngLike = hist;
        }
        if(strcmp(hist->GetName(),"fHistOpAngElecUnLike_EMCEGA")==0){
            fHistOpAngUnlike = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSig_EMCEGA")==0){
            fHistTPCSig = hist;
        }
        if(strcmp(hist->GetName(),"fHistTPCSigCut_EMCEGA")==0){
            fHistTPCSigCut = hist;
        }
        if(strcmp(hist->GetName(),"fHistITSNClus_EMCEGA")==0){
            gPad->SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistDPhiDEta28_EMCEGA")==0){
            gPad-> SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistEtaPhiTag_EMCEGA")==0){
            gPad->SetLogz();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultAway_EMCEGA")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMin_EMCEGA")==0){
            gPad-> SetLogy();
        }
        if(strcmp(hist->GetName(),"fHistTrkMultTransMax_EMCEGA")==0){
            gPad-> SetLogy();
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='C'&&hist->GetName()[8]=='_'){
            switch(hist->GetName()[23]){
                case '1':
                fHistTPC_1=hist;
                break;
                case '2':
                fHistTPC_2=hist;
                break;
                case '3':
                fHistTPC_3=hist;
                break;
                case '4':
                fHistTPC_4=hist;
                break;
                case '5':
                fHistTPC_5=hist;
                break;
                case '>':
                fHistTPC_6=hist;
                break;
            }
            TLine *sigBot = new TLine(0, -2, 10, -2);
            TLine *sigTop = new TLine(0, 2, 10, 2);
            sigBot->SetLineColor(kRed);
            sigTop->SetLineColor(kRed);
            sigBot->SetLineWidth(2);
            sigTop->SetLineWidth(2);
            sigBot->Draw();
            sigTop->Draw();
            TH2F* hist2d = (TH2F*)EMCEGA->At(i);
            TH1D *histProj = hist2d->ProjectionY(Form("%s_py", hist->GetName()));
        }
        if(hist->GetName()[5]=='T'&&hist->GetName()[6]=='R'&&hist->GetName()[7]=='D'){
            switch(hist->GetName()[23]){
                case '1':
                fHistTRD_1=hist;
                break;
                case '2':
                fHistTRD_2=hist;
                break;
                case '3':
                fHistTRD_3=hist;
                break;
                case '4':
                fHistTRD_4=hist;
                break;
                case '5':
                fHistTRD_5=hist;
                break;
                case '>':
                fHistTRD_6=hist;
                break;
            }
            TLine *sigTRD = new TLine(0, .8, 10, .8);
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
            switch(hist->GetName()[23]){
                case '1':
                fHistEMC_1=(TH1*)hist->Clone();
                break;
                case '2':
                fHistEMC_2=(TH1*)hist->Clone();
                break;
                case '3':
                fHistEMC_3=(TH1*)hist->Clone();
                break;
                case '4':
                fHistEMC_4=(TH1*)hist->Clone();
                break;
                case '5':
                fHistEMC_5=(TH1*)hist->Clone();
                break;
                case '>':
                fHistEMC_6=(TH1*)hist->Clone();
                break;
            }
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
                TF1* elecFit = new TF1("elecFit", "gaus", 0.2, 1.2);
                TF1* totalFit = new TF1("totalFit", "gaus(0)+pol0(3)", 0.8, 1.2);

                if(hist->GetName()[23]=='1'){
                    TF1* hadFit = new TF1("hadFit", "gaus", 0.2, 1.2);
                    TF1* totalFit = new TF1("totalFit", "gaus(0)+gaus(3)+pol0(6)", 0.2, 1.2);
                }

                totalFit->SetParName(0,"Scale_elecFit");
                totalFit->SetParName(1,"Mean_elecFit");
                totalFit->SetParName(2,"Sigma_elecFit");
                totalFit->SetParName(3,"Pedestal_hadCont");

                if(hist->GetName()[23]=='1'){
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

                if(hist->GetName()[23]=='1'){
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
                if(hist->GetName()[23]=='1'){
                    Double_t* par= new Double_t[];
                    par=totalFit->GetParameters();
                    hadFit->SetParameters(&par[3]);
                }
                Double_t purity = elecFit->Integral(0.8, 1.2)/totalFit->Integral(0.8, 1.2);
                cout<<purity<<"\n";
                elecFit->Draw("same");
                switch(hist->GetName()[23]){
                    case '1':
                    //Fill 1.5 Gev point in TGraph
                    purity_EMCEGA[0]=purity;
                    NElec_EMCEGA[0]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMCEGA[0]=totalFit->Integral(0.8, 1.2);
                    NSig_EMCEGA[0]=elecFit->Integral(0.8, 1.2);
                    hadFit->Draw("same");
                    break;
                    case '2':
                    //Fill 2.5 Gev point in TGraph
                    purity_EMCEGA[1]=purity;
                    NElec_EMCEGA[1]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMCEGA[1]=totalFit->Integral(0.8, 1.2);
                    NSig_EMCEGA[1]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '3':
                    //Fill 3.5 Gev point in TGraph
                    purity_EMCEGA[2]=purity;
                    NElec_EMCEGA[1]=NElec_EMCEGA[1]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMCEGA[2]=totalFit->Integral(0.8, 1.2);
                    NSig_EMCEGA[2]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '4':
                    //Fill 4.5 Gev point in TGraph
                    purity_EMCEGA[3]=purity;
                    NElec_EMCEGA[2]=hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMCEGA[3]=totalFit->Integral(0.8, 1.2);
                    NSig_EMCEGA[3]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '5':
                    //Fill 5.5 Gev point in TGraph
                    purity_EMCEGA[4]=purity;
                    NElec_EMCEGA[2]=NElec_EMCEGA[2]+hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    NTot_EMCEGA[4]=totalFit->Integral(0.8, 1.2);
                    NSig_EMCEGA[4]=elecFit->Integral(0.8, 1.2);
                    break;
                    case '>':
                    NElec6_EMCEGA = hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
                    break;
                }
            }
        }
        if(hist->GetName()[5]=='D'&&hist->GetName()[6]=='P'&&hist->GetName()[7]=='h'){
            if(hist->GetName()[9]=='_'){
                fHistDPhi[ind]=hist;
                ind++;
            }
            if(hist->GetName()[12]=='_'){
                cout<<"filling mixer"<<'\n';
                fHistDPhiMix[indMix]=hist;
                indMix++;
            }
            switch(hist->GetName()[15]){
                case '1':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_EMCEGA[0]));
                pt->Draw();
                hist->Scale(1/NElec_EMCEGA[0]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
                break;
                case '2':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_EMCEGA[1]));
                pt->Draw();
                hist->Scale(1/NElec_EMCEGA[1]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
                break;
                case '4':
                TPaveText *pt = new TPaveText(.4,.6,.6,.8, "NDC");
                pt->AddText(Form("%.1f trigger electrons",NElec_EMCEGA[2]));
                pt->Draw();
                hist->Scale(1/NElec_EMCEGA[2]);
                hist->GetYaxis()->SetTitle("\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
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
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", hist->GetName()));

        if(!histProj){continue;}
        histProj->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", histProj->GetName()));
    }

    c1=new TCanvas();

    gStyle->SetOptStat(0);


    THStack* stackTPC1=new THStack("st1", "TPC electron nSigma after TRD and EMC PID cuts");
    fHistTPC_1->SetStats(0);
    fHistTPC_2->SetStats(0);
    fHistTPC_3->SetStats(0);
    fHistTPC_4->SetStats(0);
    fHistTPC_5->SetStats(0);
    fHistTPC_6->SetStats(0);
    stackTPC1->Add(fHistTPC_1);
    stackTPC1->Add(fHistTPC_2);
    stackTPC1->Add(fHistTPC_3);
    stackTPC1->Add(fHistTPC_4);
    stackTPC1->Add(fHistTPC_5);
    stackTPC1->Add(fHistTPC_6);
    stackTPC1->Draw("nostackcol");
    stackTPC1->GetXaxis()->SetTitle("Pt");
    stackTPC1->GetYaxis()->SetTitle("nSigma");
    TLine *sigBot = new TLine(0, -2, 10, -2);
    TLine *sigTop = new TLine(0, 2, 10, 2);
    sigBot->SetLineColor(kRed);
    sigTop->SetLineColor(kRed);
    sigBot->SetLineWidth(2);
    sigTop->SetLineWidth(2);
    sigBot->Draw();
    sigTop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCFull_EMCEGA.png"));

    c1->Clear();

    THStack* stackTRD1=new THStack("strd1", "TRD electron liklihood after TPC and EMC cuts");
    fHistTRD_1->SetStats(0);
    fHistTRD_2->SetStats(0);
    fHistTRD_3->SetStats(0);
    fHistTRD_4->SetStats(0);
    fHistTRD_5->SetStats(0);
    fHistTRD_6->SetStats(0);
    stackTRD1->Add(fHistTRD_1);
    stackTRD1->Add(fHistTRD_2);
    stackTRD1->Add(fHistTRD_3);
    stackTRD1->Add(fHistTRD_4);
    stackTRD1->Add(fHistTRD_5);
    stackTRD1->Add(fHistTRD_6);
    stackTRD1->Draw("nostackcol");
    stackTRD1->GetXaxis()->SetTitle("Pt");
    stackTRD1->GetYaxis()->SetTitle("Electron Liklihood");
    TLine *sigTRD = new TLine(0, .8, 10, .8);
    sigTRD->SetLineColor(kRed);
    sigTRD->SetLineWidth(2);
    sigTRD->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TRDFull_EMCEGA.png"));

    c1->Clear();

    c1->Divide(3,2);
    c1->cd(1);
    fHistEMC_1->SetTitle(";E/p[c^2];Cts");
    fHistEMC_1->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_1->GetMaximum()*1.1, "1-2Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_1->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_1->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(2);
    fHistEMC_2->SetTitle(";E/p[c^2];Cts");
    fHistEMC_2->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_2->GetMaximum()*1.1, "2-3Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_2->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_2->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(3);
    fHistEMC_3->SetTitle(";E/p[c^2];Cts");
    fHistEMC_3->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_3->GetMaximum()*1.1, "3-4Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_3->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_3->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(4);
    fHistEMC_4->SetTitle(";E/p[c^2];Cts");
    fHistEMC_4->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_4->GetMaximum()*1.1, "4-5Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_4->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_4->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(5);
    fHistEMC_5->SetTitle(";E/p[c^2];Cts");
    fHistEMC_5->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_5->GetMaximum()*1.1, "5-6Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, fHistEMC_5->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, fHistEMC_5->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(6);
    fHistEMC_6->SetTitle(";E/p[c^2];Cts");
    fHistEMC_6->Draw();
    TLatex* text = new TLatex(.5, fHistEMC_6->GetMaximum()*1.1, ">6Gev Pt");
    text->SetTextSize(.08);
    text->Draw();
    TLine *sigEBot = new TLine(.95, 0, .95, fHistEMC_6->GetMaximum());
    TLine *sigETop = new TLine(1.25, 0, 1.25, fHistEMC_6->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EMCFull_EMCEGA.png"));

    c1=new TCanvas();


    fHistEne->SetStats(0);
    fHistEneTag->SetStats(0);
    fHistInvMassLike->SetStats(0);
    fHistInvMassUnlike->SetStats(0);
    fHistOpAngLike->SetStats(0);
    fHistOpAngUnlike->SetStats(0);
    fHistTPCSig->SetStats(0);
    fHistTPCSigCut->SetStats(0);
    fHistInvMassLike->SetTitle(";Invariant Mass[Gev/c];Cts");
    fHistInvMassUnlike->SetTitle(";Invariant Mass[Gev/c];Cts");
    fHistOpAngLike->SetTitle(";Opening Angle[rad];Cts");
    fHistOpAngUnlike->SetTitle(";Opening Angle[rad];Cts");
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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EnergyOverlay_EMCEGA.png"));

    fHistInvMassUnlike->SetFillStyle(3004);
    fHistInvMassUnlike->SetFillColor(kBlack);
    fHistInvMassUnlike->Draw();
    fHistInvMassLike->SetFillStyle(3005);
    fHistInvMassLike->SetFillColor(kBlack);
    fHistInvMassLike->SetLineColor(kRed);
    fHistInvMassLike->Draw("same");
    TLine* InvCut = new TLine(.1, 0, .1, fHistInvMassUnlike->GetMaximum());
    InvCut->SetLineColor(kBlack);
    InvCut->SetLineWidth(2);
    InvCut->Draw();
    TLatex* titl = new TLatex(0.1, fHistInvMassUnlike->GetMaximum()*2.5, "Invariant Mass for electron pairs");
    titl->SetTextSize(0.05);
    titl->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/InvMassOverlay_EMCEGA.png"));

    fHistOpAngUnlike->SetFillStyle(3004);
    fHistOpAngUnlike->SetFillColor(kBlack);
    fHistOpAngUnlike->Draw();
    fHistOpAngLike->SetFillStyle(3005);
    fHistOpAngLike->SetFillColor(kBlack);
    fHistOpAngLike->SetLineColor(kRed);
    fHistOpAngLike->Draw("same");
    TLine* OpCut = new TLine(.1, 0, .1, fHistOpAngUnlike->GetMaximum());
    OpCut->SetLineColor(kBlack);
    OpCut->SetLineWidth(2);
    OpCut->Draw();
    TLatex* titl = new TLatex(.75, fHistOpAngUnlike->GetMaximum()*2.5, "Opening angle for electron pairs");
    titl->SetTextSize(0.05);
    titl->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/OpAngOverlay_EMCEGA.png"));

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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCSigOverlay_EMCEGA.png"));

    gStyle->SetOptStat(1);  

    for(Int_t i=0; i<=EMCJet->LastIndex();i++){
        TH1 *hist = (TH1*)EMCJet->At(i);
        gPad->SetLogy(0);
        gPad->SetLogz(0);
        hist->Draw("colz");
        if(strcmp(hist->GetName(),"fHistPhotoMismatch_EMCJet")==0){
            EMCJet_mis = hist->GetEntries();
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
            switch(hist->GetName()[23]){
                case '1':
                fHistTPC_1=hist;
                break;
                case '2':
                fHistTPC_2=hist;
                break;
                case '3':
                fHistTPC_3=hist;
                break;
                case '4':
                fHistTPC_4=hist;
                break;
                case '5':
                fHistTPC_5=hist;
                break;
                case '>':
                fHistTPC_6=hist;
                break;
            }
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
            switch(hist->GetName()[23]){
                case '1':
                fHistTRD_1=hist;
                break;
                case '2':
                fHistTRD_2=hist;
                break;
                case '3':
                fHistTRD_3=hist;
                break;
                case '4':
                fHistTRD_4=hist;
                break;
                case '5':
                fHistTRD_5=hist;
                break;
                case '>':
                fHistTRD_6=hist;
                break;
            }
            TLine *sigTRD = new TLine(0, .8, 10, .8);
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
            switch(hist->GetName()[23]){
                case '1':
                fHistEMC_1=hist;
                break;
                case '2':
                fHistEMC_2=hist;
                break;
                case '3':
                fHistEMC_3=hist;
                break;
                case '4':
                fHistEMC_4=hist;
                break;
                case '5':
                fHistEMC_5=hist;
                break;
                case '>':
                fHistEMC_6=hist;
                break;
            }
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
                    case '>':
                    NElec6_EMCJet = hist->Integral(hist->GetXaxis()->FindBin(0.8),hist->GetXaxis()->FindBin(1.2));
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
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", hist->GetName()));

        if(!histProj){continue;}        
        histProj->Draw();
        c1->Update();
        c1->SaveAs(Form("./plotsKlayWeakNoSSSig/%s.png", histProj->GetName()));
    }


    THStack* stackTPC2=new THStack("st2", "TPC nSigma after TRD and EMC cuts");
    stackTPC2->Add(fHistTPC_1);
    stackTPC2->Add(fHistTPC_2);
    stackTPC2->Add(fHistTPC_3);
    stackTPC2->Add(fHistTPC_4);
    stackTPC2->Add(fHistTPC_5);
    stackTPC2->Add(fHistTPC_6);
    stackTPC2->Draw("nostackcol");
    stackTPC2->GetXaxis()->SetTitle("Pt");
    stackTPC2->GetYaxis()->SetTitle("nSigma");
    TLine *sigBot = new TLine(0, -2, 10, -2);
    TLine *sigTop = new TLine(0, 2, 10, 2);
    sigBot->SetLineColor(kRed);
    sigTop->SetLineColor(kRed);
    sigBot->SetLineWidth(2);
    sigTop->SetLineWidth(2);
    sigBot->Draw();
    sigTop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCFull_EMCJet.png"));

    c1->Clear();

    THStack* stackTRD2=new THStack("strd2", "TRD electron liklihood after TPC and EMC cuts");
    stackTRD2->Add(fHistTRD_1);
    stackTRD2->Add(fHistTRD_2);
    stackTRD2->Add(fHistTRD_3);
    stackTRD2->Add(fHistTRD_4);
    stackTRD2->Add(fHistTRD_5);
    stackTRD2->Add(fHistTRD_6);
    stackTRD2->Draw("nostackcol");
    stackTRD2->GetXaxis()->SetTitle("Pt");
    stackTRD2->GetYaxis()->SetTitle("Electron Liklihood");
    TLine *sigTRD = new TLine(0, .9, 10, .9);
    sigTRD->SetLineColor(kRed);
    sigTRD->SetLineWidth(2);
    sigTRD->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TRDFull_EMCJet.png"));

    c1->Clear();

    c1->Divide(3,2);
    c1->cd(1);
    fHistEMC_1->SetTitle(";E/p[c^2];Cts");
    fHistEMC_1->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(2);
    fHistEMC_2->SetTitle(";E/p[c^2];Cts");
    fHistEMC_2->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(3);
    fHistEMC_3->SetTitle(";E/p[c^2];Cts");
    fHistEMC_3->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(4);
    fHistEMC_4->SetTitle(";E/p[c^2];Cts");
    fHistEMC_4->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(5);
    fHistEMC_5->SetTitle(";E/p[c^2];Cts");
    fHistEMC_5->Draw();
    TLine *sigEBot = new TLine(.85, 0, .85, hist->GetMaximum());
    TLine *sigETop = new TLine(1.15, 0, 1.15, hist->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->cd(6);
    fHistEMC_6->SetTitle(";E/p[c^2];Cts");
    fHistEMC_6->Draw();
    TLine *sigEBot = new TLine(.95, 0, .95, hist->GetMaximum());
    TLine *sigETop = new TLine(1.25, 0, 1.25, hist->GetMaximum());
    sigEBot->SetLineColor(kRed);
    sigETop->SetLineColor(kRed);
    sigEBot->SetLineWidth(2);
    sigETop->SetLineWidth(2);
    sigEBot->Draw();
    sigETop->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EMCFull_EMCJet.png"));

    c1=new TCanvas();
    TH1F* Cor;
    TH1F* Dp;
    TH1F* DpM;
    Double_t assopt[7]={.3, .5, .8, 1, 2, 4, 999};
    TString trgName[3]={"MB", "EMC7", "EMCEGA"};
    for(Int_t i=0;i<indMix;i++){
        cout<<i<<'\n';
        if(!fHistDPhiMix[i]){cout<<"no Mix"<<'\n'; continue;}
        DpM=(TH1F*)fHistDPhiMix[i];
        DpM->Scale(1/DpM->GetBinContent(DpM->FindBin(0))); 
        Dp=(TH1F*)fHistDPhi[i];
        if(Dp->Divide(DpM)){
            Cor=Dp;
            Cor->Draw();
            Cor->SetTitle(Form("Correlation Function for %s%d%s%d%s%.1f%s%.1f%s%s;\\Delta\\phi;\\frac{N_{same}}{N_{mix}}","trig pt: ",i<6?1:i<12?2:i<18?4:i<24?1:i<30?2:i<36?4:i<42?1:i<48?2:i<54?4:-1,"-",i<6?2:i<12?4:i<18?8:i<24?2:i<30?4:i<36?8:i<42?2:i<48?4:i<54?8:-1, ", assoc pt: ", assopt[i%6], "-", assopt[i%6+1], " for ", trgName[i/18].Data()));
            c1->SaveAs(Form("./plotsKlayWeakNoSSSig/Correlation_%d%s%d%s%d%s%.1f%s%.1f.png",i,"trig_pt",i<6?1:i<12?2:i<18?4:i<24?1:i<30?2:i<36?4:i<42?1:i<48?2:i<54?4:-1,"",i<6?2:i<12?4:i<18?8:i<24?2:i<30?4:i<36?8:i<42?2:i<48?4:i<54?8:-1, "assoc_pt", assopt[i%6], "", assopt[i%6+1]));
        }
    }
    
    
    c1->Clear();
    c1=new TCanvas("c1", "DPhi",1000, 500);

    TString ptRange[7]={".3-.5Gev", ".5-.8Gev", ".8-1Gev", "1-2Gev", "2-3Gev", "3-4Gev", ">4Gev"};
    c1->Divide(4,2);
    Int_t Offset=0;
    cout<<ind;
    for(Int_t i=0;i<=(ind+Offset+1);i++){
        Int_t padnum=i%8+1;
        c1->cd(padnum);
        if(fHistDPhi[i-Offset]){
            fHistDPhi[i-Offset]->Rebin(5);
            fHistDPhi[i-Offset]->SetStats(0);
            fHistDPhi[i-Offset]->SetTitle(";\\Delta\\phi[rad];\\frac{1}{N_{trg}}\\frac{dN}{d\\phi}");
            fHistDPhi[i-Offset]->GetXaxis()->SetTitleSize(0.06);
            fHistDPhi[i-Offset]->GetYaxis()->SetTitleSize(0.06);
            fHistDPhi[i-Offset]->SetMarkerStyle(20);
            fHistDPhi[i-Offset]->SetMarkerSize(.5);
            /* TLatex* tite = new TLatex(-1.2, fHistDPhi[i-Offset]->GetMaximum()*1.1, Form("#Delta#phi for particles w/pt %s",ptRange[padnum-1].Data()));
            tite->SetTextSize(0.07);*/
            cout<<fHistDPhi[i-Offset]->GetName()<<'\n';
            if(i%8+1!=8){
                fHistDPhi[i-Offset]->Draw("p");
                /*tite->Draw();*/
            }
            c1->Update();   
        }
        cout<<i%8+1<<'\n';
        if(i%8+1==8){
            /*TText *title = new TText(.01,.5,Form("Trigger electrons with %d>pt>%dGev", i<8?1:(i<16?2:(i<24?4:(i<32?1:(i<40?2:(i<48?4:0))))),i<8?2:(i<16?4:(i<24?8:(i<32?2:(i<40?4:(i<48?8:0)))))));
            title->SetTextSize(.07);
            title->AppendPad();*/
            Offset++;
            c1->SaveAs(Form("./plotsKlayWeakNoSSSig/DPhi6_%d.png",i));
            /*title->Delete();*/
        }
    }

    c1=new TCanvas();


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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/EnergyOverlay_EMCJet.png"));

    fHistInvMassUnlike->SetFillStyle(3004);
    fHistInvMassUnlike->SetFillColor(kBlack);
    fHistInvMassUnlike->Draw();
    fHistInvMassLike->SetFillStyle(3005);
    fHistInvMassLike->SetFillColor(kBlack);
    fHistInvMassLike->SetLineColor(kRed);
    fHistInvMassLike->Draw("same");
    TLine* InvCut = new TLine(.1, 0, .1, fHistInvMassUnlike->GetMaximum());
    InvCut->SetLineColor(kBlack);
    InvCut->SetLineWidth(2);
    InvCut->Draw();
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistInvMassLike,"Invariant mass for like-signed electron pairs","f");
    leg->AddEntry(fHistInvMassUnlike,"Invariant mass for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/InvMassOverlay_EMCJet.png"));

    fHistOpAngUnlike->SetFillStyle(3004);
    fHistOpAngUnlike->SetFillColor(kBlack);
    fHistOpAngUnlike->Draw();
    fHistOpAngLike->SetFillStyle(3005);
    fHistOpAngLike->SetFillColor(kBlack);
    fHistOpAngLike->SetLineColor(kRed);
    fHistOpAngLike->Draw("same");
    TLine* OpCut = new TLine(.1, 0, .1, fHistOpAngUnlike->GetMaximum());
    OpCut->SetLineColor(kBlack);
    OpCut->SetLineWidth(2);
    OpCut->Draw();
    leg = new TLegend(0.3,0.7,0.6,0.9);
    leg->AddEntry(fHistOpAngLike,"Opening angle for like-signed electron pairs","f");
    leg->AddEntry(fHistOpAngUnlike,"Opening angle for unlike-signed electron pairs","f");
    leg->Draw();
    c1->Update();
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/OpAngOverlay_EMCJet.png"));

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
    c1->SaveAs(Form("./plotsKlayWeakNoSSSig/TPCSigOverlay_EMCJet.png"));

    gStyle->SetOptStat(1);

    Double_t x[5]={1.5, 2.5, 3.5, 4.5, 5.5};

    Double_t y[3]={1.5, 2.5, 3.5};
    Double_t NElecSum_MB = NElec_MB[0]+NElec_MB[1]+NElec_MB[2]+NElec6_MB;
    Double_t NElecSum_EMC7 = NElec_EMC7[0]+NElec_EMC7[1]+NElec_EMC7[2]+NElec6_EMC7;
    Double_t NElecSum_EMCEGA = NElec_EMCEGA[0]+NElec_EMCEGA[1]+NElec_EMCEGA[2]+NElec6_EMCEGA;
    Double_t NElecSum_EMCJet = NElec_EMCJet[0]+NElec_EMCJet[1]+NElec_EMCJet[2]+NElec6_EMCJet;
    cout<<NElecSum_MB<<":"<<MB_mis<<'\n';

    //calcs for error on purity
    Double_t sigAv_MB = (NSig_MB[0]+NSig_MB[1]+NSig_MB[2]+NSig_MB[3]+NSig_MB[4])/5;
    Double_t sigAv_EMC7 = (NSig_EMC7[0]+NSig_EMC7[1]+NSig_EMC7[2]+NSig_EMC7[3]+NSig_EMC7[4])/5;
    Double_t sigAv_EMCEGA = (NSig_EMCEGA[0]+NSig_EMCEGA[1]+NSig_EMCEGA[2]+NSig_EMCEGA[3]+NSig_EMCEGA[4])/5;
    Double_t totAv_MB = (NTot_MB[0]+NTot_MB[1]+NTot_MB[2]+NTot_MB[3]+NTot_MB[4])/5;
    Double_t totAv_EMC7 = (NTot_EMC7[0]+NTot_EMC7[1]+NTot_EMC7[2]+NTot_EMC7[3]+NTot_EMC7[4])/5;
    Double_t totAv_EMCEGA = (NTot_EMCEGA[0]+NTot_EMCEGA[1]+NTot_EMCEGA[2]+NTot_EMCEGA[3]+NTot_EMCEGA[4])/5;
    Double_t cov_MB = 0;
    Double_t cov_EMC7 = 0;
    Double_t cov_EMCEGA = 0;
    for(Int_t i=0;i<5;i++){
        cov_MB+=(NSig_MB[i]-sigAv_MB)*(NTot_MB[i]-totAv_MB);
        cov_EMC7+=(NSig_EMC7[i]-sigAv_EMC7)*(NTot_EMC7[i]-totAv_EMC7);
        cov_EMCEGA+=(NSig_EMCEGA[i]-sigAv_EMCEGA)*(NTot_EMCEGA[i]-totAv_EMCEGA);
        cout<<"Sig:"<<NSig_EMC7[i]<<", Tot:"<<NTot_EMC7[i]<<'\n';
    }
    cov_MB=cov_MB/4;
    cov_EMC7=cov_EMC7/4;
    cov_EMCEGA=cov_EMCEGA/4;
    cout<<"cov:"<<cov_MB<<", "<<cov_EMC7<<'\n';
    Double_t purityErr_MB[5] = {(1/NTot_MB[0])*TMath::Sqrt(NSig_MB[0]*(1-NSig_MB[0]/NTot_MB[0])),
                                (1/NTot_MB[1])*TMath::Sqrt(NSig_MB[1]*(1-NSig_MB[1]/NTot_MB[1])), 
                                (1/NTot_MB[2])*TMath::Sqrt(NSig_MB[2]*(1-NSig_MB[2]/NTot_MB[2])),
                                (1/NTot_MB[3])*TMath::Sqrt(NSig_MB[3]*(1-NSig_MB[3]/NTot_MB[3])),
                                (1/NTot_MB[4])*TMath::Sqrt(NSig_MB[4]*(1-NSig_MB[4]/NTot_MB[4]))
                               };



    Double_t purityErr_EMC7[5] = {(1/NTot_EMC7[0])*TMath::Sqrt(NSig_EMC7[0]*(1-NSig_EMC7[0]/NTot_EMC7[0])),
                                  (1/NTot_EMC7[1])*TMath::Sqrt(NSig_EMC7[1]*(1-NSig_EMC7[1]/NTot_EMC7[1])), 
                                  (1/NTot_EMC7[2])*TMath::Sqrt(NSig_EMC7[2]*(1-NSig_EMC7[2]/NTot_EMC7[2])),
                                  (1/NTot_EMC7[3])*TMath::Sqrt(NSig_EMC7[3]*(1-NSig_EMC7[3]/NTot_EMC7[3])),
                                  (1/NTot_EMC7[4])*TMath::Sqrt(NSig_EMC7[4]*(1-NSig_EMC7[4]/NTot_EMC7[4]))
                                 };
    
    Double_t purityErr_EMCEGA[5] = {(1/NTot_EMCEGA[0])*TMath::Sqrt(NSig_EMCEGA[0]*(1-NSig_EMCEGA[0]/NTot_EMCEGA[0])),
                                  (1/NTot_EMCEGA[1])*TMath::Sqrt(NSig_EMCEGA[1]*(1-NSig_EMCEGA[1]/NTot_EMCEGA[1])), 
                                  (1/NTot_EMCEGA[2])*TMath::Sqrt(NSig_EMCEGA[2]*(1-NSig_EMCEGA[2]/NTot_EMCEGA[2])),
                                  (1/NTot_EMCEGA[3])*TMath::Sqrt(NSig_EMCEGA[3]*(1-NSig_EMCEGA[3]/NTot_EMCEGA[3])),
                                  (1/NTot_EMCEGA[4])*TMath::Sqrt(NSig_EMCEGA[4]*(1-NSig_EMCEGA[4]/NTot_EMCEGA[4]))
                                 };
    for(Int_t i=0;i<5;i++){
        if(purityErr_MB[i]<0.00000000000000001){purityErr_MB[i]=1;}
        if(purityErr_EMC7[i]<0.00000000000000001){purityErr_EMC7[i]=1;}
        if(purityErr_EMCEGA[i]<0.00000000000000001){purityErr_EMCEGA[i]=1;}
    }

    Double_t data[4]={MB_mis/NElecSum_MB, EMC7_mis/NElecSum_EMC7,EMCEGA_mis/NElecSum_EMCEGA, 0/*EMCJet_mis/NElecSum_EMCJet*/};
    Double_t daterr[4]={data[0]*TMath::Sqrt(1/MB_mis+1/NElecSum_MB),data[1]*TMath::Sqrt(1/EMC7_mis+1/NElecSum_EMC7),data[2]*TMath::Sqrt(1/EMCEGA_mis+1/NElecSum_EMCEGA), 1};

    for(Int_t i=0; i<5; i++){
        cout<<i<<","<<x[i]<<","<<purity_EMC7[i];
    }

    Double_t xpur[5]={0,0,0,0,0};

    TGraphErrors* purityGraph_MB = new TGraphErrors(5, x, purity_MB, xpur, purityErr_MB);
    TGraphErrors* purityGraph_EMC7 = new TGraphErrors(5, x, purity_EMC7, xpur, purityErr_EMC7);
    TGraphErrors* purityGraph_EMCEGA = new TGraphErrors(5, x, purity_EMCEGA, xpur, purityErr_EMCEGA);
    TGraphErrors* purityGraph_EMCJet = new TGraphErrors(5, x, purity_EMCJet);
    TGraphErrors* pMiss = new TGraphErrors(3, y , data, xpur, daterr);

    gPad->SetLogy(0);

    pMiss->GetXaxis()->SetTitle("Trigger");
    pMiss->GetYaxis()->SetTitle("# of mismatches/# of triggers");
    pMiss->SetTitle("Contamination from photonic electrons");
    pMiss->SetMinimum(0);
    pMiss->SetMaximum(.1);
    pMiss->SetMarkerStyle(20);
    pMiss->Draw("Ape");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakNoSSSig/PhotonicMissGraph.png");


    cout<<"is the issue here?";

    c1->SetGrid();
    purityGraph_MB->GetXaxis()->SetTitle("Pt");
    purityGraph_MB->GetYaxis()->SetTitle("Electron purity");
    purityGraph_MB->SetTitle("MB Electron Purity after TPC, TRD, EMC cuts");
    purityGraph_MB->SetMinimum(0);
    purityGraph_MB->SetMaximum(1);
    purityGraph_MB->SetMarkerStyle(20);
    purityGraph_MB->Draw("Ap");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakNoSSSig/ElecPurity_MB.png");

    c1->SetGrid();
    purityGraph_EMC7->GetXaxis()->SetTitle("Pt");
    purityGraph_EMC7->GetYaxis()->SetTitle("Electron purity");
    purityGraph_EMC7->SetTitle("EMC7 Electron Purity after TPC, TRD, EMC cuts");
    purityGraph_EMC7->SetMinimum(0);
    purityGraph_EMC7->SetMaximum(1);
    purityGraph_EMC7->SetMarkerStyle(20);
    purityGraph_EMC7->Draw("Ap");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakNoSSSig/ElecPurity_EMC7.png");
    
    c1->SetGrid();
    purityGraph_EMCEGA->GetXaxis()->SetTitle("Pt");
    purityGraph_EMCEGA->GetYaxis()->SetTitle("Electron purity");
    purityGraph_EMCEGA->SetTitle("EMCEGA Electron Purity after TPC, TRD, EMC cuts");
    purityGraph_EMCEGA->SetMinimum(0);
    purityGraph_EMCEGA->SetMaximum(1);
    purityGraph_EMCEGA->SetMarkerStyle(20);
    purityGraph_EMCEGA->Draw("Ap");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakNoSSSig/ElecPurity_EMCEGA.png");

    c1->SetGrid();
    purityGraph_EMCJet->Draw("A");
    c1->Update();
    c1->SaveAs("./plotsKlayWeakNoSSSig/ElecPurity_EMCJet.png");
    return;
}
