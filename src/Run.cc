#include "Run.hh"

RunAction::RunAction()
{
  G4AnalysisManager * manager = G4AnalysisManager::Instance();
  manager->SetNtupleMerging(true);
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4RunManager::GetRunManager()->SetPrintProgress(0);
  G4RunManager::GetRunManager()->SetVerboseLevel(0);
  G4AnalysisManager * manager = G4AnalysisManager::Instance();
  manager->OpenFile("Simulation.root");

  auto detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());  
  auto SDs = detectorConstruction->GetSDName();
    
  for (G4int j = 0; j < SDs.size(); j++)
  {  
     manager->CreateNtuple(SDs[j],SDs[j]);
     manager->CreateNtupleIColumn("EventID");
     manager->CreateNtupleIColumn("TrackID");
     manager->CreateNtupleDColumn("track_end_X");
     manager->CreateNtupleDColumn("track_end_Y");
     manager->CreateNtupleDColumn("track_end_Z");
     manager->CreateNtupleDColumn("Edep");
     manager->CreateNtupleIColumn("CopyNo");
     manager->CreateNtupleSColumn("Volume");
     manager->CreateNtupleSColumn("Particle");
     manager->CreateNtupleDColumn("track_length_X");
     manager->CreateNtupleDColumn("track_length_Y");
     manager->CreateNtupleDColumn("track_length_Z");
     manager->CreateNtupleDColumn("track_length");
     manager->CreateNtupleDColumn("Dose");
     manager->FinishNtuple();
   }
}

void RunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager * manager = G4AnalysisManager::Instance();
  manager->Write();
  manager->CloseFile();
}


