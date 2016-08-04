#ifndef BMNGEMALIGNMENT_H
#define BMNGEMALIGNMENT_H 1

#include <TMath.h>
#include <TNamed.h>
#include "BmnGemStripReadoutModule.h"
#include "BmnGemStripDigit.h"
#include "BmnGemStripHit.h"
#include <TChain.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "BmnGemTrack.h"
#include "FairTrackParam.h"
#include "BmnAlignmentContainer.h"
#include "BmnGemStripStationSet.h"
#include "BmnGemStripStationSet_RunSummer2016.h"
#include <TH2.h>
#include <limits.h>
#include <TString.h>
#include <TSystem.h>
#include <TFile.h>
#include "BmnMille.h"

using namespace std;
using namespace TMath;

class BmnGemAlignment : public TNamed {
public:

    BmnGemAlignment() {};
    
    // Constructor to be used in case of digits
    BmnGemAlignment(Char_t*, Char_t*);
    
    
    virtual ~BmnGemAlignment();

    // Getters
    void SetDebugInfo(Bool_t val) {
        fDebugInfo = val;
    }

    // Setters
    void SetNofEvents(Int_t val) {
        if (val < 1)
            fNumEvents = fChainIn->GetEntries();
        else 
            fNumEvents = val;   
    }
    
    void SetNstat(Int_t val) {
        fNstat = val;
    }
    
    void SetMaxNofHitsPerEvent(Int_t val) {
        fMaxNofHits = val;
    }
    
    void SetSignalToNoise(Double_t val) {
        fSignalToNoise = val;
    }
    
    void SetChi2Max(Double_t val) {
        fChi2Max = val;
    }
    
    void SetThreshold(Double_t val) {
        fThreshold = val;
    }
    
    void SetMinHitsAccepted(Int_t val) {
        fMinHitsAccepted = val;
    }
    
    void SetXhitMinMax(Double_t min, Double_t max) {
        fXhitMin = min;
        fXhitMax = max;  
    }
    
    void SetYhitMinMax(Double_t min, Double_t max) {
        fYhitMin = min;
        fYhitMax = max;  
    }
    void SetAlignmentDim(TString dim) {
        if (dim == "xy" || dim == "xyz") {
            fAlignmentType = dim;
         cout << "Type " << fAlignmentType << " established" << endl;   
        }
        else {
            cout << "Specify a correct type of alignment" << endl;
            //Fatal("Хуйло ты проклятое!", "Хуйло ты проклятое!");
            throw;
          
        }
    }
    
    void PrepareData();
    void StartMille();
    void StartPede() {};
   
   
private:

    void LineFit3D(TLorentzVector*, TLorentzVector*, TVector3&, TVector3&, TClonesArray*, TClonesArray*) {};
    Double_t LineFit3D(vector <BmnGemStripHit*>, TVector3&, TVector3&);
    void CreateTrack(TVector3, TVector3, BmnGemTrack&, FairTrackParam&, Double_t, Int_t);
    Bool_t isOneTrack(TClonesArray*);
    
    void goToStations(vector<BmnGemStripHit*>&, vector<BmnGemStripHit*>*, Int_t);
    void DeriveFoundTrackParams(vector<BmnGemStripHit*>);
    
    Char_t* fDigiFilename;
    TChain* fChainIn;
    TChain* fChainOut;
    
    TFile* fRecoFile;
    TTree* fRecoTree;
    Char_t* fRecoFileName;
        
    Int_t fNumEvents;
    Int_t fNstat;
    Int_t fMaxNofHits;
    
    Double_t fSignalToNoise;
    Double_t fThreshold;
    Double_t fChi2Max;
    Int_t fMinHitsAccepted;
    
    Double_t fXhitMin;
    Double_t fXhitMax;
    Double_t fYhitMin;
    Double_t fYhitMax;
    
    TClonesArray* fGemDigits;
    TClonesArray* fGemHits;
    TClonesArray* fGemTracks;
    TClonesArray* fContainer;
    
    TClonesArray* fTrHits;
    
    Bool_t fDebugInfo;
    
    TString fAlignmentType;
    ClassDef(BmnGemAlignment, 1)
};

#endif