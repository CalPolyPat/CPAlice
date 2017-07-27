
void Config() { static UInt_t sseed = 50356828592; gRandom->SetSeed(sseed);

gSystem->Load("liblhapdf.so");
gSystem->Load("libEGPythia6");
gSystem->Load("libpythia6");
gSystem->Load("libgeant321");
gSystem->Load("libAliPythia6");

  gSystem->Load("libEG");
  gSystem->Load("libGeom");
  gSystem->Load("libVMC");
gSystem->Load("libSTEERBase");



new TGeant3TGeo("c++ Interface to Geant3");

AliRunLoader* rl = AliRunLoader::Open("galice.root", AliConfig::GetDefaultEventFolderName(), "recreate");
if(!rl) Fatal("Cong.C", "Can not instantiate the Run Loader");
rl->SetCompressionLevel(2);
rl->SetNumberOfEventsPerFile(3);

gAlice->SetRunLoader(rl);

TVirtualMCDecayer* decayer = new AliDecayerPythia();
decayer->SetForceDecay(kAll);
decayer->Init();

gMC->SetExternalDecayer(decayer);

gMC->SetProcess("DCAY", 1);

gMC->SetProcess("PAIR",1);
gMC->SetProcess("COMP",1);
gMC->SetProcess("PHOT",1);
gMC->SetProcess("PFIS",0);
gMC->SetProcess("DRAY",1);
gMC->SetProcess("ANNI",1);
gMC->SetProcess("BREM",1);
gMC->SetProcess("MUNU",1);
gMC->SetProcess("CKOV",1);
gMC->SetProcess("HADR",1);
gMC->SetProcess("LOSS",2);
gMC->SetProcess("MULS",1);
gMC->SetProcess("RAYL",1);

Float_t cut = .001;
Float_t tofmax = 10000000;

gMC->SetCut("CUTGAM", cut);
gMC->SetCut("CUTELE", cut);
gMC->SetCut("CUTNEU", cut);
gMC->SetCut("CUTHAD", cut);
gMC->SetCut("CUTMUO", cut);
gMC->SetCut("BCUTE", cut);
gMC->SetCut("BCUTM", cut);
gMC->SetCut("DCUTE", cut);
gMC->SetCut("DCUTM", cut);
gMC->SetCut("PPCUTM", cut);
gMC->SetCut("TOFMAX", tofmax);

AliGenCocktail* gener = new AliGenCocktail();

gener->SetPhiRange(0, 360);

gener->SetThetaRange(0.0394, 179.96);

gener->SetOrigin(0,0,0);
gener->SetSigma(0,0,5.3);
gener->SetCutVertexZ(1.);
gener->SetVertexSmear(kPerEvent);


// Second cocktail component: one gamma in PHOS direction
AliGenBox *genbox = new AliGenBox(1);
genbox->SetMomentumRange(10,11.);
genbox->SetPhiRange(270.5,270.7);
genbox->SetThetaRange(90.5,90.7);
genbox->SetPart(22);
gener->AddGenerator(genbox,"GENBOX GAMMA for PHOS",1);
gener->Init(); // Initialization of the coctail generator
// Field (the last parameter is 1 => L3 0.4 T)

// Make sure the current ROOT directory is in galice.root
rl->CdGAFile();
// ALICE BODY parameters. BODY is always present
AliBODY* BODY = new AliBODY("BODY", "ALICE envelop");
// Start with Magnet since detector layouts may be depending
// on the selected Magnet dimensions
AliMAG *MAG = new AliMAG("MAG", "Magnet");

// Absorber
//AliABSO *ABSO = new AliABSOv0("ABSO", "Muon Absorber");
// Dipole magnet
AliDIPO *DIPO = new AliDIPOv2("DIPO", "Dipole version 2");
// Hall
AliHALL *HALL = new AliHALL("HALL", "ALICE Hall");

// Space frame
AliFRAMEv2 *FRAME = new AliFRAMEv2("FRAME", "Space Frame");
if (kTRUE) {
FRAME->SetHoles(1);
} else {
FRAME->SetHoles(0);
}
// Shielding
//AliSHIL *SHIL = new AliSHILv2("SHIL", "Shielding Version 2");

// Beam pipe
AliPIPE *PIPE = new AliPIPEv0("PIPE", "Beam Pipe");
// ITS parameters
/*AliITSvPPRasymmFMD *ITS = new AliITSvPPRasymmFMD("ITS","ITS PPR detailed version with asymmetric services");
ITS->SetMinorVersion(2); // dont change it if youre not an ITS developer
ITS->SetReadDet(kTRUE); // dont change it if youre not an ITS developer
ITS->SetThicknessDet1(200.); // detector thickness on layer 1
// must be in the range [100,300]
ITS->SetThicknessDet2(200.); // detector thickness on layer 2
// must be in the range [100,300]
ITS->SetThicknessChip1(200.); // chip thickness on layer 1
// must be in the range [150,300]
ITS->SetThicknessChip2(200.); // chip thickness on layer 2
// must be in the range [150,300]
ITS->SetRails(0); // 1 > rails in ; 0 > rails out
ITS->SetCoolingFluid(1); // 1 > water ; 0 > freon
ITS->SetEUCLID(0); // no output for the EUCLID CAD system
*/
// TPC
AliTPC *TPC = new AliTPCv2("TPC", "Default");
// TOF
//AliTOF *TOF = new AliTOFv4T0("TOF", "normal TOF");
// HMPID
//AliRICH *RICH = new AliRICHv1("RICH", "normal RICH");

// ZDC
//AliZDC *ZDC = new AliZDCv2("ZDC", "normal ZDC");
// TRD parameters
//AliTRD *TRD = new AliTRDv1("TRD", "TRD slow simulator");
// Select the gas mixture (0: 97% Xe + 3% isobutane, 1: 90% Xe + 10% CO2)
//TRD->SetGasMix(1);
//if (kTRUE) {
//TRD->SetPHOShole();
//TRD->SetRICHhole();
//}

//AliTRDsim TRDsim = TRD->CreateTR();

// FMD
//AliFMD FMD = new AliFMDv1("FMD", "normal FMD");
// MUON parameters
/*AliMUON MUON = new AliMUONv1("MUON", "default");
MUON->AddGeometryBuilder(new AliMUONSt1GeometryBuilder(MUON));
MUON->AddGeometryBuilder(new AliMUONSt2GeometryBuilder(MUON));
MUON->AddGeometryBuilder(new AliMUONSlatGeometryBuilder(MUON));
MUON->AddGeometryBuilder(new AliMUONTriggerGeometryBuilder(MUON));

// PHOS
AliPHOS PHOS = new AliPHOSv1("PHOS", "IHEP");
// PMD
AliPMD PMD = new AliPMDv1("PMD", "normal PMD");
// START
AliSTART START = new AliSTARTv1("START", "START Detector");
// EMCAL
*/
AliEMCAL EMCAL = new AliEMCALv2("EMCAL", "SHISH");
// VZERO
//AliVZERO VZERO = new AliVZEROv5("VZERO", "normal VZERO");
}

