#include "stdlib.h"
    #include <vector>
    #include <iostream>
#include <fstream>

    void runQAana(){
    
    ofstream BadRunList;
    BadRunList.open ("./plots/BadRunsMB.txt");
    
    TString per[6] = {"c","d","e","f","g", "i"};
    for(Int_t period=0;period<6;period++){
        cout<<per[period]<<'\n';

        TFile *file = new TFile(Form("./data/LHC12%s_pass2_EMCALQA.root",per[period].Data()));
        TDirectoryFile *runData = (TDirectoryFile*)file->Get(Form("LHC12%s/pass2",per[period].Data()));
        TList *keys = (TList*) runData->GetListOfKeys();



        std::vector<Double_t> runNum;

        std::vector<Double_t> pioruns(keys->GetEntries());
        std::vector<Double_t> Emapruns;

        for(Int_t i=0;i<keys->GetEntries();i++){
            if(TString(keys->At(i)->GetName()).IsDigit()){
                runNum.push_back(TString(keys->At(i)->GetName()).Atoi());
            }
        }

        std::vector<Double_t> piomass(keys->GetEntries());
        Int_t pioind = 0;

        Int_t emapind = 0;
        TCanvas* can1 = new TCanvas("nycan", "Pi_0 mass by run number", 1920, 1024);
        can1->Draw();
        
        for(Int_t i=0;i<keys->GetEntries();i++){
            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"Pi0InvMass")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TH1* pihist = (TH1*)list->At(h);
                        if(pihist){
                            TList* funclist = (TList*)pihist->GetListOfFunctions();
                            TF1* pifit = (TF1*)funclist->At(0);

                            if(pifit){
                                piomass[pioind]=pifit->GetParameter(1); 
                                pioruns[i]=TString(keys->At(i)->GetName()).Atoi();
                                pioind++;

                            }

                        }
                    }
                }
                if(strcmp(can->GetName(),"TimeVsE")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        cout<<"TimeVsE, "<<i<<'\n';
                        TH2F* tvehist2 = ((TH2F*)list->At(h))->Clone();
                        tvehist2->Draw("colz");
                        can1->Modified();
                        can1->Update();
                        can1->SaveAs(Form("./plots/LHC12%s/TimeVsE%.0f.png",per[period].Data(), runNum[i]));
                    }
                }
            }
        }

        

        Double_t pioave = 0;
        for(Int_t i=0;i<pioind;i++){pioave+=piomass[i];}
        pioave=pioave/Double_t(pioind);

        Double_t piostd = 0;
        for(Int_t i=0;i<pioind;i++){piostd+=(piomass[i]-pioave)*(piomass[i]-pioave);}
        piostd=TMath::Sqrt((piostd/Double_t(pioind)));

        /*TH1F* label = new TH1F("a", "test", 96, runNum.front(), runNum.back());
    //label->FillN(97, runNum, piomass);


    label->SetMaximum(0.2);
    label->SetMinimum(0.1);
    label->Draw();*/

        Int_t BadRunsPi[500];
        Int_t brpInd = 0;
        
        
        TH1F* pi0mass = new TH1F("pi0mass", "Pi_0 mass by time", runNum.back()-runNum.front(), runNum.front(), runNum.back());
        pi0mass->SetStats(0);
        pi0mass->SetMarkerStyle(4);
        pi0mass->GetXaxis()->SetTitle("Time[Run #]");
        pi0mass->GetYaxis()->SetTitle("Pi_0 mass[GeV]");
        TLine* meanline = new TLine(runNum.front(), pioave, runNum.back(), pioave);
        TLine* stdlinep = new TLine(runNum.front(), pioave+piostd, runNum.back(), pioave+piostd);
        TLine* stdlinem = new TLine(runNum.front(), pioave-piostd, runNum.back(), pioave-piostd);
        stdlinep->SetLineWidth(4);
        stdlinem->SetLineWidth(4);
        stdlinep->SetLineColor(kRed);
        stdlinem->SetLineColor(kRed);
        TPaveText* pave = new TPaveText(.7, .8, .9, .7, "NDC");
        pave->AddText(Form("Mean Pi_0 Mass %.3f+/-%.3f", pioave, piostd));
        pi0mass->Draw("p");
        for(Int_t i=1;i<keys->GetEntries();i++){
            pi0mass->GetXaxis()->SetBinLabel(pi0mass->FindBin(runNum[i]), TString(Form("%.0f",runNum[i])));
            if(i<pioind){
                pi0mass->Fill(TString(Form("%.0f",pioruns[i])), piomass[i]);
                if(TMath::Abs(pioave-piomass[i])>piostd){
                    cout<<pioruns[i]<<'\n';
                    BadRunsPi[brpInd] = pioruns[i];
                    brpInd++;
                }
            }
        }
        pi0mass->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        pi0mass->Draw("p");
        meanline->Draw();
        stdlinep->Draw();
        stdlinem->Draw();
        pave->Draw();
        can1->SaveAs(Form("./plots/LHC12%s/Pi0MassTime.png",per[period].Data()));

        TH1F* pi0massrbr = new TH1F("pi0massrbr", "Pi_0 mass run by run", 96, runNum.front(), runNum.back());
        pi0massrbr->SetStats(0);
        pi0massrbr->SetMarkerStyle(4);
        pi0massrbr->GetXaxis()->SetTitle("Run Number");
        pi0massrbr->GetYaxis()->SetTitle("Pi_0 mass[GeV]");
        pi0massrbr->Draw("p");
        for(Int_t i=1;i<keys->GetEntries();i++){
            pi0massrbr->GetXaxis()->SetBinLabel(i, TString(Form("%.0f",runNum[i])));
            if(i<pioind){
                pi0massrbr->Fill(TString(Form("%.0f",pioruns[i])), piomass[i]);
            }
        }
        pi0massrbr->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        pi0massrbr->Draw("p");
        meanline->Draw();
        stdlinep->Draw();
        stdlinem->Draw();
        pave->Draw();
        can1->SaveAs(Form("./plots/LHC12%s/Pi0MassRunByRun.png",per[period].Data()));
        
        for(Int_t i=0; BadRunsPi[i]; i++){
               BadRunList<<"Pi: "<<BadRunsPi[i]<<'\n';
        }

        //Energy Map

        /*
            TH2* Emap;
            Bool_t front=kFALSE;
            Double_t norm=1;
            for(Int_t i=0;i<keys->GetEntries();i++){
                TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
                TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
                if(!findir){
                    continue;
                }

                for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                    TCanvas* can;
                    TList* plots = findir->GetListOfKeys();
                    findir->GetObject(plots->At(j)->GetName(), can);
                    TList* list=can->GetListOfPrimitives();
                    if(strcmp(can->GetName(),"Energymap")==0){
                        for(Int_t h=0;h<list->GetEntries();h++){
                            if(!front){Emap=(TH2*)(list->At(h))->Clone();front=kTRUE;}else{
                                Emap->Add((TH2*)list->At(h));
                                norm++;}
                        }
                    }
                }
            }
            cout<<"boiiiiii";

            Emap->Scale(1/norm);
            can1->Clear();
            can1->Draw();
            Emap->Draw("colz");
            can1->SaveAs(Form("./plots/LHC12%s/EMapAve.png",per[period].Data()));
            std:vector<Double_t> dev(keys->GetEntries());


            for(Int_t i=0;i<keys->GetEntries();i++){
                TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
                TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
                if(!findir){
                    continue;
                }

                for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                    TCanvas* can;
                    TList* plots = findir->GetListOfKeys();
                    findir->GetObject(plots->At(j)->GetName(), can);
                    TList* list=can->GetListOfPrimitives();
                    cout<<"b4 EMap"<<'\n';
                    if(strcmp(can->GetName(),"Energymap")==0){
                        for(Int_t h=0;h<list->GetEntries();h++){
                            if(list->At(h)){
                                TH2* temp = (TH2*)(list->At(h))->Clone();
                                if(temp){
                                    temp->Add(Emap, -1);
                                    dev[emapind]=temp->Integral();
                                    cout<<"In temp"<<'\n';
                                    Emapruns.push_back(runNum[i]);
                                    emapind++;
                                    cout<<dev[emapind]<<'\n';
                                }
                            }
                        }
                    }
                }
            }

            Double_t devmean = 0;
            for(Int_t i=0;i<emapind;i++){devmean+=dev[i];}
            devmean=devmean/Double_t(emapind);

            Double_t devstd = 0;
            for(Int_t i=0;i<emapind;i++){devstd+=(dev[i]-devmean)*(dev[i]-devmean);}
            devstd = TMath::Sqrt(devstd/Double_t(emapind));

            can1->cd();
            TH1F* energymap = new TH1F("emaprbr", "This is a plot ", 96, runNum.front(), runNum.back());
            energymap->SetStats(0);
            energymap->SetMarkerStyle(4);
            energymap->SetTitle("Sum Deviation from Average Energy Map by Run Number");
            energymap->GetXaxis()->SetTitle("Run Number");
            energymap->GetYaxis()->SetTitle("Sum Deviation from Average Energy Map");
            TLine* emapmean = new TLine(runNum.front(), devmean, runNum.back(), devmean);
            TLine* emapstdp = new TLine(runNum.front(), devmean+devstd, runNum.back(), devmean+devstd);
            TLine* emapstdm = new TLine(runNum.front(), devmean-devstd, runNum.back(), devmean-devstd);
            emapstdp->SetLineWidth(4);
            emapstdm->SetLineWidth(4);
            emapstdp->SetLineColor(kRed);
            emapstdm->SetLineColor(kRed);
            TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
            meantxt->AddText(Form("Mean Deviation from Average Energy Map %.3f+/-%.3f",devmean, devstd));
            energymap->Draw("P1");
            for(Int_t i=1;i<96;i++){
                energymap->GetXaxis()->SetBinLabel(i, TString(Form("%.0f",runNum[i])));
            }

            for(Int_t i=0;i<emapind;i++){
                cout<<"Filling bin#:"<<TString(Form("%.0f",Emapruns.at(i)))<<" With value:"<<dev[i]<<'\n';
                energymap->Fill(TString(Form("%.0f",Emapruns.at(i))), dev[i]);
            }
            energymap->GetXaxis()->SetLabelSize(0.02);
            gPad->SetGrid(1,1);
            energymap->Draw("P1");
            energymap->Print();
            emapmean->Draw();
            emapstdp->Draw();
            emapstdm->Draw();
            meantxt->Draw();
            can1->Modified();
            can1->Update();
            can1->SaveAs(Form("./plots/LHC12%s/EnergyMapRunByRun.png",per[period].Data()));

            TH1F* energymaptime = new TH1F("emaptime", "This is a plot ", runNum.back()-runNum.front(), runNum.front(), runNum.back());
            energymaptime->SetStats(0);
            energymaptime->SetMarkerStyle(4);
            energymaptime->SetTitle("Sum Deviation from Energy Map by Time");
            energymaptime->GetXaxis()->SetTitle("Time[Run #]");
            energymaptime->GetYaxis()->SetTitle("Sum Deviation from Average Energy Map");
            TLine* emapmean = new TLine(runNum.front(), devmean, runNum.back(), devmean);
            TLine* emapstdp = new TLine(runNum.front(), devmean+devstd, runNum.back(), devmean+devstd);
            TLine* emapstdm = new TLine(runNum.front(), devmean-devstd, runNum.back(), devmean-devstd);
            emapstdp->SetLineWidth(4);
            emapstdm->SetLineWidth(4);
            emapstdp->SetLineColor(kRed);
            emapstdm->SetLineColor(kRed);
            TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
            meantxt->AddText(Form("Mean Deviation from Average Energy Map %.3f+/-%.3f",devmean, devstd));
            energymaptime->Draw("P1");
            for(Int_t i=1;i<96;i++){
                energymaptime->GetXaxis()->SetBinLabel(energymaptime->FindBin(runNum[i]), TString(Form("%.0f",runNum[i])));
            }

            for(Int_t i=0;i<emapind;i++){
                cout<<"Filling bin#:"<<TString(Form("%.0f",Emapruns[i]))<<" With value:"<<dev[i]<<'\n';
                energymaptime->Fill(TString(Form("%.0f",Emapruns[i])), dev[i]);
            }
            energymaptime->GetXaxis()->SetLabelSize(0.02);
            gPad->SetGrid(1,1);
            energymaptime->Draw("P1");
            energymaptime->Print();
            emapmean->Draw();
            emapstdp->Draw();
            emapstdm->Draw();
            meantxt->Draw();
            can1->Modified();
            can1->Update();
            can1->SaveAs(Form("./plots/LHC12%s/EnergyMapTime.png",per[period].Data()));*/

        //Occupancy Map

        TCanvas* can2 = new TCanvas("nycan2", "Pi_0 mass by run number", 1920, 1024);

        can2->Draw();

        Int_t omapind=0;
        std::vector<Double_t> Omapruns(keys->GetEntries());

        TH2* Omap;
        Bool_t front=kFALSE;
        Double_t norm=1;
        for(Int_t i=0;i<keys->GetEntries();i++){
            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"Occupancy")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        if(!front){Omap=(TH2*)(list->At(h))->Clone();front=kTRUE;}else{
                            Omap->Add((TH2*)list->At(h));
                            norm++;
                        }
                    }
                }
            }
        }
        cout<<"boiiiiii";

        Omap->Scale(1/norm);
        can2->Draw();
        Omap->Draw("colz");
        can2->SaveAs(Form("./plots/LHC12%s/OMapAve.png",per[period].Data()));
        std::vector<Double_t> odev(keys->GetEntries());


        for(Int_t i=0;i<keys->GetEntries();i++){
            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"Occupancy")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TH2* temp=(TH2*)(list->At(h))->Clone();
                        temp->Add(Omap, -1);
                        odev[omapind]=temp->Integral();
                        Omapruns[omapind]=TString(keys->At(i)->GetName()).Atoi();
                        omapind++;
                    }
                }
            }
        }

        Double_t odevmean = 0;
        for(Int_t i=0;i<omapind;i++){odevmean+=odev[i];}
        odevmean=odevmean/Double_t(omapind);

        Double_t odevstd = 0;
        for(Int_t i=0;i<omapind;i++){odevstd+=(odev[i]-odevmean)*(odev[i]-odevmean);}
        odevstd = TMath::Sqrt(odevstd/Double_t(omapind));

        can2->cd();
        
        Int_t BadRunsOM[500];
        Int_t bromInd = 0;
        
        TH1F* occmap = new TH1F("occmaprbr", "This is a plot ", 96, runNum.front(), runNum.back());
        occmap->SetStats(0);
        occmap->SetMarkerStyle(4);
        occmap->SetTitle("Sum Deviation from Average Occupancy Map by Run Number");
        occmap->GetXaxis()->SetTitle("Run Number");
        occmap->GetYaxis()->SetTitle("Sum Deviation from Average Occupancy Map");
        TLine* omapmean = new TLine(runNum.front(), odevmean, runNum.back(), odevmean);
        TLine* omapstdp = new TLine(runNum.front(), odevmean+odevstd, runNum.back(), odevmean+odevstd);
        TLine* omapstdm = new TLine(runNum.front(), odevmean-odevstd, runNum.back(), odevmean-odevstd);
        omapstdp->SetLineWidth(4);
        omapstdm->SetLineWidth(4);
        omapstdp->SetLineColor(kRed);
        omapstdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Mean Deviation from Average Occupancy Map %.3f+/-%.3f",odevmean, odevstd));
        occmap->Draw("p");
        for(Int_t i=1;i<96;i++){
            occmap->GetXaxis()->SetBinLabel(i, TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<omapind;i++){
            occmap->Fill(TString(Form("%.0f",Omapruns[i])), odev[i]);
            if(TMath::Abs(odevmean-odev[i])>odevstd){
                    cout<<Omapruns[i]<<'\n';
                    BadRunsOM[bromInd] = Omapruns[i];
                    bromInd++;
                }
        }
        occmap->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        occmap->Draw("P1");
        occmap->Print();
        omapmean->Draw();
        omapstdp->Draw();
        omapstdm->Draw();
        meantxt->Draw();
        can2->Modified();
        can2->Update();
        can2->SaveAs(Form("./plots/LHC12%s/OccupancyMapRunByRun.png",per[period].Data()));


        can1->Clear();
        TH1F* occmaptime = new TH1F("omaptime", "This is a plot ", runNum.back()-runNum.front(), runNum.front(), runNum.back());
        occmaptime->SetStats(0);
        occmaptime->SetMarkerStyle(4);
        occmaptime->SetTitle("Sum Deviation from Average Occupancy Map by Time");
        occmaptime->GetXaxis()->SetTitle("Time[Run #]");
        occmaptime->GetYaxis()->SetTitle("Sum Deviation from Average Occupancy Map");
        TLine* omapmean = new TLine(runNum.front(), odevmean, runNum.back(), odevmean);
        TLine* omapstdp = new TLine(runNum.front(), odevmean+odevstd, runNum.back(), odevmean+odevstd);
        TLine* omapstdm = new TLine(runNum.front(), odevmean-odevstd, runNum.back(), odevmean-odevstd);
        omapstdp->SetLineWidth(4);
        omapstdm->SetLineWidth(4);
        omapstdp->SetLineColor(kRed);
        omapstdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Mean Deviation from Average Occupancy Map %.3f+/-%.3f",odevmean, odevstd));
        occmaptime->Draw("P1");
        for(Int_t i=1;i<96;i++){
            occmaptime->GetXaxis()->SetBinLabel(occmaptime->FindBin(runNum[i]), TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<omapind;i++){
            occmaptime->Fill(TString(Form("%.0f",Omapruns[i])), odev[i]);
        }
        occmaptime->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        occmaptime->Draw("P1");
        occmaptime->Print();
        omapmean->Draw();
        omapstdp->Draw();
        omapstdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/OccupancyMapTime.png",per[period].Data()));
        
        for(Int_t i=0; BadRunsOM[i]; i++){
               BadRunList<<"Occupancy Map: "<<BadRunsOM[i]<<'\n';
        }

        //Cluster vs track

        TProfile* cvtave = new TProfile();
        Bool_t cvtfront=kTRUE;
        std:vector<Double_t> Cvtruns;
        Double_t cvtstd;
        std:vector<Double_t> cvtdev;
        std:vector<Double_t> cvtdevstd;
        Double_t cvtnorm;
        Int_t cvtind=0;

        cout<<"front cvt\n";
        for(Int_t i=0;i<keys->GetEntries();i++){
            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* cvtlist=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"ClusterVsTrack ")==0){
                    for(Int_t h=0;h<cvtlist->GetEntries();h++){
                        TProfile* cvthist = ((TH2F*)cvtlist->At(h))->ProfileX();
                        if(cvtfront){
                            if(cvthist){
                                cvtave = cvthist;
                                cvtfront = kFALSE;
                            }
                        }
                        else{
                            if(cvthist){ 
                                cvtave->Add(cvthist);
                            }
                        }
                        cvtnorm++;
                    }
                }
            }
        }
        can1->Draw();
        cvtave->Scale(1/cvtnorm);
        cvtave->SetStats(0);
        cvtave->Draw("colz");
        can1->SaveAs(Form("./plots/LHC12%s/CvtAve.png",per[period].Data()));

        for(Int_t i=0;i<keys->GetEntries();i++){

            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"ClusterVsTrack ")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TProfile* cvthist = ((TH2F*)list->At(h))->ProfileX();
                        cvthist->Print();
                        if(cvthist){
                            TProfile* cvtdevhist = cvthist;
                            cvtdevhist->Add(cvtave, -1);
                            cvtdev.push_back(cvtdevhist->GetMean(2));
                            cvtdevstd.push_back(cvtdevhist->GetMeanError(2));
                            Cvtruns.push_back(TString(keys->At(i)->GetName()).Atoi());
                            cvtind++;
                        }
                    }
                }
            }
        }

        Double_t cdevmean = 0;
        for(Int_t i=0;i<cvtind;i++){cdevmean+=cvtdev[i];}
        cdevmean=cdevmean/Double_t(cvtind);

        Double_t cdevstd = 0;
        for(Int_t i=0;i<cvtind;i++){cdevstd+=TMath::Sqrt(cvtdevstd[i]);}
        cdevstd = cdevstd/Double_t(cvtind);

        can1->Clear();
        can1->Draw();
        can1->cd();
        
        Int_t BadRunsCV[500];
        Int_t brcvInd = 0;
        
        TH1F* cvt = new TH1F("cvtrbr", "This is a plot ", 96, runNum.front(), runNum.back());
        cvt->SetStats(0);
        cvt->SetMarkerStyle(4);
        cvt->SetTitle("Deviation from Average EMCal Multiplicity vs. Track Multiplicity Profile by Run Number");
        cvt->GetXaxis()->SetTitle("Run Number");
        cvt->GetYaxis()->SetTitle("Mean deviation from calo v. track mult. profile");
        TLine* cvtmean = new TLine(runNum.front(), cdevmean, runNum.back(), cdevmean);
        TLine* cvtstdp = new TLine(runNum.front(), +cdevstd, runNum.back(), +cdevstd);
        TLine* cvtstdm = new TLine(runNum.front(), -cdevstd, runNum.back(), -cdevstd);
        cvtstdp->SetLineWidth(4);
        cvtstdm->SetLineWidth(4);
        cvtstdp->SetLineColor(kRed);
        cvtstdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from Average EMCal Mult. vs. Track Multiplicities Profile +/-%.3f", cdevstd));
        cvt->Draw("p1");
        for(Int_t i=1;i<keys->GetEntries();i++){
            cvt->GetXaxis()->SetBinLabel(i, TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<cvtind;i++){
            cvt->Fill(TString(Form("%.0f",Cvtruns[i])), cvtdev[i]-cdevmean);
            if(TMath::Abs(cdevmean-cvtdev[i])>cdevstd){
                    cout<<Cvtruns[i]<<'\n';
                    BadRunsCV[brcvInd] = Cvtruns[i];
                    brcvInd++;
                }
        }
        cvt->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        cvt->Draw("p1");
        cvt->Print();
        cvtmean->Draw();
        cvtstdp->Draw();
        cvtstdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/CvtRunByRun.png",per[period].Data()));

        TH1F* cvttime = new TH1F("cvttime", "This is a plot ", runNum.back()-runNum.front(), runNum.front(), runNum.back());
        cvttime->SetStats(0);
        cvttime->SetMarkerStyle(4);
        cvttime->SetTitle("Deviation from Average EMCal Multiplicity vs. Track Multiplicity Profile by Run Number");
        cvttime->GetXaxis()->SetTitle("Time[Run #]");
        cvttime->GetYaxis()->SetTitle("Deviation from EMCal Mult. vs. Track Mult. Profile");
        TLine* cvtmean = new TLine(runNum.front(), cdevmean, runNum.back(), cdevmean);
        TLine* cvtstdp = new TLine(runNum.front(), +cdevstd, runNum.back(), +cdevstd);
        TLine* cvtstdm = new TLine(runNum.front(), -cdevstd, runNum.back(), -cdevstd);
        cvtstdp->SetLineWidth(4);
        cvtstdm->SetLineWidth(4);
        cvtstdp->SetLineColor(kRed);
        cvtstdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from Average EMCal Mult. vs. Track Mult. Profile +/-%.3f", cdevstd));
        cvttime->Draw("P1");
        for(Int_t i=1;i<keys->GetEntries();i++){
            cvttime->GetXaxis()->SetBinLabel(cvttime->FindBin(runNum[i]), TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<cvtind;i++){
            cvttime->Fill(TString(Form("%.0f",Cvtruns[i])), cvtdev[i]-cdevmean);
        }
        cvttime->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        cvttime->Draw("P1");
        cvttime->Print();
        cvtmean->Draw();
        cvtstdp->Draw();
        cvtstdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/CvtTime.png",per[period].Data()));
        
        for(Int_t i=0; BadRunsCV[i]; i++){
               BadRunList<<"CV: "<<BadRunsCV[i]<<'\n';
        }

        //ClusterE vs track
        can1->Clear();
        TProfile* cevtave = new TProfile();
        Bool_t cevtfront=kTRUE;
        std:vector<Double_t> Cevtruns(keys->GetEntries());
        Double_t cevtstd;
        std:vector<Double_t> cevtdev(keys->GetEntries());
        std:vector<Double_t> cevtdevstd(keys->GetEntries());
        Double_t cevtnorm=1;
        Int_t cevtind=0;

        for(Int_t i=0;i<keys->GetEntries();i++){
            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"ClusterEVsTrack ")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TProfile* cevthist = ((TH2F*)list->At(h))->ProfileX();
                        if(cevtfront){
                            if(cevthist){
                                cevtave = cevthist;
                                cevtfront=kFALSE;
                            }
                        }
                        else{
                            if(cevthist){ 
                                cevtave->Add(cevthist);
                            }
                        }
                        cevtnorm++;
                    }
                }
            }
        }
        can1->Draw();
        cevtave->SetStats(0);
        cevtave->Draw("colz");
        can1->SaveAs(Form("./plots/LHC12%s/CevtAve.png",per[period].Data()));
        for(Int_t i=0;i<keys->GetEntries();i++){

            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"ClusterEVsTrack ")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TProfile* cevthist = ((TH2F*)list->At(h))->ProfileX();
                        if(cevthist){
                            TProfile* cevtdevhist = cevthist;
                            cevtdevhist->Add(cevtave, -1);
                            cevtdev[cevtind] = cevtdevhist->GetMean(2);
                            cevtdevstd[cevtind] = cevtdevhist->GetMeanError(2);
                            Cevtruns[cevtind]=TString(keys->At(i)->GetName()).Atoi();
                            cevtind++;
                        }
                    }
                }
            }
        }

        Double_t cedevmean = 0;
        for(Int_t i=0;i<cevtind;i++){cedevmean+=cevtdev[i];}
        cedevmean=cedevmean/Double_t(cevtind);

        Double_t cedevstd = 0;
        for(Int_t i=0;i<cevtind;i++){cedevstd+=TMath::Sqrt(cevtdevstd[i]);}
        cedevstd = cedevstd/Double_t(cevtind);

        can1->Clear();
        can1->Draw();
        can1->cd();
        
        Int_t BadRunsCEV[500];
        Int_t brcevInd = 0;
        
        TH1F* cevt = new TH1F("cevtrbr", "This is a plot ", 96, runNum.front(), runNum.back());
        cevt->SetStats(0);
        cevt->SetMarkerStyle(4);
        cevt->SetTitle("Deviation from Average EMCal Energy vs. Track Multiplicity Profile by Run Number");
        cevt->GetXaxis()->SetTitle("Run Number");
        cevt->GetYaxis()->SetTitle("Deviation from EMCal Energy vs. Track Mult. Profile");
        TLine* cevtmean = new TLine(runNum.front(), cedevmean, runNum.back(), cedevmean);
        TLine* cevtstdp = new TLine(runNum.front(), +cedevstd, runNum.back(), +cedevstd);
        TLine* cevtstdm = new TLine(runNum.front(), -cedevstd, runNum.back(), -cedevstd);
        cevtstdp->SetLineWidth(4);
        cevtstdm->SetLineWidth(4);
        cevtstdp->SetLineColor(kRed);
        cevtstdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from Average EMCal Energy vs. Track Mult. profile +/-%.3f",cedevstd));
        cevt->Draw("P1");
        for(Int_t i=1;i<96;i++){
            cevt->GetXaxis()->SetBinLabel(i, TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<cevtind;i++){
            cevt->Fill(TString(Form("%.0f",Cevtruns[i])), cevtdev[i]-cedevmean);
            if(TMath::Abs(cedevmean-cevtdev[i])>cedevstd){
                    cout<<Cevtruns[i]<<'\n';
                    BadRunsCEV[brcevInd] = Cevtruns[i];
                    brcevInd++;
                }
        }
        cevt->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        cevt->Draw("P1");
        cevt->Print();
        cevtmean->Draw();
        cevtstdp->Draw();
        cevtstdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/CevtRunByRun.png",per[period].Data()));

        TH1F* cevttime = new TH1F("cevttime", "This is a plot ", runNum.back()-runNum.front(), runNum.front(), runNum.back());
        cevttime->SetStats(0);
        cevttime->SetMarkerStyle(4);
        cevttime->SetTitle("Deviation from Average EMCal Energy vs. Track Multiplicity Profile by Run Number");
        cevttime->GetXaxis()->SetTitle("Time[Run #]");
        cevttime->GetYaxis()->SetTitle("Deviation from EMCal Energy vs. Track Mult. profile");
        TLine* cevtmean = new TLine(runNum.front(), cedevmean, runNum.back(), cedevmean);
        TLine* cevtstdp = new TLine(runNum.front(), +cedevstd, runNum.back(), +cedevstd);
        TLine* cevtstdm = new TLine(runNum.front(), -cedevstd, runNum.back(), -cedevstd);
        cevtstdp->SetLineWidth(4);
        cevtstdm->SetLineWidth(4);
        cevtstdp->SetLineColor(kRed);
        cevtstdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from Average Cluster Energy vs. Track Multiplicities Profile +/-%.3f", cedevstd));
        cevttime->Draw("P1");
        for(Int_t i=1;i<96;i++){
            cevttime->GetXaxis()->SetBinLabel(cevttime->FindBin(runNum[i]), TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<cevtind;i++){
            cevttime->Fill(TString(Form("%.0f",Cevtruns[i])), cevtdev[i]-cedevmean);
        }
        cevttime->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        cevttime->Draw("P1");
        cevtmean->Draw();
        cevtstdp->Draw();
        cevtstdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/CevtTime.png",per[period].Data()));
        
        for(Int_t i=0; BadRunsCEV[i]; i++){
               BadRunList<<"CEV: "<<BadRunsCEV[i]<<'\n';
        }

        //ClusterE vs v0
        can1->Clear();
        TProfile* cev0ave = new TProfile();
        Bool_t cev0front=kTRUE;
        std:vector<Double_t> Cev0runs(keys->GetEntries());
        Double_t cev0std;
        std:vector<Double_t> cev0dev(keys->GetEntries());
        std:vector<Double_t> cev0devstd(keys->GetEntries());
        Double_t cev0norm=1;
        Int_t cev0ind=0;

        for(Int_t i=0;i<keys->GetEntries();i++){
            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"ClusterEVsV0 ")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TProfile* cev0hist = ((TH2F*)list->At(h))->ProfileX();
                        if(cev0front){
                            if(cev0hist){
                                cev0ave = cev0hist;
                                cev0front=kFALSE;
                            }
                        }
                        else{
                            if(cev0hist){ 
                                cev0ave->Add(cev0hist);
                            }
                        }
                        cev0norm++;
                    }
                }
            }
        }
        can1->Draw();
        cev0ave->SetStats(0);
        cev0ave->SetMaximum(30);
        cev0ave->Draw("colz");
        can1->SaveAs(Form("./plots/LHC12%s/Cev0Ave.png", per[period].Data()));
        for(Int_t i=0;i<keys->GetEntries();i++){

            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"ClusterEVsV0 ")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TProfile* cev0hist = ((TH2F*)list->At(h))->ProfileX();
                        if(cev0hist){
                            TProfile* cev0devhist = cev0hist;
                            cev0devhist->Add(cev0ave, -1);
                            cev0dev[cev0ind] = cev0devhist->GetMean(2);
                            cev0devstd[cev0ind] = cev0devhist->GetMeanError(2);
                            Cev0runs[cev0ind]=TString(keys->At(i)->GetName()).Atoi();
                            cev0ind++;
                        }
                    }
                }
            }
        }

        Double_t cev0devmean = 0;
        for(Int_t i=0;i<cev0ind;i++){cev0devmean+=cev0dev[i];}
        cev0devmean=cev0devmean/Double_t(cev0ind);

        Double_t cev0std = 0;
        for(Int_t i=0;i<cev0ind;i++){cev0std+=TMath::Sqrt(cev0devstd[i]);}
        cev0std = cev0std/Double_t(cev0ind);

        can1->cd();
        
        Int_t BadRunsCEV0[500];
        Int_t brcev0Ind = 0;
        
        TH1F* cev0 = new TH1F("cev0rbr", "This is a plot ", 96, runNum.front(), runNum.back());
        cev0->SetStats(0);
        cev0->SetMarkerStyle(4);
        cev0->SetTitle("Deviation from Average EMCal Energy vs. V0 Signal Profile by Run Number");
        cev0->GetXaxis()->SetTitle("Run Number");
        cev0->GetYaxis()->SetTitle("Deviation from EMCal Energy vs. V0 Signal Profile");
        TLine* cev0mean = new TLine(runNum.front(), cev0devmean, runNum.back(), cev0devmean);
        TLine* cev0stdp = new TLine(runNum.front(), +cev0std, runNum.back(), +cev0std);
        TLine* cev0stdm = new TLine(runNum.front(), -cev0std, runNum.back(), -cev0std);
        cev0stdp->SetLineWidth(4);
        cev0stdm->SetLineWidth(4);
        cev0stdp->SetLineColor(kRed);
        cev0stdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from Average EMCal Energy vs. V0 Signal Profile +/-%.3f", cev0std));
        cev0->Draw("P1");
        for(Int_t i=1;i<96;i++){
            cev0->GetXaxis()->SetBinLabel(i, TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<cev0ind;i++){
            cev0->Fill(TString(Form("%.0f",Cev0runs[i])), cev0dev[i]-cev0devmean);
            if(TMath::Abs(cev0devmean-cev0dev[i])>cev0std){
                    cout<<Cev0runs[i]<<'\n';
                    BadRunsCEV0[brcev0Ind] = Cev0runs[i];
                    brcev0Ind++;
                }
        }
        cev0->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        cev0->Draw("P1");
        cev0mean->Draw();
        cev0stdp->Draw();
        cev0stdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/Cev0RunByRun.png",per[period].Data()));

        TH1F* cev0time = new TH1F("cev0time", "This is a plot ", runNum.back()-runNum.front(), runNum.front(), runNum.back());
        cev0time->SetStats(0);
        cev0time->SetMarkerStyle(4);
        cev0time->SetTitle("Deviation from Average EMCal Energy vs. V0 Signal Profile by Run Number");
        cev0time->GetXaxis()->SetTitle("Time[Run #]");
        cev0time->GetYaxis()->SetTitle("Deviation from EMCal Energy v. V0 Signal Profile");
        TLine* cev0mean = new TLine(runNum.front(), cev0devmean, runNum.back(), cev0devmean);
        TLine* cev0stdp = new TLine(runNum.front(), +cev0std, runNum.back(), +cev0std);
        TLine* cev0stdm = new TLine(runNum.front(), -cev0std, runNum.back(), -cev0std);
        cev0stdp->SetLineWidth(4);
        cev0stdm->SetLineWidth(4);
        cev0stdp->SetLineColor(kRed);
        cev0stdm->SetLineColor(kRed);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from Average EMCal Energy vs. V0 Signal Profile +/-%.3f", cev0std));
        cev0time->Draw("P1");
        for(Int_t i=1;i<96;i++){
            cev0time->GetXaxis()->SetBinLabel(cev0time->FindBin(runNum[i]), TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<cev0ind;i++){
            cev0time->Fill(TString(Form("%.0f",Cev0runs[i])), cev0dev[i]-cev0devmean);
        }
        cev0time->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        cev0time->Draw("P1");
        cev0time->Print();
        cev0mean->Draw();
        cev0stdp->Draw();
        cev0stdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/Cev0Time.png",per[period].Data()));
        
        for(Int_t i=0; BadRunsCEV0[i]; i++){
               BadRunList<<"CEV0: "<<BadRunsCEV0[i]<<'\n';
        }

        //Time Vs. E
        can1->Clear();
        TProfile* tveave = new TProfile();
        Bool_t tvefront=kTRUE;
        std:vector<Double_t> Tveruns(keys->GetEntries());
        Double_t tvestd;
        std:vector<Double_t> tvedev(keys->GetEntries());
        std:vector<Double_t> tvedevstd(keys->GetEntries());
        Double_t tvenorm=1;
        Int_t tveind=0;

        for(Int_t i=0;i<keys->GetEntries();i++){
            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"TimeVsE")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TProfile* tvehist = ((TH2F*)list->At(h))->ProfileX();
                        if(tvefront){
                            if(tvehist){
                                tveave = tvehist;
                                tvefront=kFALSE;
                            }
                        }
                        else{
                            if(tvehist){ 
                                tveave->Add(tvehist);
                            }
                        }
                        tvenorm++;
                    }
                }
            }
        }
        can1->Draw();
        tveave->SetStats(0);
        tveave->Draw("colz");
        can1->SaveAs(Form("./plots/LHC12%s/tveAve.png", per[period].Data()));
        for(Int_t i=0;i<keys->GetEntries();i++){

            TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
            TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
            if(!findir){
                continue;
            }

            for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
                TCanvas* can;
                TList* plots = findir->GetListOfKeys();
                findir->GetObject(plots->At(j)->GetName(), can);
                TList* list=can->GetListOfPrimitives();
                if(strcmp(can->GetName(),"TimeVsE")==0){
                    for(Int_t h=0;h<list->GetEntries();h++){
                        TProfile* tvehist = ((TH2F*)list->At(h))->ProfileX();
                        if(tvehist){
                            TProfile* tvedevhist = tvehist;
                            tvedevhist->Add(tveave, -1);
                            tvedev[tveind] = tvedevhist->GetMean(2);
                            tvedevstd[tveind] = tvedevhist->GetMeanError(2);
                            Tveruns[tveind]=TString(keys->At(i)->GetName()).Atoi();
                            tveind++;
                        }
                    }
                }
            }
        }

        Double_t tvedevmean = 0;
        for(Int_t i=0;i<tveind;i++){tvedevmean+=tvedev[i];}
        tvedevmean=tvedevmean/Double_t(tveind);

        Double_t tvestd = 0;
        for(Int_t i=0;i<tveind;i++){tvestd+=TMath::Sqrt(tvedevstd[i]);}
        tvestd = tvestd/Double_t(tveind);

        can1->cd();
        
        TH1F* tve = new TH1F("tverbr", "This is a plot ", 96, runNum.front(), runNum.back());
        tve->SetStats(0);
        tve->SetMarkerStyle(4);
        tve->SetTitle("Deviation from EMCal TOF vs. EMCal Energy Profile by Run Number");
        tve->GetXaxis()->SetTitle("Run Number");
        tve->GetYaxis()->SetTitle("Deviation from EMCal TOF vs. EMCal Energy Profile");
        TLine* tvemean = new TLine(runNum.front(), tvedevmean, runNum.back(), tvedevmean);
        TLine* tvestdp = new TLine(runNum.front(), +tvestd, runNum.back(), +tvestd);
        TLine* tvestdm = new TLine(runNum.front(), -tvestd, runNum.back(), -tvestd);
        tvestdp->SetLineColor(kRed);
        tvestdm->SetLineColor(kRed);
        tvestdp->SetLineWidth(4);
        tvestdm->SetLineWidth(4);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from EMCal TOF vs. EMCal Energy Profile +/-%.3f", tvestd));
        tve->Draw("P1");
        for(Int_t i=1;i<96;i++){
            tve->GetXaxis()->SetBinLabel(i, TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<tveind;i++){
            tve->Fill(TString(Form("%.0f",Tveruns[i])), tvedev[i]-tvedevmean);
        }
        tve->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        tve->Draw("P1");
        tve->Print();
        tvemean->Draw();
        tvestdp->Draw();
        tvestdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/TveRunByRun.png",per[period].Data()));

        TH1F* tvetime = new TH1F("tvetime", "This is a plot ", runNum.back()-runNum.front(), runNum.front(), runNum.back());
        tvetime->SetStats(0);
        tvetime->SetMarkerStyle(4);
        tvetime->SetTitle("Deviation from EMCal TOF vs. EMCal Energy Profile by Run Number");
        tvetime->GetXaxis()->SetTitle("Time[Run #]");
        tvetime->GetYaxis()->SetTitle("Deviation from EMCal TOF vs. EMCal Energy Profile");
        TLine* tvemean = new TLine(runNum.front(), tvedevmean, runNum.back(), tvedevmean);
        TLine* tvestdp = new TLine(runNum.front(), +tvestd, runNum.back(), +tvestd);
        TLine* tvestdm = new TLine(runNum.front(), -tvestd, runNum.back(), -tvestd);
        tvestdp->SetLineColor(kRed);
        tvestdm->SetLineColor(kRed);
        tvestdp->SetLineWidth(4);
        tvestdm->SetLineWidth(4);
        TPaveText* meantxt = new TPaveText(.6, .8, .9, .7, "NDC");
        meantxt->AddText(Form("Deviation from EMCal TOF vs. EMCal Energy Profile +/-%.3f", tvestd));
        tvetime->Draw("P1");
        for(Int_t i=1;i<96;i++){
            tvetime->GetXaxis()->SetBinLabel(tvetime->FindBin(runNum[i]), TString(Form("%.0f",runNum[i])));
        }

        for(Int_t i=0;i<tveind;i++){
            tvetime->Fill(TString(Form("%.0f",Tveruns[i])), tvedev[i]-tvedevmean);
        }
        tvetime->GetXaxis()->SetLabelSize(0.02);
        gPad->SetGrid(1,1);
        tvetime->Draw("P1");
        tvetime->Print();
        tvemean->Draw();
        tvestdp->Draw();
        tvestdm->Draw();
        meantxt->Draw();
        can1->Modified();
        can1->Update();
        can1->SaveAs(Form("./plots/LHC12%s/tveTime.png",per[period].Data()));
    }
    BadRunList.close();
}
