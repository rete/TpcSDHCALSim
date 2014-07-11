#include "time.h"

// Geant4 headers
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIQt.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4StepLimiter.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "QGSP_FTFP_BERT.hh"
#include "Randomize.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UIterminal.hh"

// tpc sdhcal sim
#include "DetectorConstruction.h"
#include "GlobalMessenger.h"
#include "EventAction.h"
#include "TrackingAction.h"
#include "SteppingAction.h"
#include "RunAction.h"
#include "DetectorConstruction.h"
#include "PrimaryGeneratorAction.h"
#include "FTFP_BERT_HP.hh"  // physics lists
#include "RootFileManager.h"
#include "TpcSDHCALSimConfig.h"

// tclap
#include "tclap/CmdLine.h"
#include "tclap/Arg.h"

// the namespace for this executable
using namespace tpc_sdhcal;

int main(int argc,char** argv)
{
	std::string cmdLineFooter = "Please report bug to <rete@ipnl.in2p3.fr>";
	TCLAP::CmdLine *pCommandLine = new TCLAP::CmdLine(cmdLineFooter, ' ', TpcSDHCALSim_VERSION);

	// random seed
	TCLAP::ValueArg<int> randomSeedArg(
					"d"
			, "random-seed"
			, "The random seed for geant 4 simulation"
			, false
			, 0
			, "int");
	pCommandLine->add(randomSeedArg);

	// mac file
	TCLAP::ValueArg<std::string> macFileArg(
					"m"
			, "mac-file"
			, "The mac file for geant 4 simulation"
			, true
			, ""
			, "string");
	pCommandLine->add(macFileArg);

	// interactive session
	TCLAP::SwitchArg interactiveSessionArg(
				"i"
				,"interactive"
				,"Whether to open an interactive session"
				,false);
	pCommandLine->add(interactiveSessionArg);

	pCommandLine->parse(argc, argv);

	//Choose the Random engine
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
	G4long seed = 0;

	if(randomSeedArg.isSet())
		seed = randomSeedArg.getValue();
	else
		seed = time(NULL);

	CLHEP::HepRandom::setTheSeed(seed);

	// the run manager
 G4RunManager* pRunManager = new G4RunManager();

 // the global messenger
 GlobalMessenger *pGlobalMessenger = new GlobalMessenger();

 // detector geometry setup
 DetectorConstruction* pDetectorConstruction = new DetectorConstruction();
 pGlobalMessenger->SetDetectorConstruction(pDetectorConstruction);
 pRunManager->SetUserInitialization(pDetectorConstruction);

	// physics lists
	G4VUserPhysicsList* pPhysicsLists = new FTFP_BERT_HP();
	pRunManager->SetUserInitialization(pPhysicsLists);

	// primary generator action
 G4VUserPrimaryGeneratorAction* pPrimaryGeneratorAction = new PrimaryGeneratorAction();
 pRunManager->SetUserAction(pPrimaryGeneratorAction);

 // run action
 RunAction* pRunAction = new RunAction();
 pGlobalMessenger->SetRunAction(pRunAction);
 pRunManager->SetUserAction(pRunAction);

 // event action
 EventAction* pEventAction = new EventAction();
 pGlobalMessenger->SetEventAction(pEventAction);
 pRunManager->SetUserAction(pEventAction);

 // tracking action
 TrackingAction* pTrackingAction = new TrackingAction();
 pGlobalMessenger->SetTrackingAction(pTrackingAction);
 pRunManager->SetUserAction(pTrackingAction);

 // stepping action
 SteppingAction* pSteppingAction = new SteppingAction();
// pGlobalMessenger->SetSteppingAction(pSteppingAction);
 pRunManager->SetUserAction(pSteppingAction);

 G4UIExecutive* pUISession = NULL;
 G4VisManager* pVisManager = NULL;

 if(interactiveSessionArg.getValue())
 {
  pUISession = new G4UIExecutive(argc, argv) ;
		pVisManager = new G4VisExecutive();
		pVisManager->Initialize() ;
 }

 G4UImanager* pUIManager = G4UImanager::GetUIpointer();

 // !!! ATTENTION : Run manager initialization is done via the mac file !!!!
	G4String command = "/control/execute ";
	pUIManager->ApplyCommand(command + macFileArg.getValue());

 if(interactiveSessionArg.getValue())
 {
  pUISession->SessionStart();
		delete pUISession;
		delete pVisManager;
 }

	delete pRunManager;

	RootFileManager *pRootFileManager = RootFileManager::GetInstance();

	if(pRootFileManager->IsFileOpened())
	{
		bool success = pRootFileManager->Write();

		if(!success)
			std::cerr << "Couldn't write output file <" << pRootFileManager->GetRootFileName() << ">" << std::endl;
	}

	return 0;
}
