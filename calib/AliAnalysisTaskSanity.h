#ifndef AliAnalysisTaskSanity_cxx
#define AliAnalysisTaskSanity_cxx

// example of an analysis task creating a p_t spectrum
// Authors: Panos Cristakoglou, Jan Fiete Grosse-Oetringhaus, Christian Klein-Boesing

class TH1F;
class TH2F;
class AliESDEvent;

#include <AliAnalysisTaskSE.h>

class AliAnalysisTaskSanity : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskSanity(); //default constructor
  AliAnalysisTaskSanity(const char *name);
  virtual ~AliAnalysisTaskSanity() {}
  
  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *option);
  virtual void   Terminate(Option_t *);
  
 private:
  AliVEvent *fESD;    //! ESD object
  TList       *fOutputList; //! Output list
  TH1F        *fHistTrackEMId; //! Track Pt spectrum
  TH1F        *fHistTrackTOFId; //Track TOF Spectrum
  TH1F        *fHistEMClus;
  TH2F        *fHistTOFClus;
  
  AliAnalysisTaskSanity(const AliAnalysisTaskSanity&); // not implemented
  AliAnalysisTaskSanity& operator=(const AliAnalysisTaskSanity&); // not implemented
  
  ClassDef(AliAnalysisTaskSanity, 1); // example of analysis
};

#endif
