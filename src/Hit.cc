#include "Hit.hh"

DetectorHit::DetectorHit()
{
  fEdep  = 0;               // Deposited Energy   [MeV]
  fTrack = 0;               // Track Length       [MeV/cm2]
  fDist  = G4ThreeVector(); // Distance vector    [mm]
  fDose  = 0;               // Absorbed Dose      [MeV/kg]
  fPos   = G4ThreeVector(); // Termination Point  [mm]
  fevID  = 0;               // Event ID         
  ftrID  = 0;               // Track ID
  fpart  = "None";          // Particle
  fcopy  = 0;               // Copy Number
}

DetectorHit::~DetectorHit()
{}
