void savQA(){
gROOT->SetBatch(kTRUE);
TFile *file = new TFile("./data/LHC12i_pass2_EMCALQA.root");
TDirectoryFile *runData = (TDirectoryFile*)file->Get("LHC12i/pass2");
TList *keys = (TList*) runData->GetListOfKeys();

Float_t piomass[1000];
pioind = 0;

cout<<keys->GetEntries();

for(Int_t i=0;i<keys->GetEntries();i++){
	TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
	gSystem->mkdir(Form("X:\\ALICE_scripts\\plots\\LHC12i\\CaloQA_trigEMC\\%s",keys->At(i)->GetName()));
	TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_trigEMC");
	if(!findir){
		
		continue;
	}
	for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
		TCanvas* can;
		TList* plots = findir->GetListOfKeys();
		findir->GetObject(plots->At(j)->GetName(), can);
		TList* list=can->GetListOfPrimitives();
		if(list->At(0)){
			if(list->At(0)->GetName()=="Mgg"){
				TH1F* pihist = (TH1F*)list->At(0));
				cout<<pihist->GetName();
				if(pihist){
					//TF1* pifit = pihist.GetFunction();
					if(pifit){
						piomass[pioind]=pifit.GetParameter(1);
						pioind++;
					}
				}
			}
		}
				
		can->Draw();
		can->SaveAs(Form("X:\\ALICE_scripts\\plots\\LHC12i\\CaloQA_trigEMC\\%s\\%s.png",keys->At(i)->GetName(), plots->At(j)->GetName()));
	}
}

for(Int_t i=0;i<keys->GetEntries();i++){
	TDirectory* curRun = runData->GetDirectory(keys->At(i)->GetName());
	gSystem->mkdir(Form("X:\\ALICE_scripts\\plots\\LHC12i\\CaloQA_default\\%s",keys->At(i)->GetName()));
	TDirectory* findir = curRun->GetDirectory("RunLevelQA/CaloQA_default");
	cout<<"or maybe hered oh";
	if(!findir){
		cout<<"Busted ass findir";
		continue;
	}
	for(Int_t j=0;j<findir->GetListOfKeys()->GetEntries();j++){
		TCanvas* can;
		TList* plots = findir->GetListOfKeys();
		findir->GetObject(plots->At(j)->GetName(), can);
		cout<<"or could it be here doh";
		can->Draw();
		can->SaveAs(Form("X:\\ALICE_scripts\\plots\\LHC12i\\CaloQA_default\\%s\\%s.png",keys->At(i)->GetName(), plots->At(j)->GetName()));
	}
}

for(Int_t i=0; i<50; i++){
	cout<<piomass[i];
}
}
