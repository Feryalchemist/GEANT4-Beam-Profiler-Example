#include "Detector.hh"

SensitiveDetector::SensitiveDetector(G4String name, G4int noReplica)
  : G4VSensitiveDetector(name),
    fnoReplica(noReplica)
{
   collectionName.insert(name);
}

SensitiveDetector::~SensitiveDetector()
{}

void SensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{ 
  hitCollection = new DetectorHitsCollection(GetName(), collectionName[0]); 
  G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  HCE->AddHitsCollection(HCID, hitCollection);
  
  for (G4int i=0; i<fnoReplica; i++){
    hitCollection->insert(new DetectorHit());
  }
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{  
  // ==== Access Pre Emission Track
  G4StepPoint *preStepPoint  = aStep->GetPreStepPoint();
  G4ThreeVector pre_pos      = preStepPoint->GetPosition();
  G4int pre_copyNo           = preStepPoint->GetTouchable()->GetCopyNumber();  
  
  // ==== Access Post Emission Track
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
  G4ThreeVector post_pos     = postStepPoint->GetPosition();
  G4int post_copyNo          = postStepPoint->GetTouchable()->GetCopyNumber();  
  
  // ==== Access Track Properties
  G4double mass      = preStepPoint->GetPhysicalVolume()->GetLogicalVolume()->GetMass();
  G4double volume    = preStepPoint->GetPhysicalVolume()->GetLogicalVolume()->GetSolid()->GetCubicVolume();
  
  G4double edep      = aStep->GetTotalEnergyDeposit();
  G4double dose      = aStep->GetTotalEnergyDeposit() / (mass/kg);
  G4ThreeVector dist = aStep->GetDeltaPosition();
  G4double track     = aStep->GetStepLength()/cm / (volume/cm/cm/cm);
  G4ThreeVector pos  = aStep->GetPostStepPoint()->GetPosition();
  G4int eventID      = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4int trackID      = aStep->GetTrack()->GetTrackID();
  G4String Particle  = aStep->GetTrack()->GetDefinition()->GetParticleName();
  G4int copyNo       = preStepPoint->GetTouchable()->GetCopyNumber();
    
  // ==== Storing Hits
  auto hit = (*hitCollection)[copyNo-1];
  hit -> Collect(edep, dose, track, dist, pos, eventID, trackID, Particle, copyNo);
  return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitCollection)
{}
