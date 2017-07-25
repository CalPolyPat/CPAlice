// runJetAna.C
//
// run macro for jet studies with the Cal Poly group
//
// Author: Patrick j. Steffanic
//
class AliAnalysisGrid;
class AliAnalysisTaskPatJet;
class AliEmcalJetTask;
#include <TSystem.h>
    #include <TROOT.h>
    #include <TGrid.h>


    void LoadLibs();
void LoadMacros();
AliMagF* ConfigCalibTrain(const char *ocdb="raw://");
AliAnalysisGrid* CreateAlienHandler(const char *taskname, const char *gridmode, const char *proofcluster, const char *proofdataset);

//______________________________________________________________________________
void runJetAna(
    const char* runtype = "grid", // local, proof or grid
    const char *gridmode = "terminate", // Set the run mode (can be "full", "test", "offline", "submit" or "terminate"). Full & Test work for proof
    const bool bMCtruth = 0, // 1 = MCEvent handler is on (MC truth), 0 = MCEvent handler is off (MC reconstructed/real data)
    const bool bMCphyssel = 0, // 1 = looking at MC truth or reconstructed, 0 = looking at real data
    const Long64_t nentries = 10000, // for local and proof mode, ignored in grid mode. Set to 1234567890 for all events.
    const Long64_t firstentry = 0, // for local and proof mode, ignored in grid mode
    const char *proofdataset = "/alice/data/LHC10c_000120821_p1", // path to dataset on proof cluster, for proof analysis
    const char *proofcluster = "alice-caf.cern.ch", // which proof cluster to use in proof mode
    const char *taskname = "PSJetTask" // sets name of grid generated macros
)
{
    // check run type
    if(runtype != "local" && runtype != "proof" && runtype != "grid"){
        printf("\n\tIncorrect run option, check first argument of run macro");
        printf("\tint runtype = local, proof or grid\n");
        return;
    }
    printf("%s analysis chosen \n",runtype);

    
    // include ALIROOT and ALIPHYSICS


    

    //Initialize the magneic field(Do I need to do this?)
    if (!TGeoGlobalMagField::Instance()->GetField()) printf("Field map is not set.\n");
    TGeoGlobalMagField::Instance()->SetField(ConfigCalibTrain());
    if (!TGeoGlobalMagField::Instance()->GetField()) printf("Field map is not set after.\n");

    AliTrackContainer::SetDefTrackCutsPeriod("lhc12d");

    Printf("Default track cut period set to: %s", AliTrackContainer::GetDefTrackCutsPeriod().Data());


    // analysis manager
    AliAnalysisManager* mgr = new AliAnalysisManager(taskname);

    // create the alien handler and attach it to the manager
    AliAnalysisGrid *plugin = CreateAlienHandler(taskname, gridmode, proofcluster, proofdataset); 
    mgr->SetGridHandler(plugin);
    plugin->AddIncludePath("-I -I$ROOTSYS/include -I$ALICE_PHYSICS/include -I$ALICE_PHYSICS/EMCAL");
    plugin->AddIncludePath("-I$ALICE_ROOT/include");

    // create the inputhandler and assign it to the manager
    AliAODInputHandler* iH = AliAnalysisTaskEmcal::AddAODHandler();
    iH->SetNeedField(kTRUE);

    mgr->SetInputEventHandler(iH);    

    LoadLibs();

    LoadMacros();
    
        gSystem->AddIncludePath("-I$ALICE_ROOT/include -I$ALICE_ROOT -I$ALICE_PHYSICS/EMCAL");
    gSystem->AddIncludePath("-I$ALICE_PHYSICS/include");

    gROOT->ProcessLine(".L AliAnalysisTaskPatJet.cxx+");
    
    
    //________________________________________________BEGIN TASKS____________________________________________________________________________

    // CDB[Conditions Database]connect task
    AliTaskCDBconnect *taskCDB = AddTaskCDBconnect();
    taskCDB->SetFallBackToRaw(kTRUE);

    //Do EMCal corrections
    //---------------
    AliEmcalCorrectionTask * correctionTask = AliEmcalCorrectionTask::AddTaskEmcalCorrectionTask();
    correctionTask->SetForceBeamType(AliAnalysisTaskEmcal::kpp);

    // Configure and initialize
    correctionTask->SetUserConfigurationFilename("$ALICE_PHYSICS/PWG/EMCAL/config/PWGJESampleConfig.yaml");
    correctionTask->Initialize();


    //PID task          
    gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
    Bool_t isMC=kFALSE; // kTRUE in case of MC
    AddTaskPIDResponse(isMC); 

    //---------------
    
    // Full Jet finder task, usedefault uses the standard container names which must match the branches coming from the input data
    AliEmcalJetTask *FullJet02Task = AliEmcalJetTask::AddTaskEmcalJet("usedefault", "usedefault", AliJetContainer::antikt_algorithm, 0.2, AliJetContainer::kFullJet, 0.15, 0.30, .005, AliJetContainer::pt_scheme, "FJet", 1., kFALSE, kFALSE);
    FullJet02Task->GetClusterContainer(0)->SetDefaultClusterEnergy(AliVCluster::kHadCorr);
    FullJet02Task->SelectCollisionCandidates(AliVEvent::kEMCEJE);

    // Charged jet finder task
    AliEmcalJetTask *ChargedJet02Task = AliEmcalJetTask::AddTaskEmcalJet("usedefault", "usedefault", AliJetContainer::antikt_algorithm, 0.2, AliJetContainer::kChargedJet, 0.15, 0.30, 0.005, AliJetContainer::pt_scheme, "CJet", 1., kFALSE, kFALSE);
    ChargedJet02Task->SelectCollisionCandidates(AliVEvent::kEMCEJE);

    // Full Jet finder task, usedefault uses the standard container names which must match the branches coming from the input data
    AliEmcalJetTask *FullJet04Task = AliEmcalJetTask::AddTaskEmcalJet("usedefault", "usedefault", AliJetContainer::antikt_algorithm, 0.4, AliJetContainer::kFullJet, 0.15, 0.30, .005, AliJetContainer::pt_scheme, "FJet", 1., kFALSE, kFALSE);
    FullJet04Task->GetClusterContainer(0)->SetDefaultClusterEnergy(AliVCluster::kHadCorr);
    FullJet04Task->SelectCollisionCandidates(AliVEvent::kEMCEJE);

    // Charged jet finder task
    AliEmcalJetTask *ChargedJet04Task = AliEmcalJetTask::AddTaskEmcalJet("usedefault", "usedefault", AliJetContainer::antikt_algorithm, 0.4, AliJetContainer::kChargedJet, 0.15, 0.30, 0.005, AliJetContainer::pt_scheme, "CJet", 1., kFALSE, kFALSE);
    ChargedJet04Task->SelectCollisionCandidates(AliVEvent::kEMCEJE);
    
    // Full Jet finder task, usedefault uses the standard container names which must match the branches coming from the input data
    AliEmcalJetTask *FullJet07Task = AliEmcalJetTask::AddTaskEmcalJet("usedefault", "usedefault", AliJetContainer::antikt_algorithm, 0.7, AliJetContainer::kFullJet, 0.15, 0.30, .005, AliJetContainer::pt_scheme, "FJet", 1., kFALSE, kFALSE);
    FullJet07Task->GetClusterContainer(0)->SetDefaultClusterEnergy(AliVCluster::kHadCorr);
    FullJet07Task->SelectCollisionCandidates(AliVEvent::kEMCEJE);

    // Charged jet finder task
    AliEmcalJetTask *ChargedJet07Task = AliEmcalJetTask::AddTaskEmcalJet("usedefault", "usedefault", AliJetContainer::antikt_algorithm, 0.7, AliJetContainer::kChargedJet, 0.15, 0.30, 0.005, AliJetContainer::pt_scheme, "CJet", 1., kFALSE, kFALSE);
    ChargedJet07Task->SelectCollisionCandidates(AliVEvent::kEMCEJE);

    // Jet analysis task
    AliAnalysisTaskPatJet* JetTask = 0;
    JetTask = AddTaskPatJet("usedefault", "usedefault", "usedefault");

    JetTask->SetForceBeamType(AliAnalysisTaskEmcal::kpp);
    JetTask->SelectCollisionCandidates(AliVEvent::kEMCEJE);


    // Add a container to the jet analysis task. ""EmcalJetSample adds track and cluster containers in the addtask macro.
    AliJetContainer* FjetCont02 = JetTask->AddJetContainer("FJet_AKTFullR020_tracks_pT0150_caloClusters_E0300_pt_scheme", AliEmcalJet::kEMCALfid, 0.2);
    AliJetContainer* CjetCont02 = JetTask->AddJetContainer("CJet_AKTChargedR020_tracks_pT0150_pt_scheme", AliEmcalJet::kTPCfid, 0.2);
    AliJetContainer* FjetCont04 = JetTask->AddJetContainer("FJet_AKTFullR040_tracks_pT0150_caloClusters_E0300_pt_scheme", AliEmcalJet::kEMCALfid, 0.4);
    AliJetContainer* CjetCont04 = JetTask->AddJetContainer("CJet_AKTChargedR040_tracks_pT0150_pt_scheme", AliEmcalJet::kTPCfid, 0.4);
    AliJetContainer* FjetCont07 = JetTask->AddJetContainer("FJet_AKTFullR070_tracks_pT0150_caloClusters_E0300_pt_scheme", AliEmcalJet::kEMCALfid, 0.7);
    AliJetContainer* CjetCont07 = JetTask->AddJetContainer("CJet_AKTChargedR070_tracks_pT0150_pt_scheme", AliEmcalJet::kTPCfid, 0.7);

    // enable debug printouts
    mgr->SetDebugLevel(2);
    mgr->SetNSysInfo(100);
    if (!mgr->InitAnalysis()) return;
    mgr->PrintStatus();

    // start analysis
    Printf("Starting Analysis....");
    mgr->StartAnalysis(runtype,nentries,firstentry);
}

//______________________________________________________________________________

void LoadMacros(){
    gROOT->LoadMacro("$ALICE_PHYSICS/PWGPP/PilotTrain/AddTaskCDBconnect.C");
    gROOT->LoadMacro("~/cpalice/jets/JetFindingPractice/AddTaskPatJet.C");
    gROOT->LoadMacro("~/cpalice/jets/JetFindingPractice/AliAnalysisTaskPatJet.h");
    gROOT->LoadMacro("~/cpalice/jets/JetFindingPractice/AliAnalysisTaskPatJet.cxx");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/include");
}




//______________________________________________________________________________

AliAnalysisGrid* CreateAlienHandler(const char *taskname, const char *gridmode, const char *proofcluster, const char *proofdataset)
{
    AliAnalysisAlien *plugin = new AliAnalysisAlien();
    if (!TGrid::Connect("alien://")) return; 
    
    


    plugin->SetRunMode(gridmode);

    // Set versions of used packages, check the GRID package site alimonitor.cern.ch/packages
    plugin->SetAPIVersion("V1.1x");
    plugin->SetROOTVersion("v5-34-30-alice7-11");
    plugin->SetAliROOTVersion("v5-09-09-1");
    plugin->SetAliPhysicsVersion("vAN-20170628-1");

    //Tell the plugin the base directory that will be the same for each run #. Usually will be "/alice/data/year/period"
    plugin->SetGridDataDir("/alice/data/2012/LHC12d");

    //Tell the plugin which files you want form that period. You can specify a pass # and ESD or AOD. You will need a star in between the pass and the ESD/AOD type which is obvious if you view the file structure
    plugin->SetDataPattern("pass2/*/AliAOD.root"); 

    plugin->SetRunPrefix("000");   // 000 is real data, MC data would be different
    // ...then add run numbers to be considered
    Int_t runlist[110]={184127, 184132, 184135, 184137, 184138, 184188, 184208, 184209, 184215, 184371, 184673, 184678, 184682, 184687, 184784, 184786, 184928, 184933, 184938, 184964, 184967, 184968, 184987, 184988, 184990, 185029, 185031, 185116, 185126, 185127, 185132, 185134, 185157, 185160, 185164, 185189, 185196, 185198, 185203, 185206, 185208, 185221, 185217, 185282, 185284, 185288, 185289, 185291, 185292, 185293, 185296, 185299, 185300, 185302, 185303, 185349, 185350, 185351, 185356, 185359, 185360, 185361, 185362, 185363, 185371, 185375, 185457, 185461, 185465, 185563, 185565, 185574, 185575, 185578, 185580, 185581, 185582, 185583, 185588, 185589, 185680, 185687, 185695, 185697, 185698, 185699, 185701, 185734, 185735, 185738, 185756, 185757, 185764, 185765, 185768, 185775, 185776, 185778, 185784, 185909, 185912, 186163, 186164, 186165, 186167, 186205, 186208, 186229, 186319, 186320};  
    for (Int_t ind=0; ind<20; ind++) {
        plugin->AddRunNumber(runlist[ind]);
    }

    plugin->SetDefaultOutputs(kTRUE);
    
    plugin->SetNrunsPerMaster(3); //Not sure why this is here

    //plugin->SetOverwriteMode(); //See previous comment

    plugin->SetMergeViaJDL(); //Always use unless you would like an output for each subjob

    // Define alien work directory where all files will be copied. Relative to alien $HOME.
    plugin->SetGridWorkingDir(taskname);

    // Declare alien output directory. Relative to working directory.
    plugin->SetGridOutputDir("out"); // In this case will be $HOME/taskname/out

    // Declare the analysis source files names separated by blancs. To be compiled runtime
    plugin->SetAnalysisSource("AliAnalysisTaskPatJet.cxx+");

    // Declare all libraries (other than the default ones from AliROOT/AliPHYSICS. 
    // These will be loaded by the generated analysis macro. Add all extra files (task .cxx/.h) here.
    plugin->SetAdditionalLibs("AliAnalysisTaskPatJet.h AliAnalysisTaskPatJet.cxx");

    // Optionally set a name for the generated analysis macro (default MyAnalysis.C)
    plugin->SetAnalysisMacro(Form("%s.C",taskname));

    // Optionally set maximum number of input files/subjob (default 100, put 0 to ignore)
    plugin->SetSplitMaxInputFileNumber(100);

    // Optionally modify the executable name (default analysis.sh)
    plugin->SetExecutable(Form("%s.sh",taskname));

    // set number of test files to use in "test" mode
    plugin->SetNtestFiles(15);

    // Optionally resubmit threshold.
    plugin->SetMasterResubmitThreshold(90);

    // Optionally set time to live (default 30000 sec)
    plugin->SetTTL(30000);

    // Optionally set input format (default xml-single)
    plugin->SetInputFormat("xml-single");

    // Optionally modify the name of the generated JDL (default analysis.jdl)
    plugin->SetJDLName(Form("%s.jdl",taskname));

    // Optionally modify job price (default 1)
    plugin->SetPrice(1);      

    // Optionally modify split mode (default 'se')    
    plugin->SetSplitMode("se");
    
    plugin->SetMergeViaJDL(kFALSE);
    
    //plugin->SetOverwriteMode(kFALSE);

    //----------------------------------------------------------
    //---      PROOF MODE SPECIFIC SETTINGS         ------------
    //---------------------------------------------------------- 
    // Proof cluster
    
    return plugin;
}

void LoadLibs()
{
    // Load common libraries (better too many than too few)
    gSystem->Load("libTree");
    gSystem->Load("libVMC");
    gSystem->Load("libGeom");
    gSystem->Load("libGui");
    gSystem->Load("libXMLParser");
    gSystem->Load("libMinuit");
    gSystem->Load("libMinuit2");
    gSystem->Load("libProof");
    gSystem->Load("libPhysics");
    gSystem->Load("libSTEERBase");
    gSystem->Load("libESD");
    gSystem->Load("libAOD");
    gSystem->Load("libOADB");
    gSystem->Load("libANALYSIS");
    gSystem->Load("libCDB");
    gSystem->Load("libRAWDatabase");
    gSystem->Load("libSTEER");
    gSystem->Load("libEVGEN");
    gSystem->Load("libANALYSISalice");
    gSystem->Load("libCORRFW");
    gSystem->Load("libTOFbase");
    //gSystem->Load("libTOFrec");
    gSystem->Load("libRAWDatabase");
    gSystem->Load("libRAWDatarec");
    gSystem->Load("libTPCbase");
    gSystem->Load("libTPCrec");
    gSystem->Load("libITSbase");
    gSystem->Load("libITSrec");
    gSystem->Load("libTRDbase");
    gSystem->Load("libTender");
    gSystem->Load("libSTAT");
    gSystem->Load("libTRDrec");
    gSystem->Load("libHMPIDbase");
    gSystem->Load("libPWGPP");
    gSystem->Load("libPWGHFbase");
    gSystem->Load("libPWGDQdielectron");
    gSystem->Load("libPWGHFhfe");
    gSystem->Load("libEMCALUtils");
    gSystem->Load("libPHOSUtils");
    gSystem->Load("libPWGCaloTrackCorrBase");
    gSystem->Load("libEMCALraw");
    gSystem->Load("libEMCALbase");
    gSystem->Load("libEMCALrec");
    gSystem->Load("libTRDbase");
    gSystem->Load("libVZERObase");
    gSystem->Load("libVZEROrec");
    gSystem->Load("libTender");
    gSystem->Load("libTenderSupplies");
    gSystem->Load("libPWGTools");
    gSystem->Load("libPWGEMCAL");
    gSystem->Load("libESDfilter");
    gSystem->Load("libPWGGAEMCALTasks");
    gSystem->Load("libPWGCFCorrelationsBase");
    gSystem->Load("libPWGCFCorrelationsDPhi");

}

//Function used to generate magnetic field map. Not sure where I use the magnetic field.
AliMagF* ConfigCalibTrain(const char *ocdb){

    // OCDB

    printf("setting run to");
    //AliCDBManager::Instance()->SetDefaultStorage("raw://");

    AliCDBManager::Instance()->SetDefaultStorage("alien://folder=/alice/data/2012/OCDB/");
    AliCDBManager::Instance()->SetSpecificStorage("GRP/GRP/Data", "alien://folder=/alice/data/2012/OCDB/");
    AliCDBManager::Instance()->SetRun(183913); 

    // geometry
    AliGeomManager::LoadGeometry();
    AliGeomManager::ApplyAlignObjsFromCDB("GRP");



    AliCDBEntry *entry = AliCDBManager::Instance()->Get("GRP/GRP/Data");
    AliGRPObject* grpData = (AliGRPObject*)entry->GetObject();

    Bool_t ok=kTRUE;
    Float_t l3Current = grpData->GetL3Current((AliGRPObject::Stats)0);
    if (l3Current == AliGRPObject::GetInvalidFloat()) {
        printf("GRP/GRP/Data entry:  missing value for the L3 current !");
        ok = kFALSE;
    }

    Char_t l3Polarity = grpData->GetL3Polarity();
    if (l3Polarity == AliGRPObject::GetInvalidChar()) {
        printf("GRP/GRP/Data entry:  missing value for the L3 polarity !");
        ok = kFALSE;
    }

    // Dipole
    Float_t diCurrent = grpData->GetDipoleCurrent((AliGRPObject::Stats)0);
    if (diCurrent == AliGRPObject::GetInvalidFloat()) {
        printf("GRP/GRP/Data entry:  missing value for the dipole current !");
        ok = kFALSE;
    }

    Char_t diPolarity = grpData->GetDipolePolarity();
    if (diPolarity == AliGRPObject::GetInvalidChar()) {
        printf("GRP/GRP/Data entry:  missing value for the dipole polarity !");
        ok = kFALSE;
    }

    TString beamType = grpData->GetBeamType();
    if (beamType==AliGRPObject::GetInvalidString()) {
        printf("GRP/GRP/Data entry:  missing value for the beam type ! Using UNKNOWN");
        beamType = "UNKNOWN";
    }

    Float_t beamEnergy = grpData->GetBeamEnergy();
    if (beamEnergy==AliGRPObject::GetInvalidFloat()) {
        printf("GRP/GRP/Data entry:  missing value for the beam energy ! Using 0");
        beamEnergy = 0;
    }

    // read special bits for the polarity convention and map type
    //Int_t  polConvention = grpData->IsPolarityConventionLHC() ? AliMagF::kConvLHC : AliMagF::kConvDCS2008;
    Int_t  polConvention = grpData->IsPolarityConventionLHC() ? 0 : 1;
    Bool_t uniformB = grpData->IsUniformBMap();

    if (ok) {
        AliMagF* fld = AliMagF::CreateFieldMap(TMath::Abs(l3Current) * (l3Polarity ? -1:1),
                                               TMath::Abs(diCurrent) * (diPolarity ? -1:1),
                                               polConvention,uniformB,beamEnergy, beamType.Data());
        if (fld) {
            //TGeoGlobalMagField::Instance()->SetField( fld );
            //TGeoGlobalMagField::Instance()->Lock();
            printf("Running with the B field constructed out of GRP !");
        }
    }
    else{
        printf("Problem with magnetic field setup\n");
    }
    return fld;
}
