//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 11 16:17:11 2014 by ROOT version 5.34/05
// from TTree AnalysisTree/AnalysisTree
// found on file: ../TpcSDHCALSimOutput_TG5cm_B3T_E100GeV_Ppi-.root
//////////////////////////////////////////////////////////

#ifndef TpcSDHCALPreAnalysis_h
#define TpcSDHCALPreAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <stdexcept>
#include <TH2F.h>
#include <TH1F.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class TpcSDHCALPreAnalysis
{
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           nParticlesAtCalo;
   Int_t           nNeutralParticlesAtCalo;
   Int_t           nChargedParticlesAtCalo;
   Double_t        meanDistanceBetweenParticlesAtCalo;
   Double_t        totalEventMomentumAtCalo;
   Double_t        minimumDistanceBetweenParticlesAtCalo;
   Double_t        highestMomentumAtCalo;
   std::vector<double>  *enteringPointAtCaloX;
   std::vector<double>  *enteringPointAtCaloY;
   std::vector<int>     *particleChargeAtCalo;
   std::vector<double>  *particleMomentumAtCaloX;
   std::vector<double>  *particleMomentumAtCaloY;
   std::vector<double>  *particleMomentumAtCaloZ;
   std::vector<double>  *particleMomentumAtCalo;
   std::vector<int>     *particleTrackIDAtCalo;

   // List of branches
   TBranch        *b_nParticlesAtCalo;   //!
   TBranch        *b_nNeutralParticlesAtCalo;   //!
   TBranch        *b_nChargedParticlesAtCalo;   //!
   TBranch        *b_meanDistanceBetweenParticlesAtCalo;   //!
   TBranch        *b_totalEventMomentumAtCalo;   //!
   TBranch        *b_minimumDistanceBetweenParticlesAtCalo;   //!
   TBranch        *b_highestMomentumAtCalo;   //!
   TBranch        *b_enteringPointAtCaloX;   //!
   TBranch        *b_enteringPointAtCaloY;   //!
   TBranch        *b_particleChargeAtCalo;   //!
   TBranch        *b_particleMomentumAtCaloX;   //!
   TBranch        *b_particleMomentumAtCaloY;   //!
   TBranch        *b_particleMomentumAtCaloZ;   //!
   TBranch        *b_particleMomentumAtCalo;   //!
   TBranch        *b_particleTrackIDAtCalo;   //!

   TpcSDHCALPreAnalysis(TTree *tree=0);
   virtual ~TpcSDHCALPreAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void              FillHistogram(TH1F *pHistogram, float value);
   void              FillHistogram(TH2F *pHistogram, float value1, float value2);

   TH2F *m_pEnteringPositionHistogram;
   TH2F *m_pAngleVersusDistanceToBorderHistogram;
   TH1F *m_pTotalMomentumAtCaloHistogram;
   TH1F *m_pMomentumAtCaloHistogram;
   TH1F *m_pNParticlesAtCaloHistogram;
   TH1F *m_pChargedParticleMultiplicityAtCaloHistogram;
   TH1F *m_pNeutralParticleMultiplicityAtCaloHistogram;
   TH1F *m_pMeanDistanceBetweenParticlesAtCaloHistogram;
   TH1F *m_pDistanceBetweenParticlesAtCaloHistogram;
   TH1F *m_pHighestMomentumAtCaloHistogram;

   float momentumCutForDistanceBetweenParticlesAtCalo;
};

#endif

#ifdef TpcSDHCALPreAnalysis_cxx
TpcSDHCALPreAnalysis::TpcSDHCALPreAnalysis(TTree *tree) : fChain(0) 
{
	if (tree == 0)
		throw std::invalid_argument("Tree is NULL");

	Init(tree);

	m_pEnteringPositionHistogram = NULL;
	m_pAngleVersusDistanceToBorderHistogram = NULL;
	m_pNParticlesAtCaloHistogram = NULL;
	m_pTotalMomentumAtCaloHistogram = NULL;
	m_pMomentumAtCaloHistogram = NULL;
	m_pChargedParticleMultiplicityAtCaloHistogram = NULL;
	m_pMeanDistanceBetweenParticlesAtCaloHistogram = NULL;
	m_pDistanceBetweenParticlesAtCaloHistogram = NULL;
	m_pHighestMomentumAtCaloHistogram = NULL;
	m_pNeutralParticleMultiplicityAtCaloHistogram = NULL;

	momentumCutForDistanceBetweenParticlesAtCalo = 10;
}

TpcSDHCALPreAnalysis::~TpcSDHCALPreAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TpcSDHCALPreAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TpcSDHCALPreAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TpcSDHCALPreAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   enteringPointAtCaloX = 0;
   enteringPointAtCaloY = 0;
   particleChargeAtCalo = 0;
   particleMomentumAtCaloX = 0;
   particleMomentumAtCaloY = 0;
   particleMomentumAtCaloZ = 0;
   particleMomentumAtCalo = 0;
   particleTrackIDAtCalo = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nParticlesAtCalo", &nParticlesAtCalo, &b_nParticlesAtCalo);
   fChain->SetBranchAddress("nNeutralParticlesAtCalo", &nNeutralParticlesAtCalo, &b_nNeutralParticlesAtCalo);
   fChain->SetBranchAddress("nChargedParticlesAtCalo", &nChargedParticlesAtCalo, &b_nChargedParticlesAtCalo);
   fChain->SetBranchAddress("meanDistanceBetweenParticlesAtCalo", &meanDistanceBetweenParticlesAtCalo, &b_meanDistanceBetweenParticlesAtCalo);
   fChain->SetBranchAddress("totalEventMomentumAtCalo", &totalEventMomentumAtCalo, &b_totalEventMomentumAtCalo);
   fChain->SetBranchAddress("minimumDistanceBetweenParticlesAtCalo", &minimumDistanceBetweenParticlesAtCalo, &b_minimumDistanceBetweenParticlesAtCalo);
   fChain->SetBranchAddress("highestMomentumAtCalo", &highestMomentumAtCalo, &b_highestMomentumAtCalo);
   fChain->SetBranchAddress("enteringPointAtCaloX", &enteringPointAtCaloX, &b_enteringPointAtCaloX);
   fChain->SetBranchAddress("enteringPointAtCaloY", &enteringPointAtCaloY, &b_enteringPointAtCaloY);
   fChain->SetBranchAddress("particleChargeAtCalo", &particleChargeAtCalo, &b_particleChargeAtCalo);
   fChain->SetBranchAddress("particleMomentumAtCaloX", &particleMomentumAtCaloX, &b_particleMomentumAtCaloX);
   fChain->SetBranchAddress("particleMomentumAtCaloY", &particleMomentumAtCaloY, &b_particleMomentumAtCaloY);
   fChain->SetBranchAddress("particleMomentumAtCaloZ", &particleMomentumAtCaloZ, &b_particleMomentumAtCaloZ);
   fChain->SetBranchAddress("particleMomentumAtCalo", &particleMomentumAtCalo, &b_particleMomentumAtCalo);
   fChain->SetBranchAddress("particleTrackIDAtCalo", &particleTrackIDAtCalo, &b_particleTrackIDAtCalo);
   Notify();
}

Bool_t TpcSDHCALPreAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TpcSDHCALPreAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TpcSDHCALPreAnalysis::Cut(Long64_t)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TpcSDHCALPreAnalysis_cxx
