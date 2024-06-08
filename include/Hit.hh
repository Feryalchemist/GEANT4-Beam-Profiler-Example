#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"

class DetectorHit : public G4VHit
{
  public:
    DetectorHit();
    ~DetectorHit();
  void Collect(G4double edep, G4double dose, G4double track, G4ThreeVector dist, G4ThreeVector pos,
               G4int eventID, G4int trackID, G4String Particle, G4int copyNo) 
  {
    G4String ref="None";
    fEdep += edep;
    fDose += dose;
    fTrack+= track;
    fDist += dist;
    fPos   = pos;
    fevID  = eventID;
    ftrID  = trackID;
    if (fpart == ref){
       fpart  = Particle;}
    fcopy  = copyNo;
  };
  
  G4double GetEdep()      const{return fEdep;};
  G4double GetDose()      const{return fDose;};
  G4double GetTrack()     const{return fTrack;};
  G4ThreeVector GetDist() const{return fDist;};
  G4ThreeVector GetPos()  const{return fPos;};
  G4int GetEventID()      const{return fevID;};
  G4int GetTrackID()      const{return ftrID;};
  G4String GetParticle()  const{return fpart;};
  G4int GetCopyNo()       const{return fcopy;};
  
  private:
     G4int         fevID, ftrID, fcopy;
     G4double      fEdep, fTrack, fDose;
     G4String      fpart;
     G4ThreeVector fDist, fPos;
};

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;

#endif
