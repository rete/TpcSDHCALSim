#define TpcSDHCALPreAnalysis_cxx
#include "TpcSDHCALPreAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TVector3.h>

void TpcSDHCALPreAnalysis::Loop()
{
	if (fChain == 0)
	{
		std::cout << "Problem with fChain" << std::endl;
		return;
	}

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;

	TVector3 ez(0,0,1);

	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);

		if (ientry < 0)
		{
			std::cout << "Problem with ientry" << std::endl;
			break;
		}

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		if(nParticlesAtCalo < 2)
			continue;

		FillHistogram(m_pTotalMomentumAtCaloHistogram, totalEventMomentumAtCalo/1000);

		FillHistogram(m_pChargedParticleMultiplicityAtCaloHistogram, Float_t(nChargedParticlesAtCalo));
		FillHistogram(m_pNeutralParticleMultiplicityAtCaloHistogram, Float_t(nNeutralParticlesAtCalo));

		FillHistogram(m_pHighestMomentumAtCaloHistogram, highestMomentumAtCalo/1000);

		FillHistogram(m_pMeanDistanceBetweenParticlesAtCaloHistogram, meanDistanceBetweenParticlesAtCalo);

		int nParticlesReachingCalo = 0;

		for(unsigned int n=0 ; n<enteringPointAtCaloX->size() ; n++)
		{
			FillHistogram(m_pMomentumAtCaloHistogram, particleMomentumAtCalo->at(n)/1000);

			if(particleMomentumAtCalo->at(n)/1000 < momentumCutForDistanceBetweenParticlesAtCalo)
				continue;

			nParticlesReachingCalo ++;

			FillHistogram(m_pEnteringPositionHistogram, enteringPointAtCaloX->at(n), enteringPointAtCaloY->at(n));

			Double_t distanceToBorder = fabs(enteringPointAtCaloX->at(n)) > fabs(enteringPointAtCaloY->at(n)) ? fabs(enteringPointAtCaloY->at(n)) : fabs(enteringPointAtCaloX->at(n));
			Double_t angle = ez.Angle(TVector3(particleMomentumAtCaloX->at(n), particleMomentumAtCaloY->at(n), particleMomentumAtCaloZ->at(n)));
			FillHistogram(m_pAngleVersusDistanceToBorderHistogram, distanceToBorder, angle);

			for(unsigned int n2=n+1 ; n2<enteringPointAtCaloX->size() ; n2++)
			{
				if(particleMomentumAtCalo->at(n2)/1000 < momentumCutForDistanceBetweenParticlesAtCalo)
					continue;

				TVector3 pos1(enteringPointAtCaloX->at(n),  enteringPointAtCaloY->at(n), 0);
				TVector3 pos2(enteringPointAtCaloX->at(n2), enteringPointAtCaloY->at(n2), 0);

				FillHistogram(m_pDistanceBetweenParticlesAtCaloHistogram, (pos1-pos2).Mag());
			}
		}

		FillHistogram(m_pNParticlesAtCaloHistogram, nParticlesReachingCalo);

	}
}


void TpcSDHCALPreAnalysis::FillHistogram(TH1F *pHistogram, float value)
{
	if(pHistogram != NULL)
		pHistogram->Fill(value);
}


void TpcSDHCALPreAnalysis::FillHistogram(TH2F *pHistogram, float value1, float value2)
{
	if(pHistogram != NULL)
		pHistogram->Fill(value1, value2);
}
