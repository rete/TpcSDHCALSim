#include <TObject.h>
#include <TGraphErrors.h>
#include <TPaveText.h>
#include <TStyle.h>
#include <TH2.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TText.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TCanvas.h>

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <string>

#include <TpcSDHCALPreAnalysis.h>
#include <CommonTools.h>

std::string buildFileName(const std::string &fileLocation,
		                          int targetThickness,
		                          int bField,
		                          int energy,
		                          const std::string &particle,
		                          int splitID)
{
	std::stringstream fileNameStream;

	fileNameStream << fileLocation
			             << "TpcSDHCALSimOutput_"
			             << "TG" << targetThickness << "cm_"
			             << "B" << bField << "T_"
			             << "E" << energy << "GeV_"
			             << "P" << particle << "_"
			             << "I" << splitID << ".root";

	return fileNameStream.str();
}

void process_tpc_sdhcal_preanalysis()
{
	std::string fileDirectory = "/home/remi/git/TpcSDHCALSim/output/v01-00-00/";
	const std::string treeName("AnalysisTree");
	const std::string physicsList("FTFP_BERT_HP");

	int targetThickness = 12;
	int bField = 3;
	const std::string particle("pi-");
	std::vector<int> beamEnergies;
	beamEnergies.push_back(100);
	beamEnergies.push_back(150);
	beamEnergies.push_back(200);
	beamEnergies.push_back(250);
	beamEnergies.push_back(300);

	std::vector<int> splitIDList;
	for(unsigned int i=0 ; i<100 ; i++)
		splitIDList.push_back(i);

	std::vector<TpcSDHCALPreAnalysis*> tpcSDHCALPreAnalysisStorage;

	TCanvas *cc1 = new TCanvas("cc1","Entering particle position distribution");
	cc1->Divide(3,2);
	TCanvas *cc2 = new TCanvas("cc2","N Particles reaching calorimeter");
	TCanvas *cc3 = new TCanvas("cc3","Total momentum at calorimeter");
	TCanvas *cc4 = new TCanvas("cc4","Charged particle multiplicity at calorimeter");
	TCanvas *cc5 = new TCanvas("cc5","Mean distance between particles at calorimeter");
	TCanvas *cc6 = new TCanvas("cc6","Highest momentum at calorimeter");
	TCanvas *cc7 = new TCanvas("cc7","Angle / distance to border correlation");
	cc7->Divide(3,2);
	TCanvas *cc8 = new TCanvas("cc8","Momentum distribution at calorimeter");
	TCanvas *cc9 = new TCanvas("cc9","Neutral particle multiplicity at calorimeter");

	TLegend *pReachingLegend = new TLegend(0.2,0.2,0.4,0.3);
	pReachingLegend->SetLineColor(GraphSettings::commonLegendLineColor);
	pReachingLegend->SetFillColor(GraphSettings::commonLegendFillColor);

	TLegend *pTotalMomentumLegend = new TLegend(0.2,0.2,0.4,0.3);
	pTotalMomentumLegend->SetLineColor(GraphSettings::commonLegendLineColor);
	pTotalMomentumLegend->SetFillColor(GraphSettings::commonLegendFillColor);

	TLegend *pChargedMultiplicityLegend = new TLegend(0.2,0.2,0.4,0.3);
	pChargedMultiplicityLegend->SetLineColor(GraphSettings::commonLegendLineColor);
	pChargedMultiplicityLegend->SetFillColor(GraphSettings::commonLegendFillColor);

	TLegend *pMeanDistanceBetweenParticlesLegend = new TLegend(0.2,0.2,0.4,0.3);
	pMeanDistanceBetweenParticlesLegend->SetLineColor(GraphSettings::commonLegendLineColor);
	pMeanDistanceBetweenParticlesLegend->SetFillColor(GraphSettings::commonLegendFillColor);

	TLegend *pHighestMomentumLegend = new TLegend(0.2,0.2,0.4,0.3);
	pHighestMomentumLegend->SetLineColor(GraphSettings::commonLegendLineColor);
	pHighestMomentumLegend->SetFillColor(GraphSettings::commonLegendFillColor);

	TLegend *pMomentumLegend = new TLegend(0.2,0.2,0.4,0.3);
	pMomentumLegend->SetLineColor(GraphSettings::commonLegendLineColor);
	pMomentumLegend->SetFillColor(GraphSettings::commonLegendFillColor);

	TLegend *pNeutralMultiplicityLegend = new TLegend(0.2,0.2,0.4,0.3);
	pNeutralMultiplicityLegend->SetLineColor(GraphSettings::commonLegendLineColor);
	pNeutralMultiplicityLegend->SetFillColor(GraphSettings::commonLegendFillColor);

	int currentColor = 1;

	gStyle->SetOptStat(0);
	gROOT->ForceStyle();

	for(unsigned int e=0 ; e<beamEnergies.size() ; e++)
	{
		int beamEnergy = beamEnergies.at(e);

		std::stringstream ss;
		ss << "EnteringPosition_" << beamEnergy << "GeV";
		TH2F *pEnteringPositionHistogram = new TH2F(ss.str().c_str(), ss.str().c_str(), 100, -500, 500, 100, -500, 500);
		ss.str("");
		ss << "AngleVersusDistanceToBorder_" << beamEnergy << "GeV";
		TH2F *pAngleVersusDistanceToBorderHistogram = new TH2F(ss.str().c_str(), ss.str().c_str(), 50, 0, 500, 80, 0, 3.1415/2);
		ss.str("");
		ss << "nParticlesAtCalo_" << beamEnergy << "GeV";
		TH1F *pNParticlesAtCaloHistogram = new TH1F(ss.str().c_str(), ss.str().c_str(), 60, 0, 60);
		ss.str("");
		ss << "TotalMomentumAtCalo_" << beamEnergy << "GeV";
		TH1F *pTotalMomentumAtCaloHistogram = new TH1F(ss.str().c_str(), ss.str().c_str(), beamEnergies.back()/5.0, 0, beamEnergies.back());
		ss.str("");
		ss << "ChargedMultiplicityAtCalo_" << beamEnergy << "GeV";
		TH1F *pChargedMultiplicityAtCaloHistogram = new TH1F(ss.str().c_str(), ss.str().c_str(), 100, 0, 99);
		ss.str("");
		ss << "MeanDistanceBetweenParticlesAtCalo_" << beamEnergy << "GeV";
		TH1F *pMeanDistanceBetweenParticlesAtCaloHistogram = new TH1F(ss.str().c_str(), ss.str().c_str(), 100, 0, 1000);
		ss.str("");
		ss << "HighestMomentumAtCalo_" << beamEnergy << "GeV";
		TH1F *pHighestMomentumAtCaloHistogram = new TH1F(ss.str().c_str(), ss.str().c_str(), 100, 0, 350);
		ss.str("");
		ss << "MomentumAtCalo_" << beamEnergy << "GeV";
		TH1F *pMomentumAtCaloHistogram = new TH1F(ss.str().c_str(), ss.str().c_str(), 50, 0, 125);
		ss.str("");
		ss << "NeutralMultiplicityAtCalo_" << beamEnergy << "GeV";
		TH1F *pNeutralMultiplicityAtCaloHistogram = new TH1F(ss.str().c_str(), ss.str().c_str(), 100, 0, 99);
		ss.str("");

		std::string drawOption = e == 0 ? "" : "SAME";

		for(unsigned int s=0 ; s<splitIDList.size() ; s++)
		{
			int splitID = splitIDList.at(s);

			std::string fileName = buildFileName(fileDirectory, targetThickness, bField, beamEnergy, particle, splitID);

			TFile *pFile = TFile::Open(fileName.c_str());

			// some problems with 3 root files ...
			if(pFile == 0)
				continue;

			TTree *pTree = (TTree *) pFile->Get(treeName.c_str());

			TpcSDHCALPreAnalysis *pAnalysis = new TpcSDHCALPreAnalysis(pTree);
			tpcSDHCALPreAnalysisStorage.push_back(pAnalysis);

			pAnalysis->m_pNParticlesAtCaloHistogram = pNParticlesAtCaloHistogram;
			pAnalysis->m_pTotalMomentumAtCaloHistogram = pTotalMomentumAtCaloHistogram;
			pAnalysis->m_pEnteringPositionHistogram = pEnteringPositionHistogram;
			pAnalysis->m_pChargedParticleMultiplicityAtCaloHistogram = pChargedMultiplicityAtCaloHistogram;
			pAnalysis->m_pDistanceBetweenParticlesAtCaloHistogram = pMeanDistanceBetweenParticlesAtCaloHistogram;
			pAnalysis->m_pHighestMomentumAtCaloHistogram = pHighestMomentumAtCaloHistogram;
			pAnalysis->m_pAngleVersusDistanceToBorderHistogram = pAngleVersusDistanceToBorderHistogram;
			pAnalysis->m_pMomentumAtCaloHistogram = pMomentumAtCaloHistogram;
			pAnalysis->m_pNeutralParticleMultiplicityAtCaloHistogram = pNeutralMultiplicityAtCaloHistogram;

			pAnalysis->Loop();
		}

		ss.str("");
		ss << "Entering position - E_{beam} = " << beamEnergy << " GeV";

		cc1->cd(e+1);
		cc1->SetGrid();
		pEnteringPositionHistogram->SetTitle(ss.str().c_str());
		pEnteringPositionHistogram->GetXaxis()->SetTitle("x [mm]");
		pEnteringPositionHistogram->GetXaxis()->SetRangeUser(-500, 500);
		pEnteringPositionHistogram->GetYaxis()->SetTitle("y [mm]");
		pEnteringPositionHistogram->GetYaxis()->SetRangeUser(-500, 500);
		pEnteringPositionHistogram->DrawNormalized("colz");
		cc1->Update();

		ss.str("");
		ss << "E_{beam} = " << beamEnergy << " GeV";

		cc2->cd();
		cc2->SetGrid();
		pNParticlesAtCaloHistogram->SetTitle("");
		pNParticlesAtCaloHistogram->GetXaxis()->SetTitle("N at calo");
		pNParticlesAtCaloHistogram->GetYaxis()->SetTitle("");
		pNParticlesAtCaloHistogram->SetLineColor(currentColor);
		pNParticlesAtCaloHistogram->SetLineWidth(1);
		pReachingLegend->AddEntry(pNParticlesAtCaloHistogram, ss.str().c_str(), "lp");
		pNParticlesAtCaloHistogram->Draw(drawOption.c_str());
		cc2->Update();

		cc3->cd();
		cc3->SetGrid();
		pTotalMomentumAtCaloHistogram->SetTitle("");
		pTotalMomentumAtCaloHistogram->GetXaxis()->SetTitle("p_{tot} [GeV]");
		pTotalMomentumAtCaloHistogram->GetYaxis()->SetTitle("");
		pTotalMomentumAtCaloHistogram->SetLineColor(currentColor);
		pTotalMomentumAtCaloHistogram->SetLineWidth(1);
		pTotalMomentumLegend->AddEntry(pTotalMomentumAtCaloHistogram, ss.str().c_str(), "lp");
		pTotalMomentumAtCaloHistogram->Draw(drawOption.c_str());
		cc3->Update();

		cc4->cd();
		cc4->SetGrid();
		pChargedMultiplicityAtCaloHistogram->SetTitle("");
		pChargedMultiplicityAtCaloHistogram->GetXaxis()->SetTitle("N_{ch}");
		pChargedMultiplicityAtCaloHistogram->GetYaxis()->SetTitle("");
		pChargedMultiplicityAtCaloHistogram->SetLineColor(currentColor);
		pChargedMultiplicityAtCaloHistogram->SetLineWidth(1);
		pChargedMultiplicityLegend->AddEntry(pChargedMultiplicityAtCaloHistogram, ss.str().c_str(), "lp");
		pChargedMultiplicityAtCaloHistogram->Draw(drawOption.c_str());
		cc4->Update();

		cc5->cd();
		cc5->SetGrid();
		pMeanDistanceBetweenParticlesAtCaloHistogram->SetTitle("Distance between particles at calorimeter");
		pMeanDistanceBetweenParticlesAtCaloHistogram->GetXaxis()->SetTitle("<#delta_{part}> [mm]");
		pMeanDistanceBetweenParticlesAtCaloHistogram->GetYaxis()->SetTitle("");
		pMeanDistanceBetweenParticlesAtCaloHistogram->SetLineColor(currentColor);
		pMeanDistanceBetweenParticlesAtCaloHistogram->SetLineWidth(1);
		pMeanDistanceBetweenParticlesLegend->AddEntry(pMeanDistanceBetweenParticlesAtCaloHistogram, ss.str().c_str(), "lp");
		pMeanDistanceBetweenParticlesAtCaloHistogram->DrawNormalized(drawOption.c_str());
		cc5->Update();

		cc6->cd();
		cc6->SetGrid();
		pHighestMomentumAtCaloHistogram->SetTitle("");
		pHighestMomentumAtCaloHistogram->GetXaxis()->SetTitle("Highest p [GeV]");
		pHighestMomentumAtCaloHistogram->GetYaxis()->SetTitle("");
		pHighestMomentumAtCaloHistogram->SetLineColor(currentColor);
		pHighestMomentumAtCaloHistogram->SetLineWidth(1);
		pHighestMomentumLegend->AddEntry(pHighestMomentumAtCaloHistogram, ss.str().c_str(), "lp");
		pHighestMomentumAtCaloHistogram->Draw(drawOption.c_str());
		cc6->Update();

		cc8->cd();
		cc8->SetGrid();
		pMomentumAtCaloHistogram->SetTitle("");
		pMomentumAtCaloHistogram->GetXaxis()->SetTitle("p [GeV]");
		pMomentumAtCaloHistogram->GetYaxis()->SetTitle("");
		pMomentumAtCaloHistogram->SetLineColor(currentColor);
		pMomentumAtCaloHistogram->SetLineWidth(1);
		pMomentumLegend->AddEntry(pMomentumAtCaloHistogram, ss.str().c_str(), "lp");
		pMomentumAtCaloHistogram->DrawNormalized(drawOption.c_str());
		cc8->Update();

		cc9->cd();
		cc9->SetGrid();
		pNeutralMultiplicityAtCaloHistogram->SetTitle("Neutral particle multiplicity at calorimeter");
		pNeutralMultiplicityAtCaloHistogram->GetXaxis()->SetTitle("N_{n}");
		pNeutralMultiplicityAtCaloHistogram->GetYaxis()->SetTitle("");
		pNeutralMultiplicityAtCaloHistogram->SetLineColor(currentColor);
		pNeutralMultiplicityAtCaloHistogram->SetLineWidth(1);
		pNeutralMultiplicityLegend->AddEntry(pNeutralMultiplicityAtCaloHistogram, ss.str().c_str(), "lp");
		pNeutralMultiplicityAtCaloHistogram->Draw(drawOption.c_str());
		cc9->Update();

		ss.str("");
		ss << "Angle / distance to border for E_{beam} = " << beamEnergy << " GeV";

		cc7->cd(e+1);
		cc7->SetGrid();
		pAngleVersusDistanceToBorderHistogram->SetTitle(ss.str().c_str());
		pAngleVersusDistanceToBorderHistogram->GetXaxis()->SetTitle("#Delta [mm]");
		pAngleVersusDistanceToBorderHistogram->GetXaxis()->SetRangeUser(0, 500);
		pAngleVersusDistanceToBorderHistogram->GetYaxis()->SetTitle("#theta [rad]");
		pAngleVersusDistanceToBorderHistogram->GetYaxis()->SetRangeUser(0, 3.1415/2);
		pAngleVersusDistanceToBorderHistogram->DrawNormalized("colz");
		cc7->Update();

		currentColor++;

		if(currentColor == 5)
			currentColor++;
	}

	cc2->cd();
	pReachingLegend->Draw();

	cc3->cd();
	pTotalMomentumLegend->Draw();

	cc4->cd();
	pChargedMultiplicityLegend->Draw();

	cc5->cd();
	pMeanDistanceBetweenParticlesLegend->Draw();

	cc6->cd();
	pHighestMomentumLegend->Draw();

	cc8->cd();
	pMomentumLegend->Draw();

	cc9->cd();
	pNeutralMultiplicityLegend->Draw();

	cc9->WaitPrimitive();

	for( unsigned int i=0 ; i<tpcSDHCALPreAnalysisStorage.size() ; i++ )
		delete tpcSDHCALPreAnalysisStorage.at(i);
	tpcSDHCALPreAnalysisStorage.clear();
}

