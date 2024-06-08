#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4Cache.hh"

#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4UniformElectricField.hh"
#include "G4AutoDelete.hh"

#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"

class G4FieldManager;
class G4ChordFinder;
class G4EquationOfMotion;
class G4Mag_EqRhs;
class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;

#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EquationOfMotion.hh"
#include "G4EqMagElectricField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

#include "G4ClassicalRK4.hh"

#include "Detector.hh"
#include <iostream>
#include <vector>

using namespace std;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
     DetectorConstruction();
     ~DetectorConstruction();
     virtual G4VPhysicalVolume *Construct();
    
    vector<G4String> GetSDName() const {return SDName;}; 
    
    //Two different logical volumes with different local fields
    G4LogicalVolume* fElectriclogical_1;
    G4LogicalVolume* fElectriclogical_2;

    //Setup the required objects of the FIRST local field
    G4ElectricField*        fEMfield_1;
    G4EqMagElectricField*   fEquation_1;
    G4MagIntegratorStepper* fStepper_1;
    G4FieldManager*         fFieldMgr_1;
    G4double                fMinStep_1;
    G4ChordFinder*          fChordFinder_1;

    //Setup the required objects of the SECOND local field
    G4ElectricField*        fEMfield_2;
    G4EqMagElectricField*   fEquation_2;
    G4MagIntegratorStepper* fStepper_2;
    G4FieldManager*         fFieldMgr_2;
    G4double                fMinStep_2;
    G4ChordFinder*          fChordFinder_2;

    //world electric field
    G4ElectricField*        fEMfield_WORLD;
    G4EqMagElectricField*   fEquation_WORLD;
    G4MagIntegratorStepper* fStepper_WORLD;
    G4FieldManager*         fFieldMgr_WORLD;
    G4double                fMinStep_WORLD;
    G4ChordFinder*          fChordFinder_WORLD;
    
  private:
    vector<G4int>            noReplica;
    vector<G4String>         SDName;
    vector<G4LogicalVolume*> FieldDetector;
    vector<G4LogicalVolume*> LogicDetector;
    vector<G4ThreeVector>    EField;
    virtual void ConstructSDandField();
};
#endif
