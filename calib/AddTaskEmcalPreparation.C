AliAnalysisTaskSE *AddTaskEmcalPreparation(const char *perstr  = "LHC11h",
                                           UInt_t clusterizer  = AliEMCALRecParam::kClusterizerv2,
					   const char *pass    = 0 /*should not be needed; will be recovered from path of AOD/ESD; no need to specify by user; */
					   ) {

  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr)
  {
    ::Error("AddTaskEmcalPreparation", "No analysis manager to connect to.");
    return NULL;
  }

  TString period(perstr);
  period.ToLower();

  Bool_t isMC = kFALSE;
  if(period.Sizeof()>7) isMC = kTRUE;
  //  Bool_t isMC = (mgr->GetMCtruthEventHandler() != NULL); //only works for ESD
  if(isMC) Printf("AddTaskEmcalPreparation: Running on MC");
  else     Printf("AddTaskEmcalPreparation: Running on DATA");

  //----------------------- Add tender -------------------------------------------------------
  Bool_t distBC         = kFALSE; //switch for recalculation cluster position from bad channel 
  Bool_t recalibClus    = kFALSE;
  Bool_t recalcClusPos  = kFALSE;
  Bool_t nonLinearCorr  = kFALSE;
  Bool_t remExoticCell  = kFALSE;
  Bool_t remExoticClus  = kFALSE;
  Bool_t fidRegion      = kFALSE;
  Bool_t calibEnergy    = kTRUE;
  Bool_t calibTime      = kTRUE;
  Bool_t remBC          = kTRUE;
  UInt_t nonLinFunct    = 0;
  Bool_t reclusterize   = kFALSE;
  Float_t seedthresh    = 0.1;      // 100 MeV
  Float_t cellthresh    = 0.05;     // 50 MeV 
  UInt_t clusterizerT   = 0;
  Bool_t trackMatch     = kFALSE;
  Bool_t updateCellOnly = kFALSE;
  Float_t timeMin       = -50e-9;   // minimum time of physical signal in a cell/digit
  Float_t timeMax       =  50e-9;   // maximum time of physical signal in a cell/digit
  Float_t timeCut       = 1e6;
  if(period.Contains("lhc11h")) {
    timeMin = -50e-9;
    timeMax = 100e-9;
  }
  if(isMC) {
    calibEnergy = kFALSE;
    calibTime   = kFALSE;
    timeMin = -1.;
    timeMax = 1e6;
  }
  
  gROOT->LoadMacro("$ALICE_PHYSICS/PWG/EMCAL/macros/AddTaskEMCALTender.C");//tendertasks
  AliAnalysisTaskSE *tender = AddTaskEMCALTender(distBC, recalibClus, recalcClusPos, nonLinearCorr, remExoticCell, remExoticClus,
						 fidRegion, calibEnergy, calibTime, remBC, nonLinFunct, reclusterize, seedthresh,
						 cellthresh, clusterizerT, trackMatch, updateCellOnly, timeMin, timeMax, timeCut,pass);

  //----------------------- Add clusterizer -------------------------------------------------------
  remExoticCell  = kTRUE;
  TString tmpClusters = "tmpCaloClusters";
  gROOT->LoadMacro("$ALICE_PHYSICS/PWG/EMCAL/macros/AddTaskClusterizerFast.C");
  AliAnalysisTaskEMCALClusterizeFast *clusterizerTask = AddTaskClusterizerFast("ClusterizerFast","",tmpClusters.Data(),clusterizer,cellthresh,seedthresh,
									       timeMin,timeMax,timeCut,remExoticCell,distBC,
									       AliAnalysisTaskEMCALClusterizeFast::kFEEData);
  
  //----------------------- Add cluster maker -----------------------------------------------------
  gROOT->LoadMacro("$ALICE_PHYSICS/PWG/EMCAL/macros/AddTaskEmcalClusterMaker.C"); //cluster maker: non-linearity, 
  UInt_t nonLinFunct = AliEMCALRecoUtils::kBeamTestCorrected;
  if(isMC) {
    if(period == "lhc12a15a") 
      nonLinFunct = AliEMCALRecoUtils::kPi0MCv2;
    else
      nonLinFunct = AliEMCALRecoUtils::kPi0MCv3;
  }
  remExoticClus  = kTRUE;
  AliEmcalClusterMaker *clusMaker = AddTaskEmcalClusterMaker(nonLinFunct,remExoticClus,tmpClusters.Data(),"EmcCaloClusters",0.,kTRUE);
  
  return clusterizerTask;
  
}
