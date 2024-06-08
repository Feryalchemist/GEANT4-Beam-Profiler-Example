#include "Event.hh"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

EventAction::EventAction(RunAction*)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{}

void EventAction::EndOfEventAction(const G4Event* event)
{ 
  auto detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  auto manager = G4AnalysisManager::Instance();
  auto SDs     = detectorConstruction->GetSDName();
  
  vector<G4double> CSDEdep;
  vector<G4int>    EventID;
  vector<G4int>    CopyNo;
  vector<G4String> Volume;
  
  for (G4int j = 0; j < SDs.size(); j++)
  {
     G4String HCName = SDs[j];
     G4int    HCID   = G4SDManager::GetSDMpointer()->GetCollectionID(HCName);
     auto     HC     = static_cast<const DetectorHitsCollection*>(event->GetHCofThisEvent()->GetHC(HCID));
     for (G4int i=0; i < HC->entries(); i++)
     {
        G4double SDEdep = (*HC)[i]->GetEdep();
        G4double ref    = 0;
        if (SDEdep > ref)
          { 
            //-------- FWHM broadening --------
            //G4double FWHM  = 2e-3;
            //G4double sigma = FWHM/(2*sqrt(2*log(2)));
            //G4String det   = "Scintillator";
            //if (HCName == det){
            //  SDEdep = G4RandGauss::shoot(SDEdep,sigma);
            
            manager->FillNtupleIColumn(j,0,(*HC)[i]->GetEventID());      
            manager->FillNtupleIColumn(j,1,(*HC)[i]->GetTrackID());
            manager->FillNtupleDColumn(j,2,(*HC)[i]->GetPos()[0]);
            manager->FillNtupleDColumn(j,3,(*HC)[i]->GetPos()[1]);
            manager->FillNtupleDColumn(j,4,(*HC)[i]->GetPos()[2]);
            manager->FillNtupleDColumn(j,5,SDEdep);
            manager->FillNtupleIColumn(j,6,(*HC)[i]->GetCopyNo());
            manager->FillNtupleSColumn(j,7,HCName);
            manager->FillNtupleSColumn(j,8,(*HC)[i]->GetParticle());
            manager->FillNtupleDColumn(j,9,(*HC)[i]->GetDist()[0]);
            manager->FillNtupleDColumn(j,10,(*HC)[i]->GetDist()[1]);
            manager->FillNtupleDColumn(j,11,(*HC)[i]->GetDist()[2]);
            manager->FillNtupleDColumn(j,12,(*HC)[i]->GetTrack());
            manager->FillNtupleDColumn(j,13,(*HC)[i]->GetDose());
            manager->AddNtupleRow(j);
          };
              
        CSDEdep.push_back(SDEdep);
        Volume.push_back( HCName);
        EventID.push_back((*HC)[i]->GetEventID());
        CopyNo.push_back( (*HC)[i]->GetCopyNo() );
      };
   };
      
}












